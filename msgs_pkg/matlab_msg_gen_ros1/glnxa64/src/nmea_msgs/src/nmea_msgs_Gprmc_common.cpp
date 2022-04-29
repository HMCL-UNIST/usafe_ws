// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for nmea_msgs/Gprmc
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
#include "nmea_msgs/Gprmc.h"
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
namespace nmea_msgs {
namespace matlabhelper {
namespace Gprmc {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const nmea_msgs::Gprmc::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
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
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const nmea_msgs::Gprmc::_header_type& val) {
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
  NMEA_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<nmea_msgs::Gprmc>& msg, const matlab::data::StructArray arr) {
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
        //message_id
        const matlab::data::CharArray message_id_arr = arr[0]["message_id"];
        msg->message_id = message_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'message_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'message_id' is wrong type; expected a string.");
    }
    try {
        //utc_seconds
        const matlab::data::TypedArray<double> utc_seconds_arr = arr[0]["utc_seconds"];
        msg->utc_seconds = utc_seconds_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'utc_seconds' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'utc_seconds' is wrong type; expected a double.");
    }
    try {
        //position_status
        const matlab::data::CharArray position_status_arr = arr[0]["position_status"];
        msg->position_status = position_status_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position_status' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'position_status' is wrong type; expected a string.");
    }
    try {
        //lat
        const matlab::data::TypedArray<double> lat_arr = arr[0]["lat"];
        msg->lat = lat_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lat' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lat' is wrong type; expected a double.");
    }
    try {
        //lon
        const matlab::data::TypedArray<double> lon_arr = arr[0]["lon"];
        msg->lon = lon_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lon' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lon' is wrong type; expected a double.");
    }
    try {
        //lat_dir
        const matlab::data::CharArray lat_dir_arr = arr[0]["lat_dir"];
        msg->lat_dir = lat_dir_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lat_dir' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lat_dir' is wrong type; expected a string.");
    }
    try {
        //lon_dir
        const matlab::data::CharArray lon_dir_arr = arr[0]["lon_dir"];
        msg->lon_dir = lon_dir_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lon_dir' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lon_dir' is wrong type; expected a string.");
    }
    try {
        //speed
        const matlab::data::TypedArray<float> speed_arr = arr[0]["speed"];
        msg->speed = speed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'speed' is wrong type; expected a single.");
    }
    try {
        //track
        const matlab::data::TypedArray<float> track_arr = arr[0]["track"];
        msg->track = track_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'track' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'track' is wrong type; expected a single.");
    }
    try {
        //date
        const matlab::data::CharArray date_arr = arr[0]["date"];
        msg->date = date_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'date' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'date' is wrong type; expected a string.");
    }
    try {
        //mag_var
        const matlab::data::TypedArray<float> mag_var_arr = arr[0]["mag_var"];
        msg->mag_var = mag_var_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mag_var' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'mag_var' is wrong type; expected a single.");
    }
    try {
        //mag_var_direction
        const matlab::data::CharArray mag_var_direction_arr = arr[0]["mag_var_direction"];
        msg->mag_var_direction = mag_var_direction_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mag_var_direction' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'mag_var_direction' is wrong type; expected a string.");
    }
    try {
        //mode_indicator
        const matlab::data::CharArray mode_indicator_arr = arr[0]["mode_indicator"];
        msg->mode_indicator = mode_indicator_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mode_indicator' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'mode_indicator' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  NMEA_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const nmea_msgs::Gprmc>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","message_id","utc_seconds","position_status","lat","lon","lat_dir","lon_dir","speed","track","date","mag_var","mag_var_direction","mode_indicator"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // message_id
    outArray[0]["message_id"] = factory.createCharArray(msg->message_id);
    // utc_seconds
    outArray[0]["utc_seconds"] = factory.createScalar(msg->utc_seconds);
    // position_status
    outArray[0]["position_status"] = factory.createCharArray(msg->position_status);
    // lat
    outArray[0]["lat"] = factory.createScalar(msg->lat);
    // lon
    outArray[0]["lon"] = factory.createScalar(msg->lon);
    // lat_dir
    outArray[0]["lat_dir"] = factory.createCharArray(msg->lat_dir);
    // lon_dir
    outArray[0]["lon_dir"] = factory.createCharArray(msg->lon_dir);
    // speed
    outArray[0]["speed"] = factory.createScalar(msg->speed);
    // track
    outArray[0]["track"] = factory.createScalar(msg->track);
    // date
    outArray[0]["date"] = factory.createCharArray(msg->date);
    // mag_var
    outArray[0]["mag_var"] = factory.createScalar(msg->mag_var);
    // mag_var_direction
    outArray[0]["mag_var_direction"] = factory.createCharArray(msg->mag_var_direction);
    // mode_indicator
    outArray[0]["mode_indicator"] = factory.createCharArray(msg->mode_indicator);
    return std::move(outArray);
  }
} //namespace Gprmc
} //namespace matlabhelper
} //namespace nmea_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1