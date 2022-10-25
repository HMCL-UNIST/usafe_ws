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
    nh_.param<float>("dFront", dFront, 40);
    nh_.param<float>("dLuggage", dLuggage, 40);
    nh_.param<float>("thresFrontStop", thresFrontStop, 20);
    nh_.param<float>("thresTurnStop", thresTurnStop, 15);    
    nh_.param<int>("nStore", nStore, 20); //need to check
    nh_.param<int>("thresInit2", thresInit2, 40);
    nh_.param<int>("thresStopAtStartPos", thresStopAtStartPos, 20);
    nh_.param<int>("thresStartArrival", thresStartArrival, 20);
    nh_.param<int>("thresPedestrian", thresPedestrian, 30);
    nh_.param<int>("thresFrontLuggage", thresFrontLuggage, 40);
    nh_.param<int>("thresFrontCarStop", thresFrontCarStop, 10);
    nh_.param<int>("thresSpeedBump", thresSpeedBump, 10);
    nh_.param<int>("thresStopAtGoalPos", thresStopAtGoalPos, 20);
    nh_.param<float>("thresObs", thresObs, 7); 
    nh_.param<float>("thresLC", thresLC, 1.0); // need to check if 1 is sufficient
    nh_.param<float>("thresStop", thresStop, 0.5); // need to check if 0.01 is sufficient
    nh_.param<float>("thresCW", thresCW, 15);
    nh_.param<float>("thresSB", thresSB, 25);
    nh_.param<float>("thresTurn", thresTurn, 25);
    nh_.param<float>("thresMinTurn", thresMinTurn, 15);
    nh_.param<float>("thresTL", thresTL, 25);
    nh_.param<float>("thresTLtime", thresTLtime, 3);
    nh_.param<float>("thresDistSG", thresDistSG, 15);
    nh_.param<float>("successDistSG", successDistSG, 5); //need to check 



    b_factor_pub = nh_.advertise<hmcl_msgs::BehaviorFactor>("/behavior_factor",1,true);
    b_state_pub = nh_.advertise<std_msgs::Int16>("/behavior_state",1,true);
    light_pub = nh_.advertise<std_msgs::Float64>("/light_cmd",1,true);
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
    checkObstacle = true;


    getObject = false;
    getSB = false;
    getLuggage = false;
    getPedestrian = false;
    getGlobal = false;
    getPose = false;
    getSpeed = false;
    getSGpos = false;
    getSPAT1 = false;
    getSPAT2 = false;
    getSPAT3 = false;
    getMission = false;
    getRet = false;
    getMob =false;

    // to velocity planner
    front_id = -1;
    front_dist = 100;
    front_vel = -1;
    stop_line_stop = false;
    xObstacle = -1;
    yObstacle = -1;
    xSBsign = -1;
    ySBsign = -1;
    prev_object_x = -1;
    prev_object_y = -1;

    unknown_id = -1;

    currentBehavior = BehaviorState::Init2;
    ePrevBehavior = BehaviorState::Init2;
    NormalDrive = false;
    LaneFollowing = false;
    Turn = false;
    localRet = false;
    startChecker = false;
    TLstopCheck = false;
    firstCWcheck = false;

    inCW = false;
    frontPrev = false;
    stationaryPrev = false;
    sbPrev = false;
    luggagePrev = false;
    countFront = 0;
    countStationary = 0;
    countSB = 0;
    countLuggage = 0;
    countObs = 0;
    countInit2 = 0;
    countStopAtStartPos = 0;
    countStartArrival = 0;
    countPedestrian = 0;
    countFrontLuggage = 0;
    countFrontCarStop = 0;
    countSpeedBump = 0;
    countStopAtGoalPos = 0;
    prevLaneID = -1;
    pedestrian = false;
    lightPrev = 0;
    
    // pose_sub = nh_.subscribe("/current_pose",1,&BehaviorPlanner::poseCallback,this);
    pose_sub = nh_.subscribe("/pose_estimate", 1, &BehaviorPlanner::odometryCallback, this);
    // vel_sub = nh_.subscribe("/current_velocity", 1, &BehaviorPlanner::twistCallback,this);
    vel_sub = nh_.subscribe("/vehicle_status", 1, &BehaviorPlanner::vehicleStatusCallback, this);
    // objs_sub = nh_.subscribe("/detection/lidar_tracker/objects",1, &BehaviorPlanner::objsCallback,this);
    objs_sub = nh_.subscribe("/tracking_car/objects",1, &BehaviorPlanner::objsCallback,this);
    // objs_sub = nh_.subscribe("/detected_objs",1, &BehaviorPlanner::objsCallback,this);
    sb_sub = nh_.subscribe("/tracking_traffic_sign/objects",1, &BehaviorPlanner::sbCallback,this);
    lug_sub = nh_.subscribe("/tracking_unknown/objects",1, &BehaviorPlanner::luggageCallback,this);
    //goal_sub = nh_.subscribe("move_base_simple/goal", 1, &BehaviorPlanner::callbackGetGoalPose, this);
    start_goal_sub = nh_.subscribe("/start_goal_pose", 1, &BehaviorPlanner::v2xStartGoalCallback, this);
    v2x_spat_sub = nh_.subscribe("/SPAT",1, &BehaviorPlanner::v2xSPATCallback, this);
    // route_sub = nh_.subscribe("/global_traj", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    route_sub = nh_.subscribe("/lane_in_range", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    mission_sub = nh_.subscribe("/mission_state", 1, &BehaviorPlanner::missionCallback, this);
    ped_sub = nh_.subscribe("/Ped_in_Crosswalk", 1 , &BehaviorPlanner::pedestrianCallback, this);
    ret_sub = nh_.subscribe("/local_return", 1, &BehaviorPlanner::localRetCallback, this);
    target_sub = nh_.subscribe("/detected_objs",1, &BehaviorPlanner::objectCallback,this);
    ped_obj_sub = nh_.subscribe("/tracking_pedestrian/objects",1, &BehaviorPlanner::pedObjectCallback,this);

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


void BehaviorPlanner::updateFactors(){
    std::cout<< "--BEHAVIOR--BEHAVIOR--BEHAVIOR--BEHAVIOR-- " <<std::endl;
    // ROS_INFO("---------------BEHAVIOR_PLANNER----------------");
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
        if(target_msg.node_wpts.size()<1){
            ROS_INFO("Empty mission node waypoints");
            break;
        }
        // behavior factors
        missionStart = true; //for test
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
        essentialLaneChange = false;
        speedBumpSign = false;
        approachToGoalPos = false;
        goalArrivalCheck = false;

        // to velocity planner
        front_id = -1;
        front_dist = 100;
        stop_line_stop = false;

        unknown_id = -1;

        inCW = false;


        // check if ego stop
        if(egoSpeed < thresStop) stopCheck = true;
    

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
        if(!getSPAT1 || !getSPAT2 || !getSPAT3){
            ROS_INFO("Can not receive SPAT data");
            break;
        }
        if(!getMob){
            ROS_INFO("cannnot receive mobileye");
        }

        ROS_INFO("global lanes size: %d", globalLaneArray.lanes.size());
        ROS_INFO("ego lane wpts size: %d", globalLaneArray.lanes[0].waypoints.size());

        if(startChecker){
            if(globalLaneArray.lanes.size() != 0){
                bool checker = false;
                for(int i = 0; i<globalLaneArray.lanes.size(); i++){
                    if(globalLaneArray.lanes[i].waypoints.size() != 0 && globalLaneArray.lanes[i].lane_id != 1000){
                        float tmpx = globalLaneArray.lanes[i].waypoints[globalLaneArray.lanes[i].waypoints.size()-1].pose.pose.position.x - globalLaneArray.lanes[i].waypoints[0].pose.pose.position.x;
                        float tmpy = globalLaneArray.lanes[i].waypoints[globalLaneArray.lanes[i].waypoints.size()-1].pose.pose.position.y - globalLaneArray.lanes[i].waypoints[0].pose.pose.position.y;
                        if(sqrt(pow(tmpx,2)+pow(tmpy,2)) > thresDistSG) checker = true;
                        ROS_INFO("tmpx %f, tmpy %f", tmpx, tmpy);
                    }
                }
                ROS_INFO("checker %d, laneid %d, goalid %d",checker, globalLaneArray.lanes[0].lane_id, (int)goalID);
                if(!checker && globalLaneArray.lanes[0].lane_id == (int)goalID){
                    ROS_INFO("Exception: goal stop");
                    approachToGoalPos = true;
                }                                                                                                                                                       
            }
            // if(globalLaneArray.lanes.size() < 1){
            //     approachToGoalPos = true;
            // }
            // bool checkid = false;
            // for(int i = 0; i < globalLaneArray.lanes.size(); i++){
            //     if(globalLaneArray.lanes[i].lane_id != 1000) checkid = true; 
            // }
            // if(!checkid) approachToGoalPos = true;
        }
        
        if(globalLaneArray.lanes.size() < 1){
            ROS_INFO("global array zero");
            break;
        }
        else if(globalLaneArray.lanes[0].waypoints.size() < 1){
            ROS_INFO("global array doesn't contain waypoint");
            break;
        }
        startChecker = true;
        
        if(pedestrian){
            pedestrianOnCrosswalk = true;
        }

        int n0 = globalLaneArray.lanes[0].waypoints.size();
        float sarr0[n0];
        float slEgo[4], slObj[4];
        
        float sEgo, dsEgo, lEgo;
        float* psarr;

        float* psl;

        float thresDetect = 30;

        int on = 0;
        int rawon = detectedObjects.objects.size();
        int sbn = 0;
        int rawsbn = sb.objects.size();
        int lugn = 0;
        int rawlugn = luggage.objects.size();

        for(int i = 0; i < rawon; i++){
            if(sqrt(pow(detectedObjects.objects[i].pose.position.x,2)+pow(detectedObjects.objects[i].pose.position.y,2)) < thresDetect){
                on++;
            }
        }
        for(int i = 0; i < rawsbn; i++){
            if(sqrt(pow(sb.objects[i].pose.position.x,2)+pow(sb.objects[i].pose.position.y,2)) < thresDetect){
                sbn++;
            }
        }
        for(int i = 0; i < rawlugn; i++){
            if(sqrt(pow(luggage.objects[i].pose.position.x,2)+pow(luggage.objects[i].pose.position.y,2)) < thresDetect){
                lugn++;
            }
        }

        float velMob = -1;
        float xObj[on], yObj[on], vxObj[on], vyObj[on], velObj[on];
        float sObj[on], lObj[on], dsObj[on], dlObj[on];
        float xSB[sbn], ySB[sbn], vxSB[sbn], vySB[sbn], sSB[sbn], lSB[sbn];
        float xLug[lugn], yLug[lugn], vxLug[lugn], vyLug[lugn], velLug[lugn];
        float sLug[lugn], lLug[lugn], dsLug[lugn], dlLug[lugn];
        float distToGlobal = 6;
        int idEgo = 0;

        for(int i = 0; i < n0; i++){
            float dGlobal = sqrt(pow(egoPose.position.x-globalLaneArray.lanes[0].waypoints[i].pose.pose.position.x,2)+pow(egoPose.position.y-globalLaneArray.lanes[0].waypoints[i].pose.pose.position.y,2));
            if(distToGlobal > dGlobal){
                distToGlobal = dGlobal;
                idEgo = i;
            }
        }
        if(distToGlobal > 5){
            ROS_INFO("ego vehicle is not located on the global lane");
            break;
        }

        float distToStart = sqrt(pow(egoPose.position.x-startX,2)+pow(egoPose.position.y-startY,2));
        ROS_INFO("targetID: %d start_idx: %d lane_id: %d startID: %d  distToStart: %f thresDistSG: %f", targetID, (int)start_idx, globalLaneArray.lanes[0].lane_id, (int)startID, distToStart, thresDistSG);
        if(targetID == (int)start_idx && globalLaneArray.lanes[0].lane_id == (int)startID && distToStart < thresDistSG){
            approachToStartPos = true;
        }
        if(distToStart < successDistSG && stopCheck){
            startArrivalCheck = true;
        }
        ROS_INFO("dist to START: %f, %d, %f", distToStart,globalLaneArray.lanes[0].lane_id, startID);
        float distToGoal = sqrt(pow(egoPose.position.x-goalX,2)+pow(egoPose.position.y-goalY,2));
        ROS_INFO("targetID: %d goal_idx: %d lane_id: %d goalID: %d  distToGoal: %f thresDistSG: %f", targetID, (int)goal_idx, globalLaneArray.lanes[0].lane_id, (int)goalID, distToGoal, thresDistSG);
        if(targetID == (int)goal_idx && globalLaneArray.lanes[0].lane_id == (int)goalID && distToGoal < thresDistSG){
            approachToGoalPos = true;
        }
        if(distToGoal < successDistSG && stopCheck){
            goalArrivalCheck = true;
        }    
        ROS_INFO("dist to STOP: %f, %d, %f", distToGoal, globalLaneArray.lanes[0].lane_id, goalID);

        //calculate yaw angle
        float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.x + egoPose.orientation.w*egoPose.orientation.z), 1-2*(egoPose.orientation.y*egoPose.orientation.y + egoPose.orientation.z*egoPose.orientation.z));
        // ROS_INFO("egopose x: %f, y: %f",egoPose.position.x, egoPose.position.y);
        // ROS_INFO("globalpose x: %f, y: %f",globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x,globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y);

        // convert relative coordinate to global coordinate
        int idxtmp = 0;
        for(int i = 0; i < rawon; i++){
            if(sqrt(pow(detectedObjects.objects[i].pose.position.x,2)+pow(detectedObjects.objects[i].pose.position.y,2)) < thresDetect){
                xObj[idxtmp] = egoPose.position.x + detectedObjects.objects[i].pose.position.x*cos(yaw)-detectedObjects.objects[i].pose.position.y*sin(yaw);
                yObj[idxtmp] = egoPose.position.y + detectedObjects.objects[i].pose.position.x*sin(yaw)+detectedObjects.objects[i].pose.position.y*cos(yaw);
                vxObj[idxtmp] = detectedObjects.objects[i].velocity.linear.x*cos(yaw) - detectedObjects.objects[i].velocity.linear.y*sin(yaw);
                velObj[idxtmp] = detectedObjects.objects[i].velocity.linear.x;
                vyObj[idxtmp] = detectedObjects.objects[i].velocity.linear.x*sin(yaw) + detectedObjects.objects[i].velocity.linear.y*cos(yaw);
                idxtmp++;
                // ROS_INFO("i:%d,x: %f,y: %f,vx: %f,vy: %f",i,xObj[i],yObj[i],vxObj[i],vxObj[i]);
            }
        }
        idxtmp = 0;
        for(int i = 0; i < rawlugn; i++){
            if(sqrt(pow(luggage.objects[i].pose.position.x,2)+pow(luggage.objects[i].pose.position.y,2)) < thresDetect){
                xLug[idxtmp] = egoPose.position.x + luggage.objects[i].pose.position.x*cos(yaw)-luggage.objects[i].pose.position.y*sin(yaw);
                yLug[idxtmp] = egoPose.position.y + luggage.objects[i].pose.position.x*sin(yaw)+luggage.objects[i].pose.position.y*cos(yaw);
                vxLug[idxtmp] = luggage.objects[i].velocity.linear.x*cos(yaw) - luggage.objects[i].velocity.linear.y*sin(yaw);
                velLug[idxtmp] = luggage.objects[i].velocity.linear.x;
                vyLug[idxtmp] = luggage.objects[i].velocity.linear.x*sin(yaw) + luggage.objects[i].velocity.linear.y*cos(yaw);
                // ROS_INFO("i:%d,xLug: %f,yLug: %f,vxLug: %f,vyLug: %f",i,xLug[i],yLug[i],vxLug[i],vxLug[i]);
                idxtmp++;
            }
        }
        idxtmp = 0;
        for(int i = 0; i < rawsbn; i++){
            if(sqrt(pow(sb.objects[i].pose.position.x,2)+pow(sb.objects[i].pose.position.y,2)) < thresDetect){
                xSB[idxtmp] = egoPose.position.x + sb.objects[i].pose.position.x*cos(yaw)-sb.objects[i].pose.position.y*sin(yaw);
                ySB[idxtmp] = egoPose.position.y + sb.objects[i].pose.position.x*sin(yaw)+sb.objects[i].pose.position.y*cos(yaw);
                vxSB[idxtmp] = sb.objects[i].velocity.linear.x*cos(yaw) - sb.objects[i].velocity.linear.y*sin(yaw);
                vySB[idxtmp] = sb.objects[i].velocity.linear.x*sin(yaw) + sb.objects[i].velocity.linear.y*cos(yaw);
                // ROS_INFO("i:%d,xSB: %f,ySB: %f",i,xSB[i],ySB[i]);
                idxtmp++;
            }
        }
        if(mobObj.objects.size()>0){
            float vxMob = mobObj.objects[0].velocity.linear.x*cos(yaw) - mobObj.objects[0].velocity.linear.y*sin(yaw);
            float vyMob = mobObj.objects[0].velocity.linear.x*sin(yaw) + mobObj.objects[0].velocity.linear.y*cos(yaw);
            velMob = sqrt(pow(vxMob,2)+pow(vyMob,2));
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
        // ROS_INFO("egopose s: %f, l: %f, dsEgo: %f", sEgo, lEgo, dsEgo);


        // calculate Frenet coordinate of objects
        psl = slObj;
        float minFront = dFront;
        for(int i = 0; i < on; i++){
            psarr = sarr0;
            this->calculateFrenet(n0, psarr, xObj[i], yObj[i], vxObj[i], vyObj[i], psl, globalLaneArray.lanes[0]);
            sObj[i] = slObj[0];
            lObj[i] = slObj[1];
            dsObj[i] = vxObj[i];
            dlObj[i] = 0;
            bool isCar = false;
            if(detectedObjects.objects[i].label == "car") isCar = true;
            // ROS_INFO("i:%d,sObj: %f,lObj: %f,vx: %f,vy: %f, label: %d",i,sObj[i],lObj[i],dsObj[i],dlObj[i],isCar);
            if(abs(lObj[i]) <= wLane/2){
                // front vehicle
                if(sObj[i]-sEgo < minFront && sObj[i]-sEgo > 0){
                    front_id = i;
                    minFront = sObj[i]-sEgo;
                    frontCar = true;
                }
            }
        }
        float unknownFront = dLuggage;
        int lug_id = -1;
        for(int i = 0; i < lugn; i++){
            psarr = sarr0;
            this->calculateFrenet(n0, psarr, xLug[i], yLug[i], vxLug[i], vyLug[i], psl, globalLaneArray.lanes[0]);
            sLug[i] = slObj[0];
            lLug[i] = slObj[1];
            dsLug[i] = vxLug[i];
            dlLug[i] = 0;
            // ROS_INFO("i:%d,sLug: %f,lLug: %f,vx: %f,vy: %f",i,sLug[i],lLug[i],dsLug[i],dlLug[i]);
            if(abs(lLug[i]) <= wLane/2){
                // front luggage
                if(sLug[i]-sEgo < unknownFront && sLug[i]-sEgo > 0){
                    lug_id = i;
                    unknownFront = sLug[i]-sEgo;
                    luggageDrop = true;
                    luggagePrev = true;
                }
            }
        }
        float minSB = thresSB;
        for(int i = 0; i < sbn; i++){
            // calculate distance to speed bump
            psarr = sarr0;
            
            this->calculateFrenet(n0, psarr, xSB[i], ySB[i], vxSB[i], vySB[i], psl, globalLaneArray.lanes[0]);
            sSB[i] = slObj[0];
            lSB[i] = slObj[1];
            double distSB = sSB[i]-sEgo;
            ROS_INFO("speedbumpdist: %f, sbn : %d",distSB, sbn);

            if(distSB < minSB && distSB > 0 && abs(lSB[i])<7.5){
                minSB = distSB;
                speedBumpSign = true;
                countSB = 0;
                sbPrev = true;
                speedBumpPass = false;
                xSBsign = xSB[i];
                ySBsign = ySB[i];
            }
        }
        
        if(sbPrev){
            if(speedBumpSign == false){
                if(countSB < nStore){
                    speedBumpSign = true;
                    speedBumpPass = false;
                    countSB++;
                }
                else{
                    sbPrev = false;
                    countSB = 0;
                }
            }
            else{
                countSB = 0;
            }
        }
        if(xSBsign != -1){
            this->calculateFrenet(n0, psarr, xSBsign, ySBsign, 0, 0, psl, globalLaneArray.lanes[0]);
            if(slObj[0]-sEgo > 0){
                speedBumpSign = true;
                speedBumpPass = false;
                ROS_INFO("speedbump: %f",slObj[0]-sEgo);

            }
            else{
                speedBumpSign = false;
                speedBumpPass = true;
                xSBsign = -1;
                ySBsign = -1;
            }
        }
        else{
            speedBumpSign = false;
            speedBumpPass = true;
        }

        
        // calculate safe distance and check if it is stationary car
        if(frontCar || luggageDrop){
            countFront = 0;
            frontPrev = true;
            if(frontCar && luggageDrop){
                front_dist = std::min(minFront, unknownFront);
                if(front_dist == minFront){
                    front_vel = velObj[front_id];
                    if(countFrontCarStop > runRate*thresFrontCarStop*0.5 && countFrontCarStop < runRate*thresFrontCarStop*0.7){
                        xObstacle = xObj[front_id];
                        yObstacle = yObj[front_id];
                    }
                }
                else{
                    front_vel = velLug[lug_id];
                    if(countFrontCarStop > runRate*thresFrontCarStop*0.5 && countFrontCarStop < runRate*thresFrontCarStop*0.7){
                        xObstacle = xLug[lug_id];
                        yObstacle = yLug[lug_id];
                    }
                }
            }
            else if(frontCar){
                front_dist = minFront;
                front_vel = velObj[front_id];
                if(countFrontCarStop > runRate*thresFrontCarStop*0.5 && countFrontCarStop < runRate*thresFrontCarStop*0.7){
                    xObstacle = xObj[front_id];
                    yObstacle = yObj[front_id];
                }
            }
            else{
                front_dist = unknownFront;
                front_vel = velLug[lug_id];
                if(countFrontCarStop > runRate*thresFrontCarStop*0.5 && countFrontCarStop < runRate*thresFrontCarStop*0.7){
                    xObstacle = xLug[lug_id];
                    yObstacle = yLug[lug_id];
                }
            }
            if(front_dist == minFront){
                if (sqrt(pow(vxObj[front_id],2)+pow(vyObj[front_id],2)) < thresStop){
                    stationaryFrontCar = true;
                    stationaryPrev = true;
                }
            }
            else{
                if (sqrt(pow(vxLug[lug_id],2)+pow(vyLug[lug_id],2)) < thresStop){
                    stationaryFrontCar = true;
                    stationaryPrev = true;
                }
            }
            frontCar = true;
            frontPrev = true;
        }
        if(mobObj.objects.size()>0){
            float mob_dist = sqrt(pow(mobObj.objects[0].pose.position.x-egoPose.position.x,2)+pow(mobObj.objects[0].pose.position.y-egoPose.position.y,2));
            if(mob_dist < dFront){
                frontCar = true;
                frontPrev = true;
                front_dist = mob_dist;
                if (velMob != -1 && velMob < thresStop){
                    stationaryFrontCar = true;
                    stationaryPrev = true;
                }
                ROS_INFO("mobileye frontcar!!");
            } 
        }
        
        // ROS_INFO("xObstacle %f, yObstacle %f"xObstacle, yObstacle);
        // if(frontCar && luggageDrop){
        //     ros::Duration tt_ = ros::Time::now() - obj_time;
        //     obj_time = ros::Time::now();

        //     double object_x = luggage.objects[lug_id].pose.position.x;
        //     double object_y = luggage.objects[lug_id].pose.position.y;
        //     double dist_ = sqrt(pow((object_x - prev_object_x),2)+pow((object_y - prev_object_y),2));
        //     front_vel = dist_/(tt_.toSec()+1e-9);
        //     if(abs(front_vel) < 0.5){
        //         front_vel = 0.0;
        //     }
        //     prev_object_x = object_x;
        //     prev_object_y = object_y;
        // }
        
        // store front car for nStore time steps


        if(frontCar == false && frontPrev){
            countFront++;
            if(countFront < nStore){
                front_id = 1000;
                frontCar = true;
            }
            else{
                frontPrev = false;
                countFront = 0;
            }
        }
        else{
            countFront = 0;
        }
        if(stationaryFrontCar == false && stationaryPrev){
            countStationary++;
            if(countStationary < nStore){
                stationaryFrontCar = true;
            }
            else{
                countStationary = 0;
                stationaryPrev = false;
            }

        }
        else{
            countStationary = 0;
        }
        if(luggageDrop == false && luggagePrev){
            countLuggage++;
            if(countLuggage < nStore){
                luggageDrop = true;
            }
            else{
                countLuggage = 0;
                luggagePrev = false;
            }
        }
        else{
            countLuggage = 0;
        }
        for(int i = 0; i < globalLaneArray.lanes.size(); i++){
            if(globalLaneArray.lanes[i].lane_id == 1000){
                luggageDrop = false;
            }
        }
        

        // ROS_INFO("front car : %d , stationary : %d", frontCar, stationaryFrontCar);

        // compute dist to crosswalk
        float distToCW = -1;
        for(int i = idEgo; i < n0; i++){
            if(globalLaneArray.lanes[0].waypoints[i].Crosswalk == true){
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
        if(globalLaneArray.lanes[0].waypoints[idEgo].Crosswalk == true){
            inCW = true;
        }
        // ROS_INFO("distToCW: %f,inCW: %d, crosswalkPass: %d", distToCW, inCW, crosswalkPass);

        int firstIdJunc = -1;
        int lastIdJunc = -1;
        bool isJunc = false;
        float dJunc = -1, lenJunc = -1;
        float StrX, StrY, JuncX, JuncY;
        float lenStr = 0;
        float hGap = 0;
        for(int i = idEgo; i < n0; i++){    
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
            StrX = globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.x-globalLaneArray.lanes[0].waypoints[idEgo].pose.pose.position.x;
            StrY = globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.y-globalLaneArray.lanes[0].waypoints[idEgo].pose.pose.position.y;
            dJunc = sqrt(pow(StrX,2)+pow(StrY,2));
            // ROS_INFO("StrX: %f, StrY: %f", StrX, StrY);
        }
        if(isJunc && dJunc < thresTurn && dJunc > 0){
            JuncX = globalLaneArray.lanes[0].waypoints[lastIdJunc].pose.pose.position.x-globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.x;
            JuncY = globalLaneArray.lanes[0].waypoints[lastIdJunc].pose.pose.position.y-globalLaneArray.lanes[0].waypoints[firstIdJunc].pose.pose.position.y;
            lenJunc = sqrt(pow(JuncX,2)+pow(JuncY,2));
            
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
            if(hGap > 0.3){
                leftTurn = true;
                rightTurn = false;
            }
            else if(hGap < -0.3){
                leftTurn = false;
                rightTurn = true;
            }
            else if(globalLaneArray.lanes[0].waypoints[idEgo].Junction == false){
                leftTurn = false;
                rightTurn = false;
            }
            ROS_INFO("isJunc: %d, dJunc: %f", isJunc, dJunc);
            ROS_INFO("first: %d, last: %d", firstIdJunc, lastIdJunc);
            ROS_INFO("hGap: %f, lflag: %d, rflag: %d", hGap, leftTurn, rightTurn);
        }
        else if(!isJunc || dJunc != 0){
            leftTurn = false;
            rightTurn = false;
        }

        if(leftTurn || rightTurn) turn = true;

        if(currentBehavior == BehaviorState::LaneChange && isJunc && dJunc < thresMinTurn){
            laneChangeDone = true;
            ROS_INFO("fix lane change check");
        }
        // check if Lane Change is essential
        if(globalLaneArray.lanes[0].lane_change_flag == true){
            float targetX = target_msg.node_wpts[targetID].x;
            float targetY = target_msg.node_wpts[targetID].y;
            psl = slObj;
            this->calculateFrenet(n0, psarr, targetX, targetY, 0, 0, psl, globalLaneArray.lanes[0]);
            if(abs(slObj[1])>wLane/2){
                essentialLaneChange = true;
                if(prevLaneID == -1){
                    laneChangeDone = false;
                    prevLaneID = globalLaneArray.lanes[0].lane_id;
                }
            }
        }
        if(essentialLaneChange == true) luggageDrop = false;
        if(turn){
            if(unknownFront > thresTurnStop){
                luggageDrop = false;
            }
        }
        else{
            if(unknownFront > thresFrontStop){
                luggageDrop = false;
            }
        }
        
        // ROS_INFO("prev: %d, lane_id: %d", prevLaneID, globalLaneArray.lanes[0].lane_id);
        // determine doneLC
        ROS_INFO("local return: %d", localRet);
        if(prevLaneID == -2 && abs(lEgo) < thresLC){
            laneChangeDone = true;
            prevLaneID = -1;
            localRet = false;
        }
        if(prevLaneID != -1 && prevLaneID != -2 && prevLaneID != globalLaneArray.lanes[0].lane_id && abs(lEgo) < thresLC){
            laneChangeDone = true;
            prevLaneID = -1;
        }
        // ROS_INFO("lEgo : %f", lEgo);
        if(abs(lEgo)>wLane*0.7){
            frontCar = false;
            frontPrev = false;
        }
        if(abs(lEgo)>wLane*0.7) checkObstacle = true;
        // if(!checkObstacle && abs(lEgo)>wLane*0.6){
        //     bool isObstacle = false;
        //     for(int i = 0; i < on; i++){
        //         if(abs(lObj[i]) <= wLane/2){
        //             if(abs(sObj[i]-sEgo) < thresObs){
        //                 isObstacle = true;
        //             }
        //         }
        //     }
        //     for(int i = 0; i < lugn; i++){
        //         if(abs(lLug[i]) <= wLane/2){
        //             if(abs(sLug[i]-sEgo) < thresObs){
        //                 isObstacle = true;
        //             }
        //         }
        //     }
        //     if(!isObstacle){
        //         countObs++;
        //         if(countObs>nStore){
        //             checkObstacle = true;
        //             countObs = 0;
        //         }
        //     }
        //     else{
        //         countObs = 0;
        //     }
        //     ROS_INFO("check obstacle : %d, count : %d", checkObstacle, countObs);
        // }


        // get traffic light state correspond to current lane and ego 
        // need to add signalID correctly to the map 
        // int signal_id = -1;
        int signal_id = globalLaneArray.lanes[0].signal_id;
        int eventState = -1;
        int timing_min_End_Time = -1;
        // if(signal_id == 1 && leftTurn){
        //     eventState = junc1Signal.States[1].eventState;
        //     timing_min_End_Time = junc1Signal.States[1].timing_min_End_Time;
        // }
        if(signal_id == 1){
            eventState = junc1Signal.States[0].eventState;
            timing_min_End_Time = junc1Signal.States[0].timing_min_End_Time;
        }
        // else if(signal_id == 2 && leftTurn){
        //     eventState = junc1Signal.States[4].eventState;
        //     timing_min_End_Time = junc1Signal.States[4].timing_min_End_Time;
        // }
        else if(signal_id == 2){
            eventState = junc1Signal.States[3].eventState;
            timing_min_End_Time = junc1Signal.States[3].timing_min_End_Time;
        }
        // else if(signal_id == 3 && leftTurn){
        //     eventState = junc1Signal.States[7].eventState;
        //     timing_min_End_Time = junc1Signal.States[7].timing_min_End_Time;
        // }
        else if(signal_id == 3){
            eventState = junc1Signal.States[6].eventState;
            timing_min_End_Time = junc1Signal.States[6].timing_min_End_Time;
        }
        // else if(signal_id == 4 && leftTurn){
        //     eventState = junc1Signal.States[10].eventState;
        //     timing_min_End_Time = junc1Signal.States[10].timing_min_End_Time;
        // }
        else if(signal_id == 4){
            eventState = junc1Signal.States[9].eventState;
            timing_min_End_Time = junc1Signal.States[9].timing_min_End_Time;
        }
        // else if(signal_id == 5 && leftTurn){
        //     eventState = junc2Signal.States[1].eventState;
        //     timing_min_End_Time = junc2Signal.States[1].timing_min_End_Time;
        // }
        else if(signal_id == 5){
            eventState = junc2Signal.States[0].eventState;
            timing_min_End_Time = junc2Signal.States[0].timing_min_End_Time;
        }
        // else if(signal_id == 6 && leftTurn){
        //     eventState = junc2Signal.States[4].eventState;

        //     timing_min_End_Time = junc2Signal.States[4].timing_min_End_Time;
        // }
        else if(signal_id == 6){
            eventState = junc2Signal.States[3].eventState;
            timing_min_End_Time = junc2Signal.States[3].timing_min_End_Time;
        }
        // else if(signal_id == 7 && leftTurn){
        //     eventState = junc2Signal.States[7].eventState;
        //     timing_min_End_Time = junc2Signal.States[7].timing_min_End_Time;
        // }
        else if(signal_id == 7){
            eventState = junc2Signal.States[6].eventState;
            timing_min_End_Time = junc2Signal.States[6].timing_min_End_Time;

        }
        // else if(signal_id == 8 && leftTurn){
        //     eventState = junc2Signal.States[10].eventState;
        //     timing_min_End_Time = junc2Signal.States[10].timing_min_End_Time;
        // }
        else if(signal_id == 8){
            eventState = junc2Signal.States[9].eventState;
            timing_min_End_Time = junc2Signal.States[9].timing_min_End_Time;
        }
        // else if(signal_id == 9 && leftTurn){
        //     eventState = junc3Signal.States[0].eventState;
        //     timing_min_End_Time = junc3Signal.States[0].timing_min_End_Time;
        // }
        else if(signal_id == 10){
            eventState = junc3Signal.States[1].eventState;
            timing_min_End_Time = junc3Signal.States[1].timing_min_End_Time;
        }
        // else if(signal_id == 11 && leftTurn){
        //     eventState = junc3Signal.States[4].eventState;
        //     timing_min_End_Time = junc3Signal.States[4].timing_min_End_Time;
        // }
        else if(signal_id == 11){
            eventState = junc3Signal.States[3].eventState;
            timing_min_End_Time = junc3Signal.States[3].timing_min_End_Time;
        }
        if(essentialLaneChange == false && turn == false && signal_id != -1 && dJunc < thresTL && dJunc >= 0){
            // red light
            if(eventState == 3){
                trafficLightStop = true;
            }
            // green light
            else if(eventState == 5 || eventState == 6){
                if(dJunc == 0){
                    trafficLightStop = false;
                }
                else if(timing_min_End_Time < thresTLtime && dJunc >= 20){
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
        float pedDist = 20;
        if(turn){
            pedDist = 20;
        }
        else{
            pedDist = 30;
        }
        if(pedestrianOnCrosswalk){
            bool distCheck = false;
            for(int i = 0; i < pedObj.objects.size(); i++){
                if(sqrt(pow(pedObj.objects[i].pose.position.x,2) + pow(pedObj.objects[i].pose.position.y,2))< pedDist) distCheck = true;
            }
            if(!distCheck) pedestrianOnCrosswalk = false;
        }
        if(pedestrianOnCrosswalk && frontCar && lug_id != -1){
            frontCar = false;
            frontPrev = false;
            luggageDrop = false;                    
        }

        if(trafficLightStop){
            speedBumpSign = false;
        }
        
        if(approachToCrosswalk == false && inCW == false) crosswalkPass = true;
        if(turn || trafficLightStop) approachToCrosswalk = false;
        // startArrivalSuccess = startArrivalCheck; //for test
        // ROS_INFO("turn: %d, apptoCW: %d", turn, approachToCrosswalk);

        

        if(currentMission==MissionState::DriveToGoalPos){
            startArrivalSuccess = true;
        }
        if(startArrivalSuccess){
            approachToStartPos = false;
        }


        // if(countInit2 > runRate*thresInit2){
        //     missionStart = true;
        //     ROS_INFO("Init2 Time Out!!!");
        // }
        if(countStopAtStartPos > runRate*thresStopAtStartPos){
            startArrivalCheck = true;
            ROS_INFO("StopAtStartPos Time Out!!!");
        }
        // if(countStartArrival > runRate*thresStartArrival){
        //     startArrivalSuccess = true;
        //     ROS_INFO("StartArrival Time Out!!!");
        // }
        // if(countPedestrian >= runRate*thresPedestrian){
        //     pedestrianOnCrosswalk = false;
        //     countPedestrian++;
        //     if(countPedestrian > runRate*(thresPedestrian+5)) countPedestrian = 0;
        //     ROS_INFO("Pedestrian Time Out!!!");
        // }
        // if(countFrontLuggage >= runRate*thresFrontLuggage){
        //     luggageDrop = false;
        //     countFrontLuggage++;
        //     if(countFrontLuggage > runRate*(thresFrontLuggage+5)) countFrontLuggage = 0;
        //     ROS_INFO("FrontLuggage Time Out!!!");
        // }
        if(countFrontCarStop > runRate*thresFrontCarStop){
            for(int i = 0; i < globalLaneArray.lanes.size(); i++){
                if(globalLaneArray.lanes[i].lane_id == 1000){
                    brokenFrontCar = true;
                    checkObstacle = false;
                    countObs = 0;
                    ROS_INFO("Broken Front Car!!!");
                }
            }
            
        }
        // if(countSpeedBump >= runRate*thresSpeedBump){
        //     speedBumpPass = true;
        //     speedBumpSign = false;
        //     countSpeedBump++;
        //     if(countSpeedBump > runRate*(thresSpeedBump+5)) countSpeedBump = 0;
        //     ROS_INFO("SpeedBump Time Out!!!");
        // }
        if(countStopAtGoalPos > runRate*thresStopAtGoalPos){
            goalArrivalCheck = true;
            ROS_INFO("StopAtGoalPos Time Out!!!");
        }
        break;
    }




    // ROS_INFO("countInit2: %d",countInit2);
    // ROS_INFO("countStopAtStartPos: %d",countStopAtStartPos);
    // ROS_INFO("countStartArrival: %d",countStartArrival);
    // ROS_INFO("countPedestrian: %d",countPedestrian);
    // ROS_INFO("countFrontLuggage: %d",countFrontLuggage);
    // ROS_INFO("countFrontCarStop: %d",countFrontCarStop);
    // ROS_INFO("countSpeedBump: %d",countSpeedBump);
    // ROS_INFO("countStopAtGoalPos: %d",countStopAtGoalPos);

    //update behavior factor
    behaviorFactor.front_vel = front_vel; // done
    behaviorFactor.front_dist = front_dist;
    behaviorFactor.xObstacle = xObstacle;
    behaviorFactor.yObstacle = yObstacle;
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
    if(currentMission == MissionState::EmergencyStop){
        if(currentBehavior != BehaviorState::EmergencyStop2){
            ePrevBehavior = currentBehavior;
            currentBehavior = BehaviorState::EmergencyStop2;
        }
    }
    else if(currentBehavior == BehaviorState::EmergencyStop2){
        currentBehavior = ePrevBehavior;
    }
    if(NormalDrive){
        ROS_INFO("front_dist %f thresFrontStop %f stationaryFrontCar %d",front_dist , thresFrontStop,stationaryFrontCar);
        if(luggageDrop){
            currentBehavior = BehaviorState::FrontLuggage;
        }
        else if(((!turn && front_dist < thresFrontStop) || (turn && front_dist < thresTurnStop)) && stationaryFrontCar && prevBehavior != BehaviorState::TrafficLightStop){
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
        else if(localRet){
            laneChangeDone = false;
            prevLaneID = -2;
            currentBehavior = BehaviorState::LaneChange;
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
                else if(firstCWcheck && currentBehavior == BehaviorState::Forward && approachToCrosswalk){
                    TLstopCheck = false;
                    firstCWcheck = false;
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
                else{
                    goToTurn = true;
                }
            }
            else if(prevBehavior == BehaviorState::TrafficLightStop){
                if(turn && (stopCheck || trafficLightStop == false)){
                    goToTurn = true;
                }
                else if(turn == false && trafficLightStop == false){
                    goToLaneFollowing = true;
                }
            }
            else if(prevBehavior == BehaviorState::Crosswalk){
                if(pedestrianOnCrosswalk){
                    currentBehavior = BehaviorState::Pedestrian;
                }
                else if(crosswalkPass){
                    goToLaneFollowing = true;
                }
                else if (turn){
                    goToTurn = true;
                }
            }


        }
    }
    else{
        if(prevBehavior == BehaviorState::Init2){
            countInit2++;
            if(missionStart){
                countInit2 = 0;
                goToLaneFollowing = true;
            }
        }
        else if(prevBehavior == BehaviorState::StopAtStartPos){
            countStopAtStartPos++;
            if(startArrivalCheck){
                countStopAtStartPos = 0;
                currentBehavior = BehaviorState::StartArrival;
            }
        }
        else if(prevBehavior == BehaviorState::StartArrival){
            countStartArrival++;
            if(startArrivalSuccess){
                countStartArrival = 0;
                goToNormalDrive = true;
            }
        }
        else if(prevBehavior == BehaviorState::StopAtGoalPos){
            countStopAtGoalPos++;
            if(goalArrivalCheck){
                countStopAtGoalPos = 0;
                currentBehavior = BehaviorState::GoalArrival;
            }
        }
        else if(prevBehavior == BehaviorState::Pedestrian){
            countPedestrian++;
            if(pedestrianOnCrosswalk == false && turn){
                if(countPedestrian < runRate*thresPedestrian) countPedestrian = 0;
                if(trafficLightStop == true){
                    currentBehavior = BehaviorState::TrafficLightStop;
                }
                else{
                    goToTurn = true;
                }
            }
            else if(pedestrianOnCrosswalk == false){
                if(countPedestrian < runRate*thresPedestrian) countPedestrian = 0;
                currentBehavior = BehaviorState::Crosswalk;
            }
        }
        else if(prevBehavior == BehaviorState::FrontLuggage){
            countFrontLuggage++;
            if(luggageDrop == false || stationaryFrontCar == false){
                if(countFrontLuggage < runRate*thresFrontLuggage) countFrontLuggage = 0;
                goToNormalDrive = true;
            }
        }
        else if(prevBehavior == BehaviorState::FrontCarStop){
            countFrontCarStop++;
            if(stationaryFrontCar == false){
                countFrontCarStop = 0;
                goToNormalDrive = true;
            }
            else if(brokenFrontCar){
                countFrontCarStop = 0;
                currentBehavior = BehaviorState::ObstacleLaneChange;
            }
            else if(luggageDrop){
                countFrontCarStop = 0;
                currentBehavior = BehaviorState::FrontLuggage;
            }
        }
        else if(prevBehavior == BehaviorState::ObstacleLaneChange){
            if(checkObstacle){
                brokenFrontCar = false;
                goToNormalDrive = true;
            }
            else if(approachToStartPos){
                currentBehavior = BehaviorState::StopAtStartPos;
            }
            else if(approachToGoalPos){
                currentBehavior = BehaviorState::StopAtGoalPos;
            }
        }
        else if(prevBehavior == BehaviorState::LaneChange){
            if(laneChangeDone){
                goToNormalDrive = true;
            }
            else if(approachToStartPos){
                currentBehavior = BehaviorState::StopAtStartPos;
            }
            else if(approachToGoalPos){
                currentBehavior = BehaviorState::StopAtGoalPos;
            }
            else if(stopCheck && stationaryFrontCar){
                currentBehavior = BehaviorState::FrontCarStop;
            }
        }
        else if(prevBehavior == BehaviorState::SpeedBump){
            countSpeedBump++;
            if(speedBumpPass){
                if(countSpeedBump < runRate*thresSpeedBump) countSpeedBump = 0;
                goToNormalDrive = true;
            }
            else if(approachToStartPos){
                currentBehavior = BehaviorState::StopAtStartPos;
            }
            else if(approachToGoalPos){
                currentBehavior = BehaviorState::StopAtGoalPos;
            }
            else if(luggageDrop){
            currentBehavior = BehaviorState::FrontLuggage;
            }
            else if(stopCheck && stationaryFrontCar){
                currentBehavior = BehaviorState::FrontCarStop;
            }
            else if(trafficLightStop){
                currentBehavior = BehaviorState::TrafficLightStop;
            }
        }
    }
    if(goToNormalDrive){
        if(turn){
            goToTurn = true;
        }
        else if(firstCWcheck && currentBehavior == BehaviorState::Forward && approachToCrosswalk){
            TLstopCheck = false;
            firstCWcheck = false;
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
    if(currentBehavior == BehaviorState::TrafficLightStop){
        TLstopCheck = true;
    }
    if(TLstopCheck && inCW){
        firstCWcheck = true;
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
    if(currentBehavior == BehaviorState::TrafficLightStop || currentBehavior == BehaviorState::Crosswalk){
        NormalDrive = true;
    }

    //light cmd
    float tmpx0 =0;
    float tmpy0 =0;
    float tmpx1 =0;
    float tmpy1 =0; 
    if(currentBehavior == BehaviorState::LaneChange && globalLaneArray.lanes.size() >= 2){
        if(localRet == false){
            if(prevBehavior!=BehaviorState::LaneChange){
                tmpx0 = globalLaneArray.lanes[0].waypoints[1].pose.pose.position.x - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
                tmpy0 = globalLaneArray.lanes[0].waypoints[1].pose.pose.position.y - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
                tmpx1 = globalLaneArray.lanes[1].waypoints[0].pose.pose.position.x - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
                tmpy1 = globalLaneArray.lanes[1].waypoints[0].pose.pose.position.y - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
                if(tmpx0*tmpy1-tmpx1*tmpy0 > 0) lightPrev = -1;
                else lightPrev = 1;
            }
            light_msg.data = lightPrev;
        }
        else{
            if(prevBehavior!=BehaviorState::LaneChange){
                tmpx0 = globalLaneArray.lanes[0].waypoints[1].pose.pose.position.x - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
                tmpy0 = globalLaneArray.lanes[0].waypoints[1].pose.pose.position.y - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
                tmpx1 = globalLaneArray.lanes[1].waypoints[0].pose.pose.position.x - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
                tmpy1 = globalLaneArray.lanes[1].waypoints[0].pose.pose.position.y - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
                if(tmpx0*tmpy1-tmpx1*tmpy0 > 0) lightPrev = 1;
                else lightPrev = -1;
            }
            light_msg.data = lightPrev;
        }
    }
    else if(currentBehavior == BehaviorState::ObstacleLaneChange && globalLaneArray.lanes.size() >= 2){
        if(prevBehavior!=BehaviorState::ObstacleLaneChange){
            tmpx0 = globalLaneArray.lanes[0].waypoints[1].pose.pose.position.x - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
            tmpy0 = globalLaneArray.lanes[0].waypoints[1].pose.pose.position.y - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
            tmpx1 = globalLaneArray.lanes[1].waypoints[0].pose.pose.position.x - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.x;
            tmpy1 = globalLaneArray.lanes[1].waypoints[0].pose.pose.position.y - globalLaneArray.lanes[0].waypoints[0].pose.pose.position.y;
            if(tmpx0*tmpy1-tmpx1*tmpy0 > 0) lightPrev = -1;
            else lightPrev = 1;
        }
        light_msg.data = lightPrev;
    }
    else if(currentBehavior == BehaviorState::StopAtStartPos || currentBehavior == BehaviorState::StartArrival || currentBehavior == BehaviorState::StopAtGoalPos || currentBehavior == BehaviorState::GoalArrival) light_msg.data = 2;
    else if(currentBehavior == BehaviorState::LeftTurn) light_msg.data = -1;
    else if(currentBehavior == BehaviorState::RightTurn) light_msg.data = 1;
    else if(!NormalDrive && leftTurn) light_msg.data = -1;
    else if(!NormalDrive && rightTurn) light_msg.data = 1;
    else light_msg.data = 0;
    std::cout<< stateToStringBehavior(currentBehavior) <<std::endl;
    light_pub.publish(light_msg);
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
    target_msg = msg;
    if(target_msg.node_wpts.size()>1){
        start_idx = msg.start.x;
        startX = msg.node_wpts[(int)start_idx].x;
        startY = msg.node_wpts[(int)start_idx].y;
        startID = msg.start.z;
        goal_idx =  msg.end.x;
        goalX = msg.node_wpts[(int)goal_idx].x;
        goalY = msg.node_wpts[(int)goal_idx].y;
        goalID = msg.end.z;
        targetID = msg.target_idx;
    }
}

void BehaviorPlanner::v2xSPATCallback(const v2x_msgs::SPAT& msg){
    //traffic_signal
    if(msg.id == 1){
        getSPAT1 = true;
        junc1Signal = msg;
    }
    else if(msg.id == 2){
        getSPAT2 = true;
        junc2Signal = msg;
    }
    else if(msg.id == 3){
        getSPAT3 = true;
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
void BehaviorPlanner::localRetCallback(const std_msgs::Bool::ConstPtr& msg){
    if(!getRet){
        getRet = true;
        localRet = msg->data;
    }
    else{
        localRet = false;
    }
    
}
void BehaviorPlanner::pedObjectCallback(const autoware_msgs::DetectedObjectArray& msg)
{
    getPedObj = true;
    pedObj=msg;
}  
void BehaviorPlanner::objectCallback(const autoware_msgs::DetectedObjectArray& msg)
{
    getMob = true;
    mobObj=msg;
}  
int main (int argc, char** argv)
{

    ros::init(argc, argv, "behavior_planner");

    BehaviorPlanner behavior_node;

    ros::spin();
    
}