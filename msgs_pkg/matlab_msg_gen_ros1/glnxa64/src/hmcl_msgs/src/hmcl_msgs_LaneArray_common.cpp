// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/LaneArray
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
#include "hmcl_msgs/LaneArray.h"
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
namespace LaneArray {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const hmcl_msgs::LaneArray::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_hmcl_msgs_Lane_var_arr(hmcl_msgs::Lane& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_hmcl_msgs_Lane_var_arr(MDFactory_T& factory, const hmcl_msgs::LaneArray::_lanes_type& val);
  void copy_from_arr_hmcl_msgs_Waypoint_var_arr(hmcl_msgs::Waypoint& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_hmcl_msgs_Waypoint_var_arr(MDFactory_T& factory, const hmcl_msgs::Lane::_waypoints_type& val);
  void copy_from_arr_geometry_msgs_PoseStamped(geometry_msgs::PoseStamped& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_PoseStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_pose_type& val);
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
  void copy_from_arr_hmcl_msgs_Trafficlight_var_arr(hmcl_msgs::Trafficlight& val, const matlab::data::Struct& arr);
  MDArray_T get_arr_hmcl_msgs_Trafficlight_var_arr(MDFactory_T& factory, const hmcl_msgs::Lane::_trafficlights_type& val);
  void copy_from_arr_geometry_msgs_Point32(geometry_msgs::Point32& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_geometry_msgs_Point32(MDFactory_T& factory, const hmcl_msgs::Trafficlight::_pose_type& val);
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
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const hmcl_msgs::LaneArray::_header_type& val) {
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
  void copy_from_arr_hmcl_msgs_Lane_var_arr(hmcl_msgs::Lane& val, const matlab::data::Struct& arr) {
    // _hmcl_msgs_Lane_var_arr.header
    try {
        const matlab::data::StructArray _lanesheader_arr = arr["header"];
        copy_from_arr_std_msgs_Header(val.header,_lanesheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Lane_var_arr.lane_id
    try {
        const matlab::data::TypedArray<int32_t> _laneslane_id_arr = arr["lane_id"];
        val.lane_id = _laneslane_id_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lane_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lane_id' is wrong type; expected a int32.");
    }
    // _hmcl_msgs_Lane_var_arr.lane_change_flag
    try {
        const matlab::data::TypedArray<bool> _laneslane_change_flag_arr = arr["lane_change_flag"];
        val.lane_change_flag = _laneslane_change_flag_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lane_change_flag' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lane_change_flag' is wrong type; expected a logical.");
    }
    // _hmcl_msgs_Lane_var_arr.speed_limit
    try {
        const matlab::data::TypedArray<float> _lanesspeed_limit_arr = arr["speed_limit"];
        val.speed_limit = _lanesspeed_limit_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speed_limit' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'speed_limit' is wrong type; expected a single.");
    }
    // _hmcl_msgs_Lane_var_arr.waypoints
    try {
        const matlab::data::StructArray _laneswaypoints_arr = arr["waypoints"];
        for (auto _waypointsarr : _laneswaypoints_arr) {
        	hmcl_msgs::Waypoint _val;
        	copy_from_arr_hmcl_msgs_Waypoint_var_arr(_val,_waypointsarr);
        	val.waypoints.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'waypoints' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'waypoints' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Lane_var_arr.trafficlights
    try {
        const matlab::data::StructArray _lanestrafficlights_arr = arr["trafficlights"];
        for (auto _trafficlightsarr : _lanestrafficlights_arr) {
        	hmcl_msgs::Trafficlight _val;
        	copy_from_arr_hmcl_msgs_Trafficlight_var_arr(_val,_trafficlightsarr);
        	val.trafficlights.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'trafficlights' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'trafficlights' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Lane_var_arr.speedbumps
    try {
        const matlab::data::StructArray _lanesspeedbumps_arr = arr["speedbumps"];
        for (auto _speedbumpsarr : _lanesspeedbumps_arr) {
        	hmcl_msgs::Waypoint _val;
        	copy_from_arr_hmcl_msgs_Waypoint_var_arr(_val,_speedbumpsarr);
        	val.speedbumps.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'speedbumps' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'speedbumps' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_Lane_var_arr(MDFactory_T& factory, const hmcl_msgs::LaneArray::_lanes_type& val) {
    auto _lanesoutArray = factory.createStructArray({1,val.size()},{"header","lane_id","lane_change_flag","speed_limit","waypoints","trafficlights","speedbumps"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _hmcl_msgs_Lane_var_arr.header
    _lanesoutArray[idx]["header"] = get_arr_std_msgs_Header(factory, val[idx].header);
    // _hmcl_msgs_Lane_var_arr.lane_id
    	_lanesoutArray[idx]["lane_id"] = factory.createScalar(val[idx].lane_id);
    // _hmcl_msgs_Lane_var_arr.lane_change_flag
    	_lanesoutArray[idx]["lane_change_flag"] = factory.createScalar(static_cast<bool>(val[idx].lane_change_flag));
    // _hmcl_msgs_Lane_var_arr.speed_limit
    	_lanesoutArray[idx]["speed_limit"] = factory.createScalar(val[idx].speed_limit);
    // _hmcl_msgs_Lane_var_arr.waypoints
    _lanesoutArray[idx]["waypoints"] = get_arr_hmcl_msgs_Waypoint_var_arr(factory, val[idx].waypoints);
    // _hmcl_msgs_Lane_var_arr.trafficlights
    _lanesoutArray[idx]["trafficlights"] = get_arr_hmcl_msgs_Trafficlight_var_arr(factory, val[idx].trafficlights);
    // _hmcl_msgs_Lane_var_arr.speedbumps
    _lanesoutArray[idx]["speedbumps"] = get_arr_hmcl_msgs_Waypoint_var_arr(factory, val[idx].speedbumps);
    }
    return std::move(_lanesoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_Waypoint_var_arr(hmcl_msgs::Waypoint& val, const matlab::data::Struct& arr) {
    // _hmcl_msgs_Waypoint_var_arr.gid
    try {
        const matlab::data::TypedArray<int32_t> _lanes_waypointsgid_arr = arr["gid"];
        val.gid = _lanes_waypointsgid_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gid' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gid' is wrong type; expected a int32.");
    }
    // _hmcl_msgs_Waypoint_var_arr.lid
    try {
        const matlab::data::TypedArray<int32_t> _lanes_waypointslid_arr = arr["lid"];
        val.lid = _lanes_waypointslid_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lid' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lid' is wrong type; expected a int32.");
    }
    // _hmcl_msgs_Waypoint_var_arr.pose
    try {
        const matlab::data::StructArray _lanes_waypointspose_arr = arr["pose"];
        copy_from_arr_geometry_msgs_PoseStamped(val.pose,_lanes_waypointspose_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pose' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'pose' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Waypoint_var_arr.twist
    try {
        const matlab::data::StructArray _lanes_waypointstwist_arr = arr["twist"];
        copy_from_arr_geometry_msgs_TwistStamped(val.twist,_lanes_waypointstwist_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'twist' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'twist' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Waypoint_var_arr.lane_id
    try {
        const matlab::data::TypedArray<uint32_t> _lanes_waypointslane_id_arr = arr["lane_id"];
        val.lane_id = _lanes_waypointslane_id_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lane_id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lane_id' is wrong type; expected a uint32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_Waypoint_var_arr(MDFactory_T& factory, const hmcl_msgs::Lane::_waypoints_type& val) {
    auto _lanes_waypointsoutArray = factory.createStructArray({1,val.size()},{"gid","lid","pose","twist","lane_id"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _hmcl_msgs_Waypoint_var_arr.gid
    	_lanes_waypointsoutArray[idx]["gid"] = factory.createScalar(val[idx].gid);
    // _hmcl_msgs_Waypoint_var_arr.lid
    	_lanes_waypointsoutArray[idx]["lid"] = factory.createScalar(val[idx].lid);
    // _hmcl_msgs_Waypoint_var_arr.pose
    _lanes_waypointsoutArray[idx]["pose"] = get_arr_geometry_msgs_PoseStamped(factory, val[idx].pose);
    // _hmcl_msgs_Waypoint_var_arr.twist
    _lanes_waypointsoutArray[idx]["twist"] = get_arr_geometry_msgs_TwistStamped(factory, val[idx].twist);
    // _hmcl_msgs_Waypoint_var_arr.lane_id
    	_lanes_waypointsoutArray[idx]["lane_id"] = factory.createScalar(val[idx].lane_id);
    }
    return std::move(_lanes_waypointsoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_PoseStamped(geometry_msgs::PoseStamped& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_PoseStamped.header
    try {
        const matlab::data::StructArray _lanes_waypoints_poseheader_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(val.header,_lanes_waypoints_poseheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _geometry_msgs_PoseStamped.pose
    try {
        const matlab::data::StructArray _lanes_waypoints_posepose_arr = arr[0]["pose"];
        copy_from_arr_geometry_msgs_Pose(val.pose,_lanes_waypoints_posepose_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pose' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'pose' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_PoseStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_pose_type& val) {
    auto _lanes_waypoints_poseoutArray = factory.createStructArray({1,1},{"header","pose"});
    // _geometry_msgs_PoseStamped.header
    _lanes_waypoints_poseoutArray[0]["header"] = get_arr_std_msgs_Header(factory, val.header);
    // _geometry_msgs_PoseStamped.pose
    _lanes_waypoints_poseoutArray[0]["pose"] = get_arr_geometry_msgs_Pose(factory, val.pose);
    return std::move(_lanes_waypoints_poseoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Pose(geometry_msgs::Pose& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Pose.position
    try {
        const matlab::data::StructArray _lanes_waypoints_pose_poseposition_arr = arr[0]["position"];
        copy_from_arr_geometry_msgs_Point(val.position,_lanes_waypoints_pose_poseposition_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a struct.");
    }
    // _geometry_msgs_Pose.orientation
    try {
        const matlab::data::StructArray _lanes_waypoints_pose_poseorientation_arr = arr[0]["orientation"];
        copy_from_arr_geometry_msgs_Quaternion(val.orientation,_lanes_waypoints_pose_poseorientation_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'orientation' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'orientation' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Pose(MDFactory_T& factory, const geometry_msgs::PoseStamped::_pose_type& val) {
    auto _lanes_waypoints_pose_poseoutArray = factory.createStructArray({1,1},{"position","orientation"});
    // _geometry_msgs_Pose.position
    _lanes_waypoints_pose_poseoutArray[0]["position"] = get_arr_geometry_msgs_Point(factory, val.position);
    // _geometry_msgs_Pose.orientation
    _lanes_waypoints_pose_poseoutArray[0]["orientation"] = get_arr_geometry_msgs_Quaternion(factory, val.orientation);
    return std::move(_lanes_waypoints_pose_poseoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Point(geometry_msgs::Point& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Point.x
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_positionx_arr = arr[0]["x"];
        val.x = _lanes_waypoints_pose_pose_positionx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a double.");
    }
    // _geometry_msgs_Point.y
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_positiony_arr = arr[0]["y"];
        val.y = _lanes_waypoints_pose_pose_positiony_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a double.");
    }
    // _geometry_msgs_Point.z
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_positionz_arr = arr[0]["z"];
        val.z = _lanes_waypoints_pose_pose_positionz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Point(MDFactory_T& factory, const geometry_msgs::Pose::_position_type& val) {
    auto _lanes_waypoints_pose_pose_positionoutArray = factory.createStructArray({1,1},{"x","y","z"});
    // _geometry_msgs_Point.x
    _lanes_waypoints_pose_pose_positionoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Point.y
    _lanes_waypoints_pose_pose_positionoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Point.z
    _lanes_waypoints_pose_pose_positionoutArray[0]["z"] = factory.createScalar(val.z);
    return std::move(_lanes_waypoints_pose_pose_positionoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Quaternion(geometry_msgs::Quaternion& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Quaternion.x
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_orientationx_arr = arr[0]["x"];
        val.x = _lanes_waypoints_pose_pose_orientationx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a double.");
    }
    // _geometry_msgs_Quaternion.y
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_orientationy_arr = arr[0]["y"];
        val.y = _lanes_waypoints_pose_pose_orientationy_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a double.");
    }
    // _geometry_msgs_Quaternion.z
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_orientationz_arr = arr[0]["z"];
        val.z = _lanes_waypoints_pose_pose_orientationz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a double.");
    }
    // _geometry_msgs_Quaternion.w
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_pose_pose_orientationw_arr = arr[0]["w"];
        val.w = _lanes_waypoints_pose_pose_orientationw_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'w' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'w' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Quaternion(MDFactory_T& factory, const geometry_msgs::Pose::_orientation_type& val) {
    auto _lanes_waypoints_pose_pose_orientationoutArray = factory.createStructArray({1,1},{"x","y","z","w"});
    // _geometry_msgs_Quaternion.x
    _lanes_waypoints_pose_pose_orientationoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Quaternion.y
    _lanes_waypoints_pose_pose_orientationoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Quaternion.z
    _lanes_waypoints_pose_pose_orientationoutArray[0]["z"] = factory.createScalar(val.z);
    // _geometry_msgs_Quaternion.w
    _lanes_waypoints_pose_pose_orientationoutArray[0]["w"] = factory.createScalar(val.w);
    return std::move(_lanes_waypoints_pose_pose_orientationoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_TwistStamped(geometry_msgs::TwistStamped& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_TwistStamped.header
    try {
        const matlab::data::StructArray _lanes_waypoints_twistheader_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(val.header,_lanes_waypoints_twistheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _geometry_msgs_TwistStamped.twist
    try {
        const matlab::data::StructArray _lanes_waypoints_twisttwist_arr = arr[0]["twist"];
        copy_from_arr_geometry_msgs_Twist(val.twist,_lanes_waypoints_twisttwist_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'twist' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'twist' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_TwistStamped(MDFactory_T& factory, const hmcl_msgs::Waypoint::_twist_type& val) {
    auto _lanes_waypoints_twistoutArray = factory.createStructArray({1,1},{"header","twist"});
    // _geometry_msgs_TwistStamped.header
    _lanes_waypoints_twistoutArray[0]["header"] = get_arr_std_msgs_Header(factory, val.header);
    // _geometry_msgs_TwistStamped.twist
    _lanes_waypoints_twistoutArray[0]["twist"] = get_arr_geometry_msgs_Twist(factory, val.twist);
    return std::move(_lanes_waypoints_twistoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Twist(geometry_msgs::Twist& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Twist.linear
    try {
        const matlab::data::StructArray _lanes_waypoints_twist_twistlinear_arr = arr[0]["linear"];
        copy_from_arr_geometry_msgs_Vector3(val.linear,_lanes_waypoints_twist_twistlinear_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'linear' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'linear' is wrong type; expected a struct.");
    }
    // _geometry_msgs_Twist.angular
    try {
        const matlab::data::StructArray _lanes_waypoints_twist_twistangular_arr = arr[0]["angular"];
        copy_from_arr_geometry_msgs_Vector3(val.angular,_lanes_waypoints_twist_twistangular_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angular' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'angular' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Twist(MDFactory_T& factory, const geometry_msgs::TwistStamped::_twist_type& val) {
    auto _lanes_waypoints_twist_twistoutArray = factory.createStructArray({1,1},{"linear","angular"});
    // _geometry_msgs_Twist.linear
    _lanes_waypoints_twist_twistoutArray[0]["linear"] = get_arr_geometry_msgs_Vector3(factory, val.linear);
    // _geometry_msgs_Twist.angular
    _lanes_waypoints_twist_twistoutArray[0]["angular"] = get_arr_geometry_msgs_Vector3(factory, val.angular);
    return std::move(_lanes_waypoints_twist_twistoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Vector3(geometry_msgs::Vector3& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Vector3.x
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_twist_twist_linearx_arr = arr[0]["x"];
        val.x = _lanes_waypoints_twist_twist_linearx_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a double.");
    }
    // _geometry_msgs_Vector3.y
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_twist_twist_lineary_arr = arr[0]["y"];
        val.y = _lanes_waypoints_twist_twist_lineary_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a double.");
    }
    // _geometry_msgs_Vector3.z
    try {
        const matlab::data::TypedArray<double> _lanes_waypoints_twist_twist_linearz_arr = arr[0]["z"];
        val.z = _lanes_waypoints_twist_twist_linearz_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Vector3(MDFactory_T& factory, const geometry_msgs::Twist::_linear_type& val) {
    auto _lanes_waypoints_twist_twist_linearoutArray = factory.createStructArray({1,1},{"x","y","z"});
    // _geometry_msgs_Vector3.x
    _lanes_waypoints_twist_twist_linearoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Vector3.y
    _lanes_waypoints_twist_twist_linearoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Vector3.z
    _lanes_waypoints_twist_twist_linearoutArray[0]["z"] = factory.createScalar(val.z);
    return std::move(_lanes_waypoints_twist_twist_linearoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_Trafficlight_var_arr(hmcl_msgs::Trafficlight& val, const matlab::data::Struct& arr) {
    // _hmcl_msgs_Trafficlight_var_arr.header
    try {
        const matlab::data::StructArray _lanes_trafficlightsheader_arr = arr["header"];
        copy_from_arr_std_msgs_Header(val.header,_lanes_trafficlightsheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Trafficlight_var_arr.id
    try {
        const matlab::data::TypedArray<int32_t> _lanes_trafficlightsid_arr = arr["id"];
        val.id = _lanes_trafficlightsid_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'id' is wrong type; expected a int32.");
    }
    // _hmcl_msgs_Trafficlight_var_arr.pose
    try {
        const matlab::data::StructArray _lanes_trafficlightspose_arr = arr["pose"];
        copy_from_arr_geometry_msgs_Point32(val.pose,_lanes_trafficlightspose_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pose' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'pose' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_Trafficlight_var_arr.valid_stop_line
    try {
        const matlab::data::TypedArray<bool> _lanes_trafficlightsvalid_stop_line_arr = arr["valid_stop_line"];
        val.valid_stop_line = _lanes_trafficlightsvalid_stop_line_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'valid_stop_line' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'valid_stop_line' is wrong type; expected a logical.");
    }
    // _hmcl_msgs_Trafficlight_var_arr.stop_line
    try {
        const matlab::data::StructArray _lanes_trafficlightsstop_line_arr = arr["stop_line"];
        copy_from_arr_geometry_msgs_Point32(val.stop_line,_lanes_trafficlightsstop_line_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'stop_line' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'stop_line' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_Trafficlight_var_arr(MDFactory_T& factory, const hmcl_msgs::Lane::_trafficlights_type& val) {
    auto _lanes_trafficlightsoutArray = factory.createStructArray({1,val.size()},{"header","id","pose","valid_stop_line","stop_line"});
    for (size_t idx = 0; idx < val.size(); ++idx){
    // _hmcl_msgs_Trafficlight_var_arr.header
    _lanes_trafficlightsoutArray[idx]["header"] = get_arr_std_msgs_Header(factory, val[idx].header);
    // _hmcl_msgs_Trafficlight_var_arr.id
    	_lanes_trafficlightsoutArray[idx]["id"] = factory.createScalar(val[idx].id);
    // _hmcl_msgs_Trafficlight_var_arr.pose
    _lanes_trafficlightsoutArray[idx]["pose"] = get_arr_geometry_msgs_Point32(factory, val[idx].pose);
    // _hmcl_msgs_Trafficlight_var_arr.valid_stop_line
    	_lanes_trafficlightsoutArray[idx]["valid_stop_line"] = factory.createScalar(static_cast<bool>(val[idx].valid_stop_line));
    // _hmcl_msgs_Trafficlight_var_arr.stop_line
    _lanes_trafficlightsoutArray[idx]["stop_line"] = get_arr_geometry_msgs_Point32(factory, val[idx].stop_line);
    }
    return std::move(_lanes_trafficlightsoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_geometry_msgs_Point32(geometry_msgs::Point32& val, const matlab::data::StructArray& arr) {
    // _geometry_msgs_Point32.x
    try {
        const matlab::data::TypedArray<float> _lanes_trafficlights_posex_arr = arr[0]["x"];
        val.x = _lanes_trafficlights_posex_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a single.");
    }
    // _geometry_msgs_Point32.y
    try {
        const matlab::data::TypedArray<float> _lanes_trafficlights_posey_arr = arr[0]["y"];
        val.y = _lanes_trafficlights_posey_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a single.");
    }
    // _geometry_msgs_Point32.z
    try {
        const matlab::data::TypedArray<float> _lanes_trafficlights_posez_arr = arr[0]["z"];
        val.z = _lanes_trafficlights_posez_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'z' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'z' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_geometry_msgs_Point32(MDFactory_T& factory, const hmcl_msgs::Trafficlight::_pose_type& val) {
    auto _lanes_trafficlights_poseoutArray = factory.createStructArray({1,1},{"x","y","z"});
    // _geometry_msgs_Point32.x
    _lanes_trafficlights_poseoutArray[0]["x"] = factory.createScalar(val.x);
    // _geometry_msgs_Point32.y
    _lanes_trafficlights_poseoutArray[0]["y"] = factory.createScalar(val.y);
    // _geometry_msgs_Point32.z
    _lanes_trafficlights_poseoutArray[0]["z"] = factory.createScalar(val.z);
    return std::move(_lanes_trafficlights_poseoutArray);
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::LaneArray>& msg, const matlab::data::StructArray arr) {
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
        //id
        const matlab::data::TypedArray<int32_t> id_arr = arr[0]["id"];
        msg->id = id_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'id' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'id' is wrong type; expected a int32.");
    }
    try {
        //lanes
        const matlab::data::StructArray lanes_arr = arr[0]["lanes"];
        for (auto _lanesarr : lanes_arr) {
        	hmcl_msgs::Lane _val;
        	copy_from_arr_hmcl_msgs_Lane_var_arr(_val,_lanesarr);
        	msg->lanes.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'lanes' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'lanes' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::LaneArray>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","id","lanes"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // id
    outArray[0]["id"] = factory.createScalar(msg->id);
    // lanes
    outArray[0]["lanes"] = get_arr_hmcl_msgs_Lane_var_arr(factory, msg->lanes);
    return std::move(outArray);
  }
} //namespace LaneArray
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1