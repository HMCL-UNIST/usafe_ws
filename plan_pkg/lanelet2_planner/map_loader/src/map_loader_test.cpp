                                                   
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

//   Authour : Hyeonbin Lee, bin2915@unist.ac.kr


#include <iostream>
#include <string>
#include <sstream>
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
#include "map_loader_test.h"

// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )

// A_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// C_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// Q_curv << 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01;
// R_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
// P_curv << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;

MapLoader::MapLoader(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p) :  
  nh_(nh), nh_p_(nh_p),cur_filter(A_curv,B_curv,C_curv,Q_curv,R_curv,P_curv)  
{

  //Subtype Init
  PolygonFlag.isinJunction = false;
  PolygonFlag.isinExit = false;
  PolygonFlag.isinBank = false;
  PolygonFlag.isinFreespace = false;
  PolygonFlag.isinCrosswalk = false;
  PolygonFlag.isinBuilding = false;

  // using namespace lanelet;
  map_bin_pub = nh_.advertise<autoware_lanelet2_msgs::MapBin>("/lanelet_map_bin", 1, true);
  map_ver_pub = nh_.advertise<std_msgs::Int8>("/map_ver", 1, true);
  map_loaded = false;
  way_pub = nh_.advertise<hmcl_msgs::LaneArray>("/global_traj", 2, true);
  optimal_pub = nh_.advertise<hmcl_msgs::LaneArray>("/optimal_traj",2, true);
  entire_traj_pub = nh_.advertise<hmcl_msgs::LaneArray>("/entire_traj",2, true);
  entire_joker_pub = nh_.advertise<hmcl_msgs::LaneArray>("/entire_joker",2, true);

  g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true); 
  o_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/optimal_map_viz", 2, true); 
  checkpoint_pub = nh_.advertise<visualization_msgs::MarkerArray>("/checkpoints", 1, true);
  optimal_checkpoint_pub = nh_.advertise<visualization_msgs::MarkerArray>("/optimal_checkpoints", 1, true);
  max_dist = 10000;
  
  // subtype_pub = nh_.advertise<std_msgs::String>("/subtype", 1); 
  subtype_pub = nh_.advertise<hmcl_msgs::PolygonFlag>("/subtype", 1, true); 
  subtype_timer = nh_.createTimer(ros::Duration(0.1), &MapLoader::publishSubtype, this);

  pose_init = false; 
  goal_available = false;
  getMission = false;
  map_ver = 0;
  
  pose_sub = nh_.subscribe("/current_pose",1,&MapLoader::poseCallback,this);
  mission_sub = nh_.subscribe("/mission_state", 1, &MapLoader::missionCallback, this);
  nh_p_.param<std::string>("optimal_osm_file_name", optimal_osm_file_name, "Town01.osm");
  nh_p_.getParam("optimal_osm_file_name", optimal_osm_file_name);
  nh_p_.param<std::string>("osm_file_name", osm_file_name, "Town01.osm");
  nh_p_.getParam("osm_file_name", osm_file_name);
  nh_p_.param<std::string>("j_osm_file_name", j_osm_file_name, "Town01.osm");
  nh_p_.getParam("j_osm_file_name", j_osm_file_name);
  nh_p_.param<int>("map_ver", map_ver, 0);
  nh_p_.param<double>("test_direction", test_direction, 1.0);
  nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
  nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
  nh_p_.param<double>("map_origin_att", origin_att, 0.0);
  nh_p_.param<bool>("visualize_path", visualize_path, true);
  nh_p_.param<double>("map_road_resolution", map_road_resolution, 1.0);
  nh_p_.param<float>("weight_decay_rate", weight_decay_rate, 0.95);
  nh_p_.param<bool>("continuious_global_replan", continuious_global_replan, false);

  nh_p_.param<double>("local_path_scale", local_path_scale, 1.0);
  nh_p_.param<double>("lane_change_in_sec", lane_change_in_sec, 2.0);
  nh_p_.param<double>("lanechange_fsm_period", lanechange_fsm_period, 0.1);

  GeographicLib::UTMUPS::Forward(origin_lat, origin_lon, origin_zone, origin_northp, origin_easting, origin_northing);
  
  initCheckpoints();

  previous_checkpoints = j_checkpoints;
  previous_optimal_checkpoints = j_checkpoints;

  checkers.resize(n_checkpoints[0].size());  
  opt_checkers.resize(o_checkpoints[0].size());
  visualization_msgs::MarkerArray checkpoint_markers;
  checkpoint_markers.markers.clear();    
  int count = 0;
  for(int k=0; k<2; k++){
    if(k==0)checkpoints = n_checkpoints;
    else checkpoints = j_checkpoints;
    for(int i=0; i<checkpoints.size(); i++){
      for(int j=0; j<checkpoints[i].size(); j++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
        marker_tmp.id = count;
        marker_tmp.ns = "checkpoints";
        marker_tmp.type = visualization_msgs::Marker::SPHERE;
        marker_tmp.action = visualization_msgs::Marker::ADD;                  
        marker_tmp.pose.position.x = checkpoints[i][j].first;
        marker_tmp.pose.position.y = checkpoints[i][j].second;
        marker_tmp.pose.position.z = 0;
        if(k==0){
          marker_tmp.color.r = 1.0;
          marker_tmp.color.g = 0.0;
          marker_tmp.color.b = 0.0;
          marker_tmp.color.a = 1.0;
        }
        else{
          marker_tmp.color.r = 1.0;
          marker_tmp.color.g = 1.0;
          marker_tmp.color.b = 0.0;
          marker_tmp.color.a = 1.0;
        }
        marker_tmp.lifetime = ros::Duration();
        marker_tmp.scale.x = 3.0;
        marker_tmp.scale.y = 3.0;
        marker_tmp.scale.z = 3.0;                  
        count++;
        checkpoint_markers.markers.push_back(marker_tmp);
      }
    }
  }
  checkpoint_pub.publish(checkpoint_markers);


  visualization_msgs::MarkerArray optimal_checkpoint_markers;
  optimal_checkpoint_markers.markers.clear();  
  optimal_checkpoints = o_checkpoints;
  for(int i=0; i<optimal_checkpoints.size(); i++){
    for(int j=0; j<optimal_checkpoints[i].size(); j++){
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
      marker_tmp.id = count;
      marker_tmp.ns = "optimal_checkpoints";
      marker_tmp.type = visualization_msgs::Marker::SPHERE;
      marker_tmp.action = visualization_msgs::Marker::ADD;                  
      marker_tmp.pose.position.x = optimal_checkpoints[i][j].first;
      marker_tmp.pose.position.y = optimal_checkpoints[i][j].second;
      marker_tmp.pose.position.z = 0;
      marker_tmp.color.r = 0.0;
      marker_tmp.color.g = 0.0;
      marker_tmp.color.b = 1.0;
      marker_tmp.color.a = 1.0;
      marker_tmp.lifetime = ros::Duration();
      marker_tmp.scale.x = 3.0;
      marker_tmp.scale.y = 3.0;
      marker_tmp.scale.z = 3.0;                  
      count++;
      optimal_checkpoint_markers.markers.push_back(marker_tmp);
    }
  }
  optimal_checkpoint_pub.publish(optimal_checkpoint_markers);

  if(visualize_path){    
    g_traj_lanelet_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_lanelets_viz", 1, true);
    g_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_viz", 1, true);
    opt_traj_lanelet_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/optimal_traj_lanelets_viz", 1, true);
    opt_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/optimal_traj_viz", 1, true);
    entire_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/entire_traj_viz", 1, true);
    entire_joker_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/entire_joker_viz", 1, true);
    viz_timer = nh_.createTimer(ros::Duration(5.0), &MapLoader::viz_pub,this);    
  }

  global_traj_available = false;    
  local_traj_available = false;  
  optimal_traj_available = false;
  entire_traj_available = false;
  entire_joker_availble = false;
  load_map();
  bool map_fix;
  nh_p_.param<bool>("map_fix", map_fix, true);
  if(map_fix){
    fix_and_save_osm();    
  }

  lanelet::traffic_rules::TrafficRulesPtr trafficRules =
  lanelet::traffic_rules::TrafficRulesFactory::create(lanelet::Locations::Germany, lanelet::Participants::Vehicle);
  routingGraph = lanelet::routing::RoutingGraph::build(*map, *trafficRules);  
  j_routingGraph = lanelet::routing::RoutingGraph::build(*j_map, *trafficRules);  
  o_routingGraph = lanelet::routing::RoutingGraph::build(*o_map, *trafficRules);  
  
  construct_lanelets_with_viz();
  construct_lanelets_with_viz_opt();

  g_traj_timer = nh_.createTimer(ros::Duration(5.0), &MapLoader::global_traj_handler,this);
}

MapLoader::~MapLoader()
{}

void MapLoader::global_traj_handler(const ros::TimerEvent& time){
  std_msgs::Int8 map_ver_msg;
  map_ver_msg.data = map_ver;
  map_ver_pub.publish(map_ver_msg);
  if(!global_traj_available){
    compute_global_path();
    // fill_empty_path();    
  }
  if(!optimal_traj_available){
    compute_optimal_path();
  }
  if(!entire_traj_available){
    compute_entire_path();
  }
  if(!pose_init){
      return;
  }
  if(global_traj_available){
    publish_global_path();
    // ROS_INFO("GLOBAL");
  }  
  if(optimal_traj_available){
    publish_optimal_path();
    // ROS_INFO("GLOBAL");
  }  
  if (entire_traj_available){
    publish_entire_path();
  }

}

void MapLoader::convertLatLonToLocal(const std::vector<std::pair<double, double>>& latlon_points, std::vector<std::pair<double, double>>& local_points)
{
    for (const auto& latlon : latlon_points)
    {
        double northing, easting;
        int zone;
        bool northp;
        GeographicLib::UTMUPS::Forward(latlon.first, latlon.second, zone, northp, easting, northing);
        double local_x = easting - origin_easting;
        double local_y = northing - origin_northing;
        local_points.emplace_back(local_x, local_y);
    }
}

void MapLoader::initCheckpoints()
{

//     std::vector<std::vector<std::pair<double, double>>> latlon_o_checkpoints = {
//     // {
//     //     {35.64770559498, 128.40246637842}, {35.64995811374, 128.40036223039}, {35.6518487346, 128.39821545879}, 
//     //     {35.65360099336, 128.3960524943}, {35.65464657734, 128.39266421109}, {35.65647374727, 128.39308967976}, 
//     //     {35.6543745866, 128.39567574932}, {35.65116995552, 128.39931611016}, {35.64854690241, 128.4022942277}, 
//     //     {35.645861136075, 128.404865787815}
//     // },
//     // {
//     //     {35.647711341245, 128.402506213185}, {35.64998465745, 128.40039096299}, {35.65187464874, 128.39824548744}, 
//     //     {35.65363511363, 128.39607494359}, {35.65467840599, 128.39267497978}, {35.65644562565, 128.39307505026}, 
//     //     {35.65434716576, 128.39564870693}, {35.65114363601, 128.39928736587}, {35.64852578624, 128.40226171424}, 
//     //     {35.645859348114996, 128.404832208505}
//     // },
//     {
//         {35.647720436775, 128.40254253793}, {35.65000495309, 128.40042209965}, {35.65189638356, 128.39827510448}, 
//         {35.65365695894, 128.39610365399}, {35.65470878618, 128.39268995296}, {35.65641604272, 128.39306172107}, 
//         {35.65432586494, 128.39561748239}, {35.65112615603, 128.39925192517}, {35.64850549113, 128.40222968182}, 
//         {35.645858298505004, 128.404792776515}
//     }
// };

//     std::vector<std::vector<std::pair<double, double>>> latlon_n_checkpoints = {
//     {
//         {35.64770559498, 128.40246637842}, {35.64995811374, 128.40036223039}, {35.6518487346, 128.39821545879}, 
//         {35.65360099336, 128.3960524943}, {35.65464657734, 128.39266421109}, {35.65647374727, 128.39308967976}, 
//         {35.6543745866, 128.39567574932}, {35.65116995552, 128.39931611016}, {35.64854690241, 128.4022942277}, 
//         {35.645861136075, 128.404865787815}
//     },
//     {
//         {35.647711341245, 128.402506213185}, {35.64998465745, 128.40039096299}, {35.65187464874, 128.39824548744}, 
//         {35.65363511363, 128.39607494359}, {35.65467840599, 128.39267497978}, {35.65644562565, 128.39307505026}, 
//         {35.65434716576, 128.39564870693}, {35.65114363601, 128.39928736587}, {35.64852578624, 128.40226171424}, 
//         {35.645859348114996, 128.404832208505}
//     },
//     {
//         {35.647720436775, 128.40254253793}, {35.65000495309, 128.40042209965}, {35.65189638356, 128.39827510448}, 
//         {35.65365695894, 128.39610365399}, {35.65470878618, 128.39268995296}, {35.65641604272, 128.39306172107}, 
//         {35.65432586494, 128.39561748239}, {35.65112615603, 128.39925192517}, {35.64850549113, 128.40222968182}, 
//         {35.645858298505004, 128.404792776515}
//     }
// };

//     std::vector<std::vector<std::pair<double, double>>> latlon_j_checkpoints = {
//     {
//         {35.64770559498, 128.40246637842}, {35.64995811374, 128.40036223039}, {35.6518487346, 128.39821545879}, 
//         {35.6537989788, 128.39600072627}, {35.6547540664, 128.39273579862}, {35.65647374727, 128.39308967976}, 
//         {35.6543745866, 128.39567574932}, {35.65116995552, 128.39931611016}, {35.64854690241, 128.4022942277}, 
//         {35.645861136075, 128.404865787815}
//     },
//     {
//         {35.647711341245, 128.402506213185}, {35.64998465745, 128.40039096299}, {35.65187464874, 128.39824548744}, 
//         {35.65382514048, 128.3960282288}, {35.65478475867, 128.39274149865}, {35.65644562565, 128.39307505026}, 
//         {35.65434716576, 128.39564870693}, {35.65114363601, 128.39928736587}, {35.64852578624, 128.40226171424}, 
//         {35.645859348114996, 128.404832208505}
//     },
//     {
//         {35.647720436775, 128.40254253793}, {35.65000495309, 128.40042209965}, {35.65189638356, 128.39827510448}, 
//         {35.65384699205, 128.39605926351}, {35.65481836119, 128.39274357856}, {35.65641604272, 128.39306172107}, 
//         {35.65432586494, 128.39561748239}, {35.65112615603, 128.39925192517}, {35.64850549113, 128.40222968182}, 
//         {35.645858298505004, 128.404792776515}
//     }

    
// };


    std::vector<std::vector<std::pair<double, double>>> latlon_o_checkpoints = {
        // {
        //     {35.64815342844, 128.40235359544},
        //     {35.64999711258, 128.40041523203},
        //     {35.65251640214, 128.39756174232},
        //     {35.65330456316, 128.39662876816},
        //     {35.65460437902, 128.39306674827},
        //     {35.65651853871, 128.39213904201},
        //     {35.65448035203, 128.39566113695},
        //     {35.65145606765, 128.39911320063},
        //     {35.64881384532, 128.40211503927},
        //     {35.64589819108, 128.40492960309}
        // },
        // {
        //     {35.64816447921, 128.40239655403},
        //     {35.65002627205, 128.40044544083},
        //     {35.65254054554, 128.39759842129},
        //     {35.65333152183, 128.39666474665},
        //     {35.65463560635, 128.393083264},
        //     {35.65649674395, 128.39215679362},
        //     {35.65445974043, 128.39562872954},
        //     {35.65143278581, 128.39908104883},
        //     {35.64878996522, 128.40208154112},
        //     {35.64589669615, 128.40489766358}
        // },
        // {
        //     {35.64830458537, 128.40235527536},
        //     {35.65005355093, 128.40049217724},
        //     {35.65256375177, 128.39762727616},
        //     {35.65335100715, 128.39669357979},
        //     {35.6546668809, 128.3930971623},
        //     {35.65646943715, 128.39217268352},
        //     {35.65443332695, 128.39559724521},
        //     {35.65139792236, 128.39905049279},
        //     {35.64875992461, 128.40204557032},
        //     {35.64589938084, 128.40485798958}
        // }

        {
            {35.64816447921, 128.40239655403},
            {35.65002627205, 128.40044544083},
            {35.65254054554, 128.39759842129},
            {35.65463560635, 128.393083264},
            {35.65649674395, 128.39215679362},
            {35.65445974043, 128.39562872954},
            {35.65143278581, 128.39908104883},
            {35.64878996522, 128.40208154112},
            {35.64589669615, 128.40489766358}
        }
    };


    std::vector<std::vector<std::pair<double, double>>> latlon_n_checkpoints = {
        {
            {35.64826502131, 128.40226397491},
            {35.64999711258, 128.40041523203},
            {35.65251640214, 128.39756174232},
            {35.65330456316, 128.39662876816},
            {35.65460437902, 128.39306674827},
            {35.65651853871, 128.39213904201},
            {35.65448035203, 128.39566113695},
            {35.65145606765, 128.39911320063},
            {35.64881384532, 128.40211503927},
            {35.64589819108, 128.40492960309}
        },
        {
            {35.64829122656, 128.40231834421},
            {35.65002627205, 128.40044544083},
            {35.65254054554, 128.39759842129},
            {35.65333152183, 128.39666474665},
            {35.65463560635, 128.393083264},
            {35.65649674395, 128.39215679362},
            {35.65445974043, 128.39562872954},
            {35.65143278581, 128.39908104883},
            {35.64878996522, 128.40208154112},
            {35.64589669615, 128.40489766358}
        },
        {
            {35.64830458537, 128.40235527536},
            {35.65005355093, 128.40049217724},
            {35.65256375177, 128.39762727616},
            {35.65335100715, 128.39669357979},
            {35.6546668809, 128.3930971623},
            {35.65646943715, 128.39217268352},
            {35.65443332695, 128.39559724521},
            {35.65139792236, 128.39905049279},
            {35.64875992461, 128.40204557032},
            {35.64589938084, 128.40485798958}
        }
    };

    std::vector<std::vector<std::pair<double, double>>> latlon_j_checkpoints = {
        {
            {35.64826502131, 128.40226397491},
            {35.64999711258, 128.40041523203},
            {35.65251640214, 128.39756174232},
            {35.65384603988, 128.39604648808},
            {35.65479484148, 128.39278349681},
            {35.65651853871, 128.39213904201},
            {35.65448035203, 128.39566113695},
            {35.65145606765, 128.39911320063},
            {35.64881384532, 128.40211503927},
            {35.64589819108, 128.40492960309}
        },
        {
            {35.64829122656, 128.40231834421},
            {35.65002627205, 128.40044544083},
            {35.65254054554, 128.39759842129},
            {35.65387484739, 128.3960746214},
            {35.65482934551, 128.39278716403},
            {35.65649674395, 128.39215679362},
            {35.65445974043, 128.39562872954},
            {35.65143278581, 128.39908104883},
            {35.64878996522, 128.40208154112},
            {35.64589669615, 128.40489766358}
        },
        {
            {35.64830458537, 128.40235527536},
            {35.65005355093, 128.40049217724},
            {35.65256375177, 128.39762727616},
            {35.65389444928, 128.39610509752},
            {35.65486095069, 128.39278633709},
            {35.65646943715, 128.39217268352},
            {35.65443332695, 128.39559724521},
            {35.65139792236, 128.39905049279},
            {35.64875992461, 128.40204557032},
            {35.64589938084, 128.40485798958}
        }
    };

    std::vector<std::vector<std::pair<double, double>>> latlon_End_checkpoints = {
      {{35.64800213467, 128.4024240964}},
      {{35.64801532669,128.40246630771}},
      {{35.64802703312, 128.40250258608}}
    };


    // Convert to local coordinates
    for (const auto& latlon_points : latlon_o_checkpoints)
    {
        std::vector<std::pair<double, double>> local_points;
        convertLatLonToLocal(latlon_points, local_points);
        o_checkpoints.push_back(local_points);
    }
    for (const auto& latlon_points : latlon_n_checkpoints)
    {
        std::vector<std::pair<double, double>> local_points;
        convertLatLonToLocal(latlon_points, local_points);
        n_checkpoints.push_back(local_points);
    }
    for (const auto& latlon_points : latlon_j_checkpoints)
    {
        std::vector<std::pair<double, double>> local_points;
        convertLatLonToLocal(latlon_points, local_points);
        j_checkpoints.push_back(local_points);
    }
    for (const auto& latlon_points : latlon_End_checkpoints)
    {
        std::vector<std::pair<double, double>> local_points;
        convertLatLonToLocal(latlon_points, local_points);
        End_checkpoints.push_back(local_points);
    }
}


// float MapLoader::calculate_distance_pose2global(int current_checkpoint) {
//     float min_dist = 1000.0;
//     float dist = 1000.0;

//     if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction || currentMission == 10 || currentMission == 11) {
//         candidate_lane_arrays = previous_lane_arrays;
//     } else if (currentMission <= 2 || currentMission == 8 || currentMission == 9) {
//         candidate_lane_arrays = j_candidate_lane_arrays;
//     } else {
//         candidate_lane_arrays = n_candidate_lane_arrays;
//     }

//     for (int i = 0; i < candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints.size() * 0.8; i++) {
//         dist = distance(candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.x,
//                         candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.y, pose_x, pose_y);
//         if (min_dist > dist) min_dist = dist;
//     }

//     return min_dist;
// }

// float MapLoader::calculate_distance_pose2optimal(int current_checkpoint) {
//     float min_dist = 1000.0;
//     float dist = 1000.0;

//     if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction || currentMission == 10 || currentMission == 11) {
//         optimal_candidate_lane_arrays = previous_optimal_lane_arrays;
//     } else if (currentMission <= 2 || currentMission == 8 || currentMission == 9) {
//         optimal_candidate_lane_arrays = j_o_candidate_lane_arrays;
//     } else {
//         optimal_candidate_lane_arrays = o_candidate_lane_arrays;
//     }

//     for (int i = 0; i < optimal_candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints.size() * 0.8; i++) {
//         dist = distance(optimal_candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.x,
//                         optimal_candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.y, pose_x, pose_y);
//         if (min_dist > dist) min_dist = dist;
//     }

//     return min_dist;
// }

float MapLoader::calculate_distance_pose2global(int current_checkpoint) {
    float min_dist = 1000.0;
    float dist = 1000.0;

    if (PolygonFlag.isinBuilding) {
        candidate_lane_arrays = previous_lane_arrays;
    } else if (currentMission == "MissionInit" ||
              currentMission == "VehicleReady" || 
              currentMission == "StartFromPitStop" || 
              currentMission == "MissionComplete" || 
              currentMission == "PitStop") {
        candidate_lane_arrays = j_candidate_lane_arrays;
    } else {
        candidate_lane_arrays = n_candidate_lane_arrays;
    }

    for (int i = 0; i < candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints.size() * 0.8; i++) {
        dist = distance(candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.x,
                        candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.y, pose_x, pose_y);
        if (min_dist > dist) min_dist = dist;
    }

    return min_dist;
}

float MapLoader::calculate_distance_pose2optimal(int current_checkpoint) {
    float min_dist = 1000.0;
    float dist = 1000.0;

    if (PolygonFlag.isinBuilding) {
        optimal_candidate_lane_arrays = previous_optimal_lane_arrays;
    } else if (currentMission == "MissionInit" ||
              currentMission == "VehicleReady" || 
              currentMission == "StartFromPitStop" || 
              currentMission == "MissionComplete" || 
              currentMission == "PitStop") {
        optimal_candidate_lane_arrays = j_o_candidate_lane_arrays;
    } else {
        optimal_candidate_lane_arrays = o_candidate_lane_arrays;
    }

    for (int i = 0; i < optimal_candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints.size() * 0.8; i++) {
        dist = distance(optimal_candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.x,
                        optimal_candidate_lane_arrays.lanearrays[current_checkpoint].lanes[0].waypoints[i].pose.pose.position.y, pose_x, pose_y);
        if (min_dist > dist) min_dist = dist;
    }

    return min_dist;
}

// void MapLoader::check_current_pose() {
//     float check_dist = 8.0;
//     std::vector<float> dist;
//     std::vector<float> dist2glob;
//     int current_checkpoint = 0;

//     if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction || currentMission == 10 || currentMission == 11) {
//         checkpoints = previous_checkpoints;
//     } else if (currentMission <= 2 || currentMission == 8 || currentMission == 9) {
//         checkpoints = j_checkpoints;
//     } else {
//         checkpoints = n_checkpoints;
//     }

//     for (int i = 0; i < checkpoints[0].size(); i++) {
//         dist.push_back(distance(checkpoints[0][i].first, checkpoints[0][i].second, pose_x, pose_y));
//     }
//     for (int i = 0; i < checkers.size(); i++) {
//         if (checkers[i]) current_checkpoint = i;
//     }
//     float dist2curlane = calculate_distance_pose2global(current_checkpoint);
//     if (dist2curlane > check_dist) {
//         for (int i = 0; i < checkpoints[0].size(); i++) {
//             dist2glob.push_back(calculate_distance_pose2global(i));
//         }
//         float min_dist2glob = *min_element(dist2glob.begin(), dist2glob.end());
//         float min_idx = min_element(dist2glob.begin(), dist2glob.end()) - dist2glob.begin();
//         // ROS_INFO("global distance: %f, %f, %f, %f", dist2glob[0], dist2glob[1], dist2glob[2], dist2glob[3]);
//         std::fill(checkers.begin(), checkers.end(), false);
//         checkers[min_idx] = true;
//     } else {
//         for (int i = 0; i < checkers.size(); i++) {
//             if (!checkers[i] && dist[i] < check_dist) {
//                 std::fill(checkers.begin(), checkers.end(), false);
//                 checkers[i] = true;
//                 break;
//             }
//         }
//     }
// }


// void MapLoader::check_current_pose_opt() {
//     float check_dist = 8.0;
//     std::vector<float> dist;
//     std::vector<float> dist2glob;
//     int current_checkpoint = 0;

//     if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction || currentMission == 10 || currentMission == 11) {
//         optimal_checkpoints = previous_optimal_checkpoints;
//     } else if (currentMission <= 2 || currentMission == 8 || currentMission == 9) {
//         optimal_checkpoints = j_checkpoints;
//     } else {
//         optimal_checkpoints = o_checkpoints;
//     }

//     for (int i = 0; i < optimal_checkpoints[0].size(); i++) {
//         dist.push_back(distance(optimal_checkpoints[0][i].first, optimal_checkpoints[0][i].second, pose_x, pose_y));
//     }
//     for (int i = 0; i < opt_checkers.size(); i++) {
//         if (opt_checkers[i]) current_checkpoint = i;
//     }
//     float dist2curlane = calculate_distance_pose2optimal(current_checkpoint);
//     if (dist2curlane > check_dist) {
//         for (int i = 0; i < optimal_checkpoints[0].size(); i++) {
//             dist2glob.push_back(calculate_distance_pose2optimal(i));
//         }
//         float min_dist2glob = *min_element(dist2glob.begin(), dist2glob.end());
//         float min_idx = min_element(dist2glob.begin(), dist2glob.end()) - dist2glob.begin();
//         // ROS_INFO("global distance: %f, %f, %f, %f", dist2glob[0], dist2glob[1], dist2glob[2], dist2glob[3]);
//         std::fill(opt_checkers.begin(), opt_checkers.end(), false);
//         opt_checkers[min_idx] = true;
//     } else {
//         for (int i = 0; i < opt_checkers.size(); i++) {
//             if (!opt_checkers[i] && dist[i] < check_dist) {
//                 std::fill(opt_checkers.begin(), opt_checkers.end(), false);
//                 opt_checkers[i] = true;
//                 break;
//             }
//         }
//     }
// }

void MapLoader::check_current_pose() {
    float check_dist = 8.0;
    std::vector<float> dist;
    std::vector<float> dist2glob;
    int current_checkpoint = 0;

    if (PolygonFlag.isinBuilding) {
        checkpoints = previous_checkpoints;
    } else if (currentMission == "MissionInit" ||
              currentMission == "VehicleReady" || 
              currentMission == "StartFromPitStop" || 
              currentMission == "MissionComplete" || 
              currentMission == "PitStop") {
        checkpoints = j_checkpoints;
    } else {
        checkpoints = n_checkpoints;
    }

    for (int i = 0; i < checkpoints[0].size(); i++) {
        dist.push_back(distance(checkpoints[0][i].first, checkpoints[0][i].second, pose_x, pose_y));
    }
    for (int i = 0; i < checkers.size(); i++) {
        if (checkers[i]) current_checkpoint = i;
    }
    float dist2curlane = calculate_distance_pose2global(current_checkpoint);
    if (dist2curlane > check_dist) {
        for (int i = 0; i < checkpoints[0].size(); i++) {
            dist2glob.push_back(calculate_distance_pose2global(i));
        }
        float min_dist2glob = *min_element(dist2glob.begin(), dist2glob.end());
        float min_idx = min_element(dist2glob.begin(), dist2glob.end()) - dist2glob.begin();
        // ROS_INFO("global distance: %f, %f, %f, %f", dist2glob[0], dist2glob[1], dist2glob[2], dist2glob[3]);
        std::fill(checkers.begin(), checkers.end(), false);
        checkers[min_idx] = true;
    } else {
        for (int i = 0; i < checkers.size(); i++) {
            if (!checkers[i] && dist[i] < check_dist) {
                std::fill(checkers.begin(), checkers.end(), false);
                checkers[i] = true;
                break;
            }
        }
    }
}


void MapLoader::check_current_pose_opt() {
    float check_dist = 8.0;
    std::vector<float> dist;
    std::vector<float> dist2glob;
    int current_checkpoint = 0;

    if (PolygonFlag.isinBuilding) {
        optimal_checkpoints = previous_optimal_checkpoints;
    } else if (currentMission == "MissionInit" ||
              currentMission == "VehicleReady" || 
              currentMission == "StartFromPitStop" || 
              currentMission == "MissionComplete" || 
              currentMission == "PitStop") {
        optimal_checkpoints = j_checkpoints;
    } else {
        optimal_checkpoints = o_checkpoints;
    }

    for (int i = 0; i < optimal_checkpoints[0].size(); i++) {
        dist.push_back(distance(optimal_checkpoints[0][i].first, optimal_checkpoints[0][i].second, pose_x, pose_y));
    }
    for (int i = 0; i < opt_checkers.size(); i++) {
        if (opt_checkers[i]) current_checkpoint = i;
    }
    float dist2curlane = calculate_distance_pose2optimal(current_checkpoint);
    if (dist2curlane > check_dist) {
        for (int i = 0; i < optimal_checkpoints[0].size(); i++) {
            dist2glob.push_back(calculate_distance_pose2optimal(i));
        }
        float min_dist2glob = *min_element(dist2glob.begin(), dist2glob.end());
        float min_idx = min_element(dist2glob.begin(), dist2glob.end()) - dist2glob.begin();
        // ROS_INFO("global distance: %f, %f, %f, %f", dist2glob[0], dist2glob[1], dist2glob[2], dist2glob[3]);
        std::fill(opt_checkers.begin(), opt_checkers.end(), false);
        opt_checkers[min_idx] = true;
    } else {
        for (int i = 0; i < opt_checkers.size(); i++) {
            if (!opt_checkers[i] && dist[i] < check_dist) {
                std::fill(opt_checkers.begin(), opt_checkers.end(), false);
                opt_checkers[i] = true;
                break;
            }
        }
    }
}


// void MapLoader::publish_global_path() {
//     if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction || currentMission == 10 || currentMission == 11) {
//         ROS_INFO("Bank detected, using previous checkpoints and lane arrays");
//         checkpoints = previous_checkpoints;
//         candidate_lane_arrays.lanearrays.clear();
//         candidate_lane_arrays = previous_lane_arrays;
//     } else if (currentMission <= 2 || currentMission == 8 || currentMission == 9) {
//         ROS_INFO("check joker");
//         checkpoints = j_checkpoints;
//         candidate_lane_arrays.lanearrays.clear();
//         candidate_lane_arrays = j_candidate_lane_arrays;
//     } else {
//         ROS_INFO("check ");
//         checkpoints = n_checkpoints;
//         candidate_lane_arrays.lanearrays.clear();
//         candidate_lane_arrays = n_candidate_lane_arrays;
//     }

//     for (int i = 0; i < checkpoints[0].size(); i++) {
//         if (checkers[i]) {
//             ROS_INFO("Checker %d", i);
            
//             global_lane_array = candidate_lane_arrays.lanearrays[i];
//             way_pub.publish(global_lane_array);
//             global_marker_array = visualize_global_path(global_lane_array);
//             g_traj_viz_pub.publish(global_marker_array);
//             break;
//         }
//     }

//     // Update the previous checkpoints and lane arrays with current ones
//     previous_checkpoints = checkpoints;
//     previous_lane_arrays = candidate_lane_arrays;
// }

// void MapLoader::publish_optimal_path() {
//     if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction || currentMission == 10 || currentMission == 11) {
//         ROS_INFO("Bank detected, using previous optimal checkpoints and lane arrays");
//         optimal_checkpoints = previous_optimal_checkpoints;
//         optimal_candidate_lane_arrays.lanearrays.clear();
//         optimal_candidate_lane_arrays = previous_optimal_lane_arrays;
//     } else if (currentMission <= 2 || currentMission == 8 || currentMission == 9) {
//         ROS_INFO("check joker");
//         optimal_checkpoints = j_checkpoints;
//         optimal_candidate_lane_arrays.lanearrays.clear();
//         optimal_candidate_lane_arrays = j_o_candidate_lane_arrays;
//     } else {
//         ROS_INFO("check ");
//         optimal_checkpoints = o_checkpoints;
//         optimal_candidate_lane_arrays.lanearrays.clear();
//         optimal_candidate_lane_arrays = o_candidate_lane_arrays;
//     }

//     for (int i = 0; i < optimal_checkpoints[0].size(); i++) {
//         if (opt_checkers[i]) {
//             // ROS_INFO("Checker %d", i);
            
//             optimal_lane_array = optimal_candidate_lane_arrays.lanearrays[i];
//             optimal_pub.publish(optimal_lane_array);
//             optimal_marker_array = visualize_optimal_path(optimal_lane_array);
//             opt_traj_viz_pub.publish(optimal_marker_array);
//             break;
//         }
//     }

//     // Update the previous checkpoints and lane arrays with current ones
//     previous_optimal_checkpoints = optimal_checkpoints;
//     previous_optimal_lane_arrays = optimal_candidate_lane_arrays;
// }

void MapLoader::publish_global_path() {
    if (PolygonFlag.isinBuilding) {
        ROS_INFO("Building detected, using previous checkpoints and lane arrays");
        checkpoints = previous_checkpoints;
        candidate_lane_arrays.lanearrays.clear();
        candidate_lane_arrays = previous_lane_arrays;
    } else if (currentMission == "MissionInit" ||
              currentMission == "VehicleReady" || 
              currentMission == "StartFromPitStop" || 
              currentMission == "MissionComplete" || 
              currentMission == "PitStop") {
        ROS_INFO("check joker");
        checkpoints = j_checkpoints;
        candidate_lane_arrays.lanearrays.clear();
        candidate_lane_arrays = j_candidate_lane_arrays;
    } else {
        ROS_INFO("check ");
        checkpoints = n_checkpoints;
        candidate_lane_arrays.lanearrays.clear();
        candidate_lane_arrays = n_candidate_lane_arrays;
    }

    for (int i = 0; i < checkpoints[0].size(); i++) {
        if (checkers[i]) {
            ROS_INFO("Checker %d", i);
            
            global_lane_array = candidate_lane_arrays.lanearrays[i];
            way_pub.publish(global_lane_array);
            global_marker_array = visualize_global_path(global_lane_array);
            g_traj_viz_pub.publish(global_marker_array);
            break;
        }
    }

    // Update the previous checkpoints and lane arrays with current ones
    previous_checkpoints = checkpoints;
    previous_lane_arrays = candidate_lane_arrays;
}

void MapLoader::publish_optimal_path() {
    // if (PolygonFlag.isinBuilding) {
    //     ROS_INFO("Building detected, using previous optimal checkpoints and lane arrays");
    //     optimal_checkpoints = previous_optimal_checkpoints;
    //     optimal_candidate_lane_arrays.lanearrays.clear();
    //     optimal_candidate_lane_arrays = previous_optimal_lane_arrays;
    // } else if (currentMission == "MissionInit" ||
    //           currentMission == "VehicleReady" || 
    //           currentMission == "StartFromPitStop" || 
    //           currentMission == "MissionComplete" || 
    //           currentMission == "PitStop") {
    //     ROS_INFO("check joker");
    //     optimal_checkpoints = j_checkpoints;
    //     optimal_candidate_lane_arrays.lanearrays.clear();
    //     optimal_candidate_lane_arrays = j_o_candidate_lane_arrays;
    // } else {
    //     ROS_INFO("check ");
    //     optimal_checkpoints = o_checkpoints;
    //     optimal_candidate_lane_arrays.lanearrays.clear();
    //     optimal_candidate_lane_arrays = o_candidate_lane_arrays;
    // }

    // for (int i = 0; i < optimal_checkpoints[0].size(); i++) {
    //     if (opt_checkers[i]) {
    //         // ROS_INFO("Checker %d", i);
            
    //         optimal_lane_array = optimal_candidate_lane_arrays.lanearrays[i];
    //         optimal_pub.publish(optimal_lane_array);
    //         optimal_marker_array = visualize_optimal_path(optimal_lane_array);
    //         opt_traj_viz_pub.publish(optimal_marker_array);
    //         break;
    //     }
    // }
    for (int i = 0; i < checkpoints[0].size(); i++) {
        if (checkers[i]) {
            ROS_INFO("Checker %d", i);
            optimal_lane_array.lanes.clear();
            optimal_lane_array.lanes.push_back(candidate_lane_arrays.lanearrays[i].lanes[0]);
            optimal_pub.publish(optimal_lane_array);
            optimal_marker_array = visualize_optimal_path(optimal_lane_array);
            opt_traj_viz_pub.publish(optimal_marker_array);
            break;
        }
    }
    // // Update the previous checkpoints and lane arrays with current ones
    // previous_optimal_checkpoints = optimal_checkpoints;
    // previous_optimal_lane_arrays = optimal_candidate_lane_arrays;
}

void MapLoader::publish_entire_path() {
  entire_lane_array = entire_lane_arrays.lanearrays[0];
  entire_traj_pub.publish(entire_lane_array);
  entire_traj_marker_array = visualize_entire_path(entire_lane_array);
  entire_traj_viz_pub.publish(entire_traj_marker_array);

  entire_joker_array = entire_joker_arrays.lanearrays[0];
  entire_joker_pub.publish(entire_joker_array);
  entire_joker_traj_marker_array = visualize_entire_joker_path(entire_joker_array);
  entire_joker_viz_pub.publish(entire_joker_traj_marker_array);
}

double MapLoader::distance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
}


void MapLoader::publishSubtype(const ros::TimerEvent&) {
    if (!pose_init) {
        return;
    }

    std::thread(&MapLoader::performSubtypeCheck, this).detach();
}

void MapLoader::performSubtypeCheck() {
    auto start = std::chrono::high_resolution_clock::now();

    PolygonFlag.header.stamp = ros::Time::now();
    PolygonFlag.header.frame_id = "map";

    PolygonFlag.isinJunction = false;
    PolygonFlag.isinExit = false;
    PolygonFlag.isinBank = false;
    PolygonFlag.isinFreespace = false;
    PolygonFlag.isinCrosswalk = false;
    PolygonFlag.isinStopline = false;
    PolygonFlag.isinTrafficIsland = false;
    PolygonFlag.isinParking = false;
    PolygonFlag.isinBuilding = false;

    lanelet::BasicPoint2d point(cur_pose.position.x, cur_pose.position.y);

    for (const auto& area : areas) {
        if (lanelet::geometry::inside(area, point)) {
            lanelet::Attribute attr = area.attribute(lanelet::AttributeName::Subtype);
            if (attr.value() == lanelet::AttributeValueString::Junction) {
                PolygonFlag.isinJunction = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Exit) {
                PolygonFlag.isinExit = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Bank) {
                PolygonFlag.isinBank = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Freespace) {
                PolygonFlag.isinFreespace = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Crosswalk) {
                PolygonFlag.isinCrosswalk = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Stopline) {
                PolygonFlag.isinStopline = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Parking) {
                PolygonFlag.isinParking = true;
            }
            if (attr.value() == lanelet::AttributeValueString::TrafficIsland) {
                PolygonFlag.isinTrafficIsland = true;
            }
            if (attr.value() == lanelet::AttributeValueString::Building) {
                PolygonFlag.isinBuilding = true;
            }
        }
    }

    subtype_pub.publish(PolygonFlag);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // ROS_INFO("performSubtypeCheck took %f seconds", duration.count());
}



void MapLoader::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg) {
    if (!pose_init) {
        ROS_INFO("Current Pose is initialized");
        pose_init = true;
    }
    cur_pose = msg->pose;
    
    pose_x = msg->pose.position.x;
    pose_y = msg->pose.position.y;
    pose_z = msg->pose.position.z;

    if (global_traj_available) {
        check_current_pose();
    }
    if (optimal_traj_available) {
        check_current_pose_opt();
    }
}

void MapLoader::compute_global_path(){

  candidate_lane_arrays.lanearrays.clear();
  n_candidate_lane_arrays.lanearrays.clear();
  j_candidate_lane_arrays.lanearrays.clear();

  for(int k=0; k<2; k++){
    if(k==0){
      rp_.setMap(map);
      checkpoints = n_checkpoints;
      road_lanelets_const = n_road_lanelets_const;
    }
    else{
      rp_.setMap(j_map);
      checkpoints = j_checkpoints;
      road_lanelets_const = j_road_lanelets_const;
    }
    for(int n=0; n<checkpoints.size(); n++){
      xyz = checkpoints[n];
      xyz.push_back(checkpoints[n][0]);
      xyz.push_back(checkpoints[n][1]);

      for(int t=0; t<xyz.size()-2; t++){
        pose_a.position.x = xyz[t].first;
        pose_a.position.y = xyz[t].second;
        pose_b.position.x = xyz[t+2].first;
        pose_b.position.y = xyz[t+2].second;
        hmcl_msgs::LaneArray lane_array;
        lane_array.lanes.clear();
        lane_array.header.frame_id = "map";
        lane_array.header.stamp = ros::Time::now();
        hmcl_msgs::Lane ll_;  
        ll_.header = lane_array.header;
        if(road_lanelets_const.size() > 0){
          int start_closest_lane_idx = get_closest_lanelet(road_lanelets_const,pose_a);      
          int goal_closest_lane_idx = get_closest_lanelet(road_lanelets_const,pose_b);
          // lanelet::Optional<lanelet::routing::LaneletPath> route = routingGraph->shortestPath(road_lanelets[start_closest_lane_idx], road_lanelets[goal_closest_lane_idx], 1);
          if(k==0){
            route = routingGraph->getRoute(road_lanelets_const[start_closest_lane_idx], road_lanelets_const[goal_closest_lane_idx], 0);
          }
          else{
            route = j_routingGraph->getRoute(road_lanelets_const[start_closest_lane_idx], road_lanelets_const[goal_closest_lane_idx], 0);
          }
          if(!route){
            ROS_WARN("[MAP_LOADER] = Route is not found");      
            return;
          }
          lanelet::routing::LaneletPath local_path = route->shortestPath();
          if(k==0){
            routingGraph->checkValidity();      
          }
          else{
            j_routingGraph->checkValidity();      
          }
          ROS_INFO("shortest path_size = %d", local_path.size());
          if(local_path.empty()){
            ROS_WARN("[MAP_LOADER] = Path is not found");        
          }
          else{
            // Create base trajectory           
                                  
            int _lane_idx = 0;


            for (int i =0; i < local_path.size() ; i++){                
              double speed_limit = local_path[i].attributeOr("speed_limit",-1.0);                
              ll_.speed_limit = speed_limit;

              ///////////////////////// Encode waypoints  /////////////////////////////////////////              
              auto lstring = local_path[i].centerline();   
              double yaw_tmp;               
              int waypoint_idx_init = 1;
              int waypoint_idx_finish = lstring.size();
              // initial lanelet , add current position as the waypoint
              // ROS_INFO("lstring = %d", lstring.size());


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
                for(int h=0; h<areas.size(); h++){
                  lanelet::Area area = areas[h];
                  if(lanelet::geometry::inside(area,lanelet::BasicPoint2d(wp_.pose.pose.position.x,wp_.pose.pose.position.y))){
                    lanelet::Attribute attr = area.attribute(lanelet::AttributeName::Subtype);
                    if(attr.value() == lanelet::AttributeValueString::Bank){
                      wp_.bank = true;
                    }
                    if(attr.value() == lanelet::AttributeValueString::Junction){
                      wp_.junction = true;
                    }
                  }
                }
                ll_.waypoints.push_back(wp_);
              }
                
            }  
            global_traj_available = true;
            if(n==0){
              lane_array.lanes.push_back(ll_);
              if(k==0) n_candidate_lane_arrays.lanearrays.push_back(lane_array);
              else{
                j_candidate_lane_arrays.lanearrays.push_back(lane_array);
                candidate_lane_arrays.lanearrays.push_back(lane_array);
              }
            }
            else{
              if(k==0) n_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
              else{
                j_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
                candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
              }
            }
          }
          previous_lane_arrays = j_candidate_lane_arrays;
        }
        else{
          ROS_WARN("[MAP_LOADER] = Current pose is not initialized or map is not loaded");
        }
        
      }
    }
  }
}



// void MapLoader::compute_optimal_path(){

//   optimal_candidate_lane_arrays.lanearrays.clear();
//   o_candidate_lane_arrays.lanearrays.clear();
//   j_candidate_lane_arrays.lanearrays.clear();
  
//   for(int k=0; k<2; k++){
//     if(k==0){
//       rp_.setMap(o_map);
//       optimal_checkpoints = o_checkpoints;
//       optimal_road_lanelets_const = o_road_lanelets_const;
//     }
//     else{
//       rp_.setMap(j_map);
//       optimal_checkpoints = j_checkpoints;
//       optimal_road_lanelets_const = j_road_lanelets_const;
//     }
//     for(int n=0; n<optimal_checkpoints.size(); n++){
//       xyz = optimal_checkpoints[n];
//       xyz.push_back(optimal_checkpoints[n][0]);
//       xyz.push_back(optimal_checkpoints[n][1]);

//       for(int t=0; t<xyz.size()-2; t++){
//         pose_a.position.x = xyz[t].first;
//         pose_a.position.y = xyz[t].second;
//         pose_b.position.x = xyz[t+2].first;
//         pose_b.position.y = xyz[t+2].second;
//         hmcl_msgs::LaneArray lane_array;
//         lane_array.lanes.clear();
//         lane_array.header.frame_id = "map";
//         lane_array.header.stamp = ros::Time::now();
//         hmcl_msgs::Lane ll_;  
//         ll_.header = lane_array.header;
//         if(optimal_road_lanelets_const.size() > 0){
//           int start_closest_lane_idx = get_closest_lanelet(optimal_road_lanelets_const,pose_a);      
//           int goal_closest_lane_idx = get_closest_lanelet(optimal_road_lanelets_const,pose_b);
//           // lanelet::Optional<lanelet::routing::LaneletPath> route = routingGraph->shortestPath(road_lanelets[start_closest_lane_idx], road_lanelets[goal_closest_lane_idx], 1);
//           if(k==0){
//             opt_route = o_routingGraph->getRoute(optimal_road_lanelets_const[start_closest_lane_idx], optimal_road_lanelets_const[goal_closest_lane_idx], 0);
//           }
//           else{
//             opt_route = j_routingGraph->getRoute(optimal_road_lanelets_const[start_closest_lane_idx], optimal_road_lanelets_const[goal_closest_lane_idx], 0);
//           }
//           if(!opt_route){
//             ROS_WARN("[MAP_LOADER] = Route is not found");      
//             return;
//           }
//           lanelet::routing::LaneletPath local_path = opt_route->shortestPath();
//           if(k==0){
//             o_routingGraph->checkValidity();      
//           }
//           else{
//             j_routingGraph->checkValidity();      
//           }
//           ROS_INFO("shortest path_size = %d", local_path.size());
//           if(local_path.empty()){
//             ROS_WARN("[MAP_LOADER] = Path is not found");        
//           }
//           else{
//             // Create base trajectory           
                                  
//             int _lane_idx = 0;


//             for (int i =0; i < local_path.size() ; i++){                
//               double speed_limit = local_path[i].attributeOr("speed_limit",-1.0);                
//               ll_.speed_limit = speed_limit;

//               ///////////////////////// Encode waypoints  /////////////////////////////////////////              
//               auto lstring = local_path[i].centerline();   
//               double yaw_tmp;               
//               int waypoint_idx_init = 1;
//               int waypoint_idx_finish = lstring.size();
//               // initial lanelet , add current position as the waypoint
//               // ROS_INFO("lstring = %d", lstring.size());


//               for (int j = waypoint_idx_init; j < waypoint_idx_finish; j++ ){
//                 lanelet::ConstPoint3d p1Const = lstring[j]; 
//                 // ROS_INFO("x = %f, y = %f, z = %f", p1Const.x(),p1Const.y(),p1Const.z());
//                 hmcl_msgs::Waypoint wp_;                                    
//                 wp_.lane_id = ll_.lane_id;
//                 wp_.pose.pose.position.x = p1Const.x();
//                 wp_.pose.pose.position.y = p1Const.y();
//                 wp_.pose.pose.position.z = p1Const.z();         
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                 wp_.speed.twist.linear.x = p1Const.attributeOr("velocity", 0.0);
//                 wp_.curvature = p1Const.attributeOr("curvature", 0.0);  
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////

//                 // point within the lanelet, Last point will have the same yaw as the previous waypoint
//                 if(j < lstring.size()-1){      
//                   yaw_tmp = get_yaw(lstring[j], lstring[j+1]);                                    
//                 }else{
//                   yaw_tmp = get_yaw(lstring[j-1], lstring[j]);
//                 }

//                 tf2::Quaternion q;
//                 q.setRPY(0, 0, yaw_tmp);
//                 q=q.normalize();
//                 wp_.pose.pose.orientation.x = q[0];
//                 wp_.pose.pose.orientation.y = q[1];
//                 wp_.pose.pose.orientation.z = q[2];
//                 wp_.pose.pose.orientation.w = q[3];
//                 wp_.twist.twist.linear.x = ll_.speed_limit;
//                 for(int h=0; h<areas.size(); h++){
//                   lanelet::Area area = areas[h];
//                   if(lanelet::geometry::inside(area,lanelet::BasicPoint2d(wp_.pose.pose.position.x,wp_.pose.pose.position.y))){
//                     lanelet::Attribute attr = area.attribute(lanelet::AttributeName::Subtype);
//                     if(attr.value() == lanelet::AttributeValueString::Bank){
//                       wp_.bank = true;
//                     }
//                     if(attr.value() == lanelet::AttributeValueString::Junction){
//                       wp_.junction = true;
//                     }
//                   }
//                 }
//                 ll_.waypoints.push_back(wp_);
//               }
                
//             }  
//             optimal_traj_available = true;
//             if(n==0){
//               lane_array.lanes.push_back(ll_);
//               if(k==0) o_candidate_lane_arrays.lanearrays.push_back(lane_array);
//               else{
//                 j_candidate_lane_arrays.lanearrays.push_back(lane_array);
//                 optimal_candidate_lane_arrays.lanearrays.push_back(lane_array);
//               }
//             }
//             else{
//               if(k==0) o_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
//               else{
//                 j_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
//                 optimal_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
//               }
//             }
//           }
//           previous_optimal_lane_arrays = j_candidate_lane_arrays;
//         }
//         else{
//           ROS_WARN("[MAP_LOADER] = Current pose is not initialized or map is not loaded");
//         }
        
//       }
//     }
//   }
// }


void MapLoader::compute_optimal_path(){

  optimal_candidate_lane_arrays.lanearrays.clear();
  o_candidate_lane_arrays.lanearrays.clear();
  j_o_candidate_lane_arrays.lanearrays.clear();
  
  for(int k=0; k<2; k++){
    if(k==0){
      rp_.setMap(o_map);
      optimal_checkpoints = o_checkpoints;
      optimal_road_lanelets_const = o_road_lanelets_const;
      xyz = optimal_checkpoints[0];
      xyz.push_back(optimal_checkpoints[0][0]);
      xyz.push_back(optimal_checkpoints[0][1]);
    }
    else{
      rp_.setMap(j_map);
      optimal_checkpoints = j_checkpoints;
      optimal_road_lanelets_const = j_road_lanelets_const;\
      xyz = optimal_checkpoints[1];
      xyz.push_back(optimal_checkpoints[1][0]);
      xyz.push_back(optimal_checkpoints[1][1]);
    }
      for(int t=0; t<xyz.size()-2; t++){
        pose_a.position.x = xyz[t].first;
        pose_a.position.y = xyz[t].second;
        pose_b.position.x = xyz[t+2].first;
        pose_b.position.y = xyz[t+2].second;
        hmcl_msgs::LaneArray lane_array;
        lane_array.lanes.clear();
        lane_array.header.frame_id = "map";
        lane_array.header.stamp = ros::Time::now();
        hmcl_msgs::Lane ll_;  
        ll_.header = lane_array.header;
        if(optimal_road_lanelets_const.size() > 0){
          int start_closest_lane_idx = get_closest_lanelet(optimal_road_lanelets_const,pose_a);      
          int goal_closest_lane_idx = get_closest_lanelet(optimal_road_lanelets_const,pose_b);
          // lanelet::Optional<lanelet::routing::LaneletPath> route = routingGraph->shortestPath(road_lanelets[start_closest_lane_idx], road_lanelets[goal_closest_lane_idx], 1);
          if(k==0){
            opt_route = o_routingGraph->getRoute(optimal_road_lanelets_const[start_closest_lane_idx], optimal_road_lanelets_const[goal_closest_lane_idx], 0);
          }
          else{
            opt_route = j_routingGraph->getRoute(optimal_road_lanelets_const[start_closest_lane_idx], optimal_road_lanelets_const[goal_closest_lane_idx], 0);
          }
          if(!opt_route){
            ROS_WARN("[MAP_LOADER] = Route is not found");      
            return;
          }
          lanelet::routing::LaneletPath local_path = opt_route->shortestPath();
          if(k==0){
            o_routingGraph->checkValidity();      
          }
          else{
            j_routingGraph->checkValidity();      
          }
          ROS_INFO("shortest path_size = %d", local_path.size());
          if(local_path.empty()){
            ROS_WARN("[MAP_LOADER] = Path is not found");        
          }
          else{
            // Create base trajectory           
                                  
            int _lane_idx = 0;


            for (int i =0; i < local_path.size() ; i++){                
              double speed_limit = local_path[i].attributeOr("speed_limit",-1.0);                
              ll_.speed_limit = speed_limit;

              ///////////////////////// Encode waypoints  /////////////////////////////////////////              
              auto lstring = local_path[i].centerline();   
              double yaw_tmp;               
              int waypoint_idx_init = 1;
              int waypoint_idx_finish = lstring.size();
              // initial lanelet , add current position as the waypoint
              // ROS_INFO("lstring = %d", lstring.size());


              for (int j = waypoint_idx_init; j < waypoint_idx_finish; j++ ){
                lanelet::ConstPoint3d p1Const = lstring[j]; 
                // ROS_INFO("x = %f, y = %f, z = %f", p1Const.x(),p1Const.y(),p1Const.z());
                hmcl_msgs::Waypoint wp_;                                    
                wp_.lane_id = ll_.lane_id;
                wp_.pose.pose.position.x = p1Const.x();
                wp_.pose.pose.position.y = p1Const.y();
                wp_.pose.pose.position.z = p1Const.z();         
///////////////////////////////////////////////////////////////////////////////////////////////////////////
                wp_.speed.twist.linear.x = p1Const.attributeOr("velocity", 0.0);
                wp_.curvature = p1Const.attributeOr("curvature", 0.0);  
///////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                for(int h=0; h<areas.size(); h++){
                  lanelet::Area area = areas[h];
                  if(lanelet::geometry::inside(area,lanelet::BasicPoint2d(wp_.pose.pose.position.x,wp_.pose.pose.position.y))){
                    lanelet::Attribute attr = area.attribute(lanelet::AttributeName::Subtype);
                    if(attr.value() == lanelet::AttributeValueString::Bank){
                      wp_.bank = true;
                    }
                    if(attr.value() == lanelet::AttributeValueString::Junction){
                      wp_.junction = true;
                    }
                    
                  }
                }
                ll_.waypoints.push_back(wp_);
              }
                
            }  
            optimal_traj_available = true;
            lane_array.lanes.push_back(ll_);
            if(k==0) o_candidate_lane_arrays.lanearrays.push_back(lane_array);
            else{
              j_o_candidate_lane_arrays.lanearrays.push_back(lane_array);
              optimal_candidate_lane_arrays.lanearrays.push_back(lane_array);
            }
            // else{
            //   if(k==0) o_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
            //   else{
            //     j_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
            //     optimal_candidate_lane_arrays.lanearrays[t].lanes.push_back(ll_);
            //   }
            // }
          }
          previous_optimal_lane_arrays = j_o_candidate_lane_arrays;
        }
        else{
          ROS_WARN("[MAP_LOADER] = Current pose is not initialized or map is not loaded");
        }
        
      }
  }
}

void MapLoader::compute_entire_path(){
  
  // geometry_msgs::Pose first_node, last_node;
  for(int k=0; k<2; k++){
    if(k==0){
      entire_rp.setMap(map);
      checkpoints = n_checkpoints;
      road_lanelets_const = n_road_lanelets_const;
    }
    else{
      entire_rp.setMap(j_map);
      checkpoints = j_checkpoints;
      road_lanelets_const = j_road_lanelets_const;
    }
    for(int n=0; n<checkpoints.size(); n++){  
      xyz = n_checkpoints[n];
      xyz_End = End_checkpoints[n];
      first_node.position.x = xyz[0].first;
      first_node.position.y = xyz[0].second;
      last_node.position.x = xyz_End[0].first;
      last_node.position.y = xyz_End[0].second;

      hmcl_msgs::LaneArray lane_array;
      lane_array.lanes.clear();
      lane_array.header.frame_id = "map";
      lane_array.header.stamp = ros::Time::now();
      hmcl_msgs::Lane ll_;  
      ll_.header = lane_array.header;
      if(road_lanelets_const.size() > 0){
        int start_closest_lane_idx = get_closest_lanelet(road_lanelets_const,first_node);      
        int goal_closest_lane_idx = get_closest_lanelet(road_lanelets_const,last_node);
        if (k==0) {
          entire_route = routingGraph->getRoute(road_lanelets_const[start_closest_lane_idx], road_lanelets_const[goal_closest_lane_idx], 0);
        }
        else {
          entire_route = j_routingGraph->getRoute(road_lanelets_const[start_closest_lane_idx], road_lanelets_const[goal_closest_lane_idx], 0);
        }
        lanelet::routing::LaneletPath local_path = entire_route->shortestPath();
        if(k==0){
            routingGraph->checkValidity();      
          }
        else{
            j_routingGraph->checkValidity();      
        }  
        if(local_path.empty()){
          ROS_WARN("[MAP_LOADER] = Path is not found");        
        }
        else{
          // Create base trajectory           
                                
          int _lane_idx = 0;
          for (int i =0; i < local_path.size() ; i++){                
            double speed_limit = local_path[i].attributeOr("speed_limit",-1.0);                
            ll_.speed_limit = speed_limit;
            ///////////////////////// Encode waypoints  /////////////////////////////////////////              
            auto lstring = local_path[i].centerline();   
            double yaw_tmp;               
            int waypoint_idx_init = 1;
            int waypoint_idx_finish = lstring.size();
            // initial lanelet , add current position as the waypoint
            // ROS_INFO("lstring = %d", lstring.size());
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
          }  
          entire_traj_available = true;

          if(n==0){
            lane_array.lanes.push_back(ll_);
            if(k==0){
              entire_lane_arrays.lanearrays.push_back(lane_array);
            }
            else{
              entire_joker_arrays.lanearrays.push_back(lane_array);
            }
          }            
          else{
            if(k==0){
              entire_lane_arrays.lanearrays[0].lanes.push_back(ll_);
            }
            else{
              entire_joker_arrays.lanearrays[0].lanes.push_back(ll_);
            }
          }
        }
      }
    }  
  } 
}



visualization_msgs::MarkerArray MapLoader::visualize_global_path(const hmcl_msgs::LaneArray global_lane_array){
  std_msgs::ColorRGBA traj_marker_color;
  setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.5);    
  std_msgs::ColorRGBA in_bank_color;
  std_msgs::ColorRGBA in_junc_color;
  setColor(&in_bank_color, 1.0, 1.0, 0.0, 0.5);
  setColor(&in_junc_color, 0.0, 0.0, 1.0, 0.5);
  // Construct Traj_marker               
  visualization_msgs::MarkerArray marker_array;
  marker_array.markers.clear();
  for(int i=0 ; i< global_lane_array.lanes.size(); i++){     
    for( int j= 0 ; j <global_lane_array.lanes[i].waypoints.size() ; j++){
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ;
      marker_tmp.id = i*10000+j;
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
      if(global_lane_array.lanes[i].waypoints[j].junction){
        marker_tmp.color = in_junc_color;
      }
      else if(global_lane_array.lanes[i].waypoints[j].bank){
        marker_tmp.color = in_bank_color;
      }
      else{
      marker_tmp.color = traj_marker_color;
      }
      marker_tmp.lifetime = ros::Duration(5.0);
      marker_tmp.scale.x = 0.7;
      marker_tmp.scale.y = 0.4;
      marker_tmp.scale.z = 0.1;                  
      marker_array.markers.push_back(marker_tmp);
    }
  }
  return marker_array;
}

visualization_msgs::MarkerArray MapLoader::visualize_optimal_path(const hmcl_msgs::LaneArray optimal_lane_array){
  std_msgs::ColorRGBA traj_marker_color;
  setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.5);    
  std_msgs::ColorRGBA in_bank_color;
  std_msgs::ColorRGBA in_junc_color;
  setColor(&in_bank_color, 1.0, 1.0, 0.0, 0.5);
  setColor(&in_junc_color, 0.0, 0.0, 1.0, 0.5);
  // Construct Traj_marker               
  visualization_msgs::MarkerArray marker_array;
  marker_array.markers.clear();
  for(int i=0 ; i< optimal_lane_array.lanes.size(); i++){     
    for( int j= 0 ; j <optimal_lane_array.lanes[i].waypoints.size() ; j++){
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ;
      marker_tmp.id = i*100000+j;
      marker_tmp.ns = "otraj";
      marker_tmp.type = visualization_msgs::Marker::ARROW;
      marker_tmp.action = visualization_msgs::Marker::ADD;                  
      marker_tmp.pose.position.x = optimal_lane_array.lanes[i].waypoints[j].pose.pose.position.x;
      marker_tmp.pose.position.y = optimal_lane_array.lanes[i].waypoints[j].pose.pose.position.y;
      marker_tmp.pose.position.z = optimal_lane_array.lanes[i].waypoints[j].pose.pose.position.z;
      marker_tmp.pose.orientation.x = optimal_lane_array.lanes[i].waypoints[j].pose.pose.orientation.x;
      marker_tmp.pose.orientation.y = optimal_lane_array.lanes[i].waypoints[j].pose.pose.orientation.y;
      marker_tmp.pose.orientation.z = optimal_lane_array.lanes[i].waypoints[j].pose.pose.orientation.z;
      marker_tmp.pose.orientation.w = optimal_lane_array.lanes[i].waypoints[j].pose.pose.orientation.w;
      if(optimal_lane_array.lanes[i].waypoints[j].junction){
        marker_tmp.color = in_junc_color;
      }
      else if(optimal_lane_array.lanes[i].waypoints[j].bank){
        marker_tmp.color = in_bank_color;
      }
      else{
      marker_tmp.color = traj_marker_color;
      }
      marker_tmp.lifetime = ros::Duration(5.0);
      marker_tmp.scale.x = 0.7;
      marker_tmp.scale.y = 0.4;
      marker_tmp.scale.z = 0.1;                  
      marker_array.markers.push_back(marker_tmp);
    }
  }
  return marker_array;
}


visualization_msgs::MarkerArray MapLoader::visualize_entire_path(const hmcl_msgs::LaneArray entire_lane_array){
  std_msgs::ColorRGBA traj_marker_color;
  setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.5);    
  // std_msgs::ColorRGBA in_bank_color;
  // std_msgs::ColorRGBA in_junc_color;
  // setColor(&in_bank_color, 1.0, 1.0, 0.0, 0.5);
  // setColor(&in_junc_color, 0.0, 0.0, 1.0, 0.5);
  // Construct Traj_marker               
  visualization_msgs::MarkerArray marker_array;
  marker_array.markers.clear();
  for(int i=0 ; i< entire_lane_array.lanes.size(); i++){     
    for( int j= 0 ; j <entire_lane_array.lanes[i].waypoints.size() ; j++){
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ;
      marker_tmp.id = i*100000+j;
      marker_tmp.ns = "etraj";
      marker_tmp.type = visualization_msgs::Marker::ARROW;
      marker_tmp.action = visualization_msgs::Marker::ADD;                  
      marker_tmp.pose.position.x = entire_lane_array.lanes[i].waypoints[j].pose.pose.position.x;
      marker_tmp.pose.position.y = entire_lane_array.lanes[i].waypoints[j].pose.pose.position.y;
      marker_tmp.pose.position.z = entire_lane_array.lanes[i].waypoints[j].pose.pose.position.z;
      marker_tmp.pose.orientation.x = entire_lane_array.lanes[i].waypoints[j].pose.pose.orientation.x;
      marker_tmp.pose.orientation.y = entire_lane_array.lanes[i].waypoints[j].pose.pose.orientation.y;
      marker_tmp.pose.orientation.z = entire_lane_array.lanes[i].waypoints[j].pose.pose.orientation.z;
      marker_tmp.pose.orientation.w = entire_lane_array.lanes[i].waypoints[j].pose.pose.orientation.w;
      // if(entire_lane_array.lanes[i].waypoints[j].junction){
      //   marker_tmp.color = in_junc_color;
      // }
      // else if(optimal_lane_array.lanes[i].waypoints[j].bank){
      //   marker_tmp.color = in_bank_color;
      // }
      // else{
      // marker_tmp.color = traj_marker_color;
      // }
      marker_tmp.color = traj_marker_color;
      // marker_tmp.lifetime = ros::Duration(5.0);
      marker_tmp.scale.x = 0.7;
      marker_tmp.scale.y = 0.4;
      marker_tmp.scale.z = 0.1;                  
      marker_array.markers.push_back(marker_tmp);
    }
  }
  return marker_array;
}

visualization_msgs::MarkerArray MapLoader::visualize_entire_joker_path(const hmcl_msgs::LaneArray entire_joker_array){
  std_msgs::ColorRGBA traj_marker_color;
  setColor(&traj_marker_color, 0.0, 1.0, 0.0, 0.5);    
  // std_msgs::ColorRGBA in_bank_color;
  // std_msgs::ColorRGBA in_junc_color;
  // setColor(&in_bank_color, 1.0, 1.0, 0.0, 0.5);
  // setColor(&in_junc_color, 0.0, 0.0, 1.0, 0.5);
  // Construct Traj_marker               
  visualization_msgs::MarkerArray marker_array;
  marker_array.markers.clear();
  for(int i=0 ; i< entire_joker_array.lanes.size(); i++){     
    for( int j= 0 ; j <entire_joker_array.lanes[i].waypoints.size() ; j++){
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ;
      marker_tmp.id = i*100000+j;
      marker_tmp.ns = "etraj";
      marker_tmp.type = visualization_msgs::Marker::ARROW;
      marker_tmp.action = visualization_msgs::Marker::ADD;                  
      marker_tmp.pose.position.x = entire_joker_array.lanes[i].waypoints[j].pose.pose.position.x;
      marker_tmp.pose.position.y = entire_joker_array.lanes[i].waypoints[j].pose.pose.position.y;
      marker_tmp.pose.position.z = entire_joker_array.lanes[i].waypoints[j].pose.pose.position.z;
      marker_tmp.pose.orientation.x = entire_joker_array.lanes[i].waypoints[j].pose.pose.orientation.x;
      marker_tmp.pose.orientation.y = entire_joker_array.lanes[i].waypoints[j].pose.pose.orientation.y;
      marker_tmp.pose.orientation.z = entire_joker_array.lanes[i].waypoints[j].pose.pose.orientation.z;
      marker_tmp.pose.orientation.w = entire_joker_array.lanes[i].waypoints[j].pose.pose.orientation.w;
      // if(entire_joker_array.lanes[i].waypoints[j].junction){
      //   marker_tmp.color = in_junc_color;
      // }
      // else if(entire_joker_array.lanes[i].waypoints[j].bank){
      //   marker_tmp.color = in_bank_color;
      // }
      // else{
      // marker_tmp.color = traj_marker_color;
      // }
      marker_tmp.color = traj_marker_color;
      // marker_tmp.lifetime = ros::Duration(5.0);
      marker_tmp.scale.x = 0.7;
      marker_tmp.scale.y = 0.4;
      marker_tmp.scale.z = 0.1;                  
      marker_array.markers.push_back(marker_tmp);
    }
  }
  return marker_array;
}

// void MapLoader::missionCallback(const std_msgs::Int16::ConstPtr& msg){
//     getMission = true;
//     currentMission = (MissionState)msg->data;
//     ROS_INFO("current mission : %d", currentMission);
// }

void MapLoader::missionCallback(const std_msgs::Int16::ConstPtr& msg) {

        MissionState missionState = static_cast<MissionState>(msg->data);
        currentMission = stateToStringMission(missionState);
        ROS_INFO("Current mission: %s", currentMission.c_str());
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
  for(int k=0; k<2; k++){


    if(k==0){
      lanelet::Lanelets all_lanelets = laneletLayer(map); 
      lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(map);
      road_lanelets = roadLanelets(all_lanelets);
      n_road_lanelets_const = roadLaneletsConst(all_laneletsConst);
      areas = AreaLayer(map);
      bank = bankAreas(areas); 
      junction = junctionAreas(areas);
      freespace = freespaceAreas(areas);
      exit = exitAreas(areas);
      crosswalk = crosswalkAreas(areas);
      stopline = stoplineAreas(areas);
      parking = parkingAreas(areas);
      trafficisland = trafficislandAreas(areas);
      building = buildingAreas(areas);
      ROS_INFO("map with %d areas, %d bank, %d junction, %d freespace, %d exit, %d crosswalk ,%d stopline, %d parking, %d trafficisland, %d building", areas.size(), bank.size(), junction.size(), freespace.size(), exit.size(), crosswalk.size(), stopline.size(), parking.size(), trafficisland.size(), building.size());

      std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
      std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
      std_msgs::ColorRGBA cl_road, cl_bank, cl_junc, cl_free, cl_exit, cl_cross, cl_stop, cl_park, cl_traf, cl_build, cl_ll_borders;
      setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
      setColor(&cl_bank, 0.0, 1.0, 0.0, 0.5);
      setColor(&cl_junc, 0.0, 0.0, 1.0, 0.5);
      setColor(&cl_free, 1.0, 0.0, 1.0, 0.5);
      setColor(&cl_exit, 1.0, 0.5, 0.0, 0.5);
      setColor(&cl_cross, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_stop, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_park, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_traf, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_build, 0.0, 1.0, 0.0, 0.5);
      setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);
      

      insertMarkerArray(&map_marker_array, areaMarkerArray(bank,cl_bank));
      insertMarkerArray(&map_marker_array, areaMarkerArray(junction,cl_junc));
      insertMarkerArray(&map_marker_array, areaMarkerArray(freespace,cl_free));
      insertMarkerArray(&map_marker_array, areaMarkerArray(exit,cl_exit));
      insertMarkerArray(&map_marker_array, areaMarkerArray(crosswalk,cl_cross));
      insertMarkerArray(&map_marker_array, areaMarkerArray(stopline,cl_stop));
      insertMarkerArray(&map_marker_array, areaMarkerArray(parking,cl_park));
      insertMarkerArray(&map_marker_array, areaMarkerArray(trafficisland,cl_traf));
      insertMarkerArray(&map_marker_array, areaMarkerArray(building,cl_build));
      insertMarkerArray(&map_marker_array, laneletsBoundaryAsMarkerArray(
        road_lanelets, cl_ll_borders));
      ROS_INFO("Visualizing lanelet2 map with %lu lanelets, %lu stop lines",
        all_lanelets.size(), tl_stop_lines.size());
    }
    else{
      lanelet::Lanelets all_lanelets = laneletLayer(j_map); 
      lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(j_map);
      road_lanelets = roadLanelets(all_lanelets);
      j_road_lanelets_const = roadLaneletsConst(all_laneletsConst);
      j_areas = AreaLayer(j_map);
      j_bank = bankAreas(j_areas); 
      j_junction = junctionAreas(j_areas); 
      j_freespace = freespaceAreas(areas);
      j_exit = exitAreas(areas);
      j_crosswalk = crosswalkAreas(areas);
      j_stopline = stoplineAreas(areas);
      j_parking = parkingAreas(areas);
      j_trafficisland = trafficislandAreas(areas);
      j_building = buildingAreas(areas);
      ROS_INFO("joker map with %d areas, %d bank, %d junction, %d freespace, %d exit, %d crosswalk, %d stopline, %d parking, %d trafficisland, %d building", j_areas.size(), j_bank.size(), j_junction.size(), j_freespace.size(), j_exit.size(), j_crosswalk.size(), j_stopline.size(), j_parking.size(), j_trafficisland.size(), j_building.size());

      std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
      std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
      std_msgs::ColorRGBA cl_road, cl_bank, cl_junc, cl_free, cl_exit, cl_cross, cl_stop, cl_park, cl_traf, cl_build, cl_ll_borders;
      setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
      setColor(&cl_bank, 0.0, 1.0, 0.0, 0.5);
      setColor(&cl_junc, 0.0, 0.0, 1.0, 0.5);
      setColor(&cl_free, 1.0, 0.0, 1.0, 0.5);
      setColor(&cl_exit, 1.0, 0.5, 0.0, 0.5);
      setColor(&cl_cross, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_stop, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_park, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_traf, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);

      insertMarkerArray(&map_marker_array, areaMarkerArray(j_bank,cl_bank));
      insertMarkerArray(&map_marker_array, areaMarkerArray(j_junction,cl_junc));
      insertMarkerArray(&map_marker_array, areaMarkerArray(j_freespace,cl_free));
      insertMarkerArray(&map_marker_array, areaMarkerArray(j_exit,cl_exit));
      insertMarkerArray(&map_marker_array, areaMarkerArray(j_crosswalk,cl_cross));
      insertMarkerArray(&map_marker_array, areaMarkerArray(stopline,cl_stop));
      insertMarkerArray(&map_marker_array, areaMarkerArray(parking,cl_park));
      insertMarkerArray(&map_marker_array, areaMarkerArray(trafficisland,cl_traf));
      insertMarkerArray(&map_marker_array, areaMarkerArray(building,cl_build));
      insertMarkerArray(&map_marker_array, laneletsBoundaryAsMarkerArray(
        road_lanelets, cl_ll_borders));
      ROS_INFO("Visualizing joker lanelet2 map with %lu lanelets, %lu stop lines",
        all_lanelets.size(), tl_stop_lines.size());
    }


  }
}

void MapLoader::construct_lanelets_with_viz_opt(){
  for(int k=0; k<2; k++){
    if(k==0){
    // ROS_INFO("constructing lanelets viz ..... ");
    lanelet::Lanelets all_lanelets = laneletLayer(o_map); 
    lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(o_map);
    road_lanelets = roadLanelets(all_lanelets);
    o_road_lanelets_const = roadLaneletsConst(all_laneletsConst);
    o_areas = AreaLayer(o_map);
    o_bank = bankAreas(o_areas); 
    o_junction = junctionAreas(o_areas);
    o_freespace = freespaceAreas(o_areas);
    o_exit = exitAreas(o_areas);
    o_crosswalk = crosswalkAreas(o_areas);
    o_stopline = stoplineAreas(o_areas);
    o_parking = parkingAreas(o_areas);
    o_trafficisland = trafficislandAreas(o_areas);
    o_building = buildingAreas(o_areas);

    ROS_INFO("map with %d o_areas, %d o_bank, %d o_junction, %d o_freespace, %d o_exit, %d o_crosswalk ,%d o_stopline, %d o_parking, %d o_trafficisland, %d o_building", o_areas.size(), o_bank.size(), o_junction.size(), o_freespace.size(), o_exit.size(), o_crosswalk.size(), o_stopline.size(), o_parking.size(), o_trafficisland.size(), o_building.size());
    std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
    std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
    std_msgs::ColorRGBA cl_road, cl_bank, cl_junc, cl_free, cl_exit, cl_cross, cl_stop, cl_park, cl_traf, cl_build, cl_ll_borders;
    setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
    setColor(&cl_bank, 0.0, 1.0, 0.0, 0.5);
    setColor(&cl_junc, 0.0, 0.0, 1.0, 0.5);
    setColor(&cl_free, 1.0, 0.0, 1.0, 0.5);
    setColor(&cl_exit, 1.0, 0.5, 0.0, 0.5);
    setColor(&cl_cross, 0.5, 0.0, 1.0, 0.5);
    setColor(&cl_stop, 0.5, 0.0, 1.0, 0.5);
    setColor(&cl_park, 0.5, 0.0, 1.0, 0.5);
    setColor(&cl_traf, 0.5, 0.0, 1.0, 0.5);
    setColor(&cl_build, 0.0, 1.0, 0.0, 0.5);
    setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_bank,cl_bank));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_junction,cl_junc));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_freespace,cl_free));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_exit,cl_exit));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_crosswalk,cl_cross));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_stopline,cl_stop));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_parking,cl_park));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_trafficisland,cl_traf));
    insertMarkerArray(&o_map_marker_array, areaMarkerArray(o_building,cl_build));
    insertMarkerArray(&o_map_marker_array, laneletsBoundaryAsMarkerArray(road_lanelets, cl_ll_borders));
    ROS_INFO("Visualizing lanelet2 optimal map with %lu lanelets, %lu stop lines",all_lanelets.size(), tl_stop_lines.size());
    }
    else{
      lanelet::Lanelets all_lanelets = laneletLayer(j_map); 
      lanelet::ConstLanelets all_laneletsConst = laneletLayerConst(j_map);
      road_lanelets = roadLanelets(all_lanelets);
      j_road_lanelets_const = roadLaneletsConst(all_laneletsConst);
      j_areas = AreaLayer(j_map);
      j_bank = bankAreas(j_areas); 
      j_junction = junctionAreas(j_areas); 
      j_freespace = freespaceAreas(areas);
      j_exit = exitAreas(areas);
      j_crosswalk = crosswalkAreas(areas);
      j_stopline = stoplineAreas(areas);
      j_parking = parkingAreas(areas);
      j_trafficisland = trafficislandAreas(areas);
      j_building = buildingAreas(areas);
      ROS_INFO("joker map with %d areas, %d bank, %d junction, %d freespace, %d exit, %d crosswalk, %d stopline, %d parking, %d trafficisland, %d building", j_areas.size(), j_bank.size(), j_junction.size(), j_freespace.size(), j_exit.size(), j_crosswalk.size(), j_stopline.size(), j_parking.size(), j_trafficisland.size(), j_building.size());

      std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
      std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
      std_msgs::ColorRGBA cl_road, cl_bank, cl_junc, cl_free, cl_exit, cl_cross, cl_stop, cl_park, cl_traf, cl_build, cl_ll_borders;
      setColor(&cl_road, 0.2, 0.7, 0.7, 0.3);
      setColor(&cl_bank, 0.0, 1.0, 0.0, 0.5);
      setColor(&cl_junc, 0.0, 0.0, 1.0, 0.5);
      setColor(&cl_free, 1.0, 0.0, 1.0, 0.5);
      setColor(&cl_exit, 1.0, 0.5, 0.0, 0.5);
      setColor(&cl_cross, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_stop, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_park, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_traf, 0.5, 0.0, 1.0, 0.5);
      setColor(&cl_build, 0.0, 1.0, 0.0, 0.5);
      setColor(&cl_ll_borders, 1.0, 1.0, 0.0, 0.3);

      insertMarkerArray(&o_map_marker_array, areaMarkerArray(j_bank,cl_bank));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(j_junction,cl_junc));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(j_freespace,cl_free));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(j_exit,cl_exit));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(j_crosswalk,cl_cross));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(stopline,cl_stop));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(parking,cl_park));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(trafficisland,cl_traf));
      insertMarkerArray(&o_map_marker_array, areaMarkerArray(building,cl_build));
      insertMarkerArray(&o_map_marker_array, laneletsBoundaryAsMarkerArray(
        road_lanelets, cl_ll_borders));
      ROS_INFO("Visualizing joker lanelet2 map with %lu lanelets, %lu stop lines",
        all_lanelets.size(), tl_stop_lines.size());
    }
  }
}    

void MapLoader::viz_pub(const ros::TimerEvent& time){  
    g_map_pub.publish(map_marker_array);
    o_map_pub.publish(o_map_marker_array);

    // g_traj_lanelet_viz_pub.publish(traj_lanelet_marker_array);
    // g_traj_viz_pub.publish(traj_marker_array);
    
}

void MapLoader::load_map(){
  map_loaded  = true;
  ROS_INFO("map loading");
  lanelet::ErrorMessages errors;  
  lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));    
  o_map = load(optimal_osm_file_name, "osm_handler",projector,&errors);
  map = load(osm_file_name, "osm_handler",projector,&errors);
  j_map = load(j_osm_file_name, "osm_handler",projector,&errors);
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

int main (int argc, char** argv)
{
ros::init(argc, argv, "MapLoader");
ros::NodeHandle nh_;
ros::NodeHandle nh_private("~");
MapLoader MapLoader_(nh_,nh_private);

  ros::CallbackQueue callback_queue_nh;
  nh_.setCallbackQueue(&callback_queue_nh);

   std::thread spinner_thread_nh([&callback_queue_nh]() {
    ros::SingleThreadedSpinner spinner_nh;
    spinner_nh.spin(&callback_queue_nh);
  });



  ros::spin();

  spinner_thread_nh.join();

}