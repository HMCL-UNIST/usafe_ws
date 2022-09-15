// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for ackermann_msgs/AckermannDriveStamped
#include "boost/date_time.hpp"
#include "boost/shared_array.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4265)
#pragma warning(disable : 4458)
#pragma warning(disable : 4100)
#pragma warning(disable : 4127)
#pragma warning(disable : 4267)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#endif //_MSC_VER
#include "ros/ros.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include "visibility_control.h"
#ifndef FOUNDATION_MATLABDATA_API
#include "MDArray.hpp"
#include "StructArray.hpp"
#include "TypedArrayRef.hpp"
#include "Struct.hpp"
#include "ArrayFactory.hpp"
#include "StructRef.hpp"
#include "Reference.hpp"
#endif
#ifndef FOUNDATION_MATLABDATA_API
typedef matlab::data::Array MDArray_T;
typedef matlab::data::ArrayFactory MDFactory_T;
#else
typedef foundation::matlabdata::Array MDArray_T;
typedef foundation::matlabdata::standalone::ClientArrayFactory MDFactory_T;
#endif
namespace ackermann_msgs {
namespace matlabhelper {
namespace AckermannDriveStamped {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const ackermann_msgs::AckermannDriveStamped::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_ackermann_msgs_AckermannDrive(ackermann_msgs::AckermannDrive& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ackermann_msgs_AckermannDrive(MDFactory_T& factory, const ackermann_msgs::AckermannDriveStamped::_drive_type& val);
  //----------------------------------------------------------------------------
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr) {
    // _std_msgs_Header.seq
    try {
        const matlab::data::TypedArray<uint32_t> _headerseq_arr = arr[0]["seq"];
        val.seq = _headerseq_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'seq' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'seq' is wrong type; expected a uint32.");
    }
    // _std_msgs_Header.stamp
    try {
        const matlab::data::StructArray _headerstamp_arr = arr[0]["stamp"];
        copy_from_arr_ros_Time(val.stamp,_headerstamp_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stamp' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stamp' is wrong type; expected a struct.");
    }
    // _std_msgs_Header.frame_id
    try {
        const matlab::data::CharArray _headerframe_id_arr = arr[0]["frame_id"];
        val.frame_id = _headerframe_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'frame_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'frame_id' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const ackermann_msgs::AckermannDriveStamped::_header_type& val) {
    auto _headeroutArray = factory.createStructArray({1,1},{"seq","stamp","frame_id"});
    // _std_msgs_Header.seq
    _headeroutArray[0]["seq"] = factory.createScalar(val.seq);
    // _std_msgs_Header.stamp
    _headeroutArray[0]["stamp"] = get_arr_ros_Time(factory, val.stamp);
    // _std_msgs_Header.frame_id
    _headeroutArray[0]["frame_id"] = factory.createCharArray(val.frame_id);
    return std::move(_headeroutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr) {
    // _ros_Time.sec
    try {
        const matlab::data::TypedArray<uint32_t> _header_stampsec_arr = arr[0]["sec"];
        val.sec = _header_stampsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'sec' is wrong type; expected a uint32.");
    }
    // _ros_Time.nsec
    try {
        const matlab::data::TypedArray<uint32_t> _header_stampnsec_arr = arr[0]["nsec"];
        val.nsec = _header_stampnsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'nsec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'nsec' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val) {
    auto _header_stampoutArray = factory.createStructArray({1,1},{"sec","nsec"});
    // _ros_Time.sec
    _header_stampoutArray[0]["sec"] = factory.createScalar(val.sec);
    // _ros_Time.nsec
    _header_stampoutArray[0]["nsec"] = factory.createScalar(val.nsec);
    return std::move(_header_stampoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_ackermann_msgs_AckermannDrive(ackermann_msgs::AckermannDrive& val, const matlab::data::StructArray& arr) {
    // _ackermann_msgs_AckermannDrive.steering_angle
    try {
        const matlab::data::TypedArray<float> _drivesteering_angle_arr = arr[0]["steering_angle"];
        val.steering_angle = _drivesteering_angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_angle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_angle' is wrong type; expected a single.");
    }
    // _ackermann_msgs_AckermannDrive.steering_angle_velocity
    try {
        const matlab::data::TypedArray<float> _drivesteering_angle_velocity_arr = arr[0]["steering_angle_velocity"];
        val.steering_angle_velocity = _drivesteering_angle_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_angle_velocity' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_angle_velocity' is wrong type; expected a single.");
    }
    // _ackermann_msgs_AckermannDrive.speed
    try {
        const matlab::data::TypedArray<float> _drivespeed_arr = arr[0]["speed"];
        val.speed = _drivespeed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'speed' is wrong type; expected a single.");
    }
    // _ackermann_msgs_AckermannDrive.acceleration
    try {
        const matlab::data::TypedArray<float> _driveacceleration_arr = arr[0]["acceleration"];
        val.acceleration = _driveacceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acceleration' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'acceleration' is wrong type; expected a single.");
    }
    // _ackermann_msgs_AckermannDrive.jerk
    try {
        const matlab::data::TypedArray<float> _drivejerk_arr = arr[0]["jerk"];
        val.jerk = _drivejerk_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'jerk' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'jerk' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_ackermann_msgs_AckermannDrive(MDFactory_T& factory, const ackermann_msgs::AckermannDriveStamped::_drive_type& val) {
    auto _driveoutArray = factory.createStructArray({1,1},{"steering_angle","steering_angle_velocity","speed","acceleration","jerk"});
    // _ackermann_msgs_AckermannDrive.steering_angle
    _driveoutArray[0]["steering_angle"] = factory.createScalar(val.steering_angle);
    // _ackermann_msgs_AckermannDrive.steering_angle_velocity
    _driveoutArray[0]["steering_angle_velocity"] = factory.createScalar(val.steering_angle_velocity);
    // _ackermann_msgs_AckermannDrive.speed
    _driveoutArray[0]["speed"] = factory.createScalar(val.speed);
    // _ackermann_msgs_AckermannDrive.acceleration
    _driveoutArray[0]["acceleration"] = factory.createScalar(val.acceleration);
    // _ackermann_msgs_AckermannDrive.jerk
    _driveoutArray[0]["jerk"] = factory.createScalar(val.jerk);
    return std::move(_driveoutArray);
  }
  //----------------------------------------------------------------------------
  ACKERMANN_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<ackermann_msgs::AckermannDriveStamped>& msg, const matlab::data::StructArray arr) {
    try {
        //header
        const matlab::data::StructArray header_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(msg->header,header_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    try {
        //drive
        const matlab::data::StructArray drive_arr = arr[0]["drive"];
        copy_from_arr_ackermann_msgs_AckermannDrive(msg->drive,drive_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'drive' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'drive' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  ACKERMANN_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const ackermann_msgs::AckermannDriveStamped>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","drive"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // drive
    outArray[0]["drive"] = get_arr_ackermann_msgs_AckermannDrive(factory, msg->drive);
    return std::move(outArray);
  }
} //namespace AckermannDriveStamped
} //namespace matlabhelper
} //namespace ackermann_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1