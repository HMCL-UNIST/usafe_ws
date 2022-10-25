#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>
#include <ros/package.h>
#include <eigen3/Eigen/Geometry>

#include <std_msgs/Float64.h>
#include <std_msgs/Int16.h>
// #include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/WaypointArray.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/BehaviorFactor.h>
#include <hmcl_msgs/MissionWaypoint.h>   
#include <hmcl_msgs/TransitionCondition.h>
#include <v2x_msgs/SPAT.h>
#include <autoware_msgs/DetectedObjectArray.h>

#include <sensor_msgs/Imu.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using std::to_string;

//**This will be changed after behavior planner is finialzed. 
enum struct BehaviorState {Init = 0, Forward = 1, Follow = 2, StopAtStartPos=3,
                            StartArrival=4, TrafficLightStop=5, LeftTurn=6, RightTurn=7,
                            Crosswalk=8, Pedestrian=9, FrontLuggage=10, FrontCarStop=11, 
                            LaneChange=12, SpeedBump=13, StopAtGoalPos=14, GoalArrival=15, ObstacleLaneChange=16}; 

inline const char* stateToStringBehavior(BehaviorState v)
{
    switch (v)
    {
        case BehaviorState::Init:   return "Init";
        case BehaviorState::Forward:   return "Forward";
        case BehaviorState::Follow:   return "Follow";
        case BehaviorState::StopAtStartPos:   return "StopAtStartPos";
        case BehaviorState::StartArrival:   return "StartArrival";
        case BehaviorState::RightTurn:   return "RightTurn";
        case BehaviorState::LeftTurn:   return "LeftTurn";
        case BehaviorState::Crosswalk:   return "Crosswalk";
        case BehaviorState::Pedestrian:   return "Pedestrian";
        case BehaviorState::FrontLuggage:   return "FrontLuggage";
        case BehaviorState::FrontCarStop:   return "FrontCarStop";
        case BehaviorState::LaneChange:   return "LaneChange";
        case BehaviorState::SpeedBump:   return "SpeedBump";
        case BehaviorState::StopAtGoalPos:   return "StopAtGoalPos";
        case BehaviorState::GoalArrival:   return "GoalArrival";
        case BehaviorState::TrafficLightStop:   return "TrafficLightStop";
         case BehaviorState::ObstacleLaneChange: return "ObstacleLaneChange";
        default:      return "[Unknown BehaviorState]";
    }
}

enum struct MotionState {GO=0, DECELERATE=1, ACC=2, STOP=3, FAIL=4};

inline const char* stateToStringEvent(int event)
{
    switch (event)
    {
        case 3:   return "Red";
        case 5:   return "Green";
        case 6:   return "Green";
        case 7:   return "Yellow";
        case 8:  return "Yellow";
        default:      return "[Unknown]";
    }
}

inline const char* stateToStringMotion(MotionState v)
{
    switch (v)
    {
        case MotionState::GO:   return "Go";
        case MotionState::DECELERATE:   return "Decelerate";
        case MotionState::ACC:   return "ACC";
        case MotionState::STOP:   return "Stop";
        case MotionState::FAIL:   return "Fail";
        default:      return "[Unknown MotionState]";
    }
}



class VelocityPlanner 
{
private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub, vel_debug, vel_vis_pub, motionstate_vis_pub;
    ros::Subscriber target_sub, v2x_spat_sub, pose_sub, wheel_sub, acc_sub, predicted_objects_sub, start_end_sub,
                    traffic_sign_sub, behavior_state_sub, behavior_state_condition_sub, local_traj_sub;
    
    double runtime, mission_margin, judge_margin;
    
    double current_acc, current_vel, current_x, current_y;
    double object_x, object_y, object_vel;
    bool getSPAT1 =false, getSPAT2=false, getSPAT3=false, get_pose=false; 
    geometry_msgs::Point start, end;
    v2x_msgs::SPAT junc1Signal, junc2Signal, junc3Signal;
    
    int eventState = -1;
    int timing_min_End_Time =-1;

    std::string motionstate_debug;
    bool mission_stop=false;
    bool getLocalTraj;
    bool LeadVehicle=false, Mobileye = false, Pedestrian, PassStopLine;
    bool new_behavior_mode, find_stopline, find_crosswalk, find_judgeline;
    bool passcrosswalk, passjudgeline;
    bool stop = false;
    float LeadVehicleVel, LeadVehicleDist;
    float LeadVehicleVel_m, LeadVehicleDist_m;
    double wait_tt, mob_tt=0;
    short LeadVehicleInd;
    double MaxVel;
    bool getBehavior=false, getMission=false;
    int signal_id, lane_id;
    double rel_vel;

    BehaviorState CurrentMode, PreviousMode;
    MotionState MotionMode;

    // paramter for planning
    double stopline_margin, crosswalk_margin, stop_margin, vehicle_length;
    double intersection_velocity, intersection_velocity1, speedbump_velocity, max_lat_acc, max_long_acc;
    double dis_x, dis_y;

    //parameter for ACC
    double DesiredVel, Dis, DesiredDis, targetVel;
    int delay_step;
    double delay_in_sec, lag_tau, dt;
    double Q_dis, Q_vel, r_weight;
    double acc_cmd, d_safe, d_time;

    double ref_speed;
    

    std::vector<double> acc_buffer;

    hmcl_msgs::WaypointArray traj;

    Eigen::VectorXd Xk;

    Eigen::MatrixXd mcQ, mcR;  
    Eigen::MatrixXd Abaroc, Bbaroc;
    Eigen::MatrixXd Abarc, Bbarc;
    Eigen::MatrixXd Ad, Bd;

    Eigen::MatrixXd mcAd, mcBd; 
    Eigen::MatrixXd mcP;;
    
    //parameter for velocity smoother
    double visualize;
    bool fail2determine, previous_step;


public:
VelocityPlanner(); 


void callbackthread();

//**Main function
void PlanVel();
void CheckMotionState();

//**Utility function
int FindStopLine();
int FindCrossWalk();
int FindJudgeLine();
double CheckLeadVehicle();

//**ACC function
double ACC();
void computeMatrices();
double computeGain();
bool solveRiccatiIterationD(const Eigen::MatrixXd &Ad,
            const Eigen::MatrixXd &Bd, const Eigen::MatrixXd &Q,
            const Eigen::MatrixXd &R, Eigen::MatrixXd &P,
            const double &tolerance = 1.E-5,
            const uint iter_max = 100000);


//***Velocity Smoother Function
void VelocitySmoother();


//***Callback Function
double Curvature();
void v2xSPATCallback(const v2x_msgs::SPAT& msg);
void poseCallback(const nav_msgs::Odometry& state_msg);
void accCallback(const sensor_msgs::Imu& msg);
void wheelCallback(const hmcl_msgs::VehicleStatus& state_msg);
void PredictedObjectsCallback(const autoware_msgs::DetectedObjectArray& msg);
// Need to decide the message  
void trajCallback(const hmcl_msgs::Lane& msg); //from Local Planner
void BehaviorStateCallback(const std_msgs::Int16& mode); //from Behavior planner
void BehaviorStateFactorCallback(const hmcl_msgs::BehaviorFactor& msg); //from Behavior planner
// void TrafficSignCallback(); //from V2X
void startendCallback(const hmcl_msgs::MissionWaypoint& msg);
void checkTrafficSignal(const bool& leftTurn);
void viz_vel_prof(std::vector<double> profile);
void objectCallback(const autoware_msgs::DetectedObjectArray& msg);
void viz_motionstate();

};