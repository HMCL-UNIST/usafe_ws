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

#include <std_msgs/Int8.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/BehaviorFactor.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <visualization_msgs/Marker.h>
#include <hmcl_msgs/PolygonFlag.h>

#define PI 3.14159265358979323846264338
typedef enum{MissionInit, VehicleReady, StartFromPitStop, Lap1, Lap2, Lap3, Lap4, Lap5, MissionComplete, PitStop, MissionSlowOn, MissionStop} MissionState;
typedef enum{BehaviorInit, BehaviorReady, EmergencyStop, FreeDrive, MissionEndStop, MissionEnd, Overtaking, ACC, ObstacleAvoidance, SlowOn, Stop} BehaviorState;




inline const char* stateToStringBehavior(BehaviorState v) // it can be defined cause it is inline fuction

{
    switch (v)
    {
        case BehaviorState::BehaviorInit:   return "BehaviorInit";
        case BehaviorState::BehaviorReady:   return "BehaviorReady";
        case BehaviorState::EmergencyStop: return "EmergencyStop";
        case BehaviorState::FreeDrive:   return "FreeDrive";
        case BehaviorState::MissionEndStop:   return "MissionEndStop";
        case BehaviorState::MissionEnd:   return "MissionEnd";
        case BehaviorState::Overtaking:   return "Overtaking";
        case BehaviorState::ACC:   return "ACC";
        case BehaviorState::ObstacleAvoidance:   return "ObstacleAvoidance";
        case BehaviorState::SlowOn:   return "SlowOn";
        case BehaviorState::Stop:   return "Stop";
        default:      return "[Unknown BehaviorState]";
    }

}


class BehaviorPlanner
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber pose_sub, map_ver_sub, vel2_sub, vel_sub, objs_sub, route_sub, opt_sub, mission_sub, external_mission_sub, overtaking_flag_sub, subtype_sub;
        ros::Publisher b_factor_pub, b_state_pub, light_pub, behavior_viz_pub,obs_pub, stopline_viz_pub;
        // ros::Timer behavior_timer;
        double runRate;
        bool vizBehavior;
        float wLane, lenEgo, frontlenEgo, dFront, front_dist, front_vel, thresObs, thresLC, thresStop;
        geometry_msgs::Pose egoPose;
        geometry_msgs::Twist egoTwist;
        double egoSpeed;
        float xObstacle, yObstacle;
        float sEgo ,lEgo, dsEgo ,dlEgo;
        float sOpt ,lOpt, dsOpt, dlOpt, lOptFar;
        float dGlobal;
        float thresPit;
        autoware_msgs::DetectedObjectArray detectedObjects;
        int targetID;
        int lane_id, wpt_id, opt_wpt_id, prev_lane_id;
        int prefer_lane_id;


        double origin_lat;
        double origin_lon;
        double origin_att;
        double origin_easting;
        double origin_northing;
        int origin_zone;
        bool origin_northp;


        //traffic_signal
        hmcl_msgs::LaneArray globalLaneArray, optimalLaneArray ;
        MissionState currentMission;
        BehaviorState currentBehavior;
        bool vehicleReady, missionStart, missionEnd, frontOpponent, leftOpponent, rightOpponent, stationaryFrontOpponent;
        bool stopCheck, laneChangeDone, checkObstacle;
        bool isEmergency, needLeftLaneChange, needRightLaneChange;
        bool isInBank, isInStraight, isBankClose;
        short front_id, left_id, right_id, prevLaneID, unknown_id;
        int nStore, countFront, countStationary, countObs;
        bool getGlobal, getOpt, getPose, getSpeed2, getSpeed, getOpponent, getMission, getMapver, getExternalMission, getOvertakingFlag;
        bool frontOpponentPrev, stationaryFrontOpponentPrev;
        bool onDriving;
        bool onDrivingFlag;
        // bool goToStraight, goToBank;
        hmcl_msgs::BehaviorFactor behaviorFactor;
        std_msgs::Int16 behavior_msg;
        std_msgs::Float64 light_msg;
        // bool prevStraight, prevBank;
        int countBehaviorReady, countMissionEndStop;
        int thresBehaviorReady;
        int map_ver;
        int externalMission = 0;
        bool overtakingFlag, accFlag, obsavoidFlag, aebFlag;
        bool KeepSpeed;

        bool goToSecondLane; // External Mission Flag
        float distToStopLine;
        hmcl_msgs::PolygonFlag PolygonFlag;

    public:
        BehaviorPlanner(); 
        void callbackthread();
        ~BehaviorPlanner();
        void calculateLon(int n, float* psarr, hmcl_msgs::Lane &lane);
        void calculateFrenet(int n, float* psarr, float px, float py, float vx, float vy, float* psl, hmcl_msgs::Lane &lane);
        void getCurrentLaneWpt();
        void getCurrentOptWpt();
        void updatePreferLaneID();
        void updateFactors();
        void updateBehaviorState();
        void publishMsgs();
        void viz_behavior();
        double distance(double x1, double y1, double x2, double y2);
        BehaviorState getCurrentBehavior();
        void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);
        // void odometryCallback(const nav_msgs::Odometry& msg);
        void vehicleStatusCallback(const hmcl_msgs::VehicleStatusConstPtr &msg);
        void twistCallback(const geometry_msgs::TwistStampedConstPtr& msg);
        void objsCallback(const autoware_msgs::DetectedObjectArray& msg);
        void routeCallback(const hmcl_msgs::LaneArray &msg);
        void optCallback(const hmcl_msgs::LaneArray &msg);
        void missionCallback(const std_msgs::Int16::ConstPtr& msg);
        void mapverCallback(const std_msgs::Int8::ConstPtr& msg);
        void setMissionStateCallback(const std_msgs::Int16::ConstPtr& msg);
        void calculateDistToStopLine();
        void stopline_viz();
        void overtakingCallback(const std_msgs::Int8::ConstPtr& msg);
        void subtypeCallback(const hmcl_msgs::PolygonFlag::ConstPtr& msg);


};