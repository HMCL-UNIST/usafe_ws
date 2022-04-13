
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


VehicleBridge::VehicleBridge():  
  nh_("~"),
  can_recv_status(false) 
{
  Acan_callback_time = ros::Time::now();
  AcanPub = nh_.advertise<can_msgs::Frame>("acan_h2l", 1);  
  AcanSub = nh_.subscribe("acan_l2h", 100, &VehicleBridge::AcanCallback, this);
  
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
  switch(msg_id) {
    case 100:
      // code block
      ROS_INFO("dd");
      break;
      
    case 500:
      // code block
      ROS_INFO("dd");
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



int main (int argc, char** argv)
{
ros::init(argc, argv, "VehicleBridge");
VehicleBridge VehicleBridge_;
ros::spin();
}
