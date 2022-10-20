
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


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>
#include <cstdlib>


#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "lowlevel_ctrl.h"

using namespace std;

void LowlevelCtrl::LightCmdCallback(hmcl_msgs::VehicleLightConstPtr msg){
  light_frame.header.stamp = ros::Time::now();
  light_frame.id = 0x306;
  light_frame.dlc = 3;
  light_frame.is_error = false;
  light_frame.is_extended = false;
  light_frame.is_rtr = false;
  light_frame.data[0] = (unsigned int)msg->left_light & 0b11111111;  
  light_frame.data[1] = (unsigned int)msg->right_light & 0b11111111;  
  light_frame.data[2] = (unsigned int)msg->hazard_light & 0b11111111;  
}

void LowlevelCtrl::TargetVelocityCallback(std_msgs::Float64ConstPtr msg){
  target_vel = msg->data;
}
  
void LowlevelCtrl::dyn_callback(lowlevel_ctrl::testConfig &config, uint32_t level)
{
  ROS_INFO("Reconfigure Request: \n AD_STR_MODE_CMD: %s,\n AD_STR_POS_CMD: %d,\n AD_SCC_ACCEL_CMD: %d,\n AD_SCC_TAKEOVER_CMD: %s,\n AD_LEFT_TURNLAMP_STAT: %s,\n AD_RIGHT_TURNLAMP_STAT: %s,\n AD_HAZARD_STAT: %s,\n AD_GEAR_POS_CMD: %d,\n AD_SCC_MODE_CMD: %d,\n",
  config.AD_STR_MODE_CMD?"True":"False", 
  config.AD_STR_POS_CMD,
  config.AD_SCC_ACCEL_CMD, 
  config.AD_SCC_TAKEOVER_CMD?"True":"False",
  config.AD_LEFT_TURNLAMP_STAT?"True":"False",
  config.AD_RIGHT_TURNLAMP_STAT?"True":"False",
  config.AD_HAZARD_STAT?"True":"False",
  config.AD_GEAR_POS_CMD,
  config.AD_SCC_MODE_CMD);

}

void LowlevelCtrl::SteeringCmdCallback(hmcl_msgs::VehicleSteeringConstPtr msg){  
  mtx_.lock();
  short steer_value = (short)((msg->steering_angle)*gear_ratio*180/PI*10)+steering_offset;
  setSteering(steer_value);    
  mtx_.unlock();
}

void LowlevelCtrl::controlEffortCallback(const std_msgs::Float64& control_effort_input)
{
  float control_data = control_effort_input.data;
  if(control_data > -5.0 && control_data < 3.0){

  
  if(drivingState == DrivingState::Driving && scc_overwrite == false) {
      mtx_.lock();
      if(gear_info_.gear == 0){
        setScc(0);
      }else{
      double ctrl_effort;
      ctrl_effort = round(control_effort_input.data *100)/100;      
      short target_accel = (ctrl_effort*100);       
      setScc(target_accel);
      ROS_INFO("control effort callback");
      }      
      mtx_.unlock();
  }   

  }else{
    ROS_WARN("Invalid control effort");
  }
  
}

void LowlevelCtrl::LightCallback(std_msgs::Float64ConstPtr msg){  
  return;
  light_frame.header.stamp = ros::Time::now();
  light_frame.id = 0x306;
  light_frame.dlc = 3;
  light_frame.is_error = false;
  light_frame.is_extended = false;
  light_frame.is_rtr = false;
  if(msg->data >= 1){
    light_frame.data[0] = (unsigned int)0 & 0b11111111;  
    light_frame.data[1] = (unsigned int)1 & 0b11111111;    
    light_frame.data[2] = (unsigned int)0 & 0b11111111;  
  }else if(msg->data == 0.0 ){
    light_frame.data[0] = (unsigned int)0 & 0b11111111;  
    light_frame.data[1] = (unsigned int)0 & 0b11111111;    
    light_frame.data[2] = (unsigned int)0 & 0b11111111;  
  }else if(msg->data <= -1){
    light_frame.data[0] = (unsigned int)1 & 0b11111111;  
    light_frame.data[1] = (unsigned int)0 & 0b11111111;    
    light_frame.data[2] = (unsigned int)0 & 0b11111111;    
  }else{
    light_frame.data[0] = (unsigned int)0 & 0b11111111;  
    light_frame.data[1] = (unsigned int)0 & 0b11111111;    
    light_frame.data[2] = (unsigned int)1 & 0b11111111;    
  }
  
  
}

void LowlevelCtrl::emergencyRemoteCallback(std_msgs::Float64ConstPtr msg){
    int thres = 5;
    if(msg->data > 0.5){
      emergency_count++;
    }else{
      emergency_count--;
    }
    
    if(emergency_count > thres){
      emergency_stop_activate = true;  
      mtx_.lock();   
      drivingState = DrivingState::EmergencyStop;         
      mtx_.unlock();
    }else{
      emergency_stop_activate = false;            
    }
    
    if( emergency_count > thres*10 ){
      emergency_count = thres+1;
    }
    if(emergency_count < 0 ){
      emergency_count = 0;
    }
}

void LowlevelCtrl::AcanCallback(can_msgs::FrameConstPtr acan_data)
{ 
  Acan_recv_status = true;
  int msg_id = acan_data->id;  
  int a;  
  Acan_callback_time = ros::Time::now();
  double steer_d;  
  float lat_acc, long_acc, yaw_rate;
  switch(msg_id) {    
    case 0x600:      
      // receive AD_STR_INFO      
      steering_info_.header = acan_data->header;
      steering_info_.takeover = (unsigned int)acan_data->data[3]; //AD_STR_TAKEOVER_INFO 
      steering_info_.mode = (unsigned int)acan_data->data[0]; //AD_STR_MODE_STAT 
      steering_info_.steering_angle = (((short)((acan_data->data[2]  << 8)+acan_data->data[1]-steering_offset)*0.1)*PI/180.0)/gear_ratio;      
      vehicle_status_.steering_info = steering_info_; 
      // a = acan_data->data[4]; //(Reserved) 
      // a = acan_data->data[5]; //AD_STR_ALIVE_COUNT       
      break;

    case 0x602:      
      // receive AD_SCC_INFO      
      vehicle_status_.header = acan_data->header;
      // wheel_info_.header = acan_data->header;
      scc_info_.header = acan_data->header;
      scc_info_.scc_mode = (unsigned int)acan_data->data[0]; //AD_SCC_ACT_MODE_STAT 
      scc_info_.acceleration = (short)((acan_data->data[2]  << 8)+acan_data->data[1])*0.01;       
      vehicle_status_.scc_info = scc_info_;
      // vehicle_status_.wheelspeed = wheel_info_;
      
      break;

    case 0x604:
      // receive AD_SHIFT_INFO      
      gear_info_.gear = (unsigned int)acan_data->data[0]; //AD_SHIFT_MODE_STAT       
      vehicle_status_.auto_mode = (unsigned int)acan_data->data[1]; //AD_SHIFT_ACT_POS_STAT       
      vehicle_status_.gear_info = gear_info_;      
      break;

    case 0x606:
      // receive AD_BTN_INFO      
      a = acan_data->data[0]; //AD_AUTO_BTN_STAT 
      a = acan_data->data[1]; //AD_EMS_BTN_STAT 
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT       
      break;

    case 0x608:         
      // receive TL_INFO
      // left_light_on = (unsigned int)acan_data->data[0]; //AD_HAZARD_STAT 
      // 1 left 2 right
      light_on = (unsigned int)acan_data->data[1]; //AD_RIGHT_TURNLAMP_STAT  
      if(light_on == 1){
        vehicle_status_.light_info.left_light = 1;
      }else{
        vehicle_status_.light_info.left_light = 0;
      }
      if(light_on == 2){
        vehicle_status_.light_info.right_light = 1;
      }else{
        vehicle_status_.light_info.right_light = 0;
      }      
      // light_frame.data[2] = (unsigned int)msg->hazard_light & 0b11111111;            
      break;

    case 0x60:      
     // not using anymore
      a = acan_data->data[0]; //AD_WIRELESS_REMOTE_BTN_STAT_1 
      a = acan_data->data[1]; //AD_WIRELESS_REMOTE_BTN_STAT_2
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT_3      
      // receive AD_RTE_INFO
      break;

      //////////////////////  C can pass

       case 0x220:
      // mtx_.lock();
      // receive AD_ACCEL & YAW RATE 
      lat_acc = ((unsigned int)(acan_data->data[0] + ((acan_data->data[1] & 0b00000111) << 8)))*0.01-10.03;
      long_acc = ((unsigned int)(((acan_data->data[1] & 0b11100000) >> 5) + (acan_data->data[2] << 3)))*0.01-10.40;
      yaw_rate = ((unsigned int)(acan_data->data[5] + ((acan_data->data[6] & 0b00011111) << 8)))*0.01 - 41.55;           
      // vehicle_status_.y_acceleration = clamp(lat_acc, -10.23, 10.24);
      // vehicle_status_.x_acceleration = clamp(long_acc, -10.23, 10.24);
      // vehicle_status_.yaw_rate = clamp(yaw_rate, -40.95, 40.96);
      vehicle_status_.y_acceleration = lat_acc;
      vehicle_status_.x_acceleration =long_acc;
      vehicle_status_.yaw_rate = yaw_rate;
      // mtx_.unlock();
      break;

    case 0x386:
      // mtx_.lock();
      // receive WHL_SPEED      
      wheel_info_.header = acan_data->header;
      fl = ((unsigned int)(acan_data->data[0] + ((acan_data->data[1] & 0b00111111) << 8)))*0.03125; // whl speed front left
      fr = ((unsigned int)(acan_data->data[2] + ((acan_data->data[3] & 0b00111111) << 8)))*0.03125; // whl speed front right
      rl = ((unsigned int)(acan_data->data[4] + ((acan_data->data[5] & 0b00111111) << 8)))*0.03125; // whl speed rear left
      rr = ((unsigned int)(acan_data->data[6] + ((acan_data->data[7] & 0b00111111) << 8)))*0.03125; // whl speed rear right
      
      wheel_info_.wheel_speed = ((fl+fr+rl+rr)/4)/3.6; // m/s
      wheel_info_.fl = fl;
      wheel_info_.fr = fr;
      wheel_info_.rr = rr;
      wheel_info_.rl = rl;
      vehicle_status_.wheelspeed = wheel_info_;
      
      // mtx_.unlock();
      break;

      
    default:        
      return;        
  }  
  
}

void LowlevelCtrl::CcanCallback(can_msgs::FrameConstPtr ccan_data)
{
  Ccan_recv_status = true;
  int msg_id = ccan_data->id;    
  float lat_acc, long_acc, yaw_rate;
  // mtx_.lock();
  Ccan_callback_time = ros::Time::now();
  // mtx_.unlock();
   
  switch(msg_id) {    
    case 0x220:
      // mtx_.lock();
      // receive AD_ACCEL & YAW RATE 
      lat_acc = ((unsigned int)(ccan_data->data[0] + ((ccan_data->data[1] & 0b00000111) << 8)))*0.01-10.03;
      long_acc = ((unsigned int)(((ccan_data->data[1] & 0b11100000) >> 5) + (ccan_data->data[2] << 3)))*0.01-10.40;
      yaw_rate = ((unsigned int)(ccan_data->data[5] + ((ccan_data->data[6] & 0b00011111) << 8)))*0.01 - 41.55;           
      // vehicle_status_.y_acceleration = clamp(lat_acc, -10.23, 10.24);
      // vehicle_status_.x_acceleration = clamp(long_acc, -10.23, 10.24);
      // vehicle_status_.yaw_rate = clamp(yaw_rate, -40.95, 40.96);
      vehicle_status_.y_acceleration = lat_acc;
      vehicle_status_.x_acceleration =long_acc;
      vehicle_status_.yaw_rate = yaw_rate;
      // mtx_.unlock();
      break;

    case 0x386:
      // mtx_.lock();
      // receive WHL_SPEED      
      wheel_info_.header = ccan_data->header;
      fl = ((unsigned int)(ccan_data->data[0] + ((ccan_data->data[1] & 0b00111111) << 8)))*0.03125; // whl speed front left
      fr = ((unsigned int)(ccan_data->data[2] + ((ccan_data->data[3] & 0b00111111) << 8)))*0.03125; // whl speed front right
      rl = ((unsigned int)(ccan_data->data[4] + ((ccan_data->data[5] & 0b00111111) << 8)))*0.03125; // whl speed rear left
      rr = ((unsigned int)(ccan_data->data[6] + ((ccan_data->data[7] & 0b00111111) << 8)))*0.03125; // whl speed rear right
      
      wheel_info_.wheel_speed = ((fl+fr+rl+rr)/4)/3.6; // m/s
      wheel_info_.fl = fl;
      wheel_info_.fr = fr;
      wheel_info_.rr = rr;
      wheel_info_.rl = rl;
      vehicle_status_.wheelspeed = wheel_info_;
      
      // mtx_.unlock();
      break;
      
    default:        
      return;        
  }  
}

void LowlevelCtrl::gnssPoseCallback(geometry_msgs::PoseStampedConstPtr msg){
 ego_pose = *msg;
}
