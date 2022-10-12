#include "behavior_planner.h"
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



BehaviorPlanner::BehaviorPlanner(){

    nh_.param<double>("runRate", runRate, 20);
    nh_.param<float>("wLane", wLane, 3.5);
    nh_.param<float>("lenEgo", lenEgo, 4.180);
    nh_.param<float>("frontlenEgo", frontlenEgo, 4.180/2);// need to check lidar position in real vehicle
    nh_.param<float>("minFront", minFront, 100);
    nh_.param<float>("unknownFront", unknownFront, 50);
    nh_.param<int>("nStore", nStore, 10); //need to check
    nh_.param<float>("thresLC", thresLC, 0.5); // need to check if 0.5 is sufficient
    nh_.param<float>("thresStop", thresStop, 0.1); // need to check if 0.01 is sufficient
    nh_.param<float>("thresCW", thresCW, 25);
    nh_.param<float>("thresSB", thresSB, 20);
    nh_.param<float>("thresTurn", thresTurn, 30);
    nh_.param<float>("thresTLtime", thresTLtime, 3);
    nh_.param<float>("thresDistSG", thresDistSG, 30);
    nh_.param<float>("successDistSG", successDistSG, 3);

    // pose_sub = nh_.subscribe("/current_pose",1,&BehaviorPlanner::poseCallback,this);
    pose_sub = nh_.subscribe("/pose_estimate", 1, &BehaviorPlanner::odometryCallback, this);
    // vel_sub = nh_.subscribe("/current_velocity", 1, &BehaviorPlanner::twistCallback,this);
    vel_sub = nh_.subscribe("/vehicle_status", 1, &BehaviorPlanner::vehicleStatusCallback, this);
    objs_sub = nh_.subscribe("/detection/lidar_tracker/objects",1, &BehaviorPlanner::objsCallback,this);
    // objs_sub = nh_.subscribe("/tracking_car/objects",1, &BehaviorPlanner::objsCallback,this);
    sb_sub = nh_.subscribe("/tracking_traffic_sign/objects",1, &BehaviorPlanner::sbCallback,this);
    lug_sub = nh_.subscribe("/tracking_luggage/objects",1, &BehaviorPlanner::luggageCallback,this);
    //goal_sub = nh_.subscribe("move_base_simple/goal", 1, &BehaviorPlanner::callbackGetGoalPose, this);
    start_goal_sub = nh_.subscribe("/start_goal_pose", 1, &BehaviorPlanner::v2xStartGoalCallback, this);
    v2x_spat_sub = nh_.subscribe("/SPAT",1, &BehaviorPlanner::v2xSPATCallback, this);
    // route_sub = nh_.subscribe("/global_traj", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    route_sub = nh_.subscribe("/lane_in_range", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    mission_sub = nh_.subscribe("/mission_state", 1, &BehaviorPlanner::missionCallback, this);
    ped_sub = nh_.subscribe("/pedestrian", 1 , &BehaviorPlanner::pedestrianCallback, this);

    b_factor_pub = nh_.advertise<hmcl_msgs::BehaviorFactor>("/behavior_factor",1,true);
    b_state_pub = nh_.advertise<std_msgs::Int16>("/behavior_state",1,true);
    // behavior_timer = nh_.createTimer(ros::Duration(0.05), &BehaviorPlanner::behavior_handler,this);

    // behavior factors
    missionStart = false;
    approachToStartPos = false;
    startArrivalCheck = false;
    startArrivalSuccess = false;
    frontCar = false;
    stationaryFrontCar = false;
    approachToCrosswalk = false;
    crosswalkPass = false;
    pedestrianOnCrosswalk = false;
    leftTurn = false;
    rightTurn = false;
    turn = false;
    trafficLightStop = false;
    stopCheck = false;
    luggageDrop = false;
    brokenFrontCar = false;
    laneChangeDone = false;
    essentialLaneChange = false;
    speedBumpSign = false;
    speedBumpPass = false;
    approachToGoalPos = false;
    startArrivalCheck = false;


    getObject = false;
    getSB = false;
    getLuggage = false;
    getPedestrian = false;
    getGlobal = false;
    getPose = false;
    getSpeed = false;
    getSGpos = false;
    getSPAT = false;
    getMission = false;

    // to velocity planner
    front_id = -1;
    stop_line_stop = false;

    unknown_id = -1;

    currentBehavior = BehaviorState::Init2;
    NormalDrive = false;
    LaneFollowing = false;
    Turn = false;

    inCW = false;
    frontPrev = false;
    stationaryPrev = false;
    sbPrev = false;
    countFront = 0;
    countStationary = 0;
    countSB = 0;
    prevLaneID = -1;

    boost::thread callbackhandler(&BehaviorPlanner::callbackthread,this); 
}
void BehaviorPlanner::callbackthread(){   
    ros::Rate loop_rate(runRate); // rate  
    while(ros::ok()){
        updateBehaviorState();
        // ROS_INFO("DKJF");
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
    float p[2] = {lane.waypoints[idx+1].pose.pose.position.x - lane.waypoints[idx].pose.pose.position.x, lane.waypoints[idx+1].pose.pose.position.y - lane.waypoints[idx].pose.pose.position.y};
    float v[2] = {vx, vy};
    float dp = sqrt(pow(p[0],2)+pow(p[1],2));
    float dx = sqrt(pow(x[0],2)+pow(x[1],2));
    float sv = sqrt(pow(v[0],2)+pow(v[1],2));
    float theta = acos((x[0]*p[0]+x[1]*p[1])/(dx*dp));
    float theta2 = acos((v[0]*p[0]+v[1]*p[1])/(sv*dp));
    ROS_INFO("psarr: %f,dp %f, dx %f, sv %f, theta %f, theta2 %f",psarr[idx],dp, dx, sv, theta, theta2);
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


void BehaviorPlanner::updateFactors(){
    ROS_INFO("---------------BEHAVIOR_PLANNER----------------");
    while(1){
        if(!getPose){
            ROS_INFO("Can not receive pose");
            break;
        }
        if(!getSpeed){
            ROS_INFO("Can not receive speed");
            break;
        }
        if(!getSGpos){
            ROS_INFO("Can not receive start and goal pos");
            break;
        }


        // behavior factors
        // missionStart = true; //for test
        // leftTurn = false;
        // rightTurn = false;
        approachToStartPos = false;
        frontCar = false;
        stationaryFrontCar = false;
        approachToCrosswalk = false;
        crosswalkPass = false;
        pedestrianOnCrosswalk = false; // need to get from map
        turn = false;
        trafficLightStop = false;
        stopCheck = false;
        luggageDrop = false;  // need to implement
        brokenFrontCar = false;
        essentialLaneChange = false;
        speedBumpSign = false;
        approachToGoalPos = false;
        goalArrivalCheck = false;

        // to velocity planner
        front_id = -1;
        stop_line_stop = false;

        unknown_id = -1;

        inCW = false;

        if(pedestrian){
            pedestrianOnCrosswalk = true;
        }

        // check if ego stop
        if(egoSpeed < thresStop) stopCheck = true;

        float distToStart = sqrt(pow(egoPose.position.x-startX,2)+pow(egoPose.position.y-startY,2));
        if(distToStart < thresDistSG){
            approachToStartPos = true;
        }
        if(distToStart < successDistSG && stopCheck){
            startArrivalCheck = true;
        }
        ROS_INFO("dist to START: %f", distToStart);

        float distToGoal = sqrt(pow(egoPose.position.x-goalX,2)+pow(egoPose.position.y-goalY,2));
        if(distToGoal < thresDistSG){
            approachToGoalPos = true;
        }
        if(distToGoal < successDistSG && stopCheck){
            goalArrivalCheck = true;
        }
        if(startArrivalSuccess == false){
            approachToGoalPos = false;
        }
        approachToGoalPos = false;
        ROS_INFO("dist to STOP: %f", distToGoal);

        if(!getMission){
            ROS_INFO("Can not receive mission state");
            break;
        }

        // check mission start
        if((int)currentMission >= 3){
            missionStart = true;
        }

        // return if mission doesn't start
        if(missionStart == false){
            ROS_INFO("Mission doesn't start yet");
            break;
        }

        if (!getGlobal){
            ROS_INFO("Can not receive global trajectory");
            break;
        }
        
        if(!getObject){
            ROS_INFO("Can not receive objects");
        }
        if(!getSB){
            ROS_INFO("Can not receive speed bump data");
        }
        if(!getLuggage){
            ROS_INFO("Can not receive luggage data");
        }
        if(!getPedestrian){
            ROS_INFO("Can not receive pedestrian data");
        }
        if(!getSPAT){
            ROS_INFO("Can not receive SPAT data");
        }

        ROS_INFO("global lanes size: %d", globalLaneArray.lanes.size());
        ROS_INFO("ego lane wpts size: %d", globalLaneArray.lanes[0].waypoints.size());
        if(globalLaneArray.lanes.size() < 1||globalLaneArray.lanes[0].waypoints.size()<1){
            ROS_INFO("global array doesn't contain waypoint");
            break;
        }
        float distToGlobal = sqrt(pow(egoPose.position.x-globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x,2)+pow(egoPose.position.y-globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y,2));
        if(distToGlobal > 5){
            ROS_INFO("ego vehicle is not located on the global lane");
            break;
        }

        int n0 = globalLaneArray.lanes[0].waypoints.size();
        float sarr0[n0];
        float slEgo[4], slObj[4];
        
        float sEgo, dsEgo, lEgo;
        float* psarr;
        float* psl;

        int on = detectedObjects.objects.size();
        int sbn = sb.objects.size();
        int lugn = luggage.objects.size();
        float xObj[on], yObj[on], vxObj[on], vyObj[on];
        float sObj[on], lObj[on], dsObj[on], dlObj[on];
        float xSB[sbn], ySB[sbn];
        float xLug[lugn], yLug[lugn], vxLug[lugn], vyLug[lugn];
        float sLug[lugn], lLug[lugn], dsLug[lugn], dlLug[lugn];

        //calculate yaw angle
        float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.x + egoPose.orientation.w*egoPose.orientation.z), 1-2*(egoPose.orientation.y*egoPose.orientation.y + egoPose.orientation.z*egoPose.orientation.z));
        ROS_INFO("egopose x: %f, y: %f",egoPose.position.x, egoPose.position.y);
        ROS_INFO("globalpose x: %f, y: %f",globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x,globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y);

        // convert relative coordinate to global coordinate
        for(int i = 0; i < on; i++){
            xObj[i] = egoPose.position.x + detectedObjects.objects[i].pose.position.x*cos(yaw)-detectedObjects.objects[i].pose.position.y*sin(yaw);
            yObj[i] = egoPose.position.y + detectedObjects.objects[i].pose.position.x*sin(yaw)+detectedObjects.objects[i].pose.position.y*cos(yaw);
            vxObj[i] = detectedObjects.objects[i].velocity.linear.x*cos(yaw) - detectedObjects.objects[i].velocity.linear.y*sin(yaw);
            vyObj[i] = detectedObjects.objects[i].velocity.linear.x*sin(yaw) + detectedObjects.objects[i].velocity.linear.y*cos(yaw);
            ROS_INFO("i:%d,x: %f,y: %f,vx: %f,vy: %f",i,xObj[i],yObj[i],vxObj[i],vxObj[i]);
        }
        for(int i = 0; i < lugn; i++){
            xLug[i] = egoPose.position.x + luggage.objects[i].pose.position.x*cos(yaw)-luggage.objects[i].pose.position.y*sin(yaw);
            yLug[i] = egoPose.position.y + luggage.objects[i].pose.position.x*sin(yaw)+luggage.objects[i].pose.position.y*cos(yaw);
            vxLug[i] = luggage.objects[i].velocity.linear.x*cos(yaw) - luggage.objects[i].velocity.linear.y*sin(yaw);
            vyLug[i] = luggage.objects[i].velocity.linear.x*sin(yaw) + luggage.objects[i].velocity.linear.y*cos(yaw);
            ROS_INFO("i:%d,xLug: %f,yLug: %f,vxLug: %f,vyLug: %f",i,xLug[i],yLug[i],vxLug[i],vxLug[i]);
        }
        for(int i = 0; i < sbn; i++){
            xSB[i] = egoPose.position.x + sb.objects[i].pose.position.x*cos(yaw)-sb.objects[i].pose.position.y*sin(yaw);
            ySB[i] = egoPose.position.y + sb.objects[i].pose.position.x*sin(yaw)+sb.objects[i].pose.position.y*cos(yaw);
            ROS_INFO("i:%d,xSB: %f,ySB: %f",i,xSB[i],ySB[i]);

            // calculate distance to speed bump
            float distSB = sqrt(pow(egoPose.position.x-xSB[i],2)+pow(egoPose.position.y-ySB[i],2));
            if(distSB < thresSB){
                speedBumpSign = true;
                countSB = 0;
                sbPrev = true;
                speedBumpPass = false;
            }
        }
        
        if(sbPrev){
            if(speedBumpSign == false){
                if(countSB < nStore){
                    speedBumpSign = true;
                    countSB++;
                }
                else{
                    sbPrev = false;
                    countSB = 0;
                    speedBumpPass = true;
                }
            }
        }
        
        

        // calculate Frenet longitudinal length of egolane            
        psarr = sarr0;
        this->calculateLon(n0, psarr, globalLaneArray.lanes[0]);

        // calculate Frenet coordinate of ego vehicle
        psl = slEgo;
        this->calculateFrenet(n0, psarr, egoPose.position.x, egoPose.position.y, 0, 0, psl, globalLaneArray.lanes[0]);
        sEgo = slEgo[0];
        lEgo = slEgo[1];
        dsEgo = egoSpeed;
        ROS_INFO("egopose s: %f, l: %f, dsEgo: %f",sEgo,lEgo, dsEgo);


        // calculate Frenet coordinate of objects
        psl = slObj;
        for(int i = 0; i < on; i++){
            psarr = sarr0;
            this->calculateFrenet(n0, psarr, xObj[i], yObj[i], vxObj[i], vyObj[i], psl, globalLaneArray.lanes[0]);
            sObj[i] = slObj[0];
            lObj[i] = slObj[1];
            dsObj[i] = slObj[2];
            dlObj[i] = slObj[3];
            bool isCar = false;
            if(detectedObjects.objects[i].label == "car") isCar = true;
            ROS_INFO("i:%d,sObj: %f,lObj: %f,vx: %f,vy: %f, label: %d",i,sObj[i],lObj[i],dsObj[i],dlObj[i],isCar);
            if(abs(lObj[i]) <= wLane/2){
                // front vehicle
                if(sObj[i]-sEgo < minFront && sObj[i]-sEgo > 0){
                    front_id = i;
                    minFront = sObj[i]-sEgo;
                    frontCar = true;
                }
            }
        } 
        for(int i = 0; i < lugn; i++){
            psarr = sarr0;
            this->calculateFrenet(n0, psarr, xLug[i], yLug[i], vxLug[i], vyLug[i], psl, globalLaneArray.lanes[0]);
            sLug[i] = slObj[0];
            lLug[i] = slObj[1];
            dsLug[i] = slObj[2];
            dlLug[i] = slObj[3];
            ROS_INFO("i:%d,sLug: %f,lLug: %f,vx: %f,vy: %f",i,sLug[i],lLug[i],dsLug[i],dlLug[i]);
            if(abs(lLug[i]) <= wLane/2){
                // front luggage
                if(sLug[i]-sEgo < unknownFront && sLug[i]-sEgo > 0){
                    unknownFront = sLug[i]-sEgo;
                    luggageDrop = true;
                }
            }
        }  

        
        // calculate safe distance and check if it is stationary car
        if(frontCar){
            countFront = 0;
            frontPrev = true;
            if (sqrt(pow(vxObj[front_id],2)+pow(vyObj[front_id],2)) < thresStop){
                stationaryFrontCar = true;
                stationaryPrev = true;
            }
        }

        // store front car for nStore time steps
        if(frontPrev){
            if(frontCar == false){
                if(countFront < nStore){
                    front_id = 1000;
                    frontCar = true;
                    stationaryFrontCar = stationaryPrev;
                    countFront++;
                }
                else{
                    frontPrev = false;
                    stationaryPrev = false;
                    countFront = 0;
                }
            }
        }

        if(stationaryFrontCar){
            countStationary++;
            if(countStationary > 10*runRate){
                brokenFrontCar = true;
                if(prevLaneID == -1){
                    laneChangeDone = false;
                    prevLaneID = globalLaneArray.lanes[0].lane_id;
                }
            }
        }
        else{
            countStationary = 0;
        }
        ROS_INFO("front car : %d , stationary : %d", frontCar, stationaryFrontCar);

        // compute dist to crosswalk
        float distToCW = -1;
        for(int i = 0; i < n0; i++){
            if(globalLaneArray.lanes[0].waypoints[i].Crosswalk == true){
                ROS_INFO("--------Crosswalk Checker---------");
                float cwX, cwY;
                cwX = globalLaneArray.lanes[0].waypoints[i].pose.pose.position.x-egoPose.position.x;
                cwY = globalLaneArray.lanes[0].waypoints[i].pose.pose.position.y-egoPose.position.y;
                distToCW = sqrt(pow(cwX,2)+pow(cwY,2));
                if(distToCW < thresCW && distToCW > 0){
                    approachToCrosswalk = true;
                    break;
                }
            }
        }

        // decide if ego is in crosswalk
        if(globalLaneArray.lanes[0].waypoints[0].Crosswalk == true){
            inCW = true;
        }
        ROS_INFO("distToCW: %f,inCW: %d, crosswalkPass: %d", distToCW, inCW, crosswalkPass);

        int firstIdJunc = -1;
        int lastIdJunc = -1;
        bool isJunc = false;
        float dJunc = -1, lenJunc = -1;
        float StrX, StrY, JuncX, JuncY;
        for(int i = 0; i < n0; i++){    
            if(globalLaneArray.lanes[0].waypoints[i].Junction == true){
                if(firstIdJunc == -1){
                    firstIdJunc = i;
                    lastIdJunc = i;
                    isJunc = true;
                }
                else{
                    lastIdJunc = i;
                }
            }
            else if(isJunc == true){
                break;
            } 
        }
        if(isJunc){
            StrX = globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.x-globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
            StrY = globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.y-globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
            dJunc = sqrt(pow(StrX,2)+pow(StrY,2));
            ROS_INFO("StrX: %f, StrY: %f", StrX, StrY);
        }
        if(isJunc && dJunc < thresTurn){
            JuncX = globalLaneArray.lanes[0].waypoints[lastIdJunc].pose.pose.position.x-globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.x;
            JuncY = globalLaneArray.lanes[0].waypoints[lastIdJunc].pose.pose.position.y-globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.y;
            lenJunc = sqrt(pow(JuncX,2)+pow(JuncY,2));
            float lenStr = 0;
            float hGap = 0;
            if(firstIdJunc >= 2){
                StrX = globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.x-globalLaneArray.lanes[0].waypoints[firstIdJunc-2].pose.pose.position.x;
                StrY = globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.y-globalLaneArray.lanes[0].waypoints[firstIdJunc-2].pose.pose.position.y;
                lenStr = sqrt(pow(StrX,2)+pow(StrY,2));
                hGap = asin((StrX*JuncY-StrY*JuncX)/(lenStr*lenJunc));
            }
            else if(lastIdJunc >= 2 && lastIdJunc+2 < n0){
                StrX = globalLaneArray.lanes[0].waypoints[lastIdJunc+2].pose.pose.position.x-globalLaneArray.lanes[0].waypoints[lastIdJunc].pose.pose.position.x;
                StrY = globalLaneArray.lanes[0].waypoints[lastIdJunc+2].pose.pose.position.y-globalLaneArray.lanes[0].waypoints[lastIdJunc].pose.pose.position.y;
                lenStr = sqrt(pow(StrX,2)+pow(StrY,2));
                hGap = asin((JuncX*StrY-JuncY*StrX)/(lenStr*lenJunc));
            }
            if(hGap > 0.1){
                leftTurn = true;
                rightTurn = false;
            }
            else if(hGap < -0.1){
                leftTurn = false;
                rightTurn = true;
            }
        
            ROS_INFO("isJunc: %f, dJunc: %f", isJunc, dJunc);
            ROS_INFO("first: %d, last: %d", firstIdJunc, lastIdJunc);
            ROS_INFO("hGap: %f, lflag: %d, rflag: %d", hGap, leftTurn, rightTurn);
        }
        else{
            leftTurn = false;
            rightTurn = false;
        }
        if(leftTurn || rightTurn) turn = true;

        // check if Lane Change is essential
        if(globalLaneArray.lanes[0].lane_change_flag == true){
            essentialLaneChange = true;
            if(prevLaneID == -1){
                laneChangeDone = false;
                prevLaneID = globalLaneArray.lanes[0].lane_id;
            }
        }
        // determine doneLC
        if(prevLaneID != -1 && prevLaneID != globalLaneArray.lanes[0].lane_id && abs(lEgo) < thresLC){
            laneChangeDone = true;
            prevLaneID = -1;
        }

        // get traffic light state correspond to current lane and ego 
        // need to add signalID correctly to the map 
        int signal_id = -1;
        // int signal_id = globalLaneArray.lanes[0].signal_id;
        int eventState = -1;
        int timing_min_End_Time = -1;
        if(signal_id == 1 && leftTurn){
            eventState = junc1Signal.States[1].eventState;
            timing_min_End_Time = junc1Signal.States[1].timing_min_End_Time;
        }
        else if(signal_id == 1){
            eventState = junc1Signal.States[0].eventState;
            timing_min_End_Time = junc1Signal.States[0].timing_min_End_Time;
        }
        else if(signal_id == 2 && leftTurn){
            eventState = junc1Signal.States[4].eventState;
            timing_min_End_Time = junc1Signal.States[4].timing_min_End_Time;
        }
        else if(signal_id == 2){
            eventState = junc1Signal.States[3].eventState;
            timing_min_End_Time = junc1Signal.States[3].timing_min_End_Time;
        }
        else if(signal_id == 3 && leftTurn){
            eventState = junc1Signal.States[7].eventState;
            timing_min_End_Time = junc1Signal.States[7].timing_min_End_Time;
        }
        else if(signal_id == 3){
            eventState = junc1Signal.States[6].eventState;
            timing_min_End_Time = junc1Signal.States[6].timing_min_End_Time;
        }
        else if(signal_id == 4 && leftTurn){
            eventState = junc1Signal.States[10].eventState;
            timing_min_End_Time = junc1Signal.States[10].timing_min_End_Time;
        }
        else if(signal_id == 4){
            eventState = junc1Signal.States[9].eventState;
            timing_min_End_Time = junc1Signal.States[9].timing_min_End_Time;
        }
        else if(signal_id == 5 && leftTurn){
            eventState = junc2Signal.States[1].eventState;
            timing_min_End_Time = junc2Signal.States[1].timing_min_End_Time;
        }
        else if(signal_id == 5){
            eventState = junc2Signal.States[0].eventState;
            timing_min_End_Time = junc2Signal.States[0].timing_min_End_Time;
        }
        else if(signal_id == 6 && leftTurn){
            eventState = junc2Signal.States[4].eventState;
            timing_min_End_Time = junc2Signal.States[4].timing_min_End_Time;
        }
        else if(signal_id == 6){
            eventState = junc2Signal.States[3].eventState;
            timing_min_End_Time = junc2Signal.States[3].timing_min_End_Time;
        }
        else if(signal_id == 7 && leftTurn){
            eventState = junc2Signal.States[7].eventState;
            timing_min_End_Time = junc2Signal.States[7].timing_min_End_Time;
        }
        else if(signal_id == 7){
            eventState = junc2Signal.States[6].eventState;
            timing_min_End_Time = junc2Signal.States[6].timing_min_End_Time;
        }
        else if(signal_id == 8 && leftTurn){
            eventState = junc2Signal.States[10].eventState;
            timing_min_End_Time = junc2Signal.States[10].timing_min_End_Time;
        }
        else if(signal_id == 8){
            eventState = junc2Signal.States[9].eventState;
            timing_min_End_Time = junc2Signal.States[9].timing_min_End_Time;
        }
        else if(signal_id == 9 && leftTurn){
            eventState = junc3Signal.States[0].eventState;
            timing_min_End_Time = junc3Signal.States[0].timing_min_End_Time;
        }
        else if(signal_id == 10){
            eventState = junc3Signal.States[1].eventState;
            timing_min_End_Time = junc3Signal.States[1].timing_min_End_Time;
        }
        else if(signal_id == 11 && leftTurn){
            eventState = junc3Signal.States[4].eventState;
            timing_min_End_Time = junc3Signal.States[4].timing_min_End_Time;
        }
        else if(signal_id == 11){
            eventState = junc3Signal.States[3].eventState;
            timing_min_End_Time = junc3Signal.States[3].timing_min_End_Time;
        }
        if(rightTurn == false && signal_id != -1){
            // red light
            if(eventState == 3){
                trafficLightStop = true;
            }
            // green light
            else if(eventState == 5 || eventState == 6){
                if(timing_min_End_Time < thresTLtime){
                    trafficLightStop = true;
                }
                else{
                    trafficLightStop = false;
                }
            }
            // yellow light
            else if(eventState == 7 || eventState == 8){
                trafficLightStop = true;
            }
        }

        break;
    }
    
    if(approachToCrosswalk == false && inCW == false) crosswalkPass = true;
    if(turn || trafficLightStop) approachToCrosswalk = false;
    // startArrivalSuccess = startArrivalCheck; //for test
    ROS_INFO("turn: %d, apptoCW: %d", turn, approachToCrosswalk);

    if(startArrivalSuccess){
        approachToStartPos = false;
    }

    if(currentMission==MissionState::DriveToGoalPos){
        startArrivalSuccess = true;
    }
    
    //update behavior factor
    behaviorFactor.front_id = front_id; // done
    behaviorFactor.stop_line_stop = stop_line_stop;
    behaviorFactor.transition_condition.missionStart = missionStart;
    behaviorFactor.transition_condition.approachToStartPos = approachToStartPos;
    behaviorFactor.transition_condition.startArrivalCheck = startArrivalCheck;
    behaviorFactor.transition_condition.startArrivalSuccess = startArrivalSuccess;
    behaviorFactor.transition_condition.frontCar = frontCar; // need to test
    behaviorFactor.transition_condition.stationaryFrontCar = stationaryFrontCar; //need to test
    behaviorFactor.transition_condition.approachToCrosswalk = approachToCrosswalk;
    behaviorFactor.transition_condition.crosswalkPass = crosswalkPass;
    behaviorFactor.transition_condition.pedestrianOnCrosswalk = pedestrianOnCrosswalk;
    behaviorFactor.transition_condition.leftTurn = leftTurn; 
    behaviorFactor.transition_condition.rightTurn = rightTurn;
    behaviorFactor.transition_condition.turn = turn;
    behaviorFactor.transition_condition.trafficLightStop = trafficLightStop;
    behaviorFactor.transition_condition.stopCheck = stopCheck;
    behaviorFactor.transition_condition.luggageDrop = luggageDrop;
    behaviorFactor.transition_condition.brokenFrontCar = brokenFrontCar;
    behaviorFactor.transition_condition.laneChangeDone = laneChangeDone;
    behaviorFactor.transition_condition.essentialLaneChange = essentialLaneChange;
    behaviorFactor.transition_condition.speedBumpSign = speedBumpSign;
    behaviorFactor.transition_condition.speedBumpPass = speedBumpPass;
    behaviorFactor.transition_condition.approachToGoalPos = approachToGoalPos;
    behaviorFactor.transition_condition.goalArrivalCheck = goalArrivalCheck;
    b_factor_pub.publish(behaviorFactor);
}

void BehaviorPlanner::updateBehaviorState(){
    updateFactors();
    bool goToNormalDrive = false;
    bool goToLaneFollowing = false;
    bool goToTurn = false;
    BehaviorState prevBehavior = currentBehavior;
    if(NormalDrive){
        if(luggageDrop){
            currentBehavior = BehaviorState::FrontLuggage;
        }
        else if(stationaryFrontCar && prevBehavior == BehaviorState::TrafficLightStop){
            currentBehavior = BehaviorState::FrontCarStop;
        }
        else if(speedBumpSign){
            currentBehavior = BehaviorState::SpeedBump;
        }
        else if(approachToStartPos){
            currentBehavior = BehaviorState::StopAtStartPos;
        }
        else if(approachToGoalPos){
            currentBehavior = BehaviorState::StopAtGoalPos;
        }
        else if(essentialLaneChange){
            currentBehavior = BehaviorState::LaneChange;
        }
        else{
            if(LaneFollowing){
                if(turn){
                    if(trafficLightStop){
                        currentBehavior = BehaviorState::TrafficLightStop;
                    }
                    else{
                        goToTurn = true;
                    }
                }
                else if(trafficLightStop){
                    currentBehavior = BehaviorState::TrafficLightStop;
                }
                else if(approachToCrosswalk){
                    currentBehavior = BehaviorState::Crosswalk;
                }
                else{
                    goToLaneFollowing = true;
                }
            }
            if(Turn){
                if(pedestrianOnCrosswalk){
                    currentBehavior = BehaviorState::Pedestrian;
                }
                else if(turn == false){
                    goToLaneFollowing = true;
                }
            }
            if(prevBehavior == BehaviorState::TrafficLightStop){
                if(turn && (stopCheck || trafficLightStop == false)){
                    goToTurn = true;
                }
                else if(turn == false && trafficLightStop == false){
                    goToLaneFollowing = true;
                }
            }
            if(prevBehavior == BehaviorState::Crosswalk){
                if(pedestrianOnCrosswalk){
                    currentBehavior = BehaviorState::Pedestrian;
                }
                else if(crosswalkPass){
                    goToLaneFollowing = true;
                }
            }
            if(prevBehavior == BehaviorState::Pedestrian){
                if(pedestrianOnCrosswalk == false && turn){
                    if(trafficLightStop == true){
                        currentBehavior = BehaviorState::TrafficLightStop;
                    }
                    else{
                        goToTurn = true;
                    }
                }
                else if(pedestrianOnCrosswalk == false){
                    currentBehavior = BehaviorState::Crosswalk;
                }
            }

        }
    }
    else{
        if(prevBehavior == BehaviorState::Init2){
            if(missionStart){
                goToLaneFollowing = true;
            }
        }
        if(prevBehavior == BehaviorState::StopAtStartPos){
            if(startArrivalCheck){
                currentBehavior = BehaviorState::StartArrival;
            }
        }
        if(prevBehavior == BehaviorState::StartArrival){
            if(startArrivalSuccess){
                goToNormalDrive = true;
            }
        }
        if(prevBehavior == BehaviorState::StopAtGoalPos){
            if(goalArrivalCheck){
                currentBehavior = BehaviorState::GoalArrival;
            }
        }
        if(prevBehavior == BehaviorState::FrontLuggage){
            if(luggageDrop == false || stationaryFrontCar == false){
                goToNormalDrive = true;
            }
        }
        if(prevBehavior == BehaviorState::FrontCarStop){
            if(stationaryFrontCar == false){
                goToNormalDrive = true;
            }
            else if(brokenFrontCar){
                currentBehavior = BehaviorState::LaneChange;
            }
            else if(luggageDrop){
                currentBehavior = BehaviorState::FrontLuggage;
            }
        }
        if(prevBehavior == BehaviorState::LaneChange){
            if(laneChangeDone){
                goToNormalDrive = true;
            }
        }
        if(prevBehavior == BehaviorState::SpeedBump){
            if(speedBumpPass){
                goToNormalDrive = true;
            }
        }
    }
    if(goToNormalDrive){
        if(turn){
            goToTurn = true;
        }
        else if(approachToCrosswalk){
            currentBehavior = BehaviorState::Crosswalk;
        }
        else{
            goToLaneFollowing = true;
        }
    }
    if(goToLaneFollowing){
        if(frontCar){
            currentBehavior = BehaviorState::Follow;
        }
        else{
            currentBehavior = BehaviorState::Forward;
        }
    }
    if(goToTurn){
        if(rightTurn){
            currentBehavior = BehaviorState::RightTurn;
        }
        else{
            currentBehavior = BehaviorState::LeftTurn;
        }
    }
    NormalDrive = false;
    LaneFollowing = false;
    Turn = false;
    if(currentBehavior == BehaviorState::Follow || currentBehavior == BehaviorState::Forward){
        LaneFollowing = true;
        NormalDrive = true;
    }
    if(currentBehavior == BehaviorState::LeftTurn || currentBehavior == BehaviorState::RightTurn){
        Turn = true;
        NormalDrive = true;
    }
    if(currentBehavior == BehaviorState::TrafficLightStop || currentBehavior == BehaviorState::Crosswalk || currentBehavior == BehaviorState::Pedestrian){
        NormalDrive = true;
    }
    behavior_msg.data = currentBehavior;
    b_state_pub.publish(behavior_msg);
}
BehaviorState BehaviorPlanner::getCurrentBehavior(){
    return currentBehavior;
}

// void BehaviorPlanner::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
//     egoPose = msg->pose;
// }

void BehaviorPlanner::odometryCallback(const nav_msgs::Odometry& msg){
    getPose = true;
    egoPose = msg.pose.pose;
}

void BehaviorPlanner::vehicleStatusCallback(const hmcl_msgs::VehicleStatusConstPtr &msg){
    getSpeed = true;
    egoSpeed = msg->wheelspeed.wheel_speed; 
}

void BehaviorPlanner::objsCallback(const autoware_msgs::DetectedObjectArray& msg){
    getObject = true;
    detectedObjects = msg;
}

void BehaviorPlanner::sbCallback(const autoware_msgs::DetectedObjectArray& msg){
    getSB = true;
    sb = msg;
}

void BehaviorPlanner::luggageCallback(const autoware_msgs::DetectedObjectArray& msg){
    getLuggage = true;
    luggage = msg;
}

void BehaviorPlanner::v2xStartGoalCallback(const hmcl_msgs::MissionWaypoint& msg){
    getSGpos = true;
    startX = msg.start.x;
    startY = msg.start.y;
    goalX = msg.end.x;
    goalY = msg.end.y;
}

void BehaviorPlanner::v2xSPATCallback(const v2x_msgs::SPAT& msg){
    getSPAT = true;
    //traffic_signal
    if(msg.id == 1){
        junc1Signal = msg;
    }
    else if(msg.id == 2){
        junc2Signal = msg;
    }
    else if(msg.id == 3){
        junc3Signal = msg;
    }
}

void BehaviorPlanner::routeCallback(const hmcl_msgs::LaneArray &msg){
    getGlobal = true;
    globalLaneArray = msg;
}

void BehaviorPlanner::missionCallback(const std_msgs::Int16::ConstPtr& msg){
    getMission = true;
    currentMission = (MissionState)msg->data;
}

void BehaviorPlanner::pedestrianCallback(const std_msgs::Bool::ConstPtr& msg){
    getPedestrian = true;
    pedestrian = msg->data;
}


int main (int argc, char** argv)
{

    ros::init(argc, argv, "behavior_planner");

    BehaviorPlanner behavior_node;

    ros::spin();
    
}