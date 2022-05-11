// Generated by gencpp from file hmcl_msgs/VehicleStatus.msg
// DO NOT EDIT!


#ifndef HMCL_MSGS_MESSAGE_VEHICLESTATUS_H
#define HMCL_MSGS_MESSAGE_VEHICLESTATUS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/VehicleSCC.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include <hmcl_msgs/VehicleGear.h>
#include <hmcl_msgs/VehicleLight.h>
#include <hmcl_msgs/RemoteButton.h>

namespace hmcl_msgs
{
template <class ContainerAllocator>
struct VehicleStatus_
{
  typedef VehicleStatus_<ContainerAllocator> Type;

  VehicleStatus_()
    : header()
    , steering_info()
    , scc_info()
    , wheelspeed()
    , gear_info()
    , light_info()
    , remote_button_info()
    , auto_mode(0)
    , ems_mode(0)
    , x_acceleration(0.0)
    , y_acceleration(0.0)
    , yaw_rate(0.0)  {
    }
  VehicleStatus_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , steering_info(_alloc)
    , scc_info(_alloc)
    , wheelspeed(_alloc)
    , gear_info(_alloc)
    , light_info(_alloc)
    , remote_button_info(_alloc)
    , auto_mode(0)
    , ems_mode(0)
    , x_acceleration(0.0)
    , y_acceleration(0.0)
    , yaw_rate(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::hmcl_msgs::VehicleSteering_<ContainerAllocator>  _steering_info_type;
  _steering_info_type steering_info;

   typedef  ::hmcl_msgs::VehicleSCC_<ContainerAllocator>  _scc_info_type;
  _scc_info_type scc_info;

   typedef  ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator>  _wheelspeed_type;
  _wheelspeed_type wheelspeed;

   typedef  ::hmcl_msgs::VehicleGear_<ContainerAllocator>  _gear_info_type;
  _gear_info_type gear_info;

   typedef  ::hmcl_msgs::VehicleLight_<ContainerAllocator>  _light_info_type;
  _light_info_type light_info;

   typedef  ::hmcl_msgs::RemoteButton_<ContainerAllocator>  _remote_button_info_type;
  _remote_button_info_type remote_button_info;

   typedef uint8_t _auto_mode_type;
  _auto_mode_type auto_mode;

   typedef uint8_t _ems_mode_type;
  _ems_mode_type ems_mode;

   typedef double _x_acceleration_type;
  _x_acceleration_type x_acceleration;

   typedef double _y_acceleration_type;
  _y_acceleration_type y_acceleration;

   typedef double _yaw_rate_type;
  _yaw_rate_type yaw_rate;





  typedef boost::shared_ptr< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> const> ConstPtr;

}; // struct VehicleStatus_

typedef ::hmcl_msgs::VehicleStatus_<std::allocator<void> > VehicleStatus;

typedef boost::shared_ptr< ::hmcl_msgs::VehicleStatus > VehicleStatusPtr;
typedef boost::shared_ptr< ::hmcl_msgs::VehicleStatus const> VehicleStatusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hmcl_msgs::VehicleStatus_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hmcl_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'hmcl_msgs': ['/home/hmcl/usafe/src/msgs_pkg/matlab_msg_gen_ros1/glnxa64/src/hmcl_msgs/msg'], 'geometry_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg', '/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg'], 'sensor_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/sensor_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "257eaa74ca2595e01127664962d58d27";
  }

  static const char* value(const ::hmcl_msgs::VehicleStatus_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x257eaa74ca2595e0ULL;
  static const uint64_t static_value2 = 0x1127664962d58d27ULL;
};

template<class ContainerAllocator>
struct DataType< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hmcl_msgs/VehicleStatus";
  }

  static const char* value(const ::hmcl_msgs::VehicleStatus_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"hmcl_msgs/VehicleSteering steering_info\n"
"hmcl_msgs/VehicleSCC scc_info\n"
"hmcl_msgs/VehicleWheelSpeed wheelspeed\n"
"hmcl_msgs/VehicleGear gear_info\n"
"hmcl_msgs/VehicleLight light_info\n"
"hmcl_msgs/RemoteButton remote_button_info\n"
"# auto mode -> 0  off\n"
"# auto mode -> 1  on\n"
"uint8 auto_mode \n"
"# ems mode -> 0  off\n"
"# ems mode -> 1  on\n"
"uint8 ems_mode \n"
"float64 x_acceleration\n"
"float64 y_acceleration\n"
"float64 yaw_rate\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: hmcl_msgs/VehicleSteering\n"
"Header header\n"
"# steering takeover -> off       = 0\n"
"# steering takeover -> on      = 1\n"
"uint8 takeover\n"
"# steering mode -> off       = 0\n"
"# steering mode -> on      = 1\n"
"uint8 mode\n"
"float32 steering_angle\n"
"================================================================================\n"
"MSG: hmcl_msgs/VehicleSCC\n"
"Header header\n"
"# sccmode -> off       = 0\n"
"# sccmode -> ready       = 1\n"
"# sccmode -> on       = 2\n"
"uint8 scc_mode\n"
"# scc takeover -> off       = 0\n"
"# scc takeover -> n      = 1\n"
"uint8 scc_takeover\n"
"float64 acceleration\n"
"================================================================================\n"
"MSG: hmcl_msgs/VehicleWheelSpeed\n"
"Header header\n"
"float64 wheel_speed\n"
"float64 fr\n"
"float64 fl\n"
"float64 rr\n"
"float64 rl\n"
"================================================================================\n"
"MSG: hmcl_msgs/VehicleGear\n"
"# Gear -> P       = 1\n"
"# Gear -> D       = 2\n"
"# Gear -> N       = 3\n"
"# Gear -> R       = 4\n"
"uint8 gear\n"
"\n"
"================================================================================\n"
"MSG: hmcl_msgs/VehicleLight\n"
"# 0 off, 1 on \n"
"uint8 left_light\n"
"uint8 right_light\n"
"uint8 hazard_light\n"
"================================================================================\n"
"MSG: hmcl_msgs/RemoteButton\n"
"# wirelessbutton -> 0 push off, 1 -> push on\n"
"uint8 button1\n"
"uint8 button2\n"
"uint8 button3\n"
;
  }

  static const char* value(const ::hmcl_msgs::VehicleStatus_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.steering_info);
      stream.next(m.scc_info);
      stream.next(m.wheelspeed);
      stream.next(m.gear_info);
      stream.next(m.light_info);
      stream.next(m.remote_button_info);
      stream.next(m.auto_mode);
      stream.next(m.ems_mode);
      stream.next(m.x_acceleration);
      stream.next(m.y_acceleration);
      stream.next(m.yaw_rate);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VehicleStatus_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hmcl_msgs::VehicleStatus_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hmcl_msgs::VehicleStatus_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "steering_info: ";
    s << std::endl;
    Printer< ::hmcl_msgs::VehicleSteering_<ContainerAllocator> >::stream(s, indent + "  ", v.steering_info);
    s << indent << "scc_info: ";
    s << std::endl;
    Printer< ::hmcl_msgs::VehicleSCC_<ContainerAllocator> >::stream(s, indent + "  ", v.scc_info);
    s << indent << "wheelspeed: ";
    s << std::endl;
    Printer< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >::stream(s, indent + "  ", v.wheelspeed);
    s << indent << "gear_info: ";
    s << std::endl;
    Printer< ::hmcl_msgs::VehicleGear_<ContainerAllocator> >::stream(s, indent + "  ", v.gear_info);
    s << indent << "light_info: ";
    s << std::endl;
    Printer< ::hmcl_msgs::VehicleLight_<ContainerAllocator> >::stream(s, indent + "  ", v.light_info);
    s << indent << "remote_button_info: ";
    s << std::endl;
    Printer< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >::stream(s, indent + "  ", v.remote_button_info);
    s << indent << "auto_mode: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.auto_mode);
    s << indent << "ems_mode: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ems_mode);
    s << indent << "x_acceleration: ";
    Printer<double>::stream(s, indent + "  ", v.x_acceleration);
    s << indent << "y_acceleration: ";
    Printer<double>::stream(s, indent + "  ", v.y_acceleration);
    s << indent << "yaw_rate: ";
    Printer<double>::stream(s, indent + "  ", v.yaw_rate);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HMCL_MSGS_MESSAGE_VEHICLESTATUS_H