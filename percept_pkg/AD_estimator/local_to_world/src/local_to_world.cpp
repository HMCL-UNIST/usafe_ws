
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

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "local_to_world.h"



// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )


Localtoworld::Localtoworld() :  
  nh_("~"),
  sample_count(0),
  tf_available(false),
  gotFirstFix_(false),
  gotFirstLocal_(false),
  maxQSize_(0),
  gpsPoseQ_(40),
  localPoseQ_(40)   
{
  // temporary variables to retrieve parameters
  double l_to_g_sensor_x, l_to_g_sensor_y, l_to_g_sensor_z, l_to_g_sensor_roll, l_to_g_sensor_pich, l_to_g_sensor_yaw;
  std::string local_sensor_frame, global_sensor_frame;
 
  nh_.param<double>("latOrigin", latOrigin, 0.0);
  nh_.param<double>("lonOrigin", lonOrigin, 0.0);
  nh_.param<double>("altOrigin", altOrigin, 0.0);
  enu_.Reset(latOrigin,lonOrigin,altOrigin);

  nh_.param<double>("gnss_skip_distance", gnss_skip_distance, 0.5);

  nh_.param<int>("num_of_gpsPose_for_icp", num_of_gpsPose_for_icp, 10);

  nh_.param<bool>("record_transform", record_transform, false);

  
  nh_.param<std::string>("file_name", file_name, "carla_test_v1.csv");

  nh_.param<std::string>("local_sensor_frame", local_sensor_frame, "lidar");
  nh_.param<std::string>("global_sensor_frame", global_sensor_frame, "gnss");
 

  
  // Set frame between sensors
  
  try
  {
    ros::Time now = ros::Time(0);
    local_transform_listener.waitForTransform(global_sensor_frame, local_sensor_frame, now, ros::Duration(2.0));
    local_transform_listener.lookupTransform(global_sensor_frame, local_sensor_frame,  ros::Time(0), l_sensor_to_g_sensor);
    l_to_g_sensor_x = l_sensor_to_g_sensor.getOrigin().x();
    l_to_g_sensor_y = l_sensor_to_g_sensor.getOrigin().y();
    l_to_g_sensor_z = l_sensor_to_g_sensor.getOrigin().z();
    tf::Quaternion q(l_sensor_to_g_sensor.getRotation().x(), l_sensor_to_g_sensor.getRotation().y(),
                        l_sensor_to_g_sensor.getRotation().z(), l_sensor_to_g_sensor.getRotation().w());        
    tf::Matrix3x3 m(q);
    m.getRPY(l_to_g_sensor_roll, l_to_g_sensor_pich, l_to_g_sensor_yaw);
    // set transform between local and global sensors
    Eigen::Translation3f tl_local_to_global(l_to_g_sensor_x, l_to_g_sensor_y, l_to_g_sensor_z);  // tl: translation
    Eigen::AngleAxisf rot_x_local_to_global(l_to_g_sensor_roll, Eigen::Vector3f::UnitX());                   // rot: rotation
    Eigen::AngleAxisf rot_y_local_to_global(l_to_g_sensor_pich, Eigen::Vector3f::UnitY());
    Eigen::AngleAxisf rot_z_local_to_global(l_to_g_sensor_yaw, Eigen::Vector3f::UnitZ());  
    l_to_g_sensor = (tl_local_to_global * rot_z_local_to_global * rot_y_local_to_global * rot_x_local_to_global).matrix();
    g_to_l_sensor = l_to_g_sensor.inverse();
  }
  catch (tf::TransformException& ex)
  {    
    ROS_ERROR("%s", ex.what());
    ROS_ERROR("sensor frame is not available.. exit node");
    return;
  }

  
  
  // if not recording, load recorded tf data 
  if(!record_transform && boost::filesystem::exists(file_name)){    
      // set tf by info in file 
      ROS_INFO("TF file loaded");       
      std::vector<std::string> row;
      std::string line, word;
      std::fstream file(file_name, std::ios::in);
      if(file.is_open())
      {
            while(getline(file, line))
            {
            row.clear();
            std::stringstream str(line);
            while(getline(str, word, ',')){
                row.push_back(word);
            }
            tf_data.push_back(row);
            }          
          if(tf_data[0].size() > 3){
            ROS_INFO("Origin info is missing in the file, use value from ros-param");
          }           
      }else{
          ROS_WARN("Could not open file");    
          return;
      }
      latOrigin = std::stod(tf_data[0][0]);  lonOrigin = std::stod(tf_data[0][1]); altOrigin = std::stod(tf_data[0][2]);
      ROS_INFO("GNSS Origin set as, lat: %f, lon: %f, alt: %f",latOrigin,lonOrigin,altOrigin);      
      enu_.Reset(latOrigin,lonOrigin,altOrigin);
      
      if(tf_data.size() > 2){
        ROS_INFO("Multiple reference tf matrix");        
        // TO DO --> need to consider multi transform if the covered area is large
      }

      if(tf_data.size() > 1 && tf_data[1].size() > 7){

          tf::Quaternion q(std::stof(tf_data[1][6]), std::stof(tf_data[1][7]),
                          std::stof(tf_data[1][8]) , std::stof(tf_data[1][5]));        
          tf::Matrix3x3 m(q);
          double roll_tmp_,pitch_tmp_,yaw_tmp_;
          m.getRPY(roll_tmp_, pitch_tmp_, yaw_tmp_);        
          Eigen::Translation3f transtmp(std::stof(tf_data[1][2]), std::stof(tf_data[1][3]), std::stof(tf_data[1][4]));  
          Eigen::AngleAxisf rt_x_(roll_tmp_, Eigen::Vector3f::UnitX());               
          Eigen::AngleAxisf rt_y_(pitch_tmp_, Eigen::Vector3f::UnitY());
          Eigen::AngleAxisf rt_z_(yaw_tmp_, Eigen::Vector3f::UnitZ());  
          l_to_g = (transtmp * rt_z_ * rt_y_ * rt_x_).matrix();
          g_to_l = l_to_g.inverse();          
          std::cout << "l_to_g = " <<  l_to_g << std::endl;
      }
      else{
        ROS_WARN("invalid tf matrix in file");
        return;
      }

  }
  // otherwise, start recording tf 
  else{
    ROS_WARN("Let us compute new tf");
    boost::thread optimizer(&Localtoworld::compute_transform,this); 
  }
  

  worldPosePub = nh_.advertise<geometry_msgs::PoseStamped>("gps_pose_local", 1);
  localFixPub = nh_.advertise<sensor_msgs::NavSatFix>("local_fix", 1);
  localGpsPub = nh_.advertise<geometry_msgs::PoseStamped>("local_pose_in_global", 1);  

  worldGpsSub = nh_.subscribe("gps", 100, &Localtoworld::GpsCallback, this);
  localPoseSub = nh_.subscribe("pose", 100, &Localtoworld::LocalCallback, this);  

  
}

Localtoworld::~Localtoworld()
{}


void Localtoworld::GpsCallback(sensor_msgs::NavSatFixConstPtr fix)
{ 
  if(!gotFirstFix_){
    gpsPoseQ_.pushNonBlocking(fix);
    gotFirstFix_ = true;    
    return;
  }  
  double E,N,U;  
  enu_.Forward(fix->latitude, fix->longitude, fix->altitude, E, N, U);

  /////////////
  // g_to_l              
        Eigen::Translation3f trnss(E,N,U);  
        Eigen::AngleAxisf rt_x_(0, Eigen::Vector3f::UnitX());               
        Eigen::AngleAxisf rt_y_(0, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf rt_z_(0, Eigen::Vector3f::UnitZ());  
        Eigen::Matrix4f gpose = (trnss * rt_z_ * rt_y_ * rt_x_).matrix();
        // compute global sensor pose in local frame 
        Eigen::Matrix4f global_pose_in_local_frame_ = g_to_l*gpose;            
     
  geometry_msgs::PoseStamped globalPose_ENU;
  globalPose_ENU.header = fix->header;
  globalPose_ENU.header.frame_id = "map";
  globalPose_ENU.pose.position.x = global_pose_in_local_frame_(0,3);
  globalPose_ENU.pose.position.y = global_pose_in_local_frame_(1,3);
  globalPose_ENU.pose.position.z = global_pose_in_local_frame_(2,3);
  globalPose_ENU.pose.orientation.x = 0;
  globalPose_ENU.pose.orientation.y = 0;
  globalPose_ENU.pose.orientation.z = 0;
  globalPose_ENU.pose.orientation.w = 1;
  worldPosePub.publish(globalPose_ENU);    
  
  sensor_msgs::NavSatFix local_fix_msg;
  local_fix_msg.status = fix->status;
  local_fix_msg.position_covariance= fix->position_covariance;
  local_fix_msg.position_covariance_type = fix->position_covariance_type;
  local_fix_msg.header = globalPose_ENU.header;
  double local_lat, local_lon, local_alt;
  enu_.Reverse(global_pose_in_local_frame_(0,3),global_pose_in_local_frame_(1,3),global_pose_in_local_frame_(2,3),local_lat,local_lon,local_alt);
  local_fix_msg.latitude = local_lat;
  local_fix_msg.longitude = local_lon;
  local_fix_msg.altitude = local_alt;
  localFixPub.publish(local_fix_msg);
  ////////////
  
  double prev_E,prev_N,prev_U;
  prev_gpsPoseFix = gpsPoseQ_.back();
  enu_.Forward(prev_gpsPoseFix->latitude, prev_gpsPoseFix->longitude, prev_gpsPoseFix->altitude, prev_E, prev_N, prev_U);
  
  double dist = std::sqrt( std::pow(E - prev_E, 2) + std::pow(N - prev_N, 2) );
  // push gnssFix data, if distance to previous reaches certain value 
  if(dist > gnss_skip_distance){
    if (!gpsPoseQ_.pushNonBlocking(fix)){
    ROS_WARN("Poping a GPS measurement due to full queue!!");    
    gpsPoseQ_.popBlocking();    
    }  
  } 
  
}



void Localtoworld::LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose)
{ 
  if(!record_transform){
    // l_to_g
        tf::Quaternion qq(local_pose->pose.orientation.x, local_pose->pose.orientation.y,
                        local_pose->pose.orientation.z , local_pose->pose.orientation.w);        
        tf::Matrix3x3 mm(qq);
        double rll_tmp,ptch_tmp,yw_tmp;
        mm.getRPY(rll_tmp, ptch_tmp, yw_tmp);        
        Eigen::Translation3f trns(local_pose->pose.position.x, local_pose->pose.position.y, local_pose->pose.position.z);  
        Eigen::AngleAxisf rt_x_(rll_tmp, Eigen::Vector3f::UnitX());               
        Eigen::AngleAxisf rt_y_(ptch_tmp, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf rt_z_(yw_tmp, Eigen::Vector3f::UnitZ());  
        Eigen::Matrix4f lpose = (trns * rt_z_ * rt_y_ * rt_x_).matrix();
        // compute global sensor pose in local frame 
        Eigen::Matrix4f local_pose_in_global_frame_ = l_to_g*lpose;        
    Eigen::Quaternionf local_pose_in_global_frame_quat(local_pose_in_global_frame_.topLeftCorner<3, 3>());
    geometry_msgs::PoseStamped transformed_msg; 
    transformed_msg.header = local_pose->header;
    transformed_msg.pose.position.x = local_pose_in_global_frame_(0,3);
    transformed_msg.pose.position.y = local_pose_in_global_frame_(1,3);
    transformed_msg.pose.position.z = local_pose_in_global_frame_(2,3);
    transformed_msg.pose.orientation.x= local_pose_in_global_frame_quat.x();
    transformed_msg.pose.orientation.y= local_pose_in_global_frame_quat.y();
    transformed_msg.pose.orientation.z= local_pose_in_global_frame_quat.z();
    transformed_msg.pose.orientation.w= local_pose_in_global_frame_quat.w();
    localGpsPub.publish(transformed_msg);      
  }

   if(!gotFirstLocal_){
    localPoseQ_.pushNonBlocking(local_pose);
    gotFirstLocal_ = true;    
    return;
  }  
  prev_localPose = localPoseQ_.back();
  double dist = std::sqrt( std::pow(prev_localPose->pose.position.x -local_pose->pose.position.x, 2) + std::pow(prev_localPose->pose.position.y -local_pose->pose.position.y, 2) );
  if( dist > gnss_skip_distance){
    if (!localPoseQ_.pushNonBlocking(local_pose)){
      ROS_WARN("Poping a localPose measurement due to full queue!!");
      localPoseQ_.popBlocking();
      }
    }
}

void Localtoworld::compute_transform()
{
  ros::Rate loop_rate(10); // rate of GPS   
  bool icp_converged  = false;
  while (ros::ok())
  {    
    ROS_INFO("gpsPoseQ_size = %d", gpsPoseQ_.size());      
    
    if( gpsPoseQ_.size() > num_of_gpsPose_for_icp){
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in_global (new pcl::PointCloud<pcl::PointXYZ>(gpsPoseQ_.size()-1,1));
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out_local (new pcl::PointCloud<pcl::PointXYZ>(localPoseQ_.size()-1,1));

      // Fill in the CloudIn data
      for (auto& point_in : *cloud_in_global)
      {
        gpsPoseFix = gpsPoseQ_.popBlocking();
        double E_,N_,U_;
        enu_.Forward(gpsPoseFix->latitude, gpsPoseFix->longitude, gpsPoseFix->altitude, E_, N_, U_);
    
        point_in.x = E_;
        point_in.y = N_;
        point_in.z = U_;
        std::cout << "point_in.x = " <<  point_in.x << "  point_in.y = " <<  point_in.y<< "  point_in.z = " <<  point_in.z << std::endl;
      }
      // Fill in the CloutOut data
      for (auto& point_out : *cloud_out_local)
      { 
        localPose = localPoseQ_.popBlocking();
        double x,y,z; 
        x = localPose->pose.position.x;
        y = localPose->pose.position.y;
        z = localPose->pose.position.z;        
        tf::Quaternion q(localPose->pose.orientation.x, localPose->pose.orientation.y,
                        localPose->pose.orientation.z , localPose->pose.orientation.w);        
        tf::Matrix3x3 m(q);
        double roll_tmp,pitch_tmp,yaw_tmp;
        m.getRPY(roll_tmp, pitch_tmp, yaw_tmp);        
        Eigen::Translation3f trans_tmp(x, y, z);  
        Eigen::AngleAxisf rot_x_(roll_tmp, Eigen::Vector3f::UnitX());               
        Eigen::AngleAxisf rot_y_(pitch_tmp, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf rot_z_(yaw_tmp, Eigen::Vector3f::UnitZ());  
        Eigen::Matrix4f local_pose_ = (trans_tmp * rot_z_ * rot_y_ * rot_x_).matrix();
        // compute global sensor pose in local frame 
        Eigen::Matrix4f global_sensor_in_local_frame = l_to_g_sensor*local_pose_;                                        
        point_out.x = global_sensor_in_local_frame(0, 3);
        point_out.y = global_sensor_in_local_frame(1, 3);
        point_out.z = global_sensor_in_local_frame(2, 3);
        std::cout << "point_out.x = " <<  point_out.x << "  point_out.y = " <<  point_out.y<< "  point_out.z = " <<  point_out.z << std::endl;        
      }
      
      pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
      icp.setInputSource(cloud_in_global);
      icp.setInputTarget(cloud_out_local);  
      pcl::PointCloud<pcl::PointXYZ> Final;
      icp.align(Final);  
      icp_converged = icp.hasConverged();
      std::cout << "has converged:" << icp.hasConverged() << " score: " << icp.getFitnessScore() << std::endl;
      std::cout << icp.getFinalTransformation() << std::endl;
      g_to_l = icp.getFinalTransformation();      
      l_to_g = g_to_l.inverse();
      std::cout << "l_to_g = " << l_to_g << std::endl;
      ////////////////////////////////////////////////////////
      /////////////////  Check the transformed points //////////////////
      // pcl::PointCloud<pcl::PointXYZ>::Ptr local_in_global (new pcl::PointCloud<pcl::PointXYZ>(localPoseQ_.size()-1,1));
      // pcl::transformPointCloud (*cloud_out_local, *local_in_global, l_to_g);
      // for (auto& point_tmp : *local_in_global){
      //   std::cout << "local in global, point_tmp.x = " <<  point_tmp.x << "  point_tmp.y = " <<  point_tmp.y<< "  point_tmp.z = " <<  point_tmp.z << std::endl;        
      // }
      // for (auto& point_tmp : *cloud_out_local){
      //   std::cout << "local x = " <<  point_tmp.x << "  local y = " <<  point_tmp.y<< "  local z = " <<  point_tmp.z << std::endl;        
      // }
      // for (auto& point_tmp : *cloud_in_global){
      //   std::cout << "global x = " <<  point_tmp.x << "  global y = " <<  point_tmp.y<< "  global z = " <<  point_tmp.z << std::endl;        
      // }
      //////////////////////////////////////////////////////////
    }

    if(icp_converged)
      {break;}

    loop_rate.sleep();
  }
  
  /////////////////////////////////////////////
  //////////       SAVE File       ////////////
  /////////////////////////////////////////////
  std::string file_name_ = file_name;
  while(boost::filesystem::exists(file_name_))
  { 
    ROS_WARN("file already exists");     
    char file_number= file_name_.substr(0, file_name_.find(".csv")).back();
    int version_number = int(file_number)-48; // current version
    if (version_number < 1){ROS_WARN("Pls check the file name carefully, NO file saved");return;} 
    std::string tmp_delimiter = std::to_string(version_number) + ".csv";        
    file_name_ = file_name_.substr(0, file_name_.find(tmp_delimiter))+std::to_string(version_number+1)+".csv";;    
  }   

  ofs.open(file_name_.c_str(), std::ios::app);
  if (!ofs)
  {
    ROS_WARN("Could not open %s",file_name_.c_str());        
  }
  else
  {
    // lat, lon, tf_x, tf_y, tf_z, tf_q_w, tf_q_x, tf_q_y, tf_q_z    
    Eigen::Quaternionf l_to_g_quat(l_to_g.topLeftCorner<3, 3>());
    ofs << latOrigin << "," << lonOrigin << "," << altOrigin << std::endl;
    ofs << latOrigin << "," << lonOrigin << "," <<  l_to_g(0,3) << "," << l_to_g(1,3)<< "," << l_to_g(2,3)<< "," << l_to_g_quat.w() << "," << l_to_g_quat.x() << "," << l_to_g_quat.y() << "," << l_to_g_quat.z() << std::endl;        
    ofs.close();
    ROS_INFO("File is now saved ");
  }
  

}



int main (int argc, char** argv)
{
ros::init(argc, argv, "LocalToworld");
Localtoworld ltp;
ros::spin();
}
