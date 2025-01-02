/**
 * ultralytics_ros
 * Copyright (C) 2023-2024  Alpaca-zip
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tracker_with_cloud_node/tracker_with_cloud_node.h"

TrackerWithCloudNode::TrackerWithCloudNode() : pnh_("~"), has_camera_info_(false), has_lidar_(false), has_yolo_(false)
{
  pnh_.param<std::string>("camera_info_topic", camera_info_topic_, "camera_info");
  pnh_.param<std::string>("lidar_topic", lidar_topic_, "points_raw");
  pnh_.param<std::string>("yolo_result_topic", yolo_result_topic_, "yolo_result");
  pnh_.param<std::string>("yolo_3d_result_topic", yolo_3d_result_topic_, "yolo_3d_result");
  pnh_.param<float>("cluster_tolerance", cluster_tolerance_, 0.5);
  pnh_.param<float>("voxel_leaf_size", voxel_leaf_size_, 0.5);
  pnh_.param<int>("min_cluster_size", min_cluster_size_, 100);
  pnh_.param<int>("max_cluster_size", max_cluster_size_, 25000);

  detection_cloud_pub_ = nh_.advertise<sensor_msgs::PointCloud2>("detection_cloud", 1);
  // detection3d_pub_ = nh_.advertise<vision_msgs::Detection3DArray>(yolo_3d_result_topic_, 1);
  // marker_pub_ = nh_.advertise<visualization_msgs::MarkerArray>("detection_marker", 1);

  camera_info_sub_ = nh_.subscribe(camera_info_topic_, 10, &TrackerWithCloudNode::cameraInfoCallback, this);
  lidar_sub_ = nh_.subscribe(lidar_topic_, 10, &TrackerWithCloudNode::lidarCallback, this);
  yolo_result_sub_ = nh_.subscribe(yolo_result_topic_, 10, &TrackerWithCloudNode::yoloCallback, this);

  tf_buffer_.reset(new tf2_ros::Buffer(ros::Duration(2.0), true));
  tf_listener_.reset(new tf2_ros::TransformListener(*tf_buffer_));
}

void TrackerWithCloudNode::cameraInfoCallback(const sensor_msgs::CameraInfo::ConstPtr& camera_info_msg)
{
  camera_info_msg_ = camera_info_msg;
  has_camera_info_ = true;
  checkAndRunSyncCallback();
}

void TrackerWithCloudNode::lidarCallback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  cloud_msg_ = cloud_msg;
  has_lidar_ = true;
  checkAndRunSyncCallback();
}

void TrackerWithCloudNode::yoloCallback(const ultralytics_ros::YoloResultConstPtr& yolo_result_msg)
{
  yolo_result_msg_ = yolo_result_msg;
  has_yolo_ = true;
  checkAndRunSyncCallback();
}

void TrackerWithCloudNode::checkAndRunSyncCallback()
{
  if (has_camera_info_ && has_lidar_ && has_yolo_)
  {
    syncCallback(camera_info_msg_, cloud_msg_, yolo_result_msg_);

    has_camera_info_ = false;
    has_lidar_ = false;
    has_yolo_ = false;
  }
}

void TrackerWithCloudNode::syncCallback(const sensor_msgs::CameraInfo::ConstPtr& camera_info_msg,
                                        const sensor_msgs::PointCloud2ConstPtr& cloud_msg,
                                        const ultralytics_ros::YoloResultConstPtr& yolo_result_msg)
{
  cloud_header_ = cloud_msg->header;
  camera_header_ = camera_info_msg->header;

  ros::Time current_call_time = ros::Time::now();
  ros::Duration callback_interval = current_call_time - last_call_time_;
  last_call_time_ = current_call_time;
  // std::cout << callback_interval << std::endl;
  pcl::PointCloud<pcl::PointXYZ>::Ptr downsampled_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  downsampled_cloud = downsampleCloudMsg(cloud_msg);

  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud;
  cam_model_.fromCameraInfo(camera_info_msg);

  transformed_cloud = cloud2TransformedCloud(downsampled_cloud, cloud_msg->header.frame_id, cam_model_.tfFrame(),
                                             cloud_msg->header.stamp);
  vision_msgs::Detection3DArray detections3d_msg;
  sensor_msgs::PointCloud2 detection_cloud_msg;
  visualization_msgs::MarkerArray marker_array_msg;

  projectCloud(transformed_cloud, yolo_result_msg, cloud_msg->header, detections3d_msg, detection_cloud_msg);
  // marker_array_msg = createMarkerArray(detections3d_msg, callback_interval.toSec());

  // detection3d_pub_.publish(detections3d_msg);
  detection_cloud_pub_.publish(detection_cloud_msg);
  // marker_pub_.publish(marker_array_msg);
}

void TrackerWithCloudNode::projectCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud,
                                        const ultralytics_ros::YoloResultConstPtr& yolo_result_msg,
                                        const std_msgs::Header& header, vision_msgs::Detection3DArray& detections3d_msg,
                                        sensor_msgs::PointCloud2& combine_detection_cloud_msg)
{
  pcl::PointCloud<pcl::PointXYZ> combine_detection_cloud;
  detections3d_msg.header = header;
  // detections3d_msg.header.stamp = yolo_result_msg->header.stamp;
  for (size_t i = 0; i < yolo_result_msg->detections.detections.size(); i++)
  {
    pcl::PointCloud<pcl::PointXYZ>::Ptr detection_cloud_raw(new pcl::PointCloud<pcl::PointXYZ>);

    if (yolo_result_msg->masks.empty())
    {
      processPointsWithBbox(cloud, yolo_result_msg->detections.detections[i], detection_cloud_raw);
    }
    else
    {
      processPointsWithMask(cloud, yolo_result_msg->masks[i], detection_cloud_raw);
    }
    if (!detection_cloud_raw->points.empty())
    {
      pcl::PointCloud<pcl::PointXYZ>::Ptr detection_cloud =
          cloud2TransformedCloud(detection_cloud_raw, cam_model_.tfFrame(), header.frame_id, header.stamp);

      pcl::PointCloud<pcl::PointXYZ>::Ptr closest_detection_cloud = euclideanClusterExtraction(detection_cloud);

      // createBoundingBox(detections3d_msg, closest_detection_cloud, yolo_result_msg->detections.detections[i].results);
      combine_detection_cloud += *closest_detection_cloud;
    }
  }

  pcl::toROSMsg(combine_detection_cloud, combine_detection_cloud_msg);
  combine_detection_cloud_msg.header = header;
}

void TrackerWithCloudNode::processPointsWithBbox(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud,
                                                 const vision_msgs::Detection2D& detection,
                                                 pcl::PointCloud<pcl::PointXYZ>::Ptr& detection_cloud_raw)
{
  for (const auto& point : cloud->points)
  {
    cv::Point3d pt_cv(point.x, point.y, point.z);
    cv::Point2d uv = cam_model_.project3dToPixel(pt_cv);
    if (point.z > 0 && uv.x > 0 && uv.x >= detection.bbox.center.x - detection.bbox.size_x / 2 &&
        uv.x <= detection.bbox.center.x + detection.bbox.size_x / 2 &&
        uv.y >= detection.bbox.center.y - detection.bbox.size_y / 2 &&
        uv.y <= detection.bbox.center.y + detection.bbox.size_y / 2)
    {
      detection_cloud_raw->points.push_back(point);
    }
  }
}

void TrackerWithCloudNode::processPointsWithMask(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud,
                                                 const sensor_msgs::Image& mask,
                                                 pcl::PointCloud<pcl::PointXYZ>::Ptr& detection_cloud_raw)
{
  cv_bridge::CvImagePtr cv_ptr;

  try
  {
    cv_ptr = cv_bridge::toCvCopy(mask, sensor_msgs::image_encodings::MONO8);

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  for (const auto& point : cloud->points)
  {
    cv::Point3d pt_cv(point.x, point.y, point.z);

    cv::Point2d uv = cam_model_.project3dToPixel(pt_cv);

    if (point.z > 0 && uv.x >= 0 && uv.x < cv_ptr->image.cols && uv.y >= 0 && uv.y < cv_ptr->image.rows)
    {
      if (cv_ptr->image.at<uchar>(cv::Point(uv.x, uv.y)) > 0)
      {
        detection_cloud_raw->points.push_back(point);
      }
    }
  }
  std::cout << "detection_cloud_raw.size : " << detection_cloud_raw->points.size() << std::endl;

}

pcl::PointCloud<pcl::PointXYZ>::Ptr
TrackerWithCloudNode::downsampleCloudMsg(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
  pcl::fromROSMsg(*cloud_msg, *cloud);
  pcl::PointCloud<pcl::PointXYZ>::Ptr downsampled_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
  voxel_grid.setInputCloud(cloud);
  voxel_grid.setLeafSize(voxel_leaf_size_, voxel_leaf_size_, voxel_leaf_size_);
  voxel_grid.filter(*downsampled_cloud);
  return downsampled_cloud;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr
TrackerWithCloudNode::cloud2TransformedCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud,
                                             const std::string& source_frame, const std::string& target_frame,
                                             const ros::Time& stamp)
// {
//   pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>);

//   try
//   {
//     geometry_msgs::TransformStamped tf = tf_buffer_->lookupTransform(target_frame, source_frame, stamp);
//     pcl_ros::transformPointCloud(*cloud, *transformed_cloud, tf.transform);
//   }
//   catch (tf2::TransformException& e)
//   {
//     ROS_WARN("%s", e.what());
//   }

//   return transformed_cloud;
// }
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if (!tf_received_ && source_frame == cloud_header_.frame_id)
  {
    try
    {
      transform_ = tf_buffer_->lookupTransform(target_frame, source_frame, ros::Time(0), ros::Duration(1.0));
      
      inverse_.transform.translation.x = -transform_.transform.translation.x;
      inverse_.transform.translation.y = -transform_.transform.translation.y;
      inverse_.transform.translation.z = -transform_.transform.translation.z;

      Eigen::Quaterniond q(transform_.transform.rotation.w, transform_.transform.rotation.x,
                           transform_.transform.rotation.y, transform_.transform.rotation.z);
      Eigen::Quaterniond q_inverse = q.inverse();  
      inverse_.transform.rotation.x = q_inverse.x();
      inverse_.transform.rotation.y = q_inverse.y();
      inverse_.transform.rotation.z = q_inverse.z();
      inverse_.transform.rotation.w = q_inverse.w();

      std::cout << "TF recieved!!!" << std::endl;
      tf_received_ = true; 
    } 
    catch (tf2::TransformException& e)
    {
      ROS_WARN("%s", e.what());
      return transformed_cloud;
    }
  }
  if (source_frame == cloud_header_.frame_id)
  {    
    pcl_ros::transformPointCloud(*cloud, *transformed_cloud, transform_.transform);
  }
  else if (source_frame == camera_header_.frame_id)
  {    
    pcl_ros::transformPointCloud(*cloud, *transformed_cloud, inverse_.transform);
  }

  return transformed_cloud;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr
TrackerWithCloudNode::euclideanClusterExtraction(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;

  ec.setClusterTolerance(cluster_tolerance_);
  ec.setMinClusterSize(min_cluster_size_);
  ec.setMaxClusterSize(max_cluster_size_);
  ec.setSearchMethod(tree);
  ec.setInputCloud(cloud);
  ec.extract(cluster_indices);

  float min_distance = std::numeric_limits<float>::max();
  pcl::PointCloud<pcl::PointXYZ>::Ptr closest_cluster(new pcl::PointCloud<pcl::PointXYZ>);

  for (const auto& cluster : cluster_indices)
  {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
    for (const auto& indice : cluster.indices)
    {
      cloud_cluster->push_back((*cloud)[indice]);
    }

    Eigen::Vector4f centroid;
    pcl::compute3DCentroid(*cloud_cluster, centroid);
    float distance = centroid.norm();

    if (distance < min_distance)
    {
      min_distance = distance;
      *closest_cluster = *cloud_cluster;
    }
  }

  return closest_cluster;
}

void TrackerWithCloudNode::createBoundingBox(
    vision_msgs::Detection3DArray& detections3d_msg, const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud,
    const std::vector<vision_msgs::ObjectHypothesisWithPose>& detections_results)
{
  vision_msgs::Detection3D detection3d;
  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointXYZ min_pt, max_pt;
  Eigen::Vector4f centroid;
  pcl::compute3DCentroid(*cloud, centroid);
  double theta = -atan2(centroid[1], sqrt(pow(centroid[0], 2) + pow(centroid[2], 2)));

  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
  pcl::transformPointCloud(*cloud, *transformed_cloud, transform);

  pcl::getMinMax3D(*transformed_cloud, min_pt, max_pt);
  Eigen::Vector4f transformed_bbox_center =
      Eigen::Vector4f((min_pt.x + max_pt.x) / 2, (min_pt.y + max_pt.y) / 2, (min_pt.z + max_pt.z) / 2, 1);
  Eigen::Vector4f bbox_center = transform.inverse() * transformed_bbox_center;
  Eigen::Quaternionf q(transform.inverse().rotation());

  detection3d.bbox.center.position.x = bbox_center[0];
  detection3d.bbox.center.position.y = bbox_center[1];
  detection3d.bbox.center.position.z = bbox_center[2];
  detection3d.bbox.center.orientation.x = q.x();
  detection3d.bbox.center.orientation.y = q.y();
  detection3d.bbox.center.orientation.z = q.z();
  detection3d.bbox.center.orientation.w = q.w();
  detection3d.bbox.size.x = max_pt.x - min_pt.x;
  detection3d.bbox.size.y = max_pt.y - min_pt.y;
  detection3d.bbox.size.z = max_pt.z - min_pt.z;
  detection3d.results = detections_results;
  detections3d_msg.detections.push_back(detection3d);
}

visualization_msgs::MarkerArray
TrackerWithCloudNode::createMarkerArray(const vision_msgs::Detection3DArray& detections3d_msg, const double& duration)
{
  visualization_msgs::MarkerArray marker_array;
  for (size_t i = 0; i < detections3d_msg.detections.size(); i++)
  {
    if (std::isfinite(detections3d_msg.detections[i].bbox.size.x) &&
        std::isfinite(detections3d_msg.detections[i].bbox.size.y) &&
        std::isfinite(detections3d_msg.detections[i].bbox.size.z))
    {
      visualization_msgs::Marker marker;
      marker.header = detections3d_msg.header;
      marker.ns = "detection";
      marker.id = i;
      marker.type = visualization_msgs::Marker::CUBE;
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose = detections3d_msg.detections[i].bbox.center;
      marker.scale.x = detections3d_msg.detections[i].bbox.size.x;
      marker.scale.y = detections3d_msg.detections[i].bbox.size.y;
      marker.scale.z = detections3d_msg.detections[i].bbox.size.z;
      marker.color.r = 0.0;
      marker.color.g = 1.0;
      marker.color.b = 0.0;
      marker.color.a = 0.5;
      marker.lifetime = ros::Duration(duration);
      marker_array.markers.push_back(marker);
    }
  }
  return marker_array;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tracker_with_cloud_node");
  TrackerWithCloudNode node;
  ros::spin();
}
