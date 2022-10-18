
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
#include <cmath>
#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include <mutex>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64.h>
#include "planner/vehicle_model.h"
#include "tools/amathutils.hpp"

#include <tools/polyfit.h>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>

#include <eigen3/Eigen/Geometry>
#include <v2x_msgs/Mission2.h>

#include <hmcl_msgs/VehicleStatus.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/BehaviorFactor.h>
#include <hmcl_msgs/TransitionCondition.h>

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
#include <random>

#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846264338
using namespace std;
namespace planner{



class Waypoint{        
public:
    double x_pose,y_pose;    
    int cost;   
    int id;     
    Waypoint(){}
    ~Waypoint(){}
    Waypoint(double x_pose_, double y_pose_, int cost_){
        x_pose = x_pose_;
        y_pose = y_pose_;
        cost = cost_;
        // id+=1;
    }
    bool operator == (const Waypoint  &obj){
        if(x_pose == obj.x_pose &&
            y_pose == obj.y_pose && 
            cost == obj.cost){
                return true;
            }else{
                return false;
            }

    }

    bool operator = (const Waypoint  &obj){
        x_pose = obj.x_pose;
            y_pose = obj.y_pose;
            cost = obj.cost;
                id = obj.id;

    }

    double dist_to(const Waypoint & wp2){
        return sqrt((x_pose-wp2.x_pose)*(x_pose-wp2.x_pose)+ (y_pose-wp2.y_pose)*(y_pose-wp2.y_pose));
    }
    
 };



typedef pair<int, int> iPair;
 
// This class represents a directed graph using
// adjacency list representation
class Graph {
    int V; // No. of vertices 
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int> >* adj; 
public:
    Graph();
    ~Graph();
    Graph(int V); // Constructor 

    void clearEdges();
    // function to add an edge to graph
    void addEdge(int u, int v, int w); 
    // output shortest path from s to 0
    std::vector<int> shortestPath(int s);
    // generate marker array for edges 
    visualization_msgs::MarkerArray GenEdgeMarkerArray(const std::deque<Waypoint>& waypoints);
};
 




class RacingLinePlanner 
{
  
private:
    
    std::mutex mu_mtx;
    int tmp;
    ros::NodeHandle nh_, nh_p_;

    ros::Publisher  local_traj_pub, l_traj_viz_pub, target_path_pub, global_path_pub, shortest_path_pub, g_map_pub, waypoints_pub, edges_pub;
    ros::Publisher velPub, local_lane_statePub;    
    ros::Publisher boost_duration_pub, light_pub;
    // ros::Subscriber point_sub;
    ros::Subscriber curpose_sub, curodom_sub, vehicle_status_sub;    
    ros::Timer viz_timer;
    std::deque<Waypoint> waypoints;
    std::deque<geometry_msgs::Pose> waypoints_pose;
    visualization_msgs::MarkerArray edgeMarkerArray, map_marker_array, waypoint_marker_array, local_traj_marker_arrary;
    visualization_msgs::Marker shortestPathMarker, globalPathMarker;
    lanelet::LaneletMapPtr map, map_for_driving;
    lanelet::routing::RoutingGraphUPtr routingGraph, routingGraph_for_driving;
    lanelet::Lanelets road_lanelets;
    lanelet::ConstLanelets road_lanelets_const, road_lanelets_const_for_driving;
    std_msgs::Float64 local_lane_state;
    std::string osm_file_name, osm_file_name_for_driving;
    double Goal_line_pose_lat, Goal_line_pose_lon;
    lanelet::BasicPoint3d Goal_line_point;
    double origin_lat, origin_lon, origin_att;
    double edge_valid_dist_to_line_thres = 3.0;
    double edge_centerline_aling_angle_limit = PI/6;
    double avoidance_wp_add_green_dist = 3.0;
    double distance_cost_weight = 2;
    double point_projection_ignore_threshold = 3.0;
    double lane_overwrite_distance;
    double shift_distance_amount;
    double current_speed;
    double map_road_resolution;
    hmcl_msgs::Lane local_lane_msg;

    ros::Time boost_init_time;
    double boost_speed;
    double boost_duration;

    
    int prev_wp_closest_lane_idx;
    bool polyfit_error;
    double poly_error;


    double shift_speed_ratio, max_shift_speed_ratio, min_shift_speed_ratio;
    double local_path_length, max_local_path_length, min_local_path_length;
    int scenario_cout; 
    int neutral_cost;
    
    bool start_and_goal_wps_setup;
    bool above_path_complete,below_path_complete;    
    bool random_cost_assign; 
    bool cur_pose_available;
    geometry_msgs::PoseStamped cur_pose;
    nav_msgs::Odometry cur_odom;
    lanelet::projection::UtmProjector* projector;    
    
public:

RacingLinePlanner(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p); 
~RacingLinePlanner();


double vel_constant;
bool Mission_start;
bool waypoint_received;
v2x_msgs::Mission2  v2x_data;

std::deque<Waypoint> v2x_waypoints;
planner::VehicleModel* vehicle_model_;
bool positive_cost_assign_;
int number_of_node;
Eigen::MatrixXd route_graph;
std::vector<int> best_route_idx;
planner::Graph g;
planner::Graph g2;
std::deque<Waypoint> global_path_wps;
int waypoint_max_id;

void load_map();
void load_map_for_driving();
void gen_random_graph();

void convert_v2x_data();

void viz_pub(const ros::TimerEvent& time);
bool compute_best_route(int src_idx);

void curve_fitting(hmcl_msgs::Lane& local_traj_msg,std::vector<double> speed_lim);
PolyFit<double> polyfit(std::vector<double> x, std::vector<double> y);

void setup_boostup(ros::Time boost_time, double boost_speed_, double boost_duration_);

void Compute_and_pub_Velocity(std::vector<double> &speed_limits);
double get_yaw(const lanelet::Point3d & _from, const lanelet::Point3d &_to );
hmcl_msgs::Lane LanepointsToLane(std::vector<lanelet::Point3d> target_points, std::vector<double> speed_limits);
void viz_local_path(hmcl_msgs::Lane &lane_);
// std::vector<lanelet::Point3d> LaneFollowPathGen(double path_length, geometry_msgs::Pose pose_);
std::vector<lanelet::Point3d> LaneFollowPathGen(double path_length, geometry_msgs::Pose pose_, std::vector<double> &lane_speed_limits);
visualization_msgs::Marker LaneLetPointsToMarker(std::vector<lanelet::Point3d> &point3d_vector);
void compute_edge_cost();
void construct_lanelets_with_viz();

bool waypoint_s_same(Waypoint wp1, Waypoint wp2);


void currentposeCallback(const nav_msgs::OdometryConstPtr &msg);
void odomCallback(const nav_msgs::OdometryConstPtr& msg);
void callbackVehicleStatus(const hmcl_msgs::VehicleStatusConstPtr &msg);
// bool is_forward(const geometry_msgs::Pose& from_waypoint, const geometry_msgs::Pose& to_waypoint);
bool is_forward(const Waypoint& from_wp, Waypoint& to_wp);
void setupGraph();
bool is_EdgeValid(const Waypoint& wp1, const Waypoint& wp2);
planner::Waypoint gen_Wp(lanelet::ConstLanelet lanelet_,geometry_msgs::Pose& bad_wp_pose,int cost_);
std::vector<Waypoint> AddWaypoint(const Waypoint& bad_wp,int cost_);
std::vector<Waypoint> getclosest2Waypoints(const Waypoint& wp);
// void constrcut_viz();
// void viz_pub(const ros::TimerEvent& time);

// void get_distance_to_stop_line(poseition pose)
void insertDefaultWaypoints(int scenario_num);
void inserWaypoints(int id, double x, double y, int cost, bool push_front);
// void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);
bool getShortestPath();
bool setup_for_Path();
bool compute_global_path();
visualization_msgs::Marker getGlobalPathMarker(std::deque<Waypoint> wps);
void sortGlobalWaypoints();
void localPathGenCallback();



};





}


