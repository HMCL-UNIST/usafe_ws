#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <algorithm>
#include "spline.h"
#include <nav_msgs/Odometry.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

#include <std_msgs/Int16.h>
#include <std_msgs/ColorRGBA.h>
#include <hmcl_msgs/VehicleStatus.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

void setColor(std_msgs::ColorRGBA* cl, double r, double g, double b, double a)
{
  cl->r = r;
  cl->g = g;
  cl->b = b;
  cl->a = a;
}

class lirplanner
{

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_lir, pub_viz;
    ros::Subscriber sub_global, sub_pos;
    ros::Timer timer_;

    bool pose_init = false;
    bool lir_available = false;

    int previous_idx = 0; 
    int current_id = -1;
    double max_dist = 3000;


    std::vector<int> global_index;

    geometry_msgs::Pose cur_pose;
    hmcl_msgs::LaneArray global_lane, lir_array;
    visualization_msgs::MarkerArray lir_marker_array;

public:
    lirplanner(ros::NodeHandle& nh_);
    ~lirplanner();
    
    void connect_handler(const ros::TimerEvent& time);

    void poseCallback(const nav_msgs::OdometryConstPtr& msg);
    void globalCallback(const hmcl_msgs::LaneArray& lane_msg);
    void lane_in_range();
    void viz_lir(hmcl_msgs::LaneArray &lanes);
    void findnearest_lane_and_point_idx(const hmcl_msgs::LaneArray &lanes, geometry_msgs::Pose& point_, int &closest_lane_idx, int &closest_point_idx);
    bool calculate_distance_(hmcl_msgs::Waypoint &wp1, hmcl_msgs::Waypoint &wp2, double &dist, double &dist_cum);

};