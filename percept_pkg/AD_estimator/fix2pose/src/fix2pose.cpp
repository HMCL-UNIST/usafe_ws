
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
#include "fix2pose.h"



// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


Fix2Pose::Fix2Pose() :  
  nh_("~"),
  gnss_recieved(false) 
{
  // temporary variables to retrieve parameters
  double l_to_g_sensor_x, l_to_g_sensor_y, l_to_g_sensor_z, l_to_g_sensor_roll, l_to_g_sensor_pich, l_to_g_sensor_yaw;
  std::string local_sensor_frame, global_sensor_frame;
 
  nh_.param<double>("latOrigin", latOrigin, 0.0);
  nh_.param<double>("lonOrigin", lonOrigin, 0.0);
  nh_.param<double>("altOrigin", altOrigin, 0.0);
  
  enu_gnss_.Reset(latOrigin,lonOrigin,altOrigin);


  ahrs_heading_switch = false;
  heading_in_rad = 0.0;
  
  worldGnssPosePub = nh_.advertise<geometry_msgs::PoseStamped>("/gnss_pose_world", 1);  
  debugPub = nh_.advertise<geometry_msgs::PoseStamped>("/gnss/debug", 1);  

  fixgnssPoseSub = nh_.subscribe("/gnss_h_pose", 100, &Fix2Pose::fixgnssPoseSubCallback, this);  

  headingSub = nh_.subscribe("/nav/heading", 10, &Fix2Pose::headingCallback,this);  
  
}

Fix2Pose::~Fix2Pose()
{}

void Fix2Pose::fixgnssPoseSubCallback(geometry_msgs::PoseStampedConstPtr pose){
  
  
  double gnss_pose_global_x, gnss_pose_global_y, gnss_pose_global_z;  
  enu_gnss_.Forward(pose->pose.position.x, pose->pose.position.y, pose->pose.position.z, gnss_pose_global_x, gnss_pose_global_y, gnss_pose_global_z);
  geometry_msgs::PoseStamped global_gnss_pose;
  global_gnss_pose = *pose;
  global_gnss_pose.header.frame_id = pose->header.frame_id;
  global_gnss_pose.pose.position.x = gnss_pose_global_x;
  global_gnss_pose.pose.position.y = gnss_pose_global_y;
  global_gnss_pose.pose.position.z = gnss_pose_global_z;
  ahrs_heading_switch = false;
  if(ahrs_heading_switch){
    tf2::Quaternion q;
    q.setRPY(0, 0, heading_in_rad);
    q=q.normalize();
    global_gnss_pose.pose.orientation.x = q[0];
    global_gnss_pose.pose.orientation.y = q[1];
    global_gnss_pose.pose.orientation.z = q[2];
    global_gnss_pose.pose.orientation.w = q[3];
  }else{
    global_gnss_pose.pose.orientation.x = pose->pose.orientation.x;
    global_gnss_pose.pose.orientation.y = pose->pose.orientation.y;
    global_gnss_pose.pose.orientation.z = pose->pose.orientation.z;
    global_gnss_pose.pose.orientation.w = pose->pose.orientation.w;
  }
  worldGnssPosePub.publish(global_gnss_pose);    
  ahrs_heading_switch = false;
  
  
  
// if(!gnss_recieved){
//     gnss_recieved = true;
//     init_x = global_gnss_pose.pose.position.x;
//     init_y = global_gnss_pose.pose.position.y;    
//   }else{
//   double debug_gradients = atan2((global_gnss_pose.pose.position.y-init_y) , (global_gnss_pose.pose.position.x-init_x))*180/PI;
//   geometry_msgs::PoseStamped debug_msg;
//   debug_msg = global_gnss_pose; 
//   debug_msg.pose.position.x = debug_gradients;
  
//   debugPub.publish(debug_msg);
//   }
  
  
  // tf::Transform transform;
  // // transform.setOrigin( tf::Vector3(gnss_pose_global_x, gnss_pose_global_y, gnss_pose_global_z) );
  // // tf::Quaternion q(pose->pose.orientation.x,pose->pose.orientation.y,pose->pose.orientation.z,pose->pose.orientation.w);
  // transform.setOrigin( tf::Vector3(0,0,0) );
  // tf::Quaternion q(0,0,0,1);

  // transform.setRotation(q);
  // gnss_to_map_br.sendTransform(tf::StampedTransform(transform, pose->header.stamp, "map", "gnss_link"));

}

void Fix2Pose::headingCallback(microstrain_inertial_msgs::FilterHeadingConstPtr msg){
  ahrs_heading_switch = true;
  //  (90.0-float(item_list[1]))*math.pi/180 
    // heading_in_rad = msg->heading_rad;
    // heading_in_rad = M_PI/2.0 - msg->heading_rad; 
    
    heading_in_rad =  - msg->heading_rad; 
    
    while(heading_in_rad > M_PI){
      heading_in_rad = heading_in_rad - 2*M_PI;
    }
    while(heading_in_rad < -M_PI){
      heading_in_rad = heading_in_rad + 2*M_PI;
    }
    
}


int main (int argc, char** argv)
{
ros::init(argc, argv, "Fix2Pose");
Fix2Pose Fix2Pose_;
ros::spin();
}
