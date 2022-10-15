
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
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/NavSatFix.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/Trafficlight.h>

#include <mobileye_msgs/MobileyeInfo.h>

#include <nav_msgs/Odometry.h>
#include <sensor_msgs/NavSatFix.h>
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
// #include <lanelet2_core/LaneletMap.h>
#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_core/geometry/LaneletMap.h>
#include <lanelet2_core/geometry/impl/Area.h>
#include "lanelet2_core/geometry/Area.h"
#include "lanelet2_core/geometry/BoundingBox.h"
#include "lanelet2_core/geometry/LaneletMap.h"
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
#include <kalman_filter.h>
#include <autoware_lanelet2_msgs/MapBin.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/MissionWaypoint.h>
#include <v2x_msgs/Mission1.h>
#include <v2x_msgs/Mission1state.h>

// #include <lanelet2_extension/utility/message_conversion.h>
#include <polyfit.h>

// #include <lanelet2_extension/utility/query.h>
// #include <lanelet2_extension/visualization/visualization.h>
// #include <lanelet2_extension/regulatory_elements/autoware_traffic_light.h>

enum struct LaneChangeState {LeftChange = 0, Follow = 1, RightChange = 2, LeftPending = 3,RightPending = 4}; 







inline const char* stateToString(LaneChangeState v)
{
    switch (v)
    {
        case LaneChangeState::LeftChange:   return "LeftChange";
        case LaneChangeState::Follow:   return "Follow";
        case LaneChangeState::RightChange: return "RightChange";
        case LaneChangeState::LeftPending: return "LeftPending";
        case LaneChangeState::RightPending: return "RightPending";
        default:      return "[Unknown LaneChangeState]";
    }
}
// typedef enum{LeftChange, Follow, RightChange} LaneChangeState;

#define PI 3.14159265358979323846264338

Eigen::MatrixXd A_curv(3, 3); // System dynamics matrix
Eigen::MatrixXd B_curv(3, 3); // Input control matrix
Eigen::MatrixXd C_curv(3, 3); // Output matrix
Eigen::MatrixXd Q_curv(3, 3); // Process noise covariance
Eigen::MatrixXd R_curv(3, 3); // Measurement noise covariance
Eigen::MatrixXd P_curv(3, 3); // Estimate error covariance

// A_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// C_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// Q_curv << 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01;
// R_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// P_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;



class MapLoader 
{
  
private:
ros::NodeHandle nh_, nh_p_, nh_local_path_;

ros::Publisher debug_pub, map_bin_pub, autoware_lane_pub, g_map_pub, g_traj_lanelet_viz_pub, g_traj_viz_pub, local_traj_pub, l_traj_viz_pub, lir_viz_pub, ped_cw_pub;
ros::Publisher lir_pub;
ros::Publisher way_pub;
ros::Publisher mission_pub, mission_pt_pub, mission_pts_pub, ped_pts_pub;
ros::Subscriber mobileye_sub, ped_sub;
ros::Subscriber pose_sub, goal_sub, vehicle_status_sub, odom_sub, v2x_mission_sub;
ros::Subscriber lanechange_left_sub,lanechange_right_sub;
mobileye_msgs::MobileyeInfo mobileye_data;
ros::Timer viz_timer, g_traj_timer, local_traj_timer, lir_timer, ped_cw_timer;
visualization_msgs::MarkerArray map_marker_array,traj_marker_array,traj_lanelet_marker_array, local_traj_marker_arrary, lir_marker_array;
visualization_msgs::Marker mission_pt_mark;

double test_direction;
bool visualize_path, continuious_global_replan;
bool getV2Xinfo;
hmcl_msgs::MissionWaypoint mission_pt;
v2x_msgs::Mission1state MissionStates;
v2x_msgs::Mission1 Mission_msg;
visualization_msgs::MarkerArray mission1_marker_array, ped_marker_array;

autoware_msgs::DetectedObjectArray objects, prev_objects, ped_array; 

std::vector<int> id_array;
std::mutex mu_mtx;
RoutePlanner rp_;
lanelet::LaneletMapPtr map;
lanelet::routing::RoutingGraphUPtr routingGraph;
lanelet::ConstLineString3d target_ctl;
lanelet::ConstLanelet target_lane;
std::vector<lanelet::ConstLanelet> target_lanes;
std::vector<lanelet::ConstLanelet> lanes;
std::vector<lanelet::ConstLanelet> lir;
std::vector<hmcl_msgs::Lane> traj_ll;
std::vector<std::pair<double,double>> xyz;
std_msgs::Bool ped_cw;
bool map_loaded;
float local_path_length;
double origin_lat;
double origin_lon;
double origin_att;
double max_dist, max_dist_vel;
bool global_traj_available;
bool goal_available;
bool lir_available = false;
bool ped_available = false, ped_in=false, ped_tmp=false;
hmcl_msgs::LaneArray global_lane_array, global_lane_array_for_local, lir_array, route_array;

geometry_msgs::Pose pose_a, pose_b;

int mission_status;
int start_idx, end_idx;
int cl_lane_idx = 0; 
int cl_pt_idx = 0;
std::vector<int> global_index ={};
int current_id = 0;
int previous_id = -1;
bool lir_flag = false;
int ped_count;

std::string osm_file_name;
double map_road_resolution;

// transform from local sensor frame to global sensor frame
tf::StampedTransform l_sensor_to_g_sensor;
tf::TransformListener local_transform_listener;
float weight_decay_rate;
double pose_x,pose_y,pose_z;
float odom_x,odom_y,odom_z;
bool pose_init;
std::vector<geometry_msgs::Pose> v2x_nodes;
geometry_msgs::Pose cur_pose, prev_pose;
geometry_msgs::Pose cur_goal;

lanelet::Lanelets road_lanelets;
lanelet::ConstLanelets road_lanelets_const;
lanelet::Areas areas;
lanelet::Areas junction;
lanelet::Areas crosswalk;
lanelet::Areas stopline;

lanelet::Optional<lanelet::routing::Route> route;

bool find_check = false;
bool left_change_signal, right_change_signal;
LaneChangeState lane_change_state, prev_lane_change_state;
double lane_change_weight;
double dist_to_target;
double lane_change_in_sec, lanechange_fsm_period;

geometry_msgs::PoseStamped debug_msg;

double poly_error;
bool polyfit_error;

double current_speed;
double local_path_scale;
double min_local_path_length, max_local_path_length;


///////////////////////////////// Filter definition start  /////////////////////////////////



KalmanFilter cur_filter;
bool init_cuv_fit;
///////////////////////////////// END /////////////////////////////////




public:

struct Waypoint
{
    int wp_id;
    geometry_msgs::PoseStamped pose;
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

MapLoader(const ros::NodeHandle& nh, const ros::NodeHandle& nh_p, const ros::NodeHandle& nh_local_path);
~MapLoader();

void load_map();
void construct_lanelets_with_viz();
void viz_pub(const ros::TimerEvent& time);
void global_traj_handler(const ros::TimerEvent& time);
void local_traj_handler(const ros::TimerEvent& time);
void lir_handler(const ros::TimerEvent& time);
void ped_inCw_handler(const ros::TimerEvent& time);
void poseCallback(const nav_msgs::OdometryConstPtr& msg);
void llaCallback(const nav_msgs::OdometryConstPtr& msg);
void PedCallback(const autoware_msgs::DetectedObjectArray& msg);
void callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg);
void callbackVehicleStatus(const hmcl_msgs::VehicleStatusConstPtr &msg);

void mobileye_based_traj(hmcl_msgs::Lane& local_traj_msg);

void mobileyeCallback(const mobileye_msgs::MobileyeInfoConstPtr &msg);
void mobileye_follow();
void leftLancechangeCallback(const std_msgs::BoolConstPtr &msg);
void rightLancechangeCallback(const std_msgs::BoolConstPtr &msg);
void objsCallback(const autoware_msgs::DetectedObjectArrayConstPtr& msg);

double get_yaw(const lanelet::ConstPoint3d & _from, const lanelet::ConstPoint3d &_to );
unsigned int getClosestWaypoint(bool is_start, const lanelet::ConstLineString3d &lstring, geometry_msgs::Pose& point_);
void findnearest_lane_and_point_idx(const hmcl_msgs::LaneArray &lanes, geometry_msgs::Pose& point_, int &closest_lane_idx, int &closest_point_idx);
void fix_and_save_osm();
void mission_state(const std::vector<std::pair<double,double>>  mission_positions);
void mission1Callback(const v2x_msgs::Mission1& msg, const std::vector<std::pair<double,double>>  mission_positions);
void ped_state(const autoware_msgs::DetectedObjectArray& pobjects);

PolyFit<double> polyfit(std::vector<double> x, std::vector<double> y);
void curve_fitting(std::vector<double> speed_lim,std::vector<std::vector<double>>& g_points, hmcl_msgs::Lane& local_traj_msg);


void init_kalman_filters();

void compute_global_path();
void compute_local_path();
void current_lanefollow();
void lane_in_range();
int check_traffic_light(const int& id);
void wp_inArea();
void ped_inCw();
void ego_in();
bool calculate_distance(geometry_msgs::Pose &point, hmcl_msgs::Waypoint &wp, double &dist);
bool calculate_distance_(hmcl_msgs::Waypoint &wp1, hmcl_msgs::Waypoint &wp2, double &dist, double &dist_cum);
void v2x_goal_nodes();

void LaneChangeStateMachine();

void lanelet_ros_convert_loop();
void SimulatedObj();

void viz_local_path(hmcl_msgs::Lane &lane_);
void viz_lir(hmcl_msgs::LaneArray &lanes);

void pub_autoware_traj(const hmcl_msgs::Lane& lane);
// void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);

void v2xMissionCallback(const v2x_msgs::Mission1& msg);

};


