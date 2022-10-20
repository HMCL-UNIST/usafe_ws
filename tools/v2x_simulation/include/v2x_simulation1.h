
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
#include <unistd.h>
#include <sys/types.h>
#include <cmath>
#include <cstdlib>

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>

#include <sstream>
#include <string>
#include <list>
#include <queue>
#include <mutex> 
#include <thread> 
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>

#include <eigen3/Eigen/Geometry>

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include <dynamic_reconfigure/server.h>
#include <v2x_simulation/test1Config.h>
#include <std_msgs/UInt8MultiArray.h>
#include <v2x_msgs/Mission1.h>
#include <v2x_msgs/Mission1data.h>
#include <lanelet2_projection/UTM.h>
#include <geometry_msgs/PoseStamped.h>

#define PI 3.14159265358979323846264338
#define PRINT_MAT(X) std::cout << #X << ":\n" << X << std::endl << std::endl



class V2xSimulation1 
{  
private:
ros::NodeHandle nh_, nh_p_;
std::mutex mtx_;

ros::Publisher v2xPub, v2xVizPub;
ros::Subscriber point_sub;
double origin_lat, origin_lon;
lanelet::projection::UtmProjector* projector;    
dynamic_reconfigure::Server<v2x_simulation::test1Config> srv;
dynamic_reconfigure::Server<v2x_simulation::test1Config>::CallbackType f;
 
std::vector<v2x_msgs::Mission1data> mission_waypoints;
visualization_msgs::MarkerArray mission_wp_viz;

int Mission_status;
int waypoint_select;
int waypoint_edit;
double boost_duration;


public:
V2xSimulation1(const ros::NodeHandle& nh, const ros::NodeHandle& nh_p);
~V2xSimulation1();

void callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg);
void dyn_callback(v2x_simulation::test1Config& config, uint32_t level);
void simulationCallback();
void constructViz();
void add_mission_waypoints();
void insertWaypoint(const geometry_msgs::PoseStamped &msg);
void deleteWaypoint(const geometry_msgs::PoseStamped &msg);

};



