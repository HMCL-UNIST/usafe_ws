
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


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>
#include <ros/ros.h>
#include <chrono>

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "map_loader.h"
// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


// A_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// C_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// Q_curv << 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01;
// R_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// P_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;




MapLoader::MapLoader(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p, const ros::NodeHandle& nh_local_path) :  
  nh_(nh), nh_p_(nh_p), nh_local_path_(nh_local_path),cur_filter(A_curv,B_curv,C_curv,Q_curv,R_curv,P_curv)  
{
  // using namespace lanelet;
  left_change_signal = false;
  right_change_signal = false;
  lane_change_state = LaneChangeState::Follow;
  map_bin_pub = nh_.advertise<autoware_lanelet2_msgs::MapBin>("/lanelet_map_bin", 1, true);
  
  map_loaded = false;
  way_pub = nh_.advertise<hmcl_msgs::LaneArray>("/global_traj", 2, true);
  local_traj_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 2, true);
  g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);  
  autoware_lane_pub = nh_.advertise<autoware_msgs::Lane>("/local_traj_auto", 2, true);

  debug_pub = nh_.advertise<geometry_msgs::PoseStamped>("/maploader_debug", 2, true);

  lir_pub= nh_.advertise<hmcl_msgs::LaneArray>("/lane_in_range",2,true);
  
  max_dist=150;
  
  cur_pose.position.x=-77.5211;
  cur_pose.position.y=2.9457;

  pose_init = true; 
  goal_available = true;
  // pose_sub = nh_.subscribe("/current_pose",1,&MapLoader::poseCallback,this);
  // odom_sub = nh_.subscribe("/carla/hero/odometry",100, &MapLoader::llaCallback,this);
  // goal_sub = nh_.subscribe("move_base_simple/goal", 1, &MapLoader::callbackGetGoalPose, this);
  // vehicle_status_sub = nh_.subscribe("/vehicle_status", 1, &MapLoader::callbackVehicleStatus, this);
  // lanechange_left_sub  = nh_.subscribe("/left_lanechange",2,&MapLoader::leftLancechangeCallback,this);
  // lanechange_right_sub = nh_.subscribe("/right_lanechange",2,&MapLoader::rightLancechangeCallback,this);
  // mobileye_sub = nh_.subscribe("/Mobileye_Info",2,&MapLoader::mobileyeCallback,this);

  nh_p_.param<std::string>("osm_file_name", osm_file_name, "Town01.osm");
  nh_p_.getParam("osm_file_name", osm_file_name);
  nh_p_.param<double>("test_direction", test_direction, 1.0);
  nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
  nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
  nh_p_.param<double>("map_origin_att", origin_att, 0.0);
  nh_p_.param<bool>("visualize_path", visualize_path, true);
  nh_p_.param<double>("map_road_resolution", map_road_resolution, 1.0);
  nh_p_.param<float>("local_path_length", local_path_length, 20.0);
  nh_p_.param<float>("weight_decay_rate", weight_decay_rate, 0.95);
  nh_p_.param<bool>("continuious_global_replan", continuious_global_replan, false);

  nh_p_.param<double>("min_local_path_length", min_local_path_length, 5.0);
  nh_p_.param<double>("max_local_path_length", max_local_path_length, 30.0);
  nh_p_.param<double>("local_path_scale", local_path_scale, 1.0);

  nh_p_.param<double>("lane_change_in_sec", lane_change_in_sec, 2.0);
  nh_p_.param<double>("lanechange_fsm_period", lanechange_fsm_period, 0.1);

  if(visualize_path){    
    g_traj_lanelet_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_lanelets_viz", 1, true);
    g_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_viz", 1, true);
    l_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1, true);
    lir_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lir_viz",1,true);  
    viz_timer = nh_.createTimer(ros::Duration(0.1), &MapLoader::viz_pub,this);    
  }
  
  global_traj_available = true;    
  load_map();
  bool map_fix;
  nh_p_.param<bool>("map_fix", map_fix, true);
  if(map_fix){
    fix_and_save_osm();    
  }

  lanelet::traffic_rules::TrafficRulesPtr trafficRules =
  lanelet::traffic_rules::TrafficRulesFactory::create(lanelet::Locations::Germany, lanelet::Participants::Vehicle);
  routingGraph = lanelet::routing::RoutingGraph::build(*map, *trafficRules);  
  
  construct_lanelets_with_viz();
  compute_global_path();
  if(global_lane_array.lanes.size() == 0){
    ROS_INFO("Routing not occured");
  }
  if(road_lanelets_const.size() == 0){
    ROS_INFO("No road lanelets");
  }
  else{
    ROS_INFO("road lanelets are %d",road_lanelets_const.size());
  }
  // lane_in_range();
  // wp_inArea();
  rp_.setMap(map);   
}


MapLoader::~MapLoader()
{}

void MapLoader::global_traj_handler(const ros::TimerEvent& time){
  if(goal_available){
    compute_global_path();
  }  

  if(global_traj_available){
    way_pub.publish(global_lane_array);  
  }  

}

void MapLoader::compute_global_path(){
  pose_a.position.x=-77.5211;
  pose_a.position.y=2.9457;
  // pose_b.position.x=-168.8611;
  // pose_b.position.y=64.2857;
  pose_b.position.x=-194.1411;
  pose_b.position.y=70.8257;
  global_lane_array.lanes.clear();  
  if(pose_init && road_lanelets_const.size() > 0){
      int start_closest_lane_idx = get_closest_lanelet(road_lanelets_const,pose_a);      
      int goal_closest_lane_idx = get_closest_lanelet(road_lanelets_const,pose_b);
      // lanelet::Optional<lanelet::routing::LaneletPath> route = routingGraph->shortestPath(road_lanelets[start_closest_lane_idx], road_lanelets[goal_closest_lane_idx], 1);
      lanelet::Optional<lanelet::routing::Route> route = routingGraph->getRoute(road_lanelets_const[start_closest_lane_idx], road_lanelets_const[goal_closest_lane_idx], 0);
      if(!route){
        ROS_WARN("[MAP_LOADER] = Route is not found");      
        return;
      }
      lanelet::routing::LaneletPath local_path = route->shortestPath();
      routingGraph->checkValidity();      
      // ROS_INFO("shortest path_size = %d", local_path.size());
        if(local_path.empty()){
          ROS_WARN("[MAP_LOADER] = Path is not found");        
        }
        else{
          // Create base trajectory           
          global_lane_array.header.frame_id = "map";
          global_lane_array.header.stamp = ros::Time::now();          
          
          ///////////////////////// Encode lanelets  /////////////////////////////////////////                        
          int _lane_idx = 0;

          //Check if the lane change requires from the last lanelent conversion
          int last_lane_change_lanelet_idx = local_path.size()-2;          
          if (last_lane_change_lanelet_idx < 0)
              {last_lane_change_lanelet_idx = 0;}
          else{
             while(last_lane_change_lanelet_idx >=0){
            bool is_follows = lanelet::geometry::follows(local_path[last_lane_change_lanelet_idx],local_path[last_lane_change_lanelet_idx+1]);                  
            std::vector<lanelet::routing::LaneletRelation> before_last_followingrelations_ = route->followingRelations(local_path[last_lane_change_lanelet_idx]);            
              if(!is_follows){  
                last_lane_change_lanelet_idx--;
              }else{
                last_lane_change_lanelet_idx++;
                break;
               }
             }
          }
          
          for (int i =0; i < local_path.size() ; ++i ){                
              hmcl_msgs::Lane ll_;          
              ll_.header = global_lane_array.header;
              ll_.lane_id = local_path[i].id();              
              double speed_limit = local_path[i].attributeOr("speed_limit",-1.0);                
              ll_.speed_limit = speed_limit;
              
              // check the lane change flag      
              if(i <local_path.size()-1){
                  bool is_follows = lanelet::geometry::follows(local_path[i],local_path[i+1]);
                  if(!is_follows){                    
                    ll_.lane_change_flag = true;
                  }
              }              
              
              // std::vector<lanelet::routing::LaneletRelation> followingrelations_ = route->followingRelations(local_path[i]);
              // ROS_INFO("lane idx = %d, following_size = %d", i, followingrelations_.size());
              // if( (followingrelations_.size()==0) && (i < local_path.size()-1)){ll_.lane_change_flag = true;}
              // else{ll_.lane_change_flag = false;}  
                           
              ///////////////////////// Encode waypoints  /////////////////////////////////////////              
              auto lstring = local_path[i].centerline();   
              double yaw_tmp;               
              int waypoint_idx_init = 0;
              int waypoint_idx_finish = lstring.size();
              // initial lanelet , add current position as the waypoint
              
              if(i==_lane_idx){
                waypoint_idx_init = getClosestWaypoint(true,lstring,cur_pose);                                                 
                if(i==0){
                    hmcl_msgs::Waypoint wp_;  
                    wp_.lane_id = _lane_idx;
                    wp_.pose.pose.position.x = cur_pose.position.x;
                    wp_.pose.pose.position.y = cur_pose.position.y;
                    wp_.pose.pose.position.z = cur_pose.position.z;
                    wp_.pose.pose.orientation.x = cur_pose.orientation.x;
                    wp_.pose.pose.orientation.y = cur_pose.orientation.y;
                    wp_.pose.pose.orientation.z = cur_pose.orientation.z;
                    wp_.pose.pose.orientation.w = cur_pose.orientation.w;
                    wp_.twist.twist.linear.x = ll_.speed_limit;
                    ll_.waypoints.push_back(wp_);
                }                
                if(ll_.lane_change_flag){_lane_idx++;}               
              }
              // terminal lanelet , add terminal position as the waypoint
              if(i >= last_lane_change_lanelet_idx){
                waypoint_idx_finish = getClosestWaypoint(false,lstring,pose_b);                             
              }

              for (int j = waypoint_idx_init; j < waypoint_idx_finish; j++ ){
                lanelet::ConstPoint3d p1Const = lstring[j]; 
                // ROS_INFO("x = %f, y = %f, z = %f", p1Const.x(),p1Const.y(),p1Const.z());
                hmcl_msgs::Waypoint wp_;                                    
                wp_.lane_id = ll_.lane_id;
                wp_.pose.pose.position.x = p1Const.x();
                wp_.pose.pose.position.y = p1Const.y();
                wp_.pose.pose.position.z = p1Const.z();                
                
                // point within the lanelet, Last point will have the same yaw as the previous waypoint
                if(j < lstring.size()-1){      
                  yaw_tmp = get_yaw(lstring[j], lstring[j+1]);                                    
                }else{
                  yaw_tmp = get_yaw(lstring[j-1], lstring[j]);
                }

                tf2::Quaternion q;
                q.setRPY(0, 0, yaw_tmp);
                q=q.normalize();
                wp_.pose.pose.orientation.x = q[0];
                wp_.pose.pose.orientation.y = q[1];
                wp_.pose.pose.orientation.z = q[2];
                wp_.pose.pose.orientation.w = q[3];
                wp_.twist.twist.linear.x = ll_.speed_limit;
                ll_.waypoints.push_back(wp_);
              }
               // terminal lanelet , add terminal position as the waypoint
              if(i == local_path.size()-1){                
                hmcl_msgs::Waypoint wp_;  
                wp_.lane_id = _lane_idx;
                wp_.pose.pose.position.x = pose_b.position.x;
                wp_.pose.pose.position.y = pose_b.position.y;
                wp_.pose.pose.position.z = pose_b.position.z;
                wp_.pose.pose.orientation.x = pose_b.orientation.x;
                wp_.pose.pose.orientation.y = pose_b.orientation.y;
                wp_.pose.pose.orientation.z = pose_b.orientation.z;
                wp_.pose.pose.orientation.w = pose_b.orientation.w;
                wp_.twist.twist.linear.x = ll_.speed_limit;
                ll_.waypoints.push_back(wp_);
              }
              


              ///////////////////////// Encode trafficlights  /////////////////////////////////////////              
              auto trafficLightRegelems = local_path[i].regulatoryElementsAs<lanelet::TrafficLight>();
              if(trafficLightRegelems.size()>0){
                //////////// Encode (multiple) traffics light in a single lanelet
                for(int i=0; i < trafficLightRegelems.size(); i++){
                  auto tlRegelem = trafficLightRegelems[i];
                  lanelet::ConstLineStringOrPolygon3d thelight = tlRegelem->trafficLights().front();
                  hmcl_msgs::Trafficlight tl_;                  
                  auto thelight_ls = thelight.lineString();     
                  if(thelight_ls){
                    tl_.pose.x = (thelight_ls->front().x()+thelight_ls->back().x())/2.0;
                    tl_.pose.y = (thelight_ls->front().y()+thelight_ls->back().y())/2.0;
                    tl_.pose.z = (thelight_ls->front().z()+thelight_ls->back().z())/2.0;                    
                  }             
                  auto stopline_ = tlRegelem->stopLine();
                  if (stopline_){
                  tl_.valid_stop_line = true;
                  tl_.stop_line.x = (stopline_->front().x()+stopline_->back().x())/2.0;
                  tl_.stop_line.y = (stopline_->front().y()+stopline_->back().y())/2.0;
                  tl_.stop_line.z = (stopline_->front().z()+stopline_->back().z())/2.0;                         
                  }else{
                    tl_.valid_stop_line = false;                      
                    ROS_WARN("Stop line is not defined .... !!!");
                  } 
                  ll_.trafficlights.push_back(tl_);
                }
              }              
              global_lane_array.lanes.push_back(ll_);

                
            }   
          global_traj_available = true;
          // way_pub.publish(global_lane_array);          
          global_lane_array_for_local = global_lane_array;

          wp_inArea();

          if(visualize_path){
              // Construct Traj_lanelet_marker 
              traj_lanelet_marker_array.markers.clear();            
              std::vector<lanelet::ConstLanelet> traj_lanelets;
              for(int i=0; i< local_path.size();i++){traj_lanelets.push_back(local_path[i]);}                  
                      std_msgs::ColorRGBA traj_marker_color;
                      setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.5);                        
                    insertMarkerArray(&traj_lanelet_marker_array, trajectory_draw(
                    traj_lanelets, traj_marker_color));
                      std_msgs::ColorRGBA in_cross_color;
                      setColor(&in_cross_color, 1.0, 0.0, 0.0, 0.5);

              // Construct Traj_marker               
              traj_marker_array.markers.clear();
              for(int i=0 ; i< global_lane_array.lanes.size(); i++){              
                for( int j= 0 ; j <global_lane_array.lanes[i].waypoints.size() ; j++){
                      visualization_msgs::Marker marker_tmp;
                      marker_tmp.header = global_lane_array.header;
                      marker_tmp.id = i*1000+j;
                      marker_tmp.ns = "gtraj";
                      marker_tmp.type = visualization_msgs::Marker::ARROW;
                      marker_tmp.action = visualization_msgs::Marker::ADD;                  
                      marker_tmp.pose.position.x = global_lane_array.lanes[i].waypoints[j].pose.pose.position.x;
                      marker_tmp.pose.position.y = global_lane_array.lanes[i].waypoints[j].pose.pose.position.y;
                      marker_tmp.pose.position.z = global_lane_array.lanes[i].waypoints[j].pose.pose.position.z;
                      marker_tmp.pose.orientation.x = global_lane_array.lanes[i].waypoints[j].pose.pose.orientation.x;
                      marker_tmp.pose.orientation.y = global_lane_array.lanes[i].waypoints[j].pose.pose.orientation.y;
                      marker_tmp.pose.orientation.z = global_lane_array.lanes[i].waypoints[j].pose.pose.orientation.z;
                      marker_tmp.pose.orientation.w = global_lane_array.lanes[i].waypoints[j].pose.pose.orientation.w;
                      if(global_lane_array.lanes[i].waypoints[j].Crosswalk){
                        marker_tmp.color = in_cross_color;
                      }
                      else{
                      marker_tmp.color = traj_marker_color;
                      }
                      marker_tmp.lifetime = ros::Duration(0.1);
                      marker_tmp.scale.x = 0.7;
                      marker_tmp.scale.y = 0.4;
                      marker_tmp.scale.z = 0.1;                  
                      traj_marker_array.markers.push_back(marker_tmp);
                    }
              }
            
            }
        }
  }
  else{
    ROS_WARN("[MAP_LOADER] = Current pose is not initialized or map is not loaded");
  }   

}

unsigned int MapLoader::getClosestWaypoint(bool is_start, const lanelet::ConstLineString3d &lstring, geometry_msgs::Pose& point_){
  //input is usually the center line 
  int closest_idx=lstring.size()-1;  
  double min_dist_ = std::numeric_limits<double>::max();  
  lanelet::ConstPoint3d end_pConst = lstring[lstring.size()-1]; 
    if (!is_start){
      closest_idx=0;  
      end_pConst = lstring[0]; 
    }
    double dist_from_current_to_end= sqrt(pow((end_pConst.x()-point_.position.x),2) + pow((end_pConst.y()-point_.position.y),2));      
    
    for (int j = 0; j < lstring.size(); j++ ){
      
      lanelet::ConstPoint3d pConst = lstring[j]; 
      
      double dist_= sqrt(pow(pConst.x()-point_.position.x,2) + pow(pConst.y()-point_.position.y,2));     
      double dist_from_tmp_to_end= sqrt(pow(pConst.x()-end_pConst.x(),2) + pow(pConst.y()-end_pConst.y(),2));     
      
      if( (min_dist_ >= dist_)&& (dist_from_tmp_to_end <= dist_from_current_to_end)){
          closest_idx = j;
          min_dist_ =  dist_;        
        }  
      
    }
  return closest_idx;
}

void MapLoader::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){  
  if(!pose_init){
    pose_init = true;
  }
  cur_pose = msg->pose;
  pose_x = msg->pose.position.x;
  pose_y = msg->pose.position.y;
  pose_z = msg->pose.position.z;
}
void MapLoader::llaCallback(const nav_msgs::OdometryConstPtr& msg){ 
  odom_x = msg->pose.pose.position.x;
  odom_y = msg->pose.pose.position.y;
  odom_z = msg->pose.pose.position.z;
}

void MapLoader::lane_in_range(){
  hmcl_msgs::LaneArray tmp_array;
  hmcl_msgs::LaneArray lir_array;
  tmp_array = global_lane_array;
  int cl_lane_idx, cl_pt_idx, in_lane_idx, in_pt_idx;

  lir_array.lanes.clear();

  if(lir_array.lanes.empty()){
    lir_available = false;
  }

  in_lane_idx = 0;

  findnearest_lane_and_point_idx(tmp_array, cur_pose, cl_lane_idx, cl_pt_idx);
  if(cl_lane_idx < in_lane_idx + 2){
    in_lane_idx =  cl_lane_idx;
    in_pt_idx = cl_pt_idx;
  }

  if(in_lane_idx>0){
    for(int i=0; i<in_lane_idx; i++){
      tmp_array.lanes.erase(tmp_array.lanes.begin()+i);
    }
  }
  for(int i=0; i<in_pt_idx; i++){
    tmp_array.lanes[in_lane_idx].waypoints.erase(tmp_array.lanes[in_lane_idx].waypoints.begin()+i);
  }

  bool add_stop = true;
  int lane_idx, pt_idx;
  lane_idx = in_lane_idx;
  pt_idx =  in_pt_idx;
  while(add_stop){
    hmcl_msgs::Lane lir_lane;
    while(calculate_distance(cur_pose,tmp_array.lanes[lane_idx].waypoints[pt_idx],max_dist)){
      if(pt_idx<tmp_array.lanes[lane_idx].waypoints.size()){
        hmcl_msgs::Waypoint wp;
        wp = tmp_array.lanes[lane_idx].waypoints[pt_idx];
        lir_lane.waypoints.push_back(wp);
        pt_idx++;
      }
      else{
        lane_idx++;
        pt_idx=0;
      }
      if(tmp_array.lanes[lane_idx].lane_change_flag){
        break;
      }
    }
    lir_array.lanes.push_back(lir_lane);
    if(calculate_distance(cur_pose,tmp_array.lanes[lane_idx].waypoints[pt_idx],max_dist)){
      hmcl_msgs::Lane lir_lane;
      int i=0;
      while(add_stop){
        if(calculate_distance(cur_pose,tmp_array.lanes[lane_idx+1].waypoints[i],max_dist)){
          hmcl_msgs::Waypoint wp;
          wp = tmp_array.lanes[lane_idx+1].waypoints[i];
          lir_lane.waypoints.push_back(wp);
          i++;
        }
        else{
        add_stop=false;
        lir_array.lanes.push_back(lir_lane);
        }
      }
    }
  }
  if(lir_array.lanes.size()>0)
  {
    lir_available = true;
  }
}

void MapLoader::viz_lir(hmcl_msgs::LaneArray &lanes){
  std_msgs::ColorRGBA lir_marker_color;
  setColor(&lir_marker_color, 1.0, 0.0, 0.0, 0.5);
  lir_marker_array.markers.clear();
  if(lir_available){
    for(int i=0; i<lanes.lanes.size(); i++){
      for(int j=0; j<lanes.lanes[i].waypoints.size(); j++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
        marker_tmp.id = 10000+i;
        marker_tmp.ns = "ltraj";
        marker_tmp.type = visualization_msgs::Marker::ARROW;
        marker_tmp.action = visualization_msgs::Marker::ADD;                  
        marker_tmp.pose.position.x = lanes.lanes[i].waypoints[j].pose.pose.position.x;
        marker_tmp.pose.position.y = lanes.lanes[i].waypoints[j].pose.pose.position.y;
        marker_tmp.pose.position.z = lanes.lanes[i].waypoints[j].pose.pose.position.z;
        marker_tmp.pose.orientation.x = lanes.lanes[i].waypoints[j].pose.pose.orientation.x;
        marker_tmp.pose.orientation.y = lanes.lanes[i].waypoints[j].pose.pose.orientation.y;
        marker_tmp.pose.orientation.z = lanes.lanes[i].waypoints[j].pose.pose.orientation.z;
        marker_tmp.pose.orientation.w = lanes.lanes[i].waypoints[j].pose.pose.orientation.w;
        marker_tmp.color = lir_marker_color;
        marker_tmp.lifetime = ros::Duration(0.1);
        marker_tmp.scale.x = 1.2;
        marker_tmp.scale.y = 0.6;
        marker_tmp.scale.z = 0.1;                  
        lir_marker_array.markers.push_back(marker_tmp);
      }
    }
  }
}
void MapLoader::lir_handler(const ros::TimerEvent& time){
  if(global_traj_available){
    lane_in_range();
    wp_inArea();
    if(lir_array.lanes.size()>0){
      std::cout<<"lir ready"<<std::endl;
      lir_pub.publish(lir_array);
    }
    else{
      std::cout<<"empty lir"<< std::endl;
    }
  }
}

void MapLoader::wp_inArea(){
  ROS_INFO("wp is");
  if(global_traj_available){
    ROS_INFO("Hi");
    ROS_INFO("%d area", areas.size());
    for(int i=0; i<global_lane_array.lanes.size(); i++){
      for(int j=0; j<global_lane_array.lanes[i].waypoints.size(); j++){
        for(int k=0; k<areas.size(); k++){
          hmcl_msgs::Waypoint wp=global_lane_array.lanes[i].waypoints[j];
          lanelet::Area area = areas[k];
          if(lanelet::geometry::inside(area,lanelet::BasicPoint2d(wp.pose.pose.position.x,wp.pose.pose.position.y))){
            ROS_INFO("%d lane %d point is in Area",i,j);
            global_lane_array.lanes[i].waypoints[j].Crosswalk = true;
          };
        }
      }
    }
  }  
}

void MapLoader::ego_in(){
  if(lir_available){
    hmcl_msgs::LaneArray tmp_array;
    int lane_idx, point_idx;
    findnearest_lane_and_point_idx(lir_array,cur_pose,lane_idx, point_idx);
    tmp_array = lir_array;
    for(int i=0; i<point_idx; i++){
      tmp_array.lanes[lane_idx].waypoints.erase(tmp_array.lanes[lane_idx].waypoints.begin()+i);
    }
  }
}

bool MapLoader::calculate_distance(geometry_msgs::Pose &point, hmcl_msgs::Waypoint &wp, double &dist){
  double dist_;
  dist_= sqrt(pow((wp.pose.pose.position.x-point.position.x),2) + pow((wp.pose.pose.position.y-point.position.y),2));
  if (dist_< dist){
    return true;
  }
  else{
    return false;
  }
}


void MapLoader::construct_lanelets_with_viz(){
  ROS_INFO("constructing lanelets viz ..... ");
  lanelet::Lanelets all_lanelets = laneletLayer(map); 
  lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(map);
  road_lanelets = roadLanelets(all_lanelets);  
  road_lanelets_const = roadLaneletsConst(all_laneletsConst);
  areas = AreaLayer(map);

  std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
  std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
  std_msgs::ColorRGBA cl_road, cl_area, cl_cross, cl_ll_borders, cl_tl_stoplines, cl_ss_stoplines, cl_trafficlights;
  setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
  setColor(&cl_area, 0.0, 1.0, 0.0, 0.5);
  setColor(&cl_cross, 0.2, 0.7, 0.2, 0.3);
  setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);
  setColor(&cl_tl_stoplines, 1.0, 0.5, 0.0, 0.5);
  setColor(&cl_ss_stoplines, 1.0, 0.0, 0.0, 0.5);
  setColor(&cl_trafficlights, 0.0, 0.0, 1.0, 0.8);

  insertMarkerArray(&map_marker_array, areaMarkerArray(areas,cl_area));
  insertMarkerArray(&map_marker_array, laneletsBoundaryAsMarkerArray(
    road_lanelets, cl_ll_borders));
  insertMarkerArray(&map_marker_array, trafficLightsAsTriangleMarkerArray(
    tl_reg_elems, cl_trafficlights));
  
  insertMarkerArray(&map_marker_array, lineStringsAsMarkerArray(
    tl_stop_lines, "traffic_light_stop_lines", cl_tl_stoplines));

  ROS_INFO("Visualizing lanelet2 map with %lu lanelets, %lu stop lines",
    all_lanelets.size(), tl_stop_lines.size());
 
}



 


void MapLoader::viz_pub(const ros::TimerEvent& time){  
    g_map_pub.publish(map_marker_array);
    g_traj_lanelet_viz_pub.publish(traj_lanelet_marker_array);
    g_traj_viz_pub.publish(traj_marker_array);
    lir_viz_pub.publish(lir_marker_array);
    
}

void MapLoader::load_map(){
  map_loaded  = true;
  ROS_INFO("map loading");
  lanelet::ErrorMessages errors;  
  lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));    
  map = load(osm_file_name, "osm_handler",projector,&errors);
  assert(errors.empty()); 
  ROS_INFO("map loaded succesfully");
}

double MapLoader::get_yaw(const lanelet::ConstPoint3d & _from, const lanelet::ConstPoint3d &_to ){
    double _angle = std::atan2(_to.y() - _from.y(), _to.x() - _from.x());
    
    while(_angle > M_PI){
      _angle = _angle - 2*M_PI;
    }
    while(_angle < M_PI){
      _angle = _angle + 2*M_PI;
    }
  return _angle;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapLoader::fix_and_save_osm(){  
  
   for (auto li = map->laneletLayer.begin(); li != map->laneletLayer.end(); li++)
  {      // li = lanelet::Lanelet       
        if (li->hasAttribute(lanelet::AttributeName::Subtype))
        {
          lanelet::Attribute attr = li->attribute(lanelet::AttributeName::Subtype);
          if (attr.value() == lanelet::AttributeValueString::Road)
          {           
            auto iter_l =  li->leftBound().begin();                      
            double dist_;            
            int count = 0;            
            while(count < 100000){              
                auto iter_l =  li->leftBound().begin();  
                lanelet::Point3d p_l = *next(li->leftBound().begin(),count);
                lanelet::Point3d p_end = *next(li->leftBound().begin(),li->leftBound().size()-1);
                double dist_to_end_point =  lanelet::geometry::distance(p_l,p_end);     
                if( dist_to_end_point < 2 )                  
                    {break;}
                 // ->leftBound()[idx];                    
                lanelet::Point3d p_left  = *next(li->leftBound().begin(),count);
                lanelet::Point3d p_right = *next(li->leftBound().begin(),count+1);                   
                dist_ =  lanelet::geometry::distance(p_left,p_right);                  
                if(dist_ > map_road_resolution*2){                  
                  // lanelet::Point3d new_pt = p_left;
                   double x = (p_left.x() + p_right.x())/2.0;                   
                    double y = (p_left.y() + p_right.y())/2.0;
                    double z = (p_left.z() + p_right.z())/2.0;
                    lanelet::Point3d new_pt{lanelet::utils::getId(), x,y,z};    
                    double local_x_l = p_left.attributeOr("local_x",0.0);                    
                    double local_x_r =  p_right.attributeOr("local_x",0.0);
                    double local_y_l = p_left.attributeOr("local_y",0.0);                    
                    double local_y_r =  p_right.attributeOr("local_y",0.0);
                    std::string mgrs_code = p_left.attributeOr("mgrs_code","MGRS");        
                    new_pt.attributes()["local_x"] = (local_x_l +local_x_r)/2.0;
                    new_pt.attributes()["local_y"] = (local_y_l +local_y_r)/2.0;                    
                    new_pt.attributes()["mgrs_code"] = mgrs_code;                    
                    map->add(new_pt);
                    iter_l = next(iter_l,count+1);
                    li->leftBound().insert(iter_l,new_pt);                                          
                }else{                  
                  count=count+1;
                  //  iter_l =next(iter_l,1);
                }
            }

            count = 0;
            auto iter_r =  li->rightBound().begin();   
            while(count < 100000){              
                auto iter_r =  li->rightBound().begin();  
                lanelet::Point3d p_l = *next(li->rightBound().begin(),count);
                lanelet::Point3d p_end = *next(li->rightBound().begin(),li->rightBound().size()-1);
                double dist_to_end_point =  lanelet::geometry::distance(p_l,p_end);     
                if( dist_to_end_point < 2 )                  
                    {break;}                                 
                lanelet::Point3d p_left  = *next(li->rightBound().begin(),count);
                lanelet::Point3d p_right = *next(li->rightBound().begin(),count+1);                   
                dist_ =  lanelet::geometry::distance(p_left,p_right);                  
                if(dist_ > map_road_resolution*2){                  
                  // lanelet::Point3d new_pt = p_left;
                   double x = (p_left.x() + p_right.x())/2.0;                   
                    double y = (p_left.y() + p_right.y())/2.0;
                    double z = (p_left.z() + p_right.z())/2.0;
                    lanelet::Point3d new_pt{lanelet::utils::getId(), x,y,z};    
                    double local_x_l = p_left.attributeOr("local_x",0.0);                    
                    double local_x_r =  p_right.attributeOr("local_x",0.0);
                    double local_y_l = p_left.attributeOr("local_y",0.0);                    
                    double local_y_r =  p_right.attributeOr("local_y",0.0);
                    std::string mgrs_code = p_left.attributeOr("mgrs_code","MGRS");        
                    new_pt.attributes()["local_x"] = (local_x_l +local_x_r)/2.0;
                    new_pt.attributes()["local_y"] = (local_y_l +local_y_r)/2.0;                    
                    new_pt.attributes()["mgrs_code"] = mgrs_code;                                       
                    map->add(new_pt);
                    iter_r = next(iter_r,count+1);
                    li->rightBound().insert(iter_r,new_pt);                                          
                }else{                  
                  count=count+1;                  
                } 
            } // For each lanelet
          }// subtype road       
        } // Subtype exist 
     
  }


  
  ROS_INFO("map save init ...");
  lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));  
  std::string delimiter = ".osm";
  std::string package_path = ros::package::getPath("map_loader");
  std::string token = osm_file_name.substr(0, osm_file_name.find(delimiter)); // token is "scott"
  std::string osm_file_name_fixed =  token + "_fix.osm";  
  write(osm_file_name_fixed, *map,projector);
  ROS_INFO("map save complete");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapLoader::viz_local_path(hmcl_msgs::Lane &lane_){
  
              // Construct Traj_lanelet_marker 
               std_msgs::ColorRGBA local_traj_marker_color;
                setColor(&local_traj_marker_color, 0.0, 0.0, 1.0, 0.5);    
              local_traj_marker_arrary.markers.clear();  
              for(int i=0; i< lane_.waypoints.size();i++){
                      visualization_msgs::Marker marker_tmp;
                      marker_tmp.header.stamp = ros::Time::now();
                      marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
                      marker_tmp.id = 10000+i;
                      marker_tmp.ns = "ltraj";
                      marker_tmp.type = visualization_msgs::Marker::ARROW;
                      marker_tmp.action = visualization_msgs::Marker::ADD;                  
                      marker_tmp.pose.position.x = lane_.waypoints[i].pose.pose.position.x;
                      marker_tmp.pose.position.y = lane_.waypoints[i].pose.pose.position.y;
                      marker_tmp.pose.position.z = lane_.waypoints[i].pose.pose.position.z;
                      marker_tmp.pose.orientation.x = lane_.waypoints[i].pose.pose.orientation.x;
                      marker_tmp.pose.orientation.y = lane_.waypoints[i].pose.pose.orientation.y;
                      marker_tmp.pose.orientation.z = lane_.waypoints[i].pose.pose.orientation.z;
                      marker_tmp.pose.orientation.w = lane_.waypoints[i].pose.pose.orientation.w;
                      marker_tmp.color = local_traj_marker_color;
                      marker_tmp.lifetime = ros::Duration(0.1);
                      marker_tmp.scale.x = 1.2;
                      marker_tmp.scale.y = 0.6;
                      marker_tmp.scale.z = 0.1;                  
                      local_traj_marker_arrary.markers.push_back(marker_tmp);
                      
                }                  
}

void MapLoader::findnearest_lane_and_point_idx(const hmcl_msgs::LaneArray &lanes, geometry_msgs::Pose& point_, int &closest_lane_idx, int &closest_point_idx)
{  //input is usually the center line
  closest_lane_idx = 0;
  closest_point_idx = 0;
  double min_dist_ = std::numeric_limits<double>::max();    
  for(int i=0; i < lanes.lanes.size(); i++){                
      for (int j = 0 ; j < lanes.lanes[i].waypoints.size(); j++){
      double dist_= sqrt(pow((lanes.lanes[i].waypoints[j].pose.pose.position.x-point_.position.x),2) + pow((lanes.lanes[i].waypoints[j].pose.pose.position.y-point_.position.y),2));      
      if(min_dist_ >= dist_){
          closest_lane_idx = i;
          closest_point_idx = j;
          min_dist_ =  dist_;        
        }  
    }
  }
 
  return;
}

PolyFit<double> MapLoader::polyfit(std::vector<double> x, std::vector<double> y){
  try 
  {
    
    // Create options for fitting
    PolyFit<double>::Options options;
    options.polyDeg = 3; 
    options.solver = PolyFit<double>::EIGEN_JACOBI_SVD; // SVD solver
    int mxpts = x.size()-2;
    // if(mxpts > 10){ 
    //   mxpts = 10;
    // }
    options.maxMPts = mxpts; // x.size(); // #Pts to use for fitting
    options.maxTrial = 500; // Max. nr. of trials
    options.tolerance = 0.01; // Distance tolerance for inlier    
    // Create fitting object
    PolyFit<double>f(x,y,options);    
    // Solve using RANSAC 
    f.solveRLS(); 
     
    // Output result    
    polyfit_error = false;
    return f;
  }
  catch (std::exception &e)
  {
     ROS_WARN("PolyFit Error");  
     polyfit_error = true;  
    poly_error = 1e10;
  }
}

int main (int argc, char** argv)
{
ros::init(argc, argv, "MapLoader");
ros::NodeHandle nh_, nh_local_path;
ros::NodeHandle nh_private("~");
MapLoader MapLoader_(nh_,nh_private,nh_local_path);

  ros::CallbackQueue callback_queue_nh, callback_queue_nh_local_path;
  nh_.setCallbackQueue(&callback_queue_nh);
  nh_local_path.setCallbackQueue(&callback_queue_nh_local_path);

   std::thread spinner_thread_nh([&callback_queue_nh]() {
    ros::SingleThreadedSpinner spinner_nh;
    spinner_nh.spin(&callback_queue_nh);
  });

  std::thread spinner_thread_nh_local_path([&callback_queue_nh_local_path]() {
    ros::SingleThreadedSpinner spinner_nh_local_path;
    spinner_nh_local_path.spin(&callback_queue_nh_local_path);
  });

  ros::spin();

  spinner_thread_nh.join();
  spinner_thread_nh_local_path.join();

}
