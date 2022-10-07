#include "ros/ros.h"
#include <cmath>
#include <tf/tf.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

#include <std_msgs/String.h>

#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <std_msgs/Int16.h>
#include <sensor_msgs/NavSatFix.h>

#include <ros/spinner.h>
#include <ros/callback_queue.h>

#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/VehicleGear.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include "hmcl_v2x/HMCL_PVD.h"
#include "hmcl_v2x/Reply.h"

using namespace std;

class V2XPvd
{
private:
    ros::NodeHandle nh_, nh_local_;
    ros::Publisher pub_pvd;
    ros::Subscriber sub_pos, sub_dir, sub_veh;

    ros::Timer timer_;

    float lat_c = 0.0;
    float lon_c = 0.0;
    float alt_c = 0.0;
    float dir_c = 0.0;
    float vel_c = 0.0;
    int gear_c = 0;


public:
    V2XPvd(ros::NodeHandle& nh_, ros::NodeHandle& nh_local_);
    ~V2XPvd();

    void connect_handler(const ros::TimerEvent& time);

    void pos_callback(const sensor_msgs::NavSatFix::ConstPtr& nav_data);
    void dir_callback(const std_msgs::Float64::ConstPtr& dir_data);
    void veh_callback(const hmcl_msgs::VehicleStatus::ConstPtr& veh_data);
    void publisher();

};

