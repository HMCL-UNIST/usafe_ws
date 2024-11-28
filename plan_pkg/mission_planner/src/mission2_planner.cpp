
#include "mission2_planner.h"
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

    cam_health_sub = nh_.subscribe("/camera/health_status",1,&MissionStateMachine::camHealthCallback, this);
    behavior_sub = nh_.subscribe("/behavior_state", 1, &MissionStateMachine::behaviorCallback, this);
    pose_sub = nh_.subscribe("/current_pose",1,&MissionStateMachine::poseCallback,this);
    // vel_sub = nh_.subscribe("/CAN_VehicleStatus", 1, &MissionStateMachine::plantStateCallback,this);
    vel_sub = nh_.subscribe("/current_velocity", 1, &MissionStateMachine::twistCallback,this);
    signal_sub = nh_.subscribe("/pg_signal", 1, &MissionStateMachine::signalCallback, this);
    map_ver_sub = nh_.subscribe("/map_ver", 1, &MissionStateMachine::mapCallback, this);
    mission_state_sub = nh_.subscribe("/set_mission_state", 1, &MissionStateMachine::setMissionStateCallback, this);
    subtype_sub = nh_.subscribe("/subtype", 1, &MissionStateMachine::subtypeCallback, this);

    mission_pub = nh_.advertise<std_msgs::Int16>("/mission_state",1,true);
    mission_viz_pub = nh_.advertise<visualization_msgs::Marker>("/mission_state_viz",1,true);
    target_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/target_points_viz", 1, true);


    origin_lat = 35.6550026;
    origin_lon = 128.394116;
    origin_att = 48.944;

    GeographicLib::UTMUPS::Forward(origin_lat, origin_lon, origin_zone, origin_northp, origin_easting, origin_northing);

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
    slowOnFlag = false;
    slowOffFlag = false;
    stopFlag = false;
    startAgain = false;

    getSpeed = false;
    getPose = false;

    // thresGoal = 5.7;
    // thresPitStop = 4.0;
    // thresMapChangePoint = 4.0;

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
    countSlowOn = 0;
    countStop = 0;
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
    slowOnFlag = false;
    slowOffFlag = false;
    stopFlag = false;
    startAgain = false;

    currentMission = mState;
}

MissionStateMachine::~MissionStateMachine(){

}

MissionState MissionStateMachine::getCurrentMission(){
    return currentMission;
}

void MissionStateMachine::updateFactors(){

    MissionState currentMission = getCurrentMission();

    statusWait = false;
    statusStart = false;//for test
    missionEnd = false;
    goalCheck = false;
    startAfterPitStop = false;
    checkMapChangePoint = false;
    slowOffFlag = false;
    stopFlag = false;
    startAgain = false;


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

    if (currentBehavior >= BehaviorState::BehaviorReady) statusWait = true;
    if (statusWait && currentSignal == 1) statusStart = true;
    // calculateDistToGoal();
    // calculateDistToPitStop();
    // calculateDistToMapChangePoint();
    if (currentSignal == 3) slowOnFlag = true;
    if (currentSignal == 4) slowOffFlag = true;
    if (currentSignal == 5) stopFlag = true;
    if (currentMission == MissionState::MissionStop && currentSignal == 1) startAgain = true;
    if (PolygonFlag.isinFreespace && currentMission != 9 && currentMission >= 3) goalCheck = true;
    if (currentSignal == 2) statusPitStop = true;
    if (camdie) statusPitStop = true;
    if (PolygonFlag.isinJunction && statusPitStop) checkPitStop = true;
    if (checkPitStop && currentSignal == 1) startAfterPitStop = true;
    if (PolygonFlag.isinExit) checkMapChangePoint = true;
    if (!checkLap2 && goalCheck && !prevGoalCheck) checkLap2 = true;
    else if (!checkLap3 && goalCheck && !prevGoalCheck) checkLap3 = true;
    else if (!checkLap4 && goalCheck && !prevGoalCheck) checkLap4 = true;
    else if (!checkLap5 && goalCheck && !prevGoalCheck) checkLap5 = true;
    if (currentBehavior == BehaviorState::MissionEnd) missionEnd = true;
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
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                } 
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
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
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                } 
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
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
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                }
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
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
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                } 
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
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
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                } 
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
                } 
                break;
            case MissionState::Lap5:
                countLap5++;
                if(statusPitStop) {
                    currentMission = MissionState::PitStop;
                }
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                } 
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
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
                if(slowOnFlag) {
                    currentMission = MissionState::MissionSlowOn;
                } 
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
                } 
                break;
            case MissionState::MissionSlowOn:
                countSlowOn++;
                if(slowOffFlag) {
                    slowOnFlag = false;
                    currentMission = MissionState::Lap1;
                }
                if(stopFlag) {
                    currentMission = MissionState::MissionStop;
                } 
                break;
            case MissionState::MissionStop:
                countStop++;
                // if(startAgain) {
                //     stopFlag = false;
                //     currentMission = MissionState::Lap1;
                // }
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
    else if(param_id == 11) return slowOnFlag;
    else if(param_id == 12) return slowOffFlag;
    else if(param_id == 13) return stopFlag;
}

void MissionStateMachine::camHealthCallback(const std_msgs::Int8MultiArray::ConstPtr& msg){
    if(!msg->data[0]){
        ROS_INFO("FRONT CAM DIE");
        camdie = true;
    } 
    if(!msg->data[1]){
        ROS_INFO("LEFT CAM DIE");
        camdie = true;
    } 
    if(!msg->data[2]){
        ROS_INFO("RIGHT CAM DIE");
        camdie = true;
    } 
    if(!msg->data[3]){
        ROS_INFO("BACK CAM DIE");
        camdie = true;
    } 
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

void MissionStateMachine::viz_target_points() {

    // if (!getPose) {
    //     ROS_INFO("No Pose :: Can not visualize target points!!");
    //     return;
    // }

    visualization_msgs::MarkerArray markerArray;
    visualization_msgs::Marker marker;

    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "targets";
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = 3.0;
    marker.scale.y = 3.0;
    marker.scale.z = 3.0;
    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    std::vector<std::pair<double, double>> latlon_points = {
        {35.65549790934, 128.39444457287}, 
        {35.6513666097, 128.39892548022},  
        {35.65387345677, 128.39607941526}
    };

    for (size_t i = 0; i < latlon_points.size(); ++i) {
        double easting, northing;
        int zone;
        bool northp;


        GeographicLib::UTMUPS::Forward(latlon_points[i].first, latlon_points[i].second, zone, northp, easting, northing);

 
        double local_x = easting - origin_easting;
        double local_y = northing - origin_northing;

        marker.id = i;
        marker.pose.position.x = local_x;
        marker.pose.position.y = local_y;
        marker.pose.position.z = 0;
        markerArray.markers.push_back(marker);
    }

    target_viz_pub.publish(markerArray);
}

void MissionStateMachine::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
    getPose = true;
    egoPose = msg->pose;
}

void MissionStateMachine::twistCallback(const geometry_msgs::TwistStampedConstPtr& msg){
    getSpeed = true;
    egoSpeed = sqrt(pow(msg->twist.linear.x,2)+pow(msg->twist.linear.y,2));;
}
// void MissionStateMachine::plantStateCallback(const hmcl_msgs::VehicleStatus& state_msg)
// {
//   getSpeed = true;
// //   egoSpeed = state_msg.wheelspeed.wheel_speed ;
//   egoSpeed = state_msg->wheelspeed.wheel_speed
// //   ROS_INFO("egospeed: %f", egoSpeed);
// }
int main(int argc, char** argv)
{
    ros::init(argc, argv, "mission_planner");

    MissionStateMachine MissionStateMachine_;

    ros::spin();
    return 0;
}

