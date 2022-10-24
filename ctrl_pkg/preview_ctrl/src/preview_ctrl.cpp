
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

int test_count = 0;
using namespace std;

PreviewCtrl::PreviewCtrl(ros::NodeHandle& nh_ctrl, ros::NodeHandle& nh_traj):  
  nh_ctrl_(nh_ctrl),
  nh_traj_(nh_traj),
  my_steering_ok_(false),
  my_position_ok_(false),
  my_odom_ok_(false),
  state_received(false)
{
  

  // nh_traj.param<std::string>("pose_topic", pose_topic, "/current_pose");
  nh_traj.param<std::string>("pose_topic", pose_topic, "/pose_estimate");  
  nh_traj.param<std::string>("simstatus_topic", simstatus_topic, "/carla/ego_vehicle/vehicle_status");
  nh_traj.param<std::string>("status_topic", status_topic, "/vehicle_status");  
  nh_traj.param<std::string>("vehicle_states_topic", vehicle_states_topic, "/ctrl_states");
  nh_traj.param<std::string>("control_topic", control_topic, "/hmcl_ctrl_cmd");
  nh_traj.param<std::string>("waypoint_topic", waypoint_topic, "/local_traj");
  // nh_traj.param<std::string>("odom_topic", odom_topic, "/carla/ego_vehicle/odometry");
  nh_traj.param<std::string>("odom_topic", odom_topic, "pose_estimate");

  nh_traj.param<std::string>("steer_cmd_topic", steer_cmd_topic, "/usafe_steer_cmd");
  nh_traj.param<std::string>("vel_cmd_topic", vel_cmd_topic, "/setpoint");
  
  
  
  nh_traj.param<int>("path_smoothing_times_", path_smoothing_times_, 1);
  nh_traj.param<int>("curvature_smoothing_num_", curvature_smoothing_num_, 35);
  nh_traj.param<int>("path_filter_moving_ave_num_", path_filter_moving_ave_num_, 35);
  nh_traj.param<double>("angle_rate_limit", angle_rate_limit, 0.5); // rad/s 
  nh_traj.param<double>("wheelbase", wheelbase, 2.6);
  nh_traj.param<double>("lf", lf, 1.35);
  nh_traj.param<double>("lr", lr, 1.25);
  nh_traj.param<double>("mass", mass, 1800);    
  nh_traj.param<double>("dt", dt, 0.04); 
  nh_traj.param<double>("delay_in_sec", delay_in_sec, 0.14); 
  nh_traj.param<double>("lag_tau", lag_tau, 0.14); 
  nh_traj.param<int>("preview_step", preview_step, 50); 

  nh_traj.param<double>("Q_ey", Q_ey, 3.0); 
  nh_traj.param<double>("Q_eydot", Q_eydot, 5.0); 
  nh_traj.param<double>("Q_epsi", Q_epsi, 7.0); 
  nh_traj.param<double>("Q_epsidot", Q_epsidot, 1.0); 
  nh_traj.param<double>("R_weight", R_weight, 4500); 
  nh_traj.param<bool>("controller_for_low_speed", controller_for_low_speed, false);
  controller_for_low_speed = true;

  nh_traj.param<double>("error_deriv_lpf_curoff_hz", error_deriv_lpf_curoff_hz, 5); 
  
  prev_delta_cmd = 0.0;
  delay_step = (int)(delay_in_sec/dt);
  VehicleModel_.setDelayStep(delay_step);  
  VehicleModel_.setLagTau(lag_tau);
  VehicleModel_.initModel(dt, wheelbase, lf, lr, mass);

  ROS_INFO("lag_tau = %f", lag_tau);
  ROS_INFO("delay_step = %f", delay_step);
 
  lpf_lateral_error_.initialize(dt, error_deriv_lpf_curoff_hz);
  lpf_yaw_error_.initialize(dt, error_deriv_lpf_curoff_hz);
  lpf_ey.initialize(dt, error_deriv_lpf_curoff_hz);
  lpf_epsi.initialize(dt, error_deriv_lpf_curoff_hz);
  
  if(controller_for_low_speed){
    steer_filter.initialize(dt, 1.5); // 5 for high speed , 1.5 for low speed
  }else{
    steer_filter.initialize(dt, 5); // 5 for high speed , 1.5 for low speed
  }

  yaw_filter.initialize(dt, 5.0);


  std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
  VehicleModel_.reintMatrices();
  VehicleModel_.setWeight(Qweight, R_weight);
  
  
  waypointSub = nh_traj.subscribe(waypoint_topic, 2, &PreviewCtrl::callbackRefPath, this);
  // poseSub = nh_traj.subscribe(pose_topic, 2, &PreviewCtrl::callbackPose, this);
  
  simStatusSub = nh_traj.subscribe(simstatus_topic, 2, &PreviewCtrl::simstatusCallback, this);
  StatusSub = nh_traj.subscribe(status_topic, 2, &PreviewCtrl::statusCallback, this);
  
  
  odomSub = nh_traj.subscribe(odom_topic, 2, &PreviewCtrl::odomCallback, this);
  
  debugPub  = nh_ctrl.advertise<geometry_msgs::PoseStamped>("preview_debug", 2);    
  steerPub  = nh_ctrl.advertise<hmcl_msgs::VehicleSteering>(steer_cmd_topic, 2);   
  // velPub  = nh_ctrl.advertise<std_msgs::Float64>(vel_cmd_topic, 2);   
  
  pub_debug_filtered_traj_ = nh_traj.advertise<visualization_msgs::Marker>("debug/filtered_traj", 1);
  ackmanPub = nh_ctrl.advertise<ackermann_msgs::AckermannDrive>("/carla/ego_vehicle/ackermann_cmd", 2);    

  AcanPub = nh_ctrl.advertise<can_msgs::Frame>("/a_can_h2l", 5);    

  
   


  boost::thread ControlLoopHandler(&PreviewCtrl::ControlLoop,this);   
  ROS_INFO("Init Preview controller with delay compensation");
  
 
  
  f = boost::bind(&PreviewCtrl::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

PreviewCtrl::~PreviewCtrl()
{}

void PreviewCtrl::odomCallback(const nav_msgs::OdometryConstPtr& msg){
    
    vehicle_status_.header = msg->header;
    vehicle_status_.pose = msg->pose.pose;
    
    // Shift position 
    double yaw_ = normalizeRadian(tf2::getYaw(msg->pose.pose.orientation));
    // double shift_local_x = -1.35;
    // vehicle_status_.pose.position.x += shift_local_x*cos(yaw_);
    // vehicle_status_.pose.position.y += shift_local_x*sin(yaw_);
    
    
    my_position_ok_ = true;

            
    double global_x = msg->twist.twist.linear.x;
    double global_y = msg->twist.twist.linear.y;
         
    vehicle_status_.twist.linear.x = fabs(global_x*cos(-1*yaw_) - global_y*sin(-1*yaw_));
    vehicle_status_.twist.linear.y = global_x*sin(-1*yaw_) + global_y*cos(-1*yaw_);
    vehicle_status_.twist.angular.z = msg->twist.twist.angular.z;    
    my_odom_ok_ = true;
}


void PreviewCtrl::reschedule_weight(double speed){

  
      if(speed > 30/3.6){
        // For high speed
        Q_ey = 3.5;
        Q_eydot = 5.0;
        Q_epsi = 25.0;
        Q_epsidot = 1.0;
        R_weight = 4500.0;
        std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
      // double tmp_q = -0.18*speed+7 ; // -0.1*speed*3.6 + 7;      
      // tmp_q = std::min(std::max(tmp_q,3.5),7.0);
      // // double tmp_ydot_q = 0.18*speed+7;
      // // tmp_ydot_q = std::min(std::max(tmp_ydot_q,7.0),11.0);
      // double tmp_r = 80*speed*3.6 + 500;
      // tmp_r = std::min(std::max(tmp_r,1000.0),4500.0);
      // Qweight[0] = tmp_q;
      // // Qweight[2] = tmp_ydot_q;
      // R_weight = tmp_r;
      VehicleModel_.setWeight( Qweight, R_weight);
      }else if(speed > 20/3.6){
         Q_ey = 3.0;
        Q_eydot = 5.0;
        Q_epsi = 7.0;
        Q_epsidot = 1.0;
        R_weight = 2500.0;
        std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
      VehicleModel_.setWeight( Qweight, R_weight);
      }else{ //curve
        std::vector<double> Qweight = {30.0, 40.0, 10.0, 5.0};
        R_weight = 500;
        VehicleModel_.setWeight( Qweight, R_weight);
      }
        // For Low speed  
        // ROS_WARN("low speed tune");       
      // std::vector<double> Qweight = {20.0, 30.0, 2.0, 1.0};
}

void PreviewCtrl::steering_rate_reset(double speed){
    // if (speed *3.6 >= 0 && speed *3.6 < 10) {
    //   angle_rate_limit = 0.5;
    // }

    // if (speed *3.6 >= 10 && speed *3.6 < 20) {
    //   angle_rate_limit = 0.4;
    // }

    // if (speed *3.6 >= 20 && speed *3.6 < 30) {
    //   angle_rate_limit = 0.3;
    // }

    // if (speed *3.6 >= 30 && speed *3.6 < 40) {
    //   angle_rate_limit = 0.2;
    // }

    // if (speed *3.6 >= 40) {
    //   angle_rate_limit = 0.1;
    // }

    // angle_rate_limit = -0.01*speed*3.6 +0.6;
    if(speed > 40/3.6){
      // angle_rate_limit = -0.0131*speed*3.6 +0.647;
      
      // angle_rate_limit = std::min(std::max(angle_rate_limit,0.1),0.5);
        angle_rate_limit = 0.1;
    }else if(speed > 30/3.6 && speed <= 40/3.6){
      angle_rate_limit = 0.2;
    }else{
        angle_rate_limit = 20;
    }
    
    
}
// void PreviewCtrl::callbackPose(const geometry_msgs::PoseStampedConstPtr &msg){
//   vehicle_status_.header = msg->header;
//   vehicle_status_.pose = msg->pose;
//   my_position_ok_ = true;
// }
void PreviewCtrl::statusCallback(const hmcl_msgs::VehicleStatusConstPtr& msg){
  // recieve longitudinal velocity and steering 
   
    wheel_speed = msg->wheelspeed.wheel_speed;
    reschedule_weight(wheel_speed);
    steering_rate_reset(wheel_speed);
      // if(wheel_speed > 0){
        // vehicle_status_.twist.linear.x = wheel_speed;
        // if(fabs(vehicle_status_.twist.linear.x - wheel_speed) > 3){
        //   vehicle_status_.twist.linear.x = wheel_speed;
        // }
      // }
      vehicle_status_.tire_angle_rad = msg->steering_info.steering_angle;        
  my_steering_ok_ = true;
  
}

void PreviewCtrl::simstatusCallback(const carla_msgs::CarlaEgoVehicleStatusConstPtr &msg){
  // recieve longitudinal velocity and steering 
  vehicle_status_.twist.linear.x = msg->velocity;
  vehicle_status_.tire_angle_rad = -1*msg->control.steer;  
  my_steering_ok_ = true;
  
}

void PreviewCtrl::ControlLoop()
{
    ros::Rate loop_rate(20); // rate  

    while (ros::ok()){         
        auto start = std::chrono::steady_clock::now();        
        
        ///////////////////////////////////////////////////////

        // Prepare current State for state feedback control 
        if(!stateSetup()){
          ROS_WARN("Path is not close to the current position");
           loop_rate.sleep();
          continue;
        }
        VehicleModel_.setState(Xk,Cr);
        double current_speed = max(vehicle_status_.twist.linear.x ,1.5); // less than 1m/s takes too much time for riccati solver
        // double current_speed = max(wheel_speed,1.0); // less than 1m/s takes too much time for riccati solver
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
         
        // Computes control gains 
        ///////////////////////////////////////////////////////
       
           
        VehicleModel_.computeMatrices(current_speed);  

        
        bool riccati_solved = VehicleModel_.solveRiccati();
        if(!riccati_solved){
          ROS_WARN("solution not found ~~~!!!!!!! control lost"); 
           loop_rate.sleep();
          continue;
        }
        double delta_cmd = VehicleModel_.computeGain(); 
        
        // if(fabs(delta_cmd) > 0.5){
        //    loop_rate.sleep();
        //   continue;
        // }                  


        // concatenate via angular limit
        double diff_delta = delta_cmd-prev_delta_cmd;
        
        
        
        if( fabs(diff_delta)/dt > angle_rate_limit ){
          ROS_WARN("rate limit reached!!! angle_rate_limit = %f",angle_rate_limit);
          if(diff_delta>0){
              delta_cmd = prev_delta_cmd + angle_rate_limit*dt;
          }else{
              delta_cmd = prev_delta_cmd - angle_rate_limit*dt;
          }
        }
        
        // extract target velocity  (avg of local segments)
        double avg_speed_sum = std::accumulate(std::begin(traj_.vx), std::end(traj_.vx), 0.0);
        double avg_speed =  avg_speed_sum / traj_.vx.size();
        // curvature and maximum lateral accerlation filtering 
        double alat_lim = 0.2;
        double kappa = 0;
        double cur_lim_vel = sqrt(alat_lim/kappa);
        double target_speed = std::min(avg_speed,cur_lim_vel);
      //////////////////////////////////////////////////
      ////////////////////////////////////////////////// Lateral error filter 
        // filter by error , 0.3 m is margin 
        // 1m error -> reduce to 20%
        // 0.5m error -> reduce to 60%
        // Y = -0.8X + 1
      //////////////////////////////////////////////////
        // double l_lim= 0.2;        
        // double filter_ratio = -0.8*std::max(l_lim, Xk(0))+1;
        // filter_ratio = std::max(l_lim,std::min(filter_ratio,1.0));
        // target_speed = target_speed*filter_ratio;
      //////////////////////////////////////////////////
        // ROS_INFO("target_speed = %f", target_speed);
        std_msgs::Float64 vel_msg;
        vel_msg.data = target_speed;
        // velPub.publish(vel_msg);
        debug_msg.pose.position.x = delta_cmd;    
        delta_cmd = steer_filter.filter(delta_cmd);            
        debug_msg.pose.position.y = delta_cmd;    
        
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
        ackermann_msgs::AckermannDrive ctrl_msg;
        ctrl_msg.acceleration = 1.0;        
       
        
        ctrl_msg.steering_angle = delta_cmd;
        
        ackmanPub.publish(ctrl_msg);
        
        //////////////////
        can_msgs::Frame steering_frame;
        steering_frame.header.stamp = ros::Time::now();
        steering_frame.id = 0x300;
        steering_frame.dlc = 3;
        steering_frame.is_error = false;
        steering_frame.is_extended = false;
        steering_frame.is_rtr = false;        
        short steer_value = (short)(delta_cmd*15.0*180/PI*10+steering_offset);
        // ROS_INFO("delta_cmd = %f", delta_cmd);
        prev_delta_cmd = delta_cmd;
        steering_frame.data[0] = (steer_value & 0b11111111);
	      steering_frame.data[1] = ((steer_value >> 8)&0b11111111);
        steering_frame.data[2] = (unsigned int)1 & 0b11111111;
        // AcanPub.publish(steering_frame);
          

        ///////////
        
        
        
        hmcl_msgs::VehicleSteering steer_msg;
        
        steer_msg.header.stamp = ros::Time::now();
        steer_msg.steering_angle = delta_cmd;        

        steerPub.publish(steer_msg);
        ///////////////////////////////////////////////////////
        // record control inputs 
        delta_buffer.push_back(delta_cmd);
        if(delta_buffer.size()>delay_step){
          delta_buffer.erase(delta_buffer.begin());
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

      auto end = std::chrono::steady_clock::now();     
     loop_rate.sleep();
     std::chrono::duration<double> elapsed_seconds = end-start;
     if ( elapsed_seconds.count() > dt){
       ROS_ERROR("computing control gain takes too much time");
       std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
     }
      
    }
}


bool PreviewCtrl::stateSetup(){

  current_yaw = tf2::getYaw(vehicle_status_.pose.orientation);
  // debug_msg.pose.orientation.x = current_yaw;        
  yaw_filter.filter(current_yaw);
  // debug_msg.pose.orientation.y = current_yaw; 
  debug_yaw = current_yaw;
  /* calculate nearest point on reference trajectory (used as initial state) */
  unsigned int nearest_index = 0;
  double yaw_err, dist_err, nearest_traj_time;
  geometry_msgs::Pose nearest_pose;
  if (!calcNearestPoseInterp(traj_, vehicle_status_.pose, nearest_pose, nearest_index, dist_err, yaw_err, nearest_traj_time))
  {
    ROS_WARN("error in calculating nearest pose. stop mpc.");
    return false;
  };

  double err_x = vehicle_status_.pose.position.x - nearest_pose.position.x;
  double err_y = vehicle_status_.pose.position.y - nearest_pose.position.y;
  double sp_yaw = tf2::getYaw(nearest_pose.orientation);
  double err_lat = -sin(sp_yaw) * err_x + cos(sp_yaw) * err_y + 0.1;  
  double steer = vehicle_status_.tire_angle_rad;
  state_time = vehicle_status_.header.stamp;
   /* get steering angle */
  Xk = Eigen::VectorXd::Zero(delay_step+5,1);
  Cr = Eigen::VectorXd::Zero(preview_step+1);  

     

  if(!state_received){
    state_received= true;    
    prev_state_time = vehicle_status_.header.stamp;
    prev_ey = err_lat;
    prev_epsi = yaw_err;
    return true;  
  }else{      
      double diff_time = dt; //(state_time - prev_state_time).toSec();      
      double eydot = (err_lat-prev_ey)/(diff_time+1e-15);      
      double epsidot = yaw_err-prev_epsi;
      eydot = lpf_lateral_error_.filter(eydot);
      epsidot = lpf_yaw_error_.filter(epsidot);    
      Xk = Eigen::VectorXd::Zero(delay_step+5,1);      
      // err_lat = lpf_ey.filter(err_lat);
      // yaw_err = lpf_epsi.filter(yaw_err);      
      Xk(0) = err_lat;
      Xk(1) = eydot;
      Xk(2) = yaw_err;
      Xk(3) = epsidot;
      Xk(4) = steer;      

      for(int i=0; i < delta_buffer.size(); i++){
        Xk(5+i) = delta_buffer[i];
      }

      
      Cr = Eigen::VectorXd::Zero(preview_step+1);      
      int cuv_size = traj_.k.size()-nearest_index;
      for(int i=0; i< min(cuv_size,preview_step+1) ;i++){
        Cr(i) = traj_.k[nearest_index+i];
      }

      debug_msg.header.stamp = ros::Time::now();    
      debug_msg.pose.orientation.x = err_lat;  
      debug_msg.pose.orientation.y = eydot;  
      debug_msg.pose.orientation.z = yaw_err*180.0/3.14195;    
      debug_msg.pose.orientation.w = epsidot; 
      // debug_msg.pose.position.z = debug_yaw*180/PI;
      // debug_msg.pose.orientation.x = VehicleModel_.debug_preview_feedback; // ;
      // debug_msg.pose.orientation.y = Xk(0); // ;        
      // debug_msg.pose.orientation.z = Xk(2)*180/PI;
      // debug_msg.pose.orientation.w = VehicleModel_.debug_state_feedback;
      debugPub.publish(debug_msg);


  }
  prev_state_time = vehicle_status_.header.stamp;
  prev_ey = err_lat;
  prev_epsi = yaw_err;
 
  return true;
 
}



void PreviewCtrl::dyn_callback(preview_ctrl::testConfig &config, uint32_t level)
{
  return ;
  ROS_INFO("Dynamiconfigure updated");
  config_switch = config.config_switch;
  if(config_switch){
  Q_ey = config.Q_ey;
  Q_eydot = config.Q_eydot;
  Q_epsi = config.Q_epsi ;
  Q_epsidot = config.Q_epsidot;
  R_weight = config.R_weight;  
  angle_rate_limit = config.angle_rate_limit;
  // lag_tau = config.lag_tau;
  // delay_in_sec = config.delay_in_sec;
  // delay_step = (int)(delay_in_sec/dt);
  // std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
      // double tmp_q = -0.1*speed*3.6 + 7;
      // tmp_q = std::min(std::max(tmp_q,3.0),7.0);
      // double tmp_r = 80*speed*3.6 + 500;
      // tmp_r = std::min(std::max(tmp_r,1000.0),4000.0);

      // Qweight[0] = tmp_q;
      // R_weight = tmp_r;
      // VehicleModel_.setWeight( Qweight, R_weight);


  
  std::vector<double> Qweight_ = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
  VehicleModel_.setWeight( Qweight_, R_weight);
  // VehicleModel_.setDelayStep(delay_step);  
  // VehicleModel_.setLagTau(lag_tau);
  }

  
}






void PreviewCtrl::callbackRefPath(const hmcl_msgs::Lane::ConstPtr &msg)
{
  current_waypoints_ = *msg;  
 
         


  Trajectory traj;
  /* calculate relative time */
  std::vector<double> relative_time;
  calcPathRelativeTime(current_waypoints_, relative_time);  

  /* resampling */
  double traj_resample_dist_ = dt;
  convertWaypointsToMPCTrajWithDistanceResample(current_waypoints_, relative_time, traj_resample_dist_, traj);
  convertEulerAngleToMonotonic(traj.yaw);
  /* path smoothing */
  bool enable_path_smoothing_ =true;
  if (enable_path_smoothing_)
  {
    for (int i = 0; i < path_smoothing_times_; ++i)
    {
      if (!MoveAverageFilter::filt_vector(path_filter_moving_ave_num_, traj.x) ||
          !MoveAverageFilter::filt_vector(path_filter_moving_ave_num_, traj.y) ||
          !MoveAverageFilter::filt_vector(path_filter_moving_ave_num_, traj.yaw) ||
          !MoveAverageFilter::filt_vector(path_filter_moving_ave_num_, traj.vx))
      {
        ROS_WARN("path callback: filtering error. stop filtering");
        return;
      }
    }
  }

  /* calculate yaw angle */
  bool enable_yaw_recalculation_=true;
  if (enable_yaw_recalculation_)
  {
    calcTrajectoryYawFromXY(traj);
    convertEulerAngleToMonotonic(traj.yaw);
  }

  /* calculate curvature */
  calcTrajectoryCurvature(traj, curvature_smoothing_num_);
  const double max_k = *max_element(traj.k.begin(), traj.k.end());
  const double min_k = *min_element(traj.k.begin(), traj.k.end());  

  traj_ = traj;

  /* publish trajectory for visualize */
  visualization_msgs::Marker markers;
  convertTrajToMarker(traj, markers, "ref_traj", 0.0, 0.5, 1.0, 0.05);
  pub_debug_filtered_traj_.publish(markers);
  
};


void PreviewCtrl::convertTrajToMarker(const Trajectory &traj, visualization_msgs::Marker &marker,
                                      std::string ns, double r, double g, double b, double z)
{
  marker.points.clear();
  marker.header.frame_id = current_waypoints_.header.frame_id;
  marker.header.stamp = ros::Time();
  marker.ns = ns;
  marker.id = 0;
  marker.type = visualization_msgs::Marker::LINE_STRIP;
  marker.action = visualization_msgs::Marker::ADD;
  marker.scale.x = 0.15;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;
  marker.color.a = 0.9;
  marker.color.r = r;
  marker.color.g = g;
  marker.color.b = b;
  for (unsigned int i = 0; i < traj.x.size(); ++i)
  {
    geometry_msgs::Point p;
    p.x = traj.x.at(i);
    p.y = traj.y.at(i);
    p.z = traj.z.at(i) + z;
    marker.points.push_back(p);
  }



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
