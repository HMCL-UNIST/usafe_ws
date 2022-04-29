// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/line2D
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
#include "autorally_msgs/line2D.h"
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
namespace line2D {
  void copy_from_arr_autorally_msgs_point2D(autorally_msgs::point2D& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_autorally_msgs_point2D(MDFactory_T& factory, const autorally_msgs::line2D::_start_type& val);
  //----------------------------------------------------------------------------
  void copy_from_arr_autorally_msgs_point2D(autorally_msgs::point2D& val, const matlab::data::StructArray& arr) {
    // _autorally_msgs_point2D.x
    try {
        const matlab::data::TypedArray<uint16_t> _startx_arr = arr[0]["x"];
        val.x = _startx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a uint16.");
    }
    // _autorally_msgs_point2D.y
    try {
        const matlab::data::TypedArray<uint16_t> _starty_arr = arr[0]["y"];
        val.y = _starty_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a uint16.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_point2D(MDFactory_T& factory, const autorally_msgs::line2D::_start_type& val) {
    auto _startoutArray = factory.createStructArray({1,1},{"x","y"});
    // _autorally_msgs_point2D.x
    _startoutArray[0]["x"] = factory.createScalar(val.x);
    // _autorally_msgs_point2D.y
    _startoutArray[0]["y"] = factory.createScalar(val.y);
    return std::move(_startoutArray);
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::line2D>& msg, const matlab::data::StructArray arr) {
    try {
        //start
        const matlab::data::StructArray start_arr = arr[0]["start"];
        copy_from_arr_autorally_msgs_point2D(msg->start,start_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'start' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'start' is wrong type; expected a struct.");
    }
    try {
        //end
        const matlab::data::StructArray end_arr = arr[0]["end"];
        copy_from_arr_autorally_msgs_point2D(msg->end,end_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'end' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'end' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::line2D>& msg) {
    auto outArray = factory.createStructArray({1,1},{"start","end"});
    // start
    outArray[0]["start"] = get_arr_autorally_msgs_point2D(factory, msg->start);
    // end
    outArray[0]["end"] = get_arr_autorally_msgs_point2D(factory, msg->end);
    return std::move(outArray);
  }
} //namespace line2D
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1