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
#include <std_msgs/Bool.h>
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
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival, ObstacleLaneChange} BehaviorState;

class BehaviorPlanner
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber pose_sub, vel_sub, objs_sub, sb_sub, lug_sub, start_goal_sub, v2x_spat_sub, route_sub, mission_sub, ped_sub;
        // ros::Subscriber pose_sub, vel_sub, objs_sub, route_sub, mission_sub;
        ros::Publisher b_factor_pub, b_state_pub;
        // ros::Timer behavior_timer;
        double runRate;
        float wLane, lenEgo, frontlenEgo, minFront, front_dist, unknownFront, thresLC, thresStop, thresCW, thresSB, thresTurn, thresTL, thresTLtime, thresDistSG, successDistSG;
        geometry_msgs::Pose egoPose;
        double egoSpeed;
        autoware_msgs::DetectedObjectArray detectedObjects, sb, luggage;
        double startX, startY, startID, goalX, goalY, goalID;
        int remain;
        //startpos info 
        //goalpos
        //traffic_signal
        hmcl_msgs::LaneArray globalLaneArray;
        v2x_msgs::SPAT junc1Signal, junc2Signal, junc3Signal;
        MissionState currentMission;
        BehaviorState currentBehavior;
        bool missionStart, approachToStartPos, startArrivalCheck, startArrivalSuccess, frontCar, stationaryFrontCar, approachToCrosswalk, crosswalkPass;
        bool pedestrian, pedestrianOnCrosswalk, leftTurn, rightTurn, turn, trafficLightStop, stopCheck, luggageDrop, brokenFrontCar, laneChangeDone;
        bool essentialLaneChange, speedBumpSign, speedBumpPass, approachToGoalPos, goalArrivalCheck;
        short front_id, prevLaneID, unknown_id;
        int nStore, countFront, countStationary, countSB;
        bool stop_line_stop;
        bool getGlobal, getPose, getSpeed, getObject, getSB, getLuggage, getPedestrian, getSGpos, getSPAT, getMission;
        bool inCW, frontPrev, stationaryPrev, sbPrev;
        hmcl_msgs::BehaviorFactor behaviorFactor;
        std_msgs::Int16 behavior_msg;
        bool NormalDrive, LaneFollowing, Turn;

    public:
        BehaviorPlanner(); 
        void callbackthread();
        ~BehaviorPlanner();
        void calculateLon(int n, float* psarr, hmcl_msgs::Lane &lane);
        void calculateFrenet(int n, float* psarr, float px, float py, float vx, float vy, float* psl, hmcl_msgs::Lane &lane);
        void calculateSafeDistance(float vFront, float vRear, float &dSafe);
        void updateFactors();
        void updateBehaviorState();
        BehaviorState getCurrentBehavior();
        // void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);
        void odometryCallback(const nav_msgs::Odometry& msg);
        void vehicleStatusCallback(const hmcl_msgs::VehicleStatusConstPtr &msg);
        // void twistCallback(const geometry_msgs::TwistStampedConstPtr& msg);
        void objsCallback(const autoware_msgs::DetectedObjectArray& msg);
        void sbCallback(const autoware_msgs::DetectedObjectArray& msg);
        void luggageCallback(const autoware_msgs::DetectedObjectArray& msg);
        void v2xStartGoalCallback(const hmcl_msgs::MissionWaypoint& msg);
        void v2xSPATCallback(const v2x_msgs::SPAT& msg);
        void routeCallback(const hmcl_msgs::LaneArray &msg);
        void missionCallback(const std_msgs::Int16::ConstPtr& msg);
        void pedestrianCallback(const std_msgs::Bool::ConstPtr& msg);

};