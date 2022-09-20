
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
#include <chrono>

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "usafe.h"
// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


Usafe::Usafe(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p) :  
  nh_(nh), nh_p_(nh_p)
{
  
  // tools initialize
  debugger_ = new tools::Debugger();
  system_monitor_ = new tools::HeatlMonitoring();                         
  
  // perception modules initialize  
  v2x_receiver_ = new perception::V2X();
  sensors_ = new perception::VehicleStates();
  environmet_ = new perception::SurroundingEnvironment();

  //planner initialize 
  ms_planner_ = new planner::MissionStateMachine();
  rt_planner_ = new planner::RoutePlanner();
  bh_planner_ = new planner::BehaviorStatMachine();
  pp_planner_ = new planner::PathPlanner();
  vel_planner_ = new planner::VelocityPlanner();
  planner_common_ = new planner::PlannerCommon();

  // controller initiazlie 
  long_ctrl_ = new controller::LongitudinalCtrl();
  lat_ctrl_ = new controller::LateralCtrl();

  
}

Usafe::~Usafe()
{}



int main (int argc, char** argv)
{
ros::init(argc, argv, "Usafe");
ros::NodeHandle nh_;
ros::NodeHandle nh_private("~");
Usafe Usafe_(nh_,nh_private);

  ros::spin();


}
