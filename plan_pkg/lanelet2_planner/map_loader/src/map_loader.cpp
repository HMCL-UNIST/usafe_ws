
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
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>
#include <ros/ros.h>
#include <chrono>

#include <GeographicLib/UTMUPS.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>

#include <lanelet2_core/geometry/LaneletMap.h>
#include <lanelet2_core/geometry/impl/Area.h>
#include "lanelet2_core/geometry/Area.h"
#include "lanelet2_core/geometry/BoundingBox.h"
#include "lanelet2_core/geometry/LaneletMap.h"
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
  getV2Xinfo = false;
  lane_change_state = LaneChangeState::Follow;
  map_bin_pub = nh_.advertise<autoware_lanelet2_msgs::MapBin>("/lanelet_map_bin", 1, true);
  
  map_loaded = false;
  way_pub = nh_.advertise<hmcl_msgs::LaneArray>("/global_traj", 2, true);
  local_traj_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 2, true);
  g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);  
  autoware_lane_pub = nh_.advertise<autoware_msgs::Lane>("/local_traj_auto", 2, true);

  debug_pub = nh_.advertise<geometry_msgs::PoseStamped>("/maploader_debug", 2, true);

  lir_pub= nh_.advertise<hmcl_msgs::LaneArray>("/lane_in_range",2,true);
  ped_cw_pub = nh_.advertise<std_msgs::Bool>("Ped_in_Crosswalk",2,true);  
  mission_pub= nh_.advertise<hmcl_msgs::MissionWaypoint>("/start_goal_pose",2,true);
  mission_pt_pub= nh_.advertise<visualization_msgs::Marker>("/mission_pt",2,true);
  mission_pts_pub= nh_.advertise<visualization_msgs::Marker>("/mission_pts",2,true);
  ped_pts_pub= nh_.advertise<visualization_msgs::MarkerArray>("/ped_pt",2,true);
  
  max_dist = 10000;
  
  pose_init = false; 
  goal_available = false;
  pose_sub = nh_.subscribe("/pose_estimate",1,&MapLoader::poseCallback,this);
  v2x_mission_sub = nh_.subscribe("/Mission1", 1, &MapLoader::v2xMissionCallback, this);
  ped_sub = nh_.subscribe("/tracking_pedestrian/objects",1, &MapLoader::PedCallback, this);
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

  global_traj_available = false;    
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

  g_traj_timer = nh_.createTimer(ros::Duration(0.5), &MapLoader::global_traj_handler,this);
  lir_timer = nh_.createTimer(ros::Duration(0.1),&MapLoader::lir_handler,this);
  ped_cw_timer = nh_.createTimer(ros::Duration(0.05),&MapLoader::ped_inCw_handler,this);
  rp_.setMap(map);   
}


MapLoader::~MapLoader()
{}

void MapLoader::global_traj_handler(const ros::TimerEvent& time){
  if(!goal_available){
    v2x_goal_nodes();
  }
  
  if(goal_available){
    compute_global_path();
  }  

  if(global_traj_available){
    way_pub.publish(global_lane_array);
    ROS_INFO("GLOBAL");
  }  

}

void MapLoader::compute_global_path(){
  global_lane_array.lanes.clear();
  for(int t=0; t<xyz.size()-1; t++){ 
    pose_a.position.x = xyz[t].first;
    pose_a.position.y = xyz[t].second;
    pose_b.position.x = xyz[t+1].first;
    pose_b.position.y = xyz[t+1].second;


  if(pose_init && road_lanelets_const.size() > 0){
      int start_closest_lane_idx = get_closest_lanelet(road_lanelets_const,pose_a);      
      int goal_closest_lane_idx = get_closest_lanelet(road_lanelets_const,pose_b);
      // lanelet::Optional<lanelet::routing::LaneletPath> route = routingGraph->shortestPath(road_lanelets[start_closest_lane_idx], road_lanelets[goal_closest_lane_idx], 1);
      route = routingGraph->getRoute(road_lanelets_const[start_closest_lane_idx], road_lanelets_const[goal_closest_lane_idx], 0);
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
                waypoint_idx_init = getClosestWaypoint(true,lstring,pose_a);                                                 
                // if(i==0){
                //     hmcl_msgs::Waypoint wp_;  
                //     wp_.lane_id = _lane_idx;
                //     wp_.pose.pose.position.x = pose_a.position.x;
                //     wp_.pose.pose.position.y = pose_a.position.y;
                //     wp_.pose.pose.position.z = pose_a.position.z;
                //     wp_.pose.pose.orientation.x = pose_a.orientation.x;
                //     wp_.pose.pose.orientation.y = pose_a.orientation.y;
                //     wp_.pose.pose.orientation.z = pose_a.orientation.z;
                //     wp_.pose.pose.orientation.w = pose_a.orientation.w;
                //     wp_.twist.twist.linear.x = ll_.speed_limit;
                //     ll_.waypoints.push_back(wp_);
                // }                
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
              // if(i == local_path.size()-1){                
              //   hmcl_msgs::Waypoint wp_;  
              //   wp_.lane_id = _lane_idx;
              //   wp_.pose.pose.position.x = pose_b.position.x;
              //   wp_.pose.pose.position.y = pose_b.position.y;
              //   wp_.pose.pose.position.z = pose_b.position.z;
              //   wp_.pose.pose.orientation.x = pose_b.orientation.x;
              //   wp_.pose.pose.orientation.y = pose_b.orientation.y;
              //   wp_.pose.pose.orientation.z = pose_b.orientation.z;
              //   wp_.pose.pose.orientation.w = pose_b.orientation.w;
              //   wp_.twist.twist.linear.x = ll_.speed_limit;
              //   ll_.waypoints.push_back(wp_);
              // }
              


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
            for (int i =0; i < global_lane_array.lanes.size(); i++){
                global_index.push_back(global_lane_array.lanes[i].lane_id);
                }


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
                      std_msgs::ColorRGBA in_cross_color, in_junc_color, in_sl_color;
                      setColor(&in_cross_color, 1.0, 0.0, 0.0, 0.5);
                      setColor(&in_junc_color, 0.0, 0.0, 1.0, 0.5);
                      setColor(&in_sl_color, 1.0, 1.0, 0.0, 0.5);

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
                      else if(global_lane_array.lanes[i].waypoints[j].Junction){
                        marker_tmp.color = in_junc_color;
                      }
                      else if(global_lane_array.lanes[i].waypoints[j].Stop_line){
                        marker_tmp.color = in_sl_color;
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
  
  

  pose_a.position.x = xyz[start_idx+1].first;
  pose_a.position.y = xyz[start_idx+1].second;
  pose_b.position.x = xyz[end_idx+1].first;
  pose_b.position.y = xyz[end_idx+1].second;

  int s_lane_idx, s_pt_idx;
  int g_lane_idx, g_pt_idx;
  int id;
  findnearest_lane_and_point_idx(global_lane_array, pose_a, s_lane_idx, s_pt_idx);
  id = global_lane_array.lanes[s_lane_idx].lane_id;
  mission_pt.start.z = id;
  findnearest_lane_and_point_idx(global_lane_array, pose_b, g_lane_idx, g_pt_idx);
  id = global_lane_array.lanes[g_lane_idx].lane_id;
  mission_pt.end.z = id;
  // ROS_INFO("start idx is %f", mission_pt.start.z);
  // ROS_INFO("end idx is %f", mission_pt.end.z);
  mission_pt.remain = xyz.size();

  for(int t=0; t<xyz.size()-1; t++){ 

    if (find_check){
      break;
    }

    pose_a.position.x = xyz[t].first;
    pose_a.position.y = xyz[t].second;
    findnearest_lane_and_point_idx(global_lane_array, pose_a, s_lane_idx, s_pt_idx);
    id = global_lane_array.lanes[s_lane_idx].lane_id;
    // ROS_INFO("id is : %d",id);
    
    id_array.push_back(id);
    if (t == xyz.size()-2){
      find_check =true;
      ROS_INFO("start idx is %f", mission_pt.start.z);
      ROS_INFO("end idx is %f", mission_pt.end.z);
    }
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

void MapLoader::poseCallback(const nav_msgs::OdometryConstPtr& msg){  
  if(!pose_init){
    pose_init = true;
  }
  cur_pose = msg->pose.pose;
  odom_x = msg->pose.pose.position.x;
  odom_y = msg->pose.pose.position.y;
  odom_z = msg->pose.pose.position.z;
}
void MapLoader::llaCallback(const nav_msgs::OdometryConstPtr& msg){ 
  odom_x = msg->pose.pose.position.x;
  odom_y = msg->pose.pose.position.y;
  odom_z = msg->pose.pose.position.z;
}

void MapLoader::PedCallback(const autoware_msgs::DetectedObjectArray &msg){
ped_array.objects.clear();
  // ROS_INFO("pedestrian");
  for(int i=0; i<msg.objects.size(); i++){
    if(msg.objects[i].label == "pedestrian"){
      // ROS_INFO("pedestrian");
      ped_array.objects.push_back(msg.objects[i]);
    }
  }
  if(ped_array.objects.size() > 0){
    ped_available = true;
    ped_state(ped_array);
  }
}

void MapLoader::lane_in_range(){
  hmcl_msgs::LaneArray tmp_array, tmp_array2;
  tmp_array = global_lane_array;
  int near_lane_idx, near_pt_idx;
  bool add_stop = false;

  findnearest_lane_and_point_idx(tmp_array, cur_pose, cl_lane_idx, cl_pt_idx);
  current_id = tmp_array.lanes[cl_lane_idx].lane_id;
  int signal_id = check_traffic_light(current_id); 

  // ROS_INFO("current lane is: %d", current_id);
  // ROS_INFO("previous lane is: %d", previous_id);


  if (previous_id == -1){
    previous_id = cl_lane_idx;
  }
  else if(abs(cl_lane_idx - previous_id) >3 ){
    return;
  } 

  lir_array.lanes.clear();
  tmp_array2.lanes.clear();

  for (int j=0; j<tmp_array.lanes.size(); j++){
    if (tmp_array.lanes[j].lane_id == current_id){
      cl_lane_idx = j;
      break;
    }
  }
  for (int k=0; k<6; k++){
    if (cl_lane_idx+k < tmp_array.lanes.size()){
      tmp_array2.lanes.push_back(tmp_array.lanes[cl_lane_idx+k]);    
      }
  }


  previous_id = cl_lane_idx;
  findnearest_lane_and_point_idx(tmp_array2, cur_pose, cl_lane_idx, cl_pt_idx);
  // lir_flag = true;
   

  for(int i=0; i<cl_pt_idx; i++){
    tmp_array2.lanes[cl_lane_idx].waypoints.erase(tmp_array2.lanes[cl_lane_idx].waypoints.begin());
  }

  for(int i=0; i<cl_lane_idx; i++){
    tmp_array2.lanes.erase(tmp_array2.lanes.begin());
  }


  // global 
  hmcl_msgs::Lane ll;
  ll.signal_id = signal_id;
  // hmcl_msgs::LaneArray findlanes;
  // lanelet::Lanelets find_lanes;
  // lanelet::Lanelets current_lane;
  // lanelet::Lanelets find_lane;


  double dist_cum = 0;
  int lane_id = current_id;
  bool b_lane_change = true;
  lanelet::ConstLineString3d target_ctl;
  lanelet::ConstLanelet target_lane;
  std::vector<lanelet::ConstLanelet> target_lanes;
  // std::vector<lanelet::ConstLanelet> lanes;
  ROS_INFO("Current node is %d", id_array.size());
  if (id_array.size()>=1){
    if (lane_id == id_array[1]){
      id_array.erase(id_array.begin());
      ROS_INFO("Mission node is in Current lane");
      mission_pt.remain = id_array.size();
    }
  }

  bool lc_flag = false;
  for(int i=0; i<tmp_array2.lanes.size(); i++){
    if (i == 0 && !tmp_array2.lanes[i].lane_change_flag){
      // ROS_INFO("NO CHANGE HERE");
      b_lane_change = false;
      geometry_msgs::Pose pose22; 
      pose22.position.x = tmp_array2.lanes[i].waypoints[1].pose.pose.position.x;
      pose22.position.y = tmp_array2.lanes[i].waypoints[1].pose.pose.position.y;
      cl_lane_idx = get_closest_lanelet(road_lanelets_const,pose22);  
      // findnearest_lane_and_point_idx(road_lanelets_const, tmp_array2.lanes[k].waypoints[1], cl_lane_idx, cl_pt_idx);
      // current_lane = road_lanelets_const[cl_lane_idx];

      auto left_next_lane = routingGraph->left(road_lanelets_const[cl_lane_idx]);                                              
      auto right_next_lane = routingGraph->right(road_lanelets_const[cl_lane_idx]);

      if(left_next_lane){
        // ROS_INFO("left lane found");  
        target_lane =left_next_lane.get(); 
        target_lanes.push_back(target_lane);
      }
      
      if(right_next_lane){
        // ROS_INFO("right lane found");  
        target_lane = right_next_lane.get(); 
        target_lanes.push_back(target_lane);
      }
    }
    // if (current_id == 12){
    //   ROS_INFO("waypoint_size is %f", tmp_array2.lanes[i].waypoints.size()-1);
    // }
    if (tmp_array2.lanes[i].waypoints.size() <= 1){
      continue;
    }

    for(int j=0; j<tmp_array2.lanes[i].waypoints.size()-1; j++){
      
      if(!tmp_array2.lanes[i].lane_change_flag){
        ll.lane_id = lane_id;
        if(lc_flag){
            lir_array.lanes.push_back(ll);
            ll.waypoints.clear();
            lc_flag = false;
        }
        if(calculate_distance_(tmp_array2.lanes[i].waypoints[j+1],tmp_array2.lanes[i].waypoints[j], max_dist, dist_cum)){
          ll.waypoints.push_back(tmp_array2.lanes[i].waypoints[j]);
        }
        else{
          add_stop = true;
          break;
        }
      }
      else{
        ll.lane_id = lane_id;
        if(calculate_distance_(tmp_array2.lanes[i].waypoints[j+1],tmp_array2.lanes[i].waypoints[j], max_dist, dist_cum)){
          // ROS_INFO("CHANGE HERE");
          ll.waypoints.push_back(tmp_array2.lanes[i].waypoints[j]);
          
          lc_flag = true;
          if (b_lane_change){
            ll.lane_change_flag = true;
          }
          else{
            ll.lane_change_flag = false;
          }

        }
        else{ 
          lir_array.lanes.push_back(ll);
          ll.waypoints.clear();
          add_stop = true;
          break;
        }
      }
    }
    if(add_stop){
      lir_array.lanes.push_back(ll);
      ll.waypoints.clear();
      break;
    }
  }
  
  if(ll.waypoints.size()>0){
    lir_array.lanes.push_back(ll);
  }

  ll.waypoints.clear();
  if(target_lanes.size()>0){
    for(int i = 0; i <target_lanes.size(); i++)
    {
      ll.lane_id = 1000;
      auto lstring = target_lanes[i].centerline();
      for (int j = 0; j < lstring.size(); j++ ){
        lanelet::ConstPoint3d p1Const = lstring[j]; 
        // ROS_INFO("x = %f, y = %f, z = %f", p1Const.x(),p1Const.y(),p1Const.z());
        hmcl_msgs::Waypoint wp_;                                    
        // wp_.lane_id = 1000;
        wp_.pose.pose.position.x = p1Const.x();
        wp_.pose.pose.position.y = p1Const.y();
        wp_.pose.pose.position.z = p1Const.z(); 
        ll.waypoints.push_back(wp_);
      }
    }
    lir_array.lanes.push_back(ll);
  }


  if(lir_array.lanes.size()>0){
    lir_available = true;
    viz_lir(lir_array);
  }
  else{
    lir_available = false;
  }

}

void MapLoader::viz_lir(hmcl_msgs::LaneArray &lanes){
  std_msgs::ColorRGBA lir_marker_color, lir_marker_even, junction_cl, crosswalk_cl, stopline_cl;
  setColor(&lir_marker_color, 0.0, 1.0, 1.0, 0.5);
  setColor(&lir_marker_even, 1.0, 0.0, 1.0, 0.5);
  setColor(&junction_cl, 0.0, 0.0, 1.0, 0.5);
  setColor(&crosswalk_cl, 1.0, 0.0, 0.0, 0.5);
  setColor(&stopline_cl, 1.0, 1.0, 0.0, 0.5);
  lir_marker_array.markers.clear();
  if(lir_available){
    for(int i=0; i<lanes.lanes.size(); i++){
      for(int j=0; j<lanes.lanes[i].waypoints.size(); j++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
        marker_tmp.id = 10000+i*1000+j;
        marker_tmp.ns = "lir";
        marker_tmp.type = visualization_msgs::Marker::ARROW;
        marker_tmp.action = visualization_msgs::Marker::ADD;                  
        marker_tmp.pose.position.x = lanes.lanes[i].waypoints[j].pose.pose.position.x;
        marker_tmp.pose.position.y = lanes.lanes[i].waypoints[j].pose.pose.position.y;
        marker_tmp.pose.position.z = lanes.lanes[i].waypoints[j].pose.pose.position.z;
        marker_tmp.pose.orientation.x = lanes.lanes[i].waypoints[j].pose.pose.orientation.x;
        marker_tmp.pose.orientation.y = lanes.lanes[i].waypoints[j].pose.pose.orientation.y;
        marker_tmp.pose.orientation.z = lanes.lanes[i].waypoints[j].pose.pose.orientation.z;
        marker_tmp.pose.orientation.w = lanes.lanes[i].waypoints[j].pose.pose.orientation.w;
        if(lanes.lanes[i].waypoints[j].Crosswalk){
          marker_tmp.color = crosswalk_cl;
        }
        else if(lanes.lanes[i].waypoints[j].Junction){
          marker_tmp.color = junction_cl;
        }
        else if(lanes.lanes[i].waypoints[j].Stop_line){
          marker_tmp.color = stopline_cl;
        }
        else if(i%2 == 0){
          marker_tmp.color = lir_marker_color;  
        }
        else if(i%2 == 1){
          marker_tmp.color = lir_marker_even;
        }
        marker_tmp.lifetime = ros::Duration(0.1);
        marker_tmp.scale.x = 1.2;
        marker_tmp.scale.y = 0.6;
        marker_tmp.scale.z = 0.1;                  
        lir_marker_array.markers.push_back(marker_tmp);
      }
    }
  }
}



int MapLoader::check_traffic_light(const int& id){

  int signal_id;
  if (id == 56 || id ==62 || id == 75 || id == 57 || id == 63){
    signal_id = 1;
  }
  else if (id == 35 || id == 68 || id == 25){
    signal_id = 2;
  }
  else if (id == 53 || id == 47 || id == 81 || id == 69 || id == 54 || id == 48){
    signal_id = 3;
  }
  else if (id == 31 || id == 79 || id == 72 || id == 30){
    signal_id = 4;
  }
  else if (id == 58 || id == 76 || id == 64 || id == 73 || id == 59 || id == 65){
    signal_id = 5;
  }
  else if (id == 34 || id == 78 || id == 70 || id == 35){
    signal_id = 6;
  }
  else if (id == 51 || id == 44 || id ==82 || id == 45 || id == 52 || id == 45){
    signal_id = 7;
  }
  else if (id == 41 || id == 80 || id == 74 || id == 40 ){
    signal_id = 8;
  }
  else if (id == 60 || id == 66 || id == 67){
    signal_id = 9;
  }
  else if (id == 8 || id == 9 || id == 43 || id == 10){
    signal_id = 10;
  }
  else{
    signal_id = -1;
  }
  
  return signal_id;
}

void MapLoader::lir_handler(const ros::TimerEvent& time){
  if(global_traj_available){
    lane_in_range();
    if(lir_array.lanes.size()>0){
      lir_pub.publish(lir_array);
    }
    else{
      ROS_INFO("No Lane in Range");
    }
  }
}

void MapLoader::wp_inArea(){
  if(global_traj_available){
    for(int i=0; i<global_lane_array.lanes.size(); i++){
      for(int j=0; j<global_lane_array.lanes[i].waypoints.size(); j++){
        for(int k=0; k<areas.size(); k++){
          hmcl_msgs::Waypoint wp=global_lane_array.lanes[i].waypoints[j];
          lanelet::Area area = areas[k];
          if(lanelet::geometry::inside(area,lanelet::BasicPoint2d(wp.pose.pose.position.x,wp.pose.pose.position.y))){
            lanelet::Attribute attr = area.attribute(lanelet::AttributeName::Subtype);
            if(attr.value() == lanelet::AttributeValueString::Crosswalk){
            global_lane_array.lanes[i].waypoints[j].Crosswalk = true;
            }
            else if(attr.value() == lanelet::AttributeValueString::Junction){
            global_lane_array.lanes[i].waypoints[j].Junction = true;
            }
            else if(attr.value() == lanelet::AttributeValueString::Stopline){
            global_lane_array.lanes[i].waypoints[j].Stop_line = true;
            }
          }
        }
      }
    }
  }  
}
void MapLoader::ped_state(const autoware_msgs::DetectedObjectArray& pobjects)
{
  // ROS_INFO(">>>>>>>>>>>>>>>>>"  );
  ped_marker_array.markers.clear();
  if (pobjects.objects.size()> 0 && pose_init){
    for (int i = 0; i < pobjects.objects.size(); i++)
    { 
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ;
      marker_tmp.id = 10000+i;
      marker_tmp.ns = "pedd";
      marker_tmp.type = visualization_msgs::Marker::CUBE;
      marker_tmp.action = visualization_msgs::Marker::ADD;

      float x,y;
      double ped_x = pobjects.objects[i].pose.position.x;
      double ped_y = pobjects.objects[i].pose.position.y;
      geometry_msgs::Pose egoPose = cur_pose;
      float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.x + egoPose.orientation.w*egoPose.orientation.z), 1-2*(egoPose.orientation.y*egoPose.orientation.y + egoPose.orientation.z*egoPose.orientation.z));
      double xx =egoPose.position.x + ped_x*cos(yaw) - ped_y*sin(yaw);
      double yy =egoPose.position.y + ped_x*sin(yaw) + ped_y*cos(yaw);
    
      marker_tmp.pose.position.x = xx; 
      marker_tmp.pose.position.y = yy;   
      // marker_tmp.pose.position.x = pobjects.objects[i].pose.position.x;
      // marker_tmp.pose.position.y = pobjects.objects[i].pose.position.y;        
      marker_tmp.pose.position.z = 0.2;
      marker_tmp.pose.orientation.w = 1.0;
      // marker_tmp.points[0].x = ped_x; 
      // marker_tmp.points[0].y = ped_y;        
      // marker_tmp.points[0].z = 0.2;
      marker_tmp.color.r = 0.0;
      marker_tmp.color.g = 1.0;
      marker_tmp.color.b = 1.0;
      marker_tmp.scale.x = 2.0;
      marker_tmp.scale.y = 2.0;
      marker_tmp.scale.z = 2.0;

      marker_tmp.color.a = 1.0;
      // marker_tmp.scale.z = 1.0;
      // marker_tmp.lifetime = ros::Duration(1.0);
      ped_marker_array.markers.push_back(marker_tmp);

    }
  }
  ped_pts_pub.publish(ped_marker_array);
}

void MapLoader::ped_inCw(){
  if(ped_available && pose_init){
    for(int i=0; i < ped_array.objects.size(); i++){
      // ROS_INFO("HERE:::::::::::oject size is %d", ped_array.objects.size());
      float x,y;
      double ped_x = ped_array.objects[i].pose.position.x;
      double ped_y = ped_array.objects[i].pose.position.y;
      geometry_msgs::Pose egoPose = cur_pose;
      float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.x + egoPose.orientation.w*egoPose.orientation.z), 1-2*(egoPose.orientation.y*egoPose.orientation.y + egoPose.orientation.z*egoPose.orientation.z));
      x=egoPose.position.x + ped_x*cos(yaw) - ped_y*sin(yaw);
      y=egoPose.position.y + ped_x*sin(yaw) + ped_y*cos(yaw);


      double dis2ego = sqrt(pow(x-odom_x,2)+pow(y-odom_y,2));
      ROS_INFO("Distance to Ego is:::::  %f", dis2ego);
      if (dis2ego >= 30){
        continue;
      }
    

      for(int j=0; j<crosswalk.size(); j++){
        lanelet::Area cross_tmp = crosswalk[j];
        if(lanelet::geometry::inside(cross_tmp,lanelet::BasicPoint2d(x,y))){
          ped_in = true;
          ROS_INFO("HERE:::::::::::pedestrain is in");
          break;
        }
        else{
          ped_in = false;
          if (dis2ego <= 5){
            ped_in = true;
          }
        }
      }
      if(ped_in){
        break;
      }
    }
  }
  else{
    ped_in = false;
  }
  ped_available = false;
}

void MapLoader::ped_inCw_handler(const ros::TimerEvent& time){
  ped_inCw();
  if(ped_in){
    ped_tmp = true;
    ped_count = 0;
    ped_cw.data = true;
  }
  else if(ped_tmp){
    ped_count++;
    if(ped_count > 30){
      ped_cw.data=false;
      ped_tmp = false;
    }
    else{
      ped_cw.data=true;
    }
  }
  else{
    ped_cw.data = false;
  }
  ped_cw_pub.publish(ped_cw);
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
bool MapLoader::calculate_distance_(hmcl_msgs::Waypoint &wp1, hmcl_msgs::Waypoint &wp2, double &dist, double &dist_cum){
  dist_cum = dist_cum + sqrt(pow((wp1.pose.pose.position.x-wp2.pose.pose.position.x),2) + pow((wp1.pose.pose.position.y-wp2.pose.pose.position.y),2));
  // std::cout << dist_cum << std::endl;
  if (dist_cum< dist){
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
  junction = junctionAreas(areas); 
  crosswalk = crosswalkAreas(areas);
  stopline = stoplineAreas(areas);

  ROS_INFO("%d areas, %d junction, %d crosswalk, %d stopline", areas.size(), junction.size(), crosswalk.size(), stopline.size());

  std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
  std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
  std_msgs::ColorRGBA cl_road, cl_junction, cl_cross, cl_ll_borders, cl_tl_stoplines, cl_ss_stoplines, cl_trafficlights;
  setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
  setColor(&cl_junction, 0.0, 1.0, 0.0, 0.5);
  setColor(&cl_cross, 0.2, 0.7, 0.2, 0.3);
  setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);
  setColor(&cl_tl_stoplines, 1.0, 0.5, 0.0, 0.5);
  setColor(&cl_ss_stoplines, 1.0, 0.0, 0.0, 0.5);
  setColor(&cl_trafficlights, 0.0, 0.0, 1.0, 0.8);

  insertMarkerArray(&map_marker_array, areaMarkerArray(junction,cl_junction));
  insertMarkerArray(&map_marker_array, areaMarkerArray(crosswalk, cl_cross));
  insertMarkerArray(&map_marker_array, areaMarkerArray(stopline,cl_ss_stoplines));
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
    mission_pub.publish(mission_pt);
    mission_pt_pub.publish(mission_pt_mark);
    
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

void MapLoader::mission1Callback(const v2x_msgs::Mission1& msg, const std::vector<std::pair<double,double>>  mission_positions){    
    // ROS_INFO("Mission1 callback");
    mission1_marker_array.markers.clear();
    for(int i=0; i<msg.States.size(); i++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ;
        marker_tmp.id = 65000+i;
        marker_tmp.ns = "mission1";
        marker_tmp.text = std::to_string(msg.States[i].route_node_index);
        marker_tmp.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        marker_tmp.action = visualization_msgs::Marker::ADD;

        marker_tmp.pose.position.x = mission_positions[i].first; 
        marker_tmp.pose.position.y = mission_positions[i].second;        
        marker_tmp.pose.position.z = 0;
        marker_tmp.color.r = 1.0;
        marker_tmp.color.g = 1.0;
        marker_tmp.color.b = 1.0;

        marker_tmp.color.a = 1.0;
        marker_tmp.scale.z = 1.0;
        marker_tmp.lifetime = ros::Duration(1.0);

        if (msg.States[i].route_node_type == 1){
            marker_tmp.text = "start : "+std::to_string(msg.States[i].route_node_index);
        }
        else if (msg.States[i].route_node_type == 2){
            marker_tmp.text = "End : "+std::to_string(msg.States[i].route_node_index);
        }
        mission1_marker_array.markers.push_back(marker_tmp);

        marker_tmp.id = 65100+i;
        marker_tmp.type = visualization_msgs::Marker::SPHERE;
        if (msg.States[i].route_node_type == 1){
            marker_tmp.color.g = 0.0;
            marker_tmp.color.b = 0.0;
        }
        else if (msg.States[i].route_node_type == 2){
            marker_tmp.color.r = 0.0;
            marker_tmp.color.g = 0.0; 
        }
        
        marker_tmp.scale.x = 1;
        marker_tmp.scale.y = 1;

        marker_tmp.color.a = 0.3;
        mission1_marker_array.markers.push_back(marker_tmp);
    }
    mission_pts_pub.publish(mission1_marker_array);
    return;
}


void MapLoader::mission_state(const std::vector<std::pair<double,double>>  mission_positions)
{
  // visualization_msgs::MarkerArray vel_profs;
  visualization_msgs::Marker mission_pt_mark;

  mission_pt_mark.header.frame_id = "/map";
  mission_pt_mark.header.stamp = ros::Time::now();
  mission_pt_mark.ns = "mission_state";
  mission_pt_mark.id = 1;
  mission_pt_mark.type = visualization_msgs::Marker::POINTS;
  mission_pt_mark.action = visualization_msgs::Marker::ADD;


  for (int i = 0; i < mission_positions.size(); i++)
  {
      geometry_msgs::Point p;
      if (i < mission_positions.size())
      {
          p.x = mission_positions[i].first;
          // ROS_INFO("mission_pt: %f", p.x);
          p.y = mission_positions[i].second;
          p.z = 0;
          mission_pt_mark.points.push_back(p);
      }  
  }
  

  mission_pt_mark.scale.x = 1;
  mission_pt_mark.scale.y = 1;
  mission_pt_mark.scale.z = 0;

  mission_pt_mark.color.a = 1.0;
  mission_pt_mark.color.r = 0.0;
  mission_pt_mark.color.g = 1.0;
  mission_pt_mark.color.b = 1.0;
  
  // vel_profs.markers.push_back(vel_prof);
  mission_pt_pub.publish(mission_pt_mark);
}


void MapLoader::v2x_goal_nodes(){

  if (!getV2Xinfo){
    return;
  }
  double origin_x, origin_y;
  int zone=52, setzone=-1;
  double gamma, k;
  bool north=true, mgrs=false;
  


  std::vector<std::pair<double,double>> lla;
  
  std::pair<double, double> n;
  for (int i=0; i < MissionStates.States.size(); i++){
    n = {MissionStates.States[i].route_node_pos_lon, MissionStates.States[i].route_node_pos_lat};
    lla.push_back(n);

    if (MissionStates.States[i].route_node_type == 1){
      start_idx = i;
    }
    else if (MissionStates.States[i].route_node_type == 2){
      end_idx = i;
    }
  }
  //TEST1
  // std::pair<double, double> n1 = {128.4007912, 35.6473269};
  // std::pair<double, double> n2 = {128.4004897, 35.6475503};
  // std::pair<double, double> n3 = {128.400041, 35.6476327};
  // std::pair<double, double> n4 = {128.3994251, 35.6479669};
  // std::pair<double, double> n5 = {128.3991161, 35.6484246};
  // std::pair<double, double> n6 = {128.3991183, 35.6487722};
  // std::pair<double, double> n7 = {128.3988279, 35.6490777};
  // std::pair<double, double> n8 = {128.3986198, 35.649262};
  // std::pair<double, double> n9 = {128.3985271, 35.6495136};
  // std::pair<double, double> n10 = {128.3990426, 35.6492655};
  // std::pair<double, double> n11 = {128.3994456, 35.6487118};
  // std::pair<double, double> n12 = {128.3990969, 35.648453};
  // std::pair<double, double> n13 = {128.3984583, 35.6487572};
  // std::pair<double, double> n14 = {128.39822, 35.6492807};
  // std::pair<double, double> n15 = {128.3985405, 35.6491925};
  // std::pair<double, double> n16 = {128.3987532, 35.6490049};
  // std::pair<double, double> n17 = {128.3990167, 35.6488157};
  // std::pair<double, double> n18 = {128.3994719, 35.6486958};
  // std::pair<double, double> n19 = {128.4000283, 35.6483885};
  // std::pair<double, double> n20 = {128.400377, 35.6478831};
  // std::pair<double, double> n21 = {128.4004214, 35.6475648};
  // std::pair<double, double> n22 = {128.4007492, 35.6472273};

  // lla.push_back(n1); lla.push_back(n2); lla.push_back(n3); lla.push_back(n4);
  // lla.push_back(n5); lla.push_back(n6); lla.push_back(n7); lla.push_back(n8);
  // lla.push_back(n9); lla.push_back(n10); lla.push_back(n11); lla.push_back(n12);
  // lla.push_back(n13); lla.push_back(n14); lla.push_back(n15); lla.push_back(n16);
  // lla.push_back(n17); lla.push_back(n18); lla.push_back(n19); lla.push_back(n20);
  // lla.push_back(n21); lla.push_back(n22);

  //Rehearsal 1
  // std::pair<double, double> n1 = {128.4007912, 35.6473269};
  // std::pair<double, double> n2 = {128.4004897, 35.6475503};
  // std::pair<double, double> n3 = {128.400041, 35.6476327};
  // std::pair<double, double> n4 = {128.3994251, 35.6479669};
  // std::pair<double, double> n5 = {128.3991161, 35.6484246};
  // std::pair<double, double> n6 = {128.3994841, 35.6483555};
  // std::pair<double, double> n7 = {128.3998964, 35.6479855};
  // std::pair<double, double> n8 = {128.4000641, 35.6476466};
  // std::pair<double, double> n9 = {128.3994474, 35.6479488};
  // std::pair<double, double> n10 = {128.3984803, 35.6487352};
  // std::pair<double, double> n11 = {128.398201, 35.6492639};
  // std::pair<double, double> n12 = {128.3984808, 35.6492473};
  // std::pair<double, double> n13 = {128.3990016, 35.6487824};
  // std::pair<double, double> n14 = {128.3995602, 35.648287};


  // lla.push_back(n1); lla.push_back(n2); lla.push_back(n3); lla.push_back(n4);
  // lla.push_back(n5); lla.push_back(n6); lla.push_back(n7); lla.push_back(n8);
  // lla.push_back(n9); lla.push_back(n10); lla.push_back(n11); lla.push_back(n12);
  // lla.push_back(n13); lla.push_back(n14);

  GeographicLib::UTMUPS::Forward(origin_lat, origin_lon, zone, north, origin_x, origin_y, setzone, mgrs);
  if(mission_status <= 1){
    std::pair<double,double> xy = {odom_x, odom_y};
    xyz.push_back(xy);
  }

  // start_idx = 0;
  // end_idx = 13;
  std::vector<std::pair<double,double>> mission_positions;
  for(int i=0; i<lla.size(); i++){
    double x, y;
    GeographicLib::UTMUPS::Forward(lla[i].second, lla[i].first, zone, north, x, y, setzone, mgrs);
    std::pair<double,double> xy = {x-origin_x, y-origin_y};
    xyz.push_back(xy);

    if (i == start_idx){
      mission_pt.start.x = x-origin_x;
      mission_pt.start.y = y-origin_y;
    }
    else if (i == end_idx){
      mission_pt.end.x = x-origin_x;
      mission_pt.end.y = y-origin_y;
    }

    std::pair<double,double> mission_position = {x-origin_x, y-origin_y};
    mission_positions.push_back(mission_position);
  }

  mission_state(mission_positions);
  // mission1Callback(Mission_msg, mission_positions);
  goal_available = true;


  
  // for(int i=0; i<xyz.size(); i++){
  //   ROS_INFO("%f, %f", xyz[i].first, xyz[i].second);
  // }
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

void MapLoader::v2xMissionCallback(const v2x_msgs::Mission1& msg){
  getV2Xinfo = true;
  Mission_msg = msg;
  MissionStates.States = msg.States;
  mission_status = msg.status;

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