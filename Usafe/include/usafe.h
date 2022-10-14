
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
#pragma once
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

#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>


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
#include <v2x_msgs/Mission2.h>
#include <v2x_msgs/Mission2data.h>

#include <mobileye_msgs/MobileyeInfo.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>

// #include <GeographicLib/LocalCartesian.hpp>

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
#include <lanelet2_traffic_rules/TrafficRulesFactory.h>
#include <lanelet2_core/primitives/BasicRegulatoryElements.h>

// #include <lanelet2_core/LaneletMap.h>
// #include <lanelet2_core/primitives/Lanelet.h>
// #include <lanelet2_io/Io.h>
// #include <lanelet2_io/io_handlers/Factory.h>
// #include <lanelet2_io/io_handlers/Writer.h>
// #include <lanelet2_projection/UTM.h>
// #include <lanelet2_routing/Route.h>
// #include <lanelet2_routing/RoutingCost.h>
// #include <lanelet2_routing/RoutingGraph.h>
// #include <lanelet2_routing/RoutingGraphContainer.h>
// #include <lanelet2_traffic_rules/TrafficRulesFactory.h>

#include <hmcl_msgs/VehicleStatus.h>

#include <v2x_msgs/Mission2.h>

// planner include
// #include <planner/velocity_planner.h>
// #include <planner/route_planner.h>
#include <planner/racing_planner.h>
#include <planner/vehicle_model.h>
// tools include 
// #include <tools/debugger.h>
// #include <tools/healthmonitoring.h>
// #include <tools/amathutils.hpp>
// #include <tools/map_loader_utils.h>
// #include <tools/BlockingQueue.h>
// controller include 
// #include <controller/lon_ctrl.h>
// #include <controller/lat_ctrl.h>
// perception include
// #include <perception/v2x.h>
// #include <perception/surrounding_environment.h>
// #include <perception/vehicle_state.h>
#include <dynamic_reconfigure/server.h>
#include <usafe/testConfig.h>
#define PI 3.14159265358979323846264338

enum struct MissionState {InitialSetup = 0, WaitforCue = 1, Driving = 2}; 

inline const char* stateToString(MissionState v)
{
    switch (v)
    {
        case MissionState::InitialSetup:   return "InitialSetup";
        case MissionState::WaitforCue:   return "WaitforCue";
        case MissionState::Driving:   return "Driving";        
        default:      return "[Unknown MissionState]";
    }
}


class Usafe 
{
  
private:
ros::NodeHandle nh_, nh_local_, nh_p_;
std::mutex mtx;
ros::Subscriber v2xSub;
ros::Publisher velPub, missionStatePub;
MissionState mission_state;
bool v2x_received;
std::vector<double> boost_enable_idx;
planner::RacingLinePlanner*           race_planner_;
planner::VehicleModel*                 vehicle_model_;
v2x_msgs::Mission2  v2x_msg, prev_v2x_msg;


// hmcl_v2x::HMCL_Mission2 v2x_msg;

dynamic_reconfigure::Server<usafe::testConfig> srv;
dynamic_reconfigure::Server<usafe::testConfig>::CallbackType f;

bool Sum_compute_shortest_path_, Above_compute_shortest_path_,Below_compute_shortest_path_;
bool positive_cost_assign_;
public:
Usafe(const ros::NodeHandle& nh, const ros::NodeHandle& nh_local, const ros::NodeHandle& nh_p);
~Usafe();

// void planner_loop();
// void perception_loop();
// void controller_loop();
// void tools_loop();
void missionFSM();
void dyn_callback(usafe::testConfig& config, uint32_t level);
bool areV2xMsgtheSame(const v2x_msgs::Mission2 &msg1, const v2x_msgs::Mission2 &msg2);
void callbackV2X(const v2x_msgs::Mission2ConstPtr &msg);


};


