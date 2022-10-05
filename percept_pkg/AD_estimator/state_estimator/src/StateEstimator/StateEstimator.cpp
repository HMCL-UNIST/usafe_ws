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
 * @author Edited by Hojin Lee <hojinlee@unist.ac.kr> 
 * @date May 1, 2017 / modified 2022
 * @copyright 2017 Georgia Institute of Technology
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

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "StateEstimator.h"

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
using symbol_shorthand::X;
using symbol_shorthand::V;
using symbol_shorthand::B;
using symbol_shorthand::G; // GPS pose


// macro for getting the time stamp of a ros message
#define TIME(msg) ( (msg)->header.stamp.toSec() )

namespace localization_core
{

  StateEstimator::StateEstimator() :
    Diagnostics("StateEstimator", "none", ""),
    nh_("~"),
    lastImuT_(0.0),
    lastImuTgps_(0.0),
    maxQSize_(0),
    gpsOptQ_(40),
    localPoseOptQ_(40),
    imuOptQ_(400),
    odomOptQ_(100),
    gotFirstFix_(false),
    gotFirstLocalPose_(false)
  {
    // temporary variables to retrieve parameters
    double accSigma, gyroSigma, initialVelNoise, initialBiasNoiseAcc, initialBiasNoiseGyro, initialRotationNoise,
        carXAngle, carYAngle, carZAngle, sensorX, sensorY, sensorZ, sensorXAngle, sensorYAngle, sensorZAngle,
        gravityMagnitude;

    nh_.param<double>("InitialRotationNoise", initialRotationNoise, 1.0);
    nh_.param<double>("InitialVelocityNoise", initialVelNoise, 0.1);
    nh_.param<double>("InitialBiasNoiseAcc", initialBiasNoiseAcc, 1e-1);
    nh_.param<double>("InitialBiasNoiseGyro", initialBiasNoiseGyro, 1e-2);
    nh_.param<double>("AccelerometerSigma", accSigma, 6.0e-2);
    nh_.param<double>("GyroSigma", gyroSigma, 2.0e-2);
    nh_.param<double>("AccelBiasSigma", accelBiasSigma_, 2.0e-4);
    nh_.param<double>("GyroBiasSigma", gyroBiasSigma_, 3.0e-5);
    nh_.param<double>("GPSSigma", gpsSigma_, 0.07);
    nh_.param<double>("localPoseSigma", localPoseSigma_, 0.01);
    nh_.param<double>("SensorTransformX", sensorX, 0.0);
    nh_.param<double>("SensorTransformY", sensorY, 0.0);
    nh_.param<double>("SensorTransformZ", sensorZ, 0.0);
    nh_.param<double>("SensorXAngle",  sensorXAngle, 0);
    nh_.param<double>("SensorYAngle", sensorYAngle, 0);
    nh_.param<double>("SensorZAngle",   sensorZAngle, 0);
    nh_.param<double>("CarXAngle",  carXAngle, 0);
    nh_.param<double>("CarYAngle",  carYAngle, 0);
    nh_.param<double>("CarZAngle",  carZAngle, 0);
    nh_.param<double>("Gravity",   gravityMagnitude, 9.81);
    nh_.param<bool>("InvertX", invertx_, false);
    nh_.param<bool>("InvertY", inverty_, false);
    nh_.param<bool>("InvertZ", invertz_, false);
    nh_.param<double>("Imudt", imuDt_, 1.0/200.0);

    double gpsx, gpsy, gpsz;
    nh_.param<double>("GPSX",  gpsx, 0);
    nh_.param<double>("GPSY",  gpsy, 0);
    nh_.param<double>("GPSZ",  gpsz, 0);
    imuPgps_ = Pose3(Rot3(), Point3(gpsx, gpsy, gpsz));
    imuPgps_.print("IMU->GPS");

    bool fixedInitialPose;
    double initialRoll, intialPitch, initialYaw;

    nh_.param<bool>("FixedInitialPose", fixedInitialPose, false);
    nh_.param<double>("initialRoll", initialRoll, 0);
    nh_.param<double>("intialPitch", intialPitch, 0);
    nh_.param<double>("initialYaw", initialYaw, 0);

    double latOrigin, lonOrigin, altOrigin;
    nh_.param<bool>("FixedOrigin", fixedOrigin_, false);
    nh_.param<double>("latOrigin", latOrigin, 0);
    nh_.param<double>("lonOrigin", lonOrigin, 0);
    nh_.param<double>("altOrigin", altOrigin, 0);

    nh_.param<double>("utm_x_origin", utm_ori_x, 0);
    nh_.param<double>("utm_y_origin", utm_ori_y, 0);
    nh_.param<double>("utm_z_origin", utm_ori_z, 0);

    nh_.param<bool>("UseOdom", usingOdom_, false);
    nh_.param<bool>("usingWheelAsOdom",usingWheelAsOdom_,false);
    nh_.param<bool>("UseLocalPose", usingLocalPose_, false);
    nh_.param<double>("MaxGPSError", maxGPSError_, 10.0);
    nh_.param<double>("maxLocalPoseError", maxLocalPoseError_, 10.0);

    if (fixedOrigin_){
      enu_.Reset(latOrigin, lonOrigin, altOrigin);

    }

    std::cout << "InitialRotationNoise " << initialRotationNoise << "\n"
    << "InitialVelocityNoise " << initialVelNoise << "\n"
    << "InitialBiasNoiseAcc " << initialBiasNoiseAcc << "\n"
    << "InitialBiasNoiseGyro " << initialBiasNoiseGyro << "\n"
    << "AccelerometerSigma " << accSigma << "\n"
    << "GyroSigma " << gyroSigma << "\n"
    << "AccelBiasSigma " << accelBiasSigma_ << "\n"
    << "GyroBiasSigma " << gyroBiasSigma_ << "\n"
    << "GPSSigma " << gpsSigma_ << "\n"
    << "SensorTransformX " << sensorX << "\n"
    << "SensorTransformY " << sensorY << "\n"
    << "SensorTransformZ " << sensorZ << "\n"
    << "SensorXAngle " <<  sensorXAngle << "\n"
    << "SensorYAngle " << sensorYAngle << "\n"
    << "SensorZAngle " <<   sensorZAngle << "\n"
    << "CarXAngle " <<  carXAngle << "\n"
    << "CarYAngle " <<  carYAngle << "\n"
    << "CarZAngle " <<  carZAngle << "\n"
    << "Gravity " <<   gravityMagnitude << "\n";

    // Use an ENU frame
    preintegrationParams_ =  PreintegrationParams::MakeSharedU(gravityMagnitude);
    preintegrationParams_->accelerometerCovariance = accSigma * I_3x3;
    preintegrationParams_->gyroscopeCovariance = gyroSigma * I_3x3;
    preintegrationParams_->integrationCovariance = 1e-5 * I_3x3;

    Vector biases((Vector(6) << 0, 0, 0, 0, 0, 0).finished());
    optimizedBias_ = imuBias::ConstantBias(biases);
    previousBias_ = imuBias::ConstantBias(biases);
    imuPredictor_ = boost::make_shared<PreintegratedImuMeasurements>(preintegrationParams_, optimizedBias_);

    optimizedTime_ = 0;

    // imu_3dm_gx4::FilterOutputConstPtr ip;
    
    if (!fixedInitialPose)
    {
      while (!ip)
      {
        ROS_WARN("Waiting for valid initial orientation");
        // ip = ros::topic::waitForMessage<nav_msgs::Imu>("/imu_correct2", nh_, ros::Duration(15));
        ip = ros::topic::waitForMessage<geometry_msgs::PoseStamped>("/gnss_pose_world", nh_, ros::Duration(15));
        
      }
      initialPose_.orientation.w = ip->pose.orientation.w;
      initialPose_.orientation.x = ip->pose.orientation.x;
      initialPose_.orientation.y = ip->pose.orientation.y;
      initialPose_.orientation.z = ip->pose.orientation.z;
      initialPose_.bias.x = 0.0;
      initialPose_.bias.y = 0.0;
      initialPose_.bias.z = 0.0;
    }
    else
    {
      ROS_WARN("Using fixed initial orientation");
      Rot3 initialRotation = Rot3::Ypr(initialYaw, intialPitch, initialRoll);
      initialPose_.orientation.w = initialRotation.quaternion()[0];
      initialPose_.orientation.x = initialRotation.quaternion()[1];
      initialPose_.orientation.y = initialRotation.quaternion()[2];
      initialPose_.orientation.z = initialRotation.quaternion()[3];
      initialPose_.bias.x = 0;
      initialPose_.bias.y = 0;
      initialPose_.bias.z = 0;
    }

    Rot3 initRot(Quaternion(initialPose_.orientation.w, initialPose_.orientation.x, initialPose_.orientation.y,
          initialPose_.orientation.z));

    bodyPSensor_ = Pose3(Rot3::RzRyRx(sensorXAngle, sensorYAngle, sensorZAngle),
        Point3(sensorX, sensorY, sensorZ));
    carENUPcarNED_ = Pose3(Rot3::RzRyRx(carXAngle, carYAngle, carZAngle), Point3());

    bodyPSensor_.print("Body pose\n");
    carENUPcarNED_.print("CarBodyPose\n");

    pub_optPose = nh_.advertise<nav_msgs::Odometry>("/opt_pose_debug", 1);
    posePub_ = nh_.advertise<nav_msgs::Odometry>("pose", 1);
    estPosePub = nh_.advertise<geometry_msgs::PoseStamped>("estimated_pose", 1);
    biasAccPub_ = nh_.advertise<geometry_msgs::Point>("bias_acc", 1);
    biasGyroPub_ = nh_.advertise<geometry_msgs::Point>("bias_gyro", 1);
    timePub_ = nh_.advertise<geometry_msgs::Point>("time_delays", 1);
    gpsPosPub_ = nh_.advertise<geometry_msgs::PoseWithCovarianceStamped>("gps_pos", 1);
    test_pub = nh_.advertise<visualization_msgs::MarkerArray>("debug_point", 1);

    ISAM2Params params;
    params.factorization = ISAM2Params::QR;
    isam_ = new ISAM2(params);

    // prior on the first pose
    priorNoisePose_ = noiseModel::Diagonal::Sigmas(
         (Vector(6) << initialRotationNoise, initialRotationNoise, 3*initialRotationNoise,
             gpsSigma_, gpsSigma_, gpsSigma_).finished());

     // Add velocity prior
     priorNoiseVel_ = noiseModel::Diagonal::Sigmas(
         (Vector(3) << initialVelNoise, initialVelNoise, initialVelNoise).finished());

     // Add bias prior
     priorNoiseBias_ = noiseModel::Diagonal::Sigmas(
         (Vector(6) << initialBiasNoiseAcc,
             initialBiasNoiseAcc,
             initialBiasNoiseAcc,
             initialBiasNoiseGyro,
             initialBiasNoiseGyro,
             initialBiasNoiseGyro).finished());

     std::cout<<"checkpoint"<<std::endl;

     Vector sigma_acc_bias_c(3), sigma_gyro_bias_c(3);
     sigma_acc_bias_c << accelBiasSigma_,  accelBiasSigma_,  accelBiasSigma_;
     sigma_gyro_bias_c << gyroBiasSigma_, gyroBiasSigma_, gyroBiasSigma_;
     noiseModelBetweenBias_sigma_ = (Vector(6) << sigma_acc_bias_c, sigma_gyro_bias_c).finished();

     gpsSub_ = nh_.subscribe("gps", 300, &StateEstimator::GpsCallback, this);
     imuSub_ = nh_.subscribe("imu", 600, &StateEstimator::ImuCallback, this);
     if (!usingWheelAsOdom_)
      odomSub_ = nh_.subscribe("/Odometry", 300, &StateEstimator::OdomCallback, this);
     else
      odomSub_ = nh_.subscribe("wheel_odom", 300, &StateEstimator::WheelOdomCallback, this);
     
     localPoseSub_ = nh_.subscribe("local_pose", 300, &StateEstimator::localPoseCallback, this);
     
     boost::thread optimizer(&StateEstimator::GpsHelper,this); // main loop

  
  }

  StateEstimator::~StateEstimator()
  {}

  void StateEstimator::testDebug(){
    //////////////////////////////////
    int id_ = 0;
    std::vector<std::pair<double, double>> debug_list;
    debug_list.push_back(std::pair<double,double>(445820.20, 3945187.05));
    debug_list.push_back(std::pair<double,double>(445687.03, 3945328.06));
    debug_list.push_back(std::pair<double,double>(445597.61, 3945427.05));
    debug_list.push_back(std::pair<double,double>(445493.89, 3945553.02));
    debug_list.push_back(std::pair<double,double>(445152.43, 3945849.77));
    debug_list.push_back(std::pair<double,double>(445191.98, 3945829.56));
    debug_list.push_back(std::pair<double,double>(444933.60, 3945971.65));
    debug_list.push_back(std::pair<double,double>(444944.78, 3945998.52));
    debug_list.push_back(std::pair<double,double>(445201.47, 3945891.55));
    debug_list.push_back(std::pair<double,double>(445331.17, 3945753.36));
    debug_list.push_back(std::pair<double,double>(445414.68, 3945655.34));
    debug_list.push_back(std::pair<double,double>(445183.87, 3945905.04));
    debug_list.push_back(std::pair<double,double>(445334.55, 3945738.04));
    debug_list.push_back(std::pair<double,double>(445434.78, 3945633.14));
    debug_list.push_back(std::pair<double,double>(445549.51, 3945506.42));
     //////TEST DEBUG
     visualization_msgs::MarkerArray marker_array_;
     for (int i=0; i<debug_list.size(); i++){
       visualization_msgs::Marker tmp_marker_;
       tmp_marker_.header.frame_id = "/map";
       tmp_marker_.header.stamp = ros::Time::now();
       tmp_marker_.id = id_++;
       tmp_marker_.type = visualization_msgs::Marker::SPHERE;
       tmp_marker_.action = visualization_msgs::Marker::ADD;
       tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
       tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
       tmp_marker_.pose.position.z = utm_ori_z;
       tmp_marker_.pose.orientation.x = 0.0;
       tmp_marker_.pose.orientation.y = 0.0;
       tmp_marker_.pose.orientation.z = 0.0;
       tmp_marker_.pose.orientation.w = 1.0;
       tmp_marker_.scale.x = 2;
       tmp_marker_.scale.y = 2;
       tmp_marker_.scale.z = 2;
       tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
       tmp_marker_.color.r = 0.0;
       tmp_marker_.color.g = 1.0;
       tmp_marker_.color.b = 0.0;
       marker_array_.markers.push_back(tmp_marker_);
     }
    // debug_list .push_back(std::pair<double, double>(445734.76, 3945020.81));
    // debug_list .push_back(std::pair<double, double>(445688.44, 3945033.38));
    // debug_list .push_back(std::pair<double, double>(445633.22, 3945068.91));
    // debug_list .push_back(std::pair<double, double>(445602.91, 3945120.20));
    // debug_list .push_back(std::pair<double, double>(445636.79, 3945150.46));
    // debug_list .push_back(std::pair<double, double>(445690.10, 3945111.87));
    // debug_list .push_back(std::pair<double, double>(445718.48, 3945060.93));
    // debug_list .push_back(std::pair<double, double>(445684.84, 3945076.19));
    // debug_list .push_back(std::pair<double, double>(445664.31, 3945098.87));
    // debug_list .push_back(std::pair<double, double>(445645.61, 3945119.29));
    // debug_list .push_back(std::pair<double, double>(445589.07, 3945181.55));
    //  //////TEST DEBUG
    //  visualization_msgs::MarkerArray marker_array_;
    //  for (int i=0; i<debug_list.size(); i++){
    //    visualization_msgs::Marker tmp_marker_;
    //    tmp_marker_.header.frame_id = "/map";
    //    tmp_marker_.header.stamp = ros::Time::now();
    //    tmp_marker_.id = id_++;
    //    tmp_marker_.type = visualization_msgs::Marker::SPHERE;
    //    tmp_marker_.action = visualization_msgs::Marker::ADD;
    //    tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
    //    tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
    //    tmp_marker_.pose.position.z = utm_ori_z;
    //    tmp_marker_.pose.orientation.x = 0.0;
    //    tmp_marker_.pose.orientation.y = 0.0;
    //    tmp_marker_.pose.orientation.z = 0.0;
    //    tmp_marker_.pose.orientation.w = 1.0;
    //    tmp_marker_.scale.x = 2;
    //    tmp_marker_.scale.y = 2;
    //    tmp_marker_.scale.z = 2;
    //    tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
    //    tmp_marker_.color.r = 0.0;
    //    tmp_marker_.color.g = 1.0;
    //    tmp_marker_.color.b = 0.0;
    //    marker_array_.markers.push_back(tmp_marker_);
    //  }
     
    //  for (int i=0; i<debug_list.size(); i++){
    //    visualization_msgs::Marker tmp_marker_;
    //    tmp_marker_.header.frame_id = "/map";
    //    tmp_marker_.header.stamp = ros::Time::now();
    //    tmp_marker_.id = id_++;
    //    tmp_marker_.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    //    tmp_marker_.text = std::to_string(i);
    //    tmp_marker_.action = visualization_msgs::Marker::ADD;
    //    tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
    //    tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
    //    tmp_marker_.pose.orientation.w = 1.0;
    //    tmp_marker_.scale.z = 2;
    //    tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
    //    marker_array_.markers.push_back(tmp_marker_);
    //  }

    //  debug_list.clear();
    //  debug_list .push_back(std::pair<double, double>(445756.89, 3944996.39));
    //  debug_list .push_back(std::pair<double, double>(445732.17, 3945023.83));
    //  debug_list .push_back(std::pair<double, double>(445686.10, 3945074.38));
    //  debug_list .push_back(std::pair<double, double>(445666.18, 3945097.03));
    //  debug_list .push_back(std::pair<double, double>(445643.97, 3945116.09));
    //  debug_list .push_back(std::pair<double, double>(445602.12, 3945123.82));
    //  debug_list .push_back(std::pair<double, double>(445546.23, 3945156.78));
    //  debug_list .push_back(std::pair<double, double>(445523.02, 3945215.97));
    //  debug_list .push_back(std::pair<double, double>(445553.11, 3945243.52));
    //  debug_list .push_back(std::pair<double, double>(445605.56, 3945205.65));
    //  debug_list .push_back(std::pair<double, double>(445635.51, 3945154.06));
    //  debug_list .push_back(std::pair<double, double>(445637.23, 3945117.81));
    //  debug_list .push_back(std::pair<double, double>(445659.30, 3945089.29));

    // for (int i=0; i<debug_list.size(); i++){
    //    visualization_msgs::Marker tmp_marker_;
    //    tmp_marker_.header.frame_id = "/map";
    //    tmp_marker_.header.stamp = ros::Time::now();
    //    tmp_marker_.id = id_++;
    //    tmp_marker_.type = visualization_msgs::Marker::SPHERE;
    //    tmp_marker_.action = visualization_msgs::Marker::ADD;
    //    tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
    //    tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
    //    tmp_marker_.pose.position.z = utm_ori_z;
    //    tmp_marker_.pose.orientation.x = 0.0;
    //    tmp_marker_.pose.orientation.y = 0.0;
    //    tmp_marker_.pose.orientation.z = 0.0;
    //    tmp_marker_.pose.orientation.w = 1.0;
    //    tmp_marker_.scale.x = 2;
    //    tmp_marker_.scale.y = 2;
    //    tmp_marker_.scale.z = 2;
    //    tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
    //    tmp_marker_.color.r = 0.0;
    //    tmp_marker_.color.g = 0.0;
    //    tmp_marker_.color.b = 1.0;
    //    marker_array_.markers.push_back(tmp_marker_);
    //  }
    //  for (int i=0; i<debug_list.size(); i++){
    //    visualization_msgs::Marker tmp_marker_;
    //    tmp_marker_.header.frame_id = "/map";
    //    tmp_marker_.header.stamp = ros::Time::now();
    //    tmp_marker_.id = id_++;
    //    tmp_marker_.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    //    tmp_marker_.text = std::to_string(i);
    //    tmp_marker_.action = visualization_msgs::Marker::ADD;
    //    tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
    //    tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
    //    tmp_marker_.pose.position.z = utm_ori_z;
    //    tmp_marker_.pose.orientation.x = 0.0;
    //    tmp_marker_.pose.orientation.y = 0.0;
    //    tmp_marker_.pose.orientation.z = 0.0;
    //    tmp_marker_.pose.orientation.w = 1.0;
    //    tmp_marker_.scale.x = 2;
    //    tmp_marker_.scale.y = 2;
    //    tmp_marker_.scale.z = 2;
    //    tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
    //    tmp_marker_.color.r = 0.0;
    //    tmp_marker_.color.g = 0.0;
    //    tmp_marker_.color.b = 1.0;
    //    marker_array_.markers.push_back(tmp_marker_);
    //  }
    //   debug_list.clear();
    //   debug_list .push_back(std::pair<double, double>(445754.99,3944998.32));
    //   debug_list .push_back(std::pair<double, double>(445727.84,3945023.26));
    //   debug_list .push_back(std::pair<double, double>(445687.28,3945032.65));
    //   debug_list .push_back(std::pair<double, double>(445631.75,3945070.05));
    //   debug_list .push_back(std::pair<double, double>(445604.09, 3945120.99));
    //   debug_list .push_back(std::pair<double, double>(445604.52,3945159.54));
    //   debug_list .push_back(std::pair<double, double>(445578.44,3945193.58));
    //   debug_list .push_back(std::pair<double, double>(445559.73,3945214.14));
    //   debug_list .push_back(std::pair<double, double>(445551.50, 3945242.09));
    //   debug_list .push_back(std::pair<double, double>(445598.00, 3945214.29));
    //   debug_list .push_back(std::pair<double, double>(445634.11,3945152.66));
    //   debug_list .push_back(std::pair<double, double>(445602.37,3945124.15));
    //   debug_list .push_back(std::pair<double, double>(445544.76,3945158.25));
    //   debug_list .push_back(std::pair<double, double>(445523.55,3945216.43));
    //   debug_list .push_back(std::pair<double, double>(445552.50, 3945206.48));
    //   debug_list .push_back(std::pair<double, double>(445571.63,3945185.55));
    //   debug_list .push_back(std::pair<double, double>(445595.35,3945164.42));
    //   debug_list .push_back(std::pair<double, double>(445636.48, 3945150.87));
    //   debug_list .push_back(std::pair<double, double>(445686.64,3945116.48));
    //   debug_list .push_back(std::pair<double, double>(445717.87,3945060.23));
    //   debug_list .push_back(std::pair<double, double>(445721.67,3945024.91));
    //   debug_list .push_back(std::pair<double, double>(445751.17, 3900927.79));
    //   for (int i=0; i<debug_list.size(); i++){
    //    visualization_msgs::Marker tmp_marker_;
    //    tmp_marker_.header.frame_id = "/map";
    //    tmp_marker_.header.stamp = ros::Time::now();
    //    tmp_marker_.id = id_++;
    //    tmp_marker_.type = visualization_msgs::Marker::SPHERE;
    //    tmp_marker_.action = visualization_msgs::Marker::ADD;
    //    tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
    //    tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
    //    tmp_marker_.pose.position.z = utm_ori_z;
    //    tmp_marker_.pose.orientation.x = 0.0;
    //    tmp_marker_.pose.orientation.y = 0.0;
    //    tmp_marker_.pose.orientation.z = 0.0;
    //    tmp_marker_.pose.orientation.w = 1.0;
    //    tmp_marker_.scale.x = 2;
    //    tmp_marker_.scale.y = 2;
    //    tmp_marker_.scale.z = 2;
    //    tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
    //    tmp_marker_.color.r = 1.0;
    //    tmp_marker_.color.g = 0.0;
    //    tmp_marker_.color.b = 0.0;
    //    marker_array_.markers.push_back(tmp_marker_);
    //  }
    //  for (int i=0; i<debug_list.size(); i++){
    //    visualization_msgs::Marker tmp_marker_;
    //    tmp_marker_.header.frame_id = "/map";
    //    tmp_marker_.header.stamp = ros::Time::now();
    //    tmp_marker_.id = id_++;
    //    tmp_marker_.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    //    tmp_marker_.text = std::to_string(i);
    //    tmp_marker_.action = visualization_msgs::Marker::ADD;
    //    tmp_marker_.pose.position.x = debug_list[i].first - utm_ori_x;;
    //    tmp_marker_.pose.position.y = debug_list[i].second -utm_ori_y;;
    //    tmp_marker_.pose.position.z = utm_ori_z;
    //    tmp_marker_.pose.orientation.x = 0.0;
    //    tmp_marker_.pose.orientation.y = 0.0;
    //    tmp_marker_.pose.orientation.z = 0.0;
    //    tmp_marker_.pose.orientation.w = 1.0;
    //    tmp_marker_.scale.x = 2;
    //    tmp_marker_.scale.y = 2;
    //    tmp_marker_.scale.z = 2;
    //    tmp_marker_.color.a = 1.0; // Don't forget to set the alpha!
    //    tmp_marker_.color.r = 0.0;
    //    tmp_marker_.color.g = 0.0;
    //    tmp_marker_.color.b = 1.0;
    //    marker_array_.markers.push_back(tmp_marker_);
    //  }
     test_pub.publish(marker_array_);
  }
  
  void StateEstimator::localPoseCallback(geometry_msgs::PoseStampedConstPtr pose){
    if(!usingLocalPose_){
      return; 
    }
    if (!localPoseOptQ_.pushNonBlocking(pose))
      ROS_WARN("Dropping a LocalPose measurement due to full queue!!");
  }

  void StateEstimator::GpsCallback(sensor_msgs::NavSatFixConstPtr fix)
  {
    testDebug();
    if (!gpsOptQ_.pushNonBlocking(fix))
      ROS_WARN("Dropping a GPS measurement due to full queue!!");
  }

  void StateEstimator::GetAccGyro(sensor_msgs::ImuConstPtr imu, Vector3 &acc, Vector3 &gyro)
  {
    double accx, accy, accz;
    if (invertx_) accx = -imu->linear_acceleration.x;
    else accx = imu->linear_acceleration.x;
    if (inverty_) accy = -imu->linear_acceleration.y;
    else accy = imu->linear_acceleration.y;
    if (invertz_) accz = -imu->linear_acceleration.z;
    else accz = imu->linear_acceleration.z;
    acc = Vector3(accx, accy, accz);

    double gx, gy, gz;
    if (invertx_) gx = -imu->angular_velocity.x;
    else gx = imu->angular_velocity.x;
    if (inverty_) gy = -imu->angular_velocity.y;
    else gy = imu->angular_velocity.y;
    if (invertz_) gz = -imu->angular_velocity.z;
    else gz = imu->angular_velocity.z;

    gyro = Vector3(gx, gy, gz);
  }


  void StateEstimator::GpsHelper()
  {
    ros::Rate loop_rate(5); // rate of GPS 
    bool gotFirstFix = false;
    double startTime;
    int odomKey = 1;
    int imuKey = 1;
    int latestGPSKey = 0;
    imuBias::ConstantBias prevBias;
    Vector3 prevVel = (Vector(3) << 0.0,0.0,0.0).finished();
    Pose3 prevPose;


    while (ros::ok())
    {
      bool optimize = false;
      
      
      if (!gotFirstFix)
      {
        sensor_msgs::NavSatFixConstPtr fix = gpsOptQ_.popBlocking();
        startTime = TIME(fix);
        if(imuOptQ_.size() <= 0) {
          ROS_WARN_THROTTLE(1, "no IMU messages before first fix, continuing until there is");
          continue;
        }
        // errors out if the IMU and GPS are not close in timestamps
        double most_recent_imu_time = imuOptQ_.back()->header.stamp.toSec();
        if(std::abs(most_recent_imu_time - startTime) > 0.1) {
          ROS_ERROR_STREAM("There is a very large difference in the GPS and IMU timestamps " << most_recent_imu_time - startTime);
          exit(-1);
        }

        if(usingOdom_) {
          lastOdom_ = odomOptQ_.popBlocking();
        }

        if(usingLocalPose_){
           lastLocalPose_ = localPoseOptQ_.popBlocking();
        }

        NonlinearFactorGraph newFactors;
        Values newVariables;
        gotFirstFix = true;

        double E, N, U;
        if (!fixedOrigin_)
        {
          enu_.Reset(fix->latitude, fix->longitude, fix->altitude);
          E = 0; N = 0; U = 0; // we're choosing this as the origin
          // E = ip->pose.position.x;
          // N = ip->pose.position.y;
          // U = ip->pose.position.z;
        }
        else
        {
          // we are given an origin
          // enu_.Forward(fix->latitude, fix->longitude, fix->altitude, E, N, U);
          GeographicLib::UTMUPS::Forward(fix->latitude, fix->longitude, zone_, northp, E, N);
          E -= utm_ori_x;
          N -= utm_ori_y;
          U = fix->altitude - utm_ori_z;
        }

        // Add prior factors on pose, vel and bias
        Rot3 initialOrientation = Rot3::Quaternion(initialPose_.orientation.w,
            initialPose_.orientation.x,
            initialPose_.orientation.y,
            initialPose_.orientation.z);
        std::cout << "Initial orientation" << std::endl;
        std::cout << bodyPSensor_.rotation() * initialOrientation * carENUPcarNED_.rotation() << std::endl;
        Pose3 x0(bodyPSensor_.rotation() * initialOrientation * carENUPcarNED_.rotation(),
            Point3(E, N, U));
        prevPose = x0;
        PriorFactor<Pose3> priorPose(X(0), x0, priorNoisePose_);
        newFactors.add(priorPose);

        PriorFactor<Vector3> priorVel(V(0), Vector3(0, 0, 0), priorNoiseVel_);
        newFactors.add(priorVel);

        Vector biases((Vector(6) << 0, 0, 0, initialPose_.bias.x,
            -initialPose_.bias.y, -initialPose_.bias.z).finished());
        prevBias = imuBias::ConstantBias(biases);
        PriorFactor<imuBias::ConstantBias> priorBias(B(0), imuBias::ConstantBias(biases), priorNoiseBias_);
        newFactors.add(priorBias);

        //Factor for imu->gps translation
        BetweenFactor<Pose3> imuPgpsFactor(X(0), G(0), imuPgps_,
            noiseModel::Diagonal::Sigmas((Vector(6) << 0.001,0.001,0.001,0.1,0.05,0.05).finished()));
        newFactors.add(imuPgpsFactor);

        // add prior values on pose, vel and bias
        newVariables.insert(X(0), x0);
        newVariables.insert(V(0), Vector3(0, 0, 0));
        newVariables.insert(B(0), imuBias::ConstantBias(biases));
        newVariables.insert(G(0), x0.compose(imuPgps_));

        isam_->update(newFactors, newVariables);
        //Read IMU measurements up to the first GPS measurement
        lastIMU_ = imuOptQ_.popBlocking();
        //If we only pop one, we need some dt
        lastImuTgps_ = TIME(lastIMU_) - 0.005;
        while(TIME(lastIMU_) < TIME(fix))
        {
          lastImuTgps_ = TIME(lastIMU_);
          lastIMU_ = imuOptQ_.popBlocking();
        }
        loop_rate.sleep();
      }
      else //after get the first value
      {
        NonlinearFactorGraph newFactors;
        Values newVariables;


        // add IMU measurements
        while (imuOptQ_.size() > 0 && (TIME(imuOptQ_.back()) > (startTime + imuKey * 0.1)))
        {          
          double curTime = startTime + imuKey * 0.1; // why imukey * 0.1
          PreintegratedImuMeasurements pre_int_data(preintegrationParams_, previousBias_);
          while(TIME(lastIMU_) < curTime) // first gps time + 0.1 step
          {
            Vector3 acc, gyro;
            GetAccGyro(lastIMU_, acc, gyro);
            double imuDT = TIME(lastIMU_) - lastImuTgps_;
            lastImuTgps_ = TIME(lastIMU_);
            pre_int_data.integrateMeasurement(acc, gyro, imuDT);
            lastIMU_ = imuOptQ_.popBlocking();
          }
          // adding the integrated IMU measurements to the factor graph

          ImuFactor imuFactor(X(imuKey-1), V(imuKey-1), X(imuKey), V(imuKey), B(imuKey-1), pre_int_data);
          newFactors.add(imuFactor);
          newFactors.add(BetweenFactor<imuBias::ConstantBias>(B(imuKey-1), B(imuKey), imuBias::ConstantBias(),
              noiseModel::Diagonal::Sigmas( sqrt(pre_int_data.deltaTij()) * noiseModelBetweenBias_sigma_)));

          // Predict forward to get an initial estimate for the pose and velocity
          NavState curNavState(prevPose, prevVel);
          NavState nextNavState = pre_int_data.predict(curNavState, prevBias);
          
          newVariables.insert(X(imuKey), nextNavState.pose());
          newVariables.insert(V(imuKey), nextNavState.v());
          newVariables.insert(B(imuKey), previousBias_); // why no prevBias
          newVariables.insert(G(imuKey), nextNavState.pose().compose(imuPgps_));
          prevPose = nextNavState.pose();
          prevVel = nextNavState.v();
          ++imuKey;
          optimize = true; // we have at least one imu input, in 0.1s
        }
        

        // add GPS measurements that are not ahead of the imu messages
        while (optimize && gpsOptQ_.size() > 0 && TIME(gpsOptQ_.front()) < (startTime + (imuKey-1)*0.1 + 1e-2))
        {
          sensor_msgs::NavSatFixConstPtr fix = gpsOptQ_.popBlocking();
          double timeDiff = (TIME(fix) - startTime) / 0.1; // 
          int key = round(timeDiff); 
          // ROS_WARN("timeDiff = %f", timeDiff);
          // ROS_WARN("key = %d", key);
          if (std::abs(timeDiff - key) < 1e-1) //What does this mean????????????
          { 
            // ROS_WARN("gps updated");
            // this is a gps message for a factor
            latestGPSKey = key;
            double E,N,U;
            // enu_.Forward(fix->latitude, fix->longitude, fix->altitude, E, N, U);
            GeographicLib::UTMUPS::Forward(fix->latitude, fix->longitude,zone_,northp,E,N);
            E -= utm_ori_x;
            N -= utm_ori_y;
            U = fix->altitude - utm_ori_z;
            // check if the GPS message is close to our expected position
            Pose3 expectedState;
            
            if (newVariables.exists(X(key)))
              expectedState = (Pose3) newVariables.at<Pose3>(X(key));
            else
              expectedState = isam_->calculateEstimate<Pose3>(X(key)); // How can it be calculated?

            // ROS_WARN("x = %f,y = %f,z = %f,",expectedState.x(),expectedState.y(),expectedState.z());
            // ROS_WARN("E = %f,N = %f",E,N);
            double dist = std::sqrt( std::pow(expectedState.x() - E, 2) + std::pow(expectedState.y() - N, 2) );
            
            // ROS_WARN("dist = %f", dist);
            // if (dist > maxGPSError_ )
            // {ROS_WARN("dist > maxGPSError");}
            // if (latestGPSKey > imuKey-2)
            // {ROS_WARN("latestGPSKey > imuKey-2");}

            if (dist < maxGPSError_ || latestGPSKey < imuKey-2) // what imuKey-2 mean : Past GPS
            {
              geometry_msgs::PoseWithCovarianceStamped point;
              point.header.stamp = ros::Time::now();
              point.header.frame_id = "map";
              point.pose.pose.position.x = E;
              point.pose.pose.position.y = N;
              point.pose.pose.position.z = U;
              point.pose.covariance[0] = fix->position_covariance[0];
              point.pose.covariance[7] = fix->position_covariance[4];
              point.pose.covariance[14] = fix->position_covariance[8];
              gpsPosPub_.publish(point);

              SharedDiagonal gpsNoise = noiseModel::Diagonal::Sigmas(Vector3(gpsSigma_, gpsSigma_, 0.1*gpsSigma_));
              GPSFactor gpsFactor(G(key), Point3(E, N, U), gpsNoise);
              newFactors.add(gpsFactor);
              BetweenFactor<Pose3> imuPgpsFactor(X(key), G(key), imuPgps_,
                  noiseModel::Diagonal::Sigmas((Vector(6) << 0.001,0.001,0.001,0.1,0.05,0.05).finished()));
              newFactors.add(imuPgpsFactor);

              if (!usingOdom_)
                odomKey = key+1;
            }
            else
            {
              ROS_WARN("Received bad GPS message");
              diag_warn("Received bad GPS message");
            }
          }
        }

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
        // add LocalPose measurements that are not ahead of the imu messages         
        while (optimize && localPoseOptQ_.size() > 0 && TIME(localPoseOptQ_.front()) < (startTime + (imuKey-1)*0.1 + 1e-2))
        {
          geometry_msgs::PoseStampedConstPtr local_pose_ = localPoseOptQ_.popBlocking();
          double timeDiff_ = (TIME(local_pose_) - startTime) / 0.1; // 
          int key_ = round(timeDiff_);                       
          if (std::abs(timeDiff_ - key_) < 1e-1)
          { 
            gtsam::Pose3 local_pose3_ = Pose3(Rot3::Quaternion(local_pose_->pose.orientation.w, local_pose_->pose.orientation.x, local_pose_->pose.orientation.y, local_pose_->pose.orientation.z),Point3(local_pose_->pose.position.x, local_pose_->pose.position.y, local_pose_->pose.position.z));

            // check if the LocalPoseMsg message is close to our expected position
            Pose3 expectedState_;            
            if (newVariables.exists(X(key_)))
              expectedState_ = (Pose3) newVariables.at<Pose3>(X(key_));
            else
              expectedState_ = isam_->calculateEstimate<Pose3>(X(key_));            
            double dist_ = std::sqrt( std::pow(expectedState_.x() - local_pose_->pose.position.x, 2) + std::pow(expectedState_.y() - local_pose_->pose.position.y, 2) );
            
            if (dist_ < maxLocalPoseError_ || key_ < imuKey-2)
            {
              SharedDiagonal LocalPoseNoise = noiseModel::Diagonal::Sigmas(
                      (Vector(6) << 0.01*localPoseSigma_,localPoseSigma_,localPoseSigma_,localPoseSigma_,localPoseSigma_,localPoseSigma_).finished());

              PriorFactor<Pose3> localPosePrior_(X(key_), local_pose3_, LocalPoseNoise);
              newFactors.add(localPosePrior_);
              // newFactors.emplace_shared<PriorFactor<Pose3>>(X(key_), local_pose3_, LocalPoseNoise);
              // newVariables.insert(X(key_), local_pose3_);              
            }
            else
            {
              ROS_WARN("Received bad local Pose message");
              diag_warn("Received bad local Pose message");
            }
          }
        }

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
        
        // if only using odom with no GPS, then remove old messages from queue -> seems weird
        while (!usingOdom_ && odomOptQ_.size() > 0 && TIME(odomOptQ_.front()) < (odomKey*0.1 + startTime))
          lastOdom_ = odomOptQ_.popBlocking();

        // if available, add any odom factors that are not ahead of the imu messages
        while ((usingOdom_) && optimize && odomKey < imuKey && odomOptQ_.size() > 0
            && (TIME(odomOptQ_.front()) < (startTime + odomKey * 0.1)))
        {
          if (!usingWheelAsOdom_){
            double prevTime = startTime + (odomKey-1) * 0.1;

            if(relPoseInit){
              newFactors.add(OdomToFactor(prevTime, prevTime+0.1, odomKey));
              if (TIME(odomOptQ_.back()) > prevTime)
                odomKey++;
            }
            else {
              SetLastPose(prevTime, prevTime+0.1, odomKey++);
            }
          }
          else{
            double prevTime = startTime + (odomKey-1) * 0.1;
            newFactors.add(integrateWheelOdom(prevTime, prevTime+0.1, odomKey++));
          }
        }


        // if we processed imu - then we can optimize the state
        
        if (optimize)
        {
          try
          {
            isam_->update(newFactors, newVariables);
            Pose3 nextState = isam_->calculateEstimate<Pose3>(X(imuKey-1));

            prevPose = nextState;
            prevVel = isam_->calculateEstimate<Vector3>(V(imuKey-1));
            prevBias = isam_->calculateEstimate<imuBias::ConstantBias>(B(imuKey-1));

            // if we haven't added gps data for 2 message (0.2s) then change status
            if (latestGPSKey + 3 < imuKey)
            {
              diag_warn("No gps");
            }
            else
            {
              diag_ok("Still ok!");
            }

            double curTime = startTime + (imuKey-1) * 0.1;

            {
              boost::mutex::scoped_lock guard(optimizedStateMutex_);
              optimizedState_ = NavState(prevPose, prevVel);
              optimizedBias_ = prevBias;
              optimizedTime_ = curTime;
            }

            nav_msgs::Odometry poseNew;
            poseNew.header.stamp = ros::Time::now();

            Vector4 q = optimizedState_.quaternion().coeffs();
            poseNew.pose.pose.orientation.x = q[0];
            poseNew.pose.pose.orientation.y = q[1];
            poseNew.pose.pose.orientation.z = q[2];
            poseNew.pose.pose.orientation.w = q[3];

            poseNew.pose.pose.position.x = optimizedState_.position().x();
            poseNew.pose.pose.position.y = optimizedState_.position().y();
            poseNew.pose.pose.position.z = optimizedState_.position().z();

            poseNew.twist.twist.linear.x = optimizedState_.velocity().x();
            poseNew.twist.twist.linear.y = optimizedState_.velocity().y();
            poseNew.twist.twist.linear.z = optimizedState_.velocity().z();
            pub_optPose.publish(poseNew);

            
            geometry_msgs::Point ptAcc;
            ptAcc.x = prevBias.vector()[0];
            ptAcc.y = prevBias.vector()[1];
            ptAcc.z = prevBias.vector()[2];

            geometry_msgs::Point ptGyro;
            ptGyro.x = prevBias.vector()[3];
            ptGyro.y = prevBias.vector()[4];
            ptGyro.z = prevBias.vector()[5];

            biasAccPub_.publish(ptAcc);
            biasGyroPub_.publish(ptGyro);
          }
          catch(gtsam::IndeterminantLinearSystemException ex)
          {
            ROS_ERROR("Encountered Indeterminant System Error!");
            diag_error("State estimator has encountered indeterminant system error");
            {
              boost::mutex::scoped_lock guard(optimizedStateMutex_);
            }
          }
        }
        loop_rate.sleep();
      }
    }
  }


  void StateEstimator::ImuCallback(sensor_msgs::ImuConstPtr imu)
  {
    double dt;
    if (lastImuT_ == 0) dt = 0.005; // 200 Hz 
    else dt = TIME(imu) - lastImuT_;

    lastImuT_ = TIME(imu);
    //ros::Time before = ros::Time::now();

    // Push the IMU measurement to the optimization thread
    int qSize = imuOptQ_.size();
    if (qSize > maxQSize_)
      maxQSize_ = qSize;
    if (!imuOptQ_.pushNonBlocking(imu))
      ROS_WARN("Dropping an IMU measurement due to full queue!!");

    // Each time we get an imu measurement, calculate the incremental pose from the last GTSAM pose
    imuMeasurements_.push_back(imu);
    //Grab the most current optimized state
    double optimizedTime;
    NavState optimizedState;
    imuBias::ConstantBias optimizedBias;
    unsigned char status;
    {
      boost::mutex::scoped_lock guard(optimizedStateMutex_);
      optimizedState = optimizedState_;
      optimizedBias = optimizedBias_;
      optimizedTime = optimizedTime_;
    }
    if (optimizedTime == 0) return; // haven't optimized first state yet

    bool newMeasurements = false;
    int numImuDiscarded = 0;
    double imuQPrevTime;
    Vector3 acc, gyro;
    while (!imuMeasurements_.empty() && (TIME(imuMeasurements_.front()) < optimizedTime))
    {
      imuQPrevTime = TIME(imuMeasurements_.front());
      imuMeasurements_.pop_front();
      newMeasurements = true;
      numImuDiscarded++;
    }

    if(newMeasurements)
    {
      //We need to reset integration and iterate through all our IMU measurements
      imuPredictor_->resetIntegration();
      int numMeasurements = 0;
      for (auto it=imuMeasurements_.begin(); it!=imuMeasurements_.end(); ++it)
      {
        double dt_temp =  TIME(*it) - imuQPrevTime;
        imuQPrevTime = TIME(*it);
        GetAccGyro(*it, acc, gyro);
        imuPredictor_->integrateMeasurement(acc, gyro, dt_temp);
        numMeasurements++;
        // ROS_INFO("IMU time %f, dt %f", (*it)->header.stamp.toSec(), dt_temp);
      }
      // ROS_INFO("Resetting Integration, %d measurements integrated, %d discarded", numMeasurements, numImuDiscarded);
    }
    else
    {
      //Just need to add the newest measurement, no new optimized pose
      GetAccGyro(imu, acc, gyro);
      imuPredictor_->integrateMeasurement(acc, gyro, dt);
      // ROS_INFO("Integrating %f, dt %f", m_lastImuT, dt);
    }

    // predict next state given the imu measurements
    NavState currentPose = imuPredictor_->predict(optimizedState, optimizedBias);
    nav_msgs::Odometry poseNew;
    poseNew.header.stamp = imu->header.stamp;

    Vector4 q = currentPose.quaternion().coeffs();
    poseNew.pose.pose.orientation.x = q[0];
    poseNew.pose.pose.orientation.y = q[1];
    poseNew.pose.pose.orientation.z = q[2];
    poseNew.pose.pose.orientation.w = q[3];

    poseNew.pose.pose.position.x = currentPose.position().x();
    poseNew.pose.pose.position.y = currentPose.position().y();
    poseNew.pose.pose.position.z = currentPose.position().z();

    poseNew.twist.twist.linear.x = currentPose.velocity().x();
    poseNew.twist.twist.linear.y = currentPose.velocity().y();
    poseNew.twist.twist.linear.z = currentPose.velocity().z();
    
    poseNew.twist.twist.angular.x = gyro.x() + optimizedBias.gyroscope().x();
    poseNew.twist.twist.angular.y = gyro.y() + optimizedBias.gyroscope().y();
    poseNew.twist.twist.angular.z = gyro.z() + optimizedBias.gyroscope().z();

    poseNew.child_frame_id = "base_link";
    poseNew.header.frame_id = "map";


    //////////////////////////
      tf::Transform transform;
      transform.setOrigin( tf::Vector3(poseNew.pose.pose.position.x, poseNew.pose.pose.position.y, poseNew.pose.pose.position.z) );
      tf::Quaternion q_tmp(poseNew.pose.pose.orientation.x,poseNew.pose.pose.orientation.y,poseNew.pose.pose.orientation.z,poseNew.pose.pose.orientation.w);      
      transform.setRotation(q_tmp);
      tf_br.sendTransform(tf::StampedTransform(transform, poseNew.header.stamp, "map", "os_sensor"));
    ///////////////////////////
    posePub_.publish(poseNew);
    
    geometry_msgs::PoseStamped est_pose_new;
    est_pose_new.header = poseNew.header;
    est_pose_new.pose.position = poseNew.pose.pose.position;
    est_pose_new.pose.orientation = poseNew.pose.pose.orientation;
    est_pose_new.header.frame_id = "map";
    estPosePub.publish(est_pose_new);

    geometry_msgs::Point delays;
    delays.x = TIME(imu);
    delays.y = (ros::Time::now() - imu->header.stamp).toSec();
    delays.z = TIME(imu) - optimizedTime;
    timePub_.publish(delays);

    // publish the status of the estimate - set in the gpsHelper thread
    return;
  }

  void StateEstimator::WheelOdomCallback(nav_msgs::OdometryConstPtr odom)
  {
    if (usingOdom_ && usingWheelAsOdom_){
      if (!odomOptQ_.pushNonBlocking(odom)) {
        ROS_WARN("Dropping an wheel odometry measurement due to full queue!!");
      }
    }
  }

  void StateEstimator::OdomCallback(nav_msgs::OdometryConstPtr odom_)
  {
    if (usingOdom_ && !usingWheelAsOdom_){
      if (!odomOptQ_.pushNonBlocking(odom_)) {
        ROS_WARN("Dropping an odometry measurement due to full queue!!");
      }
    }
  }

  void StateEstimator::SetLastPose(double prevTime, double stopTime, int curKey){
    double dt=0, lastTimeUsed=prevTime;
    while (lastTimeUsed != stopTime)
    {
      if (odomOptQ_.size() != 0 && TIME(odomOptQ_.front()) < stopTime)
      {
        lastOdom_ = odomOptQ_.popBlocking();
        dt = TIME(lastOdom_) - lastTimeUsed;
        lastTimeUsed = TIME(lastOdom_);
      }
      else
      {
        dt = stopTime - lastTimeUsed;
        lastTimeUsed = stopTime;
      }
    }
    auto tx = lastOdom_->pose.pose.position.x;
    auto ty = lastOdom_->pose.pose.position.y;
    auto tz = lastOdom_->pose.pose.position.z;

    double roll, pitch, yaw;
    geometry_msgs::Quaternion quat_ = lastOdom_->pose.pose.orientation;
    tf::Matrix3x3(tf::Quaternion(quat_.x,quat_.y,quat_.z,quat_.w)).getRPY(roll,pitch,yaw);

    Pose3 last_pose_input = Pose3(Rot3::RzRyRx(yaw,pitch,roll), Point3(tx, ty, tz));
    relPoseInit = true;
  }

  BetweenFactor<Pose3> StateEstimator::OdomToFactor(double prevTime, double stopTime, int curKey)
  {
    double thetaVariance=0.1, dt=0, lastTimeUsed=prevTime;

    while (lastTimeUsed != stopTime)
    {
      if (odomOptQ_.size() != 0 && TIME(odomOptQ_.front()) < stopTime)
      {
        lastOdom_ = odomOptQ_.popBlocking();
        dt = TIME(lastOdom_) - lastTimeUsed;
        lastTimeUsed = TIME(lastOdom_);
      }
      else
      {
        dt = stopTime - lastTimeUsed;
        lastTimeUsed = stopTime;
      }
    }

    auto tx = lastOdom_->pose.pose.position.x;
    auto ty = lastOdom_->pose.pose.position.y;
    auto tz = lastOdom_->pose.pose.position.z;

    double roll, pitch, yaw;
    geometry_msgs::Quaternion quat_ = lastOdom_->pose.pose.orientation;
    tf::Matrix3x3(tf::Quaternion(quat_.x,quat_.y,quat_.z,quat_.w)).getRPY(roll,pitch,yaw);

    Pose3 current_pose_input = Pose3(Rot3::RzRyRx(yaw,pitch,roll), Point3(tx, ty, tz));
    Pose3 betweenPose = last_pose_input.between(current_pose_input);
    last_pose_input = current_pose_input;
    betweenPose.print("Between pose");
    return BetweenFactor<Pose3>(X(curKey-1), X(curKey), betweenPose, noiseModel::Diagonal::Sigmas(
          (Vector(6) << thetaVariance,thetaVariance,thetaVariance,0.05,0.05,0.05).finished()));
  }


  BetweenFactor<Pose3> StateEstimator::integrateWheelOdom(double prevTime, double stopTime, int curKey)
  {
    double x=0, y=0, theta=0, xVar=0, yVar=0, zVar=0, thetaVariance=0, dt=0, lastTimeUsed=prevTime;

    while (lastTimeUsed != stopTime)
    {
      if (odomOptQ_.size() != 0 && TIME(odomOptQ_.front()) < stopTime)
      {
        lastOdom_ = odomOptQ_.popBlocking();
        dt = TIME(lastOdom_) - lastTimeUsed;
        lastTimeUsed = TIME(lastOdom_);
      }
      else
      {
        dt = stopTime - lastTimeUsed;
        lastTimeUsed = stopTime;
      }

      // the local frame velocities
      if((lastOdom_->twist.twist.linear.x  != lastOdom_->twist.twist.linear.x) || (lastOdom_->twist.twist.linear.y  != lastOdom_->twist.twist.linear.y) || (lastOdom_->twist.twist.angular.z != lastOdom_->twist.twist.angular.z)){
              continue;
      }
      double vx = lastOdom_->twist.twist.linear.x;
      double vy = lastOdom_->twist.twist.linear.y;
      // update the relative position from the initial
      x += vx*dt*cos(theta) - vy*dt*sin(theta);
      y += vx*dt*sin(theta) + vy*dt*cos(theta);
      theta += dt*lastOdom_->twist.twist.angular.z;
      xVar += dt * lastOdom_->twist.covariance[0];
      yVar += dt * lastOdom_->twist.covariance[7];
      zVar += dt * lastOdom_->twist.covariance[14];
      thetaVariance += dt*lastOdom_->twist.covariance[35];
    }

    Pose3 betweenPose = Pose3(Rot3::Rz(theta), Point3(x, y, 0.0));
    return BetweenFactor<Pose3>(X(curKey-1), X(curKey), betweenPose, noiseModel::Diagonal::Sigmas(
          (Vector(6) << thetaVariance*2,thetaVariance*2,thetaVariance,xVar,yVar,zVar).finished()));
  }

  void StateEstimator::diagnosticStatus(const ros::TimerEvent& /*time*/)
  {
    //Don't do anything
    //diag_info("Test");
  }

};

int main (int argc, char** argv)
{
  ros::init(argc, argv, "StateEstimator");
  //ros::NodeHandle n;
  localization_core::StateEstimator wpt;
  ros::spin();
}
