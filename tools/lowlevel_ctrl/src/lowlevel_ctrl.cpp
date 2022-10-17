
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

LowlevelCtrl::LowlevelCtrl(ros::NodeHandle& nh_can, ros::NodeHandle& nh_acc,ros::NodeHandle& nh_steer,ros::NodeHandle& nh_light):  
  nh_can_(nh_can),
  nh_acc_(nh_acc),
  nh_steer_(nh_steer),
  nh_light_(nh_light),
  Acan_recv_status(false), 
  Ccan_recv_status(false), 
  emergency_count(0),
  emergency_stop_activate(false),
  drivingState(DrivingState::Parking),    
  scc_overwrite(false)
{  
  
  AcanPub = nh_can.advertise<can_msgs::Frame>("/a_can_h2l", 10);  
  statusPub = nh_light_.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 5);    
  sccPub    = nh_light_.advertise<hmcl_msgs::VehicleSCC>("/scc_info", 5);    
  steerPub  = nh_light_.advertise<hmcl_msgs::VehicleSteering>("/steering_info", 5);    
  wheelPub  = nh_light_.advertise<hmcl_msgs::VehicleWheelSpeed>("/wheel_info", 5);    
  driving_pub  = nh_light_.advertise<std_msgs::String>("/driving_gui", 2);    
  
  InitCanmsg();
  
  AcanSub = nh_light_.subscribe("/a_can_l2h", 100, &LowlevelCtrl::AcanCallback, this);
  CcanSub = nh_light_.subscribe("/c_can_l2h", 100, &LowlevelCtrl::CcanCallback, this);
  SteeringCmdSub = nh_can.subscribe("/usafe_steer_cmd", 10, &LowlevelCtrl::SteeringCmdCallback, this);  
  VelSub = nh_acc.subscribe("/control_effort", 2, &LowlevelCtrl::controlEffortCallback, this);  
  emergency_stopSub = nh_acc.subscribe("/volt", 2, &LowlevelCtrl::emergencyRemoteCallback, this);
  setpointSub = nh_acc.subscribe("/setpoint", 2, &LowlevelCtrl::TargetVelocityCallback, this);
  gnssPoseSub = nh_acc.subscribe("/gnss_pose_world", 2, &LowlevelCtrl::gnssPoseCallback, this);

  missionStatisSub = nh_light_.subscribe("/behavior_factor", 2, &LowlevelCtrl::missionCallback, this);
  
  
  ROS_INFO("Init A-CAN Handler");
  boost::thread AcanHandler(&LowlevelCtrl::AcanSender,this);   
  ROS_INFO("Init Driving State Machine");
  boost::thread statemachine(&LowlevelCtrl::DrivingStateMachine,this); 
  boost::thread test(&LowlevelCtrl::Test,this); 

  
  // f = boost::bind(&VehicleBridge::dyn_callback,this, _1, _2);
	// srv.setCallback(f);
}

LowlevelCtrl::~LowlevelCtrl()
{}


void LowlevelCtrl::InitCanmsg(){
  short steer_value = (short)(0.0+steering_offset) ; // input  in radian, convert into degree
  // setSteering(steer_value);  
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;  
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
  steering_frame.data[2] = (unsigned int)0 & 0b11111111;
      
  setToParking();
  short zero_dcel = (0*100);       
  setScc(zero_dcel);                           
  //ready 
  int SCC_mode_ready = 1;
  scc_frame.data[0] = (unsigned int)SCC_mode_ready & 0b11111111;
  usleep(1000);
  AcanPub.publish(scc_frame);
  usleep(1000);
  AcanPub.publish(gear_frame);
  
  light_frame.header.stamp = ros::Time::now();
  light_frame.id = 0x306;
  light_frame.dlc = 3;
  light_frame.is_error = false;
  light_frame.is_extended = false;
  light_frame.is_rtr = false;
  light_frame.data[0] = (unsigned int)0 & 0b11111111;  
  light_frame.data[1] = (unsigned int)0 & 0b11111111;  
  light_frame.data[2] = (unsigned int)0 & 0b11111111;  
  usleep(2000000);
  ROS_INFO("Init complete");
}

void LowlevelCtrl::missionCallback(hmcl_msgs::BehaviorFactorConstPtr msg){
  bool missions_statue = msg->transition_condition.missionStart;
  if(missions_statue){
    mtx_.lock();
    drivingState = DrivingState::Driving;
    mtx_.unlock();
  }else{
    drivingState = DrivingState::Parking;
  }
}

void LowlevelCtrl::AcanSender()
{
  ros::Rate loop_rate(50); // rate of cmd   
  
  while (ros::ok())
  {   
    if(!Acan_recv_status){  ROS_WARN("ACAN is not available"); continue;}
    if(!Ccan_recv_status){ ROS_WARN("CCAN is not available"); continue;}
      mtx_.lock();
      usleep(1000);

      if(target_vel <= 0.0 && abs(wheel_info_.wheel_speed) <= 0.05){        
        short zero_dcel = (0*100);       
        setScc(zero_dcel);                           
        ROS_INFO("Driving Stop activated");
      }else if(target_vel <= 0.0 && abs(wheel_info_.wheel_speed) <= 2.0){
          short hard_dcel = (-2*100);       
        setScc(hard_dcel);                   
        ROS_INFO("hard stop");
      }
      if(scc_info_.scc_mode == 0 ){
        short zero_dcel = (0*100);       
        setScc(zero_dcel);           
        int SCC_mode_ready = 1;
        scc_frame.data[0] = (unsigned int)SCC_mode_ready & 0b11111111;                
        ROS_INFO("SCC takeover");
      }
      if(scc_info_.scc_mode == 1 ){
        short zero_dcel = (0*100);       
        setScc(zero_dcel);           
        scc_frame.data[0] = (unsigned int)2 & 0b11111111;                
        ROS_INFO("SCC On");
      }
     
      
      // AcanPub.publish(scc_frame);
      usleep(1000);
      // AcanPub.publish(gear_frame);
      usleep(1000);
      AcanPub.publish(steering_frame);
      // usleep(1000);     
      // AcanPub.publish(light_frame);  
      usleep(1000);     
            // publish vehicle info 
      steerPub.publish(steering_info_);
      statusPub.publish(vehicle_status_);
      sccPub.publish(scc_info_);  
      wheelPub.publish(wheel_info_);    
      mtx_.unlock();  
    loop_rate.sleep();
  }
}



void LowlevelCtrl::setSteering(short steer_value){
  int STR_mode_on = 1;
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;  
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
  steering_frame.data[2] = (unsigned int)STR_mode_on & 0b11111111;
}


// e.g. acc_vel = 100 - > 1m/s^2
void LowlevelCtrl::setScc(short acc_vel){
          int SCC_mode_auto = 2;
          scc_frame.header.stamp = ros::Time::now();
          scc_frame.id = 0x303;
          scc_frame.dlc = 4;
          scc_frame.is_error = false;
          scc_frame.is_extended = false;
          scc_frame.is_rtr = false;                          
          scc_frame.data[0] = (unsigned int)SCC_mode_auto & 0b11111111;
          scc_frame.data[1] = (acc_vel & 0b11111111);
          scc_frame.data[2] = ((acc_vel >> 8)&0b11111111);
          scc_frame.data[3] = (unsigned int)0 & 0b11111111;
}

void LowlevelCtrl::setToParking(){
          AD_GEAR_POS_CMD = 0;
          gear_frame.header.stamp = ros::Time::now();
          gear_frame.id = 0x304;
          gear_frame.dlc = 1;
          gear_frame.is_error = false;
          gear_frame.is_extended = false;
          gear_frame.is_rtr = false;
          gear_frame.data[0] = (unsigned int)AD_GEAR_POS_CMD & 0b11111111;
}


void LowlevelCtrl::setToDrive(){
          AD_GEAR_POS_CMD = 1;
          gear_frame.header.stamp = ros::Time::now();
          gear_frame.id = 0x304;
          gear_frame.dlc = 1;
          gear_frame.is_error = false;
          gear_frame.is_extended = false;
          gear_frame.is_rtr = false;
          gear_frame.data[0] = (unsigned int)AD_GEAR_POS_CMD & 0b11111111;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "Lowlevel_ctrl");

  ros::NodeHandle nh_can, nh_acc, nh_steer, nh_light;
  LowlevelCtrl LowlevelCtrl_(nh_can,nh_acc,nh_steer,nh_light);

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
