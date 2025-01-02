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


#include <imm_ukf_pda/imm_ukf_pda.h>

ImmUkfPda::ImmUkfPda()
  : target_id_(0)
  ,  // assign unique ukf_id_ to each tracking targets
  init_(false),
  frame_count_(0),
  has_subscribed_vectormap_(false),
  private_nh_("~")
{
  private_nh_.param<std::string>("tracking_frame", tracking_frame_, "map");
  private_nh_.param<int>("life_time_threshold", life_time_threshold_, 8);
  private_nh_.param<double>("gating_threshold", gating_threshold_, 9.22);
  private_nh_.param<double>("gate_probability", gate_probability_, 0.99);
  private_nh_.param<double>("detection_probability", detection_probability_, 0.9);
  private_nh_.param<double>("static_velocity_threshold", static_velocity_threshold_, 0.5);
  private_nh_.param<int>("static_num_history_threshold", static_num_history_threshold_, 3);
  private_nh_.param<double>("prevent_explosion_threshold", prevent_explosion_threshold_, 1000);
  private_nh_.param<double>("merge_distance_threshold", merge_distance_threshold_, 0.5);
  private_nh_.param<float>("vel_stable_threshold_", vel_stable_threshold_, 3);
  private_nh_.param<float>("yaw_stable_threshold_", yaw_stable_threshold_, 0.01);
  private_nh_.param<bool>("use_sukf", use_sukf_, false);
  // for vectormap assisted tracking
  private_nh_.param<bool>("use_vectormap", use_vectormap_, false);
  private_nh_.param<double>("lane_direction_chi_threshold", lane_direction_chi_threshold_, 2.71);
  private_nh_.param<double>("nearest_lane_distance_threshold", nearest_lane_distance_threshold_, 1.0);
  private_nh_.param<std::string>("vectormap_frame", vectormap_frame_, "map");

  // rosparam for benchmark
  private_nh_.param<bool>("is_benchmark", is_benchmark_, false);
  private_nh_.param<std::string>("kitti_data_dir", kitti_data_dir_, "");
  if (is_benchmark_)
  {
    result_file_path_ = kitti_data_dir_ + "benchmark_results.txt";
    std::remove(result_file_path_.c_str());
  }
}

void ImmUkfPda::run()
{
  pub_object_array_ = node_handle_.advertise<autoware_msgs::DetectedObjectArray>("objects_out", 1);
  pub_object_array_marker_ = node_handle_.advertise<visualization_msgs::MarkerArray>("objects_marker_out", 1);

  sub_front_detected_array_ = node_handle_.subscribe("objects_in_front", 1, &ImmUkfPda::front_callback, this);
  sub_front_cam_detected_array_ = node_handle_.subscribe("objects_in_front_cam", 1, &ImmUkfPda::front_cam_callback, this);
  sub_left_cam_detected_array_ = node_handle_.subscribe("objects_in_rlb_cam", 1, &ImmUkfPda::left_cam_callback, this);
  sub_right_cam_detected_array_ = node_handle_.subscribe("objects_in_right_cam", 1, &ImmUkfPda::right_cam_callback, this);
  sub_simul_detected_array_= node_handle_.subscribe("objects_in_simul", 1, &ImmUkfPda::simul_callback, this);;
  // sub_back_detected_array_= node_handle_.subscribe("objects_in_back", 1, &ImmUkfPda::back_callback, this);;
  // sub_side_detected_array_= node_handle_.subscribe("objects_in_side", 1, &ImmUkfPda::side_callback, this);;

  pose_sub = node_handle_.subscribe("/current_pose",1,&ImmUkfPda::poseCallback,this);

  private_nh_.param<double>("tracker_hz", tracker_hz_, 10.0);
  duration = 1 / tracker_hz_;
  tracker_timer = node_handle_.createTimer(ros::Duration(duration), &ImmUkfPda::publish_tracker, this);

  if (use_vectormap_)
  {
    vmap_.subscribe(private_nh_, vector_map::Category::POINT |
                                 vector_map::Category::NODE  |
                                 vector_map::Category::LANE, 1);
  }
}

void ImmUkfPda::poseCallback(const geometry_msgs::PoseStampedConstPtr& msg)
{
    curr_pose_header = msg->header;
    egoPose = msg->pose;
}

void ImmUkfPda::simul_callback(const autoware_msgs::DetectedObjectArray& input)
{
  autoware_msgs::DetectedObjectArray simul_detected_objects_;
  simul_detected_objects_.objects.clear();
  simul_input_header_ = input.header;

  for (const auto& obj : input.objects)
  {
    autoware_msgs::DetectedObject tmp_detected_object = obj;

    tmp_detected_object.valid = true;
    tmp_detected_object.label = "car";
    tmp_detected_object.pose_reliable = true;
    tmp_detected_object.velocity_reliable = true ;

    simul_detected_objects_.objects.push_back(tmp_detected_object);
  }
  
  simul_detected_objects = simul_detected_objects_;
  // std::cout << "simul_detected_objects size : " << simul_detected_objects.objects.size() << std:: endl;

}

void ImmUkfPda::front_callback(const autoware_msgs::DetectedObjectArray& input)
{
  autoware_msgs::DetectedObjectArray front_detected_objects_;

  front_detected_objects_.objects.clear();
  front_input_header_ = input.header;

  for (const auto& obj : input.objects)
  {
    front_detected_objects_.objects.push_back(obj);
  }
  
  front_detected_objects = front_detected_objects_;
  // std::cout << "front_detected_objects size : " << front_detected_objects.objects.size() << std:: endl;

}

void ImmUkfPda::front_cam_callback(const autoware_msgs::DetectedObjectArray& input)
{
  autoware_msgs::DetectedObjectArray front_cam_detected_objects_;

  front_cam_detected_objects_.objects.clear();

  for (const auto& obj : input.objects)
  {
    front_cam_detected_objects_.objects.push_back(obj);
  }
  
  front_cam_detected_objects = front_cam_detected_objects_;
  // std::cout << "front_cam_detected_objects size : " << front_cam_detected_objects.objects.size() << std:: endl;

}

void ImmUkfPda::left_cam_callback(const autoware_msgs::DetectedObjectArray& input)
{
  autoware_msgs::DetectedObjectArray left_cam_detected_objects_;

  left_cam_detected_objects_.objects.clear();

  for (const auto& obj : input.objects)
  {
    left_cam_detected_objects_.objects.push_back(obj);
  }
  
  left_cam_detected_objects = left_cam_detected_objects_;
  // std::cout << "left_cam_detected_objects size : " << left_cam_detected_objects.objects.size() << std:: endl;

}

// void ImmUkfPda::right_cam_callback(const autoware_msgs::DetectedObjectArray& input)
// {
//   autoware_msgs::DetectedObjectArray right_cam_detected_objects_;

//   right_cam_detected_objects_.objects.clear();

//   for (const auto& obj : input.objects)
//   {
//     right_cam_detected_objects_.objects.push_back(obj);
//   }
  
//   right_cam_detected_objects = right_cam_detected_objects_;
//   // std::cout << "right_cam_detected_objects size : " << right_cam_detected_objects.objects.size() << std:: endl;

// }

void ImmUkfPda::right_cam_callback(const autoware_msgs::DetectedObjectArray& input)
{
  autoware_msgs::DetectedObjectArray tmp_right_detected_objects_ = input;
  autoware_msgs::DetectedObjectArray right_cam_detected_objects_;

  for (const auto& obj : tmp_right_detected_objects_.objects)
  {
    autoware_msgs::DetectedObject tmp_objects_ = obj;

    tmp_objects_.pose.orientation.x = egoPose.orientation.x;
    tmp_objects_.pose.orientation.y = egoPose.orientation.y;
    tmp_objects_.pose.orientation.z = egoPose.orientation.z;
    tmp_objects_.pose.orientation.w = egoPose.orientation.w;

    float obj_dist_;
    obj_dist_ = std::sqrt(std::pow(egoPose.position.x - tmp_objects_.pose.position.x, 2) + std::pow(egoPose.position.y - tmp_objects_.pose.position.y, 2));
    obj_dist_ = std::round(obj_dist_ * 10.0) / 10.0; // 소수점 첫째 자리까지 반올림
    tmp_objects_.acceleration.linear.z = obj_dist_;

    // Round velocity to one decimal place
    float tmp_tv = std::sqrt(std::pow(tmp_objects_.velocity.linear.x, 2) + std::pow(tmp_objects_.velocity.linear.y, 2));
    tmp_tv = std::round(tmp_tv * 10.0) / 10.0; // 소수점 첫째 자리까지 반올림
    tmp_objects_.velocity.linear.z = tmp_tv;

    tmp_objects_.valid = true;
    tmp_objects_.label = "car";
    tmp_objects_.pose_reliable = true;
    tmp_objects_.velocity_reliable = true ;
    // std::cout << "callback : " << tmp_tv << std::endl;

    right_cam_detected_objects_.objects.push_back(tmp_objects_);
  }
  right_cam_detected_objects = right_cam_detected_objects_;

  // std::cout << "right_cam_detected_objects size : " << right_cam_detected_objects.objects.size() << std:: endl;

}

// void ImmUkfPda::side_callback(const autoware_msgs::DetectedObjectArray& input)
// {
//   autoware_msgs::DetectedObjectArray side_detected_objects_;

//   side_detected_objects_.objects.clear();

//   for (const auto& obj : input.objects)
//   {
//     side_detected_objects_.objects.push_back(obj);
//   }
  
//   side_detected_objects = side_detected_objects_;
//   // std::cout << "side_detected_objects size : " << side_detected_objects.objects.size() << std:: endl;

// }

// void ImmUkfPda::back_callback(const autoware_msgs::DetectedObjectArray& input)
// {
//   autoware_msgs::DetectedObjectArray back_detected_objects_;

//   back_detected_objects_.objects.clear();
//   back_input_header_ = input.header;

//   for (const auto& obj : input.objects)
//   {
//     back_detected_objects_.objects.push_back(obj);
//   }
  
//   back_detected_objects = back_detected_objects_;
// //   std::cout << "back_detected_objects size : " << back_detected_objects.objects.size() << std:: endl;

// }

void ImmUkfPda::publish_tracker(const ros::TimerEvent&)
{
  // if(use_vectormap_)
  // {
  //   checkVectormapSubscription();
  // }

  // bool success = updateNecessaryTransform();
  // if (!success)
  // {
  //   ROS_INFO("Could not find coordiante transformation");
  //   return;
  // }
  // std::cout << "input size : " << input.objects.size() << std:: endl;
  autoware_msgs::DetectedObjectArray front_detected_objects_ = front_detected_objects;
  autoware_msgs::DetectedObjectArray front_cam_detected_objects_ = front_cam_detected_objects;
  autoware_msgs::DetectedObjectArray left_cam_detected_objects_ = left_cam_detected_objects;
  // autoware_msgs::DetectedObjectArray right_cam_detected_objects_ = right_cam_detected_objects;
  // autoware_msgs::DetectedObjectArray back_detected_objects_ = back_detected_objects;
  // autoware_msgs::DetectedObjectArray side_detected_objects_ = side_detected_objects;
  geometry_msgs::Pose egoPose_ = egoPose;
  std_msgs::Header cur_header_ = curr_pose_header;


  autoware_msgs::DetectedObjectArray integrated_input;
  if (front_detected_objects_.objects.size() != 0){
    integrated_input.objects.insert(integrated_input.objects.end(), front_detected_objects_.objects.begin(), front_detected_objects_.objects.end());
    // ROS_INFO("front topic integrated!!");
  }

  if (front_cam_detected_objects_.objects.size() != 0){
    integrated_input.objects.insert(integrated_input.objects.end(), front_cam_detected_objects_.objects.begin(), front_cam_detected_objects_.objects.end());
    // ROS_INFO("front topic integrated!!");
  }

  if (left_cam_detected_objects_.objects.size() != 0){
    integrated_input.objects.insert(integrated_input.objects.end(), left_cam_detected_objects_.objects.begin(), left_cam_detected_objects_.objects.end());
    // ROS_INFO("left topic integrated!!");
  }

  // if (right_cam_detected_objects_.objects.size() != 0){
  //   integrated_input.objects.insert(integrated_input.objects.end(), right_cam_detected_objects_.objects.begin(), right_cam_detected_objects_.objects.end());
  //   // ROS_INFO("right topic integrated!!");
  // }
  
  // if (back_detected_objects_.objects.size() != 0){
  //   integrated_input.objects.insert(integrated_input.objects.end(), back_detected_objects_.objects.begin(), back_detected_objects_.objects.end());
  //   // ROS_INFO("back topic integrated!!");
  // }

  // if (side_detected_objects_.objects.size() != 0){
  //   integrated_input.objects.insert(integrated_input.objects.end(), side_detected_objects_.objects.begin(), side_detected_objects_.objects.end());
  //   // ROS_INFO("back topic integrated!!");
  // }

  // integrated_input.header = front_input_header_;

  autoware_msgs::DetectedObjectArray transformed_input;
  transformed_input.header = cur_header_;
  transformed_input.header.frame_id = tracking_frame_;
  autoware_msgs::DetectedObjectArray detected_objects_output;
  transformPoseToGlobal(integrated_input, transformed_input, egoPose_);

  tracker(transformed_input, detected_objects_output);

  pub_object_array_.publish(detected_objects_output);

  front_detected_objects_.objects.clear();
  front_cam_detected_objects_.objects.clear();
  left_cam_detected_objects_.objects.clear();
  // right_cam_detected_objects_.objects.clear();
  // if (is_benchmark_)
  // {
  //   dumpResultText(detected_objects_output);
  // }
}

void ImmUkfPda::checkVectormapSubscription()
{
  if (use_vectormap_ && !has_subscribed_vectormap_)
  {
    lanes_ = vmap_.findByFilter([](const vector_map_msgs::Lane& lane) { return true; });
    if (lanes_.empty())
    {
      ROS_INFO("Has not subscribed vectormap");
    }
    else
    {
      has_subscribed_vectormap_ = true;
    }
  }
}

bool ImmUkfPda::updateNecessaryTransform()
{
  bool success = true;
  // ROS_INFO("work");
  try
  {
    // ROS_INFO("work");

    // tf_listener_.waitForTransform(input_header_.frame_id, tracking_frame_, ros::Time(0), ros::Duration(1.0));
    // tf_listener_.lookupTransform(tracking_frame_, input_header_.frame_id, ros::Time(0), local2global_);
    // std::cout <<"tracking_frame" << tracking_frame_ << std::endl;
    // std::cout <<"input_frame" << input_header_.frame_id << std::endl;
  }
  catch (tf::TransformException ex)
  {
    ROS_ERROR("%s", ex.what());
    success = false;
  }
  if (use_vectormap_ && has_subscribed_vectormap_)
  {
    try
    {
      // tf_listener_.waitForTransform(vectormap_frame_, tracking_frame_, ros::Time(0), ros::Duration(1.0));
      // tf_listener_.lookupTransform(vectormap_frame_, tracking_frame_, ros::Time(0), tracking_frame2lane_frame_);
      // tf_listener_.lookupTransform(tracking_frame_, vectormap_frame_, ros::Time(0), lane_frame2tracking_frame_);
    }
    catch (tf::TransformException ex)
    {
      ROS_ERROR("%s", ex.what());
    }
  }
  return success;
}

// void ImmUkfPda::transformPoseToGlobal(const autoware_msgs::DetectedObjectArray& input,
//                                       autoware_msgs::DetectedObjectArray& transformed_input)
// {
//   transformed_input.header = input_header_;
//   transformed_input.header.frame_id = tracking_frame_;

//   for (auto const &object: input.objects)
//   {
//     geometry_msgs::Pose out_pose = getTransformedPose(object.pose, local2global_);
//     autoware_msgs::DetectedObject dd;
//     dd.header = input.header;
//     // dd.header.frame_id = "front";
//     // dd.header.frame_id = "livox_frame";
//     dd.header.frame_id = tracking_frame_;
//     // std::cout << tracking_frame_ << std::endl ;

//     dd = object;
//     dd.pose = out_pose;

//     transformed_input.objects.push_back(dd);
//   }
// }

void ImmUkfPda::transformPoseToGlobal(const autoware_msgs::DetectedObjectArray& input,
                                      autoware_msgs::DetectedObjectArray& transformed_input, const geometry_msgs::Pose egoPose_)
{
  if (egoPose_.position.x == 0 && egoPose_.position.y == 0){
    // std::cout << "current_pose not subscribed!! using relative pose.." << std::endl;
  }
  // std::cout << "transformed_input.header" << transformed_input.header << std::endl;

  //calculate yaw angle
  Eigen::Quaternionf ego_quaternion(egoPose_.orientation.w, egoPose_.orientation.x, egoPose_.orientation.y, egoPose_.orientation.z);

  // convert relative coordinate to global coordinate

  // calculated by comparing sensor data
  Eigen::Vector3f front_translation(0.752006, 0.224721, -0.156783);
  Eigen::Quaternionf front_quaternion(0.999993, -0.0034866, -0.000302554, -0.00115192);

  // TF back sensor offset: translation and quaternion (inverse)
  Eigen::Vector3f back_translation(-0.72137199, -0.25101566, 0.16962166);
  Eigen::Quaternionf back_quaternion(0.99999484, -0.00242582, -0.00106767, -0.00181802);

  // float front_sensor_offset_x = 1.0;
  // float front_sensor_offset_y = 0.2;

  // float back_sensor_offset_x = -1.0;
  // float back_sensor_offset_y = -0.2;

  for (const auto& object : input.objects) {
    Eigen::Vector3f sensor_translation(0.0, 0.0, 0.0);
    Eigen::Quaternionf sensor_quaternion_inverse(1.0, 0.0, 0.0, 0.0); 

    if (object.header.frame_id == front_input_header_.frame_id) {
      sensor_translation = front_translation;
      sensor_quaternion_inverse = front_quaternion;
    } else if (object.header.frame_id == back_input_header_.frame_id) {
      sensor_translation = back_translation;
      sensor_quaternion_inverse = back_quaternion;
    }


    // Convert object relative position to Eigen vector
    Eigen::Vector3f relative_position(object.pose.position.x, object.pose.position.y, object.pose.position.z);

    // Apply sensor offset and quaternion inverse to transform the relative position
    Eigen::Vector3f transformed_position = sensor_quaternion_inverse * (relative_position + sensor_translation);

    // Apply egoPose quaternion (full 3D rotation) and translation
    Eigen::Vector3f global_position = ego_quaternion * transformed_position + Eigen::Vector3f(egoPose_.position.x, egoPose_.position.y, egoPose_.position.z);

    // Convert object orientation to Eigen quaternion
    Eigen::Quaternionf object_orientation(object.pose.orientation.w, object.pose.orientation.x, object.pose.orientation.y, object.pose.orientation.z);

    // Apply sensor quaternion inverse and then ego quaternion to the orientation
    Eigen::Quaternionf transformed_orientation = ego_quaternion * (sensor_quaternion_inverse * object_orientation);

    autoware_msgs::DetectedObject dd;
    dd.header = transformed_input.header;
    dd.pose.position.x = global_position.x();
    dd.pose.position.y = global_position.y();
    dd.pose.position.z = global_position.z();

    // Update the orientation with the transformed quaternion
    dd.pose.orientation.w = transformed_orientation.w();
    dd.pose.orientation.x = transformed_orientation.x();
    dd.pose.orientation.y = transformed_orientation.y();
    dd.pose.orientation.z = transformed_orientation.z();

    transformed_input.objects.push_back(dd);
  
  }
}

// void ImmUkfPda::transformPoseToLocal(autoware_msgs::DetectedObjectArray& detected_objects_output)
// {
//   detected_objects_output.header = front_input_header_;

//   tf::Transform inv_local2global = local2global_.inverse();
//   tf::StampedTransform global2local;
//   global2local.setData(inv_local2global);
//   for (auto& object : detected_objects_output.objects)
//   {
//     geometry_msgs::Pose out_pose = getTransformedPose(object.pose, global2local);
//     object.header = front_input_header_;
//     object.pose = out_pose;
//   }
// }

geometry_msgs::Pose ImmUkfPda::getTransformedPose(const geometry_msgs::Pose& in_pose,
                                                  const tf::StampedTransform& tf_stamp)
{
  tf::Transform transform;
  geometry_msgs::PoseStamped out_pose;
  transform.setOrigin(tf::Vector3(in_pose.position.x, in_pose.position.y, in_pose.position.z));
  transform.setRotation(
      tf::Quaternion(in_pose.orientation.x, in_pose.orientation.y, in_pose.orientation.z, in_pose.orientation.w));
  geometry_msgs::PoseStamped pose_out;
  tf::poseTFToMsg(tf_stamp * transform, out_pose.pose);
  return out_pose.pose;
}

void ImmUkfPda::measurementValidation(const autoware_msgs::DetectedObjectArray& input, UKF& target,
                                      const bool second_init, const Eigen::VectorXd& max_det_z,
                                      const Eigen::MatrixXd& max_det_s,
                                      std::vector<autoware_msgs::DetectedObject>& object_vec,
                                      std::vector<bool>& matching_vec)
{
  // alert: different from original imm-pda filter, here picking up most likely measurement
  // if making it allows to have more than one measurement, you will see non semipositive definite covariance
  bool exists_smallest_nis_object = false;
  double smallest_nis = std::numeric_limits<double>::max();
  int smallest_nis_ind = 0;
  for (size_t i = 0; i < input.objects.size(); i++)
  {
    double x = input.objects[i].pose.position.x;
    double y = input.objects[i].pose.position.y;

    Eigen::VectorXd meas = Eigen::VectorXd(2);
    meas << x, y;

    Eigen::VectorXd diff = meas - max_det_z;
    double nis = diff.transpose() * max_det_s.inverse() * diff;

    if (nis < gating_threshold_)
    { 

      if (nis < smallest_nis)
      {
        smallest_nis = nis;
        target.object_ = input.objects[i];
        smallest_nis_ind = i;
        exists_smallest_nis_object = true;
      }
    }
  }
  if (exists_smallest_nis_object)
  {
    matching_vec[smallest_nis_ind] = true;
    if (use_vectormap_ && has_subscribed_vectormap_)
    {
      autoware_msgs::DetectedObject direction_updated_object;
      bool use_direction_meas =
          updateDirection(smallest_nis, target.object_, direction_updated_object, target);
      if (use_direction_meas)
      {
        object_vec.push_back(direction_updated_object);
      }
      else
      {
        object_vec.push_back(target.object_);
      }
    }
    else
    {
      object_vec.push_back(target.object_);
    }
  }
}

bool ImmUkfPda::updateDirection(const double smallest_nis, const autoware_msgs::DetectedObject& in_object,
                                    autoware_msgs::DetectedObject& out_object, UKF& target)
{
  bool use_lane_direction = false;
  target.is_direction_cv_available_ = false;
  target.is_direction_ctrv_available_ = false;
  bool get_lane_success = storeObjectWithNearestLaneDirection(in_object, out_object);
  if (!get_lane_success)
  {
    return use_lane_direction;
  }
  target.checkLaneDirectionAvailability(out_object, lane_direction_chi_threshold_, use_sukf_);
  if (target.is_direction_cv_available_ || target.is_direction_ctrv_available_)
  {
    use_lane_direction = true;
  }
  return use_lane_direction;
}

bool ImmUkfPda::storeObjectWithNearestLaneDirection(const autoware_msgs::DetectedObject& in_object,
                                                 autoware_msgs::DetectedObject& out_object)
{
  geometry_msgs::Pose lane_frame_pose = getTransformedPose(in_object.pose, tracking_frame2lane_frame_);
  double min_dist = std::numeric_limits<double>::max();

  double min_yaw = 0;
  for (auto const& lane : lanes_)
  {
    vector_map_msgs::Node node = vmap_.findByKey(vector_map::Key<vector_map_msgs::Node>(lane.bnid));
    vector_map_msgs::Point point = vmap_.findByKey(vector_map::Key<vector_map_msgs::Point>(node.pid));
    double distance = std::sqrt(std::pow(point.bx - lane_frame_pose.position.y, 2) +
                                std::pow(point.ly - lane_frame_pose.position.x, 2));
    if (distance < min_dist)
    {
      min_dist = distance;
      vector_map_msgs::Node front_node = vmap_.findByKey(vector_map::Key<vector_map_msgs::Node>(lane.fnid));
      vector_map_msgs::Point front_point = vmap_.findByKey(vector_map::Key<vector_map_msgs::Point>(front_node.pid));
      min_yaw = std::atan2((front_point.bx - point.bx), (front_point.ly - point.ly));
    }
  }

  bool success = false;
  if (min_dist < nearest_lane_distance_threshold_)
  {
    success = true;
  }
  else
  {
    return success;
  }

  // map yaw in rotation matrix representation
  tf::Quaternion map_quat = tf::createQuaternionFromYaw(min_yaw);
  tf::Matrix3x3 map_matrix(map_quat);

  // vectormap_frame to tracking_frame rotation matrix
  tf::Quaternion rotation_quat = lane_frame2tracking_frame_.getRotation();
  tf::Matrix3x3 rotation_matrix(rotation_quat);

  // rotated yaw in matrix representation
  tf::Matrix3x3 rotated_matrix = rotation_matrix * map_matrix;
  double roll, pitch, yaw;
  rotated_matrix.getRPY(roll, pitch, yaw);

  out_object = in_object;
  out_object.angle = yaw;
  return success;
}

void ImmUkfPda::updateTargetWithAssociatedObject(const std::vector<autoware_msgs::DetectedObject>& object_vec,
                                                 UKF& target)
{
  target.lifetime_++;
  if (!target.object_.label.empty() && target.object_.label !="unknown")
  {
    target.label_ = target.object_.label;
  }
  updateTrackingNum(object_vec, target);
  // if (target.tracking_num_ == TrackingState::Stable || target.tracking_num_ == TrackingState::Occlusion)
  // {
  //   target.is_stable_ = true;
  // }
}

void ImmUkfPda::updateBehaviorState(const UKF& target, const bool use_sukf, autoware_msgs::DetectedObject& object)
{
  if(use_sukf)
  {
    object.behavior_state = MotionModel::CTRV;
  }
  else if (target.mode_prob_cv_ > target.mode_prob_ctrv_ && target.mode_prob_cv_ > target.mode_prob_rm_)
  {
    object.behavior_state = MotionModel::CV;
  }
  else if (target.mode_prob_ctrv_ > target.mode_prob_cv_ && target.mode_prob_ctrv_ > target.mode_prob_rm_)
  {
    object.behavior_state = MotionModel::CTRV;
  }
  else
  {
    object.behavior_state = MotionModel::RM;
  }
}

void ImmUkfPda::initTracker(const autoware_msgs::DetectedObjectArray& input, double timestamp)
{
  for (size_t i = 0; i < input.objects.size(); i++)
  {
    double px = input.objects[i].pose.position.x;
    double py = input.objects[i].pose.position.y;
    Eigen::VectorXd init_meas = Eigen::VectorXd(2);
    init_meas << px, py;

    UKF ukf;
    ukf.initialize(init_meas, timestamp, target_id_);
    targets_.push_back(ukf);
    target_id_++;
  }
  timestamp_ = timestamp;
  init_ = true;
}

void ImmUkfPda::secondInit(UKF& target, const std::vector<autoware_msgs::DetectedObject>& object_vec, double dt)
{
  if (object_vec.size() == 0)
  {
    target.tracking_num_ = TrackingState::Die;
    return;
  }
  // record init measurement for env classification
  target.init_meas_ << target.x_merge_(0), target.x_merge_(1);

  // state update
  double target_x = object_vec[0].pose.position.x;
  double target_y = object_vec[0].pose.position.y;
  double target_diff_x = target_x - target.x_merge_(0);
  double target_diff_y = target_y - target.x_merge_(1);
  double target_yaw = atan2(target_diff_y, target_diff_x);
  double dist = sqrt(target_diff_x * target_diff_x + target_diff_y * target_diff_y);
  double target_v = dist / dt;
    // std::cout << "dt_secondInit : " << dt << std::endl;


  //KR
  // if (target_diff_x < 0){
//   if (sqrt(target_x * target_x + target_y * target_y) - sqrt(target.x_merge_(0) * target.x_merge_(0) + target.x_merge_(1) * target.x_merge_(1))
//  < 0)
//  {
//     target_v = -target_v;
//   }

  while (target_yaw > M_PI)
    target_yaw -= 2. * M_PI;
  while (target_yaw < -M_PI)
    target_yaw += 2. * M_PI;

  target.x_merge_(0) = target.x_cv_(0) = target.x_ctrv_(0) = target.x_rm_(0) = target_x;
  target.x_merge_(1) = target.x_cv_(1) = target.x_ctrv_(1) = target.x_rm_(1) = target_y;
  target.x_merge_(2) = target.x_cv_(2) = target.x_ctrv_(2) = target.x_rm_(2) = target_v;
  target.x_merge_(3) = target.x_cv_(3) = target.x_ctrv_(3) = target.x_rm_(3) = target_yaw;
  // std::cout << "target_v : " << target_v << std::endl;
  target.tracking_num_++;
  return;
}

void ImmUkfPda::updateTrackingNum(const std::vector<autoware_msgs::DetectedObject>& object_vec, UKF& target)
{
  if (object_vec.size() > 0)
  {
    if (target.tracking_num_ < TrackingState::Stable)
    {
      target.tracking_num_++;
    }
    else if (target.tracking_num_ == TrackingState::Stable)
    {
      target.tracking_num_ = TrackingState::Stable;
    }
    else if (target.tracking_num_ >= TrackingState::Stable && target.tracking_num_ < TrackingState::Lost)
    {
      target.tracking_num_ = TrackingState::Stable;
    }
    else if (target.tracking_num_ == TrackingState::Lost)
    {
      target.tracking_num_ = TrackingState::Die;
    }
  }
  else
  {
    if (target.tracking_num_ < TrackingState::Stable)
    {
      target.tracking_num_ = TrackingState::Die;
    }
    else if (target.tracking_num_ >= TrackingState::Stable && target.tracking_num_ < TrackingState::Lost)
    {
      target.tracking_num_++;
    }
    else if (target.tracking_num_ == TrackingState::Lost)
    {
      target.tracking_num_ = TrackingState::Die;
    }
  }

  return;
}

bool ImmUkfPda::probabilisticDataAssociation(const autoware_msgs::DetectedObjectArray& input, const double dt,
                                             std::vector<bool>& matching_vec,
                                             std::vector<autoware_msgs::DetectedObject>& object_vec, UKF& target)
{
  double det_s = 0;
  Eigen::VectorXd max_det_z;
  Eigen::MatrixXd max_det_s;
  bool success = true;

  if (use_sukf_)
  {
    max_det_z = target.z_pred_ctrv_;
    max_det_s = target.s_ctrv_;
    det_s = max_det_s.determinant();
  }
  else
  {
    // find maxDetS associated with predZ
    target.findMaxZandS(max_det_z, max_det_s);
    det_s = max_det_s.determinant();
  }
  // std::cout << "det_s : " << det_s << std::endl;

  // prevent ukf not to explode
  if (std::isnan(det_s) || det_s > prevent_explosion_threshold_)
  {
    target.tracking_num_ = TrackingState::Die;
    success = false;

    // std::cout << "ukf explode!!!!!!" << std::endl;
    return success;
  }

  bool is_second_init;
  if (target.tracking_num_ == TrackingState::Init)
  {
    is_second_init = true;
  }
  else
  {
    is_second_init = false;
  }

  // measurement gating
  measurementValidation(input, target, is_second_init, max_det_z, max_det_s, object_vec, matching_vec);

  // second detection for a target: update v and yaw
  if (is_second_init)
  {
    secondInit(target, object_vec, dt);
    success = false;
    return success;
  }

  updateTargetWithAssociatedObject(object_vec, target);

  if (target.tracking_num_ == TrackingState::Die)
  {
    success = false;
    return success;
  }
  return success;

}

void ImmUkfPda::makeNewTargets(const double timestamp, const autoware_msgs::DetectedObjectArray& input,
                               const std::vector<bool>& matching_vec)
{
  for (size_t i = 0; i < input.objects.size(); i++)
  {
    if (matching_vec[i] == false)
    {
      // std::cout << "new target generated!!" << std::endl;
      double px = input.objects[i].pose.position.x;
      double py = input.objects[i].pose.position.y;
      Eigen::VectorXd init_meas = Eigen::VectorXd(2);
      init_meas << px, py;

      UKF ukf;
      ukf.initialize(init_meas, timestamp, target_id_);
      ukf.object_ = input.objects[i];
      targets_.push_back(ukf);
      target_id_++;
    }
  }
}

void ImmUkfPda::staticClassification()
{
  for (size_t i = 0; i < targets_.size(); i++)
  {
    // targets_[i].x_merge_(2) is referred for estimated velocity
    double current_velocity = std::abs(targets_[i].x_merge_(2));
    targets_[i].vel_history_.push_back(current_velocity);
    if (targets_[i].tracking_num_ == TrackingState::Stable && targets_[i].lifetime_ > life_time_threshold_)
    {
      int index = 0;
      double sum_vel = 0;
      double avg_vel = 0;
      for (auto rit = targets_[i].vel_history_.rbegin(); index < static_num_history_threshold_; ++rit)
      {
        index++;
        sum_vel += *rit;
      }
      avg_vel = double(sum_vel / static_num_history_threshold_);

      if(avg_vel < static_velocity_threshold_ && current_velocity < static_velocity_threshold_)
      {
        targets_[i].is_static_ = true;
      }
    }
  }
}

bool
ImmUkfPda::arePointsClose(const geometry_msgs::Point& in_point_a,
                                const geometry_msgs::Point& in_point_b,
                                float in_radius)
{
  return (fabs(in_point_a.x - in_point_b.x) <= in_radius) && (fabs(in_point_a.y - in_point_b.y) <= in_radius);
}

bool
ImmUkfPda::arePointsEqual(const geometry_msgs::Point& in_point_a,
                               const geometry_msgs::Point& in_point_b)
{
  return arePointsClose(in_point_a, in_point_b, CENTROID_DISTANCE); // CENTROID_DISTANCE default : 0.2
}

bool
ImmUkfPda::isPointInPool(const std::vector<geometry_msgs::Point>& in_pool,
                          const geometry_msgs::Point& in_point)
{
  for(size_t j=0; j<in_pool.size(); j++)
  {
    if (arePointsEqual(in_pool[j], in_point))
    {
      return true;
    }
  }
  return false;
}

autoware_msgs::DetectedObjectArray
ImmUkfPda::removeRedundantObjects(const autoware_msgs::DetectedObjectArray& in_detected_objects,
                            const std::vector<size_t> in_tracker_indices)
{
  if (in_detected_objects.objects.size() != in_tracker_indices.size())
    return in_detected_objects;

  autoware_msgs::DetectedObjectArray resulting_objects;
  resulting_objects.header = in_detected_objects.header;

  std::vector<geometry_msgs::Point> centroids;
  //create unique points
  for(size_t i=0; i<in_detected_objects.objects.size(); i++)
  {
    if(!isPointInPool(centroids, in_detected_objects.objects[i].pose.position))
    {
      centroids.push_back(in_detected_objects.objects[i].pose.position);
    }
  }
  //assign objects to the points
  std::vector<std::vector<size_t>> matching_objects(centroids.size());
  for(size_t k=0; k<in_detected_objects.objects.size(); k++)
  {
    const auto& object=in_detected_objects.objects[k];
    for(size_t i=0; i< centroids.size(); i++)
    {
      if (arePointsClose(object.pose.position, centroids[i], merge_distance_threshold_))
      {
        matching_objects[i].push_back(k);//store index of matched object to this point
      }
    }
  }
  //get oldest object on each point
  for(size_t i=0; i< matching_objects.size(); i++)
  {
    size_t oldest_object_index = 0;
    int oldest_lifespan = -1;
    std::string best_label;
    for(size_t j=0; j<matching_objects[i].size(); j++)
    {
      size_t current_index = matching_objects[i][j];
      int current_lifespan = targets_[in_tracker_indices[current_index]].lifetime_;
      if (current_lifespan > oldest_lifespan)
      {
        oldest_lifespan = current_lifespan;
        oldest_object_index = current_index;
      }
      if (!targets_[in_tracker_indices[current_index]].label_.empty() &&
        targets_[in_tracker_indices[current_index]].label_ != "unknown")
      {
        best_label = targets_[in_tracker_indices[current_index]].label_;
      }
    }
    // delete nearby targets except for the oldest target
    for(size_t j=0; j<matching_objects[i].size(); j++)
    {
      size_t current_index = matching_objects[i][j];
      if(current_index != oldest_object_index)
      {
        targets_[in_tracker_indices[current_index]].tracking_num_= TrackingState::Die;
      }
    }
    autoware_msgs::DetectedObject best_object;
    best_object = in_detected_objects.objects[oldest_object_index];
    if (best_label != "unknown"
        && !best_label.empty())
    {
      best_object.label = best_label;
    }

    resulting_objects.objects.push_back(best_object);
  }

  return resulting_objects;

}

void ImmUkfPda::makeOutput(const autoware_msgs::DetectedObjectArray& input,
                           const std::vector<bool> &matching_vec,
                           autoware_msgs::DetectedObjectArray& detected_objects_output)
{
  autoware_msgs::DetectedObjectArray tmp_objects;
  tmp_objects.header = input.header;
  tmp_objects.header.frame_id = tracking_frame_;

  std::vector<size_t> used_targets_indices;
  // std::cout << "targets_.size() = " << targets_.size() << std::endl;
  for (size_t i = 0; i < targets_.size(); i++)
  {
    // ukf.x_merge_ : [pos1 pos2 vel_abs yaw_angle yaw_rate] in SI units and rad
    double tx = targets_[i].x_merge_(0);
    double ty = targets_[i].x_merge_(1);
    double tv = targets_[i].x_merge_(2);
    double tyaw = targets_[i].x_merge_(3);
    double tyaw_rate = targets_[i].x_merge_(4);
    double tv_x, tv_y;

    while (tyaw > M_PI)
      tyaw -= 2. * M_PI;
    while (tyaw < -M_PI)
      tyaw += 2. * M_PI;

    tf::Quaternion q = tf::createQuaternionFromYaw(tyaw);
    // std::cout << "id : " << targets_[i].ukf_id_ << "  -------------------" << std::endl;
    // std::cout << "tv : " << tv << std::endl;
    tv_x = tv * std::cos(tyaw);
    tv_y = tv * std::sin(tyaw);

    autoware_msgs::DetectedObject dd;
    dd = targets_[i].object_;
    dd.id = targets_[i].ukf_id_;
    // dd.velocity.linear.x = tv;
    // dd.acceleration.linear.y = tyaw_rate;
    dd.pose.position.x = tx;
    dd.pose.position.y = ty;

    // Calculate distance from ego pose and round to one decimal place
    obj_dist = std::sqrt(std::pow(egoPose.position.x - tx, 2) + std::pow(egoPose.position.y - ty, 2));
    obj_dist = std::round(obj_dist * 10.0) / 10.0; // 소수점 첫째 자리까지 반올림
    dd.acceleration.linear.z = obj_dist;

    dd.variance.x = targets_[i].p_merge_(0, 0); // variance for tx
    dd.variance.y = targets_[i].p_merge_(1, 1); // variance for ty
    dd.variance.z = targets_[i].p_merge_(2, 2); // variance for tv
    dd.color.r = targets_[i].p_merge_(3, 3); // variance for tyaw
    dd.color.g = targets_[i].p_merge_(4, 4); // variance for tyaw
    geometry_msgs::Polygon polygon;

    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            geometry_msgs::Point32 point;
            point.x = static_cast<float>(targets_[i].p_merge_(row, col));  
            point.y = 0.0f; 
            point.z = 0.0f; 
            polygon.points.push_back(point);
        }
    }
    dd.convex_hull.polygon = polygon;
    
    if ((targets_[i].p_merge_(3, 3) < yaw_stable_threshold_ || targets_[i].p_merge_(2, 2) < vel_stable_threshold_) &&
         targets_[i].tracking_num_ >= TrackingState::Init){ //&& targets_[i].tracking_num_ <= 7 ){ // TrackingState::Occlusion = 5
      targets_[i].is_stable_ = true;
    }

    else targets_[i].is_stable_ = false;
    // std::cout << "determinant() : "<< targets_[i].p_merge_.determinant() << std::endl;
    // std::cout << "p_merge_(4, 4)() : "<< targets_[i].p_merge_(4, 4) << std::endl;
    // std::cout << "p_merge_(3, 3)() : "<< targets_[i].p_merge_(3, 3) << std::endl;
    // std::cout << "p_merge_(2, 2)() : "<< targets_[i].p_merge_(2, 2) << std::endl;
    // std::cout << "p_merge_(1, 1)() : "<< targets_[i].p_merge_(1, 1) << std::endl;

    // std::cout << "targets_[i].tracking_num_ : "<< targets_[i].tracking_num_ << std::endl;


    dd.velocity_reliable = targets_[i].is_stable_;
    dd.pose_reliable = targets_[i].is_stable_;
    dd.x = targets_[i].tracking_num_;

    if (targets_[i].is_stable_)
    {
      // // Aligh the longest side of dimentions with the estimated orientation
      // if(targets_[i].object_.dimensions.x < targets_[i].object_.dimensions.y)
      // {
      //   dd.dimensions.x = targets_[i].object_.dimensions.y;
      //   dd.dimensions.y = targets_[i].object_.dimensions.x;
      // }

      if (!std::isnan(q[0]))
        dd.pose.orientation.x = q[0];
      if (!std::isnan(q[1]))
        dd.pose.orientation.y = q[1];
      if (!std::isnan(q[2]))
        dd.pose.orientation.z = q[2];
      if (!std::isnan(q[3]))
        dd.pose.orientation.w = q[3];

      dd.velocity.angular.z = tyaw_rate;
      dd.velocity.linear.x = tv_x;
      dd.velocity.linear.y = tv_y;

      // Round velocity to one decimal place
      tv = std::round(tv * 10.0) / 10.0; // 소수점 첫째 자리까지 반올림
      dd.velocity.linear.z = tv;
    }

    else {

      if (!std::isnan(egoPose.orientation.x))
        dd.pose.orientation.x = egoPose.orientation.x;
      if (!std::isnan(egoPose.orientation.y))
        dd.pose.orientation.y = egoPose.orientation.y;
      if (!std::isnan(egoPose.orientation.z))
        dd.pose.orientation.z = egoPose.orientation.z;
      if (!std::isnan(egoPose.orientation.w))
        dd.pose.orientation.w = egoPose.orientation.w;

      dd.velocity.angular.z = 0.0;
      dd.velocity.linear.x = 0.0;
      dd.velocity.linear.y = 0.0;
      dd.velocity.linear.z = 0.0;
    }
    updateBehaviorState(targets_[i], use_sukf_, dd);

    // if (targets_[i].is_stable_ || (targets_[i].tracking_num_ >= TrackingState::Init &&
    //                                targets_[i].tracking_num_ < TrackingState::Stable))
    if (tv < 70.0 ){
      if ( //targets_[i].is_stable_ && 
          targets_[i].tracking_num_ >= TrackingState::Init &&
          targets_[i].tracking_num_ <= TrackingState::Occlusion )
      // if (targets_[i].is_stable_ || (targets_[i].tracking_num_ < TrackingState::Stable))
      {
        tmp_objects.objects.push_back(dd);
        used_targets_indices.push_back(i);
      }  
    }
    
  }
  detected_objects_output = removeRedundantObjects(tmp_objects, used_targets_indices);
  // std::cout << "---------------------------" << std::endl;
}

void ImmUkfPda::removeUnnecessaryTarget()
{
  std::vector<UKF> temp_targets;
  for (size_t i = 0; i < targets_.size(); i++)
  {
    if (targets_[i].tracking_num_ != TrackingState::Die)
    {
      temp_targets.push_back(targets_[i]);
    }
  }
  std::vector<UKF>().swap(targets_);
  targets_ = temp_targets;
}

void ImmUkfPda::makeMarker(const autoware_msgs::DetectedObjectArray& detected_objects_output)
{
    visualization_msgs::MarkerArray marker_array;
    // int id = 0; // Unique identifier for each marker
    // std::cout << "detected_objects_output : " << detected_objects_output.objects.size() << std::endl;
    for (const auto& object : detected_objects_output.objects)
    {
        // Create a marker for the bounding box
        visualization_msgs::Marker box_marker;
        box_marker.lifetime = ros::Duration(duration);

        box_marker.header = detected_objects_output.header;
        box_marker.ns = "detected_objects_box";
        box_marker.id = object.id;
        box_marker.type = visualization_msgs::Marker::CUBE;
        box_marker.action = visualization_msgs::Marker::ADD;
        box_marker.pose = object.pose;

        // double min_dimension = std::min(object.dimensions.x, object.dimensions.y);
        box_marker.scale.x = 1.0;
        box_marker.scale.y = 1.0;
        box_marker.scale.z = 1.0; // z dimension remains the same
        
        // Create a marker for the direction arrow
        visualization_msgs::Marker arrow_marker;
        arrow_marker.lifetime = ros::Duration(duration);
        
        arrow_marker.header = detected_objects_output.header;
        arrow_marker.ns = "detected_objects_arrow";
        arrow_marker.id = object.id;
        arrow_marker.type = visualization_msgs::Marker::ARROW;
        arrow_marker.action = visualization_msgs::Marker::ADD;

        // Set the start point of the arrow (center of the object)
        arrow_marker.points.resize(2);
        arrow_marker.points[0].x = object.pose.position.x;
        arrow_marker.points[0].y = object.pose.position.y;
        arrow_marker.points[0].z = object.pose.position.z;

        // Set the end point of the arrow based on heading (quaternion)
        double arrow_length = 3.0; // Length of the arrow
        arrow_marker.points[1].x = object.pose.position.x + arrow_length * cos(tf::getYaw(object.pose.orientation));
        arrow_marker.points[1].y = object.pose.position.y + arrow_length * sin(tf::getYaw(object.pose.orientation));
        arrow_marker.points[1].z = object.pose.position.z;

        arrow_marker.scale.x = 1; // Shaft diameter
        arrow_marker.scale.y = 2; // Head diameter
        arrow_marker.scale.z = 3; // Head length

        // Create a marker for the text
        visualization_msgs::Marker text_marker;
        text_marker.lifetime = ros::Duration(duration);
        
        text_marker.header = detected_objects_output.header;
        text_marker.ns = "detected_objects_text";
        text_marker.id = object.id;
        text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        text_marker.action = visualization_msgs::Marker::ADD;
        text_marker.pose.position.x = object.pose.position.x; // Position text at the object's pose
        text_marker.pose.position.y = object.pose.position.y + 4.0 ; // Position text at the object's pose

        text_marker.pose.position.z += object.dimensions.z / 2.0 + 0.5; // Raise the text above the box marker

        text_marker.scale.z = 5.0; // Height of the text

        std::stringstream ss;
        ss << "ID: " << object.id << ", v: " << object.velocity.linear.z << ", d: " << object.acceleration.linear.z;
        text_marker.text = ss.str(); // text_marker.text에 최종 문자열 설정

        if (object.pose_reliable == true){
          box_marker.color.r = 1.0f;
          box_marker.color.g = 1.0f;
          box_marker.color.b = 1.0f;
          box_marker.color.a = 1.0f; // semi-transparent
          marker_array.markers.push_back(box_marker);

          arrow_marker.color.r = 1.0f;
          arrow_marker.color.g = 1.0f;
          arrow_marker.color.b = 1.0f;
          arrow_marker.color.a = 1.0f; // fully opaque
          marker_array.markers.push_back(arrow_marker);

        }
        
        else {
          box_marker.color.r = 1.0f;
          box_marker.color.g = 0.0f;
          box_marker.color.b = 0.0f;
          box_marker.color.a = 1.0f; // semi-transparent
          marker_array.markers.push_back(box_marker);

          arrow_marker.color.r = 1.0f;
          arrow_marker.color.g = 0.0f;
          arrow_marker.color.b = 0.0f;
          arrow_marker.color.a = 1.0f; // fully opaque
          marker_array.markers.push_back(arrow_marker);

        }

        text_marker.color.r = 1.0f;
        text_marker.color.g = 1.0f;
        text_marker.color.b = 1.0f;
        text_marker.color.a = 1.0f; // fully opaque
        marker_array.markers.push_back(text_marker);

    }
    pub_object_array_marker_.publish(marker_array);
}

// void ImmUkfPda::dumpResultText(autoware_msgs::DetectedObjectArray& detected_objects)
// {
//   std::ofstream outputfile(result_file_path_, std::ofstream::out | std::ofstream::app);
//   for (size_t i = 0; i < detected_objects.objects.size(); i++)
//   {
//     double yaw = tf::getYaw(detected_objects.objects[i].pose.orientation);

//     // KITTI tracking benchmark data format:
//     // (frame_number,tracked_id, object type, truncation, occlusion, observation angle, x1,y1,x2,y2, h, w, l, cx, cy,
//     // cz, yaw)
//     // x1, y1, x2, y2 are for 2D bounding box.
//     // h, w, l, are for height, width, length respectively
//     // cx, cy, cz are for object centroid

//     // Tracking benchmark is based on frame_number, tracked_id,
//     // bounding box dimentions and object pose(centroid and orientation) from bird-eye view
//     outputfile << std::to_string(frame_count_) << " " << std::to_string(detected_objects.objects[i].id) << " "
//                << "Unknown"
//                << " "
//                << "-1"
//                << " "
//                << "-1"
//                << " "
//                << "-1"
//                << " "
//                << "-1 -1 -1 -1"
//                << " " << std::to_string(detected_objects.objects[i].dimensions.x) << " "
//                << std::to_string(detected_objects.objects[i].dimensions.y) << " "
//                << "-1"
//                << " " << std::to_string(detected_objects.objects[i].pose.position.x) << " "
//                << std::to_string(detected_objects.objects[i].pose.position.y) << " "
//                << "-1"
//                << " " << std::to_string(yaw) << "\n";
//   }
//   frame_count_++;
// }

void ImmUkfPda::tracker(const autoware_msgs::DetectedObjectArray& input,
                        autoware_msgs::DetectedObjectArray& detected_objects_output)
{
  double timestamp = input.header.stamp.toSec();
  // std::cout << "timestamp : " << dt << std::endl;

  std::vector<bool> matching_vec(input.objects.size(), false);

  if (!init_)
  {
    initTracker(input, timestamp);
    makeOutput(input, matching_vec, detected_objects_output);
    return;
  }

  double dt = (timestamp - timestamp_);
  timestamp_ = timestamp;
  // std::cout << "dt : " << dt << std::endl;


  // start UKF process
  for (size_t i = 0; i < targets_.size(); i++)
  {
    targets_[i].is_stable_ = false;
    targets_[i].is_static_ = false;

    if (targets_[i].tracking_num_ == TrackingState::Die)
    {
      continue;
    }
    // prevent ukf not to explode
    if (targets_[i].p_merge_.determinant() > prevent_explosion_threshold_ ||
        targets_[i].p_merge_(4, 4) > prevent_explosion_threshold_)
    {
      targets_[i].tracking_num_ = TrackingState::Die;
      continue;
    }

    targets_[i].prediction(use_sukf_, has_subscribed_vectormap_, dt);
    std::vector<autoware_msgs::DetectedObject> object_vec;
    bool success = probabilisticDataAssociation(input, dt, matching_vec, object_vec, targets_[i]);

    if (!success)
    {
      continue;
    }

    targets_[i].update(use_sukf_, detection_probability_, gate_probability_, gating_threshold_, object_vec);
  }
  // end UKF process

  // making new ukf target for no data association objects
  makeNewTargets(timestamp, input, matching_vec);

  // static dynamic classification
  staticClassification();

  // making output for visualization
  makeOutput(input, matching_vec, detected_objects_output);

  if (simul_detected_objects.objects.size() != 0){
    detected_objects_output.objects.insert(detected_objects_output.objects.end(), simul_detected_objects.objects.begin(), simul_detected_objects.objects.end());
    ROS_INFO("simulation topic integrated!!");
  }
  // std::cout <<  right_cam_detected_objects.objects.size() << std::endl;
  if (right_cam_detected_objects.objects.size() != 0){
    detected_objects_output.objects.insert(detected_objects_output.objects.end(), right_cam_detected_objects.objects.begin(), right_cam_detected_objects.objects.end());
    ROS_INFO("mob topic integrated!!");
  }

  makeMarker(detected_objects_output);

  // remove unnecessary ukf object
  removeUnnecessaryTarget();

}
