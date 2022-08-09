
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

#include <cstdlib>
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
#include "agents_sim.h"
// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


AgentSim::AgentSim(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p) :  
  nh_(nh), nh_p_(nh_p), dt(0.1)
{
  // using namespace lanelet;
  
  map_loaded = false;    
  nh_p_.param<std::string>("osm_file_name", osm_file_name, "Town01.osm");
  nh_p_.getParam("osm_file_name", osm_file_name);
  nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
  nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
  nh_p_.param<double>("map_origin_att", origin_att, 0.0);  
  nh_p_.param<double>("map_road_resolution", map_road_resolution, 1.0);
  
  nh_p_.param<int>("n_vehicle_agents", n_vehicle_agents, 3);  
  nh_p_.param<int>("n_ped_agents", n_ped_agents, 0);  
  
  for(int i=0; i < n_vehicle_agents; i++){
    Agents vehicle_agent;    
    vehicle_agents.push_back(vehicle_agent);
    if(i ==0){
      Eigen::VectorXd state_(4);    
      state_ << -151, 71, 5.43, 0.0;
      vehicle_agents[i].set_state(state_);  
    }else if(i == 1){
      Eigen::VectorXd state_(4);    
      state_ << -143.217, 87.6375, 3.82445, 0.0;
      vehicle_agents[i].set_state(state_);  
    }else if(i == 2){
      Eigen::VectorXd state_(4);    
      state_ << -163.47, 34.5, 2.38, 0.0;
      vehicle_agents[i].set_state(state_);  
    }
    
  }
  
  viz_timer = nh_.createTimer(ros::Duration(0.1), &AgentSim::viz_pub,this);    
  vehicle_agents_pub = nh_.advertise<visualization_msgs::MarkerArray>("/vehicle_agents_marker", 20, true);
  ped_agents_pub = nh_.advertise<visualization_msgs::MarkerArray>("/ped_agents_marker", 20, true);
  g_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/npc_global_traj_viz", 20, true);
  load_map();
  

  lanelet::traffic_rules::TrafficRulesPtr trafficRules =
  lanelet::traffic_rules::TrafficRulesFactory::create(lanelet::Locations::Germany, lanelet::Participants::Vehicle);
  routingGraph = lanelet::routing::RoutingGraph::build(*map, *trafficRules);  
  
  
  
  boost::thread agent_update_thread(&AgentSim::simulationCallback,this); 
  boost::thread agent_local_path_update_thread(&AgentSim::localpathCallback,this); 
  boost::thread agent_globalpath_update_thread(&AgentSim::globalpathCallback,this); 
  
}

AgentSim::~AgentSim()
{}


void AgentSim::globalpathCallback(){  
    ros::Rate loop_rate(0.1); // rate  
      while (ros::ok()){
        if (!map_loaded){continue;}
          for(int i=0; i < n_vehicle_agents; i++){                
            vehicle_agents[i].targetLaneArray = compute_random_path(vehicle_agents[i].getPose(),vehicle_agents[i].targetLaneMarker);            
            }
          loop_rate.sleep();
      }
      ROS_INFO("path simulation end");
}


void AgentSim::localpathCallback(){  
    ros::Rate loop_rate(1/dt); // rate  
      while (ros::ok()){
        if (!map_loaded){continue;}        
          for(int i=0; i < n_vehicle_agents; i++){                
            if (vehicle_agents[i].targetLaneArray.lanes.size() < 1){
              continue;
              }
            vehicle_agents[i].targetLane = compute_local_path(vehicle_agents[i].targetLaneArray,vehicle_agents[i].getPose());            
            }
          loop_rate.sleep();
      }
      ROS_INFO("path simulation end");
}


void AgentSim::simulationCallback(){  
    ros::Rate loop_rate(1/dt); // rate  
      while (ros::ok()){
        if (!map_loaded){continue;}
          for(int i=0; i < n_vehicle_agents; i++){
            double agent_velocity = 3.0;
            vehicle_agents[i].update_step(agent_velocity);                                  
            }
          loop_rate.sleep();
      }
      ROS_INFO("simulation end");
}


void AgentSim::viz_pub(const ros::TimerEvent& time){  
   visualization_msgs::MarkerArray vehicle_markerArray;
   visualization_msgs::MarkerArray local_traj_markerArray;

   for(int i=0; i < n_vehicle_agents; i++){            
            visualization_msgs::Marker marker_tmp = vehicle_agents[i].get_rviz_marker();
            vehicle_markerArray.markers.push_back(marker_tmp);            
            visualization_msgs::MarkerArray tt = viz_local_paths(vehicle_agents[i].targetLane);
            for(int j=0; j < tt.markers.size(); j++){            
                  local_traj_markerArray.markers.push_back(tt.markers[j]);
            }            
          }
    g_traj_viz_pub.publish(local_traj_markerArray);
    vehicle_agents_pub.publish(vehicle_markerArray);
    
    return;    
}

void AgentSim::load_map(){
  
  ROS_INFO("map loading");
  lanelet::ErrorMessages errors;  
  lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));    
  map = load(osm_file_name, "osm_handler",projector,&errors);
  assert(errors.empty()); 
  ROS_INFO("map loaded succesfully");


  ROS_INFO("constructing lanelets viz ..... ");
  lanelet::Lanelets all_lanelets = laneletLayer(map); 
  lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(map);
  road_lanelets = roadLanelets(all_lanelets);  
  road_lanelets_const = roadLaneletsConst(all_laneletsConst);    
  fix_and_save_osm();    
  map_loaded  = true;
}


hmcl_msgs::LaneArray AgentSim::compute_random_path(geometry_msgs::Pose cur_pose, visualization_msgs::MarkerArray &traj_lanelet_marker_array){  
  hmcl_msgs::LaneArray global_lane_array;  
  global_lane_array.lanes.clear();  
  if(road_lanelets_const.size() > 0){      
      int start_closest_lane_idx = get_closest_lanelet(road_lanelets_const,cur_pose);            
      lanelet::ConstLanelet lanelet = road_lanelets_const[start_closest_lane_idx];
      
      lanelet::routing::LaneletPaths local_paths = routingGraph->possiblePaths(lanelet, 100, 0, true);
            
      // ROS_INFO("shortest path_size = %d", local_path.size());
        if(local_paths.size() < 1){
          ROS_WARN("[MAP_LOADER] = Path is not found");        
        }
        else{
          lanelet::routing::LaneletPath local_path = local_paths[0];
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
              for (int j = waypoint_idx_init; j < lstring.size(); j++ ){
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
              global_lane_array.lanes.push_back(ll_);
            }   
              // Construct Traj_lanelet_marker 
              traj_lanelet_marker_array.markers.clear();            
              std::vector<lanelet::ConstLanelet> traj_lanelets;
              for(int i=0; i< local_path.size();i++){traj_lanelets.push_back(local_path[i]);}                  
                      std_msgs::ColorRGBA traj_marker_color;
                      setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.3);                        
                    insertMarkerArray(&traj_lanelet_marker_array, trajectory_draw(
                    traj_lanelets, traj_marker_color));
  
        }
  }
  else{
    ROS_WARN("[MAP_LOADER] = Current pose is not initialized or map is not loaded");
  }   

  return global_lane_array;
}


hmcl_msgs::Lane AgentSim::compute_local_path(hmcl_msgs::LaneArray global_lane_array_for_local,geometry_msgs::Pose cur_pose){

    std::vector<std::vector<double>> global_points;
    std::vector<double> speed_lim;    
    int init_l_lane_idx, init_point_idx;  
    findnearest_lane_and_point_idx(global_lane_array_for_local, cur_pose , init_l_lane_idx, init_point_idx);
    geometry_msgs::Pose prev_pose = cur_pose;
    hmcl_msgs::Lane local_traj_msg;
    local_traj_msg.header = global_lane_array_for_local.header;
    local_traj_msg.speed_limit  = global_lane_array_for_local.lanes[init_l_lane_idx].speed_limit;
    local_traj_msg.lane_id = global_lane_array_for_local.lanes[init_l_lane_idx].lane_id;
    local_traj_msg.lane_change_flag = global_lane_array_for_local.lanes[init_l_lane_idx].lane_change_flag;
    local_traj_msg.trafficlights = global_lane_array_for_local.lanes[init_l_lane_idx].trafficlights;
    local_traj_msg.speedbumps = global_lane_array_for_local.lanes[init_l_lane_idx].speedbumps;
    double local_path_length = 5.0;
    double weight_decay_rate = 0.95;
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
                
                
                speed_lim.push_back(waypoint_tmp.twist.twist.linear.x);            

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
      
  
  return local_traj_msg;

}
 

 void AgentSim::fix_and_save_osm(){  
  
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


int main (int argc, char** argv)
{
ros::init(argc, argv, "agents_sim");
ros::NodeHandle nh_;
ros::NodeHandle nh_private("~");
AgentSim AgentSim_(nh_,nh_private);

  ros::spin();


}
