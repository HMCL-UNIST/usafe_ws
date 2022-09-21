
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
#include <eigen3/Eigen/Geometry>

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
#include <tools/amathutils.hpp>
#include <random>
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846264338
using namespace std;
namespace planner{


typedef pair<int, int> iPair;
 
// This class represents a directed graph using
// adjacency list representation
class Graph {
    int V; // No. of vertices 
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int> >* adj; 
public:
    Graph(int V); // Constructor 
    void clearEdges();
    // function to add an edge to graph
    void addEdge(int u, int v, int w); 
    // output shortest path from s to 0
    std::vector<int> shortestPath(int s);
};
 


class RacingLinePlanner 
{
  
private:
    int tmp;
    
    
 
public:

RacingLinePlanner(); 
~RacingLinePlanner();

int number_of_node;
Eigen::MatrixXd route_graph;
std::vector<int> best_route_idx;
planner::Graph* g;

void load_map();

void gen_random_graph();


int get_min_cost_index(std::vector<double> costs,std::vector<bool> sptSet);
bool compute_best_route(int src_idx);

void waypoint_to_graph();
void compute_edge_cost();


// void constrcut_viz();
// void viz_pub(const ros::TimerEvent& time);

// void get_distance_to_stop_line(poseition pose)


// void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);


};





}


