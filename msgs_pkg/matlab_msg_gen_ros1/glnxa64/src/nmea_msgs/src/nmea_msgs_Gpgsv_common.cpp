// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for nmea_msgs/Gpgsv
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
#include "nmea_msgs/Gpgsv.h"
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
namespace Gpgsv {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const nmea_msgs::Gpgsv::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_nmea_msgs_GpgsvSatellite_var_arr(nmea_msgs::GpgsvSatellite& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_nmea_msgs_GpgsvSatellite_var_arr(MDFactory_T& factory, const nmea_msgs::Gpgsv::_satellites_type& val);
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
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const nmea_msgs::Gpgsv::_header_type& val) {
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
  void copy_from_arr_nmea_msgs_GpgsvSatellite_var_arr(nmea_msgs::GpgsvSatellite& val, const matlab::data::Struct& arr) {
    // _nmea_msgs_GpgsvSatellite_var_arr.prn
    try {
        const matlab::data::TypedArray<uint8_t> _satellitesprn_arr = arr["prn"];
        val.prn = _satellitesprn_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'prn' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'prn' is wrong type; expected a uint8.");
    }
    // _nmea_msgs_GpgsvSatellite_var_arr.elevation
    try {
        const matlab::data::TypedArray<uint8_t> _satelliteselevation_arr = arr["elevation"];
        val.elevation = _satelliteselevation_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'elevation' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'elevation' is wrong type; expected a uint8.");
    }
    // _nmea_msgs_GpgsvSatellite_var_arr.azimuth
    try {
        const matlab::data::TypedArray<uint16_t> _satellitesazimuth_arr = arr["azimuth"];
        val.azimuth = _satellitesazimuth_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'azimuth' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'azimuth' is wrong type; expected a uint16.");
    }
    // _nmea_msgs_GpgsvSatellite_var_arr.snr
    try {
        const matlab::data::TypedArray<int8_t> _satellitessnr_arr = arr["snr"];
        val.snr = _satellitessnr_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'snr' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'snr' is wrong type; expected a int8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_nmea_msgs_GpgsvSatellite_var_arr(MDFactory_T& factory, const nmea_msgs::Gpgsv::_satellites_type& val) {
    auto _satellitesoutArray = factory.createStructArray({1,val.size()},{"prn","elevation","azimuth","snr"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _nmea_msgs_GpgsvSatellite_var_arr.prn
    	_satellitesoutArray[idx]["prn"] = factory.createScalar(val[idx].prn);
    // _nmea_msgs_GpgsvSatellite_var_arr.elevation
    	_satellitesoutArray[idx]["elevation"] = factory.createScalar(val[idx].elevation);
    // _nmea_msgs_GpgsvSatellite_var_arr.azimuth
    	_satellitesoutArray[idx]["azimuth"] = factory.createScalar(val[idx].azimuth);
    // _nmea_msgs_GpgsvSatellite_var_arr.snr
    	_satellitesoutArray[idx]["snr"] = factory.createScalar(val[idx].snr);
    }
    return std::move(_satellitesoutArray);
  }
  //----------------------------------------------------------------------------
  NMEA_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<nmea_msgs::Gpgsv>& msg, const matlab::data::StructArray arr) {
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
        //n_msgs
        const matlab::data::TypedArray<uint8_t> n_msgs_arr = arr[0]["n_msgs"];
        msg->n_msgs = n_msgs_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'n_msgs' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'n_msgs' is wrong type; expected a uint8.");
    }
    try {
        //msg_number
        const matlab::data::TypedArray<uint8_t> msg_number_arr = arr[0]["msg_number"];
        msg->msg_number = msg_number_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'msg_number' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'msg_number' is wrong type; expected a uint8.");
    }
    try {
        //n_satellites
        const matlab::data::TypedArray<uint8_t> n_satellites_arr = arr[0]["n_satellites"];
        msg->n_satellites = n_satellites_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'n_satellites' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'n_satellites' is wrong type; expected a uint8.");
    }
    try {
        //satellites
        const matlab::data::StructArray satellites_arr = arr[0]["satellites"];
        for (auto _satellitesarr : satellites_arr) {
        	nmea_msgs::GpgsvSatellite _val;
        	copy_from_arr_nmea_msgs_GpgsvSatellite_var_arr(_val,_satellitesarr);
        	msg->satellites.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'satellites' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'satellites' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  NMEA_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const nmea_msgs::Gpgsv>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","message_id","n_msgs","msg_number","n_satellites","satellites"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // message_id
    outArray[0]["message_id"] = factory.createCharArray(msg->message_id);
    // n_msgs
    outArray[0]["n_msgs"] = factory.createScalar(msg->n_msgs);
    // msg_number
    outArray[0]["msg_number"] = factory.createScalar(msg->msg_number);
    // n_satellites
    outArray[0]["n_satellites"] = factory.createScalar(msg->n_satellites);
    // satellites
    outArray[0]["satellites"] = get_arr_nmea_msgs_GpgsvSatellite_var_arr(factory, msg->satellites);
    return std::move(outArray);
  }
} //namespace Gpgsv
} //namespace matlabhelper
} //namespace nmea_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1