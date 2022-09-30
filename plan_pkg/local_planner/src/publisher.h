#include <ros/ros.h>
#include <tf/tf.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

using namespace std;

class Publisher
{
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_traj;
    ros::Subscriber sub_traj;
    // ros::Timer timer_;

    float pos_x, pos_y, pos_z;

public:
    Publisher(ros::NodeHandle& nh_);
    ~Publisher();
    
    void connect_handler(const ros::TimerEvent& time);
    void trajCallback(const hmcl_msgs::LaneArray& lane_msg);

};