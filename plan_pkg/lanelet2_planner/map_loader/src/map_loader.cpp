                                                   
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
#include "map_loader.h"

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

  // using namespace lanelet;
  map_bin_pub = nh_.advertise<autoware_lanelet2_msgs::MapBin>("/lanelet_map_bin", 1, true);
  map_ver_pub = nh_.advertise<std_msgs::Int8>("/map_ver", 1, true);
  map_loaded = false;
  way_pub = nh_.advertise<hmcl_msgs::LaneArray>("/global_traj", 2, true);
  g_map_pub = nh_.advertise<visualization_msgs::MarkerArray>("/lanelet2_map_viz", 2, true);  
  checkpoint_pub = nh_.advertise<visualization_msgs::MarkerArray>("/checkpoints", 1, true);
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



  

  // new 123

  if(map_ver==0){
    n_checkpoints = {{{-13.3644,6.89563},{-198.298,262.944},{-391.835,473.273},{-585.57,671.21},{-894.437,792.509},
                  {-856.288,994.834},{-619.77,753.39},{-293.37,396.494},{-25.0083,103.925},{200.534,-199.635}},
                  {{-9.75051,7.64283},{-196.337,265.345},{-388.975,475.881},{-584.529,674.756},{-893.6,795.805},
                  {-858.573,991.216},{-622.874,751.146},{-296.166,394.153},{-27.9861,101.669},{196.92,-199.062}},
                  {{-6.64709,8.2246},{-194.101,267.837},{-386.944,478.043},{-584.166,678.641},{-893.215,798.993},
                  {-860.15,988.315},{-625.623,748.773},{-298.778,392.097},{-30.5283,99.5555},{193.618,-198.318}}};
    j_checkpoints = {{{-13.3644,6.89563},{-198.298,262.944},{-391.835,473.273},{-588.412,686.827},{-884.249,804.751},
                  {-856.288,994.834},{-619.77,753.39},{-293.37,396.494},{-25.0083,103.925},{200.534,-199.635}},
                  {{-9.75051,7.64283},{-196.337,265.345},{-388.975,475.881},{-585.889,689.731},{-884.172,808.21},
                  {-858.573,991.216},{-622.874,751.146},{-296.166,394.153},{-27.9861,101.669},{196.92,-199.062}},
                  {{-6.64709,8.2246},{-194.101,267.837},{-386.944,478.043},{-582.868,692.509},{-884.581,811.906},
                  {-860.15,988.315},{-625.623,748.773},{-298.778,392.097},{-30.5283,99.5555},{193.618,-198.318}}};
  }
  else if(map_ver==1){
    // checkpoints = {{{-4.46793,11.9409},{916.072,469.278},{1037.37,428.473},{55.0685,-26.3392}},
    //           {{-5.34489,8.36591},{918.92,467.198},{1035.06,432.065},{52.9272,-23.0308}},
    //           {{-5.67225,4.80412},{921.857,464.961},{1033.09,435.36},{50.9728,-19.6259}}};
    // checkpoints = {{{-5.34489,8.36591},{918.92,467.198},{1035.06,432.065},{52.9272,-23.0308}},
    //               {{-5.34489,8.36591},{918.92,467.198},{1035.06,432.065},{52.9272,-23.0308}},
    //               {{-5.34489,8.36591},{918.92,467.198},{1035.06,432.065},{52.9272,-23.0308}}};
    // normal
    n_checkpoints = {{{31.0772,10.1181},{223.495,75.8382},{507.511,207.242},{694.861,294.798},{847.94,392.074},{1003.31,599.145},
                  {1205.61,649.603},{1062.45,440.017},{536.078,195.957},{132.314,9.77846},{-303.732,-101.639}},
                  {{30.657,6.00994},{225.611,72.0122},{509.355,204.237},{696.937,291.416},{850.979,389.423},{1006.88,596.738},
                  {1203,647.721},{1061.03,443.638},{533.998,199.951},{131.353,12.9743},{-300.792,-99.0979}},
                  {{31.009,2.32728},{227.179,68.8971},{511.013,200.775},{698.546,288.347},{853.39,387.297},{1009.92,594.954},
                  {1200.41,645.475},{1059.51,446.99},{532.367,203.163},{129.609,16.6179},{-298.088,-96.7817}}};
    //joker
    j_checkpoints = {{{31.0772,10.1181},{223.495,75.8382},{507.511,207.242},{694.861,294.798},{860.871,372.135},{1018.52,590.108},
                  {1205.61,649.603},{1062.45,440.017},{536.078,195.957},{132.314,9.77846},{-303.732,-101.639}},
                  {{30.657,6.00994},{225.611,72.0122},{509.355,204.237},{696.937,291.416},{863.451,369.562},{1022.57,588.517},
                  {1203,647.721},{1061.03,443.638},{533.998,199.951},{131.353,12.9743},{-300.792,-99.0979}},
                  {{31.009,2.32728},{227.179,68.8971},{511.013,200.775},{698.546,288.347},{865.328,366.181},{1026.31,586.823},
                  {1200.41,645.475},{1059.51,446.99},{532.367,203.163},{129.609,16.6179},{-298.088,-96.7817}}};

    // n_checkpoints = {{{-20.72468,27.60187},{-141.72577,191.01080},{-353.10503,421.77226},{-493.37523,573.72734},{-632.50960,690.07780},{-876.95883,775.29994},{-986.41542,952.75572},{-743.27420,879.93109},{-351.01906,452.41657},{-51.11585,124.16988},{187.34438,-257.51936}},{{-16.68267,28.44788},{-138.72209,194.18785},{-350.80114,424.44105},{-490.78249,576.73158},{-630.90558,693.77785},{-875.74840,779.43194},{-983.83026,950.83973},{-746.29370,877.47943},{-354.19374,449.22285},{-53.86949,122.28458},{184.03107,-255.48890}},{{-13.28039,29.90059},{-136.22955,196.62705},{-348.00535,427.07125},{-488.34631,579.19586},{-629.61127,696.72023},{-874.97082,782.86991},{-980.90433,949.05324},{-749.02654,875.01409},{-356.75950,446.69422},{-56.81223,119.51733},{181.00366,-253.61507}}};


    // j_checkpoints = {{{-20.72468,27.60187},{-141.72577,191.01080},{-353.10503,421.77226},{-493.37523,573.72734},{-617.43364,708.44869},{-872.96244,792.53480},{-986.41542,952.75572},{-743.27420,879.93109},{-351.01906,452.41657},{-51.11585,124.16988},{187.34438,-257.51936}},{{-16.68267,28.44788},{-138.72209,194.18785},{-350.80114,424.44105},{-490.78249,576.73158},{-615.76468,711.68772},{-872.67518,796.87660},{-983.83026,950.83973},{-746.29370,877.47943},{-354.19374,449.22285},{-53.86949,122.28458},{184.03107,-255.48890}},{{-13.28039,29.90059},{-136.22955,196.62705},{-348.00535,427.07125},{-488.34631,579.19586},{-613.11252,714.50203},{-872.19573,800.95427},{-980.90433,949.05324},{-749.02654,875.01409},{-356.75950,446.69422},{-56.81223,119.51733},{181.00366,-253.61507}}};
  

  }
  // old 123
  else if(map_ver==2){
    // n_checkpoints = {{{-71.076,139.309},{-546.874,660.134},{-530.242,677.601},{-45.556,142.882}},
    //               {{-68.630, 142.757},{-543.951, 662.668},{-533.522, 675.464},{-48.533, 141.238}},
    //               {{-67.062, 146.574},{-542.120, 665.723},{-536.379, 673.380},{-52.418, 139.943}}};

    n_checkpoints = {{{-20.72468,27.60187},{-141.72577,191.01080},{-353.10503,421.77226},{-493.37523,573.72734},{-632.50960,690.07780},{-876.95883,775.29994},{-986.41542,952.75572},{-743.27420,879.93109},{-351.01906,452.41657},{-51.11585,124.16988},{187.34438,-257.51936}},{{-16.68267,28.44788},{-138.72209,194.18785},{-350.80114,424.44105},{-490.78249,576.73158},{-630.90558,693.77785},{-875.74840,779.43194},{-983.83026,950.83973},{-746.29370,877.47943},{-354.19374,449.22285},{-53.86949,122.28458},{184.03107,-255.48890}},{{-13.28039,29.90059},{-136.22955,196.62705},{-348.00535,427.07125},{-488.34631,579.19586},{-629.61127,696.72023},{-874.97082,782.86991},{-980.90433,949.05324},{-749.02654,875.01409},{-356.75950,446.69422},{-56.81223,119.51733},{181.00366,-253.61507}}};


    j_checkpoints = {{{-20.72468,27.60187},{-141.72577,191.01080},{-353.10503,421.77226},{-493.37523,573.72734},{-617.43364,708.44869},{-872.96244,792.53480},{-986.41542,952.75572},{-743.27420,879.93109},{-351.01906,452.41657},{-51.11585,124.16988},{187.34438,-257.51936}},{{-16.68267,28.44788},{-138.72209,194.18785},{-350.80114,424.44105},{-490.78249,576.73158},{-615.76468,711.68772},{-872.67518,796.87660},{-983.83026,950.83973},{-746.29370,877.47943},{-354.19374,449.22285},{-53.86949,122.28458},{184.03107,-255.48890}},{{-13.28039,29.90059},{-136.22955,196.62705},{-348.00535,427.07125},{-488.34631,579.19586},{-613.11252,714.50203},{-872.19573,800.95427},{-980.90433,949.05324},{-749.02654,875.01409},{-356.75950,446.69422},{-56.81223,119.51733},{181.00366,-253.61507}}};
  
  }
  // new 123 joker
  // checkpoints = {{{-13.3644,6.89563},{-198.298,262.944},{-391.835,473.273},{-583.897,683.723},{-893.312,805.441},
  //               {-856.288,994.834},{-619.77,753.39},{-293.37,396.494},{-25.0083,103.925},{200.534,-199.635}},
  //               {{-9.75051,7.64283},{-196.337,265.345},{-388.975,475.881},{-581.593,686.016},{-893.259,808.696},
  //               {-858.573,991.216},{-622.874,751.146},{-296.166,394.153},{-27.9861,101.669},{196.92,-199.062}},
  //               {{-6.64709,8.2246},{-194.101,267.837},{-386.944,478.043},{-578.837,688.685},{-893.227,812.623},
  //               {-860.15,988.315},{-625.623,748.773},{-298.778,392.097},{-30.5283,99.5555},{193.618,-198.318}}};



  checkers.resize(n_checkpoints[0].size());  
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
    previous_checkpoints = j_checkpoints;
  }
  checkpoint_pub.publish(checkpoint_markers);
  if(visualize_path){    
    g_traj_lanelet_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_lanelets_viz", 1, true);
    g_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/global_traj_viz", 1, true);
    viz_timer = nh_.createTimer(ros::Duration(5.0), &MapLoader::viz_pub,this);    
  }

  global_traj_available = false;    
  local_traj_available = false;    
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
  
  construct_lanelets_with_viz();

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
  if(!pose_init){
      return;
  }
  if(global_traj_available){
    publish_global_path();
    // ROS_INFO("GLOBAL");
  }  

}
float MapLoader::calculate_distance_pose2global(int current_checkpoint) {
    float min_dist = 1000.0;
    float dist = 1000.0;

    if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction) {
        candidate_lane_arrays = previous_lane_arrays;
    } else if (currentMission <= 2 || currentMission >= 8) {
        candidate_lane_arrays = j_candidate_lane_arrays;
    } else {
        candidate_lane_arrays = n_candidate_lane_arrays;
    }

    for (int i = 0; i < candidate_lane_arrays.lanearrays[current_checkpoint].lanes[1].waypoints.size() * 0.8; i++) {
        dist = distance(candidate_lane_arrays.lanearrays[current_checkpoint].lanes[1].waypoints[i].pose.pose.position.x,
                        candidate_lane_arrays.lanearrays[current_checkpoint].lanes[1].waypoints[i].pose.pose.position.y, pose_x, pose_y);
        if (min_dist > dist) min_dist = dist;
    }

    return min_dist;
}

void MapLoader::check_current_pose() {
    float check_dist = 8.0;
    std::vector<float> dist;
    std::vector<float> dist2glob;
    int current_checkpoint = 1;

    if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction) {
        checkpoints = previous_checkpoints;
    } else if (currentMission <= 2 || currentMission >= 8) {
        checkpoints = j_checkpoints;
    } else {
        checkpoints = n_checkpoints;
    }

    for (int i = 0; i < checkpoints[1].size(); i++) {
        dist.push_back(distance(checkpoints[1][i].first, checkpoints[1][i].second, pose_x, pose_y));
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
        ROS_INFO("global distance: %f, %f, %f, %f", dist2glob[0], dist2glob[1], dist2glob[2], dist2glob[3]);
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

void MapLoader::publish_global_path() {
    if (PolygonFlag.isinBank || PolygonFlag.isinCrosswalk || PolygonFlag.isinJunction) {
        ROS_INFO("Bank detected, using previous checkpoints and lane arrays");
        checkpoints = previous_checkpoints;
        candidate_lane_arrays.lanearrays.clear();
        candidate_lane_arrays = previous_lane_arrays;
    } else if (currentMission <= 2 || currentMission >= 8) {
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
        }
    }

    subtype_pub.publish(PolygonFlag);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    ROS_INFO("performSubtypeCheck took %f seconds", duration.count());
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
    
}

void MapLoader::compute_global_path(){

  candidate_lane_arrays.lanearrays.clear();
  n_candidate_lane_arrays.lanearrays.clear();
  j_candidate_lane_arrays.lanearrays.clear();
  

  // for(int n=0; n<1; n++){ 
    //2nd
    // if(n==0) xyz = {{-4.977, -53.535},{-625.395, 701.598},{-857.184, 785.693},{-787.356, 930.911},{-4.977, -53.535},{-625.395, 701.598}};
    // if(n==0) xyz = {{-4.977, -53.535},{-723.472, 817.352},{-849.372, 811.574},{-787.356, 930.911},{-4.977, -53.535},{-723.472, 817.352}};
    //3rd
    // if(n==0) xyz = {{-5.663,5.032},{921.877,465.172},{1032.969,435.45},{50.878,-19.511},{-5.663,5.032},{921.877,465.172}};
    // if(n==0) xyz = {{-5.663,5.032},{986.346,437.850},{1032.969,435.45},{50.878,-19.511},{-5.663,5.032},{986.346,437.850}};

    // else if(n==1) xyz = {{-68.630, 142.757},{-543.951, 662.668},{-533.522, 675.464},{-48.533, 141.238},{-68.630, 142.757},{-543.951, 662.668}};
    // else if(n==2) xyz = {{-67.062, 146.574},{-542.120, 665.723},{-536.379, 673.380},{-52.418, 139.943},{-67.062, 146.574},{-542.120, 665.723}};

    // for(int n=0; n<3; n++){ 
    //   if(n==0) xyz = {{-71.076,139.309},{-546.874,660.134},{-530.242,677.601},{-45.556,142.882},{-71.076,139.309},{-546.874,660.134}};
    //   else if(n==1) xyz = {{-68.630, 142.757},{-543.951, 662.668},{-533.522, 675.464},{-48.533, 141.238},{-68.630, 142.757},{-543.951, 662.668}};
    //   else if(n==2) xyz = {{-67.062, 146.574},{-542.120, 665.723},{-536.379, 673.380},{-52.418, 139.943},{-67.062, 146.574},{-542.120, 665.723}};
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
              int waypoint_idx_init = 0;
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

void MapLoader::fill_empty_path(){
  hmcl_msgs::LaneArrays filled_candidate_lane_arrays;
  for(int h=0; h<2; h++){
    if(h==0)candidate_lane_arrays = n_candidate_lane_arrays;
    else candidate_lane_arrays = j_candidate_lane_arrays;
    for(int i=0; i<candidate_lane_arrays.lanearrays.size(); i++){
      hmcl_msgs::LaneArray la;
      for(int j=0; j<candidate_lane_arrays.lanearrays[i].lanes.size(); j++){
        hmcl_msgs::Lane lane_;
        for(int k=1; k<candidate_lane_arrays.lanearrays[i].lanes[j].waypoints.size(); k++){
          if(candidate_lane_arrays.lanearrays[i].lanes[j].waypoints.size()<2){
            ROS_INFO("LACK OF POINTS FOR LOCAL");
            break;
          }
          hmcl_msgs::Waypoint wp;
          double wp1x = candidate_lane_arrays.lanearrays[i].lanes[j].waypoints[k-1].pose.pose.position.x;
          double wp1y = candidate_lane_arrays.lanearrays[i].lanes[j].waypoints[k-1].pose.pose.position.y;
          double wp2x = candidate_lane_arrays.lanearrays[i].lanes[j].waypoints[k].pose.pose.position.x;
          double wp2y = candidate_lane_arrays.lanearrays[i].lanes[j].waypoints[k].pose.pose.position.y;
          double dist = distance(wp1x,wp1y,wp2x,wp2y);
          if(dist > 1.0){
            int n = static_cast<int>(dist/1.0);
            ROS_INFO("ADD %d WAYPOINTS", n);
            for(int l = 0; l < n-1; l++){
              wp = candidate_lane_arrays.lanearrays[i].lanes[j].waypoints[k-1];
              wp.pose.pose.position.x = wp1x+(wp2x-wp1x)/n*(l+1);
              wp.pose.pose.position.y = wp1y+(wp2y-wp1y)/n*(l+1);
              lane_.waypoints.push_back(wp);
            }
          }
          wp = candidate_lane_arrays.lanearrays[i].lanes[j].waypoints[k];
          lane_.waypoints.push_back(wp);
        }
        la.lanes.push_back(lane_);
      }
      filled_candidate_lane_arrays.lanearrays.push_back(la);
    }
    if(h==0) n_candidate_lane_arrays = filled_candidate_lane_arrays;
    else {
      j_candidate_lane_arrays = filled_candidate_lane_arrays;
      candidate_lane_arrays = filled_candidate_lane_arrays;
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




void MapLoader::missionCallback(const std_msgs::Int16::ConstPtr& msg){
    getMission = true;
    currentMission = (MissionState)msg->data;
    ROS_INFO("current mission : %d", currentMission);
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
      ROS_INFO("map with %d areas, %d bank, %d junction, %d freespace, %d exit, %d crosswalk ,%d stopline, %d parking, %d trafficisland", areas.size(), bank.size(), junction.size(), freespace.size(), exit.size(), crosswalk.size(), stopline.size(), parking.size(), trafficisland.size());

      std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
      std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
      std_msgs::ColorRGBA cl_road, cl_bank, cl_junc, cl_free, cl_exit, cl_cross, cl_stop, cl_park, cl_traf, cl_ll_borders;
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

      insertMarkerArray(&map_marker_array, areaMarkerArray(bank,cl_bank));
      insertMarkerArray(&map_marker_array, areaMarkerArray(junction,cl_junc));
      insertMarkerArray(&map_marker_array, areaMarkerArray(freespace,cl_free));
      insertMarkerArray(&map_marker_array, areaMarkerArray(exit,cl_exit));
      insertMarkerArray(&map_marker_array, areaMarkerArray(crosswalk,cl_cross));
      insertMarkerArray(&map_marker_array, areaMarkerArray(stopline,cl_stop));
      insertMarkerArray(&map_marker_array, areaMarkerArray(parking,cl_park));
      insertMarkerArray(&map_marker_array, areaMarkerArray(trafficisland,cl_traf));
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
      ROS_INFO("joker map with %d areas, %d bank, %d junction, %d freespace, %d exit, %d crosswalk, %d stopline, %d parking, %d trafficisland", j_areas.size(), j_bank.size(), j_junction.size(), j_freespace.size(), j_exit.size(), j_crosswalk.size(), j_stopline.size(), j_parking.size(), j_trafficisland.size());

      std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems = get_trafficLights(all_lanelets);
      std::vector<lanelet::LineString3d> tl_stop_lines = getTrafficLightStopLines(road_lanelets);
      std_msgs::ColorRGBA cl_road, cl_bank, cl_junc, cl_free, cl_exit, cl_cross, cl_stop, cl_park, cl_traf,cl_ll_borders;
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
      insertMarkerArray(&map_marker_array, laneletsBoundaryAsMarkerArray(
        road_lanelets, cl_ll_borders));
      ROS_INFO("Visualizing joker lanelet2 map with %lu lanelets, %lu stop lines",
        all_lanelets.size(), tl_stop_lines.size());
    }


  }
}

void MapLoader::viz_pub(const ros::TimerEvent& time){  
    g_map_pub.publish(map_marker_array);
    // g_traj_lanelet_viz_pub.publish(traj_lanelet_marker_array);
    // g_traj_viz_pub.publish(traj_marker_array);
    
}

void MapLoader::load_map(){
  map_loaded  = true;
  ROS_INFO("map loading");
  lanelet::ErrorMessages errors;  
  lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));    
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapLoader::viz_local_path(hmcl_msgs::Lane &lane_){
  
              // Construct Traj_lanelet_marker 
               std_msgs::ColorRGBA local_traj_marker_color;
                setColor(&local_traj_marker_color, 1.0, 0.0, 0.0, 0.5);    
              local_traj_marker_array.markers.clear();  
              for(int i=0; i< lane_.waypoints.size();i++){
                      visualization_msgs::Marker marker_tmp;
                      marker_tmp.header.stamp = ros::Time::now();
                      marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
                      marker_tmp.id = 60000+i;
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
                      local_traj_marker_array.markers.push_back(marker_tmp);
                      
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
  // return PolyFit<double>(x, y, options);
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