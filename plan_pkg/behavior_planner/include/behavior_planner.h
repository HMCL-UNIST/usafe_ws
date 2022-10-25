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
#include <std_msgs/Float64.h>
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
            GoalArrivalRequest, MissionComplete, EmergencyStop} MissionState;
typedef enum{Init2, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival, ObstacleLaneChange, EmergencyStop2} BehaviorState;

inline const char* stateToStringBehavior(BehaviorState v)

{

    switch (v)

    {

        case BehaviorState::Init2:   return "Init2";

        case BehaviorState::Forward:   return "Forward";

        case BehaviorState::Follow:   return "Follow";

        case BehaviorState::StopAtStartPos:   return "StopAtStartPos";

        case BehaviorState::StartArrival:   return "StartArrival";

        case BehaviorState::TrafficLightStop:   return "TrafficLightStop";

        case BehaviorState::LeftTurn:   return "LeftTurn";

        case BehaviorState::RightTurn:   return "RightTurn";

        case BehaviorState::Crosswalk:   return "Crosswalk";

        case BehaviorState::Pedestrian:   return "Pedestrian";

        case BehaviorState::FrontLuggage:   return "FrontLuggage";

        case BehaviorState::FrontCarStop:   return "FrontCarStop";

        case BehaviorState::LaneChange:   return "LaneChange";

        case BehaviorState::SpeedBump:   return "SpeedBump";

        case BehaviorState::StopAtGoalPos:   return "StopAtGoalPos";

        case BehaviorState::GoalArrival:   return "GoalArrival";

        case BehaviorState::ObstacleLaneChange: return "ObstacleLaneChange";

        case BehaviorState::EmergencyStop2: return "EmergencyStop2";

        default:      return "[Unknown BehaviorState]";

    }

}

class BehaviorPlanner
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber target_sub, pose_sub, vel_sub, objs_sub, ped_obj_sub, sb_sub, lug_sub, start_goal_sub, v2x_spat_sub, route_sub, mission_sub, ped_sub, ret_sub;
        // ros::Subscriber pose_sub, vel_sub, objs_sub, route_sub, mission_sub;
        ros::Publisher b_factor_pub, b_state_pub, light_pub;
        // ros::Timer behavior_timer;
        // std::mutex
        double runRate;
        float wLane, lenEgo, frontlenEgo, dFront,thresFrontStop, front_dist, front_vel, dLuggage, thresObs, thresLC, thresStop, thresCW, thresSB, thresTurn,thresMinTurn, thresTL, thresTLtime, thresDistSG, successDistSG;
        geometry_msgs::Pose egoPose;
        double egoSpeed, prev_object_x, prev_object_y;
        float xObstacle, yObstacle, xSBsign, ySBsign, lightPrev;
        autoware_msgs::DetectedObjectArray detectedObjects, sb, luggage, mobObj, pedObj;
        double startX, startY, startID, start_idx, goalX, goalY, goalID, goal_idx;
        int targetID;
        ros::Time obj_time;
        //startpos info 
        //goalpos
        //traffic_signal
        hmcl_msgs::LaneArray globalLaneArray;
        v2x_msgs::SPAT junc1Signal, junc2Signal, junc3Signal;
        MissionState currentMission;
        BehaviorState currentBehavior, ePrevBehavior;
        bool missionStart, approachToStartPos, startArrivalCheck, startArrivalSuccess, frontCar, stationaryFrontCar, approachToCrosswalk, crosswalkPass;
        bool pedestrian, pedestrianOnCrosswalk, leftTurn, rightTurn, turn, trafficLightStop, stopCheck, luggageDrop, brokenFrontCar, laneChangeDone, checkObstacle;
        bool essentialLaneChange, speedBumpSign, speedBumpPass, approachToGoalPos, goalArrivalCheck, startChecker;
        short front_id, prevLaneID, unknown_id;
        int nStore, countFront, countStationary, countSB, countLuggage, countObs;
        bool stop_line_stop, localRet;
        bool getGlobal, getPose, getSpeed, getObject, getPedObj, getSB, getLuggage, getPedestrian, getSGpos, getMission, getSPAT1,getSPAT2,getSPAT3,getRet, getMob;
        bool inCW, frontPrev, stationaryPrev, sbPrev, luggagePrev;
        hmcl_msgs::BehaviorFactor behaviorFactor;
        std_msgs::Int16 behavior_msg;
        std_msgs::Float64 light_msg;
        hmcl_msgs::MissionWaypoint target_msg;
        bool NormalDrive, LaneFollowing, Turn;
        int countInit2, countStopAtStartPos, countStartArrival;
        int countPedestrian, countFrontLuggage, countFrontCarStop, countSpeedBump, countStopAtGoalPos;
        int thresInit2, thresStopAtStartPos, thresStartArrival;
        int thresPedestrian, thresFrontLuggage, thresFrontCarStop, thresSpeedBump, thresStopAtGoalPos;

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
        bool calculateDistObjs(geometry_msgs::Point& pos);
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
        void localRetCallback(const std_msgs::Bool::ConstPtr& msg);
        void objectCallback(const autoware_msgs::DetectedObjectArray& msg);
        void pedObjectCallback(const autoware_msgs::DetectedObjectArray& msg);



};