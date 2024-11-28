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
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

#include <std_msgs/Int16.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/BehaviorFactor.h>
#include <autoware_msgs/DetectedObjectArray.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include "hermite_curve.h" // Hermite curve 관련 헤더 파일 포함

using namespace std;
using namespace Eigen;

typedef enum{BehaviorInit, BehaviorReady, EmergencyStop, StraightFreeDrive, LeftLaneChange, RightLaneChange, ReadyForBank,
            BankFreeDrive, BankACC, MissionEndStop, MissionEnd} BehaviorState;
struct Sector 
{
    geometry_msgs::Pose section{};
    double speed;
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
    ros::Publisher pub_traj, pub_viz;
    ros::Publisher local_traj_pub, l_traj_viz_pub, target_pub;
    ros::Subscriber sub_pos, sub_vel, sub_traj, sub_flag,sub_obj,sub_bfac;
    
    ros::Timer timer_;
    bool lc_ing =false;
    bool lc_flag = false;
    bool obs_flag = false;
    bool rlc_flag = false;
    bool llc_flag = false;
    bool st_flag = false;
    bool vel_flag = false;
    bool local_traj_available = false;
    bool global_traj_available = false;
  
    bool behavior_factor_init = false;
    bool pose_init = false;
    
    Sector current_pos;
    std::vector<double> X,Y;
    std::vector<tuple<double,double,double>> pt_xy;

    double min_lc_len, lc_prepare_dur, lc_duration, min_lc_vel, lc_dec, lane_width,Q_vel;
    double lc_prepare_dist, lc_dist, lc_prepare_vel, lc_vel;
    double pose_x, pose_y;
    int lane_index = 0;
    int prefer_lane_id, current_lane_id;
    nav_msgs::Odometry pub_target;
    hmcl_msgs::LaneArray global_lane_array;
    hmcl_msgs::Lane local_lane;
    hmcl_msgs::Lane pub_lane, save_lane;
    autoware_msgs::DetectedObjectArray obj;
    visualization_msgs::MarkerArray local_traj_marker_array;



public:
    localplanners(ros::NodeHandle& nh_);
    ~localplanners();
    
    void local_handler(const ros::TimerEvent& time);   
    void poseCallback(const geometry_msgs::PoseStamped& state_msg);
    void velCallback(const geometry_msgs::TwistStamped& state_msg);
    // void velCallback(const hmcl_msgs::VehicleStatus& state_msg);
    void behaviorstateCallback(const std_msgs::Int16ConstPtr& flag_msg);
    void behaviorfactorCallback(const hmcl_msgs::BehaviorFactor& factor_msg);
    void globalCallback(const hmcl_msgs::LaneArray& lane_msg);
    void objCallback(const autoware_msgs::DetectedObjectArray& obj_msg);
    void publish_local_path();
    void compute_local_path();
    void setColor(std_msgs::ColorRGBA* cl, double r, double g, double b, double a);
    int calculate_distance_pose2local();
    double distance(double x1, double y1, double x2, double y2);
    visualization_msgs::MarkerArray visualize_local_path(const hmcl_msgs::Lane local_lane);
    void PreparePhase();
    int FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose);
    int FindClosest(const hmcl_msgs::Lane& lane, geometry_msgs::Pose pose);
    double calculateVLength(double current_speed);
    void print_XY(std::vector<double> X, std::vector<double> Y);
    // void splinfy(int endidx);
    void splinfy();
    bool valid_lane(const hmcl_msgs::Lane& lane, int lidx, int pidx);
    bool calculate_dist(const hmcl_msgs::Lane& lane, geometry_msgs::Pose pose);
    void viz_local(const hmcl_msgs::Lane& lane);

};