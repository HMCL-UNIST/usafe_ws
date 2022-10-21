#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <algorithm>
#include <vector>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include "spline.h"

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/BehaviorFactor.h>

#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <hmcl_msgs/VehicleStatus.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;
using namespace Eigen;

typedef enum{Init2, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival, ObstacleLaneChange} BehaviorState;
struct Sector 
{
    geometry_msgs::Pose section{};
    double speed;
};

struct Obstacle
{
    double x;
    double y;
    double length;
    bool exist = false;
};

template<class Function>
double fderiv(const Function& f, int order, double x)
{
    if(order==1) {
        double dx=2e-8*(1.0+fabs(x));
        return (f(x+dx)-f(x-dx)) / (2.0*dx);
    } else if(order==2) {
        double dx=3e-6*(1.0+fabs(x));
        return (f(x-dx)-2.0*f(x)+f(x+dx)) / (dx*dx);
    } else {
        assert(false);
        return -1.0;
    }
}


class localplanners
{
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_traj, pub_viz, pub_bool;
    ros::Subscriber sub_pos, sub_vel, sub_traj, sub_flag, sub_obs;
    
    ros::Timer timer_;

    bool lc_flag = false;
    bool st_flag = false;
    bool vel_flag = false;
    bool obs_flag = false;
    bool return_flag = false;
    Sector current_pos;
    Obstacle obs;
    hmcl_msgs::Lane pub_lane;


    double min_lc_len, lc_prepare_dur, lc_duration, min_lc_vel, lc_dec, lane_width;
    double lc_prepare_dist, lc_dist, lc_prepare_vel, lc_vel;
    double obs_len;
    hmcl_msgs::LaneArray range_lane;

    vector<int> range_index;

public:
    localplanners(ros::NodeHandle& nh_);
    ~localplanners();
    
    void connect_handler(const ros::TimerEvent& time);   
    void poseCallback(const nav_msgs::Odometry& state_msg);
    void wheelCallback(const hmcl_msgs::VehicleStatus& state_msg);
    void flagCallback(const std_msgs::Int16ConstPtr& flag_msg);
    void trajCallback(const hmcl_msgs::LaneArray& lane_msg);
    void ObsCallback(const hmcl_msgs::BehaviorFactor& obs_msg);

    double calculate_min(const hmcl_msgs::Lane& lane, double x, double y );

    void PreparePhase();
    hmcl_msgs::Lane CutoffTraj();
    int FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose);
    int FindClosest(const hmcl_msgs::Lane& lane, geometry_msgs::Pose pose);
    void viz_local(const hmcl_msgs::Lane& lane);
};
