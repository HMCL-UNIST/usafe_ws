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

    nh_.param<float>("minBrake", minBrake, 2);
    nh_.param<float>("maxBrake", maxBrake, 5);
    nh_.param<float>("maxAccel", maxAccel, 3);
    nh_.param<float>("rho", rho, 1);
    nh_.param<float>("wLane", wLane, 3.5);
    nh_.param<float>("lenEgo", lenEgo, 4.180);
    nh_.param<float>("frontlenEgo", frontlenEgo, 4.180/2);// need to check lidar position in real vehicle
    nh_.param<float>("minFront", minFront, 100);
    nh_.param<float>("thresLC", thresLC, 0.5); // need to check if 0.5 is sufficient

    // pose_sub = nh_.subscribe("/current_pose",1,&BehaviorPlanner::poseCallback,this);
    pose_sub = nh_.subscribe("/pose_estimate", 1, &BehaviorPlanner::odometryCallback, this);
    // vel_sub = nh_.subscribe("/current_velocity", 1, &BehaviorPlanner::twistCallback,this);
    vel_sub = nh_.subscribe("/vehicle_status", 1, &BehaviorPlanner::vehicleStatusCallback, this);
    objs_sub = nh_.subscribe("/detection/lidar_tracker/objects",1, &BehaviorPlanner::objsCallback,this);
    //goal_sub = nh_.subscribe("move_base_simple/goal", 1, &BehaviorPlanner::callbackGetGoalPose, this);
    v2x_mission_sub = nh_.subscribe("/Mission1", 1, &BehaviorPlanner::v2xMissionCallback, this);
    v2x_spat_sub = nh_.subscribe("/SPAT",1, &BehaviorPlanner::v2xSPATCallback, this);
    route_sub = nh_.subscribe("/global_traj", 1, &BehaviorPlanner::routeCallback, this);//need to fix topic name
    mission_sub = nh_.subscribe("/mission_state", 1, &BehaviorPlanner::missionCallback, this);
    behavior_pub = nh_.advertise<hmcl_msgs::BehaviorFactor>("/behavior_factor",1,true);
    // behavior_timer = nh_.createTimer(ros::Duration(0.05), &BehaviorPlanner::behavior_handler,this);

    // behavior factors
    missionStart = false;
    approachToStartPos = false;
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
    esssentialLaneChange = false;
    speedBumpSign = false;
    speedBumpPass = false;
    approachToGoalPos = false;

    get_global = false;
    // to velocity planner
    front_id = -1;
    stop_line_stop = false;

    boost::thread callbackhandler(&BehaviorPlanner::callbackthread,this); 
}
void BehaviorPlanner::callbackthread()
{   
    ros::Rate loop_rate(10); // rate  
    while(ros::ok()){
        updateFactors();
        // ROS_INFO("DKJF");
        loop_rate.sleep();
    }
}
BehaviorPlanner::~BehaviorPlanner(){

}

void BehaviorPlanner::calculateLon(int n, float* psarr, hmcl_msgs::Lane &lane){
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
    // ROS_INFO("dp %f, dx %f, sv %f, theta %f, theta2 %f",dp, dx, sv, theta, theta2);
    float s = psarr[idx]+dx*cos(theta);
    if(dx<0.001) s = psarr[idx];
    float ds = sv*cos(theta2);
    if(sv<0.001) ds = 0;
    float l;
    float dl;
    // ROS_INFO("idx %d, x %f, p %f, v %f", idx, x[0],p[0],v[0]);
    if(dx<0.001) l = 0;
    else if(x[0]*p[1]-x[1]*p[0]<0) l = -dx*sin(theta);
    else l = dx*sin(theta);
    if(sv<0.001) dl = 0;
    else if(v[0]*p[1]-v[1]*p[0]<0) dl = -sv*sin(theta2);
    else dl = sv*sin(theta2);
    psl[0] = s;
    psl[1] = l;
    psl[2] = ds;
    psl[3] = dl;
}

void BehaviorPlanner::calculateSafeDistance(float vFront, float vRear, float &dSafe){
    dSafe = vRear*rho + (1/2)*maxAccel*pow(rho,2) + pow((vRear + rho*maxAccel),2)/(2*minBrake) - pow(vFront,2)/(2*maxBrake);
}

void BehaviorPlanner::updateFactors(){
    
    if (!get_global){
        ROS_INFO("No Global");
        return;
    }

    // behavior factors
    // missionStart = true; //for test
    missionStart = false;
    approachToStartPos = false;
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
    esssentialLaneChange = false;
    speedBumpSign = false;
    speedBumpPass = false;
    approachToGoalPos = false;

    // to velocity planner
    front_id = -1;
    stop_line_stop = false;

    int n0 = globalLaneArray.lanes[0].waypoints.size();
    float sarr0[n0];
    float slEgo[4], slObj[4];
    int on = detectedObjects.objects.size();
    float sObj[on], lObj[on], dsObj[on], dlObj[on], laneidObj[on];
    float sEgo, dsEgo, lEgo;
    float* psarr;
    float* psl;
    float gapFront = 100, safeFront = 100;
    float xObj[on],yObj[on],vxObj[on],vyObj[on];

    float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.x + egoPose.orientation.w*egoPose.orientation.z), 1-2*(egoPose.orientation.y*egoPose.orientation.y + egoPose.orientation.z*egoPose.orientation.z));
        // ROS_INFO("egopose x: %f, y: %f",egoPose.position.x, egoPose.position.y);
    for(int i = 0; i < on; i++){
        xObj[i] = egoPose.position.x + detectedObjects.objects[i].pose.position.x*cos(yaw)-detectedObjects.objects[i].pose.position.y*sin(yaw);
        yObj[i] = egoPose.position.y + detectedObjects.objects[i].pose.position.x*sin(yaw)+detectedObjects.objects[i].pose.position.y*cos(yaw);
        vxObj[i] = detectedObjects.objects[i].velocity.linear.x*cos(yaw) - detectedObjects.objects[i].velocity.linear.y*sin(yaw);
        vyObj[i] = detectedObjects.objects[i].velocity.linear.x*sin(yaw) + detectedObjects.objects[i].velocity.linear.y*cos(yaw);
        // ROS_INFO("i:%d,x: %f,y: %f,vx: %f,vy: %f",i,xObj[i],yObj[i],vxObj[i],vxObj[i]);
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

    // determine the necessity of lane change


    // calculate Frenet coordinate of objects
    psl = slObj;
    for(int i = 0; i < on; i++){
        laneidObj[i] = 100;
        psarr = sarr0;
        this->calculateFrenet(n0, psarr, xObj[i], yObj[i], vxObj[i], vyObj[i], psl, globalLaneArray.lanes[0]);
        sObj[i] = slObj[0];
        lObj[i] = slObj[1];
        dsObj[i] = slObj[2];
        dlObj[i] = slObj[3];
        if(abs(lObj[i]) <= wLane/2) laneidObj[i] = 0;
        if(laneidObj[i] == 0){
            // behind vehicle
            if(sObj[i]-sEgo < 0) break;
            // front vehicle
            else{
                if(sObj[i]-sEgo < minFront){
                    front_id = i;
                    minFront = sObj[i]-sEgo;
                    frontCar = true;
                }
            }
        }
    }

    // calculate safe distance
    if(frontCar){
        this->calculateSafeDistance(dsObj[front_id],dsEgo,safeFront);
        gapFront = minFront - detectedObjects.objects[front_id].dimensions.x/2 - frontlenEgo;
    }

    // determine doneLC
    // if(esssentialLaneChange == true){
    //     if(this->needLC == false && abs(lEgo)<thresLC) this->doneLC = true; 
    // }
    ROS_INFO("DKJF");
    //update behavior factor
    behaviorFactor.front_id = front_id;
    behaviorFactor.stop_line_stop = stop_line_stop;
    behaviorFactor.transition_condition.missionStart = missionStart;
    behaviorFactor.transition_condition.approachToStartPos = approachToStartPos;
    behaviorFactor.transition_condition.startArrivalSuccess = startArrivalSuccess;
    behaviorFactor.transition_condition.frontCar = frontCar;
    behaviorFactor.transition_condition.stationaryFrontCar = stationaryFrontCar;
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
    behaviorFactor.transition_condition.esssentialLaneChange = esssentialLaneChange;
    behaviorFactor.transition_condition.speedBumpSign = speedBumpSign;
    behaviorFactor.transition_condition.speedBumpPass = speedBumpPass;
    behaviorFactor.transition_condition.approachToGoalPos = approachToGoalPos;
    behavior_pub.publish(behaviorFactor);
}

// void BehaviorPlanner::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
//     egoPose = msg->pose;
// }

void BehaviorPlanner::odometryCallback(const nav_msgs::Odometry& msg){
    egoPose = msg.pose.pose;
}

void BehaviorPlanner::vehicleStatusCallback(const hmcl_msgs::VehicleStatusConstPtr &msg){
    egoSpeed = msg->wheelspeed.wheel_speed; 
}

void BehaviorPlanner::objsCallback(const autoware_msgs::DetectedObjectArray& msg){
    detectedObjects = msg;
}

void BehaviorPlanner::v2xMissionCallback(const v2x_msgs::Mission1& msg){
    //startpos info 
    //goalpos
    //msg.start_lat;
    //msg.start_lon;
}

void BehaviorPlanner::v2xSPATCallback(const v2x_msgs::SPAT& msg){
    //traffic_signal
    // msg.id;
    // msg.states;
}

void BehaviorPlanner::routeCallback(const hmcl_msgs::LaneArray &msg){
    // if (msg.lanes.size() < 1){
    //     return;
    // }
    ROS_INFO("Behavior_planner");
    get_global = true;
    globalLaneArray = msg;
}

void BehaviorPlanner::missionCallback(const std_msgs::Int16::ConstPtr& msg){
    currentMission = (MissionState)msg->data;
}


int main (int argc, char** argv)
{

    ros::init(argc, argv, "behavior_planner");

    BehaviorPlanner behavior_node;

    ros::spin();
    
}