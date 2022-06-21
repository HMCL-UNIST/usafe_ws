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

#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/VehicleStatus.h>

class VelocityGenerator 
{

    private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub, vel_vis_pub, vel_debug;
    ros::Subscriber local_traj_sub, vel_sub, wheel_sub,acc_sub, acc_target_vel_sub;

    ros::Timer vel_timer;

    bool new_vel, local_traj_init, visualize, new_target_vel, previous_step;
    float speed_limit, current_acc, current_vel, target_acc_vel;
    int ttt;

    hmcl_msgs::Lane traj;
    geometry_msgs::PoseStamped debug_msg;

    public:
    VelocityGenerator();

    void callbackthread();
    void trajCallback(const hmcl_msgs::Lane& msg);
    void velCallback(const nav_msgs::Odometry& state_msg);
    void accCallback(const geometry_msgs::Point& msg);
    void targetCallback(const std_msgs::Float64& msg);
    void wheelCallback(const hmcl_msgs::VehicleStatus& state_msg);

    void CalcVel();
    void viz_vel_prof(std::vector<double> profile);
};