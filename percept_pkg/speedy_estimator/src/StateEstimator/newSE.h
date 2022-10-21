/*
* Software License Agreement (BSD License)
* Copyright (c) 2013, Georgia Institute of Technology
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**********************************************
 * @file StateEstimator.cpp
 * @author Paul Drews <pdrews3@gatech.edu>
 * @author Edited by Hojin Lee <hojinlee@unist.ac.kr> / Ilseung Yoon <y1seung@unist.ac.kr>
 * @date May 1, 2017 / modified Oct 11, 2022
 * @copyright 2017 Georgia Institute of Technology / 2022 Ulsan National Institue of Sciend and Technology
 * @brief ROS node to fuse information sources and create an accurate state estimation *
 * @details Subscribes to other pose estimate solution, GPS, IMU, and wheel odometry topics, claculates
 * an estimate of the car's current state using GTSAM, and publishes that data.
 ***********************************************/

#ifndef StateEstimator_H_
#define StateEstimator_H_

#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/base/timing.h>
#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/navigation/GPSFactor.h>

#include <list>
#include <iostream>
#include <fstream>
#include <queue>
#include <mutex>

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <tf/transform_broadcaster.h>

#include "BlockingQueue.h"

#define PI 3.14159265358979323846264338

class StateEstimator{
private:   
    ros::NodeHandle nh_;
    ros::Subscriber gps_sub_, imu_sub_, lidar_odom_sub_, gnss_pose_sub_;
    ros::Publisher pose_pub_, est_pose_pub_, bias_acc_pub_, bias_gyro_pub_, time_pub_, gps_pose_pub_;

    tf::TransformBroadcaster tf_br_map_to_gps_; // Need to select the "base" frame of the car to use

    double last_imu_time_, last_imu_use_time_, last_node_time_;
    double accel_bias_sigma_, gyro_bias_sigma_;
    double gps_sigma_, lidar_odom_sigma_, gnss_pose_sigma_;
    int max_queue_size_;

    /* Sensor msgs Queue */
    BlockingQueue<sensor_msgs::NavSatFixConstPtr> gps_opt_queue_;
    BlockingQueue<sensor_msgs::ImuConstPtr> imu_opt_queue_;
    BlockingQueue<nav_msgs::OdometryConstPtr> lidar_odom_opt_queue_;
    BlockingQueue<geometry_msgs::PoseStampedConstPtr> gnss_pose_opt_queue_;

    /* Optimized state */
    std::mutex optimized_state_mutex_;
    std::mutex isam_mutex_;
    gtsam::NavState optimized_state_;
    double optimized_time_;
    boost::shared_ptr<gtsam::PreintegratedImuMeasurements> imu_predictor_;
    double imu_dt_;
    gtsam::imuBias::ConstantBias optimized_bias_, previous_bias_;
    gtsam::Pose3 last_lidar_odom_pose_;
    sensor_msgs::ImuConstPtr last_imu_;
    boost::shared_ptr<gtsam::PreintegrationParams> preintegration_params_;

    std::list<sensor_msgs::ImuConstPtr> imu_measurements_;

    geometry_msgs::PoseStampedConstPtr initial_pose_;
    // sensor_msgs::ImuConstPtr initial_imu_   /* May need to use Or imu_3dm_gx4::FilterOutput can be used it has bias which we can use directly */ 
    gtsam::Pose3 base_to_gps_T_; /* Transfromation between sensors */
    gtsam::Pose3 imu_to_gps_T_;
    gtsam::Pose3 lidar_to_gps_T;

    /* Origin */
    bool fixed_origin_;
    GeographicLib::LocalCartesian enu_;
    int utm_zone_;
    bool utm_northp_;
    double utm_origin_x_, utm_origin_y_, utm_origin_z_;
    bool using_lidar_odom_, using_gnss_pose_;
    double max_gps_error_, max_gnss_pose_error_, max_lidar_odom_error_;

    /* GTSAM */
    gtsam::SharedDiagonal prior_noise_pose_;
    gtsam::SharedDiagonal prior_noise_vel_;
    gtsam::SharedDiagonal prior_noise_bias_;
    gtsam::Vector noise_model_between_bias_sigma_;
    gtsam::ISAM2 *isam_;

    gtsam::NonlinearFactorGraph new_graph_;
    gtsam::Values new_variables_;

    gtsam::Pose3 prev_pose_;
    gtsam::Vector3 prev_vel_;
    gtsam::imuBias::ConstantBias prev_bias_;

    bool is_graph_made_;
    bool optimizer_real_time_;
    double optimizer_hz_;
    int node_key_;

    nav_msgs::OdometryConstPtr last_lidar_odom_;
    geometry_msgs::PoseStampedConstPtr last_gnss_pose_;
    
public:
    StateEstimator();
    ~StateEstimator();
    void gpsCallback(sensor_msgs::NavSatFixConstPtr fix);
    void imuCallback(sensor_msgs::ImuConstPtr imu);
    void lidarOdomCallback(nav_msgs::OdometryConstPtr lidar_odom);
    void gnssPoseCallback(geometry_msgs::PoseStampedConstPtr gnss_pose);
    void constructPoseGraph();
    void runISAM2opt();
    void isamOptimizer();  
    

    void getAccGyro(sensor_msgs::ImuConstPtr imu, gtsam::Vector3 &acc, gtsam::Vector3 &gyro);

};

#endif /* StateEstimator_H_ */
