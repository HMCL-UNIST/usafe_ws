
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
#include <queue>
#include <mutex> 
#include <thread> 
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <eigen3/Eigen/Geometry>
#include <visualization_msgs/MarkerArray.h> 

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>


#include <dynamic_reconfigure/server.h>
#include <obj_simulation/testConfig.h>
#include <std_msgs/UInt8MultiArray.h>
#include <autoware_msgs/DetectedObjectArray.h>

#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/VehicleSCC.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

#define PI 3.14159265358979323846264338


class ObjSimulation 
{  
private:
ros::NodeHandle nh_;
std::mutex mtx_;
ros::Subscriber  emergency_stopSub, local_traj_sub, pose_sub, global_traj_sub;
ros::Publisher objPub, target_obj_Pub;
ros::Time time;

dynamic_reconfigure::Server<obj_simulation::testConfig> srv;
dynamic_reconfigure::Server<obj_simulation::testConfig>::CallbackType f;



bool emergency_stop_activate;
int emergency_count;
double alpha = 0.1;
double rel_vel, rel_dist, filtered_rel_dist, filtered_rel_dist_prev, curr_time, prev_time; 
// hmcl_msgs::Lane 
geometry_msgs::Point p0;
geometry_msgs::Point p1;
geometry_msgs::Point state;
visualization_msgs::Marker marker;
geometry_msgs::Point global_points;
hmcl_msgs::Waypoint wp;
// hmcl_msgs::objSim pub_sim_info;
public:
ObjSimulation(ros::NodeHandle& nh_);
~ObjSimulation();

void dyn_callback(obj_simulation::testConfig& config, uint32_t level);
void emergencyRemoteCallback(std_msgs::Float64ConstPtr msg);
void poseCallback(const geometry_msgs::PoseStamped& pose);
void trajCallback(const hmcl_msgs::Lane& traj);
void globaltrajCallback(const visualization_msgs::MarkerArray& global_traj);
};



