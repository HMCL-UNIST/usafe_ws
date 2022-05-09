// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/lapStats
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
#include "autorally_msgs/lapStats.h"
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
namespace lapStats {
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::lapStats>& msg, const matlab::data::StructArray arr) {
    try {
        //lap_number
        const matlab::data::TypedArray<int64_t> lap_number_arr = arr[0]["lap_number"];
        msg->lap_number = lap_number_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lap_number' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lap_number' is wrong type; expected a int64.");
    }
    try {
        //lap_time
        const matlab::data::TypedArray<double> lap_time_arr = arr[0]["lap_time"];
        msg->lap_time = lap_time_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lap_time' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lap_time' is wrong type; expected a double.");
    }
    try {
        //max_speed
        const matlab::data::TypedArray<double> max_speed_arr = arr[0]["max_speed"];
        msg->max_speed = max_speed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_speed' is wrong type; expected a double.");
    }
    try {
        //max_slip
        const matlab::data::TypedArray<double> max_slip_arr = arr[0]["max_slip"];
        msg->max_slip = max_slip_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'max_slip' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'max_slip' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::lapStats>& msg) {
    auto outArray = factory.createStructArray({1,1},{"lap_number","lap_time","max_speed","max_slip"});
    // lap_number
    outArray[0]["lap_number"] = factory.createScalar(msg->lap_number);
    // lap_time
    outArray[0]["lap_time"] = factory.createScalar(msg->lap_time);
    // max_speed
    outArray[0]["max_speed"] = factory.createScalar(msg->max_speed);
    // max_slip
    outArray[0]["max_slip"] = factory.createScalar(msg->max_slip);
    return std::move(outArray);
  }
} //namespace lapStats
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1