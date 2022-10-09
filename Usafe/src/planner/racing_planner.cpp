
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
    nh_p_.param<std::string>("osm_file_name_for_driving", osm_file_name_for_driving, "Town01.osm");
    nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
    nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
    nh_p_.param<double>("map_origin_att", origin_att, 0.0);

    nh_p_.param<double>("min_local_path_length", min_local_path_length, 20.0);
    nh_p_.param<double>("max_local_path_length", max_local_path_length, 30.0);

    nh_p_.param<double>("max_shift_speed_ratio", max_shift_speed_ratio, 0.95);
    nh_p_.param<double>("min_shift_speed_ratio", min_shift_speed_ratio, 0.987);
    nh_p_.param<double>("lane_overwrite_distance", lane_overwrite_distance, 0.8);
    
    shift_speed_ratio = min_shift_speed_ratio;
    
    local_path_length = 30.0;
     
    // Graph reset
    g.clearEdges();
    waypoint_received = false;
    positive_cost_assign_ = false;
    cur_pose_available = false;
    // Set publisher and subscriber 
    g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);      
    waypoints_pub = nh_.advertise<visualization_msgs::MarkerArray>("/waypoints", 2, true);          
    edges_pub = nh_.advertise<visualization_msgs::MarkerArray>("/Waypoint_edges", 2, true);          
    shortest_path_pub = nh_.advertise<visualization_msgs::Marker>("/shortest_path", 2, true);          
    global_path_pub = nh_.advertise<visualization_msgs::Marker>("/global_path", 2, true);          
    target_path_pub = nh_.advertise<visualization_msgs::Marker>("/target_path", 2, true);          
    point_sub = nh_.subscribe("move_base_simple/goal", 1, &RacingLinePlanner::callbackGetGoalPose, this);
    curpose_sub = nh_.subscribe("/pose_estimate", 1, &RacingLinePlanner::currentposeCallback, this);
    vehicle_status_sub = nh_.subscribe("/vehicle_status", 1, &RacingLinePlanner::callbackVehicleStatus, this);
    
    // Set timer callbacks
    viz_timer = nh_.createTimer(ros::Duration(0.1), &RacingLinePlanner::viz_pub,this);    

    // Initialize Map 
    load_map();
    load_map_for_driving();
    ROS_INFO("constructing lanelets ..... ");
    lanelet::traffic_rules::TrafficRulesPtr trafficRules =  lanelet::traffic_rules::TrafficRulesFactory::create(lanelet::Locations::Germany, lanelet::Participants::Vehicle);
    routingGraph = lanelet::routing::RoutingGraph::build(*map, *trafficRules);      
    routingGraph_for_driving = lanelet::routing::RoutingGraph::build(*map_for_driving, *trafficRules);      
    construct_lanelets_with_viz();
    start_and_goal_wps_setup = false;
    // 
    waypoints.clear();
    waypoints_pose.clear();
    scenario_cout = 0;
    // insertDefaultWaypoints(scenario_cout);

    boost::thread local_path_generation(&RacingLinePlanner::localPathGenCallback,this); 
    
  return;  
}


RacingLinePlanner::~RacingLinePlanner()
{}


std::vector<lanelet::Point3d> RacingLinePlanner::LaneFollowPathGen(double path_length, geometry_msgs::Pose pose_){        

    int wp_closest_lane_idx = get_closest_lanelet(road_lanelets_const_for_driving,pose_);      
    lanelet::ConstLineString3d target_centerline = road_lanelets_const_for_driving.at(wp_closest_lane_idx).centerline();
      // gets the projecion of point on ls
    lanelet::Point3d cur_point(lanelet::utils::getId(), pose_.position.x, pose_.position.y,0.0);        
    auto projected_point = lanelet::geometry::project(target_centerline, cur_point);
    geometry_msgs::Pose projected_pose;
    projected_pose.position.x = projected_point.x();
    projected_pose.position.y = projected_point.y();
    int closest_idx = getClosestWaypoint(true, target_centerline, projected_pose);
    auto target_point = target_centerline[closest_idx];
    lanelet::Point3d prev_point;      
    prev_point.x() = target_point.x();
    prev_point.y() = target_point.y();
    double cum_dist = 0.0;
    std::vector<lanelet::Point3d> target_points;
    for(int i = closest_idx; i < target_centerline.size(); i++){
                lanelet::Point3d iter_point; 
                iter_point.x() = target_centerline[i].x();
                iter_point.y() = target_centerline[i].y();
                double dist_tmp = lanelet::geometry::distance(iter_point,prev_point);
                cum_dist += dist_tmp;
                prev_point = iter_point;
                target_points.push_back(iter_point);
                if(cum_dist > path_length)
                    break;
    }
    // path length does not ,meet the requested length 
    if(cum_dist < path_length){
        auto following_lanes = routingGraph_for_driving->following(road_lanelets_const_for_driving.at(wp_closest_lane_idx),false);
        ROS_INFO("Number of Following lanes = %d", following_lanes.size());
        if(following_lanes.size() > 0 ){            
            auto next_target_centerline = following_lanes[0].centerline();
            for(int i = 0; i < next_target_centerline.size(); i++){
                lanelet::Point3d iter_point; 
                iter_point.x() = next_target_centerline[i].x();
                iter_point.y() = next_target_centerline[i].y();
                double dist_tmp = lanelet::geometry::distance(iter_point,prev_point);
                cum_dist += dist_tmp;
                prev_point = iter_point;
                target_points.push_back(iter_point);
                if(cum_dist > path_length)
                    break;
              }
        }        
    }
    return target_points;    
}

double RacingLinePlanner::get_yaw(const lanelet::ConstPoint3d & _from, const lanelet::ConstPoint3d &_to ){
    double _angle = std::atan2(_to.y() - _from.y(), _to.x() - _from.x());
    
    while(_angle > M_PI){
      _angle = _angle - 2*M_PI;
    }
    while(_angle < M_PI){
      _angle = _angle + 2*M_PI;
    }
  return _angle;
}

void RacingLinePlanner::callbackVehicleStatus(const hmcl_msgs::VehicleStatusConstPtr &msg){
  double local_path_scale = 1.0;
  double current_speed = msg->wheelspeed.wheel_speed; // in m/s
  if (current_speed > 0){
    double tmp_add_path_length = current_speed*local_path_scale;
    local_path_length = std::min(min_local_path_length + tmp_add_path_length,max_local_path_length);
    // 60km/h -> 0.95  / 80km/h -> 0.987    
    double tmp_shift_speed_ratio = 0.00666*current_speed + 0.839;
    shift_speed_ratio = std::min(tmp_shift_speed_ratio,max_shift_speed_ratio);
    shift_speed_ratio = std::max(min_shift_speed_ratio,shift_speed_ratio);
  }else{
    local_path_length = min_local_path_length;
  }

}

void RacingLinePlanner::localPathGenCallback() {
  double local_path_loop_hz = 10.0;
  ros::Rate loop_rate(local_path_loop_hz); 
  ROS_INFO_ONCE("Init local path generation thread");  
  while (ros::ok())
  {     
    auto start_time=  std::chrono::high_resolution_clock::now();                    
    std::vector<lanelet::Point3d> local_lane_points;
    if(!cur_pose_available){
        ROS_WARN("Current position is not available");
        loop_rate.sleep();        
        continue;
    }
    if(global_path_wps.size() > 0){
        sortGlobalWaypoints();
        if(global_path_wps.size() < 1){
            loop_rate.sleep();        
            continue;
        }
        // Find the target lookahead point given the target waypoint         
        double lookahead_dist = 50;
        geometry_msgs::Pose wp_pose;        
        wp_pose.position.x = global_path_wps.front().x_pose;
        wp_pose.position.y = global_path_wps.front().y_pose;
        int wp_closest_lane_idx = get_closest_lanelet(road_lanelets_const_for_driving,wp_pose);      
        lanelet::ConstLineString3d target_centerline = road_lanelets_const_for_driving.at(wp_closest_lane_idx).centerline();
        ///////////////////////////
        lanelet::ArcCoordinates cur_pose_cord = get_ArcCoordinate(target_centerline,cur_pose.pose);        
        ROS_INFO(" cur_pose_cord.length  =%f, distance = %f ", cur_pose_cord.length, cur_pose_cord.distance);
        lanelet::Point3d cur_point(lanelet::utils::getId(), cur_pose.pose.position.x, cur_pose.pose.position.y,0.0);        
        auto cur_projected_point = lanelet::geometry::project(target_centerline, cur_point);
        geometry_msgs::Pose cur_projected_pose;
        cur_projected_pose.position.x = cur_projected_point.x();
        cur_projected_pose.position.y = cur_projected_point.y();        
        ///////////////////////////
        if(cur_pose_cord.length == 0.0){
            ROS_WARN("Target lane is too far >> Lane Follow");      
            local_lane_points = LaneFollowPathGen(local_path_length, cur_pose.pose);      
        }
        else{
            if(fabs(cur_pose_cord.distance) > 9.0){
                ROS_WARN("Soemthing wrong with lane projection >> Lane Follow");                
                local_lane_points = LaneFollowPathGen(local_path_length, cur_pose.pose);      
            }else if(fabs(cur_pose_cord.distance) < lane_overwrite_distance){
                ROS_WARN("Distance is a small >> Target Lane Follow");                
                local_lane_points = LaneFollowPathGen(local_path_length, cur_projected_pose);     
            }else{
                ROS_WARN("Deviated Lane Follow");                
                local_lane_points = LaneFollowPathGen(local_path_length, cur_projected_pose);
                
                lanelet::LineString2d target_linstring2d;
                for(int k=0; k < local_lane_points.size(); k++){
                    target_linstring2d.push_back(lanelet::utils::to2D(local_lane_points[k]));                    
                }
                double shift_distance = cur_pose_cord.distance*shift_speed_ratio;                
                auto shifted_target_linstring2d = lanelet::geometry::offset(target_linstring2d, shift_distance);
                for(int k=0; k < local_lane_points.size(); k++){
                    local_lane_points[k].x() = shifted_target_linstring2d[k].x();                    
                    local_lane_points[k].y() = shifted_target_linstring2d[k].y();                    
                }
            }

        }                 
    }else{
        // No waypoints available --> just laneFollow
        ROS_WARN("No waypoints available >> Lane Follow");
        local_lane_points = LaneFollowPathGen(local_path_length, cur_pose.pose);      
    }
    visualization_msgs::Marker local_path_marker = LaneLetPointsToMarker(local_lane_points);
    target_path_pub.publish(local_path_marker);
    auto stop_time=  std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
    if(duration.count() > 1.0/local_path_loop_hz*1000.0){
        ROS_WARN("LocalPath takes too much time to compute = %d ms", duration.count());       
    }
    
    loop_rate.sleep();
    
  }
}

visualization_msgs::Marker RacingLinePlanner::LaneLetPointsToMarker(std::vector<lanelet::Point3d> &point3d_vector){
        visualization_msgs::Marker PathMarker;         
        PathMarker.points.clear();
        PathMarker.header.frame_id = "map";
        PathMarker.header.stamp = ros::Time();        
        PathMarker.id = 2000;
        PathMarker.ns = "predictedPath";                
        PathMarker.pose.position.x = 0.0;
        PathMarker.pose.position.y = 0.0;
        PathMarker.pose.position.z = 0.0;
        PathMarker.type = 4;
        PathMarker.action = visualization_msgs::Marker::ADD;
        PathMarker.scale.x = 0.3;
        PathMarker.color.a = 1.0; 
        PathMarker.color.r = 0.0;
        PathMarker.color.g = 0.0;
        PathMarker.color.b = 1.0;
        for(int i=0;i<point3d_vector.size();i++){                                    
                geometry_msgs::Point point_;                                            
                point_.x = point3d_vector[i].x();                
                point_.y = point3d_vector[i].y();           
                point_.z = 0.5;
                PathMarker.points.push_back(point_);                
          }    
    return PathMarker;
}

bool RacingLinePlanner::compute_global_path(){
    global_path_wps.clear();

    if(!setup_for_Path()){
        ROS_INFO("path setup fail");
        return false;
    }
        
    if(!getShortestPath()){
        ROS_INFO("shortest path found fail");
        return false;
    }
        
    globalPathMarker = getGlobalPathMarker(global_path_wps);  
    return true;
}

bool RacingLinePlanner::setup_for_Path(){
    if (waypoints.size() >2 ){              
        scenario_cout = 0;
        insertDefaultWaypoints(scenario_cout);
        start_and_goal_wps_setup = true;
        return true;
    } 
    else{
        return false;
    }
    
}

void RacingLinePlanner::inserWaypoints(int id, double x, double y, int cost, bool push_front = false){
    geometry_msgs::Pose wp_tmp;
    wp_tmp.position.x = x;
    wp_tmp.position.y = y;
    planner::Waypoint waypoint_tmp = planner::Waypoint(x, y, cost);   
    waypoint_tmp.id = id;         
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
    double goal_x = -205.89;
    double goal_y = 426.2;  
    inserWaypoints(waypoint_max_id+1,goal_x, goal_y, 0, true);    
    double start_x = 76.5;
    double start_y = -165;
    inserWaypoints(-1,start_x, start_y, 200, true);

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
                if ( waypoints[j].id - waypoints[i].id ==1 ){
                    g.addEdge(i, j,waypoints[j].cost);      
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


void RacingLinePlanner::sortGlobalWaypoints(){
    bool sorting = true;
    int while_count = 0;
    
    while(sorting && while_count < 200){
        while_count++;
        planner::Waypoint cur_wp(cur_pose.pose.position.x, cur_pose.pose.position.y, 0);
        if(global_path_wps.size()<1){
            return;
        }
        planner::Waypoint goal_front_wp(global_path_wps.front().x_pose, global_path_wps.front().y_pose,0);        
        bool check_is_front = is_forward(cur_wp,goal_front_wp);
        if(check_is_front){
           sorting = false; 
        }else{
            global_path_wps.pop_front();
        }

        
    }
    return;
}


// void RacingLinePlanner::currentposeCallback(const geometry_msgs::PoseWithCovarianceStampedConstPtr &msg){    
void RacingLinePlanner::currentposeCallback(const nav_msgs::OdometryConstPtr &msg){
    mu_mtx.lock();
    cur_pose.header = msg->header;
    cur_pose.pose = msg->pose.pose;
    cur_pose_available = true;      
    // sortGlobalWaypoints();
    mu_mtx.unlock();  
    globalPathMarker = getGlobalPathMarker(global_path_wps);    
}


void RacingLinePlanner::callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg){
    return;    
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
                global_path_wps.push_front(waypoints.at(shortest_path_wp_idx[i]));
                geometry_msgs::Point point_;                            
                point_.x = waypoints.at(shortest_path_wp_idx[i]).x_pose;                
                point_.y = waypoints.at(shortest_path_wp_idx[i]).y_pose;                
                point_.z = 1.0;
                shortestPathMarker.points.push_back(point_);                
        }
        ROS_INFO("best path computed");
    best_route_idx = shortest_path_wp_idx; 
    
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
        if (waypoints[i].cost < neutral_cost){
            marker.color.r = 0.0;
            marker.color.g = 1;
            marker.color.b = 0.0;
        }else if(waypoints[i].cost == 1){
            marker.color.r = 0.0;
            marker.color.g = 0.0;
            marker.color.b = 1.0;
        }
        else{
            marker.color.r = 1.0;
            marker.color.g = 0.0;
            marker.color.b = 0.0;
        }                    
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
  
//   lanelet::Lanelets all_lanelets = laneletLayer(map);   
//   road_lanelets = roadLanelets(all_lanelets);  
  // FOR path computing
  lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(map);
  road_lanelets_const = roadLaneletsConst(all_laneletsConst);    
  ROS_INFO("Map for Path loaded");
  // For driving 
  lanelet::ConstLanelets all_laneletsConst_for_driving = laneletLayerConst(map_for_driving);
  road_lanelets_const_for_driving = roadLaneletsConst(all_laneletsConst_for_driving);    
  ROS_INFO("Map for Driving loaded");
  
  
  std_msgs::ColorRGBA cl_road, cl_cross, cl_ll_borders;
  setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
  setColor(&cl_cross, 0.2, 0.7, 0.2, 0.3);
  setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);
  
  insertMarkerArray(&map_marker_array, laneletsBoundaryAsMarkerArray(
    road_lanelets_const_for_driving, cl_ll_borders));
  
  ROS_INFO("Visualizing lanelet2 map with %lu lanelets",
    road_lanelets_const.size());
 
}



void RacingLinePlanner::convert_v2x_data(){
// int64 mission_status
// int64 item_count
// v2x_msgs/Mission2data[] States
// int32 item_id
// int32 item_type     # 0 : laptime minus, 1 : laptime plus, 2: boost   // 1=> negative score, 2=> positive score, 3-> booster 
// int32 item_status   # 0 : get(true), 1 : get(false)
// int32 score         # 0 : unavailable(boost), (-) : laptime minus (score up), (+) laptime plus (score down)
// int32 speed         # 0 : stop, 1~254 : max speed, 255 : unavailable(item)
// int32 duration      # 0 : finish, 1~253 : left time, 254 : until final, 255 : unavailable(item)
// float64 pos_lat       
// float64 pos_long
// int32 extend        # meter (circle)
ROS_INFO("Converting V2X mission info innto Waypoints");
waypoints.clear();
waypoints_pose.clear();
if ( v2x_data.States.size()  < 1){
    ROS_WARN("No v2x data available");
}
// Cost re-scaling for graph optimization 
std::vector<double> standarded_score;
for(int i=0; i< v2x_data.States.size(); i++){
    standarded_score.push_back(v2x_data.States[i].score);    
}
standarded_score.push_back(0.0);
amathutils::standardization_(standarded_score);
int multiplier = 100;
std::transform(standarded_score.begin(), standarded_score.end(), standarded_score.begin(), [&multiplier](auto& c){return c*multiplier+2;});
neutral_cost = int(standarded_score.back());
standarded_score.pop_back();
// Minimum cost of the waypoints = 2 
// Neutral cost of the waypoints = neutral_cost
// Minimum cost of the goal = 0 
for(int i = 0; i < v2x_data.States.size(); i++){
    double Lat_data =v2x_data.States[i].pos_lat;
    double Lon_data = v2x_data.States[i].pos_long;
    lanelet::GPSPoint gnssPoint{Lat_data, Lon_data, 0.};
    lanelet::BasicPoint3d converted_point = projector->forward(gnssPoint);        
        geometry_msgs::Pose pose_tmp;
        pose_tmp.position.x = converted_point.x();
        pose_tmp.position.y = converted_point.y();
        planner::Waypoint wp_tmp;
        wp_tmp.x_pose = converted_point.x(); 
        wp_tmp.y_pose = converted_point.y();
        bool project_to_lane = true;
        if(project_to_lane){
                    int lane_index = get_closest_lanelet(road_lanelets_const,pose_tmp);  
                    auto centerline_ = road_lanelets_const[lane_index].centerline();
                    lanelet::ArcCoordinates to_cord = get_ArcCoordinate(centerline_,pose_tmp);                                
                    auto near_idx =  getClosestWaypoint(true,centerline_, pose_tmp);
                    auto near_point = centerline_[near_idx];                                            
                    if (fabs(to_cord.distance) >point_projection_ignore_threshold){                        
                        continue;
                    }else{
                    pose_tmp.position.x = near_point.x();
                    pose_tmp.position.y = near_point.y();
                    wp_tmp.x_pose = near_point.x(); 
                    wp_tmp.y_pose = near_point.y(); 
                    }
        }
        // Cost assignment
        if(v2x_data.States[i].item_type == 3){  
            // set up for booster 
            // Minimum cost of waypoint is 2 so boost has 1
            wp_tmp.cost = 1;
        }else{
            wp_tmp.cost = int(standarded_score[i]);    
        }
        // Last step of for loop   ==> add tmp position to waypoints and waypoints_pose
        wp_tmp.id = i;
        // ROS_INFO("wp_push id = %d, x = %f, y = %f", wp_tmp.id, wp_tmp.x_pose, wp_tmp.y_pose);        
        waypoints.push_back(wp_tmp);
        waypoints_pose.push_back(pose_tmp);    

  }
    // sort waypoints with respect to raceline
    for(int step= 0; step < waypoints.size(); step++){
        for (int k=0; k < waypoints.size()-step-1; k++){
            if(!is_forward(waypoints[k],waypoints[k+1])){                
                planner::Waypoint temp(waypoints[k].x_pose,waypoints[k].y_pose,waypoints[k].cost); 
                temp.id = waypoints[k].id;                                
                waypoints[k] = waypoints[k+1];
                waypoints[k+1] = temp;
            }
        }
    }
    
    

    waypoints_pose.clear();
    // re-idfication waypoints 
    for(int i=0; i < waypoints.size(); i++){
        waypoints[i].id = i;
        ROS_INFO("id = %d, x = %f, y = %f", waypoints[i].id,waypoints[i].x_pose,waypoints[i].y_pose);
        geometry_msgs::Pose pose_tmp;
        pose_tmp.position.x = waypoints[i].x_pose;
        pose_tmp.position.y = waypoints[i].y_pose;
        waypoints_pose.push_back(pose_tmp);        
    }
    waypoint_max_id = waypoints.size()-1;

    ///  add neighboring points
    for(int i=0; i< waypoints.size(); i++){
        planner::Waypoint waypoint_tmp = planner::Waypoint(waypoints[i].x_pose, waypoints[i].y_pose, neutral_cost);
        if(waypoints[i].cost <= neutral_cost){ // negative score -> good item
            std::vector<Waypoint> avoidance_wps = AddWaypoint(waypoint_tmp,neutral_cost+1);   
            if(avoidance_wps.size() > 0){
                for(int j=0; j < avoidance_wps.size(); j++){
                        avoidance_wps[j].id = waypoints[i].id; 
                    waypoints.push_back(avoidance_wps[j]);
                    geometry_msgs::Pose tmp_pose; 
                    tmp_pose.position.x = avoidance_wps[j].x_pose;
                    tmp_pose.position.y = avoidance_wps[j].y_pose;
                    waypoints_pose.push_back(tmp_pose);
                    }
            }
        }else if(waypoints[i].cost > neutral_cost) // Positive score -> bad item
        {
            std::vector<Waypoint> avoidance_wps = AddWaypoint(waypoint_tmp,neutral_cost-1);                            
            if(avoidance_wps.size() > 0){
                for(int j=0; j < avoidance_wps.size(); j++){
                        avoidance_wps[j].id = waypoints[i].id; 
                    waypoints.push_back(avoidance_wps[j]);
                    geometry_msgs::Pose tmp_pose; 
                    tmp_pose.position.x = avoidance_wps[j].x_pose;
                    tmp_pose.position.y = avoidance_wps[j].y_pose;
                    waypoints_pose.push_back(tmp_pose);
                }
            }
        }
    }
    ROS_INFO("Completing V2X mission Encoding");
}

void RacingLinePlanner::load_map_for_driving(){  
  ROS_INFO("Driving map loading");
  lanelet::ErrorMessages errors;  
    lanelet::GPSPoint originGps{origin_lat, origin_lon, 0.};    
 projector = new lanelet::projection::UtmProjector(lanelet::Origin{originGps});     
  map_for_driving = load(osm_file_name_for_driving, "osm_handler",*projector,&errors);
  assert(errors.empty()); 
  ROS_INFO("Driving map loaded succesfully");
}

void RacingLinePlanner::load_map(){  
  ROS_INFO("map loading");
  lanelet::ErrorMessages errors;  
    lanelet::GPSPoint originGps{origin_lat, origin_lon, 0.};    
 projector = new lanelet::projection::UtmProjector(lanelet::Origin{originGps});     
  map = load(osm_file_name, "osm_handler",*projector,&errors);
  assert(errors.empty()); 
  ROS_INFO("map loaded succesfully");
}

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

