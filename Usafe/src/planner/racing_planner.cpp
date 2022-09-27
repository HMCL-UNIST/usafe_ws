
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
    positive_cost_assign_ = false;
    // Set publisher and subscriber 
    g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);      
    waypoints_pub = nh_.advertise<visualization_msgs::MarkerArray>("/waypoints", 2, true);          
    edges_pub = nh_.advertise<visualization_msgs::MarkerArray>("/Waypoint_edges", 2, true);          
    shortest_path_pub = nh_.advertise<visualization_msgs::Marker>("/shortest_path", 2, true);          
    global_path_pub = nh_.advertise<visualization_msgs::Marker>("/global_path", 2, true);          
    point_sub = nh_.subscribe("move_base_simple/goal", 1, &RacingLinePlanner::callbackGetGoalPose, this);

    // Set timer callbacks
    viz_timer = nh_.createTimer(ros::Duration(0.1), &RacingLinePlanner::viz_pub,this);    

    // Initialize Map 
    load_map();
    lanelet::traffic_rules::TrafficRulesPtr trafficRules =  lanelet::traffic_rules::TrafficRulesFactory::create(lanelet::Locations::Germany, lanelet::Participants::Vehicle);
    routingGraph = lanelet::routing::RoutingGraph::build(*map, *trafficRules);      
    construct_lanelets_with_viz();
    start_and_goal_wps_setup = false;
    // 
    waypoints.clear();
    waypoints_pose.clear();
    scenario_cout = 0;
    insertDefaultWaypoints(scenario_cout);
    
  return;  
}


RacingLinePlanner::~RacingLinePlanner()
{}

bool RacingLinePlanner::compute_global_path(){
    global_path_wps.clear();
    if(!setup_for_belowPath())
        return false;
    if(!getShortestPath())
        return false;
    if(!setup_for_abovePath())
        return false;
    if(!getShortestPath())
        return false;
    globalPathMarker = getGlobalPathMarker(global_path_wps);  
    return true;
}

bool RacingLinePlanner::setup_for_abovePath(){
    if (waypoints.size() >2 ){        
        waypoints.pop_front();
        waypoints.pop_front();
        waypoints_pose.pop_front();
        waypoints_pose.pop_front();    
        scenario_cout = 0;
        insertDefaultWaypoints(scenario_cout);
        start_and_goal_wps_setup = true;
        return true;
    } 
    else{
        return false;
    }
    
}

bool RacingLinePlanner::setup_for_belowPath(){
    if (waypoints.size() >2 ){
        waypoints.pop_front();
        waypoints.pop_front();
        waypoints_pose.pop_front();
        waypoints_pose.pop_front();  
        scenario_cout = 1;
        insertDefaultWaypoints(scenario_cout);
        start_and_goal_wps_setup = true;
        return true;
    }else{
        return false;
    }
}

void RacingLinePlanner::inserWaypoints(double x, double y, int cost, bool push_front = false){
    geometry_msgs::Pose wp_tmp;
    wp_tmp.position.x = x;
    wp_tmp.position.y = y;
    planner::Waypoint waypoint_tmp = planner::Waypoint(x, y, cost);    
    if(push_front){
        waypoints.push_front(waypoint_tmp);
        waypoints_pose.push_front(wp_tmp);   
    }else{
        waypoints.push_back(waypoint_tmp);
        waypoints_pose.push_back(wp_tmp);
    }
    
}
void RacingLinePlanner::insertDefaultWaypoints(int scenario_num){
    // waypoints.clear();
    // waypoints_pose.clear();
    // Insert Start and Goal waypoint
    if(scenario_num == 0){
        // First goal point --> x = 215, y = -44.1;
        double goal_x = 222.59;
        double goal_y = -52.13;  
        inserWaypoints(goal_x, goal_y, 0, true);    
        double start_x = -510.7;
        double start_y = 754.54;
        inserWaypoints(start_x, start_y, 100, true);    
    }else{
        double goal_x = -424.38;
        double goal_y = 645.4;  
        inserWaypoints(goal_x, goal_y, 0, true);    
        double start_x = -10.0;
        double start_y = 192.6;
        inserWaypoints(start_x, start_y, 100, true);
    }
    // Second goal point --> x = 215, y = -44.1;
    
    // Insert current posision (Start posision d)
}


void RacingLinePlanner::setupGraph(){
    // Reinitilize Graph using waypoints    
    number_of_node = waypoints.size();
    if(number_of_node > 0){
        g = planner::Graph(number_of_node);        
        g.clearEdges();    
    }else{
        return;
    }     
    for(int i = 0; i < waypoints.size() ; i++){
        for(int j = 0; j < waypoints.size() ; j++){
            if(i!=j){
                // bool is_forward_tmp =is_forward(waypoints_pose[i],waypoints_pose[j]);
                bool is_forward_tmp =is_forward(waypoints[i],waypoints[j]);
                if(is_forward_tmp){                    
                    if(is_EdgeValid(waypoints[i],waypoints[j])){
                        double dist_tmp = waypoints[i].dist_to(waypoints[j]);
                        int dist_cost = int(distance_cost_weight*dist_tmp);                        
                        g.addEdge(i, j,waypoints[j].cost+dist_cost);      
                        }              
                } 
            }            
        }
    }
}

planner::Waypoint RacingLinePlanner::gen_Wp(lanelet::ConstLanelet lanelet_,geometry_msgs::Pose &bad_wp_pose,int cost_){
        lanelet::ConstLineString3d centerline_ = lanelet_.centerline();
        auto near_idx =  getClosestWaypoint(true,centerline_, bad_wp_pose);
        auto near_point = centerline_[near_idx];
        planner::Waypoint avoidance_sp;
        avoidance_sp.x_pose = near_point.x();
        avoidance_sp.y_pose = near_point.y();
        avoidance_sp.cost = cost_;
        return avoidance_sp;
}

std::vector<Waypoint> RacingLinePlanner::AddWaypoint(const Waypoint& bad_wp,int cost_){
    std::vector<Waypoint> good_waypoints;
    planner::Waypoint avoid_wp;
    geometry_msgs::Pose bad_wp_pose; 
    bad_wp_pose.position.x = bad_wp.x_pose ;
    bad_wp_pose.position.y = bad_wp.y_pose ;
        

    int to_closest_lane_idx = get_closest_lanelet(road_lanelets_const,bad_wp_pose);                      
    auto left_next_lane = routingGraph->left(road_lanelets_const.at(to_closest_lane_idx));             
        if(left_next_lane){      
            avoid_wp = gen_Wp(left_next_lane.get(),bad_wp_pose,cost_);
            good_waypoints.push_back(avoid_wp);                
            auto left_left_next_lane = routingGraph->left(left_next_lane.get());
                if(left_left_next_lane){
                    avoid_wp = gen_Wp(left_left_next_lane.get(),bad_wp_pose,cost_);
                    good_waypoints.push_back(avoid_wp);
                }
            }
                
        auto right_next_lane = routingGraph->right(road_lanelets_const.at(to_closest_lane_idx)); 
        if(right_next_lane){
          
            avoid_wp = gen_Wp(right_next_lane.get(),bad_wp_pose,cost_);
            good_waypoints.push_back(avoid_wp);                
            auto right_right_next_lane = routingGraph->right(right_next_lane.get());             
                if(right_right_next_lane){
                    
                    avoid_wp = gen_Wp(right_right_next_lane.get(),bad_wp_pose,cost_);
                    good_waypoints.push_back(avoid_wp);
                }
        }

        // filter if there is green point near by 
    std::vector<Waypoint> filt_good_waypoints;
    if(good_waypoints.size()>0){
        for(int j = 0; j<  good_waypoints.size(); j++){
            bool insert_sp = true;
            for(int i=0; i< waypoints.size(); i++){            
                double dist_tmp = waypoints[i].dist_to(good_waypoints[j]);
                if(dist_tmp < avoidance_wp_add_green_dist)
                    insert_sp = false;                    
            }       
            if(insert_sp)
                filt_good_waypoints.push_back(good_waypoints[j]);                                    
            
        }
    
    }
    return filt_good_waypoints;
}

std::vector<Waypoint> RacingLinePlanner::getclosest2Waypoints(const Waypoint& wp){
    geometry_msgs::Pose wp_pose;
    wp_pose.position.x = wp.x_pose;
    wp_pose.position.y = wp.y_pose;
    int lane_index = get_closest_lanelet(road_lanelets_const,wp_pose);  
    auto centerline_ = road_lanelets_const[lane_index].centerline();
    auto near_idx =  getClosestWaypoint(true,centerline_, wp_pose);
    std::vector<Waypoint> closest_wps;
    Waypoint closest_wp;
    closest_wp.x_pose = centerline_[near_idx].x();
    closest_wp.y_pose = centerline_[near_idx].y();
    closest_wp.cost = 50.0;
    closest_wps.push_back(closest_wp);
    if(near_idx == centerline_.size()-1){    
    closest_wp.x_pose = centerline_[near_idx-1].x();
    closest_wp.y_pose = centerline_[near_idx-1].y();    
    }else{
    closest_wp.x_pose = centerline_[near_idx+1].x();
    closest_wp.y_pose = centerline_[near_idx+1].y();    
    }
    closest_wps.push_back(closest_wp);
    return closest_wps;
}

bool RacingLinePlanner::is_EdgeValid(const Waypoint& wp1, const Waypoint& wp2){
    bool valid_flag = true;    
    // check if waypoints, which are in the middle of wp1 and wp2, too close to the line between wp1 and wp2
    for( int k=0;k < waypoints.size() ; k++){            
        if(!(waypoints[k] == wp1) && !(waypoints[k] == wp2)){
            double p1[2] = {wp1.x_pose, wp1.y_pose};
            double p2[2] = {wp2.x_pose, wp2.y_pose};
            double p3[2] = {waypoints[k].x_pose, waypoints[k].y_pose};
            double angle_ = get_angle_between_vec(p3,p1,p2);            
            // check if the points between two points
            if(fabs(angle_) > PI/2.0){
                double dist_to_line = get_project_ver_dist(p1,p2,p3);                                
                if(dist_to_line < edge_valid_dist_to_line_thres)
                    valid_flag = false;                        
            }            
        }        
    }

    // If the angle between centerline and edge too big
    if(valid_flag){
        std::vector<Waypoint> cwps =  getclosest2Waypoints(wp1);
        double wp1_[2] = {cwps[0].x_pose, cwps[0].y_pose};
        double wp2_[2] = {cwps[1].x_pose, cwps[1].y_pose};
        double wp3_[2] = {wp2.x_pose, wp2.y_pose};
        double angle_from_centerline = get_angle_between_vec(wp1_,wp2_,wp3_);            
        if (fabs(angle_from_centerline) > edge_centerline_aling_angle_limit){
             valid_flag = false;   
        }
    }
  

    return valid_flag;
}




void RacingLinePlanner::callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg){
    
    // Random cost assignment ///////////////////////////////////////////////
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> rangg(0,100);     
    // int cost = rangg(rng);    
    // while( cost > 100 ){
    //     cost = rangg(rng);    
    // }    
    // if (cost> 50){
    //     cost = 99;
    //     // obstacle 
    // }else{
    //     cost = 0;
    //     // Score item! 
    // }
    // Random cost assignment finish ///////////////////////////////////////////////
    int cost;
    if(positive_cost_assign_){
        cost = 0;    
    }else{
        cost = 99;
    }

    geometry_msgs::Pose prior_wp;
    prior_wp = msg->pose;
    int lane_index = get_closest_lanelet(road_lanelets_const,prior_wp);  
    auto centerline_ = road_lanelets_const[lane_index].centerline();
    auto near_idx =  getClosestWaypoint(true,centerline_, prior_wp);
    auto near_point = centerline_[near_idx];
    
    geometry_msgs::Pose wp_tmp;
    wp_tmp.position.x = near_point.x();
    wp_tmp.position.y = near_point.y();
    planner::Waypoint waypoint_tmp = planner::Waypoint(wp_tmp.position.x, wp_tmp.position.y, cost);
    
    waypoints.push_back(waypoint_tmp);
    waypoints_pose.push_back(wp_tmp);
    
    if( cost > 50){        
        std::vector<Waypoint> avoidance_wps = AddWaypoint(waypoint_tmp,60);                
        if(avoidance_wps.size() > 0){
            for(int i=0; i < avoidance_wps.size(); i++){
                waypoints.push_back(avoidance_wps[i]);
                geometry_msgs::Pose tmp_pose; 
                tmp_pose.position.x = avoidance_wps[i].x_pose;
                tmp_pose.position.y = avoidance_wps[i].y_pose;
                waypoints_pose.push_back(tmp_pose);
            }
        }
        
    }else{
        std::vector<Waypoint> avoidance_wps = AddWaypoint(waypoint_tmp,40);                
        if(avoidance_wps.size() > 0){
            for(int i=0; i < avoidance_wps.size(); i++){
                waypoints.push_back(avoidance_wps[i]);
                geometry_msgs::Pose tmp_pose; 
                tmp_pose.position.x = avoidance_wps[i].x_pose;
                tmp_pose.position.y = avoidance_wps[i].y_pose;
                waypoints_pose.push_back(tmp_pose);
            }
        }
    }
      
}

visualization_msgs::Marker RacingLinePlanner::getGlobalPathMarker(std::deque<Waypoint> wps){
     visualization_msgs::Marker PathMarker;
     if(waypoints_pose.size() > 1 ){          
        PathMarker.points.clear();
        PathMarker.header.frame_id = "map";
        PathMarker.header.stamp = ros::Time();        
        PathMarker.id = 2000;
        PathMarker.ns = "globalPath";                
        PathMarker.pose.position.x = 0.0;
        PathMarker.pose.position.y = 0.0;
        PathMarker.pose.position.z = 0.0;
        PathMarker.type = 4;
        PathMarker.action = visualization_msgs::Marker::ADD;
        PathMarker.scale.x = 0.5;
        PathMarker.color.a = 1.0; 
        PathMarker.color.r = 1.0;
        PathMarker.color.g = 0.0;
        PathMarker.color.b = 1.0;
        for(int i =0; i< wps.size(); i++){                                
                geometry_msgs::Point point_;                            
                point_.x = wps[i].x_pose;                
                point_.y = wps[i].y_pose;                
                point_.z = 1.0;
                PathMarker.points.push_back(point_);                
        }    
    }
    return PathMarker;
}

bool RacingLinePlanner::getShortestPath(){    
    if(!start_and_goal_wps_setup){
        return false;
    }
    if(waypoints_pose.size() < 2){
        return false;
    }
        
    
        auto start_time=  std::chrono::high_resolution_clock::now();                   
        
        setupGraph();
        edgeMarkerArray = g.GenEdgeMarkerArray(waypoints);        
        auto stop_time=  std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
        ROS_INFO("Path computation time = %d ms",duration.count() );
    


    // if(waypoints_pose.size() > 6 && scenario_cout ==0 ){          
        
        shortestPathMarker.points.clear();
        shortestPathMarker.header.frame_id = "map";
        shortestPathMarker.header.stamp = ros::Time();        
        shortestPathMarker.id = 1000;
        shortestPathMarker.ns = "shortestpath";                
        shortestPathMarker.pose.position.x = 0.0;
        shortestPathMarker.pose.position.y = 0.0;
        shortestPathMarker.pose.position.z = 0.0;
        shortestPathMarker.type = 4;
        shortestPathMarker.action = visualization_msgs::Marker::ADD;
        shortestPathMarker.scale.x = 0.5;
        shortestPathMarker.color.a = 1.0; 
        shortestPathMarker.color.r = 1.0;
        shortestPathMarker.color.g = 0.0;
        shortestPathMarker.color.b = 1.0;
        // 1 is the start point,  and 0 is the goal point
        std::vector<int> shortest_path_wp_idx = g.shortestPath(1);
        
        for(int i =0; i< shortest_path_wp_idx.size(); i++){                              
                // ROS_INFO("shortest_path_wp_idx[i] = %d", shortest_path_wp_idx[i]);
                global_path_wps.push_front(waypoints.at(shortest_path_wp_idx[i]));
                geometry_msgs::Point point_;                            
                point_.x = waypoints.at(shortest_path_wp_idx[i]).x_pose;                
                point_.y = waypoints.at(shortest_path_wp_idx[i]).y_pose;                
                point_.z = 1.0;
                shortestPathMarker.points.push_back(point_);                
        }
        ROS_INFO("best path computed");
    best_route_idx = shortest_path_wp_idx; 
    // scenario_cout++;    
   

    return true;
  
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
        if (waypoints[i].cost < 50){
            marker.color.r = 0.0;
            marker.color.g = 1-waypoints[i].cost/100.0;
        }else{
            marker.color.r = waypoints[i].cost/100.0;
            marker.color.g = 0.0;
        }        
        marker.color.b = 0.0;        
        waypoint_marker_array.markers.push_back(marker);        
    }
    waypoints_pub.publish(waypoint_marker_array);
    
    if( waypoints.size() > 1)
        edges_pub.publish(edgeMarkerArray);

    if(shortestPathMarker.points.size()>0)
        shortest_path_pub.publish(shortestPathMarker);

    if(globalPathMarker.points.size()>0)
        global_path_pub.publish(globalPathMarker);
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


void RacingLinePlanner::compute_edge_cost(){
    return ;
}



// bool RacingLinePlanner::is_forward(const geometry_msgs::Pose& from_waypoint, const geometry_msgs::Pose& to_waypoint){
bool RacingLinePlanner::is_forward(const Waypoint& from_wp, Waypoint& to_wp){
     
        geometry_msgs::Pose from_waypoint, to_waypoint;
        from_waypoint.position.x = from_wp.x_pose;
        from_waypoint.position.y = from_wp.y_pose;
        to_waypoint.position.x = to_wp.x_pose;
        to_waypoint.position.y = to_wp.y_pose;

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
            // if (from_to_valid){
            //     ROS_WARN("from - > to");     
            // }else{
            //     ROS_WARN("to - > from, backward");     
            // }        
        return from_to_valid;
            
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

visualization_msgs::MarkerArray Graph::GenEdgeMarkerArray(const std::deque<Waypoint>& waypoints){
        visualization_msgs::MarkerArray Edgemarkers;
        int id_count = 0;
        for(int i=0;i< V;i++){
            list<pair<int, int> >::iterator j;
            for (j = adj[i].begin(); j != adj[i].end(); j++) {            
            int v = (*j).first;
            int weight = (*j).second;
            visualization_msgs::Marker edge_line;
            id_count++;
            edge_line.header.frame_id = "map";
            edge_line.header.stamp = ros::Time();
            edge_line.type = 4;
            edge_line.id = id_count;
            edge_line.scale.x = 0.3;
            edge_line.color.a = 0.5;            
            if (weight > 50){
                edge_line.color.r = weight/100.0;
                edge_line.color.g = 0.0;
            }else{
                edge_line.color.r = 0.0;
                edge_line.color.g = 1-weight/100.0;
            }        
            edge_line.color.b = 0.0;      
            geometry_msgs::Point from_point, to_point;            
            from_point.x = waypoints.at(i).x_pose;
            from_point.y = waypoints.at(i).y_pose;
            from_point.z = 0.5;
            to_point.x = waypoints.at(v).x_pose;
            to_point.y = waypoints.at(v).y_pose;
            to_point.z = 0.5;
            edge_line.points.push_back(from_point);
            edge_line.points.push_back(to_point);
            Edgemarkers.markers.push_back(edge_line);

        }
    }
        
      
        return Edgemarkers;
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
