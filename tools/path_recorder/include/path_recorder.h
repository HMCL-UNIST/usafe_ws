
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
#include <ros/package.h>

#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
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
#include <path_recorder_utils.h>
#include <amathutils.hpp>


#define PI 3.14159265358979323846264338

class PathRecorder 
{
  
private:
ros::NodeHandle nh_, nh_p_;
ros::Publisher path_viz_pub;

ros::Subscriber pose_sub, gpsSub_, save_map_sub;
ros::Timer viz_timer;

geometry_msgs::Pose pre_gnss_pos, gnss_pos, pre_local_pos;
GeographicLib::LocalCartesian enu_;   /// Object to put lat/lon coordinates into local cartesian
bool gnss_init, pose_init;
bool path_record_with_gnss;

double line_resolution, point_resolution;

lanelet::LineString3d l3s_, l3s_pose_;
lanelet::LineStrings3d lines_, lines_pose_;

double origin_lat;
double origin_lon;
double origin_att;

std::string osm_file_name;


public:
PathRecorder(const ros::NodeHandle& nh, const ros::NodeHandle& nh_p);
~PathRecorder();

void GpsCallback(sensor_msgs::NavSatFixConstPtr fix);
void saveMapCallback(std_msgs::BoolConstPtr data); 
void viz_pub(const ros::TimerEvent& time);
void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);


};



