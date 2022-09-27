
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

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "planner/vehicle_model.h"


// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


namespace planner{
  
    
VehicleModel::VehicleModel(const ros::NodeHandle& nh_local,const ros::NodeHandle& nh_p):nh_local_(nh_local),nh_p_(nh_p)
{ my_odom_ok_ = false;
  curodom_sub = nh_local_.subscribe("/pose_estimate", 1, &VehicleModel::odomCallback, this);
  return;

  
}

VehicleModel::~VehicleModel()
{}

void VehicleModel::odomCallback(const nav_msgs::OdometryConstPtr& msg){
    cur_odom = *msg;
    double yaw_ = tf2::getYaw(msg->pose.pose.orientation);         
    double global_x = msg->twist.twist.linear.x;
    double global_y = msg->twist.twist.linear.y;    
    double local_vel_x = fabs(global_x*cos(-1*yaw_) - global_y*sin(-1*yaw_)); 
    my_odom_ok_ = true;
}



void VehicleModel::set_state(Eigen::VectorXd state_){
    current_state = state_;
}


void VehicleModel::compute_target(Eigen::VectorXd state_){
  
  double min_dist=10000;
  int min_idx = 0;
  for(int i=0 ; i < target_points.size(); i++){
    double dist_tmp = sqrt(pow((target_points[i].x()-state_(0)),2)+pow((target_points[i].y()-state_(1)),2));
    if(dist_tmp < min_dist){
        min_dist = dist_tmp;
        min_idx = i;
    }
  }
  

    
  double cum_dist = 0.0;
  int found_idx;
  for(int i=min_idx ; i < target_points.size(); i++){
     found_idx = i;
    if(i == target_points.size()-1){
      goal_x = target_points[i].x();
      goal_y = target_points[i].y();
      break;
    }
    else{
      double dist_tmp = sqrt(pow((target_points[i].x()-target_points[i+1].x()),2)+pow((target_points[i].y()-target_points[i+1].y()),2));
      cum_dist += dist_tmp;      
      if(cum_dist > lookahead){
        goal_x = target_points[i].x();
        goal_y = target_points[i].y();
        break;
      }
    }
    
  }
 

  
}

void VehicleModel::set_goal(double x, double y){
    goal_x = x;
    goal_y = y;
}


double VehicleModel::compute_steering(Eigen::VectorXd state){
  double delta = 0.0;
  double diff_x = goal_x - state(0);
  double diff_y = goal_y - state(1);
  double angle_to_diff_vec = atan2(diff_y,diff_x);
  double cur_yaw = state(2);

  amathutils::wrap_yaw_rad(angle_to_diff_vec);
  amathutils::wrap_yaw_rad(cur_yaw);  
  angle_to_diff_vec = angle_to_diff_vec + 4*PI;
  cur_yaw = cur_yaw + 4*PI;
  double angle_to_goal = angle_to_diff_vec- cur_yaw;
  amathutils::wrap_yaw_rad(angle_to_goal);  
  double lookahead_dist = sqrt(diff_x*diff_x+diff_y*diff_y);
  
  double tmp_ = 2*sin(angle_to_goal)*(l_r+l_f)/lookahead_dist;
  delta = atan(tmp_);
  return delta;
}


std::vector<Eigen::VectorXd> VehicleModel::getVehiclePredictedPath(int num_iter){
    // delta = compute_steering(vel);
    Eigen::VectorXd state_tmp = current_state;
    std::vector<Eigen::VectorXd> state_history;
    state_history.push_back(state_tmp);
    for(int i = 0; i < num_iter ; i ++){      
      Eigen::VectorXd next_state= Eigen::VectorXd::Zero(4);
      Eigen::VectorXd tmp_state = state_history.back();
      compute_target(tmp_state);
      double delta = compute_steering(tmp_state);      
      double beta = atan(l_r/(l_r+l_f)*tan(delta));
      double dx = tmp_state(3)*cos(tmp_state(2)+beta);
      double dy = tmp_state(3)*sin(tmp_state(2)+beta);
      double dpsi = tmp_state(3)/l_r*sin(beta);
      next_state(0) = tmp_state(0) + dt*dx;
      next_state(1) = tmp_state(1) + dt*dy;
      double  yaw = tmp_state(2)+dt*dpsi;
      amathutils::wrap_yaw_rad(yaw);
      next_state(2) = yaw;
      next_state(3) = tmp_state(3);
      state_history.push_back(next_state);
    }
    return state_history;
    
}

visualization_msgs::Marker VehicleModel::getPredictedPathMarker(std::vector<Eigen::VectorXd> &state_history){
        visualization_msgs::Marker PathMarker;         
        PathMarker.points.clear();
        PathMarker.header.frame_id = "map";
        PathMarker.header.stamp = ros::Time();        
        PathMarker.id = 2000;
        PathMarker.ns = "predictedPath";                
        PathMarker.pose.position.x = 0.0;
        PathMarker.pose.position.y = 0.0;
        PathMarker.pose.position.z = 0.0;
        PathMarker.type = 4;
        PathMarker.action = visualization_msgs::Marker::ADD;
        PathMarker.scale.x = 0.3;
        PathMarker.color.a = 1.0; 
        PathMarker.color.r = 0.0;
        PathMarker.color.g = 0.0;
        PathMarker.color.b = 1.0;
        for(int i=0;i<state_history.size();i++){                                    
                geometry_msgs::Point point_;                                            
                point_.x = state_history[i](0);                
                point_.y = state_history[i](1);           
                point_.z = 0.5;
                PathMarker.points.push_back(point_);                
          }    
    return PathMarker;
}

nav_msgs::Odometry VehicleModel::state2odom(Eigen::VectorXd &state){
    nav_msgs::Odometry odom_;     
    odom_.pose.pose.position.x = state(0);
    odom_.pose.pose.position.y = state(1);
    odom_.pose.pose.position.z = 1.0;
    
    tf2::Quaternion q_rot;
            q_rot.setRPY(0.0, 0.0, state(2));  
            q_rot.normalize();

    odom_.pose.pose.orientation.x = q_rot[0];
    odom_.pose.pose.orientation.y = q_rot[1];
    odom_.pose.pose.orientation.z = q_rot[2];
    odom_.pose.pose.orientation.w = q_rot[3]; 
    odom_.twist.twist.linear.x = state(3);   
    return odom_;
}


Eigen::VectorXd VehicleModel::pose2state(nav_msgs::Odometry &odom){
    Eigen::VectorXd state_ = Eigen::VectorXd::Zero(5);    
    geometry_msgs::Quaternion quat_; 
    quat_.x = odom.pose.pose.orientation.x;
    quat_.y = odom.pose.pose.orientation.y;
    quat_.z = odom.pose.pose.orientation.z;
    quat_.w = odom.pose.pose.orientation.w;
    tf::Quaternion quat_tf;
    tf::quaternionMsgToTF(quat_, quat_tf);
    // the tf::Quaternion has a method to acess roll pitch and yaw
    double roll, pitch, yaw;
    tf::Matrix3x3(quat_tf).getRPY(roll, pitch, yaw);
    state_(0) = odom.pose.pose.position.x;
    state_(1) = odom.pose.pose.position.y;
    amathutils::wrap_yaw_rad(yaw);
    state_(2) = yaw;
    state_(3) = odom.twist.twist.linear.x;    
    return state_;
}









}