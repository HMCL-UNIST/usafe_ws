// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/RecognizeLightStateResponse
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
#include "hmcl_msgs/RecognizeLightStateResponse.h"
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
namespace RecognizeLightStateResponse {
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::RecognizeLightStateResponse>& msg, const matlab::data::StructArray arr) {
    try {
        //class_id
        const matlab::data::TypedArray<uint8_t> class_id_arr = arr[0]["class_id"];
        msg->class_id = class_id_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'class_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'class_id' is wrong type; expected a uint8.");
    }
    try {
        //confidence
        const matlab::data::TypedArray<float> confidence_arr = arr[0]["confidence"];
        msg->confidence = confidence_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'confidence' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'confidence' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::RecognizeLightStateResponse>& msg) {
    auto outArray = factory.createStructArray({1,1},{"class_id","confidence"});
    // class_id
    outArray[0]["class_id"] = factory.createScalar(msg->class_id);
    // confidence
    outArray[0]["confidence"] = factory.createScalar(msg->confidence);
    return std::move(outArray);
  }
} //namespace RecognizeLightStateResponse
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1