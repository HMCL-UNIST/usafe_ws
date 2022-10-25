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

#include <v2x_msgs/Mission1.h>
#include <v2x_msgs/Request.h>
#include <std_msgs/Int16.h>

#define PI 3.14159265358979323846264338
typedef enum{Init = 0, ChooseDifficulty = 1, MissionRequest = 2, DriveToStartPos = 3, StartArrivalRequest = 4, DriveToGoalPos = 5,
            GoalArrivalRequest = 6, MissionComplete = 7, EmergencyStop = 8} MissionState;
typedef enum{Init2, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival, EmergencyStop2} BehaviorState;

inline const char* stateToStringMission(MissionState v)

{

    switch (v)

    {

        case MissionState::Init:   return "Init";

        case MissionState::ChooseDifficulty:   return "ChooseDifficulty";

        case MissionState::MissionRequest:   return "MissionRequest";

        case MissionState::DriveToStartPos:   return "DriveToStartPos";

        case MissionState::StartArrivalRequest:   return "StartArrivalRequest";

        case MissionState::DriveToGoalPos:   return "DriveToGoalPos";

        case MissionState::GoalArrivalRequest:   return "GoalArrivalRequest";

        case MissionState::MissionComplete:   return "MissionComplete";

        default:      return "[Unknown MissionState]";

    }

}
class MissionStateMachine
{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber v2x_mission_sub, v2x_rsp_sub, behavior_sub;
        ros::Publisher mission_pub;
        std_msgs::Int16 mission_msg;
        // ros::Timer mission_timer;
        //transition conditions
        bool statusWait, statusStart, statusEstop, missionRequestSuccess, arriveAtStartPos,startArrivalSuccess, arriveAtGoalPos, goalArrivalSuccess;
        //callback data
        int v2xMissionStat;
        double runRate;
        int countInit, countChooseDifficulty, countMissionRequest, countDriveToStartPos, countStartArrivalRequest, countDriveToGoalPos, countGoalArrivalRequest;
        int thresInit, thresChooseDifficulty, thresMissionRequest, thresDriveToStartPos, thresStartArrivalRequest, thresDriveToGoalPos, thresGoalArrivalRequest;
        BehaviorState currentBehavior;
        MissionState currentMission, ePrevMission;
    public:
        MissionStateMachine();
        MissionStateMachine(MissionState mstate);
        void callbackthread();
        ~MissionStateMachine();
        MissionState getCurrentMission();
        void updateFactors();
        void updateMissionState();
        bool getParam(int param_id);
        void v2xMissionCallback(const v2x_msgs::Mission1& msg);
        void v2xResponseCallback(const v2x_msgs::Request& msg);
        void behaviorCallback(const std_msgs::Int16::ConstPtr& msg);

};

