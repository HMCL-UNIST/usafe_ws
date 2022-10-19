// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/Waypoint
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
#include "hmcl_msgs/Waypoint.h"
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
namespace Waypoint {
  void copy_from_arr_geometry_msgs_PoseStamped(geometry_msgs::PoseStamped& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_PoseStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_pose_type& val);
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const geometry_msgs::PoseStamped::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_geometry_msgs_Pose(geometry_msgs::Pose& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_Pose(MDFactory_T& factory, const geometry_msgs::PoseStamped::_pose_type& val);
  void copy_from_arr_geometry_msgs_Point(geometry_msgs::Point& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_Point(MDFactory_T& factory, const geometry_msgs::Pose::_position_type& val);
  void copy_from_arr_geometry_msgs_Quaternion(geometry_msgs::Quaternion& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_Quaternion(MDFactory_T& factory, const geometry_msgs::Pose::_orientation_type& val);
  void copy_from_arr_geometry_msgs_TwistStamped(geometry_msgs::TwistStamped& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_TwistStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_twist_type& val);
  void copy_from_arr_geometry_msgs_Twist(geometry_msgs::Twist& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_Twist(MDFactory_T& factory, const geometry_msgs::TwistStamped::_twist_type& val);
  void copy_from_arr_geometry_msgs_Vector3(geometry_msgs::Vector3& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_Vector3(MDFactory_T& factory, const geometry_msgs::Twist::_linear_type& val);
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_PoseStamped(geometry_msgs::PoseStamped& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_PoseStamped.header
    try {
        const matlab::data::StructArray _poseheader_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(val.header,_poseheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _geometry_msgs_PoseStamped.pose
    try {
        const matlab::data::StructArray _posepose_arr = arr[0]["pose"];
        copy_from_arr_geometry_msgs_Pose(val.pose,_posepose_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pose' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'pose' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_PoseStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_pose_type& val) {
    auto _poseoutArray = factory.createStructArray({1,1},{"header","pose"});
    // _geometry_msgs_PoseStamped.header
    _poseoutArray[0]["header"] = get_arr_std_msgs_Header(factory, val.header);
    // _geometry_msgs_PoseStamped.pose
    _poseoutArray[0]["pose"] = get_arr_geometry_msgs_Pose(factory, val.pose);
    return std::move(_poseoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr) {
    // _std_msgs_Header.seq
    try {
        const matlab::data::TypedArray<uint32_t> _pose_headerseq_arr = arr[0]["seq"];
        val.seq = _pose_headerseq_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'seq' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'seq' is wrong type; expected a uint32.");
    }
    // _std_msgs_Header.stamp
    try {
        const matlab::data::StructArray _pose_headerstamp_arr = arr[0]["stamp"];
        copy_from_arr_ros_Time(val.stamp,_pose_headerstamp_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stamp' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stamp' is wrong type; expected a struct.");
    }
    // _std_msgs_Header.frame_id
    try {
        const matlab::data::CharArray _pose_headerframe_id_arr = arr[0]["frame_id"];
        val.frame_id = _pose_headerframe_id_arr.toAscii();
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'frame_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'frame_id' is wrong type; expected a string.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const geometry_msgs::PoseStamped::_header_type& val) {
    auto _pose_headeroutArray = factory.createStructArray({1,1},{"seq","stamp","frame_id"});
    // _std_msgs_Header.seq
    _pose_headeroutArray[0]["seq"] = factory.createScalar(val.seq);
    // _std_msgs_Header.stamp
    _pose_headeroutArray[0]["stamp"] = get_arr_ros_Time(factory, val.stamp);
    // _std_msgs_Header.frame_id
    _pose_headeroutArray[0]["frame_id"] = factory.createCharArray(val.frame_id);
    return std::move(_pose_headeroutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr) {
    // _ros_Time.sec
    try {
        const matlab::data::TypedArray<uint32_t> _pose_header_stampsec_arr = arr[0]["sec"];
        val.sec = _pose_header_stampsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'sec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'sec' is wrong type; expected a uint32.");
    }
    // _ros_Time.nsec
    try {
        const matlab::data::TypedArray<uint32_t> _pose_header_stampnsec_arr = arr[0]["nsec"];
        val.nsec = _pose_header_stampnsec_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'nsec' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'nsec' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val) {
    auto _pose_header_stampoutArray = factory.createStructArray({1,1},{"sec","nsec"});
    // _ros_Time.sec
    _pose_header_stampoutArray[0]["sec"] = factory.createScalar(val.sec);
    // _ros_Time.nsec
    _pose_header_stampoutArray[0]["nsec"] = factory.createScalar(val.nsec);
    return std::move(_pose_header_stampoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Pose(geometry_msgs::Pose& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Pose.position
    try {
        const matlab::data::StructArray _pose_poseposition_arr = arr[0]["position"];
        copy_from_arr_geometry_msgs_Point(val.position,_pose_poseposition_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a struct.");
    }
    // _geometry_msgs_Pose.orientation
    try {
        const matlab::data::StructArray _pose_poseorientation_arr = arr[0]["orientation"];
        copy_from_arr_geometry_msgs_Quaternion(val.orientation,_pose_poseorientation_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'orientation' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'orientation' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Pose(MDFactory_T& factory, const geometry_msgs::PoseStamped::_pose_type& val) {
    auto _pose_poseoutArray = factory.createStructArray({1,1},{"position","orientation"});
    // _geometry_msgs_Pose.position
    _pose_poseoutArray[0]["position"] = get_arr_geometry_msgs_Point(factory, val.position);
    // _geometry_msgs_Pose.orientation
    _pose_poseoutArray[0]["orientation"] = get_arr_geometry_msgs_Quaternion(factory, val.orientation);
    return std::move(_pose_poseoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Point(geometry_msgs::Point& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Point.x
    try {
        const matlab::data::TypedArray<double> _pose_pose_positionx_arr = arr[0]["x"];
        val.x = _pose_pose_positionx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a double.");
    }
    // _geometry_msgs_Point.y
    try {
        const matlab::data::TypedArray<double> _pose_pose_positiony_arr = arr[0]["y"];
        val.y = _pose_pose_positiony_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a double.");
    }
    // _geometry_msgs_Point.z
    try {
        const matlab::data::TypedArray<double> _pose_pose_positionz_arr = arr[0]["z"];
        val.z = _pose_pose_positionz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Point(MDFactory_T& factory, const geometry_msgs::Pose::_position_type& val) {
    auto _pose_pose_positionoutArray = factory.createStructArray({1,1},{"x","y","z"});
    // _geometry_msgs_Point.x
    _pose_pose_positionoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Point.y
    _pose_pose_positionoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Point.z
    _pose_pose_positionoutArray[0]["z"] = factory.createScalar(val.z);
    return std::move(_pose_pose_positionoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Quaternion(geometry_msgs::Quaternion& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Quaternion.x
    try {
        const matlab::data::TypedArray<double> _pose_pose_orientationx_arr = arr[0]["x"];
        val.x = _pose_pose_orientationx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a double.");
    }
    // _geometry_msgs_Quaternion.y
    try {
        const matlab::data::TypedArray<double> _pose_pose_orientationy_arr = arr[0]["y"];
        val.y = _pose_pose_orientationy_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a double.");
    }
    // _geometry_msgs_Quaternion.z
    try {
        const matlab::data::TypedArray<double> _pose_pose_orientationz_arr = arr[0]["z"];
        val.z = _pose_pose_orientationz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a double.");
    }
    // _geometry_msgs_Quaternion.w
    try {
        const matlab::data::TypedArray<double> _pose_pose_orientationw_arr = arr[0]["w"];
        val.w = _pose_pose_orientationw_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'w' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'w' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Quaternion(MDFactory_T& factory, const geometry_msgs::Pose::_orientation_type& val) {
    auto _pose_pose_orientationoutArray = factory.createStructArray({1,1},{"x","y","z","w"});
    // _geometry_msgs_Quaternion.x
    _pose_pose_orientationoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Quaternion.y
    _pose_pose_orientationoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Quaternion.z
    _pose_pose_orientationoutArray[0]["z"] = factory.createScalar(val.z);
    // _geometry_msgs_Quaternion.w
    _pose_pose_orientationoutArray[0]["w"] = factory.createScalar(val.w);
    return std::move(_pose_pose_orientationoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_TwistStamped(geometry_msgs::TwistStamped& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_TwistStamped.header
    try {
        const matlab::data::StructArray _twistheader_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(val.header,_twistheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _geometry_msgs_TwistStamped.twist
    try {
        const matlab::data::StructArray _twisttwist_arr = arr[0]["twist"];
        copy_from_arr_geometry_msgs_Twist(val.twist,_twisttwist_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'twist' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'twist' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_TwistStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_twist_type& val) {
    auto _twistoutArray = factory.createStructArray({1,1},{"header","twist"});
    // _geometry_msgs_TwistStamped.header
    _twistoutArray[0]["header"] = get_arr_std_msgs_Header(factory, val.header);
    // _geometry_msgs_TwistStamped.twist
    _twistoutArray[0]["twist"] = get_arr_geometry_msgs_Twist(factory, val.twist);
    return std::move(_twistoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Twist(geometry_msgs::Twist& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Twist.linear
    try {
        const matlab::data::StructArray _twist_twistlinear_arr = arr[0]["linear"];
        copy_from_arr_geometry_msgs_Vector3(val.linear,_twist_twistlinear_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'linear' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'linear' is wrong type; expected a struct.");
    }
    // _geometry_msgs_Twist.angular
    try {
        const matlab::data::StructArray _twist_twistangular_arr = arr[0]["angular"];
        copy_from_arr_geometry_msgs_Vector3(val.angular,_twist_twistangular_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angular' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'angular' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Twist(MDFactory_T& factory, const geometry_msgs::TwistStamped::_twist_type& val) {
    auto _twist_twistoutArray = factory.createStructArray({1,1},{"linear","angular"});
    // _geometry_msgs_Twist.linear
    _twist_twistoutArray[0]["linear"] = get_arr_geometry_msgs_Vector3(factory, val.linear);
    // _geometry_msgs_Twist.angular
    _twist_twistoutArray[0]["angular"] = get_arr_geometry_msgs_Vector3(factory, val.angular);
    return std::move(_twist_twistoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Vector3(geometry_msgs::Vector3& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Vector3.x
    try {
        const matlab::data::TypedArray<double> _twist_twist_linearx_arr = arr[0]["x"];
        val.x = _twist_twist_linearx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a double.");
    }
    // _geometry_msgs_Vector3.y
    try {
        const matlab::data::TypedArray<double> _twist_twist_lineary_arr = arr[0]["y"];
        val.y = _twist_twist_lineary_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a double.");
    }
    // _geometry_msgs_Vector3.z
    try {
        const matlab::data::TypedArray<double> _twist_twist_linearz_arr = arr[0]["z"];
        val.z = _twist_twist_linearz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Vector3(MDFactory_T& factory, const geometry_msgs::Twist::_linear_type& val) {
    auto _twist_twist_linearoutArray = factory.createStructArray({1,1},{"x","y","z"});
    // _geometry_msgs_Vector3.x
    _twist_twist_linearoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Vector3.y
    _twist_twist_linearoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Vector3.z
    _twist_twist_linearoutArray[0]["z"] = factory.createScalar(val.z);
    return std::move(_twist_twist_linearoutArray);
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::Waypoint>& msg, const matlab::data::StructArray arr) {
    try {
        //gid
        const matlab::data::TypedArray<int32_t> gid_arr = arr[0]["gid"];
        msg->gid = gid_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gid' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gid' is wrong type; expected a int32.");
    }
    try {
        //lid
        const matlab::data::TypedArray<int32_t> lid_arr = arr[0]["lid"];
        msg->lid = lid_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lid' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lid' is wrong type; expected a int32.");
    }
    try {
        //pose
        const matlab::data::StructArray pose_arr = arr[0]["pose"];
        copy_from_arr_geometry_msgs_PoseStamped(msg->pose,pose_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pose' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'pose' is wrong type; expected a struct.");
    }
    try {
        //twist
        const matlab::data::StructArray twist_arr = arr[0]["twist"];
        copy_from_arr_geometry_msgs_TwistStamped(msg->twist,twist_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'twist' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'twist' is wrong type; expected a struct.");
    }
    try {
        //lane_id
        const matlab::data::TypedArray<uint32_t> lane_id_arr = arr[0]["lane_id"];
        msg->lane_id = lane_id_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lane_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lane_id' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::Waypoint>& msg) {
    auto outArray = factory.createStructArray({1,1},{"gid","lid","pose","twist","lane_id"});
    // gid
    outArray[0]["gid"] = factory.createScalar(msg->gid);
    // lid
    outArray[0]["lid"] = factory.createScalar(msg->lid);
    // pose
    outArray[0]["pose"] = get_arr_geometry_msgs_PoseStamped(factory, msg->pose);
    // twist
    outArray[0]["twist"] = get_arr_geometry_msgs_TwistStamped(factory, msg->twist);
    // lane_id
    outArray[0]["lane_id"] = factory.createScalar(msg->lane_id);
    return std::move(outArray);
  }
} //namespace Waypoint
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1