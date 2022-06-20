
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
#include <random>

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "obj_simulation.h"

using namespace std;

ObjSimulation::ObjSimulation(ros::NodeHandle& nh_):  
  nh_(nh_)
{
  
  
  // objPub = nh_.advertise<autoware_msgs::DetectedObjectArray>("/detected_objs", 5);    

  emergency_stopSub = nh_.subscribe("/emer", 2, &ObjSimulation::emergencyRemoteCallback, this);
  local_traj_sub = nh_.subscribe("/local_traj", 1, &ObjSimulation::trajCallback, this);
  global_traj_sub = nh_.subscribe("/global_traj_lanelets_viz", 1, &ObjSimulation::globaltrajCallback, this);
  pose_sub = nh_.subscribe("/geo_pose_estimate", 1, &ObjSimulation::poseCallback, this);

  // targetobjPub = nh_.advertise<hmcl_msgs::objSim>("/obj_sim_info", 1);

  ROS_INFO("obj simulation");
  // boost::thread AcanHandler(&ObjSimulation::AcanSender,this); 
  // boost::thread AcanWatch(&ObjSimulation::AcanWatchdog,this); 
 
  
  f = boost::bind(&ObjSimulation::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

ObjSimulation::~ObjSimulation()
{}

void ObjSimulation::emergencyRemoteCallback(std_msgs::Float64ConstPtr msg){
    int thres = 5;
    if(msg->data > 0.5){
      emergency_count++;
    }else{
      emergency_count--;
    }
    
    if(emergency_count > thres){
      emergency_stop_activate = true;           
    }else{
      emergency_stop_activate = false;            
    }
    
    if( emergency_count > thres*10 ){
      emergency_count = thres+1;
    }
    if(emergency_count < 0 ){
      emergency_count = 0;
    }
}

void ObjSimulation::dyn_callback(obj_simulation::testConfig &config, uint32_t level)
{
  // ROS_INFO("Manual Obj Info Received");
  
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution (0.0,0.5);

  rel_dist = config.Relative_Distance + distribution(generator);
  // cout << "rel dist : " << rel_dist << endl;
}

void ObjSimulation::trajCallback(const hmcl_msgs::Lane& traj)
{
  // local traj callback
  int local_traj_size = traj.waypoints.size(); 
  p0 = traj.waypoints[0].pose.pose.position; 
  p1 = traj.waypoints[1].pose.pose.position; 
  // cout << "local traj size : " << local_traj_size << endl; 
  curr_time = ros::Time::now().toSec();
  double Ts = curr_time - prev_time; 
  double filtered_rel_dist = alpha * rel_dist + (1-alpha) * filtered_rel_dist_prev;
  rel_vel = (filtered_rel_dist - filtered_rel_dist_prev) / Ts;

  filtered_rel_dist_prev = filtered_rel_dist;
  prev_time = curr_time;
  cout << "relative distance : " << filtered_rel_dist << "m" << endl;
  cout << "relative velocity : " << rel_vel*3.6 << "km/h" << endl; 
  // cout << "sampling time : " << Ts << endl;
  // pub_sim_info.relative_distance = filtered_rel_dist; 
  // pub_sim_info.relative_velocity = rel_vel*3.6;
}

void ObjSimulation::globaltrajCallback(const visualization_msgs::MarkerArray& global_traj)
{
  // global local traj callback
  // global_points = global_traj.markers.points;
  // cout << "global traj size : " << global_traj.markers[1].points.size() << endl; 
}

void ObjSimulation::poseCallback(const geometry_msgs::PoseStamped& pose)
{
  state = pose.pose.position; 
}


// void ObjSimulation::objGen(const geometry_msgs::Point& p0,
// 		const geometry_msgs::Point& p1,
// 		const geometry_msgs::Point& state)
// {
//   state = pose.pose.position; 
// }

int main (int argc, char** argv)
{
  ros::init(argc, argv, "ObjSimulation");
  ros::NodeHandle nh_;
  ObjSimulation ObjSimulation_(nh_);


  ros::spin();

  return 0;
}