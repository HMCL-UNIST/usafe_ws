
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


#include "usafe.h"
// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


Usafe::Usafe(const ros::NodeHandle& nh, const ros::NodeHandle& nh_local,const ros::NodeHandle& nh_p) :  
  nh_(nh), nh_local_(nh_local), nh_p_(nh_p)
{
  v2xSub = nh_local_.subscribe("/Mission2", 2, &Usafe::callbackV2X, this);
  // tools initialize
  // debugger_ = new tools::Debugger();
  // system_monitor_ = new tools::HeatlMonitoring();                         
  
  // perception modules initialize  
  // v2x_receiver_ = new perception::V2X();
  // sensors_ = new perception::VehicleStates();
  // environmet_ = new perception::SurroundingEnvironment();

  //planner initialize 
  // ms_planner_ = new planner::MissionStateMachine();
  // rt_planner_ = new planner::RoutePlanner();
  // bh_planner_ = new planner::BehaviorStatMachine();
  // pp_planner_ = new planner::PathPlanner();
  // vel_planner_ = new planner::VelocityPlanner();
  // planner_common_ = new planner::PlannerCommon();
  race_planner_ = new planner::RacingLinePlanner(nh_,nh_p_);
  vehicle_model_ = new planner::VehicleModel(nh_local_,nh_p_);
  race_planner_->vehicle_model_ = vehicle_model_;
  
  Above_compute_shortest_path_ = false;
  Below_compute_shortest_path_ = false;
  Sum_compute_shortest_path_ = false;
  positive_cost_assign_ = false;
  f = boost::bind(&Usafe::dyn_callback,this, _1, _2);
	srv.setCallback(f);
  // race_planner_->number_of_node = 4;
  // race_planner_->gen_random_graph();
  // race_planner_->compute_best_route(1);
  

  // controller initiazlie 
  // long_ctrl_ = new controller::LongitudinalCtrl();
  // lat_ctrl_ = new controller::LateralCtrl();

}


Usafe::~Usafe()
{}

// void Usafe::callbackV2X(const v2x_msgs::Mission2ConstPtr &msg){
void Usafe::callbackV2X(const hmcl_v2x::HMCL_Mission2ConstPtr &msg){

  if(!race_planner_->waypoint_received){
    ROS_INFO("Encode waypoints coming from V2X");
    race_planner_->v2x_data=*msg; 
    race_planner_->convert_v2x_data();
    race_planner_->waypoint_received=true; 
  }
  
  // ROS_INFO("waypoints size = %d",msg->States.size() );
}

void Usafe::dyn_callback(usafe::testConfig &config, uint32_t level)
{
  Sum_compute_shortest_path_ = config.Sum_compute_shortest_path;
  positive_cost_assign_ = config.positive_cost_assign;
  race_planner_->positive_cost_assign_ = positive_cost_assign_; 
  if(Sum_compute_shortest_path_){
    if(race_planner_->compute_global_path()){
        ROS_WARN("Global Path found");
      }else{
        ROS_WARN("Global Path Not Found");
      }
  }
    
  
 return;  
}




int main (int argc, char** argv)
{
ros::init(argc, argv, "Usafe");
ros::NodeHandle nh, nh_local;
ros::NodeHandle nh_private("~");

Usafe Usafe_(nh,nh_local,nh_private);

ros::CallbackQueue callback_queue_nh, callback_queue_nh_local;
nh.setCallbackQueue(&callback_queue_nh);
nh_local.setCallbackQueue(&callback_queue_nh_local);

std::thread spinner_thread_nh([&callback_queue_nh]() {
    ros::SingleThreadedSpinner spinner_nh;
    spinner_nh.spin(&callback_queue_nh);
  });

  std::thread spinner_thread_nh_local_path([&callback_queue_nh_local]() {
    ros::SingleThreadedSpinner spinner_nh_local_path;
    spinner_nh_local_path.spin(&callback_queue_nh_local);
  });


  ros::spin();

  spinner_thread_nh.join();
  spinner_thread_nh_local_path.join();
}
