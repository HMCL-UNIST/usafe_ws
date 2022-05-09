// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/RemoteButton
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
#include "hmcl_msgs/RemoteButton.h"
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
namespace RemoteButton {
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::RemoteButton>& msg, const matlab::data::StructArray arr) {
    try {
        //button1
        const matlab::data::TypedArray<uint8_t> button1_arr = arr[0]["button1"];
        msg->button1 = button1_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'button1' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'button1' is wrong type; expected a uint8.");
    }
    try {
        //button2
        const matlab::data::TypedArray<uint8_t> button2_arr = arr[0]["button2"];
        msg->button2 = button2_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'button2' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'button2' is wrong type; expected a uint8.");
    }
    try {
        //button3
        const matlab::data::TypedArray<uint8_t> button3_arr = arr[0]["button3"];
        msg->button3 = button3_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'button3' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'button3' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::RemoteButton>& msg) {
    auto outArray = factory.createStructArray({1,1},{"button1","button2","button3"});
    // button1
    outArray[0]["button1"] = factory.createScalar(msg->button1);
    // button2
    outArray[0]["button2"] = factory.createScalar(msg->button2);
    // button3
    outArray[0]["button3"] = factory.createScalar(msg->button3);
    return std::move(outArray);
  }
} //namespace RemoteButton
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1