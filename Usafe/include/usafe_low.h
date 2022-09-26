
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
#include <std_msgs/Bool.h>
#include <sensor_msgs/NavSatFix.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/Trafficlight.h>

#include <mobileye_msgs/MobileyeInfo.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/Waypoint.h>

#include <GeographicLib/LocalCartesian.hpp>

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

#include <hmcl_msgs/VehicleStatus.h>

// #include <tools/map_loader_utils.h>
#include <tools/BlockingQueue.h>
// controller include 
#include <controller/lon_ctrl.h>
#include <controller/lat_ctrl.h>
#include <controller/lowlevel_ctrl.h>

#define PI 3.14159265358979323846264338

class UsafeLow 
{
  
private:
ros::NodeHandle nh_, nh_p_;


controller::LongitudinalCtrl*         long_ctrl_;
controller::LateralCtrl*            lat_ctrl_;
controller::LowLevelCtrl*           lowlevel_ctrl;


public:
UsafeLow(const ros::NodeHandle& nh, const ros::NodeHandle& nh_p);
~UsafeLow();

void planner_loop();
void perception_loop();
void controller_loop();
void tools_loop();




};



