
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
#include <numeric>
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <eigen3/Eigen/Geometry>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <can_msgs/Frame.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/VehicleSCC.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/CtrlVehicleStates.h>
#include <carla_msgs/CarlaEgoVehicleStatus.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include <dynamic_reconfigure/server.h>
#include <preview_ctrl/testConfig.h>
#include "vehicle_model_dynamics.h"
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/Float64.h>
#include "lowpass_filter.h"
#include "trajectory.h"
#include "utils.h"
#include "polyfit.h"


#define PI 3.14159265358979323846264338


class PreviewCtrl 
{  
private:
ros::NodeHandle nh_ctrl_, nh_traj_;

struct VehicleStatus
{
std_msgs::Header header;    //< @brief header
geometry_msgs::Pose pose;   //< @brief vehicle pose
geometry_msgs::Twist twist; //< @brief vehicle velocity
double tire_angle_rad;      //< @brief vehicle tire angle
};
VehicleStatus vehicle_status_; //< @brief vehicle status

bool my_steering_ok_,my_position_ok_, my_odom_ok_;
double angle_rate_limit, prev_delta_cmd;   
std::mutex mtx_;
ros::Subscriber poseSub, waypointSub, vehicleStatesSub, odomSub, StatusSub, simStatusSub;
ros::Publisher  velPub, ackmanPub, steerPub, pub_debug_filtered_traj_, debugPub, AcanPub;

Trajectory traj_;
hmcl_msgs::Lane current_waypoints_;

dynamic_reconfigure::Server<preview_ctrl::testConfig> srv;
dynamic_reconfigure::Server<preview_ctrl::testConfig>::CallbackType f;

VehicleModel VehicleModel_;
std::vector<double> delta_buffer;
int path_filter_moving_ave_num_, curvature_smoothing_num_, path_smoothing_times_;


int delay_step, preview_step;
double delay_in_sec, lag_tau;
double Q_ey, Q_eydot, Q_epsi, Q_epsidot, R_weight;

double Vx;

double dt, wheelbase, lf, lr, mass;
 geometry_msgs::PoseStamped debug_msg;
double debug_yaw;

double error_deriv_lpf_curoff_hz;
std::string vel_cmd_topic, control_topic, pose_topic, vehicle_states_topic, waypoint_topic, odom_topic, status_topic, simstatus_topic, steer_cmd_topic;

Butterworth2dFilter lpf_lateral_error_;
Butterworth2dFilter lpf_yaw_error_; 
Butterworth2dFilter lpf_ey; 
Butterworth2dFilter lpf_epsi; 
Butterworth2dFilter steer_filter; 

int steering_offset = 8;
bool state_received;
ros::Time state_time, prev_state_time;

Eigen::VectorXd Xk, Cr;
double prev_ey, prev_epsi;

bool config_switch;

public:
PreviewCtrl(ros::NodeHandle& nh_ctrl, ros::NodeHandle& nh_traj);
~PreviewCtrl();
void ControlLoop();


// void callbackPose(const geometry_msgs::PoseStampedConstPtr& msg);
void simstatusCallback(const carla_msgs::CarlaEgoVehicleStatusConstPtr& msg);
void statusCallback(const hmcl_msgs::VehicleStatusConstPtr& msg);
void odomCallback(const nav_msgs::OdometryConstPtr& msg);
void callbackRefPath(const hmcl_msgs::Lane::ConstPtr &msg);
bool stateSetup();

void reschedule_weight(double speed);
void steering_rate_reset(double speed);

void convertTrajToMarker(const Trajectory &traj, visualization_msgs::Marker &marker,
                                      std::string ns, double r, double g, double b, double z);

void dyn_callback(preview_ctrl::testConfig& config, uint32_t level);


};



