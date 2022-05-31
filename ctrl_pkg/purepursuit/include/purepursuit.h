
//   Copyright (c) 2022 Ulsan National Institute of Science and Technology (UNIST)
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

//   Authour : Hojin Lee, hojinlee@unist.ac.kr

#include <sstream>
#include <string>
#include <list>
#include <queue>
#include <mutex> 
#include <thread> 
#include <boost/thread/thread.hpp>
#include <vector>
#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Quaternion.h>
#include <eigen3/Eigen/Geometry>
#include <can_msgs/Frame.h>
// #include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf_conversions/tf_eigen.h>
#include <Eigen/Dense>

#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/VehicleSCC.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

#include <eigen_conversions/eigen_msg.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/transform_datatypes.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <iostream>
#ifdef __cplusplus
extern "C"
{
#endif

#include "dubins.h"
#ifdef __cplusplus
}
#endif
#define PI 3.14159265358979323846264338

using namespace std;

class PurePursuit 
{
   private:
    ros::NodeHandle nh_;
    std::mutex mtx_;
    ros::Subscriber local_traj_sub, pose_sub, cross_track_err_sub,
                    vel_cmd_sub, curvature_sub;
    ros::Publisher  steer_pub;
    DubinsPath dubins_path;
    // hmcl_msgs::Lane 
    geometry_msgs::Point closest_waypoint;
    geometry_msgs::Point desired_waypoint;
    geometry_msgs::Point fixed_waypoint;
    geometry_msgs::Point state;
    geometry_msgs::Quaternion quat_msg;
    std_msgs::Float64 steer_cmd;
    tf::Quaternion quat;
    
    hmcl_msgs::Lane ref_path;
    vector<double> curvature; 
    double gear_ratio = 14.5;
    double distance = 0;
    double cross_track_err = 0;
    int minElementIndex = 0;
    double Lf = 0;
    double steerCmd = 0; 
    // PP variables
    float vel_cmd;
    float r_min_v;
    // PP tunning param
    const float turning_radius = 5.6;
    const float e_MAX = 0;
    const float f_MAX = 0.4;
    const float alpha_MAX = 5.0;
    const float beta_MAX = 0.2;
    const float L = 2.6; 
    ros::Time Acan_callback_time;
    ros::Time Ccan_callback_time;

public:
    PurePursuit(ros::NodeHandle& nh_);
    ~PurePursuit();

    void ctrlPub(); 
    void poseCallback(const geometry_msgs::PoseStamped& pose);
    void trajCallback(const hmcl_msgs::Lane& traj);
    void curvCallback(const std_msgs::Float64MultiArray& msg);
    void cteCallback(const std_msgs::Float64& cte);
    void velcmdCallback(const hmcl_msgs::VehicleWheelSpeed& msg);

    void selectDesiredPoint();
    void selectOutOfPath();
};



