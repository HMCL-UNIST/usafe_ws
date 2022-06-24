
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
#include "obj_simulation.h"



using namespace std;

ObjSimulation::ObjSimulation(ros::NodeHandle& nh_):  
  nh_(nh_)
{
  target_state =  Eigen::VectorXd::Zero(5);
  sim_pose_reset = false;
  target_visible = false;
  lane_avail = false;
  target_vehicle_speed = 0.0;  
  distance_to_target = 30.0;
  
  nh_.param<double>("sim_dt", sim_dt, 0.05);

  objPub = nh_.advertise<autoware_msgs::DetectedObjectArray>("/detected_objs", 5);    
 target_vis_pub = nh_.advertise<visualization_msgs::Marker>( "/target_vehicle_viz", 0);

  traj_sub = nh_.subscribe("/local_traj", 2, &ObjSimulation::localTrajCallback, this);
  egoPose_sub = nh_.subscribe("/pose_estimate", 2, &ObjSimulation::egoPoseCallback, this);
  ROS_INFO("obj simulation");
  // boost::thread AcanHandler(&ObjSimulation::AcanSender,this); 
  boost::thread simulation_loop(&ObjSimulation::simulationCallback,this); 
 
  
  f = boost::bind(&ObjSimulation::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

ObjSimulation::~ObjSimulation()
{}


void ObjSimulation::egoPoseCallback(const nav_msgs::OdometryConstPtr msg){
  if(sim_pose_reset){
    sim_pose_reset = false;
  if(!lane_avail){
    
       double current_yaw = amathutils::getPoseYawAngle(msg->pose.pose);
      amathutils::wrap_yaw_rad(current_yaw);
      
      double x_ = msg->pose.pose.position.x + distance_to_target*cos(current_yaw);
      double y_ = msg->pose.pose.position.y + distance_to_target*sin(current_yaw);
      
      target_state(0) = x_;
      target_state(1) = y_;
      target_state(2) = msg->pose.pose.position.z;
      target_state(3) = current_yaw;
      target_state(4) = target_vehicle_speed;

    }
  }

}


void ObjSimulation::simulationCallback(){
    ros::Rate loop_rate(1/sim_dt); // rate  
      while (ros::ok()){
               // target_state -> x, y, z, psi, vel 
            target_state(0) = target_state(0) + target_state(4)*cos(target_state(3))*sim_dt;
            target_state(1) = target_state(1) + target_state(4)*sin(target_state(3))*sim_dt;
            
            autoware_msgs::DetectedObjectArray objs_msg;
            autoware_msgs::DetectedObject obj_msg;
            obj_msg.header.stamp = ros::Time::now();
            obj_msg.header.frame_id = "map";
            obj_msg.valid = true;
            obj_msg.id = 1;
            
            obj_msg.pose.position.x = target_state(0); 
            obj_msg.pose.position.y = target_state(1); 
            obj_msg.pose.position.z = target_state(2); 
            // geometry_msgs::Quaternion quat_ = getQuaternionFromYaw(target_state(3));
            tf2::Quaternion q_rot;
            q_rot.setRPY(0.0, 0.0, target_state(3));  
            q_rot.normalize();

            obj_msg.pose.orientation.x = q_rot[0];
            obj_msg.pose.orientation.y = q_rot[1];
            obj_msg.pose.orientation.z = q_rot[2];
            obj_msg.pose.orientation.w = q_rot[3];

            obj_msg.velocity.linear.x = target_state(4); 

            objs_msg.header = obj_msg.header;
            objs_msg.objects.push_back(obj_msg);

            if(target_visible){
              objPub.publish(objs_msg);

                //////////////////////////////////////////////////
                //////////////////////////////////////////////////
                visualization_msgs::Marker marker;
                marker.header.frame_id = "map";
                marker.header.stamp = ros::Time();
                marker.ns = "my_namespace";
                marker.id = 1;
                marker.type = visualization_msgs::Marker::CUBE;
                marker.action = visualization_msgs::Marker::ADD;
                marker.pose.position.x = obj_msg.pose.position.x;
                marker.pose.position.y = obj_msg.pose.position.y;
                marker.pose.position.z = obj_msg.pose.position.z;
                marker.pose.orientation.x = obj_msg.pose.orientation.x;
                marker.pose.orientation.y = obj_msg.pose.orientation.y;
                marker.pose.orientation.z = obj_msg.pose.orientation.z;
                marker.pose.orientation.w = obj_msg.pose.orientation.w;
                marker.scale.x = 1;
                marker.scale.y = 1;
                marker.scale.z = 1;
                marker.color.a = 1.0; // Don't forget to set the alpha!
                marker.color.r = 0.0;
                marker.color.g = 1.0;
                marker.color.b = 0.0;
                //only if using a MESH_RESOURCE marker type:
                // marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
                target_vis_pub.publish( marker );
                    //////////////////////////////////////////////////
                    //////////////////////////////////////////////////

            }
            loop_rate.sleep();
      }
      ROS_INFO("simulation end");
}


void ObjSimulation::localTrajCallback(const hmcl_msgs::LaneConstPtr msg){
 ego_lane = *msg;  
 lane_avail = true;
 if(sim_pose_reset){
   sim_pose_reset = false;
    if(msg->waypoints.size() > 0){
     
      double current_yaw = amathutils::getPoseYawAngle(msg->waypoints[0].pose.pose);
      amathutils::wrap_yaw_rad(current_yaw);
      
      double x_ = msg->waypoints[0].pose.pose.position.x + distance_to_target*cos(current_yaw);
      double y_ = msg->waypoints[0].pose.pose.position.y + distance_to_target*sin(current_yaw);
      
      target_state(0) = x_;
      target_state(1) = y_;
      target_state(2) = msg->waypoints[0].pose.pose.position.z;


      target_state(3) = current_yaw;
      target_state(4) = target_vehicle_speed;
      ROS_INFO("Target State reset");
    }
  }


}

void ObjSimulation::set_target_state(Eigen::VectorXd new_state){
  target_state = new_state;
}


void ObjSimulation::dyn_callback(obj_simulation::testConfig &config, uint32_t level)
{
  sim_pose_reset =  config.sim_pose_reset;
  target_vehicle_speed    = config.target_vehicle_speed;
  distance_to_target = config.distance_to_target;
  target_visible = config.target_visible;
  

}




int main (int argc, char** argv)
{
  ros::init(argc, argv, "ObjSimulation");
  
  

  ros::NodeHandle nh_;
  ObjSimulation ObjSimulation_(nh_);


    ros::spin();



  return 0;

}
 