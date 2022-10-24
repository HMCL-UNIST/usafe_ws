
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
  nh_(nh), nh_local_(nh_local), nh_p_(nh_p),mission_state(MissionState::InitialSetup)
{
  v2xSub = nh_local_.subscribe("/Mission2", 2, &Usafe::callbackV2X, this); 
   
  missionStatePub = nh_local_.advertise<std_msgs::Float64>("/MissionFSMState", 2, true);      
  lowlevelMissionPub = nh_local_.advertise<hmcl_msgs::BehaviorFactor>("/behavior_factor", 2, true);      
  v2x_received = false;
  
  
  race_planner_ = new planner::RacingLinePlanner(nh_,nh_p_);
  vehicle_model_ = new planner::VehicleModel(nh_local_,nh_p_);
  race_planner_->vehicle_model_ = vehicle_model_;
  
  Above_compute_shortest_path_ = false;
  Below_compute_shortest_path_ = false;
  Sum_compute_shortest_path_ = false;
  positive_cost_assign_ = false;
  f = boost::bind(&Usafe::dyn_callback,this, _1, _2);
	srv.setCallback(f);
  
  boost::thread mission_state_machine_thread(&Usafe::missionFSM,this); 
  
}


Usafe::~Usafe()
{}

void Usafe::missionFSM(){
  double fsm_loop_hz = 1.0;
  ros::Rate loop_rate(fsm_loop_hz); 
  ROS_INFO("Init FSM thread");  
    while (ros::ok())
    {    
      std_msgs::Float64 missionFSMState_; 
      missionFSMState_.data = static_cast<double>(mission_state);
      missionStatePub.publish(missionFSMState_);
      // InitialSetup = 0, WaitforCue = 1, Driving = 2
      int tmp_val;
      hmcl_msgs::BehaviorFactor behav_msgs;
      switch(mission_state){
        case MissionState::InitialSetup:
            behav_msgs.transition_condition.missionStart = false;
            lowlevelMissionPub.publish(behav_msgs);
            if(race_planner_->waypoint_received && v2x_received){
              ROS_INFO("Initial Setup Completed");              
              mission_state = MissionState::WaitforCue;                            
            }else{
                ROS_INFO("Initial Setting up");                                   
            }            
        break;

        case MissionState::WaitforCue:
            mtx.lock();
            
            
            behav_msgs.transition_condition.missionStart = false;
            lowlevelMissionPub.publish(behav_msgs);

            if (v2x_msg.mission_status == 1 || v2x_msg.mission_status == 4){              
               if(race_planner_->global_path_wps.size() > 0){                
                race_planner_->Mission_start = true;                
                mission_state = MissionState::Driving;                
               }
               ROS_INFO("Mission Init!!");
            }else if(v2x_msg.mission_status == 0){
              race_planner_->Mission_start = false;                
              ROS_INFO("Waiting for Mission Start");              
            }else if(v2x_msg.mission_status == 2)
              { 
              race_planner_->Mission_start = false;                
              ROS_INFO("Mission Stop");
            }else if(v2x_msg.mission_status == 3){
              ROS_INFO("Mission Completed");
            }
            mtx.unlock();               
        break;

        case MissionState::Driving:     
            mtx.lock();
            // Publish mission status; 
            
            behav_msgs.transition_condition.missionStart = true;
            lowlevelMissionPub.publish(behav_msgs);

            if(v2x_msg.mission_status == 2)
            { 
              race_planner_->Mission_start = false;    
              mission_state = MissionState::WaitforCue;                  
              ROS_INFO("Mission Stop");
            }else if(v2x_msg.mission_status == 3){
              race_planner_->Mission_start = false; 
              race_planner_->Mission_complete = true;
              mission_state = MissionState::WaitforCue;                                 
              ROS_INFO("Mission Completed");
            }
            mtx.unlock();
        break;

        default:
            ROS_INFO("NA MissionState");
        break;

        
    }
    loop_rate.sleep(); 
  }
}

bool Usafe::areV2xMsgtheSame(const v2x_msgs::Mission2 &msg1, const v2x_msgs::Mission2 &msg2){
  if(msg1.States.size() == 0 || msg2.States.size() == 0 )
    return false;

  for(int i=0; i<msg1.States.size(); i++){
    if(msg1.States[i].pos_lat != msg2.States[i].pos_lat)
      return false;
    if(msg1.States[i].pos_long != msg2.States[i].pos_long)
      return false;
    if(msg1.States[i].item_type != msg2.States[i].item_type)
      return false;
    if(msg1.States[i].score != msg2.States[i].score)
      return false;    
  }
  return true;

}


void Usafe::callbackV2X(const v2x_msgs::Mission2ConstPtr &msg){
// void Usafe::callbackV2X(const hmcl_v2x::HMCL_Mission2ConstPtr &msg){  
  if( msg->States.size() < 1){
    return;
  }
     for(int i=0; i< msg->States.size(); i++){    
    //Override boost waypoint as goal
    // if(msg->States[i].item_type ==3){
    //   mtx.lock();
    //   race_planner_->overwriteGoal(msg->States[i].pos_lat, msg->States[i].pos_long);
      
    //   mtx.unlock();
    // }

    //
    if(msg->States[i].item_type ==3 && msg->States[i].item_status == 1){      
      if(boost_enable_idx.size() > 0){
        if(std::find(boost_enable_idx.begin(), boost_enable_idx.end(), msg->States[i].item_id) != boost_enable_idx.end()){
            continue; // Found element in the history 
        }
      }
        boost_enable_idx.push_back(msg->States[i].item_id);
        ros::Time boost_time = ros::Time::now();  
        mtx.lock();    
        race_planner_->setup_boostup(boost_time, msg->States[i].speed, msg->States[i].duration);
        mtx.unlock();
    }
  }

  if(!v2x_received){
    mtx.lock();
    prev_v2x_msg = *msg;
    v2x_msg = *msg;
    v2x_received = true;    
    ROS_INFO("Init Converting V2x Data!");
    race_planner_->v2x_data=v2x_msg; 
    race_planner_->convert_v2x_data();
     ROS_INFO("Init Computing Global Path");
     race_planner_->compute_global_path();
     mtx.unlock(); 
    return;
  }
  
  
  // mtx.lock();
  v2x_msg = *msg;
  mtx.lock(); 
  race_planner_->v2x_data=v2x_msg; 
  mtx.unlock(); 
 

 ////////////// Update waypoints if so
  if(mission_state == MissionState::InitialSetup || mission_state == MissionState::WaitforCue){
    mtx.lock(); 
    if(!areV2xMsgtheSame(v2x_msg,prev_v2x_msg)){    
    ROS_INFO("Converting V2x Data !!!!!");
     race_planner_->convert_v2x_data();
     ROS_INFO("Computing Global Path ~~~~~");
     race_planner_->compute_global_path();
    }  
    mission_state = MissionState::WaitforCue;    
    mtx.unlock(); 
  }    
  // mtx.unlock();
  prev_v2x_msg = v2x_msg;

  /////////////////////////

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
