#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <algorithm>
#include <nav_msgs/Odometry.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>

#include <std_msgs/Int16.h>
#include <std_msgs/ColorRGBA.h>

#include <v2x_msgs/SPAT.h>
#include <v2x_msgs/SPATdata.h>
#include <v2x_msgs/Mission1.h>
#include <v2x_msgs/Mission2.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;

class V2X_viz
{

private:
    ros::NodeHandle nh_;
    ros::Publisher viz_spat, viz_mission1, viz_mission2;

    ros::Subscriber sub_spat, sub_mission1, sub_mission2;
    ros::Timer timer_;

    bool spat_flag = false;
    bool mission1_flag = false;
    bool mission2_flag = false;

    visualization_msgs::MarkerArray spat_marker_array, mission1_marker_array, mission2_marker_array;


public:
    V2X_viz(ros::NodeHandle& nh_);
    ~V2X_viz();

    void connect_handler(const ros::TimerEvent& time);
    void spatCallback(const v2x_msgs::SPAT& msg);
    void mission1Callback(const v2x_msgs::Mission1& msg);
    void mission2Callback(const v2x_msgs::Mission2& msg);

};