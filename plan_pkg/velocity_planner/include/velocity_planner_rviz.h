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
#include <geometry_msgs/PoseStamped.h>
#include <hmcl_msgs/LaneArray.h>
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

#include <dynamic_reconfigure/server.h>
#include <velocity_planner/testConfig.h>

using std::to_string;

//**This will be changed after behavior planner is finialzed. 
// enum struct BehaviorState {Init = 0, Forward = 1, Follow = 2, StopAtStartPos=3,
//                             StartArrival=4, TrafficLightStop=5, LeftTurn=6, RightTurn=7,
//                             Crosswalk=8, Pedestrian=9, FrontLuggage=10, FrontCarStop=11, 
//                             LaneChange=12, SpeedBump=13, StopAtGoalPos=14, GoalArrival=15, ObstacleLaneChange=16}; 


typedef enum{BehaviorInit, BehaviorReady, EmergencyStop, FreeDrive, LeftLaneChange, RightLaneChange,MissionEndStop,
                MissionEnd, Overtaking, ACC} BehaviorState;
enum ControlMode{
    CONTROL_MODE_ACC =0,
    CONTROL_MODE_LaneChange =1,
    CONTROL_MODE_OPTIMAL =2,
    CONTROL_MODE_GGV =3,


};

struct Sector
{
    geometry_msgs::Pose section{};
    double speed;
};
class VelocityPlanner 
{
private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub, vel_debug, vel_vis_pub, motionstate_vis_pub, curvature_pub;
    ros::Subscriber v2x_spat_sub, pose_sub, wheel_sub, acc_sub, predicted_objects_sub, start_end_sub,
                    traffic_sign_sub, behavior_state_sub, behavior_state_condition_sub, local_traj_sub, velocity_sub,odom_sub,sub_canAcc_sub;
    ros::Time previous_time = ros::Time::now();
    ros::Timer velocity_timer;  // Declare the timer variable
    ros::Timer curvature_timer;
    bool velocity_timer_running, curvature_timer_running;
    double runtime;
    double current_pose;
    double current_acc, current_vel, currentVel, current_x, current_y,currentAcc, previous_vel,abs_speed, final_safe_speed, can_acc;
    double object_x, object_y, object_vel;

    geometry_msgs::Point start, end;
    v2x_msgs::SPAT junc1Signal, junc2Signal, junc3Signal;
    Sector current_pos;
    int eventState = -1;
    int timing_min_End_Time =-1;
    bool lc_flag=false;
    std::string motionstate_debug;
    bool misson_stop=false;
    bool getLocalTraj;
    bool LeadVehicle=false, Pedestrian, PassStopLine;
    bool new_behavior_mode, find_stopline, find_crosswalk, find_judgeline;
    bool passcrosswalk, passjudgeline;
    bool stop = false;
    float LeadVehicleVel, LeadVehicleDist;
    double wait_tt;
    short LeadVehicleInd;
    double MaxVel;
    int signal_id, lane_id;
    double rel_vel;
    bool stop_flag, slow_flag, acc_flag;

    BehaviorState CurrentMode, PreviousMode;

    // paramter for planning
    double stopline_margin, crosswalk_margin, stop_margin, vehicle_length;
    double intersection_velocity, speedbump_velocity, max_lat_acc, max_long_acc;
    double dis_x, dis_y,currentvx,currentvy,currentax,currentay;

    //parameter for ACC
    double DesiredVel, Dis, DesiredDis, targetVel;
    int delay_step;
    double delay_in_sec, lag_tau, dt;
    double Q_dis, Q_vel, r_weight;
    double acc_cmd, d_safe, d_time, max_speed;
    bool Activate = false;

    double first_bank_lane_speed, second_bank_lane_speed, third_bank_lane_speed, first_lane_speed, second_lane_speed, third_lane_speed;
    double ref_speed;
    double planned_velocity;
    ControlMode control_mode;

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

    dynamic_reconfigure::Server<velocity_planner::testConfig> srv;
    dynamic_reconfigure::Server<velocity_planner::testConfig>::CallbackType f;



public:
VelocityPlanner(); 


void dyn_callback(velocity_planner::testConfig &config, uint32_t level);


int FindClosest(const std::vector<hmcl_msgs::Waypoint>& waypoints,
geometry_msgs::Pose pose);
void callbackthread();
//**Main function
// void PlanVel();
void CheckMotionState();
//**Debug function
double CalculateCurveDebug();
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
void VelocitySmoother(double planned_velocity);
void canAccCallback(const std_msgs::Float64& acc_msg);
double AdjustVelocityForSlip(double current_velocity);
double AdjustVelocityForLcFlag(double current_desired_velocity, double current_velocity);
void publishCurvatureSpeed();
double publishGGVSpeed();
double GGVAlgorithm();
bool calcNearestPose(unsigned int &nearest_index, double &min_dist_error);
void publishLocalTrajSpeed();


//***Callback Function
double Curvature();
void v2xSPATCallback(const v2x_msgs::SPAT& msg);
void poseCallback(const geometry_msgs::PoseStamped& state_msg);
void accCallback(const sensor_msgs::Imu& msg);
void odomCallback(const sensor_msgs::Imu& msg);
void wheelCallback(const hmcl_msgs::VehicleStatus& state_msg);
void velCallback(const geometry_msgs::TwistStamped& state_msg);
void PredictedObjectsCallback(const autoware_msgs::DetectedObjectArray& msg);
// Need to decide the message  
void trajCallback(const hmcl_msgs::Lane& msg); //from Local Planner
void BehaviorStateCallback(const std_msgs::Int16ConstPtr& flag_msg); //from Behavior planner
void BehaviorStateFactorCallback(const hmcl_msgs::BehaviorFactor& msg); //from Behavior planner
// void TrafficSignCallback(); //from V2X
void startendCallback(const hmcl_msgs::MissionWaypoint& msg);
void checkTrafficSignal(const bool& leftTurn);
void viz_vel_prof(std::vector<double> profile);
void viz_motionstate();
void visualizeGGVset();

// double GGV();

};