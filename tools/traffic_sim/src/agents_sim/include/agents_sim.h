
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

#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/NavSatFix.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/Trafficlight.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>

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
#include <lanelet2_core/geometry/Area.h>
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
#include <Agents.h>


// #include <ctime>


// #include <lanelet2_extension/utility/query.h>
// #include <lanelet2_extension/visualization/visualization.h>
// #include <lanelet2_extension/regulatory_elements/autoware_traffic_light.h>

#define PI 3.14159265358979323846264338


class AgentSim 
{
  
private:
ros::NodeHandle nh_, nh_p_;

ros::Publisher vehicle_agents_pub, ped_agents_pub, g_traj_viz_pub;
ros::Subscriber mission_sub;
std::vector<Agents> vehicle_agents;
std::vector<Agents> ped_agents;
int n_vehicle_agents, n_ped_agents;

double dt;

ros::Timer viz_timer;
visualization_msgs::MarkerArray traj_lanelet_marker_array;
lanelet::Lanelets road_lanelets;
lanelet::ConstLanelets road_lanelets_const;
lanelet::Areas all_areas;

lanelet::LaneletMapPtr map;
lanelet::routing::RoutingGraphUPtr routingGraph;

bool map_loaded, scen_available, dropper, dropped, dummy_clear, marker_clean;
double origin_lat, origin_lon, origin_att;
int mission_code;

std::string osm_file_name;
double map_road_resolution;

// time_t tstart, tend; 

public:
AgentSim(const ros::NodeHandle& nh, const ros::NodeHandle& nh_p);
~AgentSim();

void load_map();
void viz_pub(const ros::TimerEvent& time);
void MissionCallback(const std_msgs::String &msg);
void simulationCallback();
void localpathCallback();
void globalpathCallback();
void Scenario_generation();

void Bool_initialize();
void speedbump();
void dropping();
void dummy();

void fix_and_save_osm();
void lookup_trafficlight(lanelet::Areas Areas);
lanelet::Areas inlet_outlet(hmcl_msgs::LaneArray global_lane);
hmcl_msgs::LaneArray compute_random_path(geometry_msgs::Pose cur_pose, visualization_msgs::MarkerArray &traj_lanelet_marker_array);
hmcl_msgs::Lane compute_local_path(hmcl_msgs::LaneArray global_lane_array_for_local,geometry_msgs::Pose cur_pose);

};



