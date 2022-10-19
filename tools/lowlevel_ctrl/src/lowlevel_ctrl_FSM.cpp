
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

void LowlevelCtrl::DrivingStateMachine() {
  ros::Rate state_loop_rate(4); // rate of cmd   
  // cout << "states : " << ND << " " << EB << " " << RS << endl;
  ROS_INFO_ONCE("start state machine");
  while (ros::ok())
  {  
    
    std_msgs::String drivingState_msg;
    drivingState_msg.data = stateToString(drivingState);
    driving_pub.publish(drivingState_msg);

    if(emergency_stop_activate && drivingState != DrivingState::Parking){
      drivingState = DrivingState::EmergencyStop;      
    }    
    
    mtx_.lock();  
    switch(drivingState){    

      case DrivingState::Parking:
        // AWAIT BEHAVIOR & GO TO PARKING -> CHECK
        // AWAIT BEHAVIOR             
        scc_overwrite = true;
        if(abs(wheel_info_.wheel_speed) >= 0.05){          
          setToDrive();   
          short target_dcel = (-2*100);       
          setScc(target_dcel);    
          ROS_INFO("Decel for Parking");             
        }else{          
          setToParking();
          short zero_dcel = (0*100);       
          setScc(zero_dcel);                           
            
        }
        
      break;

      case DrivingState::DrivingStop: 
        scc_overwrite = true;
        if(gear_info_.gear == 0 ){
          short zero_dcel = (0*100);       
          setScc(zero_dcel);  
          setToDrive();        
        }else{
          if(abs(wheel_info_.wheel_speed) > 0.0){
            short target_dcel = (-2*100);       
            setScc(target_dcel);                        
            ROS_WARN("set -200");  
          }else{
            short zero_dcel = (0*100);       
            setScc(zero_dcel);                                               
          }  
        }
      break;  
      
      case DrivingState::Driving:
        scc_overwrite = false;
         if(gear_info_.gear == 0 ){
          setToDrive();        
        }        
      break;  

      case DrivingState::EmergencyStop:
          scc_overwrite = true;
          if(abs(wheel_info_.wheel_speed) >= 0.1){
            short target_dcel = (-4*100);       
            setScc(target_dcel);                
          }else{
            drivingState =DrivingState::Parking;      
          }         
      break;  

      

      default:
        ROS_INFO("DRIVING default Mode");
      break; 
    }    
    
    mtx_.unlock();
    state_loop_rate.sleep();
    
  }
}



void LowlevelCtrl::Test(){
  ros::Rate test_loop_rate(10); // rate 
  int lc = 0;
  while(ros::ok())
  {
    // ROS_INFO("test time = %d",lc);
    mtx_.lock();
    if(lc == 0) {      
      drivingState = DrivingState::Parking;      
    }

    if(lc > 0 && lc < 50) {      
      drivingState = DrivingState::Driving;      
    }

    // if(lc  > 50 && lc < 100) {
    //   drivingState = DrivingState::Driving;      
    // }

    //  if(lc  > 100 && lc < 200) {
    //   drivingState = DrivingState::Driving;      
    // }

    //  if(lc  > 200) {
    //   drivingState = DrivingState::Driving;      
    // }

  //  if(lc  > 200 && lc < 250) {
  //     drivingState = DrivingState::Driving;      
  //   }

  //   if(lc  > 250 && lc < 251) {
  //     drivingState = DrivingState::EmergencyStop;      
  //   }
    mtx_.unlock();
    lc++; 
    test_loop_rate.sleep();
  }
  
  
}

