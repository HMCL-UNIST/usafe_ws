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

#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include "state_estimator/Diagnostics.h"
#include "BlockingQueue.h"

#include <imu_3dm_gx4/FilterOutput.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/MarkerArray.h>

#include <tf/transform_broadcaster.h>

#define PI 3.14159265358979323846264338


namespace localization_core
{
  class StateEstimator : public Diagnostics
  {
  private:
    ros::NodeHandle nh_;
    ros::Subscriber gpsSub_, imuSub_, odomSub_, localPoseSub_;
    ros::Publisher  posePub_, estPosePub, pub_optPose, test_pub;
    ros::Publisher  biasAccPub_, biasGyroPub_;
    ros::Publisher  timePub_;
    ros::Publisher statusPub_;
    ros::Publisher gpsPosPub_;

    tf::TransformBroadcaster tf_br;

    double lastImuT_, lastImuTgps_;
    unsigned char status_;
    double accelBiasSigma_, gyroBiasSigma_;
    double gpsSigma_, localPoseSigma_;
    int maxQSize_;

    BlockingQueue<sensor_msgs::NavSatFixConstPtr> gpsOptQ_;
    BlockingQueue<sensor_msgs::ImuConstPtr> imuOptQ_;
    BlockingQueue<nav_msgs::OdometryConstPtr> odomOptQ_;
    BlockingQueue<geometry_msgs::PoseStampedConstPtr> localPoseOptQ_;

    boost::mutex optimizedStateMutex_;
    gtsam::NavState optimizedState_;
    double optimizedTime_;
    boost::shared_ptr<gtsam::PreintegratedImuMeasurements> imuPredictor_;
    double imuDt_;
    gtsam::imuBias::ConstantBias optimizedBias_, previousBias_;
    sensor_msgs::ImuConstPtr lastIMU_;
    boost::shared_ptr<gtsam::PreintegrationParams> preintegrationParams_;

    std::list<sensor_msgs::ImuConstPtr> imuMeasurements_, imuGrav_;
    
    // sensor_msgs::ImuConstPtr ip;
    geometry_msgs::PoseStampedConstPtr ip;
    imu_3dm_gx4::FilterOutput initialPose_;
    gtsam::Pose3 bodyPSensor_, carENUPcarNED_;
    gtsam::Pose3 imuPgps_;
    gtsam::Pose3 last_pose_input;
    bool relPoseInit = false;

    bool fixedOrigin_;
    GeographicLib::LocalCartesian enu_;   /// Object to put lat/lon coordinates into local cartesian
    // GeographicLib::UTMUPS utm_;
    int zone_;
    bool northp;
    double utm_ori_x, utm_ori_y, utm_ori_z;
    bool gotFirstFix_, gotFirstLocalPose_;
    bool invertx_, inverty_, invertz_;
    bool usingOdom_, usingLocalPose_, usingWheelAsOdom_;
    double maxGPSError_, maxLocalPoseError_;

    gtsam::SharedDiagonal priorNoisePose_;
    gtsam::SharedDiagonal priorNoiseVel_;
    gtsam::SharedDiagonal priorNoiseBias_;
    gtsam::Vector noiseModelBetweenBias_sigma_;
    gtsam::ISAM2 *isam_;

    nav_msgs::OdometryConstPtr lastOdom_;
    geometry_msgs::PoseStampedConstPtr lastLocalPose_;

  public:
    StateEstimator();
    ~StateEstimator();
    void testDebug();
    void GpsCallback(sensor_msgs::NavSatFixConstPtr fix);
    void ImuCallback(sensor_msgs::ImuConstPtr imu);
    void OdomCallback(nav_msgs::OdometryConstPtr odom_);
    void WheelOdomCallback(nav_msgs::OdometryConstPtr odom);
    void localPoseCallback(geometry_msgs::PoseStampedConstPtr pose);
    void GpsHelper();
    void GpsHelper_1();
    void diagnosticStatus(const ros::TimerEvent& time);
    gtsam::BetweenFactor<gtsam::Pose3> integrateWheelOdom(double prevTime, double stopTime, int curFactor);
    gtsam::BetweenFactor<gtsam::Pose3> OdomToFactor(double prevTime, double stopTime, int curFactor);
    void SetLastPose(double prevTime, double stopTime, int curKey);
    void GetAccGyro(sensor_msgs::ImuConstPtr imu, gtsam::Vector3 &acc, gtsam::Vector3 &gyro);
    
  };
};

#endif /* StateEstimator_H_ */
