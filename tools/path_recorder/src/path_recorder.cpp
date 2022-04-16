
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
#include "path_recorder.h"
// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


PathRecorder::PathRecorder(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p) :  
  nh_(nh), nh_p_(nh_p) 
{
  // using namespace lanelet;
  
  path_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/recorded_path", 1, true);  
  
  pose_init = false; 
  gnss_init = false;
  gpsSub_ = nh_.subscribe("/fix", 300, &PathRecorder::GpsCallback, this);
  save_map_sub = nh_.subscribe("/save_map", 1, &PathRecorder::saveMapCallback, this);
  pose_sub = nh_.subscribe("/current_pose",1,&PathRecorder::poseCallback,this);

  nh_p_.param<std::string>("osm_file_name", osm_file_name, "Town01.osm");
  nh_p_.getParam("osm_file_name", osm_file_name);
  nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
  nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
  nh_p_.param<double>("map_origin_att", origin_att, 0.0);
  nh_p_.param<double>("line_resolution", line_resolution, 20.0);
  nh_p_.param<double>("point_resolution", point_resolution, 1.0);
  nh_p_.param<bool>("path_record_with_gnss", path_record_with_gnss, true);
  
  
   

  // we are given an origin
  enu_.Reset(origin_lat,origin_lon,origin_att);
 
  viz_timer = nh_.createTimer(ros::Duration(0.1), &PathRecorder::viz_pub,this);    

}

PathRecorder::~PathRecorder()
{}




void PathRecorder::saveMapCallback(std_msgs::BoolConstPtr data){
  if(data->data){
    if(path_record_with_gnss){
      lanelet::LaneletMapUPtr map = lanelet::utils::createMap(lines_);
      ROS_INFO("map save init ...");
      lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));  
      std::string delimiter = ".osm";
      std::string package_path = ros::package::getPath("path_recorder");
      std::string token = osm_file_name.substr(0, osm_file_name.find(delimiter)); // token is "scott"
      std::string osm_file_name_fixed =  token + "_gnss_path.osm";  
      write(osm_file_name_fixed, *map,projector);
      ROS_INFO("path based on gnss has been saved");
    }else{
      lanelet::LaneletMapUPtr map = lanelet::utils::createMap(lines_pose_);
      ROS_INFO("map save init ...");
      lanelet::projection::UtmProjector projector(lanelet::Origin({origin_lat, origin_lon ,origin_att}));  
      std::string delimiter = ".osm";
      std::string package_path = ros::package::getPath("path_recorder");
      std::string token = osm_file_name.substr(0, osm_file_name.find(delimiter)); // token is "scott"
      std::string osm_file_name_fixed =  token + "_local_path.osm";  
      write(osm_file_name_fixed, *map,projector);
      ROS_INFO("path based on local pose has been saved");
    }
  }
}

void PathRecorder::GpsCallback(sensor_msgs::NavSatFixConstPtr fix){
  
  double E, N, U;
  enu_.Forward(fix->latitude, fix->longitude, fix->altitude, E, N, U);
  
  if(!gnss_init){
    lanelet::Point3d p3d_(lanelet::utils::getId(), E, N, U); 
    lanelet::LineString3d l3s(lanelet::utils::getId(), {p3d_});
    l3s_ = l3s;
    gnss_init = true;
  }else{
    double dist_tmp = std::sqrt(std::pow(E-pre_gnss_pos.position.x,2)+std::pow(N-pre_gnss_pos.position.y,2));
    if(dist_tmp > point_resolution){
      if(lanelet::geometry::length(l3s_) > line_resolution){
      lines_.push_back(l3s_);
      lanelet::Point3d p3d_(lanelet::utils::getId(), E, N, U); 
      lanelet::LineString3d l3s(lanelet::utils::getId(), {p3d_});
      l3s_ = l3s;
        }
    
      l3s_.push_back(lanelet::Point3d(lanelet::utils::getId(), E,N,U));

        pre_gnss_pos.position.x = E;
        pre_gnss_pos.position.y = N;
        pre_gnss_pos.position.z = U;
    }
    
  }



}


void PathRecorder::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){  
   
  double pose_x = msg->pose.position.x;
  double pose_y = msg->pose.position.y;
  double pose_z = msg->pose.position.z;

  
  if(!pose_init){
    lanelet::Point3d p3d_(lanelet::utils::getId(), pose_x, pose_y, pose_z); 
    
    lanelet::LineString3d l3s(lanelet::utils::getId(), {p3d_});
    l3s_pose_ = l3s;
    pose_init = true;
  }else{
    if(lanelet::geometry::length(l3s_pose_) > line_resolution){
      lines_pose_.push_back(l3s_pose_);
      lanelet::Point3d p3d_(lanelet::utils::getId(), pose_x, pose_y, pose_z); 
      lanelet::LineString3d l3s(lanelet::utils::getId(), {p3d_});
      l3s_pose_ = l3s;
    }else{

      l3s_pose_.push_back(lanelet::Point3d(lanelet::utils::getId(), pose_x, pose_y, pose_z));
    }
    
  }
  pre_local_pos.position.x = msg->pose.position.x;
  pre_local_pos.position.y = msg->pose.position.y;
  pre_local_pos.position.z = msg->pose.position.z;

}


void PathRecorder::viz_pub(const ros::TimerEvent& time){
  if(lines_.size() < 1 && lines_pose_.size() < 1){
    return; 
  }

  double lss = 0.2;  // line string size  
  visualization_msgs::MarkerArray path_marker_array;
  std_msgs::ColorRGBA path_color;
  setColor(&path_color, 0.0, 1.0, 1.0, 0.5);
  if(path_record_with_gnss){
        for (int i=0; i < lines_.size(); i++)
        {
          visualization_msgs::Marker line_strip;
          lineString2Marker(lines_.at(i), &line_strip, "map", "path_centerline", path_color, lss,false);
          path_marker_array.markers.push_back(line_strip);
        }
  }else{  
    for (int i=0; i < lines_pose_.size(); i++)
        {
          visualization_msgs::Marker line_strip;
          lineString2Marker(lines_pose_.at(i), &line_strip, "map", "path_centerline", path_color, lss,false);
          path_marker_array.markers.push_back(line_strip);
        }
      }
    path_viz_pub.publish(path_marker_array);
}

int main (int argc, char** argv)
{
ros::init(argc, argv, "PathRecorder");
ros::NodeHandle nh_;
ros::NodeHandle nh_private("~");
PathRecorder PathRecorder_(nh_,nh_private);


  ros::spin();

}
