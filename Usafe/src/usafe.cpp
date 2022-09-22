
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
  race_planner_ = new planner::RacingLinePlanner(nh_,nh_p_);
  race_planner_->number_of_node = 4;
  race_planner_->gen_random_graph();
  race_planner_->compute_best_route(1);
  

  // controller initiazlie 
  long_ctrl_ = new controller::LongitudinalCtrl();
  lat_ctrl_ = new controller::LateralCtrl();

}

Usafe::~Usafe()
{}

// Usafe::planner_loop(){
  
//   // get the mission state 
//   //*** (HyunBIN) //*** 
//   mission_state =  ms_planner_.get_ms_state();
  
//   // retrive goal action (pose) 
//   // (Sanghyun) //*** 
//   goal_ = v2x_receiver_.get_goal(mission_state);
 
//   // compute the behaviour state 
//   // (HyunBin) //*** 
//   behaviour_state = bh_planner_.get_behaviour(mission_state);
  
//   // Compute the local path and velocity profile depends on the behaviour state
//   //*** Junseoung //*** 
//   local_path = pp_planner_.get_local_path(behaviour_state)
//   //***  NAM //***  
//   local_vel_profile = vel_planner.get_local_velocity_profile(behaviour_state)

//   // Compute the lateral and longitudinal cmd 
//   //***MINU //*** 
//   long_ctrl_.get_vel_cmd(local_vel_profile)
//   //***MINU //*** 
//   lat_ctrl.get_vel_cmd(local_path)

// }

// Usafet::perception_loop(){
  

// }



int main (int argc, char** argv)
{
ros::init(argc, argv, "Usafe");
ros::NodeHandle nh_;
ros::NodeHandle nh_private("~");
Usafe Usafe_(nh_,nh_private);

  ros::spin();


}
