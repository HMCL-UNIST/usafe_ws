
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
#include <planner/racing_planner.h>
 #include <tools/map_loader_utils.h>
#include <random>


#define PI 3.14159265358979323846264338


namespace planner{
  
RacingLinePlanner::RacingLinePlanner(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p):nh_(nh),nh_p_(nh_p)
{

    nh_p_.param<std::string>("osm_file_name", osm_file_name, "Town01.osm");
    nh_p_.getParam("osm_file_name", osm_file_name);    
    nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
    nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
    nh_p_.param<double>("map_origin_att", origin_att, 0.0);
    // Graph reset
    g.clearEdges();

    // Set publisher and subscriber 
    g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);      
    waypoints_pub = nh_.advertise<visualization_msgs::MarkerArray>("/waypoints", 2, true);          
    point_sub = nh_.subscribe("move_base_simple/goal", 1, &RacingLinePlanner::callbackGetGoalPose, this);

    // Set timer callbacks
    viz_timer = nh_.createTimer(ros::Duration(0.1), &RacingLinePlanner::viz_pub,this);    

    // Initialize Map 
    load_map();
    lanelet::traffic_rules::TrafficRulesPtr trafficRules =  lanelet::traffic_rules::TrafficRulesFactory::create(lanelet::Locations::Germany, lanelet::Participants::Vehicle);
    routingGraph = lanelet::routing::RoutingGraph::build(*map, *trafficRules);      
    construct_lanelets_with_viz();
  
      
  return;  
}


RacingLinePlanner::~RacingLinePlanner()
{}

void RacingLinePlanner::setupGraph(){
    
}

void RacingLinePlanner::callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg){
    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rangg(1,100); 
    auto cost = rangg(rng);    
    planner::Waypoint waypoint_tmp = planner::Waypoint(msg->pose.position.x, msg->pose.position.y, double(cost));
    waypoints.push_back(waypoint_tmp);
    waypoints_pose.push_back(msg->pose);
    if(waypoints_pose.size() > 1){ 
        is_forward(waypoints_pose[waypoints_pose.size()-2],waypoints_pose[waypoints_pose.size()-1]);
        
       
    }  
    // Reinitilize Graph using waypoints
    
    
         
    
}

void RacingLinePlanner::viz_pub(const ros::TimerEvent& time){  
    g_map_pub.publish(map_marker_array);    
    // Visualize Markers 
    visualization_msgs::MarkerArray waypoint_marker_array;
    for(int i=0; i < waypoints.size(); i++){
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time();
        marker.ns = "waypoint";
        marker.id = i;
        marker.type = visualization_msgs::Marker::SPHERE;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = waypoints[i].x_pose;
        marker.pose.position.y = waypoints[i].y_pose;
        marker.pose.position.z = 0.0;        
        marker.pose.orientation.w = 1.0;        
        marker.scale.x = 2;
        marker.scale.y = 2;
        marker.scale.z = 2;
        marker.color.a = 1.0; // Don't forget to set the alpha!
        marker.color.r = waypoints[i].cost/100;
        marker.color.g = 1.0-waypoints[i].cost/100;
        marker.color.b = 0.0;        
        waypoint_marker_array.markers.push_back(marker);        
    }
    waypoints_pub.publish(waypoint_marker_array);
    // Visualize Edges between Markers
}

void RacingLinePlanner::construct_lanelets_with_viz(){
  ROS_INFO("constructing lanelets viz ..... ");
  lanelet::Lanelets all_lanelets = laneletLayer(map); 
  lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(map);
  road_lanelets = roadLanelets(all_lanelets);  
  road_lanelets_const = roadLaneletsConst(all_laneletsConst);    
  
  std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
  std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
  std_msgs::ColorRGBA cl_road, cl_cross, cl_ll_borders, cl_tl_stoplines, cl_ss_stoplines, cl_trafficlights;
  setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
  setColor(&cl_cross, 0.2, 0.7, 0.2, 0.3);
  setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);
  setColor(&cl_tl_stoplines, 1.0, 0.5, 0.0, 0.5);
  setColor(&cl_ss_stoplines, 1.0, 0.0, 0.0, 0.5);
  setColor(&cl_trafficlights, 0.0, 0.0, 1.0, 0.8);

  insertMarkerArray(&map_marker_array, laneletsBoundaryAsMarkerArray(
    road_lanelets, cl_ll_borders));
  insertMarkerArray(&map_marker_array, trafficLightsAsTriangleMarkerArray(
    tl_reg_elems, cl_trafficlights));
  
  insertMarkerArray(&map_marker_array, lineStringsAsMarkerArray(
    tl_stop_lines, "traffic_light_stop_lines", cl_tl_stoplines));

  ROS_INFO("Visualizing lanelet2 map with %lu lanelets, %lu stop lines",
    all_lanelets.size(), tl_stop_lines.size());
 
}



void RacingLinePlanner::load_map(){
  
  ROS_INFO("map loading");
  lanelet::ErrorMessages errors;  
  lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));    
  map = load(osm_file_name, "osm_handler",projector,&errors);
  assert(errors.empty()); 
  ROS_INFO("map loaded succesfully");
}


void RacingLinePlanner::gen_random_graph(){                
    if(number_of_node > 0){
        g = planner::Graph(number_of_node);        
    }    
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 8);
    g.addEdge(2, 3, 8);
    return;    
}


bool RacingLinePlanner::compute_best_route(int src_idx){        
    std::vector<int> paths_tmp = g.shortestPath(src_idx);    
    if(paths_tmp.size() > 0){
        best_route_idx = paths_tmp;        
        return true;
    }
    return false;
}

void RacingLinePlanner::waypoint_to_graph(){
return; 
}
void RacingLinePlanner::compute_edge_cost(){
    return ;
}

bool RacingLinePlanner::is_forward(const geometry_msgs::Pose& from_waypoint, const geometry_msgs::Pose& to_waypoint){
     
        auto start_time=  std::chrono::high_resolution_clock::now();            
            
        bool from_to_valid = false;    

        int from_closest_lane_idx = get_closest_lanelet(road_lanelets_const,from_waypoint);      
        int to_closest_lane_idx = get_closest_lanelet(road_lanelets_const,to_waypoint);      
        
        // if they are in the same lanelet 
        if (to_closest_lane_idx == from_closest_lane_idx){
            lanelet::ConstLineString3d centerline = road_lanelets_const.at(from_closest_lane_idx).centerline();
            lanelet::ArcCoordinates from_cord = get_ArcCoordinate(centerline,from_waypoint);
            lanelet::ArcCoordinates to_cord = get_ArcCoordinate(centerline,to_waypoint);            
            if (from_cord.length < to_cord.length)
                from_to_valid = true;                    
        }else{
            int left_next_lane_idx = -1;
            int left_left_next_lane_idx =-1; 
            int right_next_lane_idx =-1; 
            int right_right_next_lane_idx =-1; 

            auto left_next_lane = routingGraph->left(road_lanelets_const.at(from_closest_lane_idx));             
            if(left_next_lane){
                left_next_lane_idx = left_next_lane.get().id();
                auto left_left_next_lane = routingGraph->left(left_next_lane.get());             
                if(left_left_next_lane){
                    left_left_next_lane_idx = left_left_next_lane.get().id();
                }
            }
            
            auto right_next_lane = routingGraph->right(road_lanelets_const.at(from_closest_lane_idx)); 
            if(right_next_lane){
                right_next_lane_idx = right_next_lane.get().id();
                    auto right_right_next_lane = routingGraph->right(right_next_lane.get());             
                    if(right_right_next_lane){
                        right_right_next_lane_idx = right_right_next_lane.get().id();
                    }
            }   
            
            if((left_next_lane_idx == road_lanelets_const.at(to_closest_lane_idx).id()) ||
            (left_left_next_lane_idx == road_lanelets_const.at(to_closest_lane_idx).id()) ||
            (right_next_lane_idx == road_lanelets_const.at(to_closest_lane_idx).id()) ||
            (right_right_next_lane_idx == road_lanelets_const.at(to_closest_lane_idx).id()))
            {
                    lanelet::ConstLineString3d centerline = road_lanelets_const.at(from_closest_lane_idx).centerline();
                    lanelet::ArcCoordinates from_cord = get_ArcCoordinate(centerline,from_waypoint);
                    lanelet::ArcCoordinates to_cord = get_ArcCoordinate(centerline,to_waypoint);                    
                    if (from_cord.length < to_cord.length){
                        from_to_valid = true;                    
                    }
            }else{
                lanelet::Optional<lanelet::routing::Route> route = routingGraph->getRoute(road_lanelets_const[from_closest_lane_idx], road_lanelets_const[to_closest_lane_idx], 0);
                    if(!route){
                        from_to_valid = false;                        
                    }else{
                        from_to_valid = true;                        
                    }
            }
            
        }        
            if (from_to_valid){
                ROS_WARN("from - > to");     
            }else{
                ROS_WARN("to - > from, backward");     
            }        
            auto stop_time=  std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
            cout << duration.count() << endl;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


Graph::Graph(){
    V = 0;
    clearEdges();
}
Graph::~Graph()
{}
// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::clearEdges(){
    adj = new list<iPair>[V];
}
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
std::vector<int> Graph::shortestPath(int src)
{   // Start at "src" to Goal "0"  
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/  
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    vector<int> dist(V, INF);
    vector<int> paths(V,0);
    pq.push(make_pair(0, src));
    dist[src] = 0; 
    
    while (!pq.empty()) {        
        int u = pq.top().second;
        pq.pop();
        list<pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {            
            int v = (*i).first;
            int weight = (*i).second;
            if (dist[v] > dist[u] + weight) {                
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                paths[v] = u;                
            }
        }
    }         
    int idx_tmp=  0;
    int while_safe_count = 0;   
    std::vector<int> path_idxs;
    path_idxs.push_back(0);
    while (idx_tmp !=src){    
        idx_tmp = paths[idx_tmp];
        path_idxs.push_back(idx_tmp);
        while_safe_count++;
        if(while_safe_count> V*V){
            path_idxs.clear();
            break;            
        }
    }    
    std::reverse(path_idxs.begin(), path_idxs.end());
    return path_idxs;    

}


}
