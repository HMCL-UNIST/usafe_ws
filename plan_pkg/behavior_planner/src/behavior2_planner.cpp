#include "behavior2_planner.h"
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
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>
#include <chrono>

#include <boost/algorithm/string.hpp>
#include <GeographicLib/UTMUPS.hpp>



BehaviorPlanner::BehaviorPlanner(){

    nh_.param<double>("runRate", runRate, 20);
    nh_.param<float>("wLane", wLane, 3.4);
    nh_.param<float>("lenEgo", lenEgo, 4.180);
    nh_.param<float>("frontlenEgo", frontlenEgo, 4.180/2);// need to check lidar position in real vehicle
    nh_.param<float>("dFront", dFront, 80);
    nh_.param<int>("nStore", nStore, 20); //need to check
    nh_.param<int>("thresBehaviorReady", thresBehaviorReady, 40);
    nh_.param<float>("thresObs", thresObs, 7); 
    nh_.param<float>("thresLC", thresLC, 0.6); // need to check if 1 is sufficient
    nh_.param<float>("thresStop", thresStop, 0.1); // need to check if 0.01 is sufficient
    nh_.param<float>("thresPit", thresPit, 10.0); // need to check if 0.01 is sufficient
    nh_.param<bool>("vizBehavior", vizBehavior, true);

    pose_sub = nh_.subscribe("/current_pose",1,&BehaviorPlanner::poseCallback,this);
    // pose_sub = nh_.subscribe("/pose_estimate", 1, &BehaviorPlanner::odometryCallback, this);
    vel_sub = nh_.subscribe("/current_velocity", 1, &BehaviorPlanner::twistCallback,this);
    vel2_sub = nh_.subscribe("/CAN_VehicleStatus", 1, &BehaviorPlanner::vehicleStatusCallback, this);
    // objs_sub = nh_.subscribe("/detection/lidar_tracker/objects",1, &BehaviorPlanner::objsCallback,this);
    objs_sub = nh_.subscribe("/tracking/car",1, &BehaviorPlanner::objsCallback,this);
    //goal_sub = nh_.subscribe("move_base_simple/goal", 1, &BehaviorPlanner::callbackGetGoalPose, this);
    route_sub = nh_.subscribe("/global_traj", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    opt_sub = nh_.subscribe("/optimal_traj", 1, &BehaviorPlanner::optCallback, this);//need to fix topic name
    // route_sub = nh_.subscribe("/lane_in_range", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    mission_sub = nh_.subscribe("/mission_state", 1, &BehaviorPlanner::missionCallback, this);
    map_ver_sub = nh_.subscribe("/map_ver", 1, &BehaviorPlanner::mapverCallback, this);
    external_mission_sub = nh_.subscribe("/set_mission_state", 1, &BehaviorPlanner::setMissionStateCallback, this);
    overtaking_flag_sub = nh_.subscribe("/overtaking", 1, &BehaviorPlanner::overtakingCallback, this);
    subtype_sub = nh_.subscribe("/subtype", 1, &BehaviorPlanner::subtypeCallback, this);

    b_factor_pub = nh_.advertise<hmcl_msgs::BehaviorFactor>("/behavior_factor",1,true);
    b_state_pub = nh_.advertise<std_msgs::Int16>("/behavior_state",1,true);
    light_pub = nh_.advertise<std_msgs::Float64>("/light_cmd",1,true);
    behavior_viz_pub = nh_.advertise<visualization_msgs::Marker>("/behavior_state_viz",1,true);
    obs_pub = nh_.advertise<visualization_msgs::Marker>("/obstacle_viz",1,true);
    // behavior_timer = nh_.createTimer(ros::Duration(0.05), &BehaviorPlanner::behavior_handler,this);

    stopline_viz_pub = nh_.advertise<visualization_msgs::Marker>("/StopLine_viz", 1);

    origin_lat = 35.6550026;
    origin_lon = 128.394116;
    origin_att = 48.944;

    GeographicLib::UTMUPS::Forward(origin_lat, origin_lon, origin_zone, origin_northp, origin_easting, origin_northing);

    // behavior factors
    vehicleReady = false;
    missionStart = false;
    missionEnd = false;
    frontOpponent = false;
    stationaryFrontOpponent = false;
    stopCheck = false;
    laneChangeDone = false;
    checkObstacle = true;

    isEmergency = false;
    needLeftLaneChange = false;
    needRightLaneChange = false;

    getOpponent = false;
    getGlobal = false;
    getOpt = false;
    getPose = false;
    getSpeed = false;
    getMission = false;
    getMapver = false;
    getOvertakingFlag = false;
    goToSecondLane = false;



    // to velocity planner
    front_id = -1;
    front_dist = 100;
    front_vel = -1;
    xObstacle = -1;
    yObstacle = -1;
    dGlobal = -1;

    unknown_id = -1;

    currentBehavior = BehaviorState::BehaviorInit;
    // prevStraight = false;
    // prevBank = false;

    countFront = 0;
    countStationary = 0;
    countObs = 0;
    countBehaviorReady = 0;
    prefer_lane_id = 0;
    prev_lane_id = -1;
    sEgo = 0;
    lEgo = 0;
    sOpt = 0;
    lOpt = 0;
    lOptFar = 0;
    overtakingFlag = false;
    accFlag = false;
    obsavoidFlag = false;
    aebFlag = false;
    KeepSpeed = false;
    PolygonFlag.isinJunction = false;
    PolygonFlag.isinExit = false;
    PolygonFlag.isinBank = false;
    PolygonFlag.isinFreespace = false;
    PolygonFlag.isinCrosswalk = false;
    distToStopLine = 100;

    boost::thread callbackhandler(&BehaviorPlanner::callbackthread,this); 
}
void BehaviorPlanner::callbackthread(){   
    ros::Rate loop_rate(runRate); // rate  
    while(ros::ok()){
        updateBehaviorState();
        if(vizBehavior) viz_behavior();
        publishMsgs();
        stopline_viz();
        loop_rate.sleep();
    }
}
BehaviorPlanner::~BehaviorPlanner(){

}

void BehaviorPlanner::calculateLon(int n, float* psarr, hmcl_msgs::Lane &lane){
    psarr[0] = 0;
    for(int i = 1; i < n; i++){
        float d = sqrt(pow(lane.waypoints[i].pose.pose.position.x - lane.waypoints[i-1].pose.pose.position.x,2)+pow(lane.waypoints[i].pose.pose.position.y - lane.waypoints[i-1].pose.pose.position.y,2));
        psarr[i] = psarr[i-1] + d;
    }
}

void BehaviorPlanner::calculateFrenet(int n, float* psarr, float px, float py, float vx, float vy, float* psl, hmcl_msgs::Lane &lane){
    float mindist = 100;
    int minidx = 0;
    float mindist2 = 100;
    int minidx2 = 0;
    int idx = 0;
    
    for(int i = 0; i < n; i++){
        float dist = sqrt(pow(px - lane.waypoints[i].pose.pose.position.x,2)+pow(py - lane.waypoints[i].pose.pose.position.y,2));
        // ROS_INFO("dist %f", dist);
        // ROS_INFO("wpts:%f,%f",lane.waypoints[i].pose.pose.position.x,lane.waypoints[i].pose.pose.position.y);
        if(dist<mindist){
            mindist2 = mindist;
            minidx2 = minidx;
            mindist = dist;
            minidx = i;
        }
        if(minidx < minidx2) idx = minidx;
        else idx = minidx2;
    }
    
    float x[2] = {px - lane.waypoints[idx].pose.pose.position.x, py - lane.waypoints[idx].pose.pose.position.y};
    float p[2] = {lane.waypoints[idx+2].pose.pose.position.x - lane.waypoints[idx].pose.pose.position.x, lane.waypoints[idx+2].pose.pose.position.y - lane.waypoints[idx].pose.pose.position.y};
    float v[2] = {vx, vy};
    float dp = sqrt(pow(p[0],2)+pow(p[1],2));
    float dx = sqrt(pow(x[0],2)+pow(x[1],2));
    float sv = sqrt(pow(v[0],2)+pow(v[1],2));
    float theta = acos((x[0]*p[0]+x[1]*p[1])/(dx*dp));
    float theta2 = acos((v[0]*p[0]+v[1]*p[1])/(sv*dp));
    // ROS_INFO("psarr: %f,dp %f, dx %f, sv %f, theta %f, theta2 %f",psarr[idx],dp, dx, sv, theta, theta2);
    float s = psarr[idx]+dx*cos(theta);
    if(dx<0.1) s = psarr[idx];
    float ds = sv*cos(theta2);
    if(sv<0.1) ds = 0;
    float l;
    float dl;
    // ROS_INFO("idx %d, x %f, p %f, v %f", idx, x[0],p[0],v[0]);
    if(dx<0.1) l = 0;
    else if(x[0]*p[1]-x[1]*p[0]<0) l = -dx*sin(theta);
    else l = dx*sin(theta);
    if(sv<0.1) dl = 0;
    else if(v[0]*p[1]-v[1]*p[0]<0) dl = -sv*sin(theta2);
    else dl = sv*sin(theta2);
    psl[0] = s;
    psl[1] = l;
    psl[2] = ds;
    psl[3] = dl;
}
double BehaviorPlanner::distance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
}

void BehaviorPlanner::getCurrentLaneWpt(){
    float min_dist = 1000.0;
    float dist = 1000.0;
    lane_id = 0;
    wpt_id = 0;
    for(int i = 0; i < globalLaneArray.lanes.size(); i++){
        for(int j = 0; j < globalLaneArray.lanes[i].waypoints.size(); j++){
            dist = distance(globalLaneArray.lanes[i].waypoints[j].pose.pose.position.x,globalLaneArray.lanes[i].waypoints[j].pose.pose.position.y,egoPose.position.x,egoPose.position.y);
            if(min_dist > dist){
                min_dist = dist;
                lane_id = i;
                wpt_id = j;
            }
        }
    }
    dGlobal = min_dist;
}

void BehaviorPlanner::getCurrentOptWpt(){
    float min_dist = 1000.0;
    float dist = 1000.0;
    opt_wpt_id = 0;
        for(int i = 0; i < optimalLaneArray.lanes[0].waypoints.size(); i++){
            dist = distance(optimalLaneArray.lanes[0].waypoints[i].pose.pose.position.x,optimalLaneArray.lanes[0].waypoints[i].pose.pose.position.y,egoPose.position.x,egoPose.position.y);
            if(min_dist > dist){
                min_dist = dist;
                opt_wpt_id = i;
            }
        }
}

void BehaviorPlanner::updatePreferLaneID(){
    // prefer_lane_id = -1;
    // switch (currentMission) {
    //     case MissionState::StartFromPitStop:
    //         if (goToSecondLane){
    //             prefer_lane_id = 1;
    //         }
    //         else {
    //             prefer_lane_id = 1;
    //         }
    //         break;
    //     case MissionState::Lap1:
    //         prefer_lane_id = 1;
    //         break;
    //     case MissionState::Lap2:
    //         prefer_lane_id = 1;
    //         break;
    //     case MissionState::Lap3:
    //         prefer_lane_id = 1;
    //         break;
    //     case MissionState::Lap4:
    //         prefer_lane_id = 1;
    //         break;
    //     case MissionState::Lap5:
    //         prefer_lane_id = 1;
    //         break;
    //     default:
    //         prefer_lane_id = 1;
    //         break;
    // }

    // float dist1 =distance(egoPose.position.x,egoPose.position.y,1203,647.721);
    // float dist2 =distance(egoPose.position.x,egoPose.position.y,-300.792,-99.0979);
    // if(dist1 < dist2) prefer_lane_id = 1;
    // else prefer_lane_id = 0;
    prefer_lane_id = 1;
}



void BehaviorPlanner::updateFactors(){
    std::cout<< "--BEHAVIOR--BEHAVIOR--BEHAVIOR--BEHAVIOR-- " <<std::endl;
    // ROS_INFO("---------------BEHAVIOR_PLANNER----------------");


    // behavior factors
    // missionStart = true; //for test
    missionStart = false; 
    missionEnd = false;
    frontOpponent = false;
    leftOpponent = false;
    rightOpponent = false;

    stationaryFrontOpponent = false;
    stopCheck = false;
    needLeftLaneChange = false;
    needRightLaneChange = false;
    isBankClose = false;
    checkObstacle = false;


    front_id = -1;
    left_id = -1;
    right_id = -1;
    front_dist = 100;
    front_vel = 100;
    unknown_id = -1;


    if(!getSpeed || !getSpeed2){
        ROS_INFO("Can not receive speed");
        return;
    }

    // check if ego stop
    if(egoSpeed < 1.0) stopCheck = true;    
    
    // if(!getMapver){
    //     ROS_INFO("Can not receive map_ver");
    //     return;
    // }
    if(!getMission){
        ROS_INFO("Can not receive mission state");
        return;
    }
    vehicleReady = true; //for test

    // External Mission Condition

    if (externalMission >= 3 && externalMission <= 8){
        goToSecondLane = true;
    }

    // check mission start
    if((int)currentMission >= 2){
        missionStart = true;
    }
    // if(currentMission == MissionState::MissionComplete){
    //     missionEnd = true;
    // }
    // return if mission doesn't start
    if(missionStart == false){
        ROS_INFO("Mission doesn't start yet");
        return;
    }

    if (!getGlobal){
        ROS_INFO("Can not receive global trajectory");
        return;
    }
    if (!getOpt){
        ROS_INFO("Can not receive optimal trajectory");
        return;
    }
    if(!getOvertakingFlag){
        ROS_INFO("Can not receive overtaking flag");
    }    
    if(!getOpponent){
        ROS_INFO("Can not receive objects");
    }
    // ROS_INFO("global lanes size: %d", globalLaneArray.lanes.size());
    // ROS_INFO("ego lane wpts size: %d", globalLaneArray.lanes[0].waypoints.size());
    if(globalLaneArray.lanes.size() < 1){
        ROS_INFO("global array doesn't contain lane");
        return;
    }
    if(globalLaneArray.lanes[0].waypoints.size() < 1){
        ROS_INFO("global array doesn't contain waypoint");
        return;
    }
    if(optimalLaneArray.lanes.size() < 1){
        ROS_INFO("optimal array doesn't contain lane");
        return;
    }
    if(optimalLaneArray.lanes[0].waypoints.size() < 1){
        ROS_INFO("optimal array doesn't contain waypoint");
        return;
    }
    calculateDistToStopLine();

    if(currentMission == MissionState::PitStop && distToStopLine < thresPit) missionEnd = true;
    if(currentMission == MissionState::StartFromPitStop, currentMission == MissionState::Lap1, currentMission == MissionState::Lap2, 
    currentMission == MissionState::Lap3, currentMission == MissionState::Lap4, currentMission == MissionState::Lap5) onDriving = true;
    if(PolygonFlag.isinBank){
        KeepSpeed = true;
        isInBank = true;
    }
    else{
        isInBank = false;
    }
    updatePreferLaneID();
    getCurrentLaneWpt();
    getCurrentOptWpt();
    // if(globalLaneArray.lanes[lane_id].waypoints[wpt_id].bank==true){
    //     // isInBank = true;
    //     // isInStraight = false;
    //     isInBank = false;
    //     isInStraight = true;
    // }
    // else{
    //     isInBank = false;
    //     isInStraight = true;
    // }
    if(prev_lane_id==-1)prev_lane_id = lane_id; 
    // ROS_INFO("lane id : %d, wpt id: %d", lane_id, wpt_id);

    vehicleReady = true;

    int n0 = globalLaneArray.lanes[lane_id].waypoints.size();
    float sarr0[n0];
    float slEgo[4], slObj[4], slOpt[4], slOptFar[4];
    
    float dsEgo;
    float* psarr;

    float* psl;

    float thresDetect = 100;

    // int on = 0;
    // int rawon = detectedObjects.objects.size();
    int on = detectedObjects.objects.size();

    


    // for(int i = 0; i < rawon; i++){
    //     if(sqrt(pow(detectedObjects.objects[i].pose.position.x,2)+pow(detectedObjects.objects[i].pose.position.y,2)) < thresDetect){
    //         on++;
    //     }
    // }



    float xObj[on], yObj[on], vxObj[on], vyObj[on], velObj[on];
    float sObj[on], lObj[on], dsObj[on], dlObj[on];
    
    if(dGlobal > 5.0){
        ROS_INFO("ego vehicle is not located on the global lane");
        return;
    }

    //calculate yaw angle
    float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.x + egoPose.orientation.w*egoPose.orientation.z), 1-2*(egoPose.orientation.y*egoPose.orientation.y + egoPose.orientation.z*egoPose.orientation.z));
    // ROS_INFO("egopose x: %f, y: %f",egoPose.position.x, egoPose.position.y);
    // ROS_INFO("globalpose x: %f, y: %f",globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x,globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y);

    // convert relative coordinate to global coordinate
    // int idxtmp = 0;
    for(int i = 0; i < on; i++){
        // if(sqrt(pow(detectedObjects.objects[i].pose.position.x,2)+pow(detectedObjects.objects[i].pose.position.y,2)) < thresDetect){
        //     xObj[idxtmp] = egoPose.position.x + detectedObjects.objects[i].pose.position.x*cos(yaw)-detectedObjects.objects[i].pose.position.y*sin(yaw);
        //     yObj[idxtmp] = egoPose.position.y + detectedObjects.objects[i].pose.position.x*sin(yaw)+detectedObjects.objects[i].pose.position.y*cos(yaw);
        //     // vxObj[idxtmp] = detectedObjects.objects[i].velocity.linear.x*cos(yaw) - detectedObjects.objects[i].velocity.linear.y*sin(yaw);
        //     velObj[idxtmp] = egoSpeed+detectedObjects.objects[i].velocity.linear.x;
        //     // vyObj[idxtmp] = detectedObjects.objects[i].velocity.linear.x*sin(yaw) + detectedObjects.objects[i].velocity.linear.y*cos(yaw);
        //     idxtmp++;
        //     // ROS_INFO("i:%d,x: %f,y: %f,vx: %f,vy: %f",i,xObj[i],yObj[i],vxObj[i],vxObj[i]);
        // }
        xObj[i] = detectedObjects.objects[i].pose.position.x;
        yObj[i] = detectedObjects.objects[i].pose.position.y;
        vxObj[i] = detectedObjects.objects[i].velocity.linear.x;
        vyObj[i] = detectedObjects.objects[i].velocity.linear.y;
        velObj[i] = sqrt(pow(detectedObjects.objects[i].velocity.linear.x,2)+pow(detectedObjects.objects[i].velocity.linear.y,2));
        ROS_INFO("i:%d,x: %f,y: %f,vx: %f,vy: %f",i,xObj[i],yObj[i],vxObj[i],vxObj[i]);
    }


    // calculate Frenet longitudinal length of egolane            
    psarr = sarr0;
    this->calculateLon(n0, psarr, globalLaneArray.lanes[1]);
    ROS_INFO("111");

    // calculate Frenet coordinate of ego vehicle
    psl = slEgo;
    this->calculateFrenet(n0, psarr, egoPose.position.x, egoPose.position.y, egoTwist.linear.x, egoTwist.linear.y, psl, globalLaneArray.lanes[1]);
    if(!isnan(slEgo[0])){
        sEgo = slEgo[0];
        lEgo = slEgo[1];
        dsEgo = slEgo[2];
        dlEgo = slEgo[3];    
    }
    ROS_INFO("22");

    psl = slOptFar;
    int nOpt = optimalLaneArray.lanes[0].waypoints.size();
    int iOptFar = std::min(nOpt,opt_wpt_id+50); 
    this->calculateFrenet(n0, psarr, optimalLaneArray.lanes[0].waypoints[iOptFar].pose.pose.position.x, optimalLaneArray.lanes[0].waypoints[iOptFar].pose.pose.position.y, 0, 0, psl, globalLaneArray.lanes[1]);
    if(!isnan(slOptFar[0])){
        lOptFar = slOptFar[1]; 
    }
    ROS_INFO("333");

    // dsEgo = egoSpeed;
    // ROS_INFO("egopose s: %f, l: %f, dsEgo: %f", sEgo, lEgo, dsEgo);


    // calculate Frenet coordinate of objects
    psl = slObj;
    float minFront = dFront;
    float minLeft = dFront;
    float minRight = dFront;
    behaviorFactor.sObj.clear();
    behaviorFactor.lObj.clear();
    behaviorFactor.dsObj.clear();
    behaviorFactor.dlObj.clear();
    for(int i = 0; i < on; i++){
        psarr = sarr0;
        this->calculateFrenet(n0, psarr, xObj[i], yObj[i], vxObj[i], vyObj[i], psl, globalLaneArray.lanes[1]);
        sObj[i] = slObj[0];
        lObj[i] = slObj[1];
        dsObj[i] = velObj[i];
        dlObj[i] = 0;
        // dsObj[i] = slObj[2];
        // dlObj[i] = slObj[3];
        behaviorFactor.sObj.emplace_back(sObj[i]);
        behaviorFactor.lObj.emplace_back(lObj[i]);
        behaviorFactor.dsObj.emplace_back(dsObj[i]);
        behaviorFactor.dlObj.emplace_back(dlObj[i]);
        bool isCar = false;
        if(detectedObjects.objects[i].label == "car") isCar = true;
        ROS_INFO("i:%d,sObj-sEgo: %3.1f,lObj: %3.1f, dsObj: %3.1f, dlObj: %3.1f, velObj: %3.1f, label: %d",i,sObj[i]-sEgo,lObj[i],dsObj[i],dlObj[i],velObj[i],isCar);
        if(abs(lObj[i]) <= wLane*1.5){
            // front vehicle
            if(sObj[i]-sEgo < minFront && sObj[i]-sEgo > 0.0){
                front_id = i;
                minFront = sObj[i]-sEgo;
                frontOpponent = true;
            }
        }
        // else if(lane_id != 0 && lObj[i] >= -wLane*1.5 && lObj[i] < -wLane/2){
        //     if(sObj[i]-sEgo < minLeft && sObj[i]-sEgo > -20.0){
        //         left_id = i;
        //         minLeft = sObj[i]-sEgo;
        //         leftOpponent = true;
        //     }
        // }
        // else if(lane_id != 2 && lObj[i] <= wLane*1.5 && lObj[i] > wLane/2){
        //     if(sObj[i]-sEgo < minRight && sObj[i]-sEgo > -20.0){
        //         right_id = i;
        //         minRight = sObj[i]-sEgo;
        //         rightOpponent = true;
        //     }
        // }

    }



    
    // calculate safe distance and check if it is stationary car
    if(frontOpponent){
        countFront = 0;
        frontOpponentPrev = true;
        front_dist = minFront;
        front_vel = dsObj[front_id];
        xObstacle = xObj[front_id];
        yObstacle = yObj[front_id];
        if (abs(front_vel) < thresStop){
            stationaryFrontOpponent = true;
            stationaryFrontOpponentPrev = true;
        }
        frontOpponent = true;
    }
    // store front car for nStore time steps
    // if(!frontOpponent && frontOpponentPrev){
    //     countFront++;
    //     if(countFront < nStore){
    //         front_id = 1000;
    //         frontOpponent = true;
    //     }
    //     else{
    //         frontOpponentPrev = false;
    //         countFront = 0;
    //     }
    // }
    // else{
    //     countFront = 0;
    // }

    // if(!stationaryFrontOpponent && stationaryFrontOpponentPrev){
    //     countStationary++;
    //     if(countStationary < nStore){
    //         stationaryFrontOpponent = true;
    //     }
    //     else{
    //         countStationary = 0;
    //         stationaryFrontOpponentPrev = false;
    //     }

    // }
    // else{
    //     countStationary = 0;
    // }
    // this->calculateFrenet(n0, psarr, xObstacle, yObstacle, 0, 0, psl, globalLaneArray.lanes[lane_id]);
    // float sObs = slObj[0];
    // float lObs = slObj[1];
    // if(abs(lObs) <= wLane/2){
    //     if(sObs-sEgo < minFront && sObs-sEgo > 5.0){
    //         front_id = 1000;
    //         minFront = sObs-sEgo;
    //         frontOpponent = true;
    //     }
    // }
    // else if(lane_id != 0 && lObs >= -wLane*1.5 && lObs < -wLane/2){
    //     if(sObs-sEgo < minLeft && sObs-sEgo > 0.0){
    //         left_id = 1000;
    //         minLeft = sObs-sEgo;
    //         leftOpponent = true;
    //     }
    // }
    // else if(lane_id != 2 && lObs <= wLane*1.5 && lObs > wLane/2){
    //     if(sObs-sEgo < minRight && sObs-sEgo > 0.0){
    //         right_id = 1000;
    //         minRight = sObs-sEgo;
    //         rightOpponent = true;
    //     }
    // }
    // ROS_INFO("sObstacle: %f", sObs);
    // ROS_INFO("lObstacle: %f", lObs);
    // ROS_INFO("sego : %f", sEgo);
    // ROS_INFO("lego : %f", lEgo);


    // if(leftOpponent) ROS_INFO("leftOpponent!!!!");
    // if(rightOpponent) ROS_INFO("rightOpponent!!!!");




    // if(!leftOpponent && currentBehavior == BehaviorState::LeftLaneChange && prev_lane_id == lane_id){
    //     needLeftLaneChange = true;
    // }
    // else if(!leftOpponent && currentBehavior == BehaviorState::LeftLaneChange && prev_lane_id != lane_id && abs(lEgo)>1.2){
    //     needLeftLaneChange = true;
    // }
    // if(!leftOpponent && prefer_lane_id < lane_id && currentBehavior != BehaviorState::RightLaneChange){
    //     needLeftLaneChange = true;
    //     prev_lane_id = lane_id;
    // }
    // if(!rightOpponent && currentBehavior == BehaviorState::RightLaneChange && prev_lane_id == lane_id){
    //     needRightLaneChange = true; 
    // } 
    // else if(!rightOpponent && currentBehavior == BehaviorState::RightLaneChange && prev_lane_id != lane_id && abs(lEgo)>1.2){
    //     needRightLaneChange = true;
    // }
    // if(!rightOpponent && prefer_lane_id > lane_id && currentBehavior != BehaviorState::LeftLaneChange){
    //     needRightLaneChange = true;
    //     prev_lane_id = lane_id;
    // }

    // ROS_INFO("front car : %d , stationary : %d", frontOpponent, stationaryFrontOpponent);

    // check if Lane Change is essential

    // ROS_INFO("prev: %d, lane_id: %d", prevLaneID, globalLaneArray.lanes[0].lane_id);
    // determine doneLC

    // ROS_INFO("lEgo : %f", lEgo);
    // if(abs(lEgo)>wLane*0.7) frontOpponent = false;
    // if(abs(lEgo)>wLane*0.7) checkObstacle = true;


    // ROS_INFO("countInit: %d",countInit);

    // if(frontOpponent){
    //     if(!leftOpponent && lane_id > 1) needLeftLaneChange = true;
    //     if(!rightOpponent && lane_id <= 1) needRightLaneChange = true;
    //     prev_lane_id = lane_id;
    //     // ROS_INFO("111");
    // }
    n0 = optimalLaneArray.lanes[0].waypoints.size();
    float sarrOpt[n0];
    // calculate Frenet longitudinal length of egolane            
    psarr = sarrOpt;
    this->calculateLon(n0, psarr, optimalLaneArray.lanes[0]);

    // calculate Frenet coordinate of ego vehicle
    psl = slOpt;
    this->calculateFrenet(n0, psarr, egoPose.position.x, egoPose.position.y, egoTwist.linear.x, egoTwist.linear.y, psl, optimalLaneArray.lanes[0]);
    if(!isnan(slOpt[0])){
        sOpt = slOpt[0];
        lOpt = slOpt[1];
        dsOpt = slOpt[2];
        dlOpt = slOpt[3];    
    }


    if(countBehaviorReady > runRate*thresBehaviorReady){
        missionStart = true;
        // ROS_INFO("BehaviorReady Time Out!!!");
    }
    //update behavior factor
    behaviorFactor.front_vel = front_vel; // done
    behaviorFactor.front_dist = front_dist;
    behaviorFactor.xObstacle = xObstacle;
    behaviorFactor.yObstacle = yObstacle;

    behaviorFactor.current_lane_id = lane_id;
    behaviorFactor.prefer_lane_id = prefer_lane_id;

    behaviorFactor.missionStart = missionStart;
    behaviorFactor.missionEnd = missionEnd;

    behaviorFactor.frontOpponent = frontOpponent; // need to test
    behaviorFactor.stationaryFrontOpponent = stationaryFrontOpponent; //need to test

    behaviorFactor.stopCheck = stopCheck;
    behaviorFactor.laneChangeDone = laneChangeDone;

    behaviorFactor.isInBank = isInBank;
    behaviorFactor.sEgo = sEgo;
    behaviorFactor.lEgo = lEgo;
    behaviorFactor.dsEgo = dsEgo;
    behaviorFactor.dlEgo = dlEgo;
    behaviorFactor.sOpt = sOpt;
    behaviorFactor.lOpt = lOpt;
    behaviorFactor.lOptFar = lOptFar;


    // ROS_INFO("frontdist: %f", front_dist);
    b_factor_pub.publish(behaviorFactor);

    // if (false) accFlag = true;  // temp condition

    if(frontOpponent){
        visualization_msgs::Marker obs_marker;
        obs_marker.header.stamp = ros::Time::now();
        obs_marker.header.frame_id = "map" ; //global_lane_array.header.frame_id;
        obs_marker.id = 1;
        obs_marker.ns = "obstacle";
        obs_marker.type = visualization_msgs::Marker::CUBE;
        obs_marker.action = visualization_msgs::Marker::ADD;                  
        obs_marker.pose.position.x = xObstacle;
        obs_marker.pose.position.y = yObstacle;
        obs_marker.pose.position.z = 0;
        obs_marker.color.r = 1.0;
        obs_marker.color.g = 0.0;
        obs_marker.color.b = 0.0;
        obs_marker.color.a = 1.0;
        obs_marker.lifetime = ros::Duration(0.05);
        obs_marker.scale.x = 3.0;
        obs_marker.scale.y = 3.0;
        obs_marker.scale.z = 3.0; 
        obs_pub.publish(obs_marker);
    }
}

void BehaviorPlanner::updateBehaviorState(){
    if(!getPose){
        ROS_INFO("Can not receive pose");
        return;
    }
    updateFactors();
    onDriving = false;
    BehaviorState prevBehavior = currentBehavior;
    if(prevBehavior == BehaviorState::MissionEnd) currentBehavior = BehaviorState::MissionEnd;
    else if(prevBehavior == BehaviorState::BehaviorInit){
        if(vehicleReady){
            currentBehavior = BehaviorState::BehaviorReady;
        }
    }
    else if(prevBehavior == BehaviorState::BehaviorReady){
        countBehaviorReady++;
        if(missionStart){
            countBehaviorReady = 0;
            onDriving = true;
        }
    }
    else if(missionEnd){
        currentBehavior = BehaviorState::MissionEndStop;
    }
    else if(prevBehavior == BehaviorState::MissionEndStop){
        if(stopCheck){
            currentBehavior = BehaviorState::MissionEnd;
        }
    }
    else if(prevBehavior == BehaviorState::Stop) {
        KeepSpeed = false;
        if(stopCheck){
            currentBehavior = BehaviorState::MissionEnd;
        }
    }
    else if(currentMission == MissionState::MissionSlowOn){

        if (KeepSpeed) {
            currentBehavior = prevBehavior;
            KeepSpeed = false;
        }
        else {
            currentBehavior = BehaviorState::SlowOn;
        }
    }
    else if(prevBehavior == BehaviorState::SlowOn){
        KeepSpeed = false;
        if(currentMission != MissionState::MissionSlowOn) onDriving = true;
    }
    else if(currentMission == MissionState::MissionStop){

        if (KeepSpeed) {
            currentBehavior = prevBehavior;
            KeepSpeed = false;
        }
        else{
            currentBehavior = BehaviorState::Stop;
        }
    }    
    else if(onDrivingFlag){
        onDriving = true;
    }
    if(onDriving){
        // ROS_INFO("ACC fsm %d", accFlag);
        if(overtakingFlag) {
            currentBehavior = BehaviorState::Overtaking;
        }
        else if (accFlag) {
            currentBehavior = BehaviorState::ACC;
        }
        else if (obsavoidFlag) {
            currentBehavior = BehaviorState::ObstacleAvoidance;
        }
        else if (aebFlag) {
            currentBehavior = BehaviorState::EmergencyStop;
        }
        // if(needLeftLaneChange){
        //     currentBehavior = BehaviorState::LeftLaneChange;
        // }
        // else if(needRightLaneChange){
        //     currentBehavior = BehaviorState::RightLaneChange;
        // }
        else{
            currentBehavior = BehaviorState::FreeDrive;
        }
    }

    onDrivingFlag = false;

    if(currentBehavior == BehaviorState::FreeDrive || currentBehavior == BehaviorState::Overtaking || currentBehavior == BehaviorState::ACC || currentBehavior == BehaviorState::ObstacleAvoidance || currentBehavior == BehaviorState::EmergencyStop){
        onDrivingFlag = true;
    }
}

void BehaviorPlanner::publishMsgs(){
    behavior_msg.data = currentBehavior;
    b_state_pub.publish(behavior_msg);
    //light cmd
    // if(currentBehavior == BehaviorState::LeftLaneChange) light_msg.data = -1;
    // else if(currentBehavior == BehaviorState::RightLaneChange) light_msg.data = 1;
    // else light_msg.data = 0;
    std::cout<< stateToStringBehavior(currentBehavior) <<std::endl;
    light_pub.publish(light_msg);
}

BehaviorState BehaviorPlanner::getCurrentBehavior(){
    return currentBehavior;
}

void BehaviorPlanner::calculateDistToStopLine(){

    std::vector<std::pair<double, double>> latlon_stopline = {
        // {35.65394463605, 128.39599816698}
        {35.6540720659, 128.39584478693}
     };
    
    double easting, northing;
    int zone;
    bool northp;

    GeographicLib::UTMUPS::Forward(latlon_stopline[0].first, latlon_stopline[0].second, zone, northp, easting, northing);

    double local_x = easting - origin_easting;
    double local_y = northing - origin_northing;

    distToStopLine = sqrt(pow(local_x - egoPose.position.x, 2) + pow(local_y - egoPose.position.y, 2));
}

void BehaviorPlanner::overtakingCallback(const std_msgs::Int8::ConstPtr& msg){
    getOvertakingFlag = true;
    if(msg->data == 0){
        overtakingFlag = false;
        accFlag = false;
        obsavoidFlag = false;
        aebFlag = false;
    }
    else if(msg->data == 1){
        overtakingFlag = true;
        accFlag = false;
        obsavoidFlag = false;
        aebFlag = false;
    }
    else if(msg->data == 2){
        overtakingFlag = false;
        accFlag = true;
        obsavoidFlag = false;
        aebFlag = false;
    }
    else if(msg->data == 3){
        overtakingFlag = false;
        accFlag = false;
        obsavoidFlag = true;
        aebFlag = false;
    }
    else if(msg->data == 4){
        overtakingFlag = false;
        accFlag = false;
        obsavoidFlag = false;
        aebFlag = true;
    }
}

void BehaviorPlanner::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
    getPose = true;
    egoPose = msg->pose;
}
void BehaviorPlanner::twistCallback(const geometry_msgs::TwistStampedConstPtr& msg){
    getSpeed = true;
    egoTwist = msg->twist;
    // egoSpeed = sqrt(pow(msg->twist.linear.x,2)+pow(msg->twist.linear.y,2));;
}

void BehaviorPlanner::subtypeCallback(const hmcl_msgs::PolygonFlag::ConstPtr& msg) {
    PolygonFlag.isinJunction = msg->isinJunction;
    PolygonFlag.isinExit = msg->isinExit;
    PolygonFlag.isinBank = msg->isinBank;
    PolygonFlag.isinFreespace = msg->isinFreespace;
    PolygonFlag.isinCrosswalk = msg->isinCrosswalk;
}

// void BehaviorPlanner::odometryCallback(const nav_msgs::Odometry& msg){
//     getPose = true;
//     egoPose = msg.pose.pose;
// }

void BehaviorPlanner::vehicleStatusCallback(const hmcl_msgs::VehicleStatusConstPtr &msg){
    getSpeed2 = true;
    egoSpeed = msg->wheelspeed.wheel_speed; 
}

void BehaviorPlanner::objsCallback(const autoware_msgs::DetectedObjectArray& msg){
    getOpponent = true;
    detectedObjects = msg;
}


void BehaviorPlanner::routeCallback(const hmcl_msgs::LaneArray &msg){
    getGlobal = true;
    globalLaneArray = msg;
}
void BehaviorPlanner::optCallback(const hmcl_msgs::LaneArray &msg){
    getOpt = true;
    optimalLaneArray = msg;
}
void BehaviorPlanner::missionCallback(const std_msgs::Int16::ConstPtr& msg){
    getMission = true;
    currentMission = (MissionState)msg->data;
}
void BehaviorPlanner::mapverCallback(const std_msgs::Int8::ConstPtr& msg){
    getMapver = true;
    map_ver = msg->data;
}

void BehaviorPlanner::setMissionStateCallback(const std_msgs::Int16::ConstPtr& msg){
    getExternalMission = true;
    externalMission = msg->data;
}

void BehaviorPlanner::viz_behavior(){
    if(!getPose){
        return;
    }
    visualization_msgs::Marker behaviorMarker;

    behaviorMarker.header.frame_id = "map";
    behaviorMarker.header.stamp = ros::Time();
    behaviorMarker.ns = "behavior";
    behaviorMarker.id = 0;
    behaviorMarker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    behaviorMarker.action = visualization_msgs::Marker::ADD;

    behaviorMarker.pose.position.x = egoPose.position.x;
    behaviorMarker.pose.position.y = egoPose.position.y + 8;
    behaviorMarker.pose.position.z = 11;

    behaviorMarker.scale.z = 4;
    behaviorMarker.text = stateToStringBehavior(currentBehavior);

    behaviorMarker.color.a = 1.0;
    behaviorMarker.color.r = 0.0;
    behaviorMarker.color.g = 1.0;
    behaviorMarker.color.b = 1.0;

    behavior_viz_pub.publish(behaviorMarker);
}

void BehaviorPlanner::stopline_viz(){
   
    visualization_msgs::Marker stoplineMarker;

    stoplineMarker.header.frame_id = "map";
    stoplineMarker.header.stamp = ros::Time();
    stoplineMarker.ns = "stopline"; 
    stoplineMarker.type = visualization_msgs::Marker::SPHERE;
    stoplineMarker.action = visualization_msgs::Marker::ADD;
    stoplineMarker.scale.x = 3.0;
    stoplineMarker.scale.y = 3.0;
    stoplineMarker.scale.z = 3.0;
    stoplineMarker.color.a = 1.0;
    stoplineMarker.color.r = 0.0;
    stoplineMarker.color.g = 0.0;
    stoplineMarker.color.b = 1.0;

    std::vector<std::pair<double, double>> latlon_stopline = {
        {35.65394463605, 128.39599816698}
     };
    
    double easting, northing;
    int zone;
    bool northp;

    GeographicLib::UTMUPS::Forward(latlon_stopline[0].first, latlon_stopline[0].second, zone, northp, easting, northing);

    double local_x = easting - origin_easting;
    double local_y = northing - origin_northing;

    stoplineMarker.id = 0;
    stoplineMarker.pose.position.x = local_x;
    stoplineMarker.pose.position.y = local_y;
    stoplineMarker.pose.position.z = 0.0;

    stopline_viz_pub.publish(stoplineMarker);
}


int main (int argc, char** argv)
{

    ros::init(argc, argv, "behavior_planner");

    BehaviorPlanner behavior_node;

    ros::spin();
    
}