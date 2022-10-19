// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for nmea_msgs/Gpgga
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
#include "nmea_msgs/Gpgga.h"
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
namespace Gpgga {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const nmea_msgs::Gpgga::_header_type& val);
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
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const nmea_msgs::Gpgga::_header_type& val) {
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
  NMEA_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<nmea_msgs::Gpgga>& msg, const matlab::data::StructArray arr) {
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
        //gps_qual
        const matlab::data::TypedArray<uint32_t> gps_qual_arr = arr[0]["gps_qual"];
        msg->gps_qual = gps_qual_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gps_qual' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gps_qual' is wrong type; expected a uint32.");
    }
    try {
        //num_sats
        const matlab::data::TypedArray<uint32_t> num_sats_arr = arr[0]["num_sats"];
        msg->num_sats = num_sats_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'num_sats' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'num_sats' is wrong type; expected a uint32.");
    }
    try {
        //hdop
        const matlab::data::TypedArray<float> hdop_arr = arr[0]["hdop"];
        msg->hdop = hdop_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'hdop' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'hdop' is wrong type; expected a single.");
    }
    try {
        //alt
        const matlab::data::TypedArray<float> alt_arr = arr[0]["alt"];
        msg->alt = alt_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'alt' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'alt' is wrong type; expected a single.");
    }
    try {
        //altitude_units
        const matlab::data::CharArray altitude_units_arr = arr[0]["altitude_units"];
        msg->altitude_units = altitude_units_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'altitude_units' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'altitude_units' is wrong type; expected a string.");
    }
    try {
        //undulation
        const matlab::data::TypedArray<float> undulation_arr = arr[0]["undulation"];
        msg->undulation = undulation_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'undulation' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'undulation' is wrong type; expected a single.");
    }
    try {
        //undulation_units
        const matlab::data::CharArray undulation_units_arr = arr[0]["undulation_units"];
        msg->undulation_units = undulation_units_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'undulation_units' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'undulation_units' is wrong type; expected a string.");
    }
    try {
        //diff_age
        const matlab::data::TypedArray<uint32_t> diff_age_arr = arr[0]["diff_age"];
        msg->diff_age = diff_age_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'diff_age' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'diff_age' is wrong type; expected a uint32.");
    }
    try {
        //station_id
        const matlab::data::CharArray station_id_arr = arr[0]["station_id"];
        msg->station_id = station_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'station_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'station_id' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  NMEA_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const nmea_msgs::Gpgga>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","message_id","utc_seconds","lat","lon","lat_dir","lon_dir","gps_qual","num_sats","hdop","alt","altitude_units","undulation","undulation_units","diff_age","station_id"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // message_id
    outArray[0]["message_id"] = factory.createCharArray(msg->message_id);
    // utc_seconds
    outArray[0]["utc_seconds"] = factory.createScalar(msg->utc_seconds);
    // lat
    outArray[0]["lat"] = factory.createScalar(msg->lat);
    // lon
    outArray[0]["lon"] = factory.createScalar(msg->lon);
    // lat_dir
    outArray[0]["lat_dir"] = factory.createCharArray(msg->lat_dir);
    // lon_dir
    outArray[0]["lon_dir"] = factory.createCharArray(msg->lon_dir);
    // gps_qual
    outArray[0]["gps_qual"] = factory.createScalar(msg->gps_qual);
    // num_sats
    outArray[0]["num_sats"] = factory.createScalar(msg->num_sats);
    // hdop
    outArray[0]["hdop"] = factory.createScalar(msg->hdop);
    // alt
    outArray[0]["alt"] = factory.createScalar(msg->alt);
    // altitude_units
    outArray[0]["altitude_units"] = factory.createCharArray(msg->altitude_units);
    // undulation
    outArray[0]["undulation"] = factory.createScalar(msg->undulation);
    // undulation_units
    outArray[0]["undulation_units"] = factory.createCharArray(msg->undulation_units);
    // diff_age
    outArray[0]["diff_age"] = factory.createScalar(msg->diff_age);
    // station_id
    outArray[0]["station_id"] = factory.createCharArray(msg->station_id);
    return std::move(outArray);
  }
} //namespace Gpgga
} //namespace matlabhelper
} //namespace nmea_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1