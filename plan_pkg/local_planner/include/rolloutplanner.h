#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

#include <autoware_msgs/DetectedObjectArray.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <hmcl_msgs/VehicleStatus.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;

typedef enum{Init2, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival, ObstacleLaneChange} BehaviorState;

struct Point
{
    double x;
    double y;
    double vel;
    double psi;

    double q_x;
    double q_y;
    double q_z;
    double q_w;
};


struct Obstacle
{
    double x;
    double y;
    double length;
    bool exist = false;
};

class rolloutPlanner
{
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_traj, pub_viz, pub_bool, pub_all;
    ros::Subscriber sub_pos, sub_vel, sub_traj, sub_flag, sub_obs;
    ros::Timer timer_;
    
    bool lc_flag = false;
    bool st_flag = false;
    bool vel_flag = false;
    bool obs_flag = false;
    bool return_flag = false;
    
    Point pos_c;
    Obstacle obs;
    hmcl_msgs::Lane ref_lane;

    //vehicle parameter
    double veh_m, veh_mf, veh_mr, veh_l, veh_lf, veh_lr; 
    double dt, vel_param, angle, ang_obs, ang_lc;
    int N_, N, M, N_pre;
    int n_samples;

    // lane change paramter
    double min_prepare_len, min_lc_len, lc_prepare_dur, lc_duration, lane_width;
    double lc_prepare_dist, lc_dist;
    double obs_len;

    std::vector<Point> pt_sample;
    std::vector<std::vector<Point>> pts_data;

    hmcl_msgs::LaneArray range_lane;
    hmcl_msgs::LaneArray lane_all;

public:
    rolloutPlanner(ros::NodeHandle& nh);
    ~rolloutPlanner();

    void connect_handler(const ros::TimerEvent& time);   
    void poseCallback(const nav_msgs::Odometry& state_msg);
    void wheelCallback(const hmcl_msgs::VehicleStatus& state_msg);
    void flagCallback(const std_msgs::Int16ConstPtr& flag_msg);
    void trajCallback(const hmcl_msgs::LaneArray& lane_msg);
    void ObsCallback(const autoware_msgs::DetectedObjectArray& obs_msg);

    void PreparePhase();
    hmcl_msgs::Lane Cutofflane();

    //rollouts
    void diffequation_kin(double *x, double u);
    double PurePursuit(double *x,int idx);
    Point fill_out_state(const double *x);
    int evaluatelane(const hmcl_msgs::LaneArray& lane_arr);
    hmcl_msgs::Lane Cutofflane(const hmcl_msgs::Lane& lane);

    double calculate_dist_cost_short(const hmcl_msgs::Lane& ref, const hmcl_msgs::Lane& lane);
    double calculate_dist_cost(const hmcl_msgs::Lane& ref, const hmcl_msgs::Lane& lane);
    double calculate_min(const hmcl_msgs::Lane& lane, double x, double y );
    int calculate_min_idx(const hmcl_msgs::Lane& ref, double x1, double y1);

    void viz_local(const hmcl_msgs::Lane& lane);
    void viz_all(const hmcl_msgs::LaneArray& lane_arr);
};