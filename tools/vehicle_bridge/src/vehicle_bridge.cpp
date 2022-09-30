
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
#include "vehicle_bridge.h"

using namespace std;

VehicleBridge::VehicleBridge(ros::NodeHandle& nh_can, ros::NodeHandle& nh_acc,ros::NodeHandle& nh_steer,ros::NodeHandle& nh_light):  
  nh_can_(nh_can),
  nh_acc_(nh_acc),
  nh_steer_(nh_steer),
  nh_light_(nh_light),
  Acan_recv_status(false), 
  Ccan_recv_status(false), 
  emergency_count(0),
  emergency_stop_activate(false),
  drivingState(DrivingState::Init),  
  missionState(MissionState::ACC),
  scc_overwrite(false)
{
  Acan_callback_time = ros::Time::now();
  
  InitCanmsg();
  
  scc_overwrite_value = ((round(0.0 *100)/100)*100);        
  test_count = 0; 
  AcanSub = nh_light_.subscribe("/a_can_l2h", 100, &VehicleBridge::AcanCallback, this);
  CcanSub = nh_light_.subscribe("/c_can_l2h", 100, &VehicleBridge::CcanCallback, this);
  AcanPub = nh_can.advertise<can_msgs::Frame>("/a_can_h2l", 10);  
  statusPub = nh_light_.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 5);    
  sccPub    = nh_light_.advertise<hmcl_msgs::VehicleSCC>("/scc_info", 5);    
  steerPub  = nh_light_.advertise<hmcl_msgs::VehicleSteering>("/steering_info", 5);    
  wheelPub  = nh_light_.advertise<hmcl_msgs::VehicleWheelSpeed>("/wheel_info", 5);    

  right_lc_pub  = nh_light_.advertise<std_msgs::Bool>("/right_lanechange", 2);    
  left_lc_pub  = nh_light_.advertise<std_msgs::Bool>("/left_lanechange", 2);    

  mission_pub  = nh_light_.advertise<std_msgs::String>("/mission_gui", 2);    
  driving_pub  = nh_light_.advertise<std_msgs::String>("/driving_gui", 2);    



  // velPub  = nh_light_.advertise<std_msgs::Float64>("/setpoint", 2);   
  // test_pub = nh_light_.advertise<std_msgs::Float64>("/str_test", 5);    
  // debug_pub = nh_can.advertise<std_msgs::UInt8MultiArray>("/debug_sig",10);
  // SteeringCmdSub = nh_can.subscribe("/usafe_steer_cmd", 10, &VehicleBridge::SteeringCmdFloatCallback, this); 
  SteeringCmdSub = nh_can.subscribe("/usafe_steer_cmd", 10, &VehicleBridge::SteeringCmdCallback, this);  
  VelSub = nh_acc.subscribe("control_effort", 2, &VehicleBridge::controlEffortCallback, this);  
  emergency_stopSub = nh_acc.subscribe("/volt", 2, &VehicleBridge::emergencyRemoteCallback, this);
  // setpointSub = nh_acc.subscribe("/setpoint", 2, &VehicleBridge::SetpointCallback, this);
  gnssPoseSub = nh_acc.subscribe("/gnss_pose_world", 2, &VehicleBridge::gnssPoseCallback, this);
  
  
  
  ROS_INFO("Init A-CAN Handler");
  boost::thread AcanHandler(&VehicleBridge::AcanSender,this); 
  // boost::thread AcanWatch(&VehicleBridge::AcanWatchdog,this); 
  boost::thread statemachine(&VehicleBridge::DrivingStateMachine,this); 
  // boost::thread missionMachine(&VehicleBridge::MissionStateMachine,this); 
  // boost::thread test(&VehicleBridge::TestCase,this); 

  
  // f = boost::bind(&VehicleBridge::dyn_callback,this, _1, _2);
	// srv.setCallback(f);
}

VehicleBridge::~VehicleBridge()
{}

void VehicleBridge::emergencyRemoteCallback(std_msgs::Float64ConstPtr msg){
    int thres = 1;
    if(msg->data > 0.5){
      emergency_count++;
    }else{
      emergency_count--;
    }
    
    if(emergency_count > thres){
      emergency_stop_activate = true;    
      scc_overwrite_value = ((round(-5.0*100)/100)*100);        
      scc_overwrite = true;       
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
void VehicleBridge::AcanCallback(can_msgs::FrameConstPtr acan_data)
{ 
  Acan_recv_status = true;
  int msg_id = acan_data->id;  
  int a;
  
  Acan_callback_time = ros::Time::now();
  
   
  double steer_d;
  switch(msg_id) {    
    case 0x600:      
      // receive AD_STR_INFO      
      steering_info_.header = acan_data->header;
      steering_info_.takeover = (unsigned int)acan_data->data[3]; //AD_STR_TAKEOVER_INFO 
      steering_info_.mode = (unsigned int)acan_data->data[0]; //AD_STR_MODE_STAT 
      steering_info_.steering_angle = (((short)((acan_data->data[2]  << 8)+acan_data->data[1]-steering_offset)*0.1)*PI/180.0)/gear_ratio;      
      vehicle_status_.steering_info = steering_info_; 
      // a = acan_data->data[4]; //(Reserved) 
      // a = acan_data->data[5]; //AD_STR_ALIVE_COUNT       
      break;

    case 0x602:      
      // receive AD_SCC_INFO      
      vehicle_status_.header = acan_data->header;
      // wheel_info_.header = acan_data->header;
      scc_info_.header = acan_data->header;
      scc_info_.scc_mode = (unsigned int)acan_data->data[0]; //AD_SCC_ACT_MODE_STAT 
      scc_info_.acceleration = (short)((acan_data->data[2]  << 8)+acan_data->data[1])*0.01;       
      vehicle_status_.scc_info = scc_info_;
      // vehicle_status_.wheelspeed = wheel_info_;
      
      break;

    case 0x604:
      // receive AD_SHIFT_INFO      
      gear_info_.gear = (unsigned int)acan_data->data[0]; //AD_SHIFT_MODE_STAT       
      vehicle_status_.auto_mode = (unsigned int)acan_data->data[1]; //AD_SHIFT_ACT_POS_STAT       
      vehicle_status_.gear_info = gear_info_;      
      break;

    case 0x606:
      // receive AD_BTN_INFO      
      a = acan_data->data[0]; //AD_AUTO_BTN_STAT 
      a = acan_data->data[1]; //AD_EMS_BTN_STAT 
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT       
      break;

    case 0x608:   
      
      // receive TL_INFO
      // left_light_on = (unsigned int)acan_data->data[0]; //AD_HAZARD_STAT 
      // 1 left 2 right
      light_on = (unsigned int)acan_data->data[1]; //AD_RIGHT_TURNLAMP_STAT  
      if(light_on == 1){
        vehicle_status_.light_info.left_light = 1;
      }else{
        vehicle_status_.light_info.left_light = 0;
      }
      if(light_on == 2){
        vehicle_status_.light_info.right_light = 1;
      }else{
        vehicle_status_.light_info.right_light = 0;
      }
      
      // light_frame.data[2] = (unsigned int)msg->hazard_light & 0b11111111;      
      
      break;

    case 0x60:
      
      a = acan_data->data[0]; //AD_WIRELESS_REMOTE_BTN_STAT_1 
      a = acan_data->data[1]; //AD_WIRELESS_REMOTE_BTN_STAT_2
      a = acan_data->data[2]; //AD_WIRELESS_REMOTE_BTN_STAT_3
      
      // receive AD_RTE_INFO
      break;
      
    default:  
      
      return;        
  }  
  
}
void VehicleBridge::CcanCallback(can_msgs::FrameConstPtr ccan_data)
{
  Ccan_recv_status = true;
  int msg_id = ccan_data->id;    
  float lat_acc, long_acc, yaw_rate;
  // mtx_.lock();
  Ccan_callback_time = ros::Time::now();
  // mtx_.unlock();
   
  switch(msg_id) {    
    case 0x220:
      // mtx_.lock();
      // receive AD_ACCEL & YAW RATE 
      lat_acc = ((unsigned int)(ccan_data->data[0] + ((ccan_data->data[1] & 0b00000111) << 8)))*0.01-10.03;
      long_acc = ((unsigned int)(((ccan_data->data[1] & 0b11100000) >> 5) + (ccan_data->data[2] << 3)))*0.01-10.40;
      yaw_rate = ((unsigned int)(ccan_data->data[5] + ((ccan_data->data[6] & 0b00011111) << 8)))*0.01 - 41.55;           
      // vehicle_status_.y_acceleration = clamp(lat_acc, -10.23, 10.24);
      // vehicle_status_.x_acceleration = clamp(long_acc, -10.23, 10.24);
      // vehicle_status_.yaw_rate = clamp(yaw_rate, -40.95, 40.96);
      vehicle_status_.y_acceleration = lat_acc;
      vehicle_status_.x_acceleration =long_acc;
      vehicle_status_.yaw_rate = yaw_rate;
      // mtx_.unlock();
      break;

    case 0x386:
      // mtx_.lock();
      // receive WHL_SPEED      
      wheel_info_.header = ccan_data->header;
      fl = ((unsigned int)(ccan_data->data[0] + ((ccan_data->data[1] & 0b00111111) << 8)))*0.03125; // whl speed front left
      fr = ((unsigned int)(ccan_data->data[2] + ((ccan_data->data[3] & 0b00111111) << 8)))*0.03125; // whl speed front right
      rl = ((unsigned int)(ccan_data->data[4] + ((ccan_data->data[5] & 0b00111111) << 8)))*0.03125; // whl speed rear left
      rr = ((unsigned int)(ccan_data->data[6] + ((ccan_data->data[7] & 0b00111111) << 8)))*0.03125; // whl speed rear right
      
      wheel_info_.wheel_speed = ((fl+fr+rl+rr)/4)/3.6; // m/s
      wheel_info_.fl = fl;
      wheel_info_.fr = fr;
      wheel_info_.rr = rr;
      wheel_info_.rl = rl;
      vehicle_status_.wheelspeed = wheel_info_;
      
      // mtx_.unlock();
      break;
      
    default:        
      return;        
  }  
}

void VehicleBridge::gnssPoseCallback(geometry_msgs::PoseStampedConstPtr msg){
 ego_pose = *msg;
}


void VehicleBridge::InitCanmsg(){
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;
  short steer_value = (short)(0.0+steering_offset) ; // input  in radian, convert into degree
  steering_frame.data[2] = (unsigned int)0 & 0b11111111;

  scc_frame.header.stamp = ros::Time::now();
  scc_frame.id = 0x303;
  scc_frame.dlc = 4;
  scc_frame.is_error = false;
  scc_frame.is_extended = false;
  scc_frame.is_rtr = false;
  accel_value = 0;
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
  gear_frame.data[0] = (unsigned int)1 & 0b11111111;  

  light_frame.header.stamp = ros::Time::now();
  light_frame.id = 0x306;
  light_frame.dlc = 3;
  light_frame.is_error = false;
  light_frame.is_extended = false;
  light_frame.is_rtr = false;
  light_frame.data[0] = (unsigned int)0 & 0b11111111;  
  light_frame.data[1] = (unsigned int)0 & 0b11111111;  
  light_frame.data[2] = (unsigned int)0 & 0b11111111;  
}


void VehicleBridge::AcanSender()
{
  ros::Rate loop_rate(50); // rate of cmd   
  while (ros::ok())
  {  
      // publish vehicle info
      mtx_.lock(); 
      steerPub.publish(steering_info_);
      statusPub.publish(vehicle_status_);
      sccPub.publish(scc_info_);  
      wheelPub.publish(wheel_info_);  
      
      
      //  scc_overwrite_value = ((round(2 *100)/100)*100); 
      if(scc_overwrite){    
        ROS_INFO("scc overwrite in acansender");
        scc_frame.data[1] = (-500 & 0b11111111);
        scc_frame.data[2] = ((-500 >> 8)&0b11111111);  
      }
      // ROS_INFO("@@ scc frame = %d", scc_frame.data[1]);
      usleep(10);
      ROS_INFO("HERE");
      AcanPub.publish(scc_frame);
      usleep(10);
      gear_frame.data[0] = (unsigned int)1 & 0b11111111;  
      AcanPub.publish(gear_frame);
      usleep(10);
      // AcanPub.publish(steering_frame);
      // usleep(10);     
      // AcanPub.publish(light_frame);      
      mtx_.unlock();
    loop_rate.sleep();
  }
}

void VehicleBridge::controlEffortCallback(const std_msgs::Float64& control_effort_input)
{
  // the stabilizing control effort
  scc_frame.header.stamp = ros::Time::now();
  scc_frame.id = 0x303;
  scc_frame.dlc = 4;
  scc_frame.is_error = false;
  scc_frame.is_extended = false;
  scc_frame.is_rtr = false;
  acc_cmd = control_effort_input.data;
  // if(drivingState == DrivingState::NormalDriving){  
  if(gear_info_.gear == 0){
        scc_overwrite_value = ((round(0.0 *100)/100)*100);        
        scc_overwrite = true;
      }
      
    control_effort = round(control_effort_input.data *100)/100;      
    accel_value = (control_effort*100);  
    ROS_INFO("accel_value %d", accel_value);
    scc_frame.data[1] = (accel_value & 0b11111111);
    scc_frame.data[2] = ((accel_value >> 8)&0b11111111);  
  // }
}
void VehicleBridge::SteeringCmdFloatCallback(std_msgs::Float64ConstPtr msg){
  ROS_INFO("!!!");
 steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;
  short steer_value = (short)((msg->data)*gear_ratio*180/PI*10)+steering_offset;
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
}

void VehicleBridge::SteeringCmdCallback(hmcl_msgs::VehicleSteeringConstPtr msg){
  steering_frame.header.stamp = ros::Time::now();
  steering_frame.id = 0x300;
  steering_frame.dlc = 3;
  steering_frame.is_error = false;
  steering_frame.is_extended = false;
  steering_frame.is_rtr = false;
  short steer_value = (short)((msg->steering_angle)*gear_ratio*180/PI*10)+steering_offset;
  ROS_INFO("steer  value : %d", steer_value);
  steering_frame.data[0] = (steer_value & 0b11111111);
	steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
  
}



void VehicleBridge::SetpointCallback(std_msgs::Float64ConstPtr msg){
  setpoint_value = msg->data;
}
  

void VehicleBridge::MissionStateMachine(){
   ros::Rate mission_loop_rate(2); // rate 
   
    double ref_x =  0.0;
    double ref_y = 0.0;
    double dist_to_ref = 1e3;

    double ref_x2 =  0.0;
    double ref_y2 = 0.0;
    double dist_to_ref2 = 1e3;
    while(ros::ok())
  { 

      // ROS_INFO("missionState = %s",stateToString(missionState));
      std_msgs::String missionState_msg;
      missionState_msg.data = stateToString(missionState);
      mission_pub.publish(missionState_msg);

    if(light_on == 1){
        left_lc_msg.data = true;
        right_lc_msg.data = false;
    }else if(light_on == 2)
    {
      left_lc_msg.data = false;
      right_lc_msg.data = true;
    }
    else
    {
      left_lc_msg.data = false;
      right_lc_msg.data = false;
      }
        
        
        
        right_lc_pub.publish(right_lc_msg);
        left_lc_pub.publish(left_lc_msg);  
        

    switch(missionState){
      case MissionState::Init:
          drivingState = DrivingState::Init;
          ref_x = -903.9;
          ref_y = 893.4;
          dist_to_ref = sqrt(pow((ref_x-ego_pose.pose.position.x),2)+pow((ref_y-ego_pose.pose.position.y),2));
          if(dist_to_ref < 5.0){
            missionState = MissionState::LaneChange;
          }
      
      break;

      case MissionState::LaneChange:    
       
      
          ref_x = 238.5;
          ref_y = -73.0;

        

          dist_to_ref = sqrt(pow((ref_x-ego_pose.pose.position.x),2)+pow((ref_y-ego_pose.pose.position.y),2));
          if(dist_to_ref < 5.0){
            missionState = MissionState::ACC;
          }      

          ref_x2 = -746.66;
          ref_y2 = 940.81;
          
          dist_to_ref2 = sqrt(pow((ref_x2-ego_pose.pose.position.x),2)+pow((ref_y2-ego_pose.pose.position.y),2));
          if(dist_to_ref2 < 2.0){
            missionState = MissionState::Incline;
          }  
         
      break;

      case MissionState::ACC:                         
          ref_x = -746.66;
          ref_y = 940.81;
          
          dist_to_ref = sqrt(pow((ref_x-ego_pose.pose.position.x),2)+pow((ref_y-ego_pose.pose.position.y),2));
          if(dist_to_ref < 2.0){
            missionState = MissionState::Incline;
          }           
         
      break;


      case MissionState::Incline:
             // Stop if the vehicle want to stop and reaches low speed 
             if(abs(wheel_info_.wheel_speed) < 0.5 && setpoint_value <= 1.0){
                drivingState = DrivingState::Parking;
              }
              // initialize 
              if(drivingState == DrivingState::Parking && setpoint_value > 1.0){
                   drivingState = DrivingState::Init;
              }

          
      break;

      default:
          ROS_INFO("NA MissionState");
      break;

    }

    mission_loop_rate.sleep();
  }
  
}


void VehicleBridge::TestCase(){
  ros::Rate test_loop_rate(10); // rate 
  int lc = 0;

  while(ros::ok())
  {
    //ROS_INFO("test time = %d",lc);
    
    if(lc == 0) {
      // vehicle_status_.gear_info.gear = 0;
      drivingState = DrivingState::Parking;
      ROS_INFO("Test Case : Parking");
    }

    if(lc == 20) {
      // vehicle_status_.gear_info.gear = 0;
      drivingState = DrivingState::Init;
      ROS_INFO("Test Case : Init");
    }

    // if(lc  > 50 && lc < 150) {
    //   std_msgs::Float64 vel_msg;
    //   vel_msg.data = 40/3.6;
    //   velPub.publish(vel_msg);            
    // }

    // if(lc >  150){
    //   // std_msgs::Float64 vel_msg;
    //   // vel_msg.data = 0.0;
    //   // velPub.publish(vel_msg);            

    //   if(abs(wheel_info_.wheel_speed) < 0.1){
    //     drivingState = DrivingState::Parking;
    //   }

      
    // }

    // if( lc > 150 && drivingState == DrivingState::Parking){
    //   lc =0;
    // }

    
    
    
    lc++; 
    test_loop_rate.sleep();
  }
  
  
}
// Init = 0, NormalDriving = 1, EmergencyBrake = 2, Parking
void VehicleBridge::prevent_brake_system_error(){
  scc_overwrite = false;
  // double acc_cmd = (short)((acan_data->data[2]  << 8)+acan_data->data[1])*0.01;       
  if(acc_cmd < 0){
    switch(drivingState){
      case DrivingState::Init:
          return;
      break;

      case DrivingState::NormalDriving:
        
        if(abs(wheel_info_.wheel_speed) < 0.1){
          scc_overwrite_value = ((round(0.0 *100)/100)*100);        
          scc_overwrite = true;
          // ROS_INFO("scc_overwrite = true");
        }       
        if(gear_info_.gear == 0){
          scc_overwrite_value = ((round(0.0 *100)/100)*100);        
          scc_overwrite = true;
          // ROS_INFO("scc_overwrite = true gear ");
        }
        
      break;

      case DrivingState::EmergencyBrake:
          
          // if(abs(wheel_info_.wheel_speed) < 5/3.6){
          //   scc_overwrite_value = ((round(-7*100)/100)*100);        
          // }
          // else{
          //   scc_overwrite_value = ((round(-7*100)/100)*100);        
          // }

          // scc_overwrite_value = ((round(-10*100)/100)*100);
          // scc_frame.data[1] = (-1000 & 0b11111111);
          // scc_frame.data[2] = ((-1000 >> 8)&0b11111111);

          // AcanPub.publish(scc_frame); 

          scc_overwrite = true;
          // ROS_INFO("scc_overwrite = true emergency brake");
        return;
      break;

      case DrivingState::Parking:
          return;
      break;

      default:
          ROS_INFO("NA state");
      break;

    }
  }
  
}

void VehicleBridge::DrivingStateMachine() {
  ros::Rate state_loop_rate(2); // rate of cmd   
  // cout << "states : " << ND << " " << EB << " " << RS << endl;
  ROS_INFO_ONCE("start state machine");
  while (ros::ok())
  {  
    
    prevent_brake_system_error();

    // ROS_INFO("drivingState = %s",stateToString(drivingState));
    std_msgs::String drivingState_msg;
    drivingState_msg.data = stateToString(drivingState);
    driving_pub.publish(drivingState_msg);

    if(emergency_stop_activate && drivingState != DrivingState::Parking){
      drivingState = DrivingState::EmergencyBrake;      
    }
    int SCC_mode_auto = 2;
    int SCC_mode_off = 0;
    int STR_mode_on = 1;
    int STR_mode_off = 0;
    switch(drivingState){      
      case DrivingState::Init: 
        // AWAIT BEHAVIOR & GO TO DRIVING GEAR -> NORMAL DRIVING STAT
        mtx_.lock();
        ROS_INFO_ONCE("start init");
        // AWAITING BEHAVIOR : Always SCC Ready with 0 accel      
        scc_frame.header.stamp = ros::Time::now();
        scc_frame.id = 0x303;
        scc_frame.dlc = 4;
        scc_frame.is_error = false;
        scc_frame.is_extended = false;
        scc_frame.is_rtr = false;
        scc_frame.data[0] = (unsigned int)SCC_mode_auto & 0b11111111;
        
        scc_frame.data[1] = (-100 & 0b11111111);
        scc_frame.data[2] = ((-100 >> 8)&0b11111111);
        scc_frame.data[3] = (unsigned int)0 & 0b11111111;
        // AcanPub.publish(scc_frame);
        usleep(1000);
        steering_frame.header.stamp = ros::Time::now();
        steering_frame.id = 0x300;
        steering_frame.dlc = 3;
        steering_frame.is_error = false;
        steering_frame.is_extended = false;
        steering_frame.is_rtr = false;
        steering_frame.data[2] = (unsigned int)STR_mode_on & 0b11111111;
        // GO TO DRIVING GEAR        
        // GO TO NORMAL DRIVING STAT
        
        // if (scc_info_.scc_mode == 2) {           
        if (missionState == MissionState::Incline){
            drivingState = DrivingState::NormalDriving;
        }else{
          drivingState = DrivingState::NormalDriving;
        }
        // }
        mtx_.unlock();
      break;  

      case DrivingState::NormalDriving:

        ROS_INFO("normal_driving");
         // NORMAL DRIVING BEHAVIOR
        scc_frame.header.stamp = ros::Time::now();
        scc_frame.id = 0x303;
        scc_frame.dlc = 4;
        scc_frame.is_error = false;
        scc_frame.is_extended = false;
        scc_frame.is_rtr = false;                
        
        AD_GEAR_POS_CMD = 1;
        gear_frame.header.stamp = ros::Time::now();
        gear_frame.id = 0x304;
        gear_frame.dlc = 1;
        gear_frame.is_error = false;
        gear_frame.is_extended = false;
        gear_frame.is_rtr = false;
        gear_frame.data[0] = (unsigned int)AD_GEAR_POS_CMD & 0b11111111;

        
        steering_frame.header.stamp = ros::Time::now();
        steering_frame.id = 0x300;
        steering_frame.dlc = 3;
        steering_frame.is_error = false;
        steering_frame.is_extended = false;
        steering_frame.is_rtr = false;
        steering_frame.data[2] = (unsigned int)STR_mode_on & 0b11111111;
        
        // if(abs(wheel_info_.wheel_speed) < 0.1 && abs(control_effort2) < 0.1){
        //   drivingState = DrivingState::Parking;
        // }
        // else{
        //   drivingState = DrivingState::NormalDriving;
        // }
      break;  

      case DrivingState::EmergencyBrake:
          scc_overwrite_value = ((round(-4.9 *100)/100)*100);  

          scc_frame.data[1] = (-490 & 0b11111111);
          scc_frame.data[2] = ((-490 >> 8)&0b11111111);
          AcanPub.publish(scc_frame);      
          scc_overwrite = true;
          ROS_INFO("over write true emergency driving state");
         if(abs(wheel_info_.wheel_speed) < 0.1){
            drivingState =DrivingState::Parking;            
         }
      break;  

      case DrivingState::Parking:
        // AWAIT BEHAVIOR & GO TO PARKING -> CHECK
        // AWAIT BEHAVIOR     
        mtx_.lock();

         if(abs(wheel_info_.wheel_speed) <= 1 && abs(wheel_info_.wheel_speed) >= 0.1){
          scc_frame.header.stamp = ros::Time::now();
          scc_frame.id = 0x303;
          scc_frame.dlc = 4;
          scc_frame.is_error = false;
          scc_frame.is_extended = false;
          scc_frame.is_rtr = false;        
          scc_frame.data[1] = (-100 & 0b11111111);
          scc_frame.data[2] = ((-100 >> 8)&0b11111111);       
       }
       
        if(abs(wheel_info_.wheel_speed) < 0.1){
      // GO TO PARKING GEAR
        AD_GEAR_POS_CMD = 0;
        gear_frame.header.stamp = ros::Time::now();
        gear_frame.id = 0x304;
        gear_frame.dlc = 1;
        gear_frame.is_error = false;
        gear_frame.is_extended = false;
        gear_frame.is_rtr = false;
        gear_frame.data[0] = (unsigned int)AD_GEAR_POS_CMD & 0b11111111;
        // CHECK GEAR STTAT : PARKING         
       }

        
        scc_frame.header.stamp = ros::Time::now();
        scc_frame.id = 0x303;
        scc_frame.dlc = 4;
        scc_frame.is_error = false;
        scc_frame.is_extended = false;
        scc_frame.is_rtr = false;        
        scc_frame.data[1] = (0 & 0b11111111);
        scc_frame.data[2] = ((0 >> 8)&0b11111111);        
       
        mtx_.unlock();

      break;

      case DrivingState::Incline:
        scc_frame.header.stamp = ros::Time::now();
        scc_frame.id = 0x303;
        scc_frame.dlc = 4;
        scc_frame.is_error = false;
        scc_frame.is_extended = false;
        scc_frame.is_rtr = false;                
        
        AD_GEAR_POS_CMD = 1;
        gear_frame.header.stamp = ros::Time::now();
        gear_frame.id = 0x304;
        gear_frame.dlc = 1;
        gear_frame.is_error = false;
        gear_frame.is_extended = false;
        gear_frame.is_rtr = false;
        gear_frame.data[0] = (unsigned int)AD_GEAR_POS_CMD & 0b11111111;

        
        steering_frame.header.stamp = ros::Time::now();
        steering_frame.id = 0x300;
        steering_frame.dlc = 3;
        steering_frame.is_error = false;
        steering_frame.is_extended = false;
        steering_frame.is_rtr = false;
        steering_frame.data[2] = (unsigned int)STR_mode_on & 0b11111111;

        scc_overwrite_value = ((round(0.1 *100)/100)*100);        
        scc_overwrite = true;
        ROS_INFO("scc_overwrite = true driving state incline");
         if(abs(wheel_info_.wheel_speed) > 0.3){                 
            scc_overwrite = false;       
            scc_overwrite_value = 0.0;
            drivingState =DrivingState::NormalDriving;
         }
      break;

      default:
        ROS_INFO("DRIVING default Mode");
      break; 
    }    
    state_loop_rate.sleep();
  }
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
