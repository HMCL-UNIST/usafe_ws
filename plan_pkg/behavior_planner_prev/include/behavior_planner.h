// #include "planner/planner_common.h"

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

#include <std_msgs/Int16.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/MissionWaypoint.h>
#include <hmcl_msgs/BehaviorFactor.h>
#include <hmcl_msgs/TransitionCondition.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <v2x_msgs/SPAT.h>

#define PI 3.14159265358979323846264338
typedef enum{Init, ChooseDifficulty, MissionRequest, DriveToStartPos, StartArrivalRequest, DriveToGoalPos,
            GoalArrivalRequest, MissionComplete} MissionState;
typedef enum{Init2, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival} BehaviorState;



class BehaviorPlanner
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber pose_sub, vel_sub, objs_sub, start_goal_sub, v2x_spat_sub, route_sub, mission_sub;
        // ros::Subscriber pose_sub, vel_sub, objs_sub, route_sub, mission_sub;
        ros::Publisher behavior_pub;
        // ros::Timer behavior_timer;
        float wLane, lenEgo, frontlenEgo, minFront, thresLC, thresStop, thresCW, thresDistSG, successDistSG;
        geometry_msgs::Pose egoPose;
        double egoSpeed;
        autoware_msgs::DetectedObjectArray detectedObjects;
        double startX, startY, goalX, goalY;
        //startpos info 
        //goalpos
        //traffic_signal
        hmcl_msgs::LaneArray globalLaneArray;
        MissionState currentMission;
        bool missionStart, approachToStartPos, startArrivalCheck, startArrivalSuccess, frontCar, stationaryFrontCar, approachToCrosswalk, crosswalkPass;
        bool pedestrianOnCrosswalk, leftTurn, rightTurn, turn, trafficLightStop, stopCheck, luggageDrop, brokenFrontCar, laneChangeDone;
        bool esssentialLaneChange, speedBumpSign, speedBumpPass, approachToGoalPos;
        short front_id, prevLaneID;
        int nStoreFront, countFront;
        bool stop_line_stop;
        bool getGlobal, getPose, getSpeed, getObject, getSGpos, getSPAT, getMission;
        bool inCW, inCWprev, frontPrev;
        hmcl_msgs::BehaviorFactor behaviorFactor;

    public:
        BehaviorPlanner(); 
        void callbackthread();
        ~BehaviorPlanner();
        void calculateLon(int n, float* psarr, hmcl_msgs::Lane &lane);
        void calculateFrenet(int n, float* psarr, float px, float py, float vx, float vy, float* psl, hmcl_msgs::Lane &lane);
        void calculateSafeDistance(float vFront, float vRear, float &dSafe);
        void updateFactors();
        // void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);
        void odometryCallback(const nav_msgs::Odometry& msg);
        void vehicleStatusCallback(const hmcl_msgs::VehicleStatusConstPtr &msg);
        // void twistCallback(const geometry_msgs::TwistStampedConstPtr& msg);
        void objsCallback(const autoware_msgs::DetectedObjectArray& msg);
        void v2xStartGoalCallback(const hmcl_msgs::MissionWaypoint& msg);
        void v2xSPATCallback(const v2x_msgs::SPAT& msg);
        void routeCallback(const hmcl_msgs::LaneArray &msg);
        void missionCallback(const std_msgs::Int16::ConstPtr& msg);
};