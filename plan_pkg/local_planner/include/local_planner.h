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

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/WaypointArray.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>


enum struct BehaviorState {Init = 0, Forward = 1, Follow = 2, StopAtStartPos=3,
                            StartArrival=4, TrafficLightStop=5, LeftTurn=6, RightTurn=7,
                            Crosswalk=8, Pedestrian=9, FrontLuggage=10, FrontCarStop=11, 
                            LaneChange=12, SpeedBump=13, StopAtGoalPos=14, StopArrival=15}; 

class LocalPlanner
{
private:
    ros::NodeHandle nh_;
    ros::Publisher local_pub;
    ros::Subscriber pose_sub, behavior_state_sub, global_traj_sub;
    
    BehaviorState CurrentMode;
    geometry_msgs::Pose cur_pose;
    hmcl_msgs::Lane local_traj,c_local_traj;
    hmcl_msgs::LaneArray global_traj;
    double pose_x, pose_y, pose_z;

    bool get_global, pose_init;

public:
    LocalPlanner();
    void callbackthread();
    void PlanLocalTraj();
    void BehaviorStateCallback(const std_msgs::Int16& msg);
    void poseCallback(const nav_msgs::OdometryConstPtr& msg);
    void trajCallback(const hmcl_msgs::LaneArray& msg);
};