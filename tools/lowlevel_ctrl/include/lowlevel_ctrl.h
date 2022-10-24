
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
#include <std_msgs/Int64.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <eigen3/Eigen/Geometry>
#include <can_msgs/Frame.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/VehicleSCC.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>

#include <hmcl_msgs/BehaviorFactor.h>
#include <hmcl_msgs/TransitionCondition.h>

#include <dynamic_reconfigure/server.h>
#include <lowlevel_ctrl/testConfig.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/String.h>
#define PI 3.14159265358979323846264338


enum struct DrivingState {Parking = 0, DrivingStop = 1, Driving = 2, EmergencyStop = 3}; 




inline const char* stateToString(DrivingState v)
{
    switch (v)
    {
        case DrivingState::Parking:   return "Parking";        
        case DrivingState::DrivingStop:   return "DrivingStop";
        case DrivingState::Driving: return "Driving";
        case DrivingState::EmergencyStop: return "EmergencyStop";
        default:      return "[Unknown DrivingState]";
    }
}


class LowlevelCtrl 
{  
private:
ros::NodeHandle nh_can_, nh_acc_, nh_steer_, nh_light_;
std::mutex mtx_;
ros::Subscriber AcanSub, CcanSub, emergency_stopSub, gnssPoseSub, missionStatisSub, lightSub;
ros::Subscriber SteeringCmdSub, AccCmdSub, ShiftCmdSub, LightCmdSub, VelSub, SCCmdSub, setpointSub;
ros::Publisher  driving_pub, AcanPub, CcanPub, statusPub, sccPub, steerPub, wheelPub ;

hmcl_msgs::BehaviorFactor behav_msg;

dynamic_reconfigure::Server<lowlevel_ctrl::testConfig> srv;
dynamic_reconfigure::Server<lowlevel_ctrl::testConfig>::CallbackType f;
DrivingState drivingState;

// boost::mutex optimizedStateMutex_;
bool Acan_recv_status;
bool Ccan_recv_status;
bool emergency_stop_activate;
int emergency_count;

unsigned int light_on;
double target_vel;
bool scc_overwrite;

hmcl_msgs::VehicleStatus vehicle_status_;
hmcl_msgs::VehicleSCC scc_info_;
hmcl_msgs::VehicleSteering steering_info_;
hmcl_msgs::VehicleWheelSpeed wheel_info_;
hmcl_msgs::VehicleGear gear_info_;

can_msgs::Frame steering_frame, scc_frame, gear_frame, light_frame;
double acc_cmd;
double gear_ratio = 15.0;
int steering_offset = 8;         

// variables for dynamic configure 
bool AD_STR_MODE_CMD, AD_SCC_TAKEOVER_CMD, AD_LEFT_TURNLAMP_STAT;
bool AD_RIGHT_TURNLAMP_STAT, AD_HAZARD_STAT;
int  AD_STR_POS_CMD, AD_SCC_ACCEL_CMD, AD_GEAR_POS_CMD, AD_SCC_MODE_CMD;    
int MODE_D = 0, MODE_P = 0, DRIVING = 0, PARKING = 0;   

float fl, fr, rl, rr, whl_speed_mean;
geometry_msgs::PoseStamped ego_pose;

ros::Time Acan_callback_time;
ros::Time Ccan_callback_time;

public:
LowlevelCtrl(ros::NodeHandle& nh_can, ros::NodeHandle& nh_acc,ros::NodeHandle& nh_steer,ros::NodeHandle& nh_light);
~LowlevelCtrl();
void InitCanmsg();
void AcanSender();
void Test();
void DrivingStateMachine();
void setToParking();
void setToDrive();
void setScc(short acc_vel);
void setSteering(short steer_value);

void missionCallback(hmcl_msgs::BehaviorFactorConstPtr msg);

void LightCallback(std_msgs::Float64ConstPtr msg);
void AcanCallback(can_msgs::FrameConstPtr acan_data);
void CcanCallback(can_msgs::FrameConstPtr ccan_data);
void gnssPoseCallback(geometry_msgs::PoseStampedConstPtr msg);
void TargetVelocityCallback(std_msgs::Float64ConstPtr msg);

void dyn_callback(lowlevel_ctrl::testConfig& config, uint32_t level);

// Vehicle commands Callbacks
void SteeringCmdCallback(hmcl_msgs::VehicleSteeringConstPtr msg);
void AccCmdCallback(hmcl_msgs::VehicleSCCConstPtr msg);
// void LightCmdCallback(std_msgs::Float64ConstPtr msg);
void controlEffortCallback(const std_msgs::Float64& control_effort_input);
void emergencyRemoteCallback(std_msgs::Float64ConstPtr msg);
};


