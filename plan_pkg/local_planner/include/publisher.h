#include <ros/ros.h>
#include <tf/tf.h>

#include <nav_msgs/Odometry.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/WaypointArray.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;

class Publisher
{
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_traj, pub_viz;
    ros::Subscriber sub_traj, sub_global, sub_pos;
    // ros::Timer timer_;

    bool pr_flag = false;
    double current_x, current_y, current_vel;
    hmcl_msgs::LaneArray global_lane;
    vector<int> global_index, range_index, global_change;

public:
    Publisher(ros::NodeHandle& nh_);
    ~Publisher();
    
    void connect_handler(const ros::TimerEvent& time);
    
    void poseCallback(const nav_msgs::Odometry& state_msg);
    void trajCallback(const hmcl_msgs::LaneArray& lane_msg);
    void globalCallback(const hmcl_msgs::LaneArray& lane_msg);

    hmcl_msgs::Lane cuttraj(const hmcl_msgs::Lane& msg);
    void viz_local(const hmcl_msgs::Lane& msg);

};