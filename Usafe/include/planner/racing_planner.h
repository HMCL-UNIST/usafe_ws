
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
#include <cmath>
#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <chrono>
#include <ros/ros.h>
#include <ros/time.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/PoseStamped.h>

#include <eigen3/Eigen/Geometry>

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
    Waypoint(){}
    ~Waypoint(){}
    Waypoint(double x_pose_, double y_pose_, int cost_){
        x_pose = x_pose_;
        y_pose = y_pose_;
        cost = cost_;
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
    visualization_msgs::MarkerArray GenEdgeMarkerArray(const std::vector<Waypoint>& waypoints);
};
 




class RacingLinePlanner 
{
  
private:
    int tmp;
    ros::NodeHandle nh_, nh_p_;
    ros::Publisher  shortest_path_pub, g_map_pub, waypoints_pub, edges_pub;
    ros::Subscriber point_sub;
    ros::Timer viz_timer;
    std::vector<Waypoint> waypoints;
    std::vector<geometry_msgs::Pose> waypoints_pose;
    visualization_msgs::MarkerArray edgeMarkerArray, map_marker_array, waypoint_marker_array;
    visualization_msgs::Marker shortestPathMarker;
    lanelet::LaneletMapPtr map;
    lanelet::routing::RoutingGraphUPtr routingGraph;
    lanelet::Lanelets road_lanelets;
    lanelet::ConstLanelets road_lanelets_const;
    std::string osm_file_name;
    double origin_lat, origin_lon, origin_att;
    double edge_valid_dist_to_line_thres = 3.0;
    double edge_centerline_aling_angle_limit = PI/6;
    double avoidance_wp_add_green_dist = 3.0;
    int scenario_cout; 
public:
RacingLinePlanner(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p); 
~RacingLinePlanner();

int number_of_node;
Eigen::MatrixXd route_graph;
std::vector<int> best_route_idx;
planner::Graph g;
planner::Graph g2;

void load_map();

void gen_random_graph();


void viz_pub(const ros::TimerEvent& time);
bool compute_best_route(int src_idx);


void compute_edge_cost();
void construct_lanelets_with_viz();
void callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg);
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
void inserWaypoints(double x, double y, int cost);
// void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);
void getShortestPath();

};





}


