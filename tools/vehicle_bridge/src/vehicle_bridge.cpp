
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
#include <ros/ros.h>

// #include <vehicle_bridge/test.h>

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "vehicle_bridge.h"

using namespace std;
unsigned int AD_STR_MODE_CMD;
short AD_STR_POS_CMD;
short AD_SCC_ACCEL_CMD;
unsigned int AD_SCC_TAKEOVER_CMD;
unsigned int AD_LEFT_TURNLAMP_STAT;
unsigned int AD_RIGHT_TURNLAMP_STAT;
unsigned int AD_HAZARD_STAT;
unsigned int AD_GEAR_POS_CMD;
unsigned int AD_SCC_MODE_CMD;

VehicleBridge::VehicleBridge(ros::NodeHandle& nh_can, ros::NodeHandle& nh_acc,ros::NodeHandle& nh_steer,ros::NodeHandle& nh_light):  
  nh_can_(nh_can),
  nh_acc_(nh_acc),
  nh_steer_(nh_steer),
  nh_light_(nh_light),
  can_recv_status(false) 
{
  Acan_callback_time = ros::Time::now();
  
  AcanSub = nh_can.subscribe("/a_can_l2h", 100, &VehicleBridge::AcanCallback, this);
  AcanPub = nh_can.advertise<can_msgs::Frame>("/a_can_h2l", 1);

  statusPub = nh_can.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 1);    
  sccPub    = nh_can.advertise<hmcl_msgs::VehicleSCC>("/scc_info", 1);    
  steerPub  = nh_can.advertise<hmcl_msgs::VehicleSteering>("/steering_info", 1);    
  wheelPub  = nh_can.advertise<hmcl_msgs::VehicleWheelSpeed>("/wheel_info", 1);    
  
  SteeringCmdSub = nh_steer_.subscribe("/usafe_steer_cmd", 1, &VehicleBridge::SteeringCmdCallback, this);
  AccCmdSub = nh_acc_.subscribe("/usafe_acc_cmd", 1, &VehicleBridge::AccCmdCallback, this);
  ShiftCmdSub = nh_light_.subscribe("/usafe_shift_cmd", 1, &VehicleBridge::ShiftCmdCallback, this);
  LightCmdSub = nh_light_.subscribe("/usafe_lights_cmd", 1, &VehicleBridge::LightCmdCallback, this);

  ROS_INFO("Init A-CAN Handler");
  boost::thread AcanHandler(&VehicleBridge::AcanSender,this); 
  boost::thread AcanWatch(&VehicleBridge::AcanWatchdog,this); 
  
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
      steering_info_.steering_angle = (short)((acan_data->data[2]  << 8)+acan_data->data[1])*0.1;      
      // a = acan_data->data[4]; //(Reserved) 
      // a = acan_data->data[5]; //AD_STR_ALIVE_COUNT 
      mtx_.unlock();
      break;

    case 0x602:
      mtx_.lock();
    
      // receive AD_SCC_INFO
      scc_info_.scc_mode = (unsigned int)acan_data->data[0]; //AD_SCC_ACT_MODE_STAT 
      scc_info_.acceleration = (int)(acan_data->data[1] + (acan_data->data[2] << 8))*0.01; //AD_SCC_SPD_STAT 
      scc_info_.kph = (unsigned int)acan_data->data[3]; //AD_SCC_WHL_SPD_STAT 
      mtx_.unlock();
      break;

    case 0x604:
      // receive AD_SHIFT_INFO
    
      mtx_.lock();
      a = acan_data->data[0]; //AD_SHIFT_ACT_POS_STAT 
      a = acan_data->data[1]; //AD_SHIFT_MODE_STAT       
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


void VehicleBridge::AcanWatchdog()
{
    ros::Rate loop_rate(10); // rate of GPS   
    while (ros::ok())
    { ros::Duration duration = ros::Time::now() - Acan_callback_time;
      if(duration.toSec() > 0.2){
        // if no can msg received in 0.2 sec
        ROS_INFO("Acan is empty for %lf ms", duration.toSec()*1000);
        can_recv_status = false;
      }
    }
}

void VehicleBridge::AcanSender()
{
  
  bool icp_converged  = false;
  ros::Rate loop_rate(100); // rate of cmd   
  while (ros::ok())
  {  
    if(can_recv_status){
      steerPub.publish(steering_info_);
      sccPub.publish(scc_info_);
    }
    can_msgs::Frame steer; 
    can_msgs::Frame shift; 
    can_msgs::Frame light; 
    can_msgs::Frame scc; 

    if (AD_STR_MODE_CMD)
    {
      steer.header.stamp = ros::Time::now();
      steer.id = 0x300;
      steer.dlc = 3;
      steer.is_error = false;
      steer.is_extended = false;
      steer.is_rtr = false;
      short steer_value = (short)AD_STR_POS_CMD;
      steer.data[0] = (steer_value & 0b11111111);
      steer.data[1] = ((steer_value >> 8)&0b11111111);
      steer.data[2] = (unsigned int)AD_STR_MODE_CMD & 0b11111111;
      AcanPub.publish(steer);
    }
    
    if (AD_SCC_MODE_CMD)
    {
      scc.header.stamp = ros::Time::now();
      scc.id = 0x303;
      scc.dlc = 4;
      scc.is_error = false;
      scc.is_extended = false;
      scc.is_rtr = false;
      scc.data[0] = (AD_SCC_MODE_CMD & 0b11111111);
      scc.data[1] = AD_SCC_ACCEL_CMD & 0b11111111;
      scc.data[2] = ((AD_SCC_ACCEL_CMD >> 8)&0b11111111);
      scc.data[3] = (AD_SCC_TAKEOVER_CMD & 0b11111111);
      AcanPub.publish(scc);
      // ROS_INFO("AD_SCC_MODE_CMD : %d", AD_SCC_MODE_CMD);
    }
    
    shift.header.stamp = ros::Time::now();
    shift.id = 0x304;
    shift.dlc = 1;
    shift.is_error = false;
    shift.is_extended = false;
    shift.is_rtr = false;
    // cout << AD_GEAR_POS_CMD << endl;
    shift.data[0] = (AD_GEAR_POS_CMD & 0b11111111); // have to modify
    AcanPub.publish(shift);

    light.header.stamp = ros::Time::now();
    light.id = 0x306;
    light.dlc = 3;
    light.is_error = false;
    light.is_extended = false;
    light.is_rtr = false;
    light.data[0] = (AD_LEFT_TURNLAMP_STAT & 0b11111111); // have to modify
    light.data[1] = (AD_RIGHT_TURNLAMP_STAT & 0b11111111);
    light.data[2] = (AD_HAZARD_STAT & 0b11111111);
    AcanPub.publish(light);
    
    loop_rate.sleep();
  }
}

void VehicleBridge::SteeringCmdCallback(hmcl_msgs::VehicleSteeringConstPtr msg){
  ROS_INFO("Steering cmd recieved");
  
  // can_msgs::Frame t; 
  // t.header.stamp = ros::Time::now();
  // t.id = 0x300;
  // t.dlc = 3;
  // t.is_error = false;
  // t.is_extended = false;
  // t.is_rtr = false;
  // short steer_value = (short)(msg->steering_angle*10);
  // t.data[0] = (steer_value & 0b11111111);
	// t.data[1] = ((steer_value >> 8)&0b11111111);
  // t.data[2] = (unsigned int)1 & 0b11111111;
  // AcanPub.publish(t);
//   Header header
// uint32 id
// bool is_rtr
// bool is_extended
// bool is_error
// uint8 dlc
// uint8[8] data
}

void VehicleBridge::AccCmdCallback(hmcl_msgs::VehicleSCCConstPtr msg){
  ROS_INFO("recieved");
  can_msgs::Frame t; 
  t.header.stamp = ros::Time::now();
  t.id = 0x303;
  t.dlc = 4;
  t.is_error = false;
  t.is_extended = false;
  t.is_rtr = false;
  // short acc_value = (short)(msg->steering_angle*10); //have to change
  // t.data[0] = (AD_SCC_MODE_CMD & 0b11111111);
	// t.data[1] = AD_SCC_ACCEL_CMD & 0b11111111;
  // t.data[2] = ((AD_SCC_ACCEL_CMD >> 8)&0b11111111);
  // t.data[3] = (AD_SCC_TAKEOVER_CMD & 0b11111111);
  // AcanPub.publish(t);
}

void VehicleBridge::ShiftCmdCallback(hmcl_msgs::VehicleGearConstPtr msg){
  ROS_INFO("recieved");
  can_msgs::Frame t; 
  t.header.stamp = ros::Time::now();
  t.id = 0x304;
  t.dlc = 1;
  t.is_error = false;
  t.is_extended = false;
  t.is_rtr = false;
  // t.data[0] = (AD_GEAR_POS_CMD & 0b11111111); // have to modify
  // AcanPub.publish(t);

}
void VehicleBridge::LightCmdCallback(hmcl_msgs::VehicleLightConstPtr msg){
  ROS_INFO("recieved");
  can_msgs::Frame t; 
  t.header.stamp = ros::Time::now();
  t.id = 0x306;
  t.dlc = 3;
  t.is_error = false;
  t.is_extended = false;
  t.is_rtr = false;
  // t.data[0] = (AD_LEFT_TURNLAMP_STAT & 0b11111111); // have to modify
  // t.data[1] = (AD_RIGHT_TURNLAMP_STAT & 0b11111111);
  // t.data[2] = (AD_HAZARD_STAT & 0b11111111);
  // AcanPub.publish(t);

}
void callback(vehicle_bridge::testConfig &config, uint32_t level)
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
  AD_STR_MODE_CMD = config.AD_STR_MODE_CMD;
  AD_STR_POS_CMD = config.AD_STR_POS_CMD;
  AD_SCC_ACCEL_CMD = config.AD_SCC_ACCEL_CMD;
  AD_SCC_TAKEOVER_CMD = config.AD_SCC_TAKEOVER_CMD;
  AD_LEFT_TURNLAMP_STAT = config.AD_LEFT_TURNLAMP_STAT;
  AD_RIGHT_TURNLAMP_STAT = config.AD_RIGHT_TURNLAMP_STAT;
  AD_HAZARD_STAT = config.AD_HAZARD_STAT;
  AD_GEAR_POS_CMD = config.AD_GEAR_POS_CMD;
  AD_SCC_MODE_CMD = config.AD_SCC_MODE_CMD;
  // cout << AD_STR_MODE_CMD << endl;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "VehicleBridge");
  dynamic_reconfigure::Server<vehicle_bridge::testConfig> srv;
  dynamic_reconfigure::Server<vehicle_bridge::testConfig>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  srv.setCallback(f);
  
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
