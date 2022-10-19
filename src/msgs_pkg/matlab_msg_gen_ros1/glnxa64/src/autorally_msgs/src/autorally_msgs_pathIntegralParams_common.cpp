// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/pathIntegralParams
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
#include "autorally_msgs/pathIntegralParams.h"
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
namespace pathIntegralParams {
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::pathIntegralParams>& msg, const matlab::data::StructArray arr) {
    try {
        //hz
        const matlab::data::TypedArray<int64_t> hz_arr = arr[0]["hz"];
        msg->hz = hz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'hz' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'hz' is wrong type; expected a int64.");
    }
    try {
        //num_timesteps
        const matlab::data::TypedArray<int64_t> num_timesteps_arr = arr[0]["num_timesteps"];
        msg->num_timesteps = num_timesteps_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'num_timesteps' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'num_timesteps' is wrong type; expected a int64.");
    }
    try {
        //num_iters
        const matlab::data::TypedArray<int64_t> num_iters_arr = arr[0]["num_iters"];
        msg->num_iters = num_iters_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'num_iters' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'num_iters' is wrong type; expected a int64.");
    }
    try {
        //gamma
        const matlab::data::TypedArray<double> gamma_arr = arr[0]["gamma"];
        msg->gamma = gamma_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gamma' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gamma' is wrong type; expected a double.");
    }
    try {
        //init_steering
        const matlab::data::TypedArray<double> init_steering_arr = arr[0]["init_steering"];
        msg->init_steering = init_steering_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'init_steering' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'init_steering' is wrong type; expected a double.");
    }
    try {
        //init_throttle
        const matlab::data::TypedArray<double> init_throttle_arr = arr[0]["init_throttle"];
        msg->init_throttle = init_throttle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'init_throttle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'init_throttle' is wrong type; expected a double.");
    }
    try {
        //steering_var
        const matlab::data::TypedArray<double> steering_var_arr = arr[0]["steering_var"];
        msg->steering_var = steering_var_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_var' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_var' is wrong type; expected a double.");
    }
    try {
        //throttle_var
        const matlab::data::TypedArray<double> throttle_var_arr = arr[0]["throttle_var"];
        msg->throttle_var = throttle_var_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'throttle_var' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'throttle_var' is wrong type; expected a double.");
    }
    try {
        //max_throttle
        const matlab::data::TypedArray<double> max_throttle_arr = arr[0]["max_throttle"];
        msg->max_throttle = max_throttle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_throttle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_throttle' is wrong type; expected a double.");
    }
    try {
        //speed_coefficient
        const matlab::data::TypedArray<double> speed_coefficient_arr = arr[0]["speed_coefficient"];
        msg->speed_coefficient = speed_coefficient_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speed_coefficient' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'speed_coefficient' is wrong type; expected a double.");
    }
    try {
        //track_coefficient
        const matlab::data::TypedArray<double> track_coefficient_arr = arr[0]["track_coefficient"];
        msg->track_coefficient = track_coefficient_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'track_coefficient' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'track_coefficient' is wrong type; expected a double.");
    }
    try {
        //max_slip_angle
        const matlab::data::TypedArray<double> max_slip_angle_arr = arr[0]["max_slip_angle"];
        msg->max_slip_angle = max_slip_angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_slip_angle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_slip_angle' is wrong type; expected a double.");
    }
    try {
        //track_slop
        const matlab::data::TypedArray<double> track_slop_arr = arr[0]["track_slop"];
        msg->track_slop = track_slop_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'track_slop' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'track_slop' is wrong type; expected a double.");
    }
    try {
        //crash_coeff
        const matlab::data::TypedArray<double> crash_coeff_arr = arr[0]["crash_coeff"];
        msg->crash_coeff = crash_coeff_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'crash_coeff' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'crash_coeff' is wrong type; expected a double.");
    }
    try {
        //map_path
        const matlab::data::CharArray map_path_arr = arr[0]["map_path"];
        msg->map_path = map_path_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'map_path' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'map_path' is wrong type; expected a string.");
    }
    try {
        //desired_speed
        const matlab::data::TypedArray<double> desired_speed_arr = arr[0]["desired_speed"];
        msg->desired_speed = desired_speed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'desired_speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'desired_speed' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::pathIntegralParams>& msg) {
    auto outArray = factory.createStructArray({1,1},{"hz","num_timesteps","num_iters","gamma","init_steering","init_throttle","steering_var","throttle_var","max_throttle","speed_coefficient","track_coefficient","max_slip_angle","track_slop","crash_coeff","map_path","desired_speed"});
    // hz
    outArray[0]["hz"] = factory.createScalar(msg->hz);
    // num_timesteps
    outArray[0]["num_timesteps"] = factory.createScalar(msg->num_timesteps);
    // num_iters
    outArray[0]["num_iters"] = factory.createScalar(msg->num_iters);
    // gamma
    outArray[0]["gamma"] = factory.createScalar(msg->gamma);
    // init_steering
    outArray[0]["init_steering"] = factory.createScalar(msg->init_steering);
    // init_throttle
    outArray[0]["init_throttle"] = factory.createScalar(msg->init_throttle);
    // steering_var
    outArray[0]["steering_var"] = factory.createScalar(msg->steering_var);
    // throttle_var
    outArray[0]["throttle_var"] = factory.createScalar(msg->throttle_var);
    // max_throttle
    outArray[0]["max_throttle"] = factory.createScalar(msg->max_throttle);
    // speed_coefficient
    outArray[0]["speed_coefficient"] = factory.createScalar(msg->speed_coefficient);
    // track_coefficient
    outArray[0]["track_coefficient"] = factory.createScalar(msg->track_coefficient);
    // max_slip_angle
    outArray[0]["max_slip_angle"] = factory.createScalar(msg->max_slip_angle);
    // track_slop
    outArray[0]["track_slop"] = factory.createScalar(msg->track_slop);
    // crash_coeff
    outArray[0]["crash_coeff"] = factory.createScalar(msg->crash_coeff);
    // map_path
    outArray[0]["map_path"] = factory.createCharArray(msg->map_path);
    // desired_speed
    outArray[0]["desired_speed"] = factory.createScalar(msg->desired_speed);
    return std::move(outArray);
  }
} //namespace pathIntegralParams
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1