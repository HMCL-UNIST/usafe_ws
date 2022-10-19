// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for ackermann_msgs/AckermannDrive
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
#include "ackermann_msgs/AckermannDrive.h"
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
namespace AckermannDrive {
  //----------------------------------------------------------------------------
  ACKERMANN_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<ackermann_msgs::AckermannDrive>& msg, const matlab::data::StructArray arr) {
    try {
        //steering_angle
        const matlab::data::TypedArray<float> steering_angle_arr = arr[0]["steering_angle"];
        msg->steering_angle = steering_angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_angle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_angle' is wrong type; expected a single.");
    }
    try {
        //steering_angle_velocity
        const matlab::data::TypedArray<float> steering_angle_velocity_arr = arr[0]["steering_angle_velocity"];
        msg->steering_angle_velocity = steering_angle_velocity_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_angle_velocity' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_angle_velocity' is wrong type; expected a single.");
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
        //acceleration
        const matlab::data::TypedArray<float> acceleration_arr = arr[0]["acceleration"];
        msg->acceleration = acceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acceleration' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'acceleration' is wrong type; expected a single.");
    }
    try {
        //jerk
        const matlab::data::TypedArray<float> jerk_arr = arr[0]["jerk"];
        msg->jerk = jerk_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'jerk' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'jerk' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  ACKERMANN_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const ackermann_msgs::AckermannDrive>& msg) {
    auto outArray = factory.createStructArray({1,1},{"steering_angle","steering_angle_velocity","speed","acceleration","jerk"});
    // steering_angle
    outArray[0]["steering_angle"] = factory.createScalar(msg->steering_angle);
    // steering_angle_velocity
    outArray[0]["steering_angle_velocity"] = factory.createScalar(msg->steering_angle_velocity);
    // speed
    outArray[0]["speed"] = factory.createScalar(msg->speed);
    // acceleration
    outArray[0]["acceleration"] = factory.createScalar(msg->acceleration);
    // jerk
    outArray[0]["jerk"] = factory.createScalar(msg->jerk);
    return std::move(outArray);
  }
} //namespace AckermannDrive
} //namespace matlabhelper
} //namespace ackermann_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1