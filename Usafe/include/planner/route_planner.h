
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
#include <iostream>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/NavSatFix.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <GeographicLib/LocalCartesian.hpp>
#include <eigen3/Eigen/Geometry>

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <vector>

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
#include <tools/amathutils.hpp>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/Trafficlight.h>


#define PI 3.14159265358979323846264338

namespace planner{

class RoutePlanner 
{
  
private:
    int tmp;
    RoutePlanner rp_;
    lanelet::LaneletMapPtr map;
    lanelet::routing::RoutingGraphUPtr routingGraph;
    lanelet::ConstLineString3d target_ctl;
    lanelet::ConstLanelet target_lane;
    std::vector<lanelet::ConstLanelet> target_lanes;
    std::vector<lanelet::ConstLanelet> lanes;
    std::vector<lanelet::ConstLanelet> lir;
    std::vector<hmcl_msgs::Lane> traj_ll;

public:
RoutePlanner(); 
~RoutePlanner();

struct Waypoint
{
    int wp_id;
    geometry_msgs::PoseStamped pose;
    double speed_limit;
    bool junction_in, crosswalk_in, stopline_in;
};

typedef struct
{
    int lane_id;
    bool lane_change_flag;
    int corner;
    std::vector<Waypoint> waypoints;
}Lane;

struct surface_mark
{
    int mark_id;
    int mark_type;
    double mark_dist;
    std::vector<geometry_msgs::Pose> points;
};

void load_map(); // load lanelet2 osm file
void construct_lanelets_with_viz(); // visualize osm file
void global_traj_handler();
void local_traj_handler();
void lir_handler(); 

void compute_global_path(); // compute global path
void compute_local_path(); // compute local path
void current_lanefollow();
void lane_in_range(); // split and merge lanes
void wp_inArea(); // check waypoints in junction, stop line, crosswalk
void dist_toMark(); // distance to stop line, crosswalk
bool calculate_distance(geometry_msgs::Pose &point, hmcl_msgs::Waypoint &wp, double &dist);

void LaneChangeStateMachine();

void lanelet_ros_convert_loop();
void SimulatedObj();

void viz_local_path(hmcl_msgs::Lane &lane_);
void viz_lir(hmcl_msgs::LaneArray &lanes);

void pub_autoware_traj(const hmcl_msgs::Lane& lane);


};

}


