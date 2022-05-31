
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
#include <algorithm>

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
  cross_track_err_sub = nh_.subscribe("/path_debug_info", 1, &PurePursuit::cteCallback, this);
  vel_cmd_sub = nh_.subscribe("/wheel_info", 1, &PurePursuit::velcmdCallback, this);
  // debug_pub = nh_.advertise<std_msgs::Float64>("/path_debug_info", 10);
  // statusPub = nh_light_.advertise<hmcl_msgs::VehicleStatus>("/vehicle_status", 5);    

  ROS_INFO("Init Traj Debugger");
  boost::thread PurePursuitNode(&PurePursuit::ctrlPub,this); 
}

PurePursuit::~PurePursuit()
{}

void PurePursuit::ctrlPub()
{
  ros::Rate loop_rate(50);    
  while (ros::ok())
  {      
    selectDesiredPoint();
    // publish vehicle info 
    // debug_pub.publish(lat_dev);
    loop_rate.sleep();
  }
}

void PurePursuit::trajCallback(const hmcl_msgs::Lane& traj)
{
  // local traj callback
  closest_waypoint = traj.waypoints[0].pose.pose.position; // p_w
  ref_path = traj; 
  quat_msg = traj.waypoints[0].pose.pose.orientation;
  tf::quaternionMsgToTF(quat_msg, quat);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
  closest_waypoint.z = yaw; 
}

void PurePursuit::poseCallback(const geometry_msgs::PoseStamped& pose)
{
  state = pose.pose.position; 
}

void PurePursuit::cteCallback(const std_msgs::Float64& cte)
{
  cross_track_err = cte.data; 
}

void PurePursuit::velcmdCallback(const hmcl_msgs::VehicleWheelSpeed& msg)
{
  vel_cmd = msg.wheel_speed; // km/h
  r_min_v = pow(vel_cmd, 2) / (127 * (e_MAX + f_MAX));
  if (r_min_v < 5.6) { r_min_v = 5.6; } 
}

void PurePursuit::selectDesiredPoint()
{
  geometry_msgs::Quaternion quat_msg_;
  tf::Quaternion quat_;

  double q0[3] = { 0,0,0 };
  double q1[200][3] = { 0,0.0 };
  vector<double> dub_len(200, 10000);
  q0[0] = closest_waypoint.x;
  q0[1] = closest_waypoint.y;
  q0[2] = closest_waypoint.z; // heading (rad)
  for (unsigned int i = 0; i < ref_path.waypoints.size(); i++) {
    double dx = closest_waypoint.x - ref_path.waypoints[i].pose.pose.position.x;
    double dy = closest_waypoint.y - ref_path.waypoints[i].pose.pose.position.y;

    quat_msg_ = ref_path.waypoints[i].pose.pose.orientation;
    tf::quaternionMsgToTF(quat_msg_, quat_);
    double roll, pitch, yaw;
    tf::Matrix3x3(quat_).getRPY(roll, pitch, yaw);

    q1[i][0] = ref_path.waypoints[i].pose.pose.position.x;
    q1[i][1] = ref_path.waypoints[i].pose.pose.position.y;
    q1[i][2] = yaw;

    if (r_min_v <= sqrt(pow(dx, 2) + pow(dy, 2))) {
      // dubins path len calc
      dubins_shortest_path(&dubins_path, q0, q1, turning_radius);
      dub_len[i] = dubins_path_length(&dubins_path);
    }
  }
  int minElementIndex = min_element(dub_len.begin(),dub_len.end()) - dub_len.begin();
  int minElement = *min_element(dub_len.begin(), dub_len.end());

  // cout << "minElementIndex:" << minElementIndex << ", minElement:" << minElement << endl;
  // d_w
  desired_waypoint.x = q1[minElementIndex][0];
  desired_waypoint.y = q1[minElementIndex][1];
  desired_waypoint.z = q1[minElementIndex][2]; 
}

void PurePursuit::selectOutOfPath() {
  // p_w = closest waypoint
  double dx = closest_waypoint.x - state.x;
  double dy = closest_waypoint.y - state.y;
  double dist = sqrt(pow(dx, 2) + pow(dy, 2));
  if (dist < alpha_MAX) {
    alpha = dist / alphaMax;
  }    
  else {
    alpha = 1;
  }
          
  cur_pw = curv(idx);
  cur_pd = curv(idx_lD);

  if cur_pw >= cur_pd
      beta = 0;
  elseif (cur_pd - cur_pw) < beta_MAX
      beta = (cur_pd - cur_pw)/beta_MAX;
  elseif (cur_pd - cur_pw) >= beta_MAX
      beta = 1;
  end

  tau = (1 - alpha)*beta;

  p_wd = norm(p_w - p_d); % (6)
  thetaWd = atan2((p_d(2)-p_w(2)),(p_d(1)-p_w(1))); %(6)
  theta = thetaWd - p_v(3); % (7)
  thetaDl = thetaWd - sign(theta)*pi/2; %(6)
  pDl = p_wd * tan(abs(theta));
  pl(1,1) = p_d(1,1) + tau * pDl * cos(thetaDl);
  pl(1,2) = p_d(1,2) + tau * pDl * sin(thetaDl);
  L_f = norm(pl - p_v(1:2));
}

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
