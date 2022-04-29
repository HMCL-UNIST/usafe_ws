// Copyright 2019-2020 The MathWorks, Inc.
// Common copy functions for hmcl_msgs/VehicleStatus
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
#include "hmcl_msgs/VehicleStatus.h"
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
namespace VehicleStatus {
  void copy_from_arr_std_msgs_Header(std_msgs::Header& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_header_type& val);
  void copy_from_arr_ros_Time(ros::Time& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_ros_Time(MDFactory_T& factory, const std_msgs::Header::_stamp_type& val);
  void copy_from_arr_hmcl_msgs_VehicleSteering(hmcl_msgs::VehicleSteering& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_hmcl_msgs_VehicleSteering(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_steering_info_type& val);
  void copy_from_arr_hmcl_msgs_VehicleSCC(hmcl_msgs::VehicleSCC& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_hmcl_msgs_VehicleSCC(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_scc_info_type& val);
  void copy_from_arr_hmcl_msgs_VehicleWheelSpeed(hmcl_msgs::VehicleWheelSpeed& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_hmcl_msgs_VehicleWheelSpeed(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_wheelspeed_type& val);
  void copy_from_arr_hmcl_msgs_VehicleGear(hmcl_msgs::VehicleGear& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_hmcl_msgs_VehicleGear(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_gear_info_type& val);
  void copy_from_arr_hmcl_msgs_VehicleLight(hmcl_msgs::VehicleLight& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_hmcl_msgs_VehicleLight(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_light_info_type& val);
  void copy_from_arr_hmcl_msgs_RemoteButton(hmcl_msgs::RemoteButton& val, const matlab::data::StructArray& arr);
  MDArray_T get_arr_hmcl_msgs_RemoteButton(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_remote_button_info_type& val);
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
  MDArray_T get_arr_std_msgs_Header(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_header_type& val) {
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
  void copy_from_arr_hmcl_msgs_VehicleSteering(hmcl_msgs::VehicleSteering& val, const matlab::data::StructArray& arr) {
    // _hmcl_msgs_VehicleSteering.takeover
    try {
        const matlab::data::TypedArray<uint8_t> _steering_infotakeover_arr = arr[0]["takeover"];
        val.takeover = _steering_infotakeover_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'takeover' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'takeover' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_VehicleSteering.mode
    try {
        const matlab::data::TypedArray<uint8_t> _steering_infomode_arr = arr[0]["mode"];
        val.mode = _steering_infomode_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'mode' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'mode' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_VehicleSteering.steering_angle
    try {
        const matlab::data::TypedArray<float> _steering_infosteering_angle_arr = arr[0]["steering_angle"];
        val.steering_angle = _steering_infosteering_angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_angle' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_angle' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_VehicleSteering(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_steering_info_type& val) {
    auto _steering_infooutArray = factory.createStructArray({1,1},{"takeover","mode","steering_angle"});
    // _hmcl_msgs_VehicleSteering.takeover
    _steering_infooutArray[0]["takeover"] = factory.createScalar(val.takeover);
    // _hmcl_msgs_VehicleSteering.mode
    _steering_infooutArray[0]["mode"] = factory.createScalar(val.mode);
    // _hmcl_msgs_VehicleSteering.steering_angle
    _steering_infooutArray[0]["steering_angle"] = factory.createScalar(val.steering_angle);
    return std::move(_steering_infooutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_VehicleSCC(hmcl_msgs::VehicleSCC& val, const matlab::data::StructArray& arr) {
    // _hmcl_msgs_VehicleSCC.scc_mode
    try {
        const matlab::data::TypedArray<uint8_t> _scc_infoscc_mode_arr = arr[0]["scc_mode"];
        val.scc_mode = _scc_infoscc_mode_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'scc_mode' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'scc_mode' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_VehicleSCC.scc_takeover
    try {
        const matlab::data::TypedArray<uint8_t> _scc_infoscc_takeover_arr = arr[0]["scc_takeover"];
        val.scc_takeover = _scc_infoscc_takeover_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'scc_takeover' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'scc_takeover' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_VehicleSCC.acceleration
    try {
        const matlab::data::TypedArray<double> _scc_infoacceleration_arr = arr[0]["acceleration"];
        val.acceleration = _scc_infoacceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'acceleration' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'acceleration' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_VehicleSCC(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_scc_info_type& val) {
    auto _scc_infooutArray = factory.createStructArray({1,1},{"scc_mode","scc_takeover","acceleration"});
    // _hmcl_msgs_VehicleSCC.scc_mode
    _scc_infooutArray[0]["scc_mode"] = factory.createScalar(val.scc_mode);
    // _hmcl_msgs_VehicleSCC.scc_takeover
    _scc_infooutArray[0]["scc_takeover"] = factory.createScalar(val.scc_takeover);
    // _hmcl_msgs_VehicleSCC.acceleration
    _scc_infooutArray[0]["acceleration"] = factory.createScalar(val.acceleration);
    return std::move(_scc_infooutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_VehicleWheelSpeed(hmcl_msgs::VehicleWheelSpeed& val, const matlab::data::StructArray& arr) {
    // _hmcl_msgs_VehicleWheelSpeed.header
    try {
        const matlab::data::StructArray _wheelspeedheader_arr = arr[0]["header"];
        copy_from_arr_std_msgs_Header(val.header,_wheelspeedheader_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'header' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'header' is wrong type; expected a struct.");
    }
    // _hmcl_msgs_VehicleWheelSpeed.wheel_speed
    try {
        const matlab::data::TypedArray<double> _wheelspeedwheel_speed_arr = arr[0]["wheel_speed"];
        val.wheel_speed = _wheelspeedwheel_speed_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'wheel_speed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'wheel_speed' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_VehicleWheelSpeed(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_wheelspeed_type& val) {
    auto _wheelspeedoutArray = factory.createStructArray({1,1},{"header","wheel_speed"});
    // _hmcl_msgs_VehicleWheelSpeed.header
    _wheelspeedoutArray[0]["header"] = get_arr_std_msgs_Header(factory, val.header);
    // _hmcl_msgs_VehicleWheelSpeed.wheel_speed
    _wheelspeedoutArray[0]["wheel_speed"] = factory.createScalar(val.wheel_speed);
    return std::move(_wheelspeedoutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_VehicleGear(hmcl_msgs::VehicleGear& val, const matlab::data::StructArray& arr) {
    // _hmcl_msgs_VehicleGear.gear
    try {
        const matlab::data::TypedArray<uint8_t> _gear_infogear_arr = arr[0]["gear"];
        val.gear = _gear_infogear_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gear' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gear' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_VehicleGear(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_gear_info_type& val) {
    auto _gear_infooutArray = factory.createStructArray({1,1},{"gear"});
    // _hmcl_msgs_VehicleGear.gear
    _gear_infooutArray[0]["gear"] = factory.createScalar(val.gear);
    return std::move(_gear_infooutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_VehicleLight(hmcl_msgs::VehicleLight& val, const matlab::data::StructArray& arr) {
    // _hmcl_msgs_VehicleLight.left_light
    try {
        const matlab::data::TypedArray<uint8_t> _light_infoleft_light_arr = arr[0]["left_light"];
        val.left_light = _light_infoleft_light_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'left_light' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'left_light' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_VehicleLight.right_light
    try {
        const matlab::data::TypedArray<uint8_t> _light_inforight_light_arr = arr[0]["right_light"];
        val.right_light = _light_inforight_light_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'right_light' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'right_light' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_VehicleLight.hazard_light
    try {
        const matlab::data::TypedArray<uint8_t> _light_infohazard_light_arr = arr[0]["hazard_light"];
        val.hazard_light = _light_infohazard_light_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'hazard_light' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'hazard_light' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_VehicleLight(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_light_info_type& val) {
    auto _light_infooutArray = factory.createStructArray({1,1},{"left_light","right_light","hazard_light"});
    // _hmcl_msgs_VehicleLight.left_light
    _light_infooutArray[0]["left_light"] = factory.createScalar(val.left_light);
    // _hmcl_msgs_VehicleLight.right_light
    _light_infooutArray[0]["right_light"] = factory.createScalar(val.right_light);
    // _hmcl_msgs_VehicleLight.hazard_light
    _light_infooutArray[0]["hazard_light"] = factory.createScalar(val.hazard_light);
    return std::move(_light_infooutArray);
  }
  //----------------------------------------------------------------------------
  void copy_from_arr_hmcl_msgs_RemoteButton(hmcl_msgs::RemoteButton& val, const matlab::data::StructArray& arr) {
    // _hmcl_msgs_RemoteButton.button1
    try {
        const matlab::data::TypedArray<uint8_t> _remote_button_infobutton1_arr = arr[0]["button1"];
        val.button1 = _remote_button_infobutton1_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'button1' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'button1' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_RemoteButton.button2
    try {
        const matlab::data::TypedArray<uint8_t> _remote_button_infobutton2_arr = arr[0]["button2"];
        val.button2 = _remote_button_infobutton2_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'button2' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'button2' is wrong type; expected a uint8.");
    }
    // _hmcl_msgs_RemoteButton.button3
    try {
        const matlab::data::TypedArray<uint8_t> _remote_button_infobutton3_arr = arr[0]["button3"];
        val.button3 = _remote_button_infobutton3_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'button3' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'button3' is wrong type; expected a uint8.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T get_arr_hmcl_msgs_RemoteButton(MDFactory_T& factory, const hmcl_msgs::VehicleStatus::_remote_button_info_type& val) {
    auto _remote_button_infooutArray = factory.createStructArray({1,1},{"button1","button2","button3"});
    // _hmcl_msgs_RemoteButton.button1
    _remote_button_infooutArray[0]["button1"] = factory.createScalar(val.button1);
    // _hmcl_msgs_RemoteButton.button2
    _remote_button_infooutArray[0]["button2"] = factory.createScalar(val.button2);
    // _hmcl_msgs_RemoteButton.button3
    _remote_button_infooutArray[0]["button3"] = factory.createScalar(val.button3);
    return std::move(_remote_button_infooutArray);
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT void copy_from_arr(boost::shared_ptr<hmcl_msgs::VehicleStatus>& msg, const matlab::data::StructArray arr) {
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
        //steering_info
        const matlab::data::StructArray steering_info_arr = arr[0]["steering_info"];
        copy_from_arr_hmcl_msgs_VehicleSteering(msg->steering_info,steering_info_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'steering_info' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'steering_info' is wrong type; expected a struct.");
    }
    try {
        //scc_info
        const matlab::data::StructArray scc_info_arr = arr[0]["scc_info"];
        copy_from_arr_hmcl_msgs_VehicleSCC(msg->scc_info,scc_info_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'scc_info' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'scc_info' is wrong type; expected a struct.");
    }
    try {
        //wheelspeed
        const matlab::data::StructArray wheelspeed_arr = arr[0]["wheelspeed"];
        copy_from_arr_hmcl_msgs_VehicleWheelSpeed(msg->wheelspeed,wheelspeed_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'wheelspeed' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'wheelspeed' is wrong type; expected a struct.");
    }
    try {
        //gear_info
        const matlab::data::StructArray gear_info_arr = arr[0]["gear_info"];
        copy_from_arr_hmcl_msgs_VehicleGear(msg->gear_info,gear_info_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'gear_info' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'gear_info' is wrong type; expected a struct.");
    }
    try {
        //light_info
        const matlab::data::StructArray light_info_arr = arr[0]["light_info"];
        copy_from_arr_hmcl_msgs_VehicleLight(msg->light_info,light_info_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'light_info' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'light_info' is wrong type; expected a struct.");
    }
    try {
        //remote_button_info
        const matlab::data::StructArray remote_button_info_arr = arr[0]["remote_button_info"];
        copy_from_arr_hmcl_msgs_RemoteButton(msg->remote_button_info,remote_button_info_arr);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'remote_button_info' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'remote_button_info' is wrong type; expected a struct.");
    }
    try {
        //auto_mode
        const matlab::data::TypedArray<uint8_t> auto_mode_arr = arr[0]["auto_mode"];
        msg->auto_mode = auto_mode_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'auto_mode' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'auto_mode' is wrong type; expected a uint8.");
    }
    try {
        //ems_mode
        const matlab::data::TypedArray<uint8_t> ems_mode_arr = arr[0]["ems_mode"];
        msg->ems_mode = ems_mode_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'ems_mode' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'ems_mode' is wrong type; expected a uint8.");
    }
    try {
        //x_acceleration
        const matlab::data::TypedArray<double> x_acceleration_arr = arr[0]["x_acceleration"];
        msg->x_acceleration = x_acceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x_acceleration' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'x_acceleration' is wrong type; expected a double.");
    }
    try {
        //y_acceleration
        const matlab::data::TypedArray<double> y_acceleration_arr = arr[0]["y_acceleration"];
        msg->y_acceleration = y_acceleration_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y_acceleration' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'y_acceleration' is wrong type; expected a double.");
    }
    try {
        //yaw_rate
        const matlab::data::TypedArray<double> yaw_rate_arr = arr[0]["yaw_rate"];
        msg->yaw_rate = yaw_rate_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'yaw_rate' is missing.");
    } catch (matlab::data::TypeMismatchException&) {
        throw std::invalid_argument("Field 'yaw_rate' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  HMCL_MSGS_EXPORT MDArray_T get_arr(MDFactory_T& factory, const boost::shared_ptr<const hmcl_msgs::VehicleStatus>& msg) {
    auto outArray = factory.createStructArray({1,1},{"header","steering_info","scc_info","wheelspeed","gear_info","light_info","remote_button_info","auto_mode","ems_mode","x_acceleration","y_acceleration","yaw_rate"});
    // header
    outArray[0]["header"] = get_arr_std_msgs_Header(factory, msg->header);
    // steering_info
    outArray[0]["steering_info"] = get_arr_hmcl_msgs_VehicleSteering(factory, msg->steering_info);
    // scc_info
    outArray[0]["scc_info"] = get_arr_hmcl_msgs_VehicleSCC(factory, msg->scc_info);
    // wheelspeed
    outArray[0]["wheelspeed"] = get_arr_hmcl_msgs_VehicleWheelSpeed(factory, msg->wheelspeed);
    // gear_info
    outArray[0]["gear_info"] = get_arr_hmcl_msgs_VehicleGear(factory, msg->gear_info);
    // light_info
    outArray[0]["light_info"] = get_arr_hmcl_msgs_VehicleLight(factory, msg->light_info);
    // remote_button_info
    outArray[0]["remote_button_info"] = get_arr_hmcl_msgs_RemoteButton(factory, msg->remote_button_info);
    // auto_mode
    outArray[0]["auto_mode"] = factory.createScalar(msg->auto_mode);
    // ems_mode
    outArray[0]["ems_mode"] = factory.createScalar(msg->ems_mode);
    // x_acceleration
    outArray[0]["x_acceleration"] = factory.createScalar(msg->x_acceleration);
    // y_acceleration
    outArray[0]["y_acceleration"] = factory.createScalar(msg->y_acceleration);
    // yaw_rate
    outArray[0]["yaw_rate"] = factory.createScalar(msg->yaw_rate);
    return std::move(outArray);
  }
} //namespace VehicleStatus
} //namespace matlabhelper
} //namespace hmcl_msgs
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1