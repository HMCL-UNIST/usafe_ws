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

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>

#include <boost/thread/thread.hpp>
#include <vector>
#include "newSE.h"

#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>

using namespace gtsam;
// Convenience for named keys
using symbol_shorthand::X; // State
using symbol_shorthand::V; // Velocity
using symbol_shorthand::B; // IMU bias
using symbol_shorthand::G; // GPS pose

// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )

StateEstimator::StateEstimator():
    nh_("~"),
    last_imu_time_(0.0),
    last_imu_use_time_(0.0),
    max_queue_size_(0),
    gps_opt_queue_(40),
    gnss_pose_opt_queue_(40),
    imu_opt_queue_(400),
    lidar_odom_opt_queue_(100),
    is_graph_made_(false)
{
    // temporary variables to retrieve parameters
    double acc_sigma, gyro_sigma, init_vel_noise, init_bias_noise_acc, init_bias_noise_gyro, init_rot_noise,
        sensor_x, sensor_y, sensor_z, sensor_roll, sensor_pitch, sensor_yaw, lidar_x, lidar_y, lidar_z, lidar_roll, lidar_pitch, lidar_yaw,
        gravity_magnitude;

    nh_.param<double>("InitialRotationNoise", init_rot_noise, 1.0);
    nh_.param<double>("InitialVelocityNoise", init_vel_noise, 0.1);
    nh_.param<double>("InitialBiasNoiseAcc", init_bias_noise_acc, 1e-1);
    nh_.param<double>("InitialBiasNoiseGyro", init_bias_noise_gyro, 1e-2);
    nh_.param<double>("AccelerometerSigma", acc_sigma, 6.0e-2);
    nh_.param<double>("GyroSigma", gyro_sigma, 2.0e-2);
    nh_.param<double>("AccelBiasSigma", accel_bias_sigma_, 2.0e-4);
    nh_.param<double>("GyroBiasSigma", gyro_bias_sigma_, 3.0e-5);
    nh_.param<double>("GPSSigma", gps_sigma_, 0.07);
    nh_.param<double>("gnssPoseSigma", gnss_pose_sigma_, 0.01);
    nh_.param<double>("lidarOdomSigma", lidar_odom_sigma_, 0.001);
    nh_.param<double>("SensorTransformX", sensor_x, 0.0);
    nh_.param<double>("SensorTransformY", sensor_y, 0.0);
    nh_.param<double>("SensorTransformZ", sensor_z, 0.0);
    nh_.param<double>("SensorXAngle",  sensor_roll, 0);
    nh_.param<double>("SensorYAngle", sensor_pitch, 0);
    nh_.param<double>("SensorZAngle",   sensor_yaw, 0);
    nh_.param<double>("Gravity",   gravity_magnitude, 9.81);
    nh_.param<double>("Imudt", imu_dt_, 1.0/200.0);

    double imu_gps_x, imu_gps_y, imu_gps_z;
    nh_.param<double>("imu_gps_x",  imu_gps_x, 0);
    nh_.param<double>("imu_gps_y",  imu_gps_y, 0);
    nh_.param<double>("imu_gps_z",  imu_gps_z, 0);
    imu_to_gps_T_ = Pose3(Rot3(), Point3(imu_gps_x, imu_gps_y, imu_gps_z));
    imu_to_gps_T_.print("IMU->GPS");

    nh_.param<double>("lidar_roll",  lidar_roll, 0);
    nh_.param<double>("lidar_pitch",  lidar_pitch, 0);
    nh_.param<double>("lidar_yaw",  lidar_yaw, 0);
    nh_.param<double>("lidar_x",  lidar_x, 0);
    nh_.param<double>("lidar_y",  lidar_y, 0);
    nh_.param<double>("lidar_z",  lidar_z, 0);

    bool fixed_initial_pose_;
    double initial_roll, initial_pitch, initial_yaw;

    nh_.param<bool>("FixedInitialPose", fixed_initial_pose_, false);
    nh_.param<double>("initial_roll", initial_roll, 0);
    nh_.param<double>("initial_pitch", initial_pitch, 0);
    nh_.param<double>("initial_yaw", initial_yaw, 0);

    double lat_origin, lon_origin, alt_origin;
    nh_.param<bool>("FixedOrigin", fixed_origin_, false);
    nh_.param<double>("lat_origin", lat_origin, 0);
    nh_.param<double>("lon_origin", lon_origin, 0);
    nh_.param<double>("alt_origin", alt_origin, 0);

    nh_.param<double>("utm_x_origin", utm_origin_x_, 0);
    nh_.param<double>("utm_y_origin", utm_origin_y_, 0);
    nh_.param<double>("utm_z_origin", utm_origin_z_, 0);

    nh_.param<bool>("UseOdom", using_lidar_odom_, false);
    nh_.param<bool>("UseLocalPose", using_gnss_pose_, false);
    nh_.param<double>("MaxGPSError", max_gps_error_, 10.0);
    nh_.param<double>("maxLocalPoseError", max_gnss_pose_error_, 10.0);

    nh_.param<bool>("optimizer_real_time", optimizer_real_time_, true);
    nh_.param<double>("optimizer_hz", optimizer_hz_, 1.0);

    if (fixed_origin_){
        enu_.Reset(lat_origin, lon_origin, alt_origin);
    }

    std::cout << "InitialRotationNoise " << init_rot_noise << "\n"
    << "InitialVelocityNoise " << init_vel_noise << "\n"
    << "InitialBiasNoiseAcc " << init_bias_noise_acc << "\n"
    << "InitialBiasNoiseGyro " << init_bias_noise_gyro << "\n"
    << "AccelerometerSigma " << acc_sigma << "\n"
    << "GyroSigma " << gyro_sigma << "\n"
    << "AccelBiasSigma " << accel_bias_sigma_ << "\n"
    << "GyroBiasSigma " << gyro_bias_sigma_ << "\n"
    << "GPSSigma " << gps_sigma_ << "\n"
    << "SensorTransformX " << sensor_x << "\n"
    << "SensorTransformY " << sensor_y << "\n"
    << "SensorTransformZ " << sensor_z << "\n"
    << "sensor_roll " <<  sensor_roll << "\n"
    << "SensorYAngle " << sensor_pitch << "\n"
    << "SensorZAngle " <<   sensor_yaw << "\n"
    << "Gravity " <<   gravity_magnitude << "\n";

    // Use an ENU frame
    preintegration_params_ =  PreintegrationParams::MakeSharedU(gravity_magnitude);
    preintegration_params_->accelerometerCovariance = acc_sigma * I_3x3;
    preintegration_params_->gyroscopeCovariance = gyro_sigma * I_3x3;
    preintegration_params_->integrationCovariance = 1e-5 * I_3x3;

    Vector biases((Vector(6) << 0, 0, 0, 0, 0, 0).finished());
    optimized_bias_ = imuBias::ConstantBias(biases);
    previous_bias_ = imuBias::ConstantBias(biases);
    imu_predictor_ = boost::make_shared<PreintegratedImuMeasurements>(preintegration_params_, optimized_bias_);

    optimized_time_ = 0;

    // imu_3dm_gx4::FilterOutputConstPtr initial_pose_;
    
    // if (!fixed_initial_pose_)
    // {
        while (!initial_pose_)
        {
        ROS_WARN("Waiting for valid initial orientation");
        // initial_pose_ = ros::topic::waitForMessage<nav_msgs::Imu>("/imu_correct2", nh_, ros::Duration(15));
        initial_pose_ = ros::topic::waitForMessage<geometry_msgs::PoseStamped>("/gnss_pose_world", nh_, ros::Duration(15));
        }
    // }
    // else
    // {
    //     ROS_WARN("Using fixed initial orientation");
    //     Rot3 initialRotation = Rot3::Ypr(initial_yaw, initial_pitch, initial_roll);
    // }

    last_lidar_odom_pose_ = Pose3(Rot3::RzRyRx(0.0, 0.0, 0.0),
        Point3(0.0, 0.0, 0.0));
    
    base_to_gps_T_ = Pose3(Rot3::RzRyRx(sensor_roll, sensor_pitch, sensor_yaw),
        Point3(sensor_x, sensor_y, sensor_z));

    base_to_gps_T_.print("Body pose\n");
    
    lidar_to_gps_T = Pose3(Rot3::RzRyRx(lidar_roll, lidar_pitch, lidar_yaw),
        Point3(lidar_x, lidar_y, lidar_z));

    lidar_to_gps_T.print("Lidar To GPS");

    pose_pub_ = nh_.advertise<nav_msgs::Odometry>("pose", 1);
    est_pose_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("estimated_pose", 1);
    bias_acc_pub_ = nh_.advertise<geometry_msgs::Point>("bias_acc", 1);
    bias_gyro_pub_ = nh_.advertise<geometry_msgs::Point>("bias_gyro", 1);
    time_pub_ = nh_.advertise<geometry_msgs::Point>("time_delays", 1);
    gps_pose_pub_ = nh_.advertise<geometry_msgs::PoseWithCovarianceStamped>("gps_pos", 1);

    ISAM2Params params;
    params.factorization = ISAM2Params::QR;
    isam_ = new ISAM2(params);

    // prior on the first pose
    prior_noise_pose_ = noiseModel::Diagonal::Sigmas(
        (Vector(6) << init_rot_noise, init_rot_noise, init_rot_noise,
            gps_sigma_, gps_sigma_, gps_sigma_).finished());

    // Add velocity prior
    prior_noise_vel_ = noiseModel::Diagonal::Sigmas(
        (Vector(3) << init_vel_noise, init_vel_noise, init_vel_noise).finished());

    // Add bias prior
    prior_noise_bias_ = noiseModel::Diagonal::Sigmas(
        (Vector(6) << init_bias_noise_acc,
            init_bias_noise_acc,
            init_bias_noise_acc,
            init_bias_noise_gyro,
            init_bias_noise_gyro,
            init_bias_noise_gyro).finished());

    Vector sigma_acc_bias_c(3), sigma_gyro_bias_c(3);
    sigma_acc_bias_c << accel_bias_sigma_,  accel_bias_sigma_,  accel_bias_sigma_;
    sigma_gyro_bias_c << gyro_bias_sigma_, gyro_bias_sigma_, gyro_bias_sigma_;
    noise_model_between_bias_sigma_ = (Vector(6) << sigma_acc_bias_c, sigma_gyro_bias_c).finished();

    gps_sub_ = nh_.subscribe("gps", 300, &StateEstimator::gpsCallback, this);
    imu_sub_ = nh_.subscribe("imu", 600, &StateEstimator::imuCallback, this);
    
    lidar_odom_sub_ = nh_.subscribe("lidar_odom", 300, &StateEstimator::lidarOdomCallback, this);
    
    gnss_pose_sub_ = nh_.subscribe("gnss_pose", 300, &StateEstimator::gnssPoseCallback, this);

    boost::thread posegraph_builder(&StateEstimator::constructPoseGraph,this);
    
    if(!optimizer_real_time_){
        boost::thread optimizer(&StateEstimator::isamOptimizer,this); // if real time is not possible...
    }
}

void StateEstimator::gpsCallback(sensor_msgs::NavSatFixConstPtr fix){
    if(!gps_opt_queue_.pushNonBlocking(fix))
        ROS_WARN("Dropping a GPS measurement due to full queue!!");
}

void StateEstimator::imuCallback(sensor_msgs::ImuConstPtr imu){
    double dt;
    if (last_imu_time_ == 0) dt = 0.05; /* 200 Hz*/ 
    else dt = TIME(imu) - last_imu_time_;

    last_imu_time_ = TIME(imu);

    /* Push imu measurements */
    if(!imu_opt_queue_.pushNonBlocking(imu))
        ROS_WARN("Dropping an IMU measurement due to full queue!!");

    // Each time we get an imu measurement, calculate the incremental pose from the last GTSAM pose
    imu_measurements_.push_back(imu);
    //Grab the most current optimized state 
    double optimized_time;
    NavState optimized_state;
    imuBias::ConstantBias optimized_bias;
    
    optimized_state_mutex_.lock();
    optimized_time = optimized_time_;
    optimized_state = optimized_state_;
    optimized_bias = optimized_bias_;
    optimized_state_mutex_.unlock();

    if(optimized_time == 0) return; //haven't optimized first state yet

    bool left_measurements = false;
    int num_imu_discarded = 0;
    double imu_queue_prev_time;
    Vector3 acc, gyro;
    while (!imu_measurements_.empty() && (TIME(imu_measurements_.front()) < optimized_time)){ //Discard imu meas got before the optimized time
        imu_queue_prev_time = TIME(imu_measurements_.front());
        imu_measurements_.pop_front();
        left_measurements = true; // Right?
        num_imu_discarded++;
    }

    if(left_measurements){
        // reset Integration
        imu_predictor_->resetIntegration();
        int num_measurements = 0;
        for(auto it=imu_measurements_.begin(); it!=imu_measurements_.end(); ++it){ //iterate with imu got after optimized time
            double dt_temp = TIME(*it) - imu_queue_prev_time;
            imu_queue_prev_time = TIME(*it);
            getAccGyro(*it, acc, gyro);
            imu_predictor_->integrateMeasurement(acc, gyro, dt_temp);
            num_measurements++;
        }
    }
    else{
        getAccGyro(imu,acc,gyro);
        imu_predictor_->integrateMeasurement(acc, gyro,dt);
    }

    // Predict next state given the imu measurements - Odometry
    NavState current_pose = imu_predictor_->predict(optimized_state, optimized_bias);
    nav_msgs::Odometry pose_new;
    pose_new.header.stamp = imu->header.stamp;

    Vector4 q = current_pose.quaternion().coeffs();
    pose_new.pose.pose.orientation.x = q[0];
    pose_new.pose.pose.orientation.y = q[1];
    pose_new.pose.pose.orientation.z = q[2];
    pose_new.pose.pose.orientation.w = q[3];

    pose_new.pose.pose.position.x = current_pose.position().x();
    pose_new.pose.pose.position.y = current_pose.position().y();
    pose_new.pose.pose.position.z = current_pose.position().z();

    pose_new.twist.twist.linear.x = current_pose.velocity().x();
    pose_new.twist.twist.linear.y = current_pose.velocity().y();
    pose_new.twist.twist.linear.z = current_pose.velocity().z();
    
    pose_new.twist.twist.angular.x = gyro.x() + optimized_bias.gyroscope().x();
    pose_new.twist.twist.angular.y = gyro.y() + optimized_bias.gyroscope().y();
    pose_new.twist.twist.angular.z = gyro.z() + optimized_bias.gyroscope().z();

    pose_new.child_frame_id = "base_link";
    pose_new.header.frame_id = "map";

    pose_pub_.publish(pose_new);

    /* TF broadcasting */
    tf::Transform transform;
    transform.setOrigin( tf::Vector3(pose_new.pose.pose.position.x, pose_new.pose.pose.position.y, pose_new.pose.pose.position.z) );
    tf::Quaternion q_tmp(pose_new.pose.pose.orientation.x,pose_new.pose.pose.orientation.y,pose_new.pose.pose.orientation.z,pose_new.pose.pose.orientation.w);      
    transform.setRotation(q_tmp);
    tf_br_map_to_gps_.sendTransform(tf::StampedTransform(transform, pose_new.header.stamp, "map", "gnss_link"));

    // PoseStamped
    geometry_msgs::PoseStamped est_pose_new;
    est_pose_new.header = pose_new.header;
    est_pose_new.pose.position = pose_new.pose.pose.position;
    est_pose_new.pose.orientation = pose_new.pose.pose.orientation;
    est_pose_new.header.frame_id = "/map";
    est_pose_pub_.publish(est_pose_new);

    // Time delay debugging
    geometry_msgs::Point delays;
    delays.x = TIME(imu);
    delays.y = (ros::Time::now() - imu->header.stamp).toSec();
    delays.z = TIME(imu) - optimized_time;
    time_pub_.publish(delays);

}

void StateEstimator::lidarOdomCallback(nav_msgs::OdometryConstPtr lidar_odom){
    if (using_lidar_odom_){
        if(!lidar_odom_opt_queue_.pushNonBlocking(lidar_odom)){
            ROS_WARN("Dropping an lidar odom measurements due to full queue!!");
        }
    }
}

void StateEstimator::gnssPoseCallback(geometry_msgs::PoseStampedConstPtr gnss_pose){
    if(using_gnss_pose_){
        if(!gnss_pose_opt_queue_.pushNonBlocking(gnss_pose)){
            ROS_WARN("Dropping an GNSS pose measurements due to full queue!!");
        }
    }
}

void StateEstimator::constructPoseGraph(){
    // while(1)
    double start_time;
    int last_lidar_odom_key = 1;
    node_key_ = 0;
    int last_gps_key = 0;
    prev_vel_ = (Vector(3) << 0.0, 0.0, 0.0).finished();
    bool skip = false;
    

    while(ros::ok()){
        while( //!gps_opt_queue_.empty() ||
                ( (!gnss_pose_opt_queue_.empty() && using_gnss_pose_) ||
                    (!lidar_odom_opt_queue_.empty() && using_lidar_odom_) ) &&
                imu_opt_queue_.size() > 0 ){
            
            isam_mutex_.lock();
            if(!is_graph_made_){ //pose graph is not yet made
                sensor_msgs::NavSatFixConstPtr fix = gps_opt_queue_.popBlocking();
                start_time = TIME(fix);

                // Check there is an imu measurement before gps 
                if(imu_opt_queue_.empty()){
                    ROS_WARN_THROTTLE(1, "no IMU messages before first fix, continuing until there is");
                    continue;
                }

                // error if the IMU and GPS have some gap in timestamp
                double most_recent_imu_time = imu_opt_queue_.back()->header.stamp.toSec();
                if(std::abs(most_recent_imu_time - start_time) > 0.1){
                    ROS_ERROR_STREAM("There is a very large difference in the GPS and IMU timestamps " << most_recent_imu_time - start_time);
                    exit(-1);
                }

                double E,N,U;
                if(!fixed_origin_){
                    enu_.Reset(fix->latitude, fix->longitude, fix->altitude);
                    E = 0; N = 0; U = 0;
                }
                else{
                    GeographicLib::UTMUPS::Forward(fix->latitude, fix->longitude, utm_zone_, utm_northp_, E, N);
                    E -= utm_origin_x_;
                    N -= utm_origin_y_;
                    U = fix->altitude - utm_origin_z_;
                }

                // Add prior factors on pose, vel and bias
                Rot3 initial_orientation = Rot3::Quaternion(initial_pose_->pose.orientation.w,
                                                            initial_pose_->pose.orientation.x,
                                                            initial_pose_->pose.orientation.y,
                                                            initial_pose_->pose.orientation.z);
                
                Pose3 x0(base_to_gps_T_.rotation() * initial_orientation, Point3(E, N, U));
                prev_pose_ = x0;
                x0.print("Initial Pose");

                PriorFactor<Pose3> prior_pose(X(0), x0, prior_noise_pose_);
                new_graph_.add(prior_pose);

                PriorFactor<Vector3> prior_vel(V(0) , Vector3(0,0,0), prior_noise_vel_);
                new_graph_.add(prior_vel);

                Vector biases((Vector(6) << 0,0,0,0,0,0).finished()); 
                prev_bias_ = imuBias::ConstantBias(biases);
                PriorFactor<imuBias::ConstantBias> prior_bias(B(0), imuBias::ConstantBias(biases), prior_noise_bias_);
                new_graph_.add(prior_bias);

                // Factor for imu->gps transformation
                BetweenFactor<Pose3> imu_to_gps_factor(X(0),G(0), imu_to_gps_T_, 
                    noiseModel::Diagonal::Sigmas((Vector(6) << 0.001,0.001,0.001,0.03,0.03,0.03).finished()));

                // add prior values
                new_variables_.insert(X(0), x0);
                new_variables_.insert(V(0), Vector3(0, 0, 0));
                new_variables_.insert(B(0), imuBias::ConstantBias(biases));
                new_variables_.insert(G(0), x0.compose(imu_to_gps_T_));
                
                // isam_->update(new_graph_, new_variables_);

                last_imu_ = imu_opt_queue_.popBlocking();
                last_imu_use_time_ = TIME(last_imu_) - (1/200);
                while(TIME(last_imu_) < TIME(fix)){
                    last_imu_use_time_ = TIME(last_imu_);
                    last_imu_ = imu_opt_queue_.popBlocking();
                }
                while (gnss_pose_opt_queue_.size() > 0){ // for delete gnss_pose which has ealier time with fix
                    gnss_pose_opt_queue_.popBlocking();
                }
                while (lidar_odom_opt_queue_.size() > 0){ // for delete lidar which has ealier time with fix
                    lidar_odom_opt_queue_.popBlocking();
                }

                is_graph_made_ = true;
                // std::cout << "GRAPH MADE" << std::endl;
            }
            else { // after the graph was made
                // We have two reference poses 1. gnss_pose 2. lidar_odom
                // Compare each time and construct the pose graph

                // add gnss_pose measurements, t
                // std::cout << "lidar odom size : " << lidar_odom_opt_queue_.size() << std::endl;
                // std::cout << "gnss  pose size : " << gnss_pose_opt_queue_.size() << std::endl;
                // std::cout << "imu        size : " << imu_opt_queue_.size() << std::endl;
                if (lidar_odom_opt_queue_.size() == 0){
                        
                    geometry_msgs::PoseStampedConstPtr gnss_pose = gnss_pose_opt_queue_.popBlocking();
                    // std::cout << "POP GNSS" << std::endl;
                    last_node_time_ = TIME(gnss_pose);
                    if (last_node_time_ < last_imu_use_time_+0.001)
                        skip = true;
                    if(!skip){
                        Pose3 gnss_pose3(Rot3::Quaternion(gnss_pose->pose.orientation.w,gnss_pose->pose.orientation.x,
                                                        gnss_pose->pose.orientation.y,gnss_pose->pose.orientation.z),
                                        Point3(gnss_pose->pose.position.x,gnss_pose->pose.position.y,gnss_pose->pose.position.z));
                        // Need to check it is okay?? Near the expected state
                        SharedDiagonal gnss_pose_noise = noiseModel::Diagonal::Sigmas(
                            (Vector(6) << gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_).finished());
                        PriorFactor<Pose3> gnss_pose_prior(X(node_key_), gnss_pose3, gnss_pose_noise);
                    
                        new_graph_.add(gnss_pose_prior);
                        // new_variables_.insert(X(node_key_), gnss_pose3);
                    }
                }

                else if(gnss_pose_opt_queue_.size() == 0){
                    // std::cout <<"POP LIDAR" <<std::endl;
                        
                    nav_msgs::OdometryConstPtr lidar_odom = lidar_odom_opt_queue_.popBlocking();
                    last_node_time_ = TIME(lidar_odom);
                    if (last_node_time_ < TIME(last_imu_)){
                        // std::cout << "SKIP" << std::endl;
                        skip = true;
                    }
                    if(!skip){

                        Pose3 lidar_odom_pose3(Rot3::Quaternion(lidar_odom->pose.pose.orientation.w,lidar_odom->pose.pose.orientation.x,
                                                        lidar_odom->pose.pose.orientation.y,lidar_odom->pose.pose.orientation.z),
                                        Point3(lidar_odom->pose.pose.position.x,lidar_odom->pose.pose.position.y,lidar_odom->pose.pose.position.z));

                        Pose3 lidar_odom_rel_pose = last_lidar_odom_pose_.between(lidar_odom_pose3).compose(lidar_to_gps_T);
                        lidar_odom_rel_pose.print("rel");
                        
                        SharedDiagonal lidar_odom_noise = noiseModel::Diagonal::Sigmas(
                            (Vector(6) << lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_).finished());
                        BetweenFactor<Pose3> lidar_odom_factor(X(last_lidar_odom_key),X(node_key_), lidar_odom_rel_pose, lidar_odom_noise);
                        
                        new_graph_.add(lidar_odom_factor);
                        // new_variables_.insert(X(node_key_), isam_->calculateEstimate<Pose3>(X(node_key_-1)).compose(lidar_odom_rel_pose));
                        // new_variables_.insert(X(node_key_), lidar_odom_pose3);
                        last_lidar_odom_key = node_key_;
                        last_lidar_odom_pose_ = lidar_odom_pose3;           
                    }         
                }
                
                else if (TIME(gnss_pose_opt_queue_.front()) < TIME(lidar_odom_opt_queue_.front())){ // gnss pose is faster
                        
                    geometry_msgs::PoseStampedConstPtr gnss_pose = gnss_pose_opt_queue_.popBlocking();
                    last_node_time_ = TIME(gnss_pose);
                    if (last_node_time_ < TIME(last_imu_)){
                        std::cout << "SKIP" << std::endl;
                        skip = true;
                    }
                    if(!skip){
                        Pose3 gnss_pose3(Rot3::Quaternion(gnss_pose->pose.orientation.w,gnss_pose->pose.orientation.x,
                                                        gnss_pose->pose.orientation.y,gnss_pose->pose.orientation.z),
                                        Point3(gnss_pose->pose.position.x,gnss_pose->pose.position.y,gnss_pose->pose.position.z));
                        // Need to check it is okay?? Near the expected state
                        SharedDiagonal gnss_pose_noise = noiseModel::Diagonal::Sigmas(
                            (Vector(6) << gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_,gnss_pose_sigma_).finished());
                        PriorFactor<Pose3> gnss_pose_prior(X(node_key_), gnss_pose3, gnss_pose_noise);
                        
                        new_graph_.add(gnss_pose_prior);
                        // new_variables_.insert(X(node_key_), gnss_pose3);
                    }
                }
                else if (TIME(lidar_odom_opt_queue_.front()) < TIME(gnss_pose_opt_queue_.front())){ // lidar odom is faster
                    nav_msgs::OdometryConstPtr lidar_odom = lidar_odom_opt_queue_.popBlocking();
                    last_node_time_ = TIME(lidar_odom);
                    if (last_node_time_ < TIME(last_imu_)){
                        // std::cout << "SKIP" << std::endl;
                        skip = true;
                    }
                    if (!skip){
                        Pose3 lidar_odom_pose3(Rot3::Quaternion(lidar_odom->pose.pose.orientation.w,lidar_odom->pose.pose.orientation.x,
                                                        lidar_odom->pose.pose.orientation.y,lidar_odom->pose.pose.orientation.z),
                                        Point3(lidar_odom->pose.pose.position.x,lidar_odom->pose.pose.position.y,lidar_odom->pose.pose.position.z));

                        Pose3 lidar_odom_rel_pose = last_lidar_odom_pose_.between(lidar_odom_pose3).compose(lidar_to_gps_T);
                        
                        SharedDiagonal lidar_odom_noise = noiseModel::Diagonal::Sigmas(
                            (Vector(6) << lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_,lidar_odom_sigma_).finished());
                        BetweenFactor<Pose3> lidar_odom_factor(X(last_lidar_odom_key),X(node_key_), lidar_odom_rel_pose, lidar_odom_noise);
                        
                        new_graph_.add(lidar_odom_factor);
                        // new_variables_.insert(X(node_key_), isam_->calculateEstimate<Pose3>(X(node_key_-1)).compose(lidar_odom_rel_pose));
                        // new_variables_.insert(X(node_key_), lidar_odom_pose3);

                        last_lidar_odom_key = node_key_;
                        last_lidar_odom_pose_ = lidar_odom_pose3;
                    }     
                }  
                //add IMU measurements
                while (!imu_opt_queue_.empty() && (TIME(last_imu_) < last_node_time_ ) && !skip){
                    // std::cout << "HERE imu" << std::endl;
                    PreintegratedImuMeasurements preintegrated_data(preintegration_params_, previous_bias_);
                    // std::cout << "HERE imu" << std::endl;
                    //Get all imu data got before the gnss_pose and integrating it
                    while (TIME(last_imu_) < last_node_time_){
                        Vector3 acc, gyro;
                        getAccGyro(last_imu_, acc, gyro);
                        double imu_dt = TIME(last_imu_) - last_imu_use_time_;
                        last_imu_use_time_ = TIME(last_imu_);
                        preintegrated_data.integrateMeasurement(acc, gyro, imu_dt);
                        last_imu_ = imu_opt_queue_.popBlocking();
                    }
                    // std::cout << "HERE imu" << std::endl;
                    //adding the integraed IMU measurements to the factor graph
                    
                    ImuFactor imu_factor(X(node_key_-1), V(node_key_-1), X(node_key_), V(node_key_),
                                        B(node_key_-1), preintegrated_data);
                    // std::cout << "HERE" << std::endl;
                    new_graph_.add(imu_factor);
                    new_graph_.add(BetweenFactor<imuBias::ConstantBias>(B(node_key_-1), B(node_key_), imuBias::ConstantBias(),
                        noiseModel::Diagonal::Sigmas( sqrt(preintegrated_data.deltaTij()) * noise_model_between_bias_sigma_)));
                    
                    //Predict forward to get an initial estimate for the pose and velocity
                    NavState cur_nav_state(prev_pose_, prev_vel_);
                    NavState next_nav_state = preintegrated_data.predict(cur_nav_state, prev_bias_);
                    new_variables_.insert(X(node_key_), next_nav_state.pose());
                    new_variables_.insert(V(node_key_), next_nav_state.v());
                    new_variables_.insert(B(node_key_), previous_bias_);
                    new_variables_.insert(G(node_key_), next_nav_state.pose().compose(imu_to_gps_T_)); //Seems a little bit weird
                    
                    prev_pose_ = next_nav_state.pose();
                    prev_vel_ = next_nav_state.v();
                    
                }
                /* Do GPS Later */
                // add GPS measurements got before the gnss_pose
                while(!gps_opt_queue_.empty() && (TIME(gps_opt_queue_.front()) < last_node_time_)){
                    sensor_msgs::NavSatFixConstPtr fix = gps_opt_queue_.popBlocking();
                    double E, N, U;
                    GeographicLib::UTMUPS::Forward(fix->latitude, fix->longitude,utm_zone_,utm_northp_,E,N);
                    E -= utm_origin_x_;
                    N -= utm_origin_y_;
                    U = fix->altitude - utm_origin_z_;

                    SharedDiagonal gps_noise = noiseModel::Diagonal::Sigmas(Vector3(gps_sigma_, gps_sigma_, 3.0 * gps_sigma_));
                    GPSFactor gps_factor(G(node_key_), Point3(E, N, U), gps_noise);
                    new_graph_.add(gps_factor);
                    BetweenFactor<Pose3> imu_p_gps_factor(X(node_key_), G(node_key_), imu_to_gps_T_,
                        noiseModel::Diagonal::Sigmas((Vector(6) << 0.001,0.001,0.001,0.03,0.03,0.03).finished()));
                    new_graph_.add(imu_p_gps_factor);
                }

                
            }
            if(!skip){
                node_key_++;
                if(optimizer_real_time_)
                runISAM2opt();
            }
            else
                skip = false;
            
            isam_mutex_.unlock();

        } 
    }
}

// void StateEstimator::addGnssPoseFactorAndImuFactor(){}

// void StateEstimator::addLidarOdomFactorAndImuFactor(){}

void StateEstimator::getAccGyro(sensor_msgs::ImuConstPtr imu, Vector3 &acc, Vector3 &gyro){
    double accx, accy, accz;
    accx = imu->linear_acceleration.x;
    accy = -imu->linear_acceleration.y;
    accz = -imu->linear_acceleration.z;
    acc = Vector3(accx, accy, accz);

    double gx, gy, gz;
    gx = imu->angular_velocity.x;
    gy = -imu->angular_velocity.y;
    gz = -imu->angular_velocity.z;
    gyro = Vector3(gx, gy, gz);
}

void StateEstimator::runISAM2opt(){
    if (is_graph_made_){
        try{
            // std::cout << "node key : " << node_key_ << std::endl;
            if (!(new_variables_.exists(V(node_key_-1)) && new_variables_.exists(B(node_key_-1))))
                return;
            // std::cout <<  "isam" << std::endl;
            isam_->update(new_graph_, new_variables_);
            // std::cout <<  "isam2" << std::endl;
            isam_->update();

            new_graph_.resize(0);
            new_variables_.clear();

            Pose3 next_state = isam_->calculateEstimate<Pose3>(X(node_key_-1));

            prev_pose_ = next_state;
            prev_vel_ = isam_->calculateEstimate<Vector3>(V(node_key_-1));
            prev_bias_ = isam_->calculateEstimate<imuBias::ConstantBias>(B(node_key_-1));
        
            optimized_state_mutex_.lock();
            optimized_state_ = NavState(prev_pose_, prev_vel_);
            optimized_bias_ = prev_bias_;
            optimized_time_ = last_imu_use_time_;
            optimized_state_mutex_.unlock();

            // std::cout <<  "isam end" << std::endl;
            
        }
        catch(gtsam::IndeterminantLinearSystemException ex){
            std::cout << "OPTIMIZATION BOOOOOOOOOOOOOOM!!!" << std::endl;
        }
        
    }
}

void StateEstimator::isamOptimizer(){
    float hz = optimizer_hz_;
    ros::Rate rate(hz);
    while(ros::ok()){
        rate.sleep();
        if(is_graph_made_){
            isam_mutex_.lock();
            runISAM2opt();
            isam_mutex_.unlock();
        }
    }
}

StateEstimator::~StateEstimator(){}

int main (int argc, char** argv){
    ros::init(argc, argv, "StateEstimator");
    StateEstimator SE;
    ros::spin();
}