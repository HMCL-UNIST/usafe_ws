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

    // v2x_mission_sub = nh_.subscribe("/V2X/MissionList", 1, &MissionStateMachine::v2xMissionCallback, this);
    // v2x_rsp_sub = nh_.subscribe("/Reply", 1, &MissionStateMachine::v2xResponseCallback, this);
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

    currentMission = Init;
    callbackthread();
}
void MissionStateMachine::callbackthread()
{   
    ros::Rate loop_rate(10); // rate  
    while(ros::ok()){
        updateMissionState();
        loop_rate.sleep();
    }
}
MissionStateMachine::MissionStateMachine(MissionState mState){

    // v2x_mission_sub = nh_.subscribe("/V2X/MissionList", 1, &MissionStateMachine::v2xMissionCallback, this);
    // v2x_rsp_sub = nh_.subscribe("/Reply", 1, &MissionStateMachine::v2xResponseCallback, this);
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

    statusWait = false;
    statusStart = false;
    arriveAtStartPos = false;
    arriveAtGoalPos = false;

    switch(v2xMissionStat)
    {
    case 1:
        statusWait = true;
        break;
    case 2:
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
}

void MissionStateMachine::updateMissionState(){   
    updateFactors();
    switch(currentMission)
    {
        case MissionState::Init:
            if(statusWait){
                currentMission = MissionState::ChooseDifficulty;
            }
            break;
        case MissionState::ChooseDifficulty:
            if(statusStart){
                currentMission = MissionState::MissionRequest;
            }
            break;
        case MissionState::MissionRequest:
            if(missionRequestSuccess){
                currentMission = MissionState::DriveToStartPos;
            }
            break;
        case MissionState::DriveToStartPos:
            if(arriveAtStartPos){
                currentMission = MissionState::StartArrivalRequest;
            }
            break;
        case MissionState::StartArrivalRequest:
            if(startArrivalSuccess){
                currentMission = MissionState::DriveToGoalPos;
            }
            break;
        case MissionState::DriveToGoalPos:
            if(arriveAtGoalPos){
                currentMission = MissionState::GoalArrivalRequest;
            }
            break;
        case MissionState::GoalArrivalRequest:
            if(goalArrivalSuccess){
                currentMission = MissionState::MissionComplete;
            }
            break;
        default:
            break;
    }
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

// void MissionStateMachine::v2xMissionCallback(const hmcl_v2x::MissionArray::ConstPtr& msg){
//     v2xMissionStat = msg->status;
// }

// void MissionStateMachine::v2xResponseCallback(const hmcl_v2x::Reply::ConstPtr& msg){
//     missionRequestSuccess = msg->mission;
//     startArrivalSuccess = msg->arrive_start;
//     goalArrivalSuccess = msg->arrive_goal;
// }

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