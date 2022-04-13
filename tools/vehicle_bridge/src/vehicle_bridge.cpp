
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


VehicleBridge::VehicleBridge(ros::NodeHandle& nh_can, ros::NodeHandle& nh_acc,ros::NodeHandle& nh_steer,ros::NodeHandle& nh_light):  
  nh_can_(nh_can),
  nh_acc_(nh_acc),
  nh_steer_(nh_steer),
  nh_light_(nh_light),
  can_recv_status(false) 
{
  Acan_callback_time = ros::Time::now();
  
  AcanSub = nh_can.subscribe("a_can_l2h", 100, &VehicleBridge::AcanCallback, this);
  AcanPub = nh_can.advertise<can_msgs::Frame>("a_can_h2l", 1);    
  
  SteeringCmdSub = nh_steer_.subscribe("usafe_steer", 1, &VehicleBridge::SteeringCmdCallback, this);
  AccCmdSub = nh_acc_.subscribe("usafe_acc", 1, &VehicleBridge::AccCmdCallback, this);
  ShiftCmdSub = nh_light_.subscribe("usafe_shift", 1, &VehicleBridge::ShiftCmdCallback, this);
  LightCmdSub = nh_light_.subscribe("usafe_lights", 1, &VehicleBridge::LightCmdCallback, this);

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
  float a;
  mtx_.lock();
  switch(msg_id) {    
    case 600:
      // receive AD_STR_INFO
      a = acan_data->data[0]; //AD_STR_MODE_STAT 
      // a = acan_data->data[1:2]; //AD_STR_ACT_POS_STAT 
      a = acan_data->data[3]; //AD_STR_TAKEOVER_INFO 
      a = acan_data->data[4]; //(Reserved) 
      a = acan_data->data[5]; //AD_STR_ALIVE_COUNT 
      break;

    case 602:
      // receive AD_SCC_INFO
      a = acan_data->data[0]; //AD_SCC_ACT_MODE_STAT 
      // a = acan_data->data[1:2]; //AD_SCC_SPD_STAT 
      a = acan_data->data[3]; //AD_SCC_WHL_SPD_STAT 
      break;

    case 604:
      // receive AD_SHIFT_INFO
      a = acan_data->data[0]; //AD_SHIFT_ACT_POS_STAT 
      a = acan_data->data[1]; //AD_SHIFT_MODE_STAT       
      break;

    case 606:
      // receive AD_BTN_INFO
      a = acan_data->data[0]; //AD_AUTO_BTN_STAT 
      a = acan_data->data[1]; //AD_EMS_BTN_STAT 
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT 
      break;

    case 608:
      // receive TL_INFO
      a = acan_data->data[0]; //AD_HAZARD_STAT 
      a = acan_data->data[1]; //AD_RIGHT_TURNLAMP_STAT       
      break;

    case 60:
      a = acan_data->data[0]; //AD_WIRELESS_REMOTE_BTN_STAT_1 
      a = acan_data->data[1]; //AD_WIRELESS_REMOTE_BTN_STAT_2
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT_3
      // receive AD_RTE_INFO
      break;
      
    default:    
      return;        
  }  
  mtx_.unlock();
}


void VehicleBridge::AcanWatchdog()
{
    ros::Rate loop_rate(10); // rate of GPS   
    while (ros::ok())
    { ros::Duration duration = ros::Time::now() - Acan_callback_time;
      if(duration.toSec() > 0.2){
        // if no can msg received in 0.2 sec
        ROS_INFO("Acan is empty for %lf secs", duration.toSec());
        can_recv_status = false;
      }
    }
}

void VehicleBridge::AcanSender()
{
  
  bool icp_converged  = false;
  ros::Rate loop_rate(1000); // rate of cmd   
  while (ros::ok())
  {  
    if(can_recv_status){
      
    }
    loop_rate.sleep();
  }
}

void VehicleBridge::SteeringCmdCallback(hmcl_msgs::VehicleSteeringConstPtr msg){
ROS_INFO("recieved");
mtx_.lock();
mtx_.unlock();
}

void VehicleBridge::AccCmdCallback(hmcl_msgs::VehicleSCCConstPtr msg){
  ROS_INFO("recieved");
  mtx_.lock();
  mtx_.unlock();
}

void VehicleBridge::ShiftCmdCallback(hmcl_msgs::VehicleGearConstPtr msg){
  ROS_INFO("recieved");
  mtx_.lock();
  mtx_.unlock();
}
void VehicleBridge::LightCmdCallback(hmcl_msgs::VehicleLightConstPtr msg){
  ROS_INFO("recieved");
  mtx_.lock();
  mtx_.unlock();
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
