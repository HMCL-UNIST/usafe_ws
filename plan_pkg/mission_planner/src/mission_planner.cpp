#include "mission_planner.h"
#define PI 3.14159265358979323846264338

#include <sstream>
#include <string>
#include <list>
#include <mutex>
#include <iostream>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <math.h>

#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <ros/package.h>



MissionStateMachine::MissionStateMachine(){

    nh_.param<double>("runRate", runRate, 10);
    nh_.param<int>("thresInit", thresInit, 30);
    nh_.param<int>("thresChooseDifficulty", thresChooseDifficulty, 5);
    nh_.param<int>("thresMissionRequest", thresMissionRequest, 5);
    nh_.param<int>("thresDriveToStartPos", thresDriveToStartPos, 600);
    nh_.param<int>("thresStartArrivalRequest", thresStartArrivalRequest, 20);
    nh_.param<int>("thresDriveToGoalPos", thresDriveToGoalPos, 600);
    nh_.param<int>("thresGoalArrivalRequest", thresGoalArrivalRequest, 20);

    v2x_mission_sub = nh_.subscribe("/Mission1", 1, &MissionStateMachine::v2xMissionCallback, this);
    v2x_rsp_sub = nh_.subscribe("/Request", 1, &MissionStateMachine::v2xResponseCallback, this);
    behavior_sub = nh_.subscribe("/behavior_state", 1, &MissionStateMachine::behaviorCallback, this);

    mission_pub = nh_.advertise<std_msgs::Int16>("/mission_state",1,true);
    // mission_timer = nh_.createTimer(ros::Duration(0.05), &MissionStateMachine::mission_handler,this);

    // mission transition conditions
    statusWait = false;
    statusStart = false;
    missionRequestSuccess = false;
    arriveAtStartPos = false;
    startArrivalSuccess = false;
    arriveAtGoalPos = false;
    goalArrivalSuccess = false;

    countInit = 0;
    countChooseDifficulty = 0;
    countMissionRequest = 0;
    countDriveToStartPos = 0;
    countStartArrivalRequest = 0;
    countDriveToGoalPos = 0;
    countGoalArrivalRequest = 0;


    currentMission = Init;
    boost::thread callbackhandler(&MissionStateMachine::callbackthread,this); 
}
void MissionStateMachine::callbackthread()
{   
    ros::Rate loop_rate(runRate); // rate  
    while(ros::ok()){
        updateMissionState();
        loop_rate.sleep();
    }
}
MissionStateMachine::MissionStateMachine(MissionState mState){

    v2x_mission_sub = nh_.subscribe("/Mission1", 1, &MissionStateMachine::v2xMissionCallback, this);
    v2x_rsp_sub = nh_.subscribe("/Request", 1, &MissionStateMachine::v2xResponseCallback, this);
    behavior_sub = nh_.subscribe("/behavior_state", 1, &MissionStateMachine::behaviorCallback, this);

    mission_pub = nh_.advertise<std_msgs::Int16>("/mission_state",1,true);
    // mission_timer = nh_.createTimer(ros::Duration(0.05), &MissionPlanner::mission_handler,this);

    // mission transition conditions
    statusWait = false;
    statusStart = false;
    missionRequestSuccess = false;
    arriveAtStartPos = false;
    startArrivalSuccess = false;
    arriveAtGoalPos = false;
    goalArrivalSuccess = false;

    currentMission = mState;
}

MissionStateMachine::~MissionStateMachine(){

}

MissionState MissionStateMachine::getCurrentMission(){
    return currentMission;
}

void MissionStateMachine::updateFactors(){

    statusWait = true; //for test
    arriveAtStartPos = false;
    // arriveAtStartPos = true; //for test
    arriveAtGoalPos = false;

    std::cout<<"--MISSION--MISSION--MISSION--MISSION--"<<std::endl;

    switch(v2xMissionStat)
    {
    case 0:
        statusWait = true;
        break;
    case 1:
        statusStart = true;
    default:
        break;
    }
    switch(currentBehavior){
        case BehaviorState::StopAtStartPos:
            arriveAtStartPos = true;
        case BehaviorState::StopAtGoalPos:
            arriveAtGoalPos = true; 
    }

//     if(countInit>thresInit*runRate){
//         statusWait = true;
//         countInit = 0;
//         ROS_INFO("Init Time Out!!!");
//     }
//     if(countChooseDifficulty>thresChooseDifficulty*runRate){
//         statusStart = true;
//         countChooseDifficulty = 0;
//         ROS_INFO("ChooseDifficulty Time Out!!!");
//     }
//     if(countMissionRequest>thresMissionRequest*runRate){
//         missionRequestSuccess = true;
//         countMissionRequest = 0;
//         ROS_INFO("MissionRequest Time Out!!!");
//     }
//     if(countDriveToStartPos>thresDriveToStartPos*runRate){
//         arriveAtStartPos = true;
//         countDriveToStartPos = 0;
//         ROS_INFO("DriveToStartPos Time Out!!!");
//     }
//     if(countStartArrivalRequest>thresStartArrivalRequest*runRate){
//         startArrivalSuccess = true;
//         countStartArrivalRequest = 0;
//         ROS_INFO("StartArrivalRequest Time Out!!!");
//     }
//     if(countDriveToGoalPos>thresDriveToGoalPos*runRate){
//         arriveAtGoalPos = true;
//         countDriveToGoalPos = 0;
//         ROS_INFO("DriveToGoalPos Time Out!!!");
//     }
//     if(countGoalArrivalRequest>thresGoalArrivalRequest*runRate){
//         goalArrivalSuccess = true;
//         countGoalArrivalRequest = 0;
//         ROS_INFO("GoalArrivalRequest Time Out!!!");
//     }
}

void MissionStateMachine::updateMissionState(){   
    updateFactors();
    switch(currentMission)
    {
        case MissionState::Init:
            countInit++;
            if(statusWait){
                currentMission = MissionState::ChooseDifficulty;
            }
            break;
        case MissionState::ChooseDifficulty:
            countChooseDifficulty++;
            if(statusStart){
                currentMission = MissionState::MissionRequest;
            }
            break;
        case MissionState::MissionRequest:
            countMissionRequest++;
            if(missionRequestSuccess){
                currentMission = MissionState::DriveToStartPos;
            }
            break;
        case MissionState::DriveToStartPos:
            countDriveToStartPos++;
            if(arriveAtStartPos){
                currentMission = MissionState::StartArrivalRequest;
            }
            break;
        case MissionState::StartArrivalRequest:
            countStartArrivalRequest++;
            if(startArrivalSuccess){
                currentMission = MissionState::DriveToGoalPos;
            }
            break;
        case MissionState::DriveToGoalPos:
            countDriveToGoalPos++;
            if(arriveAtGoalPos){
                currentMission = MissionState::GoalArrivalRequest;
            }
            break;
        case MissionState::GoalArrivalRequest:
            countGoalArrivalRequest++;
            if(goalArrivalSuccess){
                currentMission = MissionState::MissionComplete;
            }
            break;
        default:
            break;
    }
    mission_msg.data = currentMission;
    mission_pub.publish(mission_msg);
    std::cout<< stateToStringMission(currentMission) <<std::endl;
}

bool MissionStateMachine::getParam(int param_id){
    if(param_id == 1) return statusWait;
    else if(param_id == 2) return statusStart;
    else if(param_id == 3) return missionRequestSuccess;
    else if(param_id == 4) return arriveAtStartPos;
    else if(param_id == 5) return startArrivalSuccess;
    else if(param_id == 6) return arriveAtGoalPos;
    else if(param_id == 7) return goalArrivalSuccess;
}

void MissionStateMachine::v2xMissionCallback(const v2x_msgs::Mission1& msg){
    v2xMissionStat = msg.status;
}

void MissionStateMachine::v2xResponseCallback(const v2x_msgs::Request& msg){
    missionRequestSuccess = msg.mission;
    startArrivalSuccess = msg.start;
    goalArrivalSuccess = msg.goal;
}

void MissionStateMachine::behaviorCallback(const std_msgs::Int16::ConstPtr& msg){
    currentBehavior = (BehaviorState)msg->data;
}




int main(int argc, char** argv)
{
    ros::init(argc, argv, "mission_planner");

    MissionStateMachine MissionStateMachine_;

    ros::spin();
    return 0;
}