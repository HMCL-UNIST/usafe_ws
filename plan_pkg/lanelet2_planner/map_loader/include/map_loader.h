
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
#include <iostream>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <math.h>



#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <ros/package.h>

#include <std_msgs/Float64.h>
#include <sensor_msgs/NavSatFix.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/Trafficlight.h>


#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/Waypoint.h>


#include <GeographicLib/LocalCartesian.hpp>
#include "BlockingQueue.h"
#include <eigen3/Eigen/Geometry>
#include <mutex> 
#include <thread>
#include <boost/thread/thread.hpp>


#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <vector>
#include <lanelet2_core/LaneletMap.h>
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
#include <map_loader_utils.h>
#include <amathutils.hpp>
#include <route_planner.h>
#include <autoware_lanelet2_msgs/MapBin.h>
#include <hmcl_msgs/VehicleStatus.h>

#include <lanelet2_extension/utility/message_conversion.h>
#include <polyfit.h>
// #include <lanelet2_extension/utility/query.h>
// #include <lanelet2_extension/visualization/visualization.h>
// #include <lanelet2_extension/regulatory_elements/autoware_traffic_light.h>



#define PI 3.14159265358979323846264338

class MapLoader 
{
  
private:
ros::NodeHandle nh_, nh_p_, nh_local_path_;

ros::Publisher map_bin_pub, autoware_lane_pub, g_map_pub, g_traj_lanelet_viz_pub, g_traj_viz_pub, local_traj_pub, l_traj_viz_pub;

ros::Publisher way_pub;

ros::Subscriber pose_sub, goal_sub, vehicle_status_sub;

ros::Timer viz_timer, g_traj_timer, local_traj_timer;
visualization_msgs::MarkerArray map_marker_array,traj_marker_array,traj_lanelet_marker_array, local_traj_marker_arrary;

double test_direction;
bool visualize_path, continuious_global_replan;


std::mutex mu_mtx;
RoutePlanner rp_;
lanelet::LaneletMapPtr map;
lanelet::routing::RoutingGraphUPtr routingGraph;
bool map_loaded;
float local_path_length;
double origin_lat;
double origin_lon;
double origin_att;
bool global_traj_available;
bool goal_available;
hmcl_msgs::LaneArray global_lane_array, global_lane_array_for_local;



std::string osm_file_name;
double map_road_resolution;

// transform from local sensor frame to global sensor frame
tf::StampedTransform l_sensor_to_g_sensor;
tf::TransformListener local_transform_listener;
float weight_decay_rate;
double pose_x,pose_y,pose_z;
bool pose_init;
geometry_msgs::Pose cur_pose, prev_pose;
geometry_msgs::Pose cur_goal;

lanelet::Lanelets road_lanelets;
lanelet::ConstLanelets road_lanelets_const;


double poly_error;
bool polyfit_error;

double current_speed;
double local_path_scale;
double min_local_path_length, max_local_path_length;

public:
MapLoader(const ros::NodeHandle& nh, const ros::NodeHandle& nh_p, const ros::NodeHandle& nh_local_path);
~MapLoader();

void load_map();
void construct_lanelets_with_viz();
void viz_pub(const ros::TimerEvent& time);
void global_traj_handler(const ros::TimerEvent& time);
void local_traj_handler(const ros::TimerEvent& time);
void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);
void callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg);
void callbackVehicleStatus(const hmcl_msgs::VehicleStatusConstPtr &msg);

double get_yaw(const lanelet::ConstPoint3d & _from, const lanelet::ConstPoint3d &_to );
unsigned int getClosestWaypoint(bool is_start, const lanelet::ConstLineString3d &lstring, geometry_msgs::Pose& point_);
void findnearest_lane_and_point_idx(const hmcl_msgs::LaneArray &lanes, geometry_msgs::Pose& point_, int &closest_lane_idx, int &closest_point_idx);
void fix_and_save_osm();

PolyFit<double> polyfit(std::vector<double> x, std::vector<double> y);
void curve_fitting(std::vector<std::vector<double>>& g_points, hmcl_msgs::Lane& local_traj_msg);

void compute_global_path();
void compute_local_path();

void lanelet_ros_convert_loop();

void viz_local_path(hmcl_msgs::Lane &lane_);

void pub_autoware_traj(const hmcl_msgs::Lane& lane);
// void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);


};



