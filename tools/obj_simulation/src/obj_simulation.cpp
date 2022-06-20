
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
#include "obj_simulation.h"

using namespace std;

ObjSimulation::ObjSimulation(ros::NodeHandle& nh_):  
  nh_(nh_)
{
  
  
  objPub = nh_.advertise<autoware_msgs::DetectedObjectArray>("/detected_objs", 5);    

  emergency_stopSub = nh_.subscribe("/emer", 2, &ObjSimulation::emergencyRemoteCallback, this);
  ROS_INFO("obj simulation");
  // boost::thread AcanHandler(&ObjSimulation::AcanSender,this); 
  // boost::thread AcanWatch(&ObjSimulation::AcanWatchdog,this); 
 
  
  f = boost::bind(&ObjSimulation::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

ObjSimulation::~ObjSimulation()
{}

void ObjSimulation::emergencyRemoteCallback(std_msgs::Float64ConstPtr msg){
    int thres = 5;
    if(msg->data > 0.5){
      emergency_count++;
    }else{
      emergency_count--;
    }
    
    if(emergency_count > thres){
      emergency_stop_activate = true;           
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

void ObjSimulation::dyn_callback(obj_simulation::testConfig &config, uint32_t level)
{
  ROS_INFO("received");
  
  

}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "ObjSimulation");
  
  

  ros::NodeHandle nh_;
  ObjSimulation ObjSimulation_(nh_);


    ros::spin();



  return 0;

}
