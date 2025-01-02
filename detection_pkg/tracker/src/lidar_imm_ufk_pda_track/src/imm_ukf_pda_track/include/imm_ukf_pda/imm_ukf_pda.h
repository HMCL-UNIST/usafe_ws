/*
 * Copyright 2018-2019 Autoware Foundation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OBJECT_TRACKING_IMM_UKF_JPDAF_H
#define OBJECT_TRACKING_IMM_UKF_JPDAF_H


#include <vector>
#include <chrono>
#include <stdio.h>
#include <cmath>

#include <ros/ros.h>
#include <ros/package.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>

#include <tf/transform_listener.h>

#include <vector_map/vector_map.h>

#include "autoware_msgs/DetectedObject.h"
#include "autoware_msgs/DetectedObjectArray.h"

#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <geometry_msgs/Pose.h>

#include "ukf.h"

class ImmUkfPda
{
private:
  int target_id_;
  bool init_;
  double timestamp_;

  std::vector<UKF> targets_;

  // probabilistic data association params
  double gating_threshold_;
  double gate_probability_;
  double detection_probability_;

  // object association param
  int life_time_threshold_;

  // static classification param
  double static_velocity_threshold_;
  int static_num_history_threshold_;

  // switch sukf and ImmUkfPda
  bool use_sukf_;

  // whether if benchmarking tracking result
  bool is_benchmark_;
  int frame_count_;
  std::string kitti_data_dir_;

  // for benchmark
  std::string result_file_path_;

  // prevent explode param for ukf
  double prevent_explosion_threshold_;
  float vel_stable_threshold_;
  float yaw_stable_threshold_;

  // for vectormap assisted tarcking
  bool use_vectormap_;
  bool has_subscribed_vectormap_;
  double lane_direction_chi_threshold_;
  double nearest_lane_distance_threshold_;
  std::string vectormap_frame_;
  vector_map::VectorMap vmap_;
  std::vector<vector_map_msgs::Lane> lanes_;

  double merge_distance_threshold_;
  const double CENTROID_DISTANCE = 0.2;//distance to consider centroids the same

  std::string input_topic_;
  std::string output_topic_;

  std::string tracking_frame_;

  tf::TransformListener tf_listener_;
  tf::StampedTransform local2global_;
  tf::StampedTransform tracking_frame2lane_frame_;
  tf::StampedTransform lane_frame2tracking_frame_;

  ros::NodeHandle node_handle_;
  ros::NodeHandle private_nh_;
  ros::Subscriber sub_front_detected_array_;
  ros::Subscriber sub_front_cam_detected_array_;
  ros::Subscriber sub_left_cam_detected_array_;
  ros::Subscriber sub_right_cam_detected_array_;
  ros::Subscriber sub_back_detected_array_;
  ros::Subscriber sub_simul_detected_array_;
  ros::Subscriber sub_side_detected_array_;
  ros::Timer tracker_timer;


  ros::Subscriber pose_sub;
  ros::Publisher pub_object_array_;
  ros::Publisher pub_object_array_marker_;

  autoware_msgs::DetectedObjectArray front_detected_objects;
  autoware_msgs::DetectedObjectArray front_cam_detected_objects;
  autoware_msgs::DetectedObjectArray left_cam_detected_objects;
  autoware_msgs::DetectedObjectArray right_cam_detected_objects;
  autoware_msgs::DetectedObjectArray back_detected_objects;
  autoware_msgs::DetectedObjectArray side_detected_objects;
  autoware_msgs::DetectedObjectArray simul_detected_objects;

  std_msgs::Header input_header_;
  std_msgs::Header front_input_header_;
  std_msgs::Header side_input_header_;
  std_msgs::Header back_input_header_;
  std_msgs::Header simul_input_header_;
  std_msgs::Header curr_pose_header;
  geometry_msgs::Pose egoPose;
  geometry_msgs::Twist egovel;
  float global_x, global_y;
  float obj_dist;

  double tracker_hz_, duration;

  void front_callback(const autoware_msgs::DetectedObjectArray& input);

  void front_cam_callback(const autoware_msgs::DetectedObjectArray& input);

  void left_cam_callback(const autoware_msgs::DetectedObjectArray& input);

  void right_cam_callback(const autoware_msgs::DetectedObjectArray& input);

  void simul_callback(const autoware_msgs::DetectedObjectArray& input);

  void back_callback(const autoware_msgs::DetectedObjectArray& input);

  void side_callback(const autoware_msgs::DetectedObjectArray& input);

  void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg);

  void publish_tracker(const ros::TimerEvent&);

  void transformPoseToGlobal(const autoware_msgs::DetectedObjectArray& input,
                             autoware_msgs::DetectedObjectArray& transformed_input, const geometry_msgs::Pose egoPose_);
  void transformPoseToLocal(autoware_msgs::DetectedObjectArray& detected_objects_output);

  geometry_msgs::Pose getTransformedPose(const geometry_msgs::Pose& in_pose,
                                                const tf::StampedTransform& tf_stamp);

  bool updateNecessaryTransform();

  void measurementValidation(const autoware_msgs::DetectedObjectArray& input, UKF& target, const bool second_init,
                             const Eigen::VectorXd& max_det_z, const Eigen::MatrixXd& max_det_s,
                             std::vector<autoware_msgs::DetectedObject>& object_vec, std::vector<bool>& matching_vec);
  autoware_msgs::DetectedObject getNearestObject(UKF& target,
                                                 const std::vector<autoware_msgs::DetectedObject>& object_vec);
  void updateBehaviorState(const UKF& target, const bool use_sukf, autoware_msgs::DetectedObject& object);

  void initTracker(const autoware_msgs::DetectedObjectArray& input, double timestamp);
  void secondInit(UKF& target, const std::vector<autoware_msgs::DetectedObject>& object_vec, double dt);

  void updateTrackingNum(const std::vector<autoware_msgs::DetectedObject>& object_vec, UKF& target);

  bool probabilisticDataAssociation(const autoware_msgs::DetectedObjectArray& input, const double dt,
                                    std::vector<bool>& matching_vec,
                                    std::vector<autoware_msgs::DetectedObject>& object_vec, UKF& target);
  void makeNewTargets(const double timestamp, const autoware_msgs::DetectedObjectArray& input,
                      const std::vector<bool>& matching_vec);

  void staticClassification();

  void makeOutput(const autoware_msgs::DetectedObjectArray& input,
                  const std::vector<bool>& matching_vec,
                  autoware_msgs::DetectedObjectArray& detected_objects_output);

  void makeMarker(const autoware_msgs::DetectedObjectArray& detected_objects_output);

  void removeUnnecessaryTarget();

  void dumpResultText(autoware_msgs::DetectedObjectArray& detected_objects);

  void tracker(const autoware_msgs::DetectedObjectArray& transformed_input,
               autoware_msgs::DetectedObjectArray& detected_objects_output);

  bool updateDirection(const double smallest_nis, const autoware_msgs::DetectedObject& in_object,
                           autoware_msgs::DetectedObject& out_object, UKF& target);

  bool storeObjectWithNearestLaneDirection(const autoware_msgs::DetectedObject& in_object,
                                      autoware_msgs::DetectedObject& out_object);

  void checkVectormapSubscription();

  autoware_msgs::DetectedObjectArray
  removeRedundantObjects(const autoware_msgs::DetectedObjectArray& in_detected_objects,
                         const std::vector<size_t> in_tracker_indices);

  autoware_msgs::DetectedObjectArray
  forwardNonMatchedObject(const autoware_msgs::DetectedObjectArray& tmp_objects,
                          const autoware_msgs::DetectedObjectArray&  input,
                          const std::vector<bool>& matching_vec);

  bool
  arePointsClose(const geometry_msgs::Point& in_point_a,
                 const geometry_msgs::Point& in_point_b,
                 float in_radius);

  bool
  arePointsEqual(const geometry_msgs::Point& in_point_a,
                 const geometry_msgs::Point& in_point_b);

  bool
  isPointInPool(const std::vector<geometry_msgs::Point>& in_pool,
                const geometry_msgs::Point& in_point);

  void updateTargetWithAssociatedObject(const std::vector<autoware_msgs::DetectedObject>& object_vec,
                                        UKF& target);

public:
  ImmUkfPda();
  void run();
};

#endif /* OBJECT_TRACKING_IMM_UKF_JPDAF_H */
