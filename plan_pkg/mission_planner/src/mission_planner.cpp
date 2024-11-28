
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
    nh_.param<int>("thresMissionInit", thresMissionInit, 30);
    nh_.param<int>("thresVehicleReady", thresVehicleReady, 5);
    nh_.param<int>("thresLap1", thresLap1, 5);
    nh_.param<int>("thresLap2", thresLap2, 600);
    nh_.param<int>("thresLap3", thresLap3, 20);
    nh_.param<int>("thresLap4", thresLap4, 600);
    nh_.param<int>("thresLap5", thresLap5, 20);
    nh_.param<bool>("vizMission", vizMission, true);

    behavior_sub = nh_.subscribe("/behavior_state", 1, &MissionStateMachine::behaviorCallback, this);
    pose_sub = nh_.subscribe("/current_pose",1,&MissionStateMachine::poseCallback,this);
    vel_sub = nh_.subscribe("/CAN_VehicleStatus", 1, &MissionStateMachine::plantStateCallback,this);
    signal_sub = nh_.subscribe("/pg_signal", 1, &MissionStateMachine::signalCallback, this);
    map_ver_sub = nh_.subscribe("/map_ver", 1, &MissionStateMachine::mapCallback, this);
    mission_state_sub = nh_.subscribe("/set_mission_state", 1, &MissionStateMachine::setMissionStateCallback, this);
    subtype_sub = nh_.subscribe("/subtype", 1, &MissionStateMachine::subtypeCallback, this);

    mission_pub = nh_.advertise<std_msgs::Int16>("/mission_state",1,true);
    mission_viz_pub = nh_.advertise<visualization_msgs::Marker>("/mission_state_viz",1,true);
    target_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/target_points_viz", 1, true);


    // mission transition conditions
    statusWait = false;
    statusStart = false;
    statusPitStop = false;
    checkPitStop = false;
    startAfterPitStop = false;
    checkMapChangePoint = false;
    checkLap2 = false;
    checkLap3 = false;
    checkLap4 = false;
    checkLap5 = false;
    missionEnd = false;

    getSpeed = false;
    getPose = false;

    thresGoal = 5.7;
    thresPitStop = 4.0;
    thresMapChangePoint = 4.0;

    countMissionInit = 0;
    countVehicleReady = 0;
    countPitStop = 0;
    countStartFromPitStop = 0;
    countLap1 = 0;
    countLap2 = 0;
    countLap3 = 0;
    countLap4 = 0;
    countLap5 = 0;
    countMissionComplete = 0;

    currentMission = MissionState::MissionInit;
    externalMission = -1;

    boost::thread callbackhandler(&MissionStateMachine::callbackthread,this); 
}
void MissionStateMachine::callbackthread()
{   
    ros::Rate loop_rate(runRate); // rate  
    while(ros::ok()){
        updateMissionState();
        if(vizMission) 
        viz_mission();
        viz_target_points();
        loop_rate.sleep();
    }
}
MissionStateMachine::MissionStateMachine(MissionState mState){

    behavior_sub = nh_.subscribe("/behavior_state", 1, &MissionStateMachine::behaviorCallback, this);

    signal_sub = nh_.subscribe("/pg_signal", 1, &MissionStateMachine::signalCallback, this);

    map_ver_sub = nh_.subscribe("/map_ver", 1, &MissionStateMachine::mapCallback, this);

    mission_state_sub = nh_.subscribe("/set_mission_state", 1, &MissionStateMachine::setMissionStateCallback, this);

    subtype_sub = nh_.subscribe("/subtype", 1, &MissionStateMachine::subtypeCallback, this);

    mission_pub = nh_.advertise<std_msgs::Int16>("/mission_state",1,true);

    
    // mission transition conditions
    statusWait = false;
    statusStart = false;
    statusPitStop = false;
    checkPitStop = false;

    startAfterPitStop = false;
    checkMapChangePoint = false;
    checkLap2 = false;
    checkLap3 = false;
    checkLap4 = false;
    checkLap5 = false;
    missionEnd = false;
    goalCheck = false;
    prevGoalCheck = false;

    currentMission = mState;
}

MissionStateMachine::~MissionStateMachine(){

}

MissionState MissionStateMachine::getCurrentMission(){
    return currentMission;
}

void MissionStateMachine::calculateDistToGoal(){
    double goalpose[2];
    if (currentMap_ver == 0) {
        goalpose[0] = -337.2119;
        goalpose[1] = 409.2322;
    } else if (currentMap_ver == 1) {
        goalpose[0] = 490.4437;
        goalpose[1] = 195.1581;
    }
    distToGoal = sqrt(pow(goalpose[0] - egoPose.position.x, 2) + pow(goalpose[1] - egoPose.position.y, 2));
}

void MissionStateMachine::calculateDistToPitStop(){
    double goalpose[2];
    if (currentMap_ver == 0) {
        goalpose[0] = -593.8443;
        goalpose[1] = 689.5376;
    } else if (currentMap_ver == 1) {
        goalpose[0] = 836.1776;
        goalpose[1] = 356.3966;
    }
    distToPitStop = sqrt(pow(goalpose[0] - egoPose.position.x, 2) + pow(goalpose[1] - egoPose.position.y, 2));
}

void MissionStateMachine::calculateDistToMapChangePoint(){
    double goalpose[2];
    if (currentMap_ver == 0) {
        goalpose[0] = -746.6455;
        goalpose[1] = 877.3912;
    } else if (currentMap_ver == 1) {
        goalpose[0] = 1052.4774;
        goalpose[1] = 439.9011;
    }
    distToMapChangePoint = sqrt(pow(goalpose[0] - egoPose.position.x, 2) + pow(goalpose[1] - egoPose.position.y, 2));
}

void MissionStateMachine::updateFactors(){

    MissionState currentMission = getCurrentMission();

    statusWait = false;
    statusStart = false;//for test
    missionEnd = false;
    goalCheck = false;
    startAfterPitStop = false;
    checkMapChangePoint = false;

    std::cout<<"--MISSION--MISSION--MISSION--MISSION--"<<std::endl;

    if(!getBehavior){
        ROS_INFO("Can not receive behavior state");
        return;
    }

    if(!getSignal){
        ROS_INFO("Can not receive signal");
        return;
    }

    if(!getMap_ver){
        ROS_INFO("Can not receive map version");
        return;
    }
    if(!getSpeed){
        ROS_INFO("Can not receive velocity");
        return;
    }

    if (currentBehavior == BehaviorState::BehaviorReady) statusWait = true;
    if (statusWait && currentSignal == 1) statusStart = true;
    calculateDistToGoal();
    calculateDistToPitStop();
    calculateDistToMapChangePoint();
    if (PolygonFlag.isinFreespace && currentMission != 9 && currentMission >= 3) goalCheck = true;
    if (currentSignal == 2) statusPitStop = true;
    if (PolygonFlag.isinJunction && statusPitStop) checkPitStop = true;
    if (checkPitStop && currentSignal == 1) startAfterPitStop = true;
    if (PolygonFlag.isinExit) checkMapChangePoint = true;
    if (!checkLap2 && goalCheck && !prevGoalCheck) checkLap2 = true;
    else if (!checkLap3 && goalCheck && !prevGoalCheck) checkLap3 = true;
    else if (!checkLap4 && goalCheck && !prevGoalCheck) checkLap4 = true;
    else if (!checkLap5 && goalCheck && !prevGoalCheck) checkLap5 = true;
    if (egoSpeed < 1.0) missionEnd = true;
    prevGoalCheck = goalCheck;
}

void MissionStateMachine::updateMissionState() {
    if (getExternalMission) {
        switch (externalMission) {

            case 2:
                currentMission = MissionState::StartFromPitStop;
                break;
            case 3:
                currentMission = MissionState::Lap1;
                break;
            case 4:
                currentMission = MissionState::Lap2;
                break;
            case 5:
                currentMission = MissionState::Lap3;
                break;
            case 6:
                currentMission = MissionState::Lap4;
                break;
            case 7:
                currentMission = MissionState::Lap5;
                break;
            default:
                break;
        }
        externalMission = -1;
        getExternalMission = false;
    } else {
        updateFactors();
        switch(currentMission) {
            case MissionState::MissionInit:
                countMissionInit++;
                if(statusWait) {
                    currentMission = MissionState::VehicleReady;
                }
                break;
            case MissionState::VehicleReady:
                countVehicleReady++;
                if(statusStart) {
                    currentMission = MissionState::StartFromPitStop;
                }
                break;
            case MissionState::StartFromPitStop:
                countStartFromPitStop++;
                checkPitStop = false;
                if(statusPitStop) {
                    countPitStop++;
                    currentMission = MissionState::PitStop;
                }
                if(checkMapChangePoint) {
                    currentMission = MissionState::Lap1;
                }
                break;
            case MissionState::Lap1:
                countLap1++;
                if(statusPitStop) {
                    countPitStop++;
                    currentMission = MissionState::PitStop;
                }
                if(checkLap2) {
                    currentMission = MissionState::Lap2;
                }
                break;
            case MissionState::Lap2:
                countLap2++;
                if(statusPitStop) {
                    currentMission = MissionState::PitStop;
                }
                if(checkLap3) {
                    currentMission = MissionState::Lap3;
                }
                break;
            case MissionState::Lap3:
                countLap3++;
                if(statusPitStop) {
                    currentMission = MissionState::PitStop;
                }
                if(checkLap4) {
                    currentMission = MissionState::Lap4;
                }
                break;
            case MissionState::Lap4:
                countLap4++;
                if(statusPitStop) {
                    currentMission = MissionState::PitStop;
                }
                if(checkLap5) {
                    currentMission = MissionState::Lap5;
                }
                break;
            case MissionState::Lap5:
                countLap5++;
                if(statusPitStop) {
                    currentMission = MissionState::PitStop;
                }
                break;
            case MissionState::PitStop:
                countPitStop++;
                if(startAfterPitStop) {
                    statusPitStop = false;
                    currentMission = MissionState::StartFromPitStop;
                }
                if(missionEnd) {
                    currentMission = MissionState::MissionComplete;
                }
                break;
            default:
                break;
        }
    }

    mission_msg.data = currentMission;
    mission_pub.publish(mission_msg);
    std::cout << stateToStringMission(currentMission) << std::endl;
}

bool MissionStateMachine::getParam(int param_id){
    if(param_id == 1) return statusWait;
    else if(param_id == 2) return statusStart;
    else if(param_id == 3) return checkLap2;
    else if(param_id == 4) return checkLap3;
    else if(param_id == 5) return checkLap4;
    else if(param_id == 6) return checkLap5;
    else if(param_id == 7) return missionEnd;
    else if(param_id == 8) return statusPitStop;
    else if(param_id == 9) return startAfterPitStop;
    else if(param_id == 10) return checkMapChangePoint;
}


void MissionStateMachine::behaviorCallback(const std_msgs::Int16::ConstPtr& msg){
    getBehavior = true;
    currentBehavior = (BehaviorState)msg->data;
}

void MissionStateMachine::signalCallback(const std_msgs::Int8::ConstPtr& msg){
    getSignal = true;
    currentSignal = msg->data;
}

void MissionStateMachine::mapCallback(const std_msgs::Int8::ConstPtr& msg){
    getMap_ver = true;
    currentMap_ver = msg->data;

}

void MissionStateMachine::setMissionStateCallback(const std_msgs::Int16::ConstPtr& msg){
    getExternalMission = true;
    externalMission = msg->data;

    if (externalMission >= 0 && externalMission <= 3) {
        checkLap2 = false;
        checkLap3 = false;
        checkLap4 = false;
        checkLap5 = false;
    } else if (externalMission == 4) {
        checkLap2 = true;
        checkLap3 = false;
        checkLap4 = false;
        checkLap5 = false;
    } else if (externalMission == 5) {
        checkLap2 = true;
        checkLap3 = true;
        checkLap4 = false;
        checkLap5 = false;
    } else if (externalMission == 6) {
        checkLap2 = true;
        checkLap3 = true;
        checkLap4 = true;
        checkLap5 = false;
    } else if (externalMission == 7) {
        checkLap2 = true;
        checkLap3 = true;
        checkLap4 = true;
        checkLap5 = true;
    }
}


void MissionStateMachine::subtypeCallback(const hmcl_msgs::PolygonFlag::ConstPtr& msg) {
    PolygonFlag.isinJunction = msg->isinJunction;
    PolygonFlag.isinExit = msg->isinExit;
    PolygonFlag.isinBank = msg->isinBank;
    PolygonFlag.isinFreespace = msg->isinFreespace;
    PolygonFlag.isinCrosswalk = msg->isinCrosswalk;
}


void MissionStateMachine::viz_mission(){


    if(!getPose){
        ROS_INFO("No Pose :: Can not visualize mission state!!");
        return;
    }
    visualization_msgs::Marker missionMarker;

    missionMarker.header.frame_id = "map";
    missionMarker.header.stamp = ros::Time();
    missionMarker.ns = "mission";
    missionMarker.id = 0;
    missionMarker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    missionMarker.action = visualization_msgs::Marker::ADD;

    missionMarker.pose.position.x = egoPose.position.x;
    missionMarker.pose.position.y = egoPose.position.y + 11;
    missionMarker.pose.position.z = 16;

    missionMarker.scale.z = 4;
    missionMarker.text = stateToStringMission(currentMission);

    missionMarker.color.a = 1.0;
    missionMarker.color.r = 1.0;
    missionMarker.color.g = 0.0;
    missionMarker.color.b = 1.0;

    mission_viz_pub.publish(missionMarker);
}

void MissionStateMachine::viz_target_points(){
    if(!getPose){
        ROS_INFO("No Pose :: Can not visualize target points!!");
        return;
    }
    
    visualization_msgs::MarkerArray markerArray;
    visualization_msgs::Marker marker;

    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "targets";
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = 2.0;
    marker.scale.y = 2.0;
    marker.scale.z = 2.0;
    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    double points[3][2];
    if (currentMap_ver == 0) {
        points[0][0] = -337.2119; points[0][1] = 409.2322;
        points[1][0] = -593.8443; points[1][1] = 689.5376;
        points[2][0] = -746.6455;  points[2][1] = 877.3912;
    } else if (currentMap_ver == 1) {
        points[0][0] = 490.4437;  points[0][1] = 195.1581;
        points[1][0] = 836.1776;  points[1][1] = 356.3966;
        points[2][0] = 1052.4774; points[2][1] = 439.9011;
    }

    for (int i = 0; i < 3; ++i) {
        marker.id = i;
        marker.pose.position.x = points[i][0];
        marker.pose.position.y = points[i][1];
        marker.pose.position.z = 0;
        markerArray.markers.push_back(marker);
    }

    target_viz_pub.publish(markerArray);
}

void MissionStateMachine::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
    getPose = true;
    egoPose = msg->pose;
}

// void MissionStateMachine::twistCallback(const geometry_msgs::TwistStampedConstPtr& msg){
//     getSpeed = true;
//     egoSpeed = sqrt(pow(msg->twist.linear.x,2)+pow(msg->twist.linear.y,2));;
// }
void MissionStateMachine::plantStateCallback(const hmcl_msgs::VehicleStatus& state_msg)
{
  getSpeed = true;
  egoSpeed = state_msg.wheelspeed.wheel_speed ;
//   ROS_INFO("egospeed: %f", egoSpeed);
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "mission_planner");

    MissionStateMachine MissionStateMachine_;

    ros::spin();
    return 0;
}

