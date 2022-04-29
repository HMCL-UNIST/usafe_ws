// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/VehicleSCC
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
#include "hmcl_msgs/VehicleSCC.h"
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
namespace VehicleSCC {
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::VehicleSCC>& msg, const matlab::data::StructArray arr) {
    try {
        //scc_mode
        const matlab::data::TypedArray<uint8_t> scc_mode_arr = arr[0]["scc_mode"];
        msg->scc_mode = scc_mode_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'scc_mode' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'scc_mode' is wrong type; expected a uint8.");
    }
    try {
        //scc_takeover
        const matlab::data::TypedArray<uint8_t> scc_takeover_arr = arr[0]["scc_takeover"];
        msg->scc_takeover = scc_takeover_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'scc_takeover' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'scc_takeover' is wrong type; expected a uint8.");
    }
    try {
        //acceleration
        const matlab::data::TypedArray<double> acceleration_arr = arr[0]["acceleration"];
        msg->acceleration = acceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acceleration' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'acceleration' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::VehicleSCC>& msg) {
    auto outArray = factory.createStructArray({1,1},{"scc_mode","scc_takeover","acceleration"});
    // scc_mode
    outArray[0]["scc_mode"] = factory.createScalar(msg->scc_mode);
    // scc_takeover
    outArray[0]["scc_takeover"] = factory.createScalar(msg->scc_takeover);
    // acceleration
    outArray[0]["acceleration"] = factory.createScalar(msg->acceleration);
    return std::move(outArray);
  }
} //namespace VehicleSCC
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1