
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
#include "purepursuit.h"


using namespace std;

PurePursuit::PurePursuit(ros::NodeHandle& nh_):  
  nh_(nh_)
{  
  local_traj_sub = nh_.subscribe("/local_traj", 1, &PurePursuit::trajCallback, this);
  pose_sub = nh_.subscribe("/geo_pose_estimate", 1, &PurePursuit::poseCallback, this);
  cross_track_err_sub = nh_.subscribe("/geo_pose_estimate", 1, &PurePursuit::cteCallback, this);
  vel_cmd_sub = nh_.subscribe("/", 1, &PurePursuit::velcmdCallback, this);
  // debug_pub = nh_.advertise<std_msgs::Float64>("/path_debug_info", 10);
  // statusPub = nh_light_.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 5);    

  ROS_INFO("Init Traj Debugger");
  // boost::thread PurePursuitNode(&PurePursuit::ctrlPub,this); 
}

PurePursuit::~PurePursuit()
{}

// void PurePursuit::PurePursuit()
// {
//   ros::Rate loop_rate(50);    
//   while (ros::ok())
//   {      
//     double distance = linearInterpolationDistance2D(p0, p1, state);
//     lat_dev.data = distance;
//     // publish vehicle info 
//     debug_pub.publish(lat_dev);
//     loop_rate.sleep();
//   }
// }

void PurePursuit::trajCallback(const hmcl_msgs::Lane& traj)
{
  // local traj callback
  closest_waypoint = traj.waypoints[0].pose.pose.position; // p_w
  cout << "local x : " << closest_waypoint.x << endl;
  cout << "local y : " << closest_waypoint.y << endl;
  ref_path = traj;  
  

}

void PurePursuit::poseCallback(const geometry_msgs::PoseStamped& pose)
{
  state = pose.pose.position; 
}

void PurePursuit::cteCallback(const std_msgs::Float64& cte)
{
  cross_track_err = cte.data; 
}

void PurePursuit::velcmdCallback(const std_msgs::Float64& msg)
{
  vel_cmd = msg.data; // km/h
  r_min_v = pow(vel_cmd, 2) / (127 * (e_MAX + f_MAX));
  if (r_min_v < 5.6) { r_min_v = 5.6; } 
}

// double PurePursuit::selectDesiredPoint(const std_msgs::Float64& vCmd,
// 		const hmcl_msgs::Lane& reference_path,
// 		const geometry_msgs::Point& closest_point, float& r_min_v)
// {
//   for (int i = 0; i < reference_path.size(); i++) {
//     double dx = closest_point.x - reference_path.waypoints[i].pose.pose.position.x;
//     double dy = closest_point.y - reference_path.waypoints[i].pose.pose.position.y;
//     if (r_min_v <= sqrt(pow(dx, 2) + pow(dy, 2))) {
//       // dubins path len calc
//     }
//   }
  
// 	return sign * (v.cross(_state - _p1)).norm()/v.norm();
// }

int main (int argc, char** argv)
{
  ros::init(argc, argv, "Path_Debug");

  ros::NodeHandle nh_;

  PurePursuit PurePursuit_(nh_);

  ros::CallbackQueue callback_queue_debug;
  nh_.setCallbackQueue(&callback_queue_debug);

  std::thread spinner_thread_pp([&callback_queue_debug]() {
    ros::SingleThreadedSpinner spinner_can;
    spinner_can.spin(&callback_queue_debug);
  });

    ros::spin();


    spinner_thread_pp.join();

  return 0;

}
