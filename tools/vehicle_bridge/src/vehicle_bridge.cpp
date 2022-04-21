
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


#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "vehicle_bridge.h"

using namespace std;

VehicleBridge::VehicleBridge(ros::NodeHandle& nh_can, ros::NodeHandle& nh_acc,ros::NodeHandle& nh_steer,ros::NodeHandle& nh_light):  
  nh_can_(nh_can),
  nh_acc_(nh_acc),
  nh_steer_(nh_steer),
  nh_light_(nh_light),
  can_recv_status(false) 
{
  Acan_callback_time = ros::Time::now();
  
  InitCanmsg();

  AcanSub = nh_light_.subscribe("/a_can_l2h", 100, &VehicleBridge::AcanCallback, this);
  AcanPub = nh_can.advertise<can_msgs::Frame>("/a_can_h2l", 100);
  statusPub = nh_can.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 100);    
  sccPub    = nh_can.advertise<hmcl_msgs::VehicleSCC>("/scc_info", 100);    
  steerPub  = nh_can.advertise<hmcl_msgs::VehicleSteering>("/steering_info", 100);    
  wheelPub  = nh_can.advertise<hmcl_msgs::VehicleWheelSpeed>("/wheel_info", 100);    
  // debug_pub = nh_can.advertise<std_msgs::UInt8MultiArray>("/debug_sig",10);
  SteeringCmdSub = nh_steer_.subscribe("/usafe_steer_cmd", 1, &VehicleBridge::SteeringCmdCallback, this);
  // AccCmdSub = nh_acc_.subscribe("/usafe_acc_cmd", 1, &VehicleBridge::AccCmdCallback, this);
  ShiftCmdSub = nh_light_.subscribe("/usafe_shift_cmd", 1, &VehicleBridge::ShiftCmdCallback, this);
  LightCmdSub = nh_light_.subscribe("/usafe_lights_cmd", 1, &VehicleBridge::LightCmdCallback, this);
  VelSub = nh_acc.subscribe("control_effort", 1, &VehicleBridge::controlEffortCallback, this);

  
  ROS_INFO("Init A-CAN Handler");
  boost::thread AcanHandler(&VehicleBridge::AcanSender,this); 
  boost::thread AcanWatch(&VehicleBridge::AcanWatchdog,this); 
 
  
  f = boost::bind(&VehicleBridge::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

VehicleBridge::~VehicleBridge()
{}


void VehicleBridge::AcanCallback(can_msgs::FrameConstPtr acan_data)
{ 
  can_recv_status = true;
  int msg_id = acan_data->id;  
  int a;
  
  mtx_.lock();
  Acan_callback_time = ros::Time::now();
  mtx_.unlock();
   
  double steer_d;
  switch(msg_id) {    
    case 0x600:
      mtx_.lock();
      // receive AD_STR_INFO      
      steering_info_.takeover = (unsigned int)acan_data->data[3]; //AD_STR_TAKEOVER_INFO 
      steering_info_.mode = (unsigned int)acan_data->data[0]; //AD_STR_MODE_STAT 
      steering_info_.steering_angle = ((short)((acan_data->data[2]  << 8)+acan_data->data[1])*0.1)*PI/180.0;      
      vehicle_status_.steering_info = steering_info_; 
      // a = acan_data->data[4]; //(Reserved) 
      // a = acan_data->data[5]; //AD_STR_ALIVE_COUNT 
      mtx_.unlock();
      break;

    case 0x602:
      mtx_.lock();
      // receive AD_SCC_INFO      
      vehicle_status_.header = acan_data->header;
      wheel_info_.header = acan_data->header;
      scc_info_.scc_mode = (unsigned int)acan_data->data[0]; //AD_SCC_ACT_MODE_STAT 
      scc_info_.acceleration = (short)((acan_data->data[2]  << 8)+acan_data->data[1])*0.01; 
      wheel_info_.wheel_speed = ((unsigned int)acan_data->data[3]) / 3.6; //AD_SCC_WHL_SPD_STAT  convert to m/s
      vehicle_status_.scc_info = scc_info_;
      vehicle_status_.wheelspeed = wheel_info_;
      mtx_.unlock();
      break;

    case 0x604:
      // receive AD_SHIFT_INFO
      mtx_.lock();
      vehicle_status_.auto_mode = (unsigned int)acan_data->data[0]; //AD_SHIFT_ACT_POS_STAT 
      gear_info_.gear = (unsigned int)acan_data->data[1]; //AD_SHIFT_MODE_STAT       
      vehicle_status_.gear_info = gear_info_;
      mtx_.unlock();
      break;

    case 0x606:
      // receive AD_BTN_INFO
      mtx_.lock();
      a = acan_data->data[0]; //AD_AUTO_BTN_STAT 
      a = acan_data->data[1]; //AD_EMS_BTN_STAT 
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT 
      mtx_.unlock();
      break;

    case 0x608:
    
      mtx_.lock();
      // receive TL_INFO
      a = acan_data->data[0]; //AD_HAZARD_STAT 
      a = acan_data->data[1]; //AD_RIGHT_TURNLAMP_STAT      
      mtx_.unlock(); 
      break;

    case 0x60:
      mtx_.lock();
      a = acan_data->data[0]; //AD_WIRELESS_REMOTE_BTN_STAT_1 
      a = acan_data->data[1]; //AD_WIRELESS_REMOTE_BTN_STAT_2
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT_3
      mtx_.unlock();
      // receive AD_RTE_INFO
      break;
      
    default:  
      
      return;        
  }  
  
}

void VehicleBridge::InitCanmsg(){
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;
  short steer_value = (short)(0.0) ; // input  in radian, convert into degree
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
  steering_frame.data[2] = (unsigned int)0 & 0b11111111;

  scc_frame.header.stamp = ros::Time::now();
  scc_frame.id = 0x303;
  scc_frame.dlc = 4;
  scc_frame.is_error = false;
  scc_frame.is_extended = false;
  scc_frame.is_rtr = false;
  short accel_value = (short)(0.0*100);
  scc_frame.data[0] = (unsigned int)0 & 0b11111111;
  scc_frame.data[1] = (accel_value & 0b11111111);
	scc_frame.data[2] = ((accel_value >> 8)&0b11111111);
  scc_frame.data[3] = (unsigned int)0 & 0b11111111;
  
  gear_frame.header.stamp = ros::Time::now();
  gear_frame.id = 0x304;
  gear_frame.dlc = 1;
  gear_frame.is_error = false;
  gear_frame.is_extended = false;
  gear_frame.is_rtr = false;
  gear_frame.data[0] = (unsigned int)0 & 0b11111111;  

  light_frame.header.stamp = ros::Time::now();
  light_frame.id = 0x306;
  light_frame.dlc = 3;
  light_frame.is_error = false;
  light_frame.is_extended = false;
  light_frame.is_rtr = false;
  light_frame.data[0] = (unsigned int)0 & 0b11111111;  
  light_frame.data[1] = (unsigned int)0 & 0b11111111;  
  light_frame.data[2] = (unsigned int)1 & 0b11111111;  

}
void VehicleBridge::AcanWatchdog()
{
    ros::Rate loop_rate(10); // rate  
    while (ros::ok())
    { ros::Duration duration = ros::Time::now() - Acan_callback_time;
      // ros::Duration duration_steering = ros::Time::now() - steering_frame.header.stamp;
      ros::Duration duration_accl = ros::Time::now() - scc_frame.header.stamp;
      
      // if no can msg received in 0.2 sec
      if(duration.toSec() > 0.2){        
        ROS_WARN("Acan is empty for %lf secs", duration.toSec());
        mtx_.lock();
        can_recv_status = false;
        mtx_.unlock();
      }

      // If no accerlation command for more than 0.5 sec, slow down vehicle
       if(duration_accl.toSec() > 0.5){        
        ROS_WARN("acceleration command is not arrived for %lf secs", duration_accl.toSec());
        mtx_.lock();
        short accel_value = (short)(-1*100);
        scc_frame.data[1] = (accel_value & 0b11111111);
	      scc_frame.data[2] = ((accel_value >> 8)&0b11111111);
        mtx_.unlock();
      }

     loop_rate.sleep();
    }
}

void VehicleBridge::AcanSender()
{
  ros::Rate loop_rate(50); // rate of cmd   
  while (ros::ok())
  {  
    if(can_recv_status){
      // publish vehicle info 
      steerPub.publish(steering_info_);
      statusPub.publish(vehicle_status_); 
      sccPub.publish(scc_info_);    
      wheelPub.publish(wheel_info_);  


      // publish vehicle command 
      // std_msgs::UInt8MultiArray debug_msg;
      // for(int i=0;i < 8; i++){
      //   debug_msg.data.push_back(i);
      // }
      
      // debug_pub.publish(debug_msg);
      AcanPub.publish(steering_frame);
      AcanPub.publish(scc_frame);
      AcanPub.publish(gear_frame);
      AcanPub.publish(light_frame);      
    }
    loop_rate.sleep();
  }
}

void VehicleBridge::controlEffortCallback(const std_msgs::Float64& control_effort_input)
{
  // the stabilizing control effort
  control_effort = round(control_effort_input.data *100)/100;
  scc_frame.header.stamp = ros::Time::now();
  scc_frame.id = 0x303;
  scc_frame.dlc = 4;
  scc_frame.is_error = false;
  scc_frame.is_extended = false;
  scc_frame.is_rtr = false;
  short accel_value = (short)(control_effort*100);
  scc_frame.data[0] = (unsigned int)AD_SCC_MODE_CMD & 0b11111111;
  scc_frame.data[1] = (accel_value & 0b11111111);
	scc_frame.data[2] = ((accel_value >> 8)&0b11111111);
  scc_frame.data[3] = (unsigned int)AD_SCC_TAKEOVER_CMD & 0b11111111;
  // cout << control_effort << endl;
}

void VehicleBridge::SteeringCmdCallback(hmcl_msgs::VehicleSteeringConstPtr msg){
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;
  short steer_value = (short)(msg->steering_angle*10*180/PI) ; // input  in radian, convert into degree
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
  steering_frame.data[2] = (unsigned int)msg->mode & 0b11111111;
}

void VehicleBridge::AccCmdCallback(hmcl_msgs::VehicleSCCConstPtr msg){
  scc_frame.header.stamp = ros::Time::now();
  scc_frame.id = 0x303;
  scc_frame.dlc = 4;
  scc_frame.is_error = false;
  scc_frame.is_extended = false;
  scc_frame.is_rtr = false;
  short accel_value = (short)(msg->acceleration*100);
  scc_frame.data[0] = (unsigned int)msg->scc_mode & 0b11111111;
  scc_frame.data[1] = (accel_value & 0b11111111);
	scc_frame.data[2] = ((accel_value >> 8)&0b11111111);
  scc_frame.data[3] = (unsigned int)msg->scc_takeover & 0b11111111;
  
}

void VehicleBridge::ShiftCmdCallback(hmcl_msgs::VehicleGearConstPtr msg){
  gear_frame.header.stamp = ros::Time::now();
  gear_frame.id = 0x304;
  gear_frame.dlc = 1;
  gear_frame.is_error = false;
  gear_frame.is_extended = false;
  gear_frame.is_rtr = false;
  gear_frame.data[0] = (unsigned int)msg->gear & 0b11111111;  
}
void VehicleBridge::LightCmdCallback(hmcl_msgs::VehicleLightConstPtr msg){
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



void VehicleBridge::dyn_callback(vehicle_bridge::testConfig &config, uint32_t level)
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
  Master_Switch         = config.Master_Switch;
  
  AD_STR_MODE_CMD       = config.AD_STR_MODE_CMD;
  AD_STR_POS_CMD        = config.AD_STR_POS_CMD;
  AD_SCC_ACCEL_CMD      = config.AD_SCC_ACCEL_CMD;
  AD_SCC_TAKEOVER_CMD   = config.AD_SCC_TAKEOVER_CMD;
  AD_LEFT_TURNLAMP_STAT = config.AD_LEFT_TURNLAMP_STAT;
  AD_RIGHT_TURNLAMP_STAT= config.AD_RIGHT_TURNLAMP_STAT;
  AD_HAZARD_STAT        = config.AD_HAZARD_STAT;
  AD_GEAR_POS_CMD       = config.AD_GEAR_POS_CMD;
  AD_SCC_MODE_CMD       = config.AD_SCC_MODE_CMD;

  if(Master_Switch){
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  short steer_value = (short)(AD_STR_POS_CMD*10) ; // input  in radian, convert into degree
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
  steering_frame.data[2] = (unsigned int)AD_STR_MODE_CMD & 0b11111111;

  // scc_frame.header.stamp = ros::Time::now();
  // scc_frame.id = 0x303;
  // scc_frame.dlc = 4;
  // short accel_value = (short)(AD_SCC_ACCEL_CMD*100);
  // scc_frame.data[0] = (unsigned int)AD_SCC_MODE_CMD & 0b11111111;
  // scc_frame.data[1] = (accel_value & 0b11111111);
	// scc_frame.data[2] = ((accel_value >> 8)&0b11111111);
  // scc_frame.data[3] = (unsigned int)AD_SCC_TAKEOVER_CMD & 0b11111111;

  gear_frame.header.stamp = ros::Time::now();
  gear_frame.id = 0x304;
  gear_frame.dlc = 1;
  gear_frame.data[0] = (unsigned int)AD_GEAR_POS_CMD & 0b11111111; 

  

  }
  // cout << AD_STR_MODE_CMD << endl;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "VehicleBridge");
  
  

  ros::NodeHandle nh_can, nh_acc, nh_steer, nh_light;
  VehicleBridge VehicleBridge_(nh_can,nh_acc,nh_steer,nh_light);

  ros::CallbackQueue callback_queue_can, callback_queue_acc, callback_queue_steer, callback_queue_light;
  nh_can.setCallbackQueue(&callback_queue_can);
  nh_acc.setCallbackQueue(&callback_queue_acc);
  nh_steer.setCallbackQueue(&callback_queue_steer);
  nh_light.setCallbackQueue(&callback_queue_light);

  std::thread spinner_thread_can([&callback_queue_can]() {
    ros::SingleThreadedSpinner spinner_can;
    spinner_can.spin(&callback_queue_can);
  });

  std::thread spinner_thread_acc([&callback_queue_acc]() {
    ros::SingleThreadedSpinner spinner_acc;
    spinner_acc.spin(&callback_queue_acc);
  });

  std::thread spinner_thread_steer([&callback_queue_steer]() {
    ros::SingleThreadedSpinner spinner_steer;
    spinner_steer.spin(&callback_queue_steer);
  });

  std::thread spinner_thread_light([&callback_queue_light]() {
    ros::SingleThreadedSpinner spinner_light;
    spinner_light.spin(&callback_queue_light);
  });


    ros::spin();

    spinner_thread_can.join();
    spinner_thread_acc.join();
    spinner_thread_steer.join();
    spinner_thread_light.join();


  return 0;

}
