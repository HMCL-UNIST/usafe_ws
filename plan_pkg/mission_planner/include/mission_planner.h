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

// #include <hmcl_v2x/MissionArray.h>
// #include <hmcl_v2x/Reply.h>
#include <std_msgs/Int16.h>

#define PI 3.14159265358979323846264338
typedef enum{Init, ChooseDifficulty, MissionRequest, DriveToStartPos, StartArrivalRequest, DriveToGoalPos,
            GoalArrivalRequest, MissionComplete} MissionState;
typedef enum{Init2, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival} BehaviorState;


class MissionStateMachine
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber v2x_mission_sub, v2x_rsp_sub, behavior_sub;
        ros::Publisher mission_pub;
        // ros::Timer mission_timer;
        //transition conditions
        bool statusWait, statusStart, missionRequestSuccess, arriveAtStartPos,startArrivalSuccess, arriveAtGoalPos, goalArrivalSuccess;
        //callback data
        int v2xMissionStat;
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
        // void v2xMissionCallback(const hmcl_v2x::MissionArray::ConstPtr& msg);
        // void v2xResponseCallback(const hmcl_v2x::Reply::ConstPtr& msg);
        void behaviorCallback(const std_msgs::Int16::ConstPtr& msg);

};

