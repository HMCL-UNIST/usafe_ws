// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/neuralNetLayer
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
#include "autorally_msgs/neuralNetLayer.h"
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
namespace neuralNetLayer {
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::neuralNetLayer>& msg, const matlab::data::StructArray arr) {
    try {
        //name
        const matlab::data::CharArray name_arr = arr[0]["name"];
        msg->name = name_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'name' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'name' is wrong type; expected a string.");
    }
    try {
        //weight
        const matlab::data::TypedArray<float> weight_arr = arr[0]["weight"];
        size_t nelem = weight_arr.getNumberOfElements();
        	msg->weight.resize(nelem);
        	std::copy(weight_arr.begin(), weight_arr.begin()+nelem, msg->weight.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'weight' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'weight' is wrong type; expected a single.");
    }
    try {
        //bias
        const matlab::data::TypedArray<float> bias_arr = arr[0]["bias"];
        size_t nelem = bias_arr.getNumberOfElements();
        	msg->bias.resize(nelem);
        	std::copy(bias_arr.begin(), bias_arr.begin()+nelem, msg->bias.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'bias' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'bias' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::neuralNetLayer>& msg) {
    auto outArray = factory.createStructArray({1,1},{"name","weight","bias"});
    // name
    outArray[0]["name"] = factory.createCharArray(msg->name);
    // weight
    outArray[0]["weight"] = factory.createArray<autorally_msgs::neuralNetLayer::_weight_type::const_iterator, float>({1, msg->weight.size()}, msg->weight.begin(), msg->weight.end());
    // bias
    outArray[0]["bias"] = factory.createArray<autorally_msgs::neuralNetLayer::_bias_type::const_iterator, float>({1, msg->bias.size()}, msg->bias.begin(), msg->bias.end());
    return std::move(outArray);
  }
} //namespace neuralNetLayer
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1