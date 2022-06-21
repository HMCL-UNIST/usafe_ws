/*
 * space_filter.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: ne0
 */
#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/extract_indices.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>


class SpaceFilter
{
public:
  SpaceFilter();

private:

  ros::NodeHandle node_handle_;
  ros::Subscriber cloud_sub_;
  ros::Publisher   cloud_pub_;

  std::string   subscribe_topic_;
  std::string    output_topic_;

  bool      lateral_removal_;
  bool      vertical_removal_;

  double       left_distance_;
  double       right_distance_;
  double       below_distance_;
  double       above_distance_;

  bool      ego_vehicle_removal_;
  double      ego_vehicle_front_;
  double      ego_vehicle_back_;
  double      ego_vehicle_left_;
  double      ego_vehicle_right_;

  void VelodyneCallback(const sensor_msgs::PointCloud2::Ptr& in_sensor_cloud_ptr);
  void KeepLanes(const pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud_ptr,
              pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud_ptr,
              float in_left_lane_threshold,
              float in_right_lane_threshold);
  void ClipCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud_ptr,
              pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud_ptr,
              float in_min_height,
              float in_max_height);
  void ClipEgovehicle(const pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud_ptr, 
              pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud_ptr,
              float in_float,
              float in_back,
              float in_left,
              float in_right);
};

SpaceFilter::SpaceFilter() :
    node_handle_("~")
{

  node_handle_.param<std::string>("subscribe_topic",  subscribe_topic_,  "/points_raw");
  node_handle_.param<std::string>("output_topic", output_topic_, "/points_clipped");

  node_handle_.param("lateral_removal",  lateral_removal_,  true);
  node_handle_.param("left_distance",  left_distance_,  5.0);
  node_handle_.param("right_distance",  right_distance_,  5.0);

  node_handle_.param("vertical_removal",  vertical_removal_,  true);
  node_handle_.param("below_distance",  below_distance_,  -1.5);
  node_handle_.param("above_distance",  above_distance_,  0.5);

  node_handle_.param("ego_vehicle_removal", ego_vehicle_removal_, true);
  node_handle_.param("ego_vehicle_front", ego_vehicle_front_, 2.5);
  node_handle_.param("ego_vehicle_back", ego_vehicle_back_, 2.5);
  node_handle_.param("ego_vehicle_left", ego_vehicle_left_, 1.6);
  node_handle_.param("ego_vehicle_right", ego_vehicle_right_, 1.6);

  cloud_sub_ = node_handle_.subscribe(subscribe_topic_, 10, &SpaceFilter::VelodyneCallback, this);
  cloud_pub_ = node_handle_.advertise<sensor_msgs::PointCloud2>(output_topic_, 10);
}

void SpaceFilter::KeepLanes(const pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud_ptr,
    pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud_ptr,
    float in_left_lane_threshold,
    float in_right_lane_threshold)
{
  pcl::PointIndices::Ptr far_indices (new pcl::PointIndices);
  for(unsigned int i=0; i< in_cloud_ptr->points.size(); i++)
  {
    if (
      in_cloud_ptr->points[i].y > (in_left_lane_threshold) || in_cloud_ptr->points[i].y < -1.0*in_right_lane_threshold
    )
    {
      far_indices->indices.push_back(i);
    }
  }
  out_cloud_ptr->points.clear();
  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud (in_cloud_ptr);
  extract.setIndices(far_indices);
  extract.setNegative(true);//true removes the indices, false leaves only the indices
  extract.filter(*out_cloud_ptr);
}

void SpaceFilter::ClipCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud_ptr,
    pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud_ptr,
    float in_min_height,
    float in_max_height)
{
  out_cloud_ptr->points.clear();
  for (unsigned int i=0; i<in_cloud_ptr->points.size(); i++)
  {
    if (in_cloud_ptr->points[i].z >= in_min_height &&
        in_cloud_ptr->points[i].z <= in_max_height)
    {
      out_cloud_ptr->points.push_back(in_cloud_ptr->points[i]);
    }
  }
}

void SpaceFilter::ClipEgovehicle(const pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud_ptr, 
    pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud_ptr,
    float in_front,
    float in_back,
    float in_left,
    float in_right)
{
  out_cloud_ptr->points.clear();
  
  pcl::PointIndices::Ptr ego_vehicle_indices (new pcl::PointIndices);

  for (unsigned int i=0; i<in_cloud_ptr->points.size(); i++)
  {
    if (in_cloud_ptr->points[i].x < in_front &&
        in_cloud_ptr->points[i].x > -1.0*in_back &&
        in_cloud_ptr->points[i].y < in_left &&
        in_cloud_ptr->points[i].y > -1.0*in_right )
    {
      ego_vehicle_indices->indices.push_back(i);
    }    
  } 

  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud(in_cloud_ptr);
  extract.setIndices(ego_vehicle_indices);
  extract.setNegative(true);//true removes the indices, false leaves only the indices
  extract.filter(*out_cloud_ptr);
}

void SpaceFilter::VelodyneCallback(const sensor_msgs::PointCloud2::Ptr& in_sensor_cloud_ptr)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr current_sensor_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr inlanes_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr clipped_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr ego_vehicle_removed_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::fromROSMsg(*in_sensor_cloud_ptr, *current_sensor_cloud_ptr);

  if (lateral_removal_)
  {
    KeepLanes(current_sensor_cloud_ptr, inlanes_cloud_ptr, left_distance_, right_distance_);
  }
  else
  {
    inlanes_cloud_ptr = current_sensor_cloud_ptr;
  }
  if (vertical_removal_)
  {
    ClipCloud(inlanes_cloud_ptr, clipped_cloud_ptr, below_distance_, above_distance_);
  }
  else
  {
    clipped_cloud_ptr = inlanes_cloud_ptr;
  }
  if (ego_vehicle_removal_)
  {
    ClipEgovehicle(clipped_cloud_ptr, ego_vehicle_removed_cloud_ptr, ego_vehicle_front_,
                  ego_vehicle_back_,ego_vehicle_left_,ego_vehicle_right_);
  }
  else
  {
    ego_vehicle_removed_cloud_ptr = clipped_cloud_ptr;
  }

  sensor_msgs::PointCloud2 cloud_msg;

  pcl::toROSMsg(*ego_vehicle_removed_cloud_ptr, cloud_msg);

  cloud_msg.header=in_sensor_cloud_ptr->header;
  cloud_pub_.publish(cloud_msg);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "space_filter");
  SpaceFilter node;
  ros::spin();

  return 0;
}




