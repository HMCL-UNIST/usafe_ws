
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
#include "path_debug.h"

using namespace std;

PathDebug::PathDebug(ros::NodeHandle& nh_):  
  nh_(nh_)
{  
  local_traj_sub = nh_.subscribe("/local_traj", 1, &PathDebug::trajCallback, this);
  pose_sub = nh_.subscribe("/geo_pose_estimate", 1, &PathDebug::poseCallback, this);
  debug_pub = nh_.advertise<geometry_msgs::PointStamped>("/path_debug_info", 10);
  // statusPub = nh_light_.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 5);    

  ROS_INFO("Init Traj Debugger");
  boost::thread PathDebugger(&PathDebug::debugPub,this); 
}

PathDebug::~PathDebug()
{}

void PathDebug::debugPub()
{
  ros::Rate loop_rate(50);    
  while (ros::ok())
  {      
    double distance = linearInterpolationDistance2D(p0, p1, state);
    lat_dev.header.stamp = ros::Time::now();
    lat_dev.point.x = distance;
    // publish vehicle info 
    debug_pub.publish(lat_dev);
    loop_rate.sleep();
  }
}

void PathDebug::trajCallback(const hmcl_msgs::Lane& traj)
{
  // local traj callback
  p0 = traj.waypoints[0].pose.pose.position; 
  p1 = traj.waypoints[1].pose.pose.position;  
}

void PathDebug::poseCallback(const geometry_msgs::PoseStamped& pose)
{
  state = pose.pose.position; 
}

double PathDebug::linearInterpolationDistance2D(const geometry_msgs::Point& p0,
		const geometry_msgs::Point& p1,
		const geometry_msgs::Point& state)
{
  auto sign = 1;
	Eigen::Vector3d _p0;
	tf::pointMsgToEigen(p0, _p0);
	_p0[2] = 0.0;
	Eigen::Vector3d _p1;
	tf::pointMsgToEigen(p1, _p1);
	_p1[2] = 0.0;
	Eigen::Vector3d _state;
	tf::pointMsgToEigen(state, _state);
	_state[2] = 0.0;
	auto v = _p1 - _p0;
  if (v.cross(_state - _p1)[2] >= 0) { sign  = 1; }
  else { sign = -1; }
	
	return sign * (v.cross(_state - _p1)).norm()/v.norm();
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "Path_Debug");

  ros::NodeHandle nh_;
  PathDebug PathDebug_(nh_);

  ros::CallbackQueue callback_queue_debug;
  nh_.setCallbackQueue(&callback_queue_debug);

  std::thread spinner_thread_debug([&callback_queue_debug]() {
    ros::SingleThreadedSpinner spinner_can;
    spinner_can.spin(&callback_queue_debug);
  });

    ros::spin();


    spinner_thread_debug.join();

  return 0;

}
