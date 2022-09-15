// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/pathIntegralStats
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
#include "autorally_msgs/pathIntegralStats.h"
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
namespace autorally_msgs {
namespace matlabhelper {
namespace pathIntegralStats {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const autorally_msgs::pathIntegralStats::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_autorally_msgs_pathIntegralParams(autorally_msgs::pathIntegralParams& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_autorally_msgs_pathIntegralParams(MDFactory_T& factory, const autorally_msgs::pathIntegralStats::_params_type& val);
  void copy_from_arr_autorally_msgs_lapStats(autorally_msgs::lapStats& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_autorally_msgs_lapStats(MDFactory_T& factory, const autorally_msgs::pathIntegralStats::_stats_type& val);
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
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const autorally_msgs::pathIntegralStats::_header_type& val) {
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
  void copy_from_arr_autorally_msgs_pathIntegralParams(autorally_msgs::pathIntegralParams& val, const matlab::data::StructArray& arr) {
    // _autorally_msgs_pathIntegralParams.hz
    try {
        const matlab::data::TypedArray<int64_t> _paramshz_arr = arr[0]["hz"];
        val.hz = _paramshz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'hz' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'hz' is wrong type; expected a int64.");
    }
    // _autorally_msgs_pathIntegralParams.num_timesteps
    try {
        const matlab::data::TypedArray<int64_t> _paramsnum_timesteps_arr = arr[0]["num_timesteps"];
        val.num_timesteps = _paramsnum_timesteps_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'num_timesteps' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'num_timesteps' is wrong type; expected a int64.");
    }
    // _autorally_msgs_pathIntegralParams.num_iters
    try {
        const matlab::data::TypedArray<int64_t> _paramsnum_iters_arr = arr[0]["num_iters"];
        val.num_iters = _paramsnum_iters_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'num_iters' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'num_iters' is wrong type; expected a int64.");
    }
    // _autorally_msgs_pathIntegralParams.gamma
    try {
        const matlab::data::TypedArray<double> _paramsgamma_arr = arr[0]["gamma"];
        val.gamma = _paramsgamma_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gamma' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gamma' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.init_steering
    try {
        const matlab::data::TypedArray<double> _paramsinit_steering_arr = arr[0]["init_steering"];
        val.init_steering = _paramsinit_steering_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'init_steering' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'init_steering' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.init_throttle
    try {
        const matlab::data::TypedArray<double> _paramsinit_throttle_arr = arr[0]["init_throttle"];
        val.init_throttle = _paramsinit_throttle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'init_throttle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'init_throttle' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.steering_var
    try {
        const matlab::data::TypedArray<double> _paramssteering_var_arr = arr[0]["steering_var"];
        val.steering_var = _paramssteering_var_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_var' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_var' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.throttle_var
    try {
        const matlab::data::TypedArray<double> _paramsthrottle_var_arr = arr[0]["throttle_var"];
        val.throttle_var = _paramsthrottle_var_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'throttle_var' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'throttle_var' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.max_throttle
    try {
        const matlab::data::TypedArray<double> _paramsmax_throttle_arr = arr[0]["max_throttle"];
        val.max_throttle = _paramsmax_throttle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_throttle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_throttle' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.speed_coefficient
    try {
        const matlab::data::TypedArray<double> _paramsspeed_coefficient_arr = arr[0]["speed_coefficient"];
        val.speed_coefficient = _paramsspeed_coefficient_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speed_coefficient' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'speed_coefficient' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.track_coefficient
    try {
        const matlab::data::TypedArray<double> _paramstrack_coefficient_arr = arr[0]["track_coefficient"];
        val.track_coefficient = _paramstrack_coefficient_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'track_coefficient' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'track_coefficient' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.max_slip_angle
    try {
        const matlab::data::TypedArray<double> _paramsmax_slip_angle_arr = arr[0]["max_slip_angle"];
        val.max_slip_angle = _paramsmax_slip_angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_slip_angle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_slip_angle' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.track_slop
    try {
        const matlab::data::TypedArray<double> _paramstrack_slop_arr = arr[0]["track_slop"];
        val.track_slop = _paramstrack_slop_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'track_slop' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'track_slop' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.crash_coeff
    try {
        const matlab::data::TypedArray<double> _paramscrash_coeff_arr = arr[0]["crash_coeff"];
        val.crash_coeff = _paramscrash_coeff_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'crash_coeff' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'crash_coeff' is wrong type; expected a double.");
    }
    // _autorally_msgs_pathIntegralParams.map_path
    try {
        const matlab::data::CharArray _paramsmap_path_arr = arr[0]["map_path"];
        val.map_path = _paramsmap_path_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'map_path' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'map_path' is wrong type; expected a string.");
    }
    // _autorally_msgs_pathIntegralParams.desired_speed
    try {
        const matlab::data::TypedArray<double> _paramsdesired_speed_arr = arr[0]["desired_speed"];
        val.desired_speed = _paramsdesired_speed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'desired_speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'desired_speed' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_pathIntegralParams(MDFactory_T& factory, const autorally_msgs::pathIntegralStats::_params_type& val) {
    auto _paramsoutArray = factory.createStructArray({1,1},{"hz","num_timesteps","num_iters","gamma","init_steering","init_throttle","steering_var","throttle_var","max_throttle","speed_coefficient","track_coefficient","max_slip_angle","track_slop","crash_coeff","map_path","desired_speed"});
    // _autorally_msgs_pathIntegralParams.hz
    _paramsoutArray[0]["hz"] = factory.createScalar(val.hz);
    // _autorally_msgs_pathIntegralParams.num_timesteps
    _paramsoutArray[0]["num_timesteps"] = factory.createScalar(val.num_timesteps);
    // _autorally_msgs_pathIntegralParams.num_iters
    _paramsoutArray[0]["num_iters"] = factory.createScalar(val.num_iters);
    // _autorally_msgs_pathIntegralParams.gamma
    _paramsoutArray[0]["gamma"] = factory.createScalar(val.gamma);
    // _autorally_msgs_pathIntegralParams.init_steering
    _paramsoutArray[0]["init_steering"] = factory.createScalar(val.init_steering);
    // _autorally_msgs_pathIntegralParams.init_throttle
    _paramsoutArray[0]["init_throttle"] = factory.createScalar(val.init_throttle);
    // _autorally_msgs_pathIntegralParams.steering_var
    _paramsoutArray[0]["steering_var"] = factory.createScalar(val.steering_var);
    // _autorally_msgs_pathIntegralParams.throttle_var
    _paramsoutArray[0]["throttle_var"] = factory.createScalar(val.throttle_var);
    // _autorally_msgs_pathIntegralParams.max_throttle
    _paramsoutArray[0]["max_throttle"] = factory.createScalar(val.max_throttle);
    // _autorally_msgs_pathIntegralParams.speed_coefficient
    _paramsoutArray[0]["speed_coefficient"] = factory.createScalar(val.speed_coefficient);
    // _autorally_msgs_pathIntegralParams.track_coefficient
    _paramsoutArray[0]["track_coefficient"] = factory.createScalar(val.track_coefficient);
    // _autorally_msgs_pathIntegralParams.max_slip_angle
    _paramsoutArray[0]["max_slip_angle"] = factory.createScalar(val.max_slip_angle);
    // _autorally_msgs_pathIntegralParams.track_slop
    _paramsoutArray[0]["track_slop"] = factory.createScalar(val.track_slop);
    // _autorally_msgs_pathIntegralParams.crash_coeff
    _paramsoutArray[0]["crash_coeff"] = factory.createScalar(val.crash_coeff);
    // _autorally_msgs_pathIntegralParams.map_path
    _paramsoutArray[0]["map_path"] = factory.createCharArray(val.map_path);
    // _autorally_msgs_pathIntegralParams.desired_speed
    _paramsoutArray[0]["desired_speed"] = factory.createScalar(val.desired_speed);
    return std::move(_paramsoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_autorally_msgs_lapStats(autorally_msgs::lapStats& val, const matlab::data::StructArray& arr) {
    // _autorally_msgs_lapStats.lap_number
    try {
        const matlab::data::TypedArray<int64_t> _statslap_number_arr = arr[0]["lap_number"];
        val.lap_number = _statslap_number_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lap_number' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lap_number' is wrong type; expected a int64.");
    }
    // _autorally_msgs_lapStats.lap_time
    try {
        const matlab::data::TypedArray<double> _statslap_time_arr = arr[0]["lap_time"];
        val.lap_time = _statslap_time_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lap_time' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lap_time' is wrong type; expected a double.");
    }
    // _autorally_msgs_lapStats.max_speed
    try {
        const matlab::data::TypedArray<double> _statsmax_speed_arr = arr[0]["max_speed"];
        val.max_speed = _statsmax_speed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_speed' is wrong type; expected a double.");
    }
    // _autorally_msgs_lapStats.max_slip
    try {
        const matlab::data::TypedArray<double> _statsmax_slip_arr = arr[0]["max_slip"];
        val.max_slip = _statsmax_slip_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_slip' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_slip' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_lapStats(MDFactory_T& factory, const autorally_msgs::pathIntegralStats::_stats_type& val) {
    auto _statsoutArray = factory.createStructArray({1,1},{"lap_number","lap_time","max_speed","max_slip"});
    // _autorally_msgs_lapStats.lap_number
    _statsoutArray[0]["lap_number"] = factory.createScalar(val.lap_number);
    // _autorally_msgs_lapStats.lap_time
    _statsoutArray[0]["lap_time"] = factory.createScalar(val.lap_time);
    // _autorally_msgs_lapStats.max_speed
    _statsoutArray[0]["max_speed"] = factory.createScalar(val.max_speed);
    // _autorally_msgs_lapStats.max_slip
    _statsoutArray[0]["max_slip"] = factory.createScalar(val.max_slip);
    return std::move(_statsoutArray);
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::pathIntegralStats>& msg, const matlab::data::StructArray arr) {
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
        //tag
        const matlab::data::CharArray tag_arr = arr[0]["tag"];
        msg->tag = tag_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'tag' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'tag' is wrong type; expected a string.");
    }
    try {
        //params
        const matlab::data::StructArray params_arr = arr[0]["params"];
        copy_from_arr_autorally_msgs_pathIntegralParams(msg->params,params_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'params' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'params' is wrong type; expected a struct.");
    }
    try {
        //stats
        const matlab::data::StructArray stats_arr = arr[0]["stats"];
        copy_from_arr_autorally_msgs_lapStats(msg->stats,stats_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stats' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stats' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::pathIntegralStats>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","tag","params","stats"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // tag
    outArray[0]["tag"] = factory.createCharArray(msg->tag);
    // params
    outArray[0]["params"] = get_arr_autorally_msgs_pathIntegralParams(factory, msg->params);
    // stats
    outArray[0]["stats"] = get_arr_autorally_msgs_lapStats(factory, msg->stats);
    return std::move(outArray);
  }
} //namespace pathIntegralStats
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1