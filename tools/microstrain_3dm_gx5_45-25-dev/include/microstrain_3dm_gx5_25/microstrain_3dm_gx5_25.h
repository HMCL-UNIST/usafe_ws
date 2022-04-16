/** ROS node

/*

Copyright (c) 2017, Brian Bingham
All rights reserved

This file is part of the microstrain_3dm_gx5_45 package.

microstrain_3dm_gx5_45 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

microstrain_3dm_gx5_45 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef _MICROSTRAIN_3DM_GX5_25_H
#define _MICROSTRAIN_3DM_GX5_25_H

// Tell compiler that the following MIP SDI are C functions
extern "C" {
#include "mip_sdk.h"
#include "byteswap_utilities.h"
#include "mip_gx4_imu.h"
#include "mip_gx4_25.h"
}

#include <cstdio>
#include <unistd.h>


// ROS
#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_srvs/Empty.h"
#include "sensor_msgs/MagneticField.h"
#include "geometry_msgs/Vector3Stamped.h"

#define MIP_SDK_GX4_25_IMU_STANDARD_MODE	0x01
#define MIP_SDK_GX4_25_IMU_DIRECT_MODE	0x02

#define NUM_COMMAND_LINE_ARGUMENTS 3

#define DEFAULT_PACKET_TIMEOUT_MS  1000 //milliseconds

//macro to cause Sleep call to behave as it does for windows
#define Sleep(x) usleep(x*1000.0)

/**
 * \brief Contains functions for micostrain driver
 */
namespace Microstrain
{
  /**
   * \brief Microstrain class
   *
   */

  class Microstrain
  {
  public:
    /**
     * Contructor
     */
    Microstrain();

    /** Destructor */
    ~Microstrain();

    /**
     * Main run loop
     */
    void run();

    //! EKF callback
    void filter_packet_callback(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type);
    //! @brief AHRS (CF) callback
    void ahrs_packet_callback(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type);


  private:
  //! @brief Reset KF service callback
  bool reset_callback(std_srvs::Empty::Request &req,
		      std_srvs::Empty::Response &resp);
  //! @brief Convience for printing packet stats
  void print_packet_stats();

  // Variables/fields
  //The primary device interface structure
  mip_interface device_interface_;

  //Packet Counters (valid, timeout, and checksum errors)
  u32 filter_valid_packet_count_;
  u32 ahrs_valid_packet_count_;

  u32 filter_timeout_packet_count_;
  u32 ahrs_timeout_packet_count_;

  u32 filter_checksum_error_packet_count_;
  u32 ahrs_checksum_error_packet_count_;

  //Data field storage
  //AHRS
  mip_ahrs_scaled_gyro  curr_ahrs_gyro_;
  mip_ahrs_scaled_accel curr_ahrs_accel_;
  mip_ahrs_scaled_mag   curr_ahrs_mag_;
  mip_ahrs_quaternion  curr_ahrs_quaternion_;
  mip_ahrs_euler_angles curr_ahrs_euler_angles_;

  //FILTER
  mip_filter_llh_pos               curr_filter_pos_;
  mip_filter_ned_velocity          curr_filter_vel_;
  mip_filter_attitude_euler_angles curr_filter_angles_;
  mip_filter_attitude_quaternion   curr_filter_quaternion_;
  mip_filter_compensated_angular_rate curr_filter_angular_rate_;
  mip_filter_llh_pos_uncertainty   curr_filter_pos_uncertainty_;
  mip_filter_ned_vel_uncertainty   curr_filter_vel_uncertainty_;
  mip_filter_euler_attitude_uncertainty curr_filter_att_uncertainty_;
  mip_filter_status curr_filter_status_;
  mip_filter_compensated_acceleration curr_filter_accel_;
  mip_filter_quaternion_attitude_uncertainty curr_filter_quat_uncertainty_;

   // ROS
   ros::Publisher status_pub_;
   std_msgs::Int16MultiArray status_msg_;
   std::string imu_frame_id_;
   bool tf_ned_to_enu_;
   //Complementary Filter
   ros::Publisher cf_pub_;
   bool publish_cf_;
   int cf_rate_;
   sensor_msgs::Imu cf_imu_msg_;

   //EKF Filter
   ros::Publisher ekf_pub_;
   int ekf_rate_;
   sensor_msgs::Imu ekf_imu_msg_;

   //Magnetometer
   ros::Publisher mag_pub_;
   bool publish_mag_;
   sensor_msgs::MagneticField mag_msg_;

   //RPY
   bool publish_rpy_;
   ros::Publisher cf_rpy_pub_;
   ros::Publisher ekf_rpy_pub_;
   geometry_msgs::Vector3Stamped cf_rpy_msg_;
   geometry_msgs::Vector3Stamped ekf_rpy_msg_;

  }; // Microstrain class


  // Define wrapper functions that call the Microstrain member functions
#ifdef __cplusplus
  extern "C"
#endif
  {

    /**
     * Callback for KF estimate packets from sensor.
     */
    void filter_packet_callback_wrapper(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type);
    /**
     * Callback for AHRS packets from sensor.
     */
    void ahrs_packet_callback_wrapper(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type);


#ifdef __cplusplus
  }
#endif

} // namespace Microstrain

#endif  // _MICROSTRAIN_3DM_GX5_45_H
