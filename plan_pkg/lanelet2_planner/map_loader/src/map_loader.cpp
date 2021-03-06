
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



MapLoader::MapLoader(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p, const ros::NodeHandle& nh_local_path) :  
  nh_(nh), nh_p_(nh_p), nh_local_path_(nh_local_path)  
{
  // using namespace lanelet;

  map_bin_pub = nh_.advertise<autoware_lanelet2_msgs::MapBin>("/lanelet_map_bin", 1, true);
  
  map_loaded = false;
  way_pub = nh_.advertise<hmcl_msgs::LaneArray>("/global_traj", 2, true);
  local_traj_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 2, true);
  g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);  
  autoware_lane_pub = nh_.advertise<autoware_msgs::Lane>("/local_traj_auto", 2, true);
  
  pose_init = false; 
  goal_available = false;
  pose_sub = nh_.subscribe("/current_pose",1,&MapLoader::poseCallback,this);
  goal_sub = nh_.subscribe("move_base_simple/goal", 1, &MapLoader::callbackGetGoalPose, this);
  vehicle_status_sub = nh_.subscribe("/vehicle_status", 1, &MapLoader::callbackVehicleStatus, this);
  

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

  
   
 
  
  
  

  if(visualize_path){    
    g_traj_lanelet_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_lanelets_viz", 1, true);
    g_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_viz", 1, true);
    l_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1, true);  
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
  rp_.setMap(map);


  local_traj_timer = nh_local_path_.createTimer(ros::Duration(0.1), &MapLoader::local_traj_handler,this);    
  if(continuious_global_replan){
    g_traj_timer = nh_.createTimer(ros::Duration(0.5), &MapLoader::global_traj_handler,this);    
  }
  
  boost::thread lanelet_ros_convert(&MapLoader::lanelet_ros_convert_loop,this); 
}

MapLoader::~MapLoader()
{}

void MapLoader::lanelet_ros_convert_loop(){
ros::Rate loop_rate(0.1); // rate  
  while (ros::ok())
  { if(map_loaded){
      autoware_lanelet2_msgs::MapBin map_bin_msg;
      map_bin_msg.header.stamp = ros::Time::now();
      map_bin_msg.header.frame_id = "map";
      map_bin_msg.format_version = "v1";
      map_bin_msg.map_version = "v1";
      lanelet::utils::conversion::toBinMsg(map, &map_bin_msg);
      
      map_bin_pub.publish(map_bin_msg);
    }
  loop_rate.sleep();
  }

}


void MapLoader::global_traj_handler(const ros::TimerEvent& time){
  if(goal_available){
    compute_global_path();
  }  

  if(global_traj_available){
    way_pub.publish(global_lane_array);  
  }  

}

void MapLoader::compute_global_path(){
  
  global_lane_array.lanes.clear();  
  if(pose_init && road_lanelets_const.size() > 0){
      int start_closest_lane_idx = get_closest_lanelet(road_lanelets_const,cur_pose);      
      int goal_closest_lane_idx = get_closest_lanelet(road_lanelets_const,cur_goal);
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
                waypoint_idx_finish = getClosestWaypoint(false,lstring,cur_goal);                             
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
                wp_.pose.pose.position.x = cur_goal.position.x;
                wp_.pose.pose.position.y = cur_goal.position.y;
                wp_.pose.pose.position.z = cur_goal.position.z;
                wp_.pose.pose.orientation.x = cur_goal.orientation.x;
                wp_.pose.pose.orientation.y = cur_goal.orientation.y;
                wp_.pose.pose.orientation.z = cur_goal.orientation.z;
                wp_.pose.pose.orientation.w = cur_goal.orientation.w;
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

          if(visualize_path){
              // Construct Traj_lanelet_marker 
              traj_lanelet_marker_array.markers.clear();            
              std::vector<lanelet::ConstLanelet> traj_lanelets;
              for(int i=0; i< local_path.size();i++){traj_lanelets.push_back(local_path[i]);}                  
                      std_msgs::ColorRGBA traj_marker_color;
                      setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.5);                        
                    insertMarkerArray(&traj_lanelet_marker_array, trajectory_draw(
                    traj_lanelets, traj_marker_color));

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
                      marker_tmp.color = traj_marker_color;
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



void MapLoader::callbackVehicleStatus(const hmcl_msgs::VehicleStatusConstPtr &msg){
  current_speed = msg->wheelspeed.wheel_speed; // in m/s
  if (current_speed > 0){
    double tmp_add_path_length = current_speed*local_path_scale;
    local_path_length = std::min(min_local_path_length + tmp_add_path_length,max_local_path_length);
  }else{
    local_path_length = min_local_path_length;
  }

}

void MapLoader::callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg){
  cur_goal = msg->pose;
  goal_available = true;
  ROS_INFO("goal received");    
  
  compute_global_path();
  goal_available = true;
  
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
  //  if((dist_from_tmp_to_end >= dist_from_current_to_end) && (closest_idx >= lstring.size()-1)){
  //       closest_idx = closest_idx+1;
  //     }
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

void MapLoader::construct_lanelets_with_viz(){
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



 


void MapLoader::viz_pub(const ros::TimerEvent& time){  
    g_map_pub.publish(map_marker_array);
    g_traj_lanelet_viz_pub.publish(traj_lanelet_marker_array);
    g_traj_viz_pub.publish(traj_marker_array);
    
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
            while(count < 10000){              
                auto iter_l =  li->leftBound().begin();  
                lanelet::Point3d p_l = *next(li->leftBound().begin(),count);
                lanelet::Point3d p_end = *next(li->leftBound().begin(),li->leftBound().size()-1);
                double dist_to_end_point =  lanelet::geometry::distance(p_l,p_end);     
                if( dist_to_end_point <= 1 )                  
                    {break;}
                 // ->leftBound()[idx];                    
                lanelet::Point3d p_left  = *next(li->leftBound().begin(),count);
                lanelet::Point3d p_right = *next(li->leftBound().begin(),count+1);                   
                dist_ =  lanelet::geometry::distance(p_left,p_right);                  
                if(dist_ > map_road_resolution){                  
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
            while(count < 10000){              
                auto iter_r =  li->rightBound().begin();  
                lanelet::Point3d p_l = *next(li->rightBound().begin(),count);
                lanelet::Point3d p_end = *next(li->rightBound().begin(),li->rightBound().size()-1);
                double dist_to_end_point =  lanelet::geometry::distance(p_l,p_end);     
                if( dist_to_end_point <= 1 )                  
                    {break;}                                 
                lanelet::Point3d p_left  = *next(li->rightBound().begin(),count);
                lanelet::Point3d p_right = *next(li->rightBound().begin(),count+1);                   
                dist_ =  lanelet::geometry::distance(p_left,p_right);                  
                if(dist_ > map_road_resolution){                  
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


void MapLoader::compute_local_path(){

  

    std::vector<std::vector<double>> global_points;

    // extract local trajectory from "global_lane_array_for_local" to -- >  "local_traj"
    // If we found lane change, we add linstrtings upto the next of the lane which has lane change signal
    int init_l_lane_idx, init_point_idx;  
    findnearest_lane_and_point_idx(global_lane_array_for_local, cur_pose , init_l_lane_idx, init_point_idx);
    prev_pose = cur_pose;
    hmcl_msgs::Lane local_traj_msg;
    local_traj_msg.header = global_lane_array_for_local.header;
    local_traj_msg.speed_limit  = global_lane_array_for_local.lanes[init_l_lane_idx].speed_limit;
    local_traj_msg.lane_id = global_lane_array_for_local.lanes[init_l_lane_idx].lane_id;
    local_traj_msg.lane_change_flag = global_lane_array_for_local.lanes[init_l_lane_idx].lane_change_flag;
    local_traj_msg.trafficlights = global_lane_array_for_local.lanes[init_l_lane_idx].trafficlights;
    local_traj_msg.speedbumps = global_lane_array_for_local.lanes[init_l_lane_idx].speedbumps;
    double lane_weight =1.0;
    float lane_dist_cumulative = 0;   
    bool lane_change_found = false;
    bool lane_change_init = false;
    int nearest_point_to_prev_lane = 0;
    bool complete_loops = false;
    for(int i=init_l_lane_idx; i < global_lane_array_for_local.lanes.size(); i++){
          if(global_lane_array_for_local.lanes[i].lane_change_flag){
                lane_change_found = true;            
                // compute the nearest index to the preious lane                 
                float min_dist_ = std::numeric_limits<float>::max();  
                for(int k=0; k < global_lane_array_for_local.lanes[i].waypoints.size();k++){
                  double dist_= sqrt(pow((global_lane_array_for_local.lanes[i+1].waypoints[0].pose.pose.position.x-global_lane_array_for_local.lanes[i].waypoints[k].pose.pose.position.x),2) 
                                    + pow((global_lane_array_for_local.lanes[i+1].waypoints[0].pose.pose.position.y-global_lane_array_for_local.lanes[i].waypoints[k].pose.pose.position.y),2));      
                  if(min_dist_ >= dist_){
                    nearest_point_to_prev_lane = k;
                    min_dist_ =  dist_;  }  
                }
          }    
          for(int j = 0 ; j < global_lane_array_for_local.lanes[i].waypoints.size(); j++){
              if (i == 0 && j == 0){
                continue;  // this waypoints is the same as current position.  so skip 
              }
              if ( i == init_l_lane_idx &&  j < init_point_idx){
                  continue;
                }
                hmcl_msgs::Waypoint waypoint_tmp =  global_lane_array_for_local.lanes[i].waypoints[j];
                if(lane_change_found){ 
                  if(j >= nearest_point_to_prev_lane){             
                  // initialize lane_weight 
                      if(!lane_change_init){
                          if(i == init_l_lane_idx){
                        double dist_nextlane, dist_curlane; 
                        dist_curlane= sqrt(pow((global_lane_array_for_local.lanes[i].waypoints[j].pose.pose.position.x-cur_pose.position.x),2) 
                                          + pow((global_lane_array_for_local.lanes[i].waypoints[j].pose.pose.position.y-cur_pose.position.y),2));      
                        dist_nextlane= sqrt(pow((global_lane_array_for_local.lanes[i+1].waypoints[j].pose.pose.position.x-cur_pose.position.x),2) 
                                          + pow((global_lane_array_for_local.lanes[i+1].waypoints[j].pose.pose.position.y-cur_pose.position.y),2));                                      
                        lane_weight =dist_nextlane/(dist_curlane+dist_nextlane);                                
                        }else{ 
                          lane_weight= 1;
                        }
                          lane_change_init = true;
                      }else{ 
                          lane_weight = lane_weight*weight_decay_rate;  
                      }
                  
                  lane_weight = std::min(std::max(0.0,lane_weight),1.0);
                  waypoint_tmp.pose.pose.position.x =  global_lane_array_for_local.lanes[i].waypoints[j].pose.pose.position.x*lane_weight+ global_lane_array_for_local.lanes[i+1].waypoints[j].pose.pose.position.x*(1-lane_weight);
                  waypoint_tmp.pose.pose.position.y =  global_lane_array_for_local.lanes[i].waypoints[j].pose.pose.position.y*lane_weight+ global_lane_array_for_local.lanes[i+1].waypoints[j].pose.pose.position.y*(1-lane_weight);
                  }
                }
                local_traj_msg.waypoints.push_back(waypoint_tmp);
                std::vector<double> tmp_points; 
                tmp_points.push_back(waypoint_tmp.pose.pose.position.x);
                tmp_points.push_back(waypoint_tmp.pose.pose.position.y);
                global_points.push_back(tmp_points);                                
                double lane_dist_= sqrt(pow((prev_pose.position.x - waypoint_tmp.pose.pose.position.x),2) + pow((prev_pose.position.y - waypoint_tmp.pose.pose.position.y),2));      
                lane_dist_cumulative = lane_dist_cumulative + lane_dist_;
                prev_pose.position.x = waypoint_tmp.pose.pose.position.x;
                prev_pose.position.y = waypoint_tmp.pose.pose.position.y;
              if(lane_dist_cumulative > local_path_length){
                complete_loops = true;
                break;
              }             
          }             
        if(lane_change_found || complete_loops)
          {break;}
    }
      
  

  ////////////////////////////////////////////////////
  // curve fitting   
  
  curve_fitting(global_points, local_traj_msg);
  
  /////////////////////////

  local_traj_pub.publish(local_traj_msg);
      if(visualize_path){
          viz_local_path(local_traj_msg);
          l_traj_viz_pub.publish(local_traj_marker_arrary);
      }
  pub_autoware_traj(local_traj_msg);

}


void MapLoader::curve_fitting(std::vector<std::vector<double>>& g_points, hmcl_msgs::Lane& local_traj_msg){
      if(g_points.size() < 10){
        ROS_WARN("polyfit is not done as number of points are not enough");
        return;
      } 
      std::vector<double> local_xs, local_ys; 
      double current_yaw = amathutils::getPoseYawAngle(cur_pose);
      amathutils::wrap_yaw_rad(current_yaw);
      double psi = -1*current_yaw;
      double dx = -1*cur_pose.position.x;
      double dy = -1*cur_pose.position.y;  

       // convert to local frame 
      for(int i=0;i< g_points.size();i++){    
          double local_x = cos(psi)*(g_points[i][0]+dx) - sin(psi)*(g_points[i][1]+dy);
          double local_y = sin(psi)*(g_points[i][0]+dx) + cos(psi)*(g_points[i][1]+dy);
          local_xs.push_back(local_x);
          local_ys.push_back(local_y);          
      }  

      // fit in local frame 
      
      PolyFit<double> f = polyfit(local_xs, local_ys);
      if(polyfit_error){
        ROS_WARN("No solution found from polyfit"); 
        return; 
      }   
      Eigen::Matrix<double, Eigen::Dynamic, 1> Pcoef_tmp = f.getCoefficients();
      // ROS_INFO("current Pose  x = %f,y  = %f,yaw  = %f ", -1*dx, -1*dy, -1*psi);
      // ROS_INFO("c3 = %f,c2 = %f,c1 = %f,c0 = %f ", Pcoef_tmp(0,0), Pcoef_tmp(1,0), Pcoef_tmp(2,0), Pcoef_tmp(3,0));
      
      double c3 = Pcoef_tmp(0,0);
      double c2 = Pcoef_tmp(1,0);
      double c1 = Pcoef_tmp(2,0);
      double c0 = Pcoef_tmp(3,0);      

      poly_error = f.getMSE();         
      float init_s = 0.0;
      if(poly_error < 10){                    
          std::vector<double> xeval = linspaces(init_s,local_path_length,int(local_path_length/map_road_resolution));
          std::vector<double> yval = f.evalPoly(xeval);             
          
          hmcl_msgs::Lane local_traj_msg_fit;
          local_traj_msg_fit.header = global_lane_array_for_local.header;
          for(int i=0; i< xeval.size(); i++){    
            hmcl_msgs::Waypoint waypoint_tmp;        
            waypoint_tmp.pose.pose.position.x = (cos(-1*psi)*xeval[i]-sin(-1*psi)*yval[i])-dx;
            waypoint_tmp.pose.pose.position.y = (sin(-1*psi)*xeval[i]+cos(-1*psi)*yval[i])-dy;          
            double epsi_tmp = 3*xeval[i]*xeval[i]*c3 + 2*xeval[i]*c2 + c1;     
            epsi_tmp = atan(epsi_tmp)- psi;       
            tf2::Quaternion q_tmp;
            q_tmp.setRPY(0, 0, epsi_tmp);
            q_tmp=q_tmp.normalize();
            waypoint_tmp.pose.pose.orientation.x = q_tmp[0];
            waypoint_tmp.pose.pose.orientation.y = q_tmp[1];
            waypoint_tmp.pose.pose.orientation.z = q_tmp[2];
            waypoint_tmp.pose.pose.orientation.w = q_tmp[3];
            waypoint_tmp.twist.twist.linear.x = 7;
            local_traj_msg_fit.waypoints.push_back(waypoint_tmp);            
          }
          local_traj_msg = local_traj_msg_fit;
          
      }else{
        ROS_INFO("poly_error = %f", poly_error);
      }

}





void MapLoader::pub_autoware_traj(const hmcl_msgs::Lane& lane){
  autoware_msgs::Lane autoware_lane;
  autoware_lane.header = lane.header;
  
  for(const auto lane_waypoint: lane.waypoints){
    autoware_msgs::Waypoint wp;
    wp.pose = lane_waypoint.pose;
    wp.twist = lane_waypoint.twist;
    autoware_lane.waypoints.push_back(wp);
  }
  autoware_lane_pub.publish(autoware_lane);
}

void MapLoader::local_traj_handler(const ros::TimerEvent& time){  
    
    //////////////////////// //////////////////////// ////////////////////////
  // hmcl_msgs::Lane local_traj_test_msg;
  //      local_traj_test_msg.header.frame_id = "map";
  //         local_traj_test_msg.header.stamp = ros::Time::now();  
  // std::vector<double> p1,p2;
  // if(test_direction > 0){
  //   p1.push_back(417.856);
  //   p1.push_back(639.95);
    
  //   p2.push_back(691.05);
  //   p2.push_back(725.87);
    
    
  // }else{
    
  //   p2.push_back(417.856);
  //   p2.push_back(639.95);

    
  //   p1.push_back(691.05);
  //   p1.push_back(725.87);
  // }
  
  

  // double dist_tmp = sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]));
  // double resolution = 0.5;
  // int num_of_points = dist_tmp/resolution;
  // std::vector<double> x_poses = linspace(p1[0], p2[0], num_of_points);

  // //  y = (p2[1]-p1[2]/(p2[0]-p1[0])*(x-p1[0])+p1[0];
  
  // for(int i=0;i < x_poses.size(); i++){    
  //   hmcl_msgs::Waypoint waypoint_tmp;
  //   waypoint_tmp.pose.header = local_traj_test_msg.header;
  //   waypoint_tmp.pose.pose.position.x = x_poses[i];
  //   waypoint_tmp.pose.pose.position.y=  (p2[1]-p1[1])/(p2[0]-p1[0])*(x_poses[i]-p1[0])+p1[1];
  //   local_traj_test_msg.waypoints.push_back(waypoint_tmp);
  // }
  
  // local_traj_pub.publish(local_traj_test_msg);
  //     if(visualize_path){
  //         viz_local_path(local_traj_test_msg);
  //         l_traj_viz_pub.publish(local_traj_marker_arrary);
  //     }
  // pub_autoware_traj(local_traj_test_msg);
  //////////////////////// //////////////////////// //////////////////////// ////////////////////////
  mu_mtx.lock();
    if(global_traj_available){
      // std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        compute_local_path();
  //     std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
  // std::cout << "loop iteration time = " << sec.count() << " seconds" << std::endl;
    }    
    mu_mtx.unlock();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
