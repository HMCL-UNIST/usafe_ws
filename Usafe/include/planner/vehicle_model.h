
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
// #pragma once
#pragma once
#include <cmath>
#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include <mutex>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>
#include <eigen3/Eigen/Geometry>
#include <vector>
#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_core/LaneletMap.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_io/io_handlers/Factory.h>
#include <lanelet2_io/io_handlers/Writer.h>
#include <lanelet2_projection/UTM.h>
#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include "tools/utils.h"
#include "tools/amathutils.hpp"
#define PI 3.14159265358979323846264338

namespace planner{

class VehicleModel 
{
 
public:
ros::NodeHandle nh_local_, nh_p_;
ros::Subscriber curodom_sub;
Eigen::VectorXd current_state= Eigen::VectorXd::Zero(4);
geometry_msgs::PoseStamped current_pose;
nav_msgs::Odometry cur_odom;
visualization_msgs::MarkerArray xy_history_marker;
double l_r = 1.5;
double l_f = 1.5;
double dt = 0.1;
double lookahead = 20;
double goal_x, goal_y;
bool my_odom_ok_;
std::vector<lanelet::Point3d> target_points;
// hmcl_msgs::LaneArray globalLaneArray;
// hmcl_msgs::Lane localLaneArray;



VehicleModel(const ros::NodeHandle& nh_local, const ros::NodeHandle& nh_p);
~VehicleModel();


Eigen::VectorXd pose2state(nav_msgs::Odometry &odom);
nav_msgs::Odometry state2odom(Eigen::VectorXd &state);
void set_state(Eigen::VectorXd state_);
void set_goal(double x, double y);
void compute_target(Eigen::VectorXd state_);
double compute_steering(Eigen::VectorXd state);
std::vector<Eigen::VectorXd> getVehiclePredictedPath(int num_iter);
void odomCallback(const nav_msgs::OdometryConstPtr& msg);
visualization_msgs::Marker getPredictedPathMarker(std::vector<Eigen::VectorXd> &state_history);
};

}


