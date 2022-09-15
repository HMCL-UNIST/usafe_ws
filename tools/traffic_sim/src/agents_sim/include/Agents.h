
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

#include <sstream>
#include <string>
#include <list>
#include <mutex>
#include <queue>
#include <math.h>
#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <ros/package.h>
#include <eigen3/Eigen/Geometry>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <amathutils.hpp>
#include <geometry_msgs/Quaternion.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#define PI 3.14159265358979323846264338

#include <lanelet2_core/LaneletMap.h>
#include <lanelet2_core/geometry/LaneletMap.h>
#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_io/io_handlers/Factory.h>
#include <lanelet2_io/io_handlers/Writer.h>
#include <lanelet2_projection/UTM.h>

#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include <lanelet2_traffic_rules/TrafficRulesFactory.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>


class Agents 
{
  
protected:
// state = x, y, yaw, Vspeed
Eigen::VectorXd current_state= Eigen::VectorXd::Zero(5);
std::vector<std::vector<double>> target_pose;
geometry_msgs::PoseStamped current_pose;
nav_msgs::Odometry current_odom;
int agents_type; 
double l_r = 1.5;
double l_f = 1.5;
double dt = 0.1;
static int agents_id;
int agent_id;


public:
Agents(){
    agent_id = agents_id;
    agents_id++;    
}
// ~Agents();

hmcl_msgs::LaneArray targetLaneArray;
hmcl_msgs::Lane targetLane;
lanelet::Areas targetArea;
visualization_msgs::MarkerArray targetLaneMarker;
bool isvehicle;



Eigen::VectorXd pose2state(nav_msgs::Odometry &odom){
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

geometry_msgs::Pose getPose(){
      geometry_msgs::Pose pose;     
    pose.position.x = current_state(0);
    pose.position.y = current_state(1);
    pose.position.z = 1.0;    
    tf2::Quaternion q_rot;
            q_rot.setRPY(0.0, 0.0, current_state(2));  
            q_rot.normalize();
    pose.orientation.x = q_rot[0];
    pose.orientation.y = q_rot[1];
    pose.orientation.z = q_rot[2];
    pose.orientation.w = q_rot[3];     
    return pose;
}

nav_msgs::Odometry state2odom(Eigen::VectorXd &state){
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



void set_state(Eigen::VectorXd state_){
    current_state = state_;
}

void update(double vel, double delta){
    double beta = atan(l_r/(l_r+l_f)*tan(delta));
    double dx = vel*cos(current_state(2)+beta);
    double dy = vel*sin(current_state(2)+beta);
    double dpsi = vel/l_r*sin(beta);
    current_state(0) += dt*dx;
    current_state(1) += dt*dy;
    double  yaw = current_state(2)+dt*dpsi;
    amathutils::wrap_yaw_rad(yaw);
    current_state(2) = yaw;
    current_state(3) = vel;
}

void update_step(double vel){
    if (targetLane.waypoints.size() < 1){
    return;
    }  
    hmcl_msgs::Waypoint front_wp = targetLane.waypoints[0]; 
    hmcl_msgs::Waypoint wp_ = targetLane.waypoints[targetLane.waypoints.size()-1];    
    double theta = atan2((-current_state(1)+wp_.pose.pose.position.y),(-current_state(0)+wp_.pose.pose.position.x));
    current_state(0) = current_state(0)+ cos(theta)*vel*dt;
    current_state(1) = current_state(1)+ sin(theta)*vel*dt;

    geometry_msgs::Quaternion quat_; 
    quat_.x = front_wp.pose.pose.orientation.x;
    quat_.y = front_wp.pose.pose.orientation.y;
    quat_.z = front_wp.pose.pose.orientation.z;
    quat_.w = front_wp.pose.pose.orientation.w;
    tf::Quaternion quat_tf;
    tf::quaternionMsgToTF(quat_, quat_tf);
    // the tf::Quaternion has a method to acess roll pitch and yaw
    double roll, pitch, target_yaw;
    tf::Matrix3x3(quat_tf).getRPY(roll, pitch, target_yaw);
    current_state(2) = target_yaw;
    current_state(3) = vel;
}

visualization_msgs::Marker get_rviz_marker(){
    visualization_msgs::Marker marker;
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();
        marker.ns = "agents";
        marker.id = agent_id;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::ADD;
        tf2::Quaternion q_rot;
        q_rot.setRPY(0.0, 0.0, current_state(2));  
        q_rot.normalize();
        marker.pose.position.x = current_state(0);
        marker.pose.position.y = current_state(1);
        marker.pose.position.z = 1.0;
        marker.pose.orientation.x = q_rot.x();
        marker.pose.orientation.y = q_rot.y();
        marker.pose.orientation.z = q_rot.z();
        marker.pose.orientation.w = q_rot.w();
        marker.scale.x = 4.2;
        marker.scale.y = 1.9;
        marker.scale.z = 1.5;
        marker.color.a = 0.5; // Don't forget to set the alpha!
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
    return marker;
}

void get_ros_msg();
void set_target_waypoints(std::vector<double> target_pose_);

};

int Agents::agents_id = 0;


