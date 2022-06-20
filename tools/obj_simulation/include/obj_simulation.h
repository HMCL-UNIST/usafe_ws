
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

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <visualization_msgs/Marker.h>

#include <dynamic_reconfigure/server.h>
#include <obj_simulation/testConfig.h>
#include <std_msgs/UInt8MultiArray.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <hmcl_msgs/Lane.h> 
#include <amathutils.hpp>

#define PI 3.14159265358979323846264338
#define PRINT_MAT(X) std::cout << #X << ":\n" << X << std::endl << std::endl

class ObjSimulation 
{  
private:
ros::NodeHandle nh_;
std::mutex mtx_;
ros::Subscriber  traj_sub;
ros::Publisher objPub;
ros::Publisher target_vis_pub;

double dt;
hmcl_msgs::Lane ego_lane;
double target_vehicle_speed;
double distance_to_target;
bool target_visible;
double sim_dt;
bool sim_pose_reset;
dynamic_reconfigure::Server<obj_simulation::testConfig> srv;
dynamic_reconfigure::Server<obj_simulation::testConfig>::CallbackType f;

Eigen::MatrixXd A, B;
Eigen::VectorXd target_state; 


std::vector<double> target_pose;

bool emergency_stop_activate;
int emergency_count;

public:
ObjSimulation(ros::NodeHandle& nh_);
~ObjSimulation();

void dyn_callback(obj_simulation::testConfig& config, uint32_t level);
void emergencyRemoteCallback(std_msgs::Float64ConstPtr msg);
void localTrajCallback(const hmcl_msgs::LaneConstPtr msg);
void set_target_state(Eigen::VectorXd new_state);
void simulationCallback();

};



