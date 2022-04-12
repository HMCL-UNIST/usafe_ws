
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
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <GeographicLib/LocalCartesian.hpp>
#include "BlockingQueue.h"
#include <eigen3/Eigen/Geometry>

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>

#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>


#define PI 3.14159265358979323846264338


class Localtoworld 
{
  
private:
ros::NodeHandle nh_;
ros::Subscriber worldGpsSub, localPoseSub;
ros::Publisher  worldPosePub, localGpsPub, localFixPub;

BlockingQueue<sensor_msgs::NavSatFixConstPtr> gpsPoseQ_;
BlockingQueue<sensor_msgs::NavSatFixConstPtr> gpsPoseQ_tmp;
BlockingQueue<geometry_msgs::PoseStampedConstPtr> localPoseQ_;
BlockingQueue<geometry_msgs::PoseStampedConstPtr> localPoseQ_tmp;

// boost::mutex optimizedStateMutex_;
sensor_msgs::NavSatFixConstPtr gpsPoseFix;
sensor_msgs::NavSatFixConstPtr prev_gpsPoseFix;

geometry_msgs::PoseStampedConstPtr gpsPose, localPose;
geometry_msgs::PoseStampedConstPtr prev_localPose;

bool fixedOrigin_;
GeographicLib::LocalCartesian enu_;   /// Object to put lat/lon coordinates into local cartesian
bool gotFirstFix_, gotFirstLocal_;
bool record_transform;
double maxGPS_dist_Error_;
double gnss_skip_distance;
int maxQSize_;
std::ofstream ofs;
 


std::string file_name;
int sample_count, num_of_gpsPose_for_icp;
bool tf_available;

double latOrigin, lonOrigin, altOrigin;
std::vector<std::vector<std::string>> tf_data;

Eigen::Matrix4f l_to_g, g_to_l;
Eigen::Matrix4f l_to_g_sensor, g_to_l_sensor;

// transform from local sensor frame to global sensor frame
tf::StampedTransform l_sensor_to_g_sensor;
tf::TransformListener local_transform_listener;

public:
Localtoworld();
~Localtoworld();
void GpsCallback(sensor_msgs::NavSatFixConstPtr fix);
void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);

void compute_transform();



};



