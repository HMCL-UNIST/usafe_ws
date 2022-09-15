// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for autorally_msgs/imageMask
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
#include "autorally_msgs/imageMask.h"
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
namespace imageMask {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const autorally_msgs::imageMask::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_autorally_msgs_point2D_var_arr(autorally_msgs::point2D& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_autorally_msgs_point2D_var_arr(MDFactory_T& factory, const autorally_msgs::imageMask::_points_type& val);
  void copy_from_arr_autorally_msgs_line2D_var_arr(autorally_msgs::line2D& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_autorally_msgs_line2D_var_arr(MDFactory_T& factory, const autorally_msgs::imageMask::_lines_type& val);
  void copy_from_arr_autorally_msgs_point2D(autorally_msgs::point2D& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_autorally_msgs_point2D(MDFactory_T& factory, const autorally_msgs::line2D::_start_type& val);
  void copy_from_arr_sensor_msgs_RegionOfInterest_var_arr(sensor_msgs::RegionOfInterest& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_sensor_msgs_RegionOfInterest_var_arr(MDFactory_T& factory, const autorally_msgs::imageMask::_rois_type& val);
  //----------------------------------------------------------------------------
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr) {
    // _std_msgs_Header.seq
    try {
        const matlab::data::TypedArray<uint32_t> _headerseq_arr = arr[0]["seq"];
        val.seq = _headerseq_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'seq' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'seq' is wrong type; expected a uint32.");
    }
    // _std_msgs_Header.stamp
    try {
        const matlab::data::StructArray _headerstamp_arr = arr[0]["stamp"];
        copy_from_arr_ros_Time(val.stamp,_headerstamp_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stamp' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stamp' is wrong type; expected a struct.");
    }
    // _std_msgs_Header.frame_id
    try {
        const matlab::data::CharArray _headerframe_id_arr = arr[0]["frame_id"];
        val.frame_id = _headerframe_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'frame_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'frame_id' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const autorally_msgs::imageMask::_header_type& val) {
    auto _headeroutArray = factory.createStructArray({1,1},{"seq","stamp","frame_id"});
    // _std_msgs_Header.seq
    _headeroutArray[0]["seq"] = factory.createScalar(val.seq);
    // _std_msgs_Header.stamp
    _headeroutArray[0]["stamp"] = get_arr_ros_Time(factory, val.stamp);
    // _std_msgs_Header.frame_id
    _headeroutArray[0]["frame_id"] = factory.createCharArray(val.frame_id);
    return std::move(_headeroutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr) {
    // _ros_Time.sec
    try {
        const matlab::data::TypedArray<uint32_t> _header_stampsec_arr = arr[0]["sec"];
        val.sec = _header_stampsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'sec' is wrong type; expected a uint32.");
    }
    // _ros_Time.nsec
    try {
        const matlab::data::TypedArray<uint32_t> _header_stampnsec_arr = arr[0]["nsec"];
        val.nsec = _header_stampnsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'nsec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'nsec' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val) {
    auto _header_stampoutArray = factory.createStructArray({1,1},{"sec","nsec"});
    // _ros_Time.sec
    _header_stampoutArray[0]["sec"] = factory.createScalar(val.sec);
    // _ros_Time.nsec
    _header_stampoutArray[0]["nsec"] = factory.createScalar(val.nsec);
    return std::move(_header_stampoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_autorally_msgs_point2D_var_arr(autorally_msgs::point2D& val, const matlab::data::Struct& arr) {
    // _autorally_msgs_point2D_var_arr.x
    try {
        const matlab::data::TypedArray<uint16_t> _pointsx_arr = arr["x"];
        val.x = _pointsx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a uint16.");
    }
    // _autorally_msgs_point2D_var_arr.y
    try {
        const matlab::data::TypedArray<uint16_t> _pointsy_arr = arr["y"];
        val.y = _pointsy_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a uint16.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_point2D_var_arr(MDFactory_T& factory, const autorally_msgs::imageMask::_points_type& val) {
    auto _pointsoutArray = factory.createStructArray({1,val.size()},{"x","y"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _autorally_msgs_point2D_var_arr.x
    	_pointsoutArray[idx]["x"] = factory.createScalar(val[idx].x);
    // _autorally_msgs_point2D_var_arr.y
    	_pointsoutArray[idx]["y"] = factory.createScalar(val[idx].y);
    }
    return std::move(_pointsoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_autorally_msgs_line2D_var_arr(autorally_msgs::line2D& val, const matlab::data::Struct& arr) {
    // _autorally_msgs_line2D_var_arr.start
    try {
        const matlab::data::StructArray _linesstart_arr = arr["start"];
        copy_from_arr_autorally_msgs_point2D(val.start,_linesstart_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'start' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'start' is wrong type; expected a struct.");
    }
    // _autorally_msgs_line2D_var_arr.end
    try {
        const matlab::data::StructArray _linesend_arr = arr["end"];
        copy_from_arr_autorally_msgs_point2D(val.end,_linesend_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'end' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'end' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_line2D_var_arr(MDFactory_T& factory, const autorally_msgs::imageMask::_lines_type& val) {
    auto _linesoutArray = factory.createStructArray({1,val.size()},{"start","end"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _autorally_msgs_line2D_var_arr.start
    _linesoutArray[idx]["start"] = get_arr_autorally_msgs_point2D(factory, val[idx].start);
    // _autorally_msgs_line2D_var_arr.end
    _linesoutArray[idx]["end"] = get_arr_autorally_msgs_point2D(factory, val[idx].end);
    }
    return std::move(_linesoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_autorally_msgs_point2D(autorally_msgs::point2D& val, const matlab::data::StructArray& arr) {
    // _autorally_msgs_point2D.x
    try {
        const matlab::data::TypedArray<uint16_t> _lines_startx_arr = arr[0]["x"];
        val.x = _lines_startx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a uint16.");
    }
    // _autorally_msgs_point2D.y
    try {
        const matlab::data::TypedArray<uint16_t> _lines_starty_arr = arr[0]["y"];
        val.y = _lines_starty_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a uint16.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_autorally_msgs_point2D(MDFactory_T& factory, const autorally_msgs::line2D::_start_type& val) {
    auto _lines_startoutArray = factory.createStructArray({1,1},{"x","y"});
    // _autorally_msgs_point2D.x
    _lines_startoutArray[0]["x"] = factory.createScalar(val.x);
    // _autorally_msgs_point2D.y
    _lines_startoutArray[0]["y"] = factory.createScalar(val.y);
    return std::move(_lines_startoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_sensor_msgs_RegionOfInterest_var_arr(sensor_msgs::RegionOfInterest& val, const matlab::data::Struct& arr) {
    // _sensor_msgs_RegionOfInterest_var_arr.x_offset
    try {
        const matlab::data::TypedArray<uint32_t> _roisx_offset_arr = arr["x_offset"];
        val.x_offset = _roisx_offset_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x_offset' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x_offset' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_RegionOfInterest_var_arr.y_offset
    try {
        const matlab::data::TypedArray<uint32_t> _roisy_offset_arr = arr["y_offset"];
        val.y_offset = _roisy_offset_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y_offset' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y_offset' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_RegionOfInterest_var_arr.height
    try {
        const matlab::data::TypedArray<uint32_t> _roisheight_arr = arr["height"];
        val.height = _roisheight_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'height' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'height' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_RegionOfInterest_var_arr.width
    try {
        const matlab::data::TypedArray<uint32_t> _roiswidth_arr = arr["width"];
        val.width = _roiswidth_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'width' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'width' is wrong type; expected a uint32.");
    }
    // _sensor_msgs_RegionOfInterest_var_arr.do_rectify
    try {
        const matlab::data::TypedArray<bool> _roisdo_rectify_arr = arr["do_rectify"];
        val.do_rectify = _roisdo_rectify_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'do_rectify' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'do_rectify' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_sensor_msgs_RegionOfInterest_var_arr(MDFactory_T& factory, const autorally_msgs::imageMask::_rois_type& val) {
    auto _roisoutArray = factory.createStructArray({1,val.size()},{"x_offset","y_offset","height","width","do_rectify"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _sensor_msgs_RegionOfInterest_var_arr.x_offset
    	_roisoutArray[idx]["x_offset"] = factory.createScalar(val[idx].x_offset);
    // _sensor_msgs_RegionOfInterest_var_arr.y_offset
    	_roisoutArray[idx]["y_offset"] = factory.createScalar(val[idx].y_offset);
    // _sensor_msgs_RegionOfInterest_var_arr.height
    	_roisoutArray[idx]["height"] = factory.createScalar(val[idx].height);
    // _sensor_msgs_RegionOfInterest_var_arr.width
    	_roisoutArray[idx]["width"] = factory.createScalar(val[idx].width);
    // _sensor_msgs_RegionOfInterest_var_arr.do_rectify
    	_roisoutArray[idx]["do_rectify"] = factory.createScalar(static_cast<bool>(val[idx].do_rectify));
    }
    return std::move(_roisoutArray);
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<autorally_msgs::imageMask>& msg, const matlab::data::StructArray arr) {
    try {
        //header
        const matlab::data::StructArray header_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(msg->header,header_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    try {
        //sender
        const matlab::data::CharArray sender_arr = arr[0]["sender"];
        msg->sender = sender_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sender' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'sender' is wrong type; expected a string.");
    }
    try {
        //points
        const matlab::data::StructArray points_arr = arr[0]["points"];
        for (auto _pointsarr : points_arr) {
        	autorally_msgs::point2D _val;
        	copy_from_arr_autorally_msgs_point2D_var_arr(_val,_pointsarr);
        	msg->points.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'points' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'points' is wrong type; expected a struct.");
    }
    try {
        //lines
        const matlab::data::StructArray lines_arr = arr[0]["lines"];
        for (auto _linesarr : lines_arr) {
        	autorally_msgs::line2D _val;
        	copy_from_arr_autorally_msgs_line2D_var_arr(_val,_linesarr);
        	msg->lines.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lines' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lines' is wrong type; expected a struct.");
    }
    try {
        //rois
        const matlab::data::StructArray rois_arr = arr[0]["rois"];
        for (auto _roisarr : rois_arr) {
        	sensor_msgs::RegionOfInterest _val;
        	copy_from_arr_sensor_msgs_RegionOfInterest_var_arr(_val,_roisarr);
        	msg->rois.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'rois' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'rois' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  AUTORALLY_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const autorally_msgs::imageMask>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","sender","points","lines","rois"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // sender
    outArray[0]["sender"] = factory.createCharArray(msg->sender);
    // points
    outArray[0]["points"] = get_arr_autorally_msgs_point2D_var_arr(factory, msg->points);
    // lines
    outArray[0]["lines"] = get_arr_autorally_msgs_line2D_var_arr(factory, msg->lines);
    // rois
    outArray[0]["rois"] = get_arr_sensor_msgs_RegionOfInterest_var_arr(factory, msg->rois);
    return std::move(outArray);
  }
} //namespace imageMask
} //namespace matlabhelper
} //namespace autorally_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1