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

#include "microstrain_3dm_gx5_25.h"
#include <tf2/LinearMath/Transform.h>
#include <string>
#include <algorithm>

namespace Microstrain
{
Microstrain::Microstrain() :
	// Initialization list
	filter_valid_packet_count_(0),
	ahrs_valid_packet_count_(0),
	filter_timeout_packet_count_(0),
	ahrs_timeout_packet_count_(0),
	filter_checksum_error_packet_count_(0),
	ahrs_checksum_error_packet_count_(0),
	imu_frame_id_("imu_frame"),
	publish_cf_(false),
	publish_rpy_(false),
	publish_mag_(false),
	tf_ned_to_enu_(true)
{
	// pass
}
Microstrain::~Microstrain()
{
	// pass
}
//void quaternionCovFromYawPitchRollCov(float yaw, float pitch, float roll);
void Microstrain::run()
{
// Variables for device configuration, ROS parameters, etc.
	u32 com_port, baudrate;
	bool device_setup = false;
	bool readback_settings = true;
	bool save_settings = true;
	bool auto_init = true;
	u8 auto_init_u8 = 1;
	u8 readback_headingsource = 0;
	u8 readback_auto_init = 0;
	u8 dynamics_mode           = 0;
	u8 readback_dynamics_mode  = 0;
	int declination_source;
	u8 declination_source_u8;
	u8 readback_declination_source;
	double declination;

	// Variables
	tf2::Quaternion quat;
	base_device_info_field device_info;
	u8 temp_string[20] = {0};
	u32 bit_result;
	u8 enable = 1;
	u8 data_stream_format_descriptors[10];
	u16 data_stream_format_decimation[10];
	u8 data_stream_format_num_entries = 0;
	u8 readback_data_stream_format_descriptors[10] = {0};
	u16 readback_data_stream_format_decimation[10]  = {0};
	u8 readback_data_stream_format_num_entries     =  0;
	u16 base_rate = 0;
	u16 device_descriptors[128]  = {0};
	u16 device_descriptors_size  = 128*2;
	s16 i;
	u16 j;
	u8 com_mode = 0;
	u8 readback_com_mode = 0;
	float angles[3]             = {0};
	float readback_angles[3]    = {0};
	float offset[3]             = {0};
	float readback_offset[3]    = {0};
	float hard_iron[3]          = {0};
	float hard_iron_readback[3] = {0};
	float soft_iron[9]          = {0};
	float soft_iron_readback[9] = {0};
	u16 estimation_control   = 0, estimation_control_readback = 0;
	u8 heading_source = 0x1;
	float noise[3]          = {0};
	float readback_noise[3] = {0};
	float beta[3]                 = {0};
	float readback_beta[3]        = {0};
	mip_low_pass_filter_settings filter_settings;
	float bias_vector[3]       = {0};
	u16 duration = 0;
	gx4_imu_diagnostic_device_status_field imu_diagnostic_field;
	gx4_imu_basic_status_field imu_basic_field;
	gx4_25_diagnostic_device_status_field diagnostic_field;
	gx4_25_basic_status_field basic_field;
	mip_filter_external_heading_update_command external_heading_update;
	mip_filter_zero_update_command zero_update_control, zero_update_readback;
	mip_filter_external_heading_with_time_command external_heading_with_time;
	mip_complementary_filter_settings comp_filter_command, comp_filter_readback;

	mip_filter_accel_magnitude_error_adaptive_measurement_command accel_magnitude_error_command, accel_magnitude_error_readback;
	mip_filter_magnetometer_magnitude_error_adaptive_measurement_command mag_magnitude_error_command, mag_magnitude_error_readback;
	mip_filter_magnetometer_dip_angle_error_adaptive_measurement_command mag_dip_angle_error_command, mag_dip_angle_error_readback;

	// ROS setup
	ros::Time::init();
	ros::NodeHandle node;
	ros::NodeHandle private_nh("~");

	// ROS Parameters
	// Comms Parameters
	std::string port;
	int baud, pdyn_mode;
	private_nh.param("port", port, std::string("/dev/ttyACM3"));
	private_nh.param("baudrate",baud,115200);
	baudrate = (u32)baud;
	// Configuration Parameters
	private_nh.param("device_setup",device_setup,false);
	private_nh.param("readback_settings",readback_settings,true);
	private_nh.param("save_settings",save_settings,true);

	private_nh.param("auto_init",auto_init,true);
	private_nh.param("cf_rate",cf_rate_, 10);
	private_nh.param("ekf_rate",ekf_rate_, 10);
	private_nh.param("dynamics_mode",pdyn_mode,1);

	///////////////////////////////////////////////////////////////////////
	//Dynamics Mode Options:
	//1 = Portable, 2 = Automotive, 3 = Airborne
	///////////////////////////////////////////////////////////////////////
	dynamics_mode = (u8)pdyn_mode; //(u8)pdyn_mode;
	if (dynamics_mode < 1 || dynamics_mode > 3) {
		ROS_WARN("dynamics_mode can't be %#04X, must be 1, 2 or 3.  Setting to 1.",dynamics_mode);
		dynamics_mode = 1;
	}

	///////////////////////////////////////////////////////////////////////
	//Declination Source (0x0D, 0x43)
	//0x01 - None, 0x02 - World Magnetic Model (Default), 0x03 (Manual)
	///////////////////////////////////////////////////////////////////////
	ROS_INFO("Dynamics mode set to: %#04X", dynamics_mode);
	private_nh.param("declination_source",declination_source,2);
	if (declination_source < 1 || declination_source > 3) {
		ROS_WARN("declination_source can't be %#04X, must be 1, 2 or 3.  Setting to 2.",declination_source);
		declination_source = 2;
	}
	declination_source_u8 = (u8)declination_source;

	private_nh.param("declination",declination,0.23);
	private_nh.param("imu_frame_id",imu_frame_id_, std::string("imu_link"));
	private_nh.param("publish_cf",publish_cf_, false);
	private_nh.param("publish_rpy",publish_rpy_,false);
	private_nh.param("publish_mag",publish_mag_,false);
	private_nh.param("tf_ned_to_enu",tf_ned_to_enu_,true);

	// ROS publishers and subscribers
	status_pub_ = node.advertise<std_msgs::Int16MultiArray>("imu/status",100);
	ekf_pub_ = node.advertise<sensor_msgs::Imu>("imu/data",100);
	if (publish_rpy_)
		ekf_rpy_pub_ = node.advertise<geometry_msgs::Vector3Stamped>("imu/rpy",100);

	if (publish_cf_)
	{
		cf_pub_ = node.advertise<sensor_msgs::Imu>("imu/cf/data",100);
		if (publish_rpy_)
			cf_rpy_pub_ = node.advertise<geometry_msgs::Vector3Stamped>("imu/cf/rpy",100);
	}

	if (publish_mag_)
		mag_pub_ = node.advertise<sensor_msgs::MagneticField>("imu/mag",100);                                                                                                                 //SJP Added


	ros::ServiceServer service = node.advertiseService("reset_kf", &Microstrain::reset_callback, this);


	//Initialize the serial interface to the device
	ROS_INFO("Attempting to open serial port <%s> at <%d> \n",
	         port.c_str(),baudrate);
	if(mip_interface_init(port.c_str(), baudrate, &device_interface_, DEFAULT_PACKET_TIMEOUT_MS) != MIP_INTERFACE_OK) {
		ROS_FATAL("Couldn't open serial port!  Is it plugged in?");
	}


	// Setup device callbacks
	if(mip_interface_add_descriptor_set_callback(&device_interface_, MIP_FILTER_DATA_SET, this, &filter_packet_callback_wrapper) != MIP_INTERFACE_OK)
	{
		ROS_INFO("Can't setup filter (EKF Estimate) callback!");
		return;
	}
	if(mip_interface_add_descriptor_set_callback(&device_interface_, MIP_AHRS_DATA_SET, this, &ahrs_packet_callback_wrapper) != MIP_INTERFACE_OK)
	{
		ROS_INFO("Can't setup ahrs (CF Estimate) callbacks!");
		return;
	}

	////////////////////////////////////////
	// Device setup
	////////////////////////////////////////
	float dT=0.5; // common sleep time after setup communications
	if (device_setup)
	{
		// Put device into standard mode - we never really use "direct mode"
		ROS_INFO("Putting device communications into 'standard mode'");
		device_descriptors_size  = 128*2;
		com_mode = MIP_SDK_GX4_25_IMU_STANDARD_MODE; //MIP_SDK_GX4_45_IMU_STANDARD_MODE = 0x01
		while(mip_system_com_mode(&device_interface_, MIP_FUNCTION_SELECTOR_WRITE, &com_mode) != MIP_INTERFACE_OK) {}
		//Verify device mode setting
		ROS_INFO("Verify comm's mode");
		while(mip_system_com_mode(&device_interface_, MIP_FUNCTION_SELECTOR_READ, &com_mode) != MIP_INTERFACE_OK) {}
		ROS_INFO("Sleep for a second...");
		ros::Duration(dT).sleep();
		ROS_INFO("Right mode?");
		if(com_mode != MIP_SDK_GX4_25_IMU_STANDARD_MODE)
		{
			ROS_ERROR("Appears we didn't get into standard mode!");
		}

		// Put into idle mode
		ROS_INFO("Idling Device: Stopping data streams and/or waking from sleep");
		while(mip_base_cmd_idle(&device_interface_) != MIP_INTERFACE_OK) {}
		ros::Duration(dT).sleep();


		//////////////////////////////////////////////////////////////////////////
		// Magnetometer calibration readbacks
		//////////////////////////////////////////////////////////////////////////
		while(mip_3dm_cmd_hard_iron(&device_interface_, MIP_FUNCTION_SELECTOR_READ, hard_iron_readback) != MIP_INTERFACE_OK){}
		std::cout << "Hard iron offsets are: [X = " << hard_iron_readback[0] <<
							 "] [Y = " << hard_iron_readback[1] <<
						    "] [Z = " << hard_iron_readback[2] << "]." << std::endl;

		while(mip_3dm_cmd_soft_iron(&device_interface_, MIP_FUNCTION_SELECTOR_READ, soft_iron_readback) != MIP_INTERFACE_OK){}
		std::cout << "Soft iron matrix is: [" << soft_iron_readback[0] << " " << soft_iron_readback[1] << " " << soft_iron_readback[2] << std::endl;
  		std::cout << "                      " << soft_iron_readback[3] << " " << soft_iron_readback[4] << " " << soft_iron_readback[5] << std::endl;
		std::cout << "                      " << soft_iron_readback[6] << " " << soft_iron_readback[7] << " " << soft_iron_readback[8] << "]." << std::endl;

		////////////////////////////////////
		// AHRS Setup - Complementary Filter
		////////////////////////////////////
		if (publish_cf_ | publish_mag_) {
			// Get base rate
			while(mip_3dm_cmd_get_ahrs_base_rate(&device_interface_, &base_rate) != MIP_INTERFACE_OK) {}
			ROS_INFO("AHRS Base Rate => %d Hz", base_rate);
			ros::Duration(dT).sleep();

			// Deterimine decimation to get close to goal rate
			u8 cf_decimation = (u8)((float)base_rate/ (float)cf_rate_);
			ROS_INFO("AHRS (CF) decimation set to %#04X",cf_decimation);

			// AHRS Message Format
			ROS_INFO("Setting the AHRS message format");
			data_stream_format_descriptors[0] = MIP_AHRS_DATA_ACCEL_SCALED;
			data_stream_format_descriptors[1] = MIP_AHRS_DATA_GYRO_SCALED;
			data_stream_format_descriptors[2] = MIP_AHRS_DATA_QUATERNION;
			data_stream_format_descriptors[3] = MIP_AHRS_DATA_MAG_SCALED;
			data_stream_format_descriptors[4] = MIP_AHRS_DATA_EULER_ANGLES;

			data_stream_format_decimation[0]  = cf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[1]  = cf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[2]  = cf_decimation;                                                                                                                                                                        //0x32;                                                                                                                                                                    //SJP Added
			data_stream_format_decimation[3]  = cf_decimation;                                                                                                                                                                        //0x32; SJP Added                                                                                                                                                      //SJP Added
			data_stream_format_decimation[4]  = cf_decimation;                                                                                                                                                                        //0x32; SJP Added

			data_stream_format_num_entries = 5;                                                                                                                                                                         //SJP Changed from 3;

			// Set message format
			while(mip_3dm_cmd_ahrs_message_format(&device_interface_, MIP_FUNCTION_SELECTOR_WRITE, &data_stream_format_num_entries, data_stream_format_descriptors, data_stream_format_decimation) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();

			// Poll to verify
			ROS_INFO("Poll AHRS data to verify");
			while(mip_3dm_cmd_poll_ahrs(&device_interface_, MIP_3DM_POLLING_ENABLE_ACK_NACK, data_stream_format_num_entries, data_stream_format_descriptors) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();

			// Save
			if (save_settings)
			{
				ROS_INFO("Saving AHRS (CF) data settings");
				while(mip_3dm_cmd_ahrs_message_format(&device_interface_, MIP_FUNCTION_SELECTOR_STORE_EEPROM, 0, NULL,NULL) != MIP_INTERFACE_OK) {}
				ros::Duration(dT).sleep();
			}

			// Declination Source
			// Set declination
			ROS_INFO("Setting declination source to %#04X",declination_source_u8);
			while(mip_filter_declination_source(&device_interface_, MIP_FUNCTION_SELECTOR_WRITE, &declination_source_u8) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();
			//Read back the declination source
			ROS_INFO("Reading back declination source");
			while(mip_filter_declination_source(&device_interface_, MIP_FUNCTION_SELECTOR_READ, &readback_declination_source) != MIP_INTERFACE_OK) {}
			if(declination_source_u8 == readback_declination_source)
			{
				ROS_INFO("Success: Declination source set to %#04X", declination_source_u8);
			}
			else
			{
				ROS_WARN("Failed to set the declination source to %#04X!", declination_source_u8);
			}
			ros::Duration(dT).sleep();
			if (save_settings)
			{
				ROS_INFO("Saving declination source settings to EEPROM");
				while(mip_filter_declination_source(&device_interface_,
				                                    MIP_FUNCTION_SELECTOR_STORE_EEPROM,
				                                    NULL) != MIP_INTERFACE_OK)
				{}
				ros::Duration(dT).sleep();
			}

		}  // end of AHRS setup


		//////////////////////////////
		// Filter Setup - EKF Estimate
		//////////////////////////////
			//Get base rate
			while(mip_3dm_cmd_get_filter_base_rate(&device_interface_, &base_rate) != MIP_INTERFACE_OK) {}
			ROS_INFO("Filter (EKF) Base Rate => %d Hz", base_rate);
			u8 ekf_decimation = (u8)((float)base_rate/ (float)ekf_rate_);
			ros::Duration(dT).sleep();
			ROS_INFO("Filter (EKF) decimation set to %#04X",ekf_decimation);

			//Filter Message Format
			ROS_INFO("Setting Filter stream format");
			data_stream_format_descriptors[0] = MIP_FILTER_DATA_COMPENSATED_ACCELERATION;
			data_stream_format_descriptors[1] = MIP_FILTER_DATA_ATT_EULER_ANGLES;
			data_stream_format_descriptors[2] = MIP_FILTER_DATA_ATT_QUATERNION;
			data_stream_format_descriptors[3] = MIP_FILTER_DATA_COMPENSATED_ANGULAR_RATE;
			data_stream_format_descriptors[4] = MIP_FILTER_DATA_FILTER_STATUS;
			data_stream_format_descriptors[5] = MIP_FILTER_DATA_ATT_UNCERTAINTY_EULER;
			data_stream_format_descriptors[6] = MIP_FILTER_DATA_ATT_UNCERTAINTY_QUATERNION;

			data_stream_format_decimation[0]  = ekf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[1]  = ekf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[2]  = ekf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[3]  = ekf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[4]  = ekf_decimation;                                                                                                                                                                        //0x32;
			data_stream_format_decimation[5]  = ekf_decimation;
      	data_stream_format_decimation[6]  = ekf_decimation;

			data_stream_format_num_entries = 7;

			ROS_INFO("Finished setting Filter stream format");

			// Set Filter Message Format
			while(mip_3dm_cmd_filter_message_format(&device_interface_, MIP_FUNCTION_SELECTOR_WRITE, &data_stream_format_num_entries,data_stream_format_descriptors, data_stream_format_decimation) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();

			// Poll to verify
			ROS_INFO("Poll filter data to test stream");
			while(mip_3dm_cmd_poll_filter(&device_interface_, MIP_3DM_POLLING_ENABLE_ACK_NACK, data_stream_format_num_entries, data_stream_format_descriptors) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();

			// Save
			if (save_settings)
			{
				ROS_INFO("Saving Filter data settings");
				while(mip_3dm_cmd_filter_message_format(&device_interface_,
																	MIP_FUNCTION_SELECTOR_STORE_EEPROM,
																	0, NULL,NULL) != MIP_INTERFACE_OK) {}
				ros::Duration(dT).sleep();
			}


			///////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////
			// Dynamics Mode
			// Set dynamics mode
			///////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////
			/*
			ROS_INFO("Setting dynamics mode to %#04X",dynamics_mode);
			while(mip_filter_vehicle_dynamics_mode(&device_interface_,
																MIP_FUNCTION_SELECTOR_WRITE,
																&dynamics_mode) != MIP_INTERFACE_OK){}
			ros::Duration(dT).sleep();


			// Readback dynamics mode
			if (readback_settings)
			{
				// Read the settings back
				ROS_INFO("Reading back dynamics mode setting");
				while(mip_filter_vehicle_dynamics_mode(&device_interface_,
				                                       MIP_FUNCTION_SELECTOR_READ,
				                                       &readback_dynamics_mode)!= MIP_INTERFACE_OK){}
				ros::Duration(dT).sleep();
				if (dynamics_mode == readback_dynamics_mode)
					ROS_INFO("Success: Dynamics mode setting is: %#04X",readback_dynamics_mode);
				else
					ROS_ERROR("Failure: Dynamics mode set to be %#04X, but reads as %#04X",
					          dynamics_mode,readback_dynamics_mode);
			}

			if (save_settings)
			{
				ROS_INFO("Saving dynamics mode settings to EEPROM");
				while(mip_filter_vehicle_dynamics_mode(&device_interface_,
				                                       MIP_FUNCTION_SELECTOR_STORE_EEPROM,
				                                       NULL) != MIP_INTERFACE_OK)	{}
				ros::Duration(dT).sleep();
			}
			*/


			///////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////
			// Heading Source -- Select the source for aiding heading
			//							updates to the Kalman filter
			// 0 = No heading aids, 1 = Use the internal magnetometer, 3 = Use external heading message
			///////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////

			ROS_INFO("Set heading source to internal mag.");
			heading_source = 0x1;

			// Set heading source
			ROS_INFO("Setting heading source to %#04X",heading_source);
			while(mip_filter_heading_source(&device_interface_,
														MIP_FUNCTION_SELECTOR_WRITE,
														&heading_source) != MIP_INTERFACE_OK)	{}
			ros::Duration(dT).sleep();

			// Read heading source
			ROS_INFO("Read back heading source...");
			while(mip_filter_heading_source(&device_interface_,
			                                MIP_FUNCTION_SELECTOR_READ,
			                                &readback_headingsource)!= MIP_INTERFACE_OK) {}
			ROS_INFO("Heading source = %#04X",readback_headingsource);
			ros::Duration(dT).sleep();

			// Save heading source
			if (save_settings)
			{
				ROS_INFO("Saving heading source to EEPROM");
				while(mip_filter_heading_source(&device_interface_,
				                                MIP_FUNCTION_SELECTOR_STORE_EEPROM,
				                                NULL)!= MIP_INTERFACE_OK) {}
				ros::Duration(dT).sleep();
			}
		// end of Filter setup


		// I believe the auto-init pertains to the kalman filter for the -45
		// OR for the complementary filter for the -25  - need to test

		//////////////////////
		// Auto Initialization
		//////////////////////

		// Set auto-initialization based on ROS parameter
		ROS_INFO("Setting auto-initinitalization to: %#04X",auto_init);
		auto_init_u8 = auto_init; // convert bool to u8
		while(mip_filter_auto_initialization(&device_interface_,
		                                     MIP_FUNCTION_SELECTOR_WRITE,
		                                     &auto_init_u8) != MIP_INTERFACE_OK)
		{}
		ros::Duration(dT).sleep();

		// Read initialization settings
		if (readback_settings)
		{
			// Read the settings back
			ROS_INFO("Reading back auto-initialization value");
			while(mip_filter_auto_initialization(&device_interface_,
			                                     MIP_FUNCTION_SELECTOR_READ,
			                                     &readback_auto_init)!= MIP_INTERFACE_OK)
			{}
			ros::Duration(dT).sleep();
			if (auto_init == readback_auto_init)
				ROS_INFO("Success: Auto init. setting is: %#04X",readback_auto_init);
			else
				ROS_ERROR("Failure: Auto init. setting set to be %#04X, but reads as %#04X",
				          auto_init,readback_auto_init);
		}

		// Save initialization settings
		if (save_settings)
		{
			ROS_INFO("Saving auto init. settings to EEPROM");
			while(mip_filter_auto_initialization(&device_interface_,
			                                     MIP_FUNCTION_SELECTOR_STORE_EEPROM,
			                                     NULL) != MIP_INTERFACE_OK)
			{}
			ros::Duration(dT).sleep();
		}

		//////////////////////
		// Enable Data streams
		//////////////////////
		dT = 0.25;
			ROS_INFO("Enabling Filter (EKF Estimate) stream");
			enable = 0x01;
			while(mip_3dm_cmd_continuous_data_stream(&device_interface_, MIP_FUNCTION_SELECTOR_WRITE, MIP_3DM_INS_DATASTREAM, &enable) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();

		if (publish_cf_ | publish_mag_) {
			ROS_INFO("Enabling AHRS (Complementary Filter) stream");
			enable = 0x01;
			while(mip_3dm_cmd_continuous_data_stream(&device_interface_, MIP_FUNCTION_SELECTOR_WRITE, MIP_3DM_AHRS_DATASTREAM, &enable) != MIP_INTERFACE_OK) {}
			ros::Duration(dT).sleep();
		}


		ROS_INFO("End of device setup - starting streaming");
	}
	else
	{
		ROS_INFO("Skipping device setup and listing for existing streams");
	}                                                         // end of device_setup

	// Reset filter - should be for either the KF or CF
	ROS_INFO("Reset filter");
	while(mip_filter_reset_filter(&device_interface_) != MIP_INTERFACE_OK) {}
	ros::Duration(dT).sleep();

	// Loop
	// Determine loop rate as 2*(max update rate), but abs. max of 1kHz
	int max_rate = 1;
	max_rate = std::max(max_rate,ekf_rate_);
	if (publish_cf_ | publish_mag_)
	{
		max_rate = std::max(max_rate,cf_rate_);
	}


	int spin_rate = std::min(3*max_rate,1000);

	ROS_INFO("Setting spin rate to <%d>",spin_rate);
	ros::Rate r(spin_rate);                                                         // Rate in Hz
	while (ros::ok())
	{
		//Update the parser (this function reads the port and parses the bytes
		mip_interface_update(&device_interface_);
		ros::spinOnce();                                                                                                                 // take care of service requests.
		r.sleep();

		//ROS_INFO("Spinning");
	}                                                         // end loop

	// close serial port
	mip_sdk_port_close(device_interface_.port_handle);

}   // End of ::run()


bool Microstrain::reset_callback(std_srvs::Empty::Request &req,
                                 std_srvs::Empty::Response &resp)
{
	ROS_INFO("Reseting the filter");
	while(mip_filter_reset_filter(&device_interface_) != MIP_INTERFACE_OK) {}

	return true;
}

void Microstrain::filter_packet_callback(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type)
{
	//std::cout << "filter callback" << std::endl;
	mip_field_header *field_header;
	u8               *field_data;
	u16 field_offset = 0;

	// If we aren't publishing, then return


	//The packet callback can have several types, process them all
	switch(callback_type)
	{
	///
	//Handle valid packets
	///

	case MIP_INTERFACE_CALLBACK_VALID_PACKET:
	{
		filter_valid_packet_count_++;

		///
		//Loop through all of the data fields
		///

		while(mip_get_next_field(packet, &field_header, &field_data, &field_offset) == MIP_OK)
		{

			///
			// Decode the field
			///
			switch(field_header->descriptor)
			{
			//////////////////////////////////////////////////////////////
			// Accelerations
			//////////////////////////////////////////////////////////////
			case MIP_FILTER_DATA_COMPENSATED_ACCELERATION:
			{
				memcpy(&curr_filter_accel_, field_data, sizeof(mip_filter_compensated_acceleration));

				//For little-endian targets, byteswap the data field
				mip_filter_compensated_acceleration_byteswap(&curr_filter_accel_);

				// Stuff into ROS message - acceleration in m/s^2
				// Header
				ekf_imu_msg_.header.seq = filter_valid_packet_count_;
				ekf_imu_msg_.header.stamp = ros::Time::now();
				// ekf_imu_msg_.header.frame_id = imu_frame_id_;
				ekf_imu_msg_.header.frame_id = "imu_link";
				if (tf_ned_to_enu_)
				{
					ekf_imu_msg_.linear_acceleration.x = curr_filter_accel_.y;
					ekf_imu_msg_.linear_acceleration.y = curr_filter_accel_.x;
					ekf_imu_msg_.linear_acceleration.z = -curr_filter_accel_.z;
				}
				else
				{
					ekf_imu_msg_.linear_acceleration.x = curr_filter_accel_.x;
					ekf_imu_msg_.linear_acceleration.y = curr_filter_accel_.y;
					ekf_imu_msg_.linear_acceleration.z = curr_filter_accel_.z;
				}
				ekf_rpy_msg_.header.seq = filter_valid_packet_count_;
				ekf_rpy_msg_.header.stamp = ros::Time::now();
				ekf_rpy_msg_.header.frame_id = imu_frame_id_;

			} break;

			//////////////////////////////////////////////////////////////
			// Estimated Attitude, Euler Angles
			//////////////////////////////////////////////////////////////
			case MIP_FILTER_DATA_ATT_EULER_ANGLES:
			{
				memcpy(&curr_filter_angles_, field_data, sizeof(mip_filter_attitude_euler_angles));

				//For little-endian targets, byteswap the data field
				mip_filter_attitude_euler_angles_byteswap(&curr_filter_angles_);

				if (tf_ned_to_enu_)
				{
					ekf_rpy_msg_.vector.x = curr_filter_angles_.pitch;//Roll in ENU = Pitch in NED
					ekf_rpy_msg_.vector.y = curr_filter_angles_.roll; //Pitch in ENU = Roll in NED
					ekf_rpy_msg_.vector.z = -curr_filter_angles_.yaw; //Yaw in ENU = -Yaw in NED
				}
				else
				{
					ekf_rpy_msg_.vector.x = curr_filter_angles_.roll;
					ekf_rpy_msg_.vector.y = curr_filter_angles_.pitch;
					ekf_rpy_msg_.vector.z = curr_filter_angles_.yaw;
				}
			} break;

			//////////////////////////////////////////////////////////////
			// Quaternion
			//////////////////////////////////////////////////////////////
			case MIP_FILTER_DATA_ATT_QUATERNION:
			{
				memcpy(&curr_filter_quaternion_, field_data, sizeof(mip_filter_attitude_quaternion));

				//For little-endian targets, byteswap the data field
				mip_filter_attitude_quaternion_byteswap(&curr_filter_quaternion_);

				if (tf_ned_to_enu_)
				{
					ekf_imu_msg_.orientation.x = curr_filter_quaternion_.q[2];
					ekf_imu_msg_.orientation.y = curr_filter_quaternion_.q[1];
					ekf_imu_msg_.orientation.z = -1.0*curr_filter_quaternion_.q[3];
					ekf_imu_msg_.orientation.w = curr_filter_quaternion_.q[0];
				}
				else
				{
					ekf_imu_msg_.orientation.x = curr_filter_quaternion_.q[1];
					ekf_imu_msg_.orientation.y = curr_filter_quaternion_.q[2];
					ekf_imu_msg_.orientation.z = curr_filter_quaternion_.q[3];
					ekf_imu_msg_.orientation.w = curr_filter_quaternion_.q[0];
				}

			} break;

			//////////////////////////////////////////////////////////////
			// Angular Rates
			//////////////////////////////////////////////////////////////
			case MIP_FILTER_DATA_COMPENSATED_ANGULAR_RATE:
			{
				memcpy(&curr_filter_angular_rate_, field_data, sizeof(mip_filter_compensated_angular_rate));

				//For little-endian targets, byteswap the data field
				mip_filter_compensated_angular_rate_byteswap(&curr_filter_angular_rate_);

				if (tf_ned_to_enu_)
				{
					ekf_imu_msg_.angular_velocity.x = curr_filter_angular_rate_.y;
					ekf_imu_msg_.angular_velocity.y = curr_filter_angular_rate_.x;
					ekf_imu_msg_.angular_velocity.z = -curr_filter_angular_rate_.z;
				}
				else
				{
					ekf_imu_msg_.angular_velocity.x = curr_filter_angular_rate_.x;
					ekf_imu_msg_.angular_velocity.y = curr_filter_angular_rate_.y;
					ekf_imu_msg_.angular_velocity.z = curr_filter_angular_rate_.z;
				}

			} break;

			//////////////////////////////////////////////////////////////
			// Attitude Uncertainty (Euler)
			//////////////////////////////////////////////////////////////
			case MIP_FILTER_DATA_ATT_UNCERTAINTY_EULER:
			{
				memcpy(&curr_filter_att_uncertainty_, field_data, sizeof(mip_filter_euler_attitude_uncertainty));

				//For little-endian targets, byteswap the data field
				mip_filter_euler_attitude_uncertainty_byteswap(&curr_filter_att_uncertainty_);
				if (tf_ned_to_enu_)
				{
					ekf_imu_msg_.orientation_covariance[0] = curr_filter_att_uncertainty_.pitch*curr_filter_att_uncertainty_.pitch;
					ekf_imu_msg_.orientation_covariance[4] = curr_filter_att_uncertainty_.roll*curr_filter_att_uncertainty_.roll;
					ekf_imu_msg_.orientation_covariance[8] = curr_filter_att_uncertainty_.yaw*curr_filter_att_uncertainty_.yaw;
				}
				else
				{
					ekf_imu_msg_.orientation_covariance[0] = curr_filter_att_uncertainty_.roll*curr_filter_att_uncertainty_.roll;
					ekf_imu_msg_.orientation_covariance[4] = curr_filter_att_uncertainty_.pitch*curr_filter_att_uncertainty_.pitch;
					ekf_imu_msg_.orientation_covariance[8] = curr_filter_att_uncertainty_.yaw*curr_filter_att_uncertainty_.yaw;
				}
			} break;


			//////////////////////////////////////////////////////////////
			// Attitude Uncertainty (Quaternion)
			//////////////////////////////////////////////////////////////
			case MIP_FILTER_DATA_ATT_UNCERTAINTY_QUATERNION:
			{
				memcpy(&curr_filter_quat_uncertainty_, field_data, sizeof(mip_filter_quaternion_attitude_uncertainty));

				//For little-endian targets, byteswap the data field
				mip_filter_quaternion_attitude_uncertainty_byteswap(&curr_filter_quat_uncertainty_);

				//ekf_imu_msg_.orientation_covariance[1] = curr_filter_quat_uncertainty_.q2*curr_filter_quat_uncertainty_.q2;
				//ekf_imu_msg_.orientation_covariance[5] = curr_filter_quat_uncertainty_.q1*curr_filter_quat_uncertainty_.q1;
				//ekf_imu_msg_.orientation_covariance[7] = curr_filter_quat_uncertainty_.q3*curr_filter_quat_uncertainty_.q3;

			} break;


			// Filter Status
			case MIP_FILTER_DATA_FILTER_STATUS:
			{
				memcpy(&curr_filter_status_, field_data, sizeof(mip_filter_status));

				//For little-endian targets, byteswap the data field
				mip_filter_status_byteswap(&curr_filter_status_);
				status_msg_.data.clear();
				//ROS_DEBUG_THROTTLE(1.0,"Filter Status: %#06X, Dyn. Mode: %#06X, Filter State: %#06X",
				//	       curr_filter_status_.filter_state,
				//	       curr_filter_status_.dynamics_mode,
				//	       curr_filter_status_.status_flags);
				status_msg_.data.push_back(curr_filter_status_.filter_state);
				status_msg_.data.push_back(curr_filter_status_.dynamics_mode);
				status_msg_.data.push_back(curr_filter_status_.status_flags);
				status_pub_.publish(status_msg_);

			} break;

			default: break;
			}
		}
		// Publish
		ekf_imu_msg_.angular_velocity_covariance[0]=0.01;
		ekf_imu_msg_.angular_velocity_covariance[4]=0.01;
		ekf_imu_msg_.angular_velocity_covariance[8]=0.01;

		ekf_imu_msg_.linear_acceleration_covariance[0]=0.01;
		ekf_imu_msg_.linear_acceleration_covariance[4]=0.01;
		ekf_imu_msg_.linear_acceleration_covariance[8]=0.01;

		// ekf_imu_msg_.orientation_covariance[0]=0.01;
		// ekf_imu_msg_.orientation_covariance[4]=0.01;
		// ekf_imu_msg_.orientation_covariance[8]=0.01;

		// ekf_rpy_msg_.angular_velocity_covariance[0]=0.01;
		// ekf_rpy_msg_.angular_velocity_covariance[4]=0.01;
		// ekf_rpy_msg_.angular_velocity_covariance[8]=0.01;

		// ekf_rpy_msg_.linear_acceleration_covariance[0]=0.01;
		// ekf_rpy_msg_.linear_acceleration_covariance[4]=0.01;
		// ekf_rpy_msg_.linear_acceleration_covariance[8]=0.01;
		

		// ekf_rpy_msg_.orientation_covariance[0]=0.01;
		// ekf_rpy_msg_.orientation_covariance[4]=0.01;
		// ekf_rpy_msg_.orientation_covariance[8]=0.01;


		ekf_pub_.publish(ekf_imu_msg_);
		if(publish_rpy_)
			ekf_rpy_pub_.publish(ekf_rpy_msg_);

	} break;


	///
	//Handle checksum error packets
	///

	case MIP_INTERFACE_CALLBACK_CHECKSUM_ERROR:
	{
		filter_checksum_error_packet_count_++;
	} break;

	///
	//Handle timeout packets
	///

	case MIP_INTERFACE_CALLBACK_TIMEOUT:
	{
		filter_timeout_packet_count_++;
	} break;
	default: break;
	}

	print_packet_stats();
}   // filter_packet_callback


////////////////////////////////////////////////////////////////////////////////
//
// AHRS Packet Callback
//
////////////////////////////////////////////////////////////////////////////////

void Microstrain::ahrs_packet_callback(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type)
{
	mip_field_header *field_header;
	u8               *field_data;
	u16 field_offset = 0;
	// If we aren't publishing, then return
	if (!publish_cf_ && !publish_mag_)
		return;
	//The packet callback can have several types, process them all
	switch(callback_type)
	{
	///
	//Handle valid packets
	///

	case MIP_INTERFACE_CALLBACK_VALID_PACKET:
	{
		ahrs_valid_packet_count_++;

		///
		//Loop through all of the data fields
		///

		while(mip_get_next_field(packet, &field_header, &field_data, &field_offset) == MIP_OK)
		{

			///
			// Decode the field
			///

			switch(field_header->descriptor)
			{
			///
			// Scaled Accelerometer
			///

			case MIP_AHRS_DATA_ACCEL_SCALED:
			{
				memcpy(&curr_ahrs_accel_, field_data, sizeof(mip_ahrs_scaled_accel));

				//For little-endian targets, byteswap the data field
				mip_ahrs_scaled_accel_byteswap(&curr_ahrs_accel_);

				// Stuff into ROS message - acceleration in m/s^2
				// Header
				cf_imu_msg_.header.seq = ahrs_valid_packet_count_;
				cf_imu_msg_.header.stamp = ros::Time::now();
				cf_imu_msg_.header.frame_id = imu_frame_id_;
				if (tf_ned_to_enu_)
				{
					cf_imu_msg_.linear_acceleration.x =  9.81*curr_ahrs_accel_.scaled_accel[1];                                                                                                                                                                                                                                //SJP Modified from 9.81*curr_ahrs_accel_.scaled_accel[0];
					cf_imu_msg_.linear_acceleration.y = 9.81*curr_ahrs_accel_.scaled_accel[0];                                                                                                                                                                                                                                 //SJP Modified from 9.81*curr_ahrs_accel_.scaled_accel[1];
					cf_imu_msg_.linear_acceleration.z = -9.81*curr_ahrs_accel_.scaled_accel[2];                                                                                                                                                                                                                                 //SJP Modified from 9.81*curr_ahrs_accel_.scaled_accel[2];
				}
				else
				{
					cf_imu_msg_.linear_acceleration.x =  9.81*curr_ahrs_accel_.scaled_accel[0];                                                                                                                                                                                                                                //SJP Modified from 9.81*curr_ahrs_accel_.scaled_accel[0];
					cf_imu_msg_.linear_acceleration.y = 9.81*curr_ahrs_accel_.scaled_accel[1];                                                                                                                                                                                                                                 //SJP Modified from 9.81*curr_ahrs_accel_.scaled_accel[1];
					cf_imu_msg_.linear_acceleration.z = 9.81*curr_ahrs_accel_.scaled_accel[2];
				}
				mag_msg_.header.seq = ahrs_valid_packet_count_;                                                                                                                                                                                                                                 //SJP Added
				mag_msg_.header.stamp = ros::Time::now();                                                                                                                                                                                                                                 //SJP Added
				mag_msg_.header.frame_id = imu_frame_id_;
				cf_rpy_msg_.header.seq = ahrs_valid_packet_count_;                                                                                                                                                                                                                                 //SJP Added
				cf_rpy_msg_.header.stamp = ros::Time::now();                                                                                                                                                                                                                                 //SJP Added
				cf_rpy_msg_.header.frame_id = imu_frame_id_;                                                                                                                                                                                                                                 //SJP Added

			} break;

			///
			// Scaled Gyro
			///

			case MIP_AHRS_DATA_GYRO_SCALED:
			{
				memcpy(&curr_ahrs_gyro_, field_data, sizeof(mip_ahrs_scaled_gyro));

				//For little-endian targets, byteswap the data field
				mip_ahrs_scaled_gyro_byteswap(&curr_ahrs_gyro_);
			if (tf_ned_to_enu_)
			{
				cf_imu_msg_.angular_velocity.x = curr_ahrs_gyro_.scaled_gyro[1];                                                                                                                                                                                                                                //SJP Modified from curr_ahrs_gyro_.scaled_gyro[0];
				cf_imu_msg_.angular_velocity.y = curr_ahrs_gyro_.scaled_gyro[0];                                                                                                                                                                                                                                //SJP Modified from curr_ahrs_gyro_.scaled_gyro[1];
				cf_imu_msg_.angular_velocity.z = -curr_ahrs_gyro_.scaled_gyro[2];                                                                                                                                                                                                                                //SJP Modified from curr_ahrs_gyro_.scaled_gyro[2];
			}
			else
			{
				cf_imu_msg_.angular_velocity.x = curr_ahrs_gyro_.scaled_gyro[0];                                                                                                                                                                                                                                //SJP Modified from curr_ahrs_gyro_.scaled_gyro[0];
				cf_imu_msg_.angular_velocity.y = curr_ahrs_gyro_.scaled_gyro[1];                                                                                                                                                                                                                                //SJP Modified from curr_ahrs_gyro_.scaled_gyro[1];
				cf_imu_msg_.angular_velocity.z = curr_ahrs_gyro_.scaled_gyro[2];
			}
			} break;

			///
			// Scaled Magnetometer
			///

			case MIP_AHRS_DATA_MAG_SCALED:
			{
				memcpy(&curr_ahrs_mag_, field_data, sizeof(mip_ahrs_scaled_mag));

				//For little-endian targets, byteswap the data field
				mip_ahrs_scaled_mag_byteswap(&curr_ahrs_mag_);
			if (tf_ned_to_enu_)
			{
				mag_msg_.magnetic_field.x = curr_ahrs_mag_.scaled_mag[1];                                                                                                                                                                                                                                 //SJP Added (ENU x = NED y)
				mag_msg_.magnetic_field.y = curr_ahrs_mag_.scaled_mag[0];                                                                                                                                                                                                                                 //SJP Added (ENU y = NED x)
				mag_msg_.magnetic_field.z = -curr_ahrs_mag_.scaled_mag[2];                                                                                                                                                                                                                                 //SJP Added (ENU z = -NED z)
			}
			else
			{
				mag_msg_.magnetic_field.x = curr_ahrs_mag_.scaled_mag[0];                                                                                                                                                                                                                                 //SJP Added (ENU x = NED y)
				mag_msg_.magnetic_field.y = curr_ahrs_mag_.scaled_mag[1];                                                                                                                                                                                                                                 //SJP Added (ENU y = NED x)
				mag_msg_.magnetic_field.z = curr_ahrs_mag_.scaled_mag[2];
			}
			} break;

			// Quaternion
			case MIP_AHRS_DATA_QUATERNION:
			{
				memcpy(&curr_ahrs_quaternion_, field_data, sizeof(mip_ahrs_quaternion));

				//For little-endian targets, byteswap the data field
				mip_ahrs_quaternion_byteswap(&curr_ahrs_quaternion_);
			if (tf_ned_to_enu_)
			{
				cf_imu_msg_.orientation.x = curr_ahrs_quaternion_.q[2];
				cf_imu_msg_.orientation.y = curr_ahrs_quaternion_.q[1];
				cf_imu_msg_.orientation.z = -curr_ahrs_quaternion_.q[3];
				cf_imu_msg_.orientation.w = curr_ahrs_quaternion_.q[0];
			}
			else
			{
				cf_imu_msg_.orientation.x = curr_ahrs_quaternion_.q[1];
				cf_imu_msg_.orientation.y = curr_ahrs_quaternion_.q[2];
				cf_imu_msg_.orientation.z = curr_ahrs_quaternion_.q[3];
				cf_imu_msg_.orientation.w = curr_ahrs_quaternion_.q[0];
			}
			} break;


			case MIP_AHRS_DATA_EULER_ANGLES:
			{
				memcpy(&curr_ahrs_euler_angles_, field_data, sizeof(mip_ahrs_euler_angles));

				//For little-endian targets, byteswap the data field
				mip_ahrs_euler_angles_byteswap(&curr_ahrs_euler_angles_);
			if (tf_ned_to_enu_)
			{
				cf_rpy_msg_.vector.x = curr_ahrs_euler_angles_.pitch;                                                                                                                                                                                                                                //Roll in ENU = Pitch in NED
				cf_rpy_msg_.vector.y = curr_ahrs_euler_angles_.roll;                                                                                                                                                                                                                                //Pitch in ENU = Roll in NED
				cf_rpy_msg_.vector.z = -curr_ahrs_euler_angles_.yaw;                                                                                                                                                                                                                                 //Yaw in ENU = -Yaw in NED
			}
			else
			{
				cf_rpy_msg_.vector.x = curr_ahrs_euler_angles_.roll;                                                                                                                                                                                                                                //Roll in ENU = Pitch in NED
				cf_rpy_msg_.vector.y = curr_ahrs_euler_angles_.pitch;                                                                                                                                                                                                                                //Pitch in ENU = Roll in NED
				cf_rpy_msg_.vector.z = curr_ahrs_euler_angles_.yaw;
			}
			} break;

			default: break;
			}
		}


		cf_imu_msg_.angular_velocity_covariance[0]=0.01;
		cf_imu_msg_.angular_velocity_covariance[4]=0.01;
		cf_imu_msg_.angular_velocity_covariance[8]=0.01;

		cf_imu_msg_.linear_acceleration_covariance[0]=0.01;
		cf_imu_msg_.linear_acceleration_covariance[4]=0.01;
		cf_imu_msg_.linear_acceleration_covariance[8]=0.01;

		cf_imu_msg_.orientation_covariance[0]=0.01;
		cf_imu_msg_.orientation_covariance[4]=0.01;
		cf_imu_msg_.orientation_covariance[8]=0.01;

		

		// Publish
		if(publish_cf_)
		{	
			cf_pub_.publish(cf_imu_msg_);
			if(publish_rpy_)
				cf_rpy_pub_.publish(cf_rpy_msg_);
		}
		if(publish_mag_)
			mag_pub_.publish(mag_msg_);


	} break;

	///
	//Handle checksum error packets
	///

	case MIP_INTERFACE_CALLBACK_CHECKSUM_ERROR:
	{
		ahrs_checksum_error_packet_count_++;
	} break;

	///
	//Handle timeout packets
	///

	case MIP_INTERFACE_CALLBACK_TIMEOUT:
	{
		ahrs_timeout_packet_count_++;
	} break;
	default: break;
	}

	print_packet_stats();
}   // ahrs_packet_callback


void Microstrain::print_packet_stats()
{
	ROS_DEBUG_THROTTLE(1.0,"%u FILTER (%u errors)    %u AHRS (%u errors)", filter_valid_packet_count_,  filter_timeout_packet_count_ + filter_checksum_error_packet_count_,
	                   ahrs_valid_packet_count_, ahrs_timeout_packet_count_ + ahrs_checksum_error_packet_count_);
}   // print_packet_stats


// Wrapper callbacks
void filter_packet_callback_wrapper(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type)
{
	Microstrain* ustrain = (Microstrain*) user_ptr;
	ustrain->filter_packet_callback(user_ptr,packet,packet_size,callback_type);
}

void ahrs_packet_callback_wrapper(void *user_ptr, u8 *packet, u16 packet_size, u8 callback_type)
{
	Microstrain* ustrain = (Microstrain*) user_ptr;
	ustrain->ahrs_packet_callback(user_ptr,packet,packet_size,callback_type);
}
// Wrapper callbacks



} // Microstrain namespace
