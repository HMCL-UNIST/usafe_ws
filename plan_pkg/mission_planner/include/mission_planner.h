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
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <ros/package.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int8.h>
#include <std_msgs/String.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/PolygonFlag.h>
#include <GeographicLib/UTMUPS.hpp>

#define PI 3.14159265358979323846264338
typedef enum{MissionInit, VehicleReady, StartFromPitStop, Lap1, Lap2, Lap3, Lap4, Lap5, MissionComplete, PitStop} MissionState;
typedef enum{BehaviorInit, BehaviorReady, EmergencyStop, StraightFreeDrive, LeftLaneChange, RightLaneChange, ReadyForBank,
            BankFreeDrive, BankACC, MissionEndStop, MissionEnd} BehaviorState;

inline const char* stateToStringMission(MissionState v)

{
    switch (v)
    {
        case MissionState::MissionInit:   return "MissionInit";
        case MissionState::VehicleReady: return "VehicleReady";
        case MissionState::StartFromPitStop:   return "StartFromPitStop";
        case MissionState::Lap1:   return "Lap1";
        case MissionState::Lap2:   return "Lap2";
        case MissionState::Lap3:   return "Lap3";
        case MissionState::Lap4:   return "Lap4";
        case MissionState::Lap5:   return "Lap5";
        case MissionState::MissionComplete:   return "MissionComplete";
        case MissionState::PitStop: return "PitStop";
        default:      return "[Unknown MissionState]";
    }

}
class MissionStateMachine
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber behavior_sub, pose_sub, vel_sub, signal_sub, map_ver_sub, mission_state_sub, subtype_sub ;
        ros::Publisher mission_pub, mission_viz_pub, target_viz_pub;
        std_msgs::Int16 mission_msg;
        hmcl_msgs::PolygonFlag PolygonFlag;

        //transition conditions
        bool goalCheck, prevGoalCheck;
        bool getPose, getSpeed, getBehavior, vizMission, getSignal, getMap_ver, getExternalMission ,getSubType;
        bool statusWait, statusStart, statusPitStop, checkPitStop, startAfterPitStop, checkMapChangePoint, checkLap2, checkLap3, checkLap4, checkLap5, missionEnd;


        //callback data
        double runRate, distToGoal, thresGoal, distToPitStop, thresPitStop, thresMapChangePoint, distToMapChangePoint;
        int countMissionInit, countVehicleReady, countPitStop, countStartFromPitStop, countLap1, countLap2, countLap3, countLap4, countLap5, countMissionComplete;
        int thresMissionInit, thresVehicleReady, thresLap1, thresLap2, thresLap3, thresLap4, thresLap5;
        geometry_msgs::Pose egoPose;
        int currentSignal = 0;
        int currentMap_ver = -1;
        int externalMission = -1;
        double egoSpeed;

        BehaviorState currentBehavior;
        MissionState currentMission;
    public:
        MissionStateMachine();
        MissionStateMachine(MissionState mstate);
        void callbackthread();
        ~MissionStateMachine();
        MissionState getCurrentMission();
        void updateFactors();
        void updateMissionState();
        bool getParam(int param_id);
        void plantStateCallback(const hmcl_msgs::VehicleStatus& state_msg);
        void behaviorCallback(const std_msgs::Int16::ConstPtr& msg);
        void signalCallback(const std_msgs::Int8::ConstPtr& msg);
        void mapCallback(const std_msgs::Int8::ConstPtr& msg);
        void setMissionStateCallback(const std_msgs::Int16::ConstPtr& msg);
        void viz_mission();
        void viz_target_points();
        void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);
        void calculateDistToGoal();
        void calculateDistToPitStop();
        void calculateDistToMapChangePoint();
        void subtypeCallback(const hmcl_msgs::PolygonFlag::ConstPtr& msg);

};

