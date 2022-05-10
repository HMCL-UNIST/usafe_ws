
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

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <eigen3/Eigen/Geometry>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/VehicleSCC.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/Lane.h>
#include <carla_msgs/CarlaEgoVehicleStatus.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include <dynamic_reconfigure/server.h>
#include <preview_ctrl/testConfig.h>
#include "vehicle_model_dynamics.h"
#include <std_msgs/UInt8MultiArray.h>



#define PI 3.14159265358979323846264338


class PreviewCtrl 
{  
private:
ros::NodeHandle nh_ctrl_, nh_traj_;



std::mutex mtx_;
ros::Subscriber poseSub, waypointSub, vehicleStatusSub, odomSub;
ros::Publisher  steerPub;


  
dynamic_reconfigure::Server<preview_ctrl::testConfig> srv;
dynamic_reconfigure::Server<preview_ctrl::testConfig>::CallbackType f;

VehicleModel VehicleModel_;


int delay_step;
double delay_in_sec, lag_tau;
double Q_ey, Q_eydot, Q_epsi, Q_epsidot, R_weight;

double Vx;

double dt, wheelbase, lf, lr, mass;

double Vx_test = 0.0;

std::string control_topic, pose_topic, vehicle_status_topic, waypoint_topic, odom_topic;

hmcl_msgs::VehicleStatus vehicle_status_;
hmcl_msgs::VehicleSCC scc_info_;
hmcl_msgs::VehicleSteering steering_info_;
hmcl_msgs::VehicleWheelSpeed wheel_info_;
hmcl_msgs::VehicleGear gear_info_;






public:
PreviewCtrl(ros::NodeHandle& nh_ctrl, ros::NodeHandle& nh_traj);
~PreviewCtrl();
void ControlLoop();
void PoseCallback(geometry_msgs::PoseStampedConstPtr pose_msg);
void WaypointCallback(hmcl_msgs::LaneConstPtr waypoints_msg);
void VehicleStatusCallback(carla_msgs::CarlaEgoVehicleStatusConstPtr status_msg);
void odomCabllback(nav_msgs::OdometryConstPtr odom_msg);




void dyn_callback(preview_ctrl::testConfig& config, uint32_t level);



};



