#ifndef UTILS_H
#define UTILS_H

#include "yolo_lidar_fusion/yolo_lidar_fusion.h"

#include <autoware_msgs/DetectedObjectArray.h>
#include <std_msgs/Header.h>
#include <geometry_msgs/Pose.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/shared_ptr.hpp>

#include <opencv2/core.hpp>
#include <sensor_msgs/CameraInfo.h>
// #include <geometry_msgs/Pose.h>
#include <cv_bridge/cv_bridge.h>

// 함수 선언
autoware_msgs::DetectedObject transformAutowareObject(const Box&, const std_msgs::Header&, const geometry_msgs::Pose&);

void segmentGround(const boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& input_cloud,
                   boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& ground_cloud,
                   boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& non_ground_cloud,
                   int max_iterations, float distance_threshold, bool optimize_coefficients);
void applyCropBoxFilter(const boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& input_cloud,
                        boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& output_cloud,
                        const Eigen::Vector4f& min_pt, const Eigen::Vector4f& max_pt, bool set_negative);
void applyVoxelGridFilter(const boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& input_cloud,
                          boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ>>& output_cloud, 
                          float voxel_size);

Eigen::Matrix4f transformTFToEigenMatrix(const tf::StampedTransform& tf_transform);
bool IsPointInPolygon(const std::vector<cv::Point2f>& polygon, float x, float y);
Box axisAlignedBoundingBox(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cluster, int id);
Box axisAlignedBoundingBox(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cluster, int id, const float x_roi_threshold);
void AdjustPolygonSize(std::vector<cv::Point2f>& polygon, float min_width, float min_height, float scale_x_manual, float scale_y_manual);
void DrawPolygon(cv::Mat& image, const std::vector<cv::Point2f>& polygon, const cv::Scalar& color, int thickness);
void projectLidarToImage(const sensor_msgs::CompressedImage::ConstPtr& image_msg, pcl::PointCloud<pcl::PointXYZI>::Ptr& cloud, const Eigen::Matrix4f& transform,\
 const image_geometry::PinholeCameraModel cm, const float fx_l_, const float fy_l_, const float cx_l_, const float cy_l_, const std::vector<std::vector<cv::Point2f>>polygons);

#endif // UTILS_H
