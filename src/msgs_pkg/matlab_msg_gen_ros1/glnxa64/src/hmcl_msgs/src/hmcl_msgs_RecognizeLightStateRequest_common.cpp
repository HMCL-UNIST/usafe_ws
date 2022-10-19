// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/RecognizeLightStateRequest
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
#include "hmcl_msgs/RecognizeLightStateRequest.h"
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
namespace RecognizeLightStateRequest {
  void copy_from_arr_sensor_msgs_Image(sensor_msgs::Image& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_sensor_msgs_Image(MDFactory_T& factory, const hmcl_msgs::RecognizeLightStateRequest::_roi_image_type& val);
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const sensor_msgs::Image::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  //----------------------------------------------------------------------------
  void copy_from_arr_sensor_msgs_Image(sensor_msgs::Image& val, const matlab::data::StructArray& arr) {
    // _sensor_msgs_Image.header
    try {
        const matlab::data::StructArray _roi_imageheader_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(val.header,_roi_imageheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _sensor_msgs_Image.height
    try {
        const matlab::data::TypedArray<uint32_t> _roi_imageheight_arr = arr[0]["height"];
        val.height = _roi_imageheight_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'height' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'height' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_Image.width
    try {
        const matlab::data::TypedArray<uint32_t> _roi_imagewidth_arr = arr[0]["width"];
        val.width = _roi_imagewidth_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'width' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'width' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_Image.encoding
    try {
        const matlab::data::CharArray _roi_imageencoding_arr = arr[0]["encoding"];
        val.encoding = _roi_imageencoding_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'encoding' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'encoding' is wrong type; expected a string.");
    }
    // _sensor_msgs_Image.is_bigendian
    try {
        const matlab::data::TypedArray<uint8_t> _roi_imageis_bigendian_arr = arr[0]["is_bigendian"];
        val.is_bigendian = _roi_imageis_bigendian_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'is_bigendian' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'is_bigendian' is wrong type; expected a uint8.");
    }
    // _sensor_msgs_Image.step
    try {
        const matlab::data::TypedArray<uint32_t> _roi_imagestep_arr = arr[0]["step"];
        val.step = _roi_imagestep_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'step' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'step' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_Image.data
    try {
        const matlab::data::TypedArray<uint8_t> _roi_imagedata_arr = arr[0]["data"];
        size_t nelem = _roi_imagedata_arr.getNumberOfElements();
        	val.data.resize(nelem);
        	std::copy(_roi_imagedata_arr.begin(), _roi_imagedata_arr.begin()+nelem, val.data.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'data' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'data' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_sensor_msgs_Image(MDFactory_T& factory, const hmcl_msgs::RecognizeLightStateRequest::_roi_image_type& val) {
    auto _roi_imageoutArray = factory.createStructArray({1,1},{"header","height","width","encoding","is_bigendian","step","data"});
    // _sensor_msgs_Image.header
    _roi_imageoutArray[0]["header"] = get_arr_std_msgs_Header(factory, val.header);
    // _sensor_msgs_Image.height
    _roi_imageoutArray[0]["height"] = factory.createScalar(val.height);
    // _sensor_msgs_Image.width
    _roi_imageoutArray[0]["width"] = factory.createScalar(val.width);
    // _sensor_msgs_Image.encoding
    _roi_imageoutArray[0]["encoding"] = factory.createCharArray(val.encoding);
    // _sensor_msgs_Image.is_bigendian
    _roi_imageoutArray[0]["is_bigendian"] = factory.createScalar(val.is_bigendian);
    // _sensor_msgs_Image.step
    _roi_imageoutArray[0]["step"] = factory.createScalar(val.step);
    // _sensor_msgs_Image.data
    _roi_imageoutArray[0]["data"] = factory.createArray<sensor_msgs::Image::_data_type::const_iterator, uint8_t>({1, val.data.size()}, val.data.begin(), val.data.end());
    return std::move(_roi_imageoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr) {
    // _std_msgs_Header.seq
    try {
        const matlab::data::TypedArray<uint32_t> _roi_image_headerseq_arr = arr[0]["seq"];
        val.seq = _roi_image_headerseq_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'seq' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'seq' is wrong type; expected a uint32.");
    }
    // _std_msgs_Header.stamp
    try {
        const matlab::data::StructArray _roi_image_headerstamp_arr = arr[0]["stamp"];
        copy_from_arr_ros_Time(val.stamp,_roi_image_headerstamp_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stamp' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stamp' is wrong type; expected a struct.");
    }
    // _std_msgs_Header.frame_id
    try {
        const matlab::data::CharArray _roi_image_headerframe_id_arr = arr[0]["frame_id"];
        val.frame_id = _roi_image_headerframe_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'frame_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'frame_id' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const sensor_msgs::Image::_header_type& val) {
    auto _roi_image_headeroutArray = factory.createStructArray({1,1},{"seq","stamp","frame_id"});
    // _std_msgs_Header.seq
    _roi_image_headeroutArray[0]["seq"] = factory.createScalar(val.seq);
    // _std_msgs_Header.stamp
    _roi_image_headeroutArray[0]["stamp"] = get_arr_ros_Time(factory, val.stamp);
    // _std_msgs_Header.frame_id
    _roi_image_headeroutArray[0]["frame_id"] = factory.createCharArray(val.frame_id);
    return std::move(_roi_image_headeroutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr) {
    // _ros_Time.sec
    try {
        const matlab::data::TypedArray<uint32_t> _roi_image_header_stampsec_arr = arr[0]["sec"];
        val.sec = _roi_image_header_stampsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'sec' is wrong type; expected a uint32.");
    }
    // _ros_Time.nsec
    try {
        const matlab::data::TypedArray<uint32_t> _roi_image_header_stampnsec_arr = arr[0]["nsec"];
        val.nsec = _roi_image_header_stampnsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'nsec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'nsec' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val) {
    auto _roi_image_header_stampoutArray = factory.createStructArray({1,1},{"sec","nsec"});
    // _ros_Time.sec
    _roi_image_header_stampoutArray[0]["sec"] = factory.createScalar(val.sec);
    // _ros_Time.nsec
    _roi_image_header_stampoutArray[0]["nsec"] = factory.createScalar(val.nsec);
    return std::move(_roi_image_header_stampoutArray);
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::RecognizeLightStateRequest>& msg, const matlab::data::StructArray arr) {
    try {
        //roi_image
        const matlab::data::StructArray roi_image_arr = arr[0]["roi_image"];
        copy_from_arr_sensor_msgs_Image(msg->roi_image,roi_image_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'roi_image' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'roi_image' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::RecognizeLightStateRequest>& msg) {
    auto outArray = factory.createStructArray({1,1},{"roi_image"});
    // roi_image
    outArray[0]["roi_image"] = get_arr_sensor_msgs_Image(factory, msg->roi_image);
    return std::move(outArray);
  }
} //namespace RecognizeLightStateRequest
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1