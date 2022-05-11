
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
  nh_traj_(nh_traj),
  my_steering_ok_(false),
  my_position_ok_(false),
  state_received(false)
{
  

  nh_traj.param<std::string>("pose_topic", pose_topic, "/current_pose");
  nh_traj.param<std::string>("status_topic", status_topic, "/carla/ego_vehicle/vehicle_status");
  nh_traj.param<std::string>("vehicle_states_topic", vehicle_states_topic, "/ctrl_states");
  nh_traj.param<std::string>("control_topic", control_topic, "/hmcl_ctrl_cmd");
  nh_traj.param<std::string>("waypoint_topic", waypoint_topic, "/local_traj");
  nh_traj.param<std::string>("odom_topic", odom_topic, "/carla/ego_vehicle/odometry");
 
   
  nh_traj.param<int>("path_smoothing_times_", path_smoothing_times_, 1);
  nh_traj.param<int>("curvature_smoothing_num_", curvature_smoothing_num_, 35);
  nh_traj.param<int>("path_filter_moving_ave_num_", path_filter_moving_ave_num_, 35);
  nh_traj.param<double>("wheelbase", wheelbase, 2.7);
  nh_traj.param<double>("lf", lf, 1.35);
  nh_traj.param<double>("lr", lr, 1.35);
  nh_traj.param<double>("mass", mass, 1650);    
  nh_traj.param<double>("dt", dt, 0.04); 
  nh_traj.param<double>("delay_in_sec", delay_in_sec, 0.2); 
  nh_traj.param<double>("lag_tau", lag_tau, 0.2); 
  nh_traj.param<int>("preview_step", preview_step, 6); 

  nh_traj.param<double>("Q_ey", Q_ey, 3.0); 
  nh_traj.param<double>("Q_eydot", Q_eydot, 5.0); 
  nh_traj.param<double>("Q_epsi", Q_epsi, 7.0); 
  nh_traj.param<double>("Q_epsidot", Q_epsidot, 1.0); 
  nh_traj.param<double>("R_weight", R_weight, 1500); 
  
  

  nh_traj.param<double>("error_deriv_lpf_curoff_hz", error_deriv_lpf_curoff_hz, 5.0); 
  

  delay_step = (int)(delay_in_sec/dt);
  VehicleModel_.init(dt, wheelbase, lf, lr, mass, delay_step);
  VehicleModel_.setDelayStep(delay_step);  
  VehicleModel_.setLagTau(lag_tau);
  ROS_INFO("lag_tau = %f", lag_tau);
  ROS_INFO("delay_step = %f", delay_step);
 
  lpf_lateral_error_.initialize(dt, error_deriv_lpf_curoff_hz);
  lpf_yaw_error_.initialize(dt, error_deriv_lpf_curoff_hz);


  std::vector<double> Qweight = {Q_ey, Q_eydot, Q_epsi, Q_epsidot};
  VehicleModel_.reintMatrices();
  VehicleModel_.setWeight(Qweight, R_weight);
  
  
  waypointSub = nh_traj.subscribe(waypoint_topic, 2, &PreviewCtrl::callbackRefPath, this);
  poseSub = nh_traj.subscribe(pose_topic, 2, &PreviewCtrl::callbackPose, this);
  StatusSub = nh_traj.subscribe(status_topic, 2, &PreviewCtrl::statusCallback, this);


  steerPub  = nh_ctrl.advertise<hmcl_msgs::VehicleSteering>(control_topic, 2);    
  pub_debug_filtered_traj_ = nh_traj.advertise<visualization_msgs::Marker>("debug/filtered_traj", 1);
    
  boost::thread ControlLoopHandler(&PreviewCtrl::ControlLoop,this);   
  ROS_INFO("Init Preview controller with delay compensation");
  
 
  
  f = boost::bind(&PreviewCtrl::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

PreviewCtrl::~PreviewCtrl()
{}

void PreviewCtrl::callbackPose(const geometry_msgs::PoseStampedConstPtr &msg){
  vehicle_status_.header = msg->header;
  vehicle_status_.pose = msg->pose;
  my_position_ok_ = true;
}

void PreviewCtrl::statusCallback(const carla_msgs::CarlaEgoVehicleStatusConstPtr &msg){
  // recieve longitudinal velocity and steering 
  vehicle_status_.twist.linear.x = msg->velocity;
  vehicle_status_.tire_angle_rad = -1*msg->control.steer;  
  my_steering_ok_ = true;
  
}

void PreviewCtrl::ControlLoop()
{
    ros::Rate loop_rate(25); // rate  

    while (ros::ok()){         
        auto start = std::chrono::steady_clock::now();        
        
        ///////////////////////////////////////////////////////
        // Prepare current State for state feedback control 
        if(!stateSetup()){
          ROS_WARN("Path is not close to the current position");
          continue;
        }
        VehicleModel_.setState(Xk,Cr);
        double current_speed = max(vehicle_status_.twist.linear.x ,1.0); // less than 1m/s takes too much time for riccati solver
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
         
        // Computes control gains 
        ///////////////////////////////////////////////////////
        VehicleModel_.computeMatrices(current_speed);  
        bool riccati_solved = VehicleModel_.solveRiccati();
        if(!riccati_solved){
          ROS_WARN("solution not found ~~~!!!!!!! control lost"); 
          continue;
        }
        VehicleModel_.computeGain();           
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

        ///////////////////////////////////////////////////////
        // record control inputs 
        double delta_cmd = 0.0;        
        delta_buffer.push_back(delta_cmd);
        if(delta_buffer.size()>delay_step){
          delta_buffer.erase(delta_buffer.begin());
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

        auto end = std::chrono::steady_clock::now();     
     loop_rate.sleep();
     std::chrono::duration<double> elapsed_seconds = end-start;
      std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
}


bool PreviewCtrl::stateSetup(){

  const double current_yaw = tf2::getYaw(vehicle_status_.pose.orientation);
  /* calculate nearest point on reference trajectory (used as initial state) */
  unsigned int nearest_index = 0;
  double yaw_err, dist_err, nearest_traj_time;
  geometry_msgs::Pose nearest_pose;
  if (!calcNearestPoseInterp(traj_, vehicle_status_.pose, nearest_pose, nearest_index, dist_err, yaw_err, nearest_traj_time))
  {
    ROS_WARN("[MPC] calculateMPC: error in calculating nearest pose. stop mpc.");
    return false;
  };

  double err_x = vehicle_status_.pose.position.x - nearest_pose.position.x;
  double err_y = vehicle_status_.pose.position.y - nearest_pose.position.y;
  double sp_yaw = tf2::getYaw(nearest_pose.orientation);
  double err_lat = -sin(sp_yaw) * err_x + cos(sp_yaw) * err_y;
  double steer = vehicle_status_.tire_angle_rad;
  state_time = vehicle_status_.header.stamp;
   /* get steering angle */
  
  if(!state_received){
    state_received= true;    
    prev_state_time = vehicle_status_.header.stamp;
    prev_ey = err_lat;
    prev_epsi = yaw_err;
    return true;  
  }else{      
      double diff_time = (prev_state_time-state_time).toSec();
      double eydot = (err_lat-prev_ey)/(diff_time+1e-8);
      double epsidot = yaw_err-prev_epsi;
      eydot = lpf_lateral_error_.filter(eydot);
      epsidot = lpf_yaw_error_.filter(epsidot);    
      Xk = Eigen::VectorXd::Zero(delay_step+5,1);
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
      for(int i=nearest_index; i< min(cuv_size,preview_step+1) ;i++){
        Cr(i) = traj_.k[i];
      }


  }
  prev_state_time = vehicle_status_.header.stamp;
  prev_ey = err_lat;
  prev_epsi = yaw_err;
 
  return true;
 
}



void PreviewCtrl::dyn_callback(preview_ctrl::testConfig &config, uint32_t level)
{
  
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
