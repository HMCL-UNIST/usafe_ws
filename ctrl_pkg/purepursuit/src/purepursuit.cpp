
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
  curvature_sub = nh_.subscribe("/curvature", 1, &PurePursuit::curvCallback, this);
  steer_pub = nh_.advertise<hmcl_msgs::VehicleSteering>("/usafe_steer_cmd", 1);

  ROS_INFO("Init Pure Pursuit");
  boost::thread PurePursuitNode(&PurePursuit::ctrlPub,this); 
}

PurePursuit::~PurePursuit()
{}

void PurePursuit::ctrlPub()
{
  ros::Rate loop_rate(50);    
  while (ros::ok())
  {      
    steer_cmd.header.stamp = ros::Time::now();
    steer_cmd.steering_angle = steerCmd;
    // publish vehicle info 
    steer_pub.publish(steer_cmd);

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

  geometry_msgs::Quaternion quat_msg_;
  tf::Quaternion quat_;
  quat_msg_ = pose.pose.orientation;
  tf::quaternionMsgToTF(quat_msg, quat_);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat_).getRPY(roll, pitch, yaw);
  state.z = yaw;
}

void PurePursuit::curvCallback(const std_msgs::Float64MultiArray& msg)
{
  curvature = msg.data; 
  // cout << curvature[0] << " " << curvature[10] << endl; 
  selectDesiredPoint();
  selectOutOfPath();
}

void PurePursuit::cteCallback(const geometry_msgs::PointStamped& cte)
{
  cross_track_err = cte.point.x; 
  cout << "cross_track_err : " << cross_track_err << endl;
}

void PurePursuit::velcmdCallback(const hmcl_msgs::VehicleWheelSpeed& msg)
{
  vel_cmd = msg.wheel_speed; // km/h
  r_min_v = pow(vel_cmd/3.6, 2) / (9.79 * (e_MAX + f_MAX));
  if (r_min_v < 5.6) { r_min_v = 5.6; } 
}

void PurePursuit::selectDesiredPoint()
{
  geometry_msgs::Quaternion quat_msg_;
  tf::Quaternion quat_;

  double q0[3] = { 0,0,0 };
  double q1[200][3] = { 0, 0 ,0 };
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
      dubins_shortest_path(&dubins_path, q0, q1[i], turning_radius);
      dub_len[i] = dubins_path_length(&dubins_path);
    }
  }
  minElementIndex = min_element(dub_len.begin(),dub_len.end()) - dub_len.begin();
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
  double alpha = 0;
  double beta = 0;
  int sign = 1;
  double cur_pw = 0;
  double cur_pd = 0;

  if (dist < alpha_MAX) {
    alpha = dist / alpha_MAX;
  }    
  else {
    alpha = 1;
  }
  cur_pw = curvature[0]; 
  cur_pd = curvature[minElementIndex];
  if (cur_pw >= cur_pd) {
    beta = 0;
  }
  else if ((cur_pd - cur_pw) < beta_MAX) {
    beta = (cur_pd - cur_pw)/beta_MAX;
  }
  else if ((cur_pd - cur_pw) >= beta_MAX) {
    beta = 1;
  } 
  double tau = (1 - alpha)*beta;

  double p_wd = sqrt(pow((closest_waypoint.x - desired_waypoint.x),2) + pow((closest_waypoint.y - desired_waypoint.y),2));
  double thetaWd = atan2((desired_waypoint.y - closest_waypoint.y),(desired_waypoint.x - closest_waypoint.x));
  // double thetaWd = atan2((state.y - closest_waypoint.y),(state.x - closest_waypoint.x));
  double theta = state.z - thetaWd;
  

  if (theta >= 0) { sign = 1; }
  else { sign = -1; }
  double thetaDl = thetaWd - sign * PI/2;
  double pDl = p_wd * tan(abs(theta));
  fixed_waypoint.x = desired_waypoint.x + tau * pDl * cos(thetaDl);
  fixed_waypoint.y = desired_waypoint.y + tau * pDl * sin(thetaDl);
  

  Lf = sqrt(pow((fixed_waypoint.x - state.x),2) + pow((fixed_waypoint.y - state.y),2)); 
  // calc steering angle
  steerCmd = (atan2(2*L*sin(theta), Lf) * 180/PI * gear_ratio * 10 + steering_offset) + (-cross_track_err * 200);
  // (-cross_track_err * 100)
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "Pure pursuit");

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
