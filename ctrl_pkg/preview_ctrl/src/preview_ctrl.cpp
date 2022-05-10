
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
#include <chrono>


#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "preview_ctrl.h"


using namespace std;

PreviewCtrl::PreviewCtrl(ros::NodeHandle& nh_ctrl, ros::NodeHandle& nh_traj):  
  nh_ctrl_(nh_ctrl),
  nh_traj_(nh_traj)  
{
  
  nh_traj.param<std::string>("pose_topic", pose_topic, "/current_pose");
  nh_traj.param<std::string>("vehicle_status_topic", vehicle_status_topic, "/hmcl_vehicle_status");
  nh_traj.param<std::string>("control_topic", control_topic, "/hmcl_ctrl_cmd");
  nh_traj.param<std::string>("waypoint_topic", waypoint_topic, "/final_waypoints");
  nh_traj.param<std::string>("odom_topic", odom_topic, "/carla/ego_vehicle/odometry");
 
  nh_traj.param<double>("wheelbase", wheelbase, 2.7);
  nh_traj.param<double>("lf", lf, 1.35);
  nh_traj.param<double>("lr", lr, 1.35);
  nh_traj.param<double>("mass", mass, 1650);    
  nh_traj.param<double>("dt", dt, 0.04); 
  nh_traj.param<double>("delay_in_sec", delay_in_sec, 0.2); 
  nh_traj.param<double>("lag_tau", lag_tau, 0.2); 

  nh_traj.param<double>("Q_ey", Q_ey, 3.0); 
  nh_traj.param<double>("Q_eydot", Q_eydot, 5.0); 
  nh_traj.param<double>("Q_epsi", Q_epsi, 7.0); 
  nh_traj.param<double>("Q_epsidot", Q_epsidot, 1.0); 
  nh_traj.param<double>("R_weight", R_weight, 1500); 

  delay_step = (int)(delay_in_sec/dt);
  VehicleModel_.init(dt, wheelbase, lf, lr, mass, delay_step);
  VehicleModel_.setDelayStep(delay_step);  
  VehicleModel_.setLagTau(lag_tau);
  ROS_INFO("lag_tau = %f", lag_tau);
  ROS_INFO("delay_step = %f", delay_step);
 


  std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
  VehicleModel_.reintMatrices();
  VehicleModel_.setWeight(Qweight, R_weight);
  
  

  
  


  poseSub = nh_traj.subscribe( pose_topic ,2 , &PreviewCtrl::PoseCallback, this);
  waypointSub = nh_traj.subscribe(waypoint_topic, 2, &PreviewCtrl::WaypointCallback, this);
  vehicleStatusSub = nh_traj.subscribe(vehicle_status_topic, 2, &PreviewCtrl::VehicleStatusCallback, this);
  odomSub = nh_traj.subscribe(odom_topic, 2, &PreviewCtrl::odomCabllback, this);

  steerPub  = nh_ctrl.advertise<hmcl_msgs::VehicleSteering>(control_topic, 2);    
    
  boost::thread ControlLoopHandler(&PreviewCtrl::ControlLoop,this);   
  ROS_INFO("Init Preview controller with delay compensation");
  
 
  
  f = boost::bind(&PreviewCtrl::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

PreviewCtrl::~PreviewCtrl()
{}



void PreviewCtrl::ControlLoop()
{
    ros::Rate loop_rate(25); // rate  
    while (ros::ok()){         
        auto start = std::chrono::steady_clock::now();
        Vx_test = max(Vx_test,1.0);
        VehicleModel_.computeMatrices(Vx_test);        
        VehicleModel_.solveRiccati();
        auto end = std::chrono::steady_clock::now();        
     loop_rate.sleep();
     std::chrono::duration<double> elapsed_seconds = end-start;
      std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
}

void PreviewCtrl::odomCabllback(nav_msgs::OdometryConstPtr odom_msg){
  return; 
}

void PreviewCtrl::stateCallback(geometry_msgs::PoseStampedConstPtr pose_msg){
  
}

// void PreviewCtrl::PoseCallback(geometry_msgs::PoseStampedConstPtr pose_msg){
//   return;
// }
// void PreviewCtrl::WaypointCallback(hmcl_msgs::LaneConstPtr waypoints_msg){
//   return;
// }
void PreviewCtrl::VehicleStatusCallback(carla_msgs::CarlaEgoVehicleStatusConstPtr status_msg){
  return;
}



void PreviewCtrl::dyn_callback(preview_ctrl::testConfig &config, uint32_t level)
{
  Vx_test = config.Vx_test;
  Q_ey = config.Q_ey;
  Q_eydot = config.Q_eydot;
  Q_epsi = config.Q_epsi ;
  Q_epsidot = config.Q_epsidot;
  R_weight = config.R_weight;  
  lag_tau = config.lag_tau;
  delay_in_sec = config.delay_in_sec;
  delay_step = (int)(delay_in_sec/dt);
  
  std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
  VehicleModel_.setWeight( Qweight, R_weight);
  VehicleModel_.setDelayStep(delay_step);  
  VehicleModel_.setLagTau(lag_tau);


  
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "PreviewCtrl");
  
  ros::NodeHandle nh_ctrl, nh_traj;
  PreviewCtrl PreviewCtrl_(nh_ctrl, nh_traj);

  ros::CallbackQueue callback_queue_ctrl, callback_queue_traj;
  nh_ctrl.setCallbackQueue(&callback_queue_ctrl);
  nh_traj.setCallbackQueue(&callback_queue_traj);
  

  std::thread spinner_thread_ctrl([&callback_queue_ctrl]() {
    ros::SingleThreadedSpinner spinner_ctrl;
    spinner_ctrl.spin(&callback_queue_ctrl);
  });

  std::thread spinner_thread_traj([&callback_queue_traj]() {
    ros::SingleThreadedSpinner spinner_traj;
    spinner_traj.spin(&callback_queue_traj);
  });

 

    ros::spin();

    spinner_thread_ctrl.join();
    spinner_thread_traj.join();


  return 0;

}
