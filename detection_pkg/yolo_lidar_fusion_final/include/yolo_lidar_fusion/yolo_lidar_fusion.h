#ifndef PROJECT_PIXEL_CLOUD_FUSION_H
#define PROJECT_PIXEL_CLOUD_FUSION_H

#define __APP_NAME__ "yolo_lidar_fusion"

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

#include <ros/ros.h>
#include <tf/tf.h>

#include <deque>

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CameraInfo.h>
#include <jsk_recognition_msgs/BoundingBox.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/common/pca.h>
#include <pcl/common/transforms.h>
#include <pcl/io/pcd_io.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/crop_box.h>
#include <pcl/filters/extract_indices.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <Eigen/Eigen>
#include <Eigen/Geometry> 

#include <autoware_msgs/DetectedObjectArray.h>

#include <visualization_msgs/MarkerArray.h>
#include <opencv2/imgproc.hpp>
#include <image_geometry/pinhole_camera_model.h>
#include <opencv2/opencv.hpp>


#include <tf2_eigen/tf2_eigen.h>  // tf2와 Eigen 간의 변환을 위한 헤더
#include <tf2_geometry_msgs/tf2_geometry_msgs.h> // tf2의 변환 기능
#include <pcl/filters/passthrough.h>
#include <pcl/filters/crop_box.h>

namespace std {
  template <>
  class hash<cv::Point> {
  public:
    size_t operator()(const cv::Point& pixel_cloud) const {
      return hash<std::string>()(std::to_string(pixel_cloud.x) + "|" + std::to_string(pixel_cloud.y));
    }
  };
};
struct Box
{
 public:
	int id;
	Eigen::Vector3f position;
	Eigen::Vector3f dimension;
	Eigen::Quaternionf quaternion;

	Box() {};

	Box(int id, Eigen::Vector3f position, Eigen::Vector3f dimension)
		: id(id), position(position), dimension(dimension)
	{
		quaternion = Eigen::Quaternionf(1, 0, 0, 0);
	}

	Box(int id, Eigen::Vector3f position, Eigen::Vector3f dimension, Eigen::Quaternionf quaternion)
		: id(id), position(position), dimension(dimension), quaternion(quaternion)
	{}
};

struct BoundingBox {
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};
// autoware_msgs::DetectedObject transformAutowareObject(
//     const Box &box, const std_msgs::Header &header,
//     const geometry_msgs::Pose &pose_transformed) {
//   autoware_msgs::DetectedObject autoware_object;
//   autoware_object.header = header;
//   autoware_object.id = box.id;
//   autoware_object.label = "unknown";
//   autoware_object.score = 1.0f;
//   autoware_object.pose = pose_transformed;
//   autoware_object.pose_reliable = true;
//   autoware_object.dimensions.x = box.dimension(0);
//   autoware_object.dimensions.y = box.dimension(1);
//   autoware_object.dimensions.z = box.dimension(2);
//   autoware_object.valid = true;

//   return autoware_object;
// }

// void segmentGround(
//     const pcl::PointCloud<pcl::PointXYZ>::Ptr& input_cloud,  // Input cloud
//     pcl::PointCloud<pcl::PointXYZ>::Ptr& ground_cloud,       // Output: ground points
//     pcl::PointCloud<pcl::PointXYZ>::Ptr& non_ground_cloud,   // Output: non-ground points
//     int num_iterations,                                      // RANSAC max iterations
//     float distance_threshold,                                // Distance threshold for plane segmentation
//     bool optimize_coefficients = true                        // Optional: optimize plane coefficients
// ) {
//     // Segmentation object
//     pcl::SACSegmentation<pcl::PointXYZ> sac_seg;
//     sac_seg.setOptimizeCoefficients(optimize_coefficients);
//     sac_seg.setModelType(pcl::SACMODEL_PLANE);
//     sac_seg.setMethodType(pcl::SAC_RANSAC);
//     // sac_seg.setMethodType(pcl::SAC_RRANSAC);
//     sac_seg.setMaxIterations(num_iterations);
//     sac_seg.setDistanceThreshold(distance_threshold);

//     // 추가적으로 확률, 각도, 축 등을 설정 가능
//     sac_seg.setProbability(0.99);         // 성공 확률 설정 (기본값 0.99)
//     sac_seg.setEpsAngle(0.1);             // 각도 허용 오차 설정
//     Eigen::Vector3f axis(0.0, 0.0, 1.0);  // 수직 평면을 찾기 위한 축 설정
//     sac_seg.setAxis(axis);

//     // Point indices for the ground
//     pcl::PointIndices::Ptr ground_indices(new pcl::PointIndices);
//     pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
//     pcl::ExtractIndices<pcl::PointXYZ> extract;

//     // Segment the largest planar component (ground)
//     sac_seg.setInputCloud(input_cloud);
//     sac_seg.segment(*ground_indices, *coefficients);

//     if (ground_indices->indices.empty()) {
//         std::cerr << "No ground plane found!" << std::endl;
//         return;
//     }

//     // Extract ground points
//     extract.setInputCloud(input_cloud);
//     extract.setIndices(ground_indices);
//     extract.setNegative(false); // Keep ground points
//     extract.filter(*ground_cloud); // Store ground points in 'ground_cloud'

//     // Extract non-ground points
//     extract.setNegative(true); // Remove ground points, keep others
//     extract.filter(*non_ground_cloud); // Store non-ground points in 'non_ground_cloud'
// }




class ROSPixelCloudFusionApp {
  bool use_voxel_filter, use_ground_filter, pub_filtered_cloud, pub_fused_cloud, pub_fused_clustered_cloud, use_polygon_resize;
  float voxel_size;
  int num_iterations;
  float distance_threshold;
  double cluster_tolerance;
  int cluster_min_size, cluster_max_size;

  float min_width, min_height, scale_w, scale_h;
  float x_roi_threshold;
  
  ros::Subscriber image_subscriber_;                          // Front YOLO mask subscriber
  ros::Subscriber yolo_subscriber_;                          // Front YOLO mask subscriber
  void image_callback(const sensor_msgs::CompressedImage::ConstPtr& image_msg);
  void yolo_callback(const sensor_msgs::Image::ConstPtr& image_msg);

  sensor_msgs::CompressedImage::ConstPtr image_msg_;

  ros::NodeHandle node_handle_;                                // ROS node handle
  ros::Publisher publisher_fused_cloud_,publisher_filtered_cloud_, publisher_fused_clustered_cloud_, pub_jsk_bboxes, pub_autoware_objects, pub_marker_array;                       // Publisher for fused point cloud

  // Subscribers for left, right, back, and front camera intrinsics and YOLO masks
  ros::Subscriber intrinsics_subscriber_l_;                    // Left camera intrinsics subscriber
  ros::Subscriber intrinsics_subscriber_r_;                    // Right camera intrinsics subscriber
  ros::Subscriber intrinsics_subscriber_b_;                    // Back camera intrinsics subscriber
  ros::Subscriber intrinsics_subscriber_f_;                    // Front camera intrinsics subscriber
  ros::Subscriber cloud_subscriber_;                           // Point cloud subscriber
  ros::Subscriber mask_subscriber_l_;                          // Left YOLO mask subscriber
  ros::Subscriber mask_subscriber_r_;                          // Right YOLO mask subscriber
  ros::Subscriber mask_subscriber_b_;                          // Back YOLO mask subscriber
  ros::Subscriber mask_subscriber_f_;                          // Front YOLO mask subscriber

  tf::TransformListener* transform_listener_;                  // TF listener to get transformations
  tf::StampedTransform camera_lidar_tf_l_;                     // Left camera-lidar transform
  tf::StampedTransform camera_lidar_tf_r_;                     // Right camera-lidar transform
  tf::StampedTransform camera_lidar_tf_b_;                     // Back camera-lidar transform
  tf::StampedTransform camera_lidar_tf_f_;                     // Front camera-lidar transform
  Eigen::Matrix4f transform_l;
  Eigen::Matrix4f transform_r;
  Eigen::Matrix4f transform_f;
  Eigen::Matrix4f transform_b;
  std_msgs::Header mask_header_;                               // Mask header

  // Intrinsic parameters for left, right, back, and front cameras
  cv::Size image_size_l_;                                      // Image size for left camera
  cv::Size image_size_r_;                                      // Image size for right camera
  cv::Size image_size_b_;                                      // Image size for back camera
  cv::Size image_size_f_;                                      // Image size for front camera
  cv::Mat camera_intrinsics_l_;                                // Intrinsics matrix for left camera
  cv::Mat camera_intrinsics_r_;                                // Intrinsics matrix for right camera
  cv::Mat camera_intrinsics_b_;                                // Intrinsics matrix for back camera
  cv::Mat camera_intrinsics_f_;                                // Intrinsics matrix for front camera
  cv::Mat distortion_coefficients_l_;                          // Distortion coefficients for left camera
  cv::Mat distortion_coefficients_r_;                          // Distortion coefficients for right camera
  cv::Mat distortion_coefficients_b_;                          // Distortion coefficients for back camera
  cv::Mat distortion_coefficients_f_;                   // Distortion coefficients for front camera

  image_geometry::PinholeCameraModel camera_model_r;
  image_geometry::PinholeCameraModel camera_model_l;
  image_geometry::PinholeCameraModel camera_model_b;
  image_geometry::PinholeCameraModel camera_model_f;

    
  // Polygon masks for left, right, back, and front YOLO results
  std::vector<std::vector<cv::Point2f>> polygons_2d_l;         // Left camera 2D polygons
  std::vector<std::vector<cv::Point2f>> polygons_2d_r;         // Right camera 2D polygons
  std::vector<std::vector<cv::Point2f>> polygons_2d_b;         // Back camera 2D polygons
  std::vector<std::vector<cv::Point2f>> polygons_2d_f;         // Front camera 2D polygons
  std::vector<std::vector<cv::Point2f>> polygons_2d_l_;
  std::vector<std::vector<cv::Point2f>> polygons_2d_r_;
  std::vector<std::vector<cv::Point2f>> polygons_2d_b_;
  std::vector<std::vector<cv::Point2f>> polygons_2d_f_;

  // Frame ID for left, right, back, and front cameras
  std::string image_frame_id_l_;                               // Left camera frame ID
  std::string image_frame_id_r_;                               // Right camera frame ID
  std::string image_frame_id_b_;                               // Back camera frame ID
  std::string image_frame_id_f_;                               // Front camera frame ID

  double intensity_threshold;                                  // Intensity threshold for filtering points

  bool processing_;                                            // Flag to indicate if processing is ongoing
  bool camera_info_ok_l_;                                      // Flag for left camera info availability
  bool camera_info_ok_r_;                                      // Flag for right camera info availability
  bool camera_info_ok_b_;                                      // Flag for back camera info availability
  bool camera_info_ok_f_;                                      // Flag for front camera info availability
  bool camera_lidar_tf_ok_l_;                                  // Flag for left camera-lidar TF availability
  bool camera_lidar_tf_ok_r_;                                  // Flag for right camera-lidar TF availability
  bool camera_lidar_tf_ok_b_;                                  // Flag for back camera-lidar TF availability
  bool camera_lidar_tf_ok_f_;                                  // Flag for front camera-lidar TF availability

  // Intrinsic parameters for left, right, back, and front cameras
  float fx_l_, fy_l_, cx_l_, cy_l_;                            // Left camera intrinsic parameters
  float fx_r_, fy_r_, cx_r_, cy_r_;                            // Right camera intrinsic parameters
  float fx_b_, fy_b_, cx_b_, cy_b_;                            // Back camera intrinsic parameters
  float fx_f_, fy_f_, cx_f_, cy_f_;                            // Front camera intrinsic parameters

  // Transforms a point based on the provided transformation
  pcl::PointXYZ TransformPoint(const pcl::PointXYZ& in_point, const tf::StampedTransform& in_transform);

  // Callback function for processing point cloud
  void CloudCallback(const sensor_msgs::PointCloud2::ConstPtr& in_cloud_msg);

  // Callback functions for processing YOLO segmentation markers
  void SegmentCallback_l(const visualization_msgs::MarkerArray::ConstPtr& in_marker_msg);
  void SegmentCallback_r(const visualization_msgs::MarkerArray::ConstPtr& in_marker_msg);
  void SegmentCallback_b(const visualization_msgs::MarkerArray::ConstPtr& in_marker_msg);
  void SegmentCallback_f(const visualization_msgs::MarkerArray::ConstPtr& in_marker_msg);  // Front camera segmentation callback

  /*!
   * Obtains Transformation between two frames registered in the TF Tree
   * @param in_target_frame The target frame ID
   * @param in_source_frame The source frame ID
   * @return the found transformation in the tree
   */
  tf::StampedTransform FindTransform(const std::string& in_target_frame, const std::string& in_source_frame);

  // Intrinsics callbacks for left, right, back, and front cameras
  void IntrinsicsCallback_l(const sensor_msgs::CameraInfo& in_message);
  void IntrinsicsCallback_r(const sensor_msgs::CameraInfo& in_message);
  void IntrinsicsCallback_b(const sensor_msgs::CameraInfo& in_message);
  void IntrinsicsCallback_f(const sensor_msgs::CameraInfo& in_message);  // Front camera intrinsics callback

  /*!
   * Reads the config params from the command line and initializes the ROS communication.
   * @param in_private_handle ROS NodeHandle for private namespace
   */
  void InitializeROSIo(ros::NodeHandle& in_private_handle);


public:
  // Main run loop of the application
  void Run();

  // Constructor
  ROSPixelCloudFusionApp();
};

#endif // PROJECT_PIXEL_CLOUD_FUSION_H
