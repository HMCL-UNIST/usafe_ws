// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/VehicleLight
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
#include "hmcl_msgs/VehicleLight.h"
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
namespace hmcl_msgs {
namespace matlabhelper {
namespace VehicleLight {
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::VehicleLight>& msg, const matlab::data::StructArray arr) {
    try {
        //left_light
        const matlab::data::TypedArray<uint8_t> left_light_arr = arr[0]["left_light"];
        msg->left_light = left_light_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'left_light' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'left_light' is wrong type; expected a uint8.");
    }
    try {
        //right_light
        const matlab::data::TypedArray<uint8_t> right_light_arr = arr[0]["right_light"];
        msg->right_light = right_light_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'right_light' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'right_light' is wrong type; expected a uint8.");
    }
    try {
        //hazard_light
        const matlab::data::TypedArray<uint8_t> hazard_light_arr = arr[0]["hazard_light"];
        msg->hazard_light = hazard_light_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'hazard_light' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'hazard_light' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::VehicleLight>& msg) {
    auto outArray = factory.createStructArray({1,1},{"left_light","right_light","hazard_light"});
    // left_light
    outArray[0]["left_light"] = factory.createScalar(msg->left_light);
    // right_light
    outArray[0]["right_light"] = factory.createScalar(msg->right_light);
    // hazard_light
    outArray[0]["hazard_light"] = factory.createScalar(msg->hazard_light);
    return std::move(outArray);
  }
} //namespace VehicleLight
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1