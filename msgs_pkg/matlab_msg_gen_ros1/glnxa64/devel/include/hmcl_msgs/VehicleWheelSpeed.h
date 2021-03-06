// Generated by gencpp from file hmcl_msgs/VehicleWheelSpeed.msg
// DO NOT EDIT!


#ifndef HMCL_MSGS_MESSAGE_VEHICLEWHEELSPEED_H
#define HMCL_MSGS_MESSAGE_VEHICLEWHEELSPEED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace hmcl_msgs
{
template <class ContainerAllocator>
struct VehicleWheelSpeed_
{
  typedef VehicleWheelSpeed_<ContainerAllocator> Type;

  VehicleWheelSpeed_()
    : header()
    , wheel_speed(0.0)
    , fr(0.0)
    , fl(0.0)
    , rr(0.0)
    , rl(0.0)  {
    }
  VehicleWheelSpeed_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , wheel_speed(0.0)
    , fr(0.0)
    , fl(0.0)
    , rr(0.0)
    , rl(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _wheel_speed_type;
  _wheel_speed_type wheel_speed;

   typedef double _fr_type;
  _fr_type fr;

   typedef double _fl_type;
  _fl_type fl;

   typedef double _rr_type;
  _rr_type rr;

   typedef double _rl_type;
  _rl_type rl;





  typedef boost::shared_ptr< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> const> ConstPtr;

}; // struct VehicleWheelSpeed_

typedef ::hmcl_msgs::VehicleWheelSpeed_<std::allocator<void> > VehicleWheelSpeed;

typedef boost::shared_ptr< ::hmcl_msgs::VehicleWheelSpeed > VehicleWheelSpeedPtr;
typedef boost::shared_ptr< ::hmcl_msgs::VehicleWheelSpeed const> VehicleWheelSpeedConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dd9bfec439fcf31963b917a79106fa20";
  }

  static const char* value(const ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdd9bfec439fcf319ULL;
  static const uint64_t static_value2 = 0x63b917a79106fa20ULL;
};

template<class ContainerAllocator>
struct DataType< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hmcl_msgs/VehicleWheelSpeed";
  }

  static const char* value(const ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"float64 wheel_speed\n"
"float64 fr\n"
"float64 fl\n"
"float64 rr\n"
"float64 rl\n"
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
;
  }

  static const char* value(const ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.wheel_speed);
      stream.next(m.fr);
      stream.next(m.fl);
      stream.next(m.rr);
      stream.next(m.rl);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VehicleWheelSpeed_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hmcl_msgs::VehicleWheelSpeed_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "wheel_speed: ";
    Printer<double>::stream(s, indent + "  ", v.wheel_speed);
    s << indent << "fr: ";
    Printer<double>::stream(s, indent + "  ", v.fr);
    s << indent << "fl: ";
    Printer<double>::stream(s, indent + "  ", v.fl);
    s << indent << "rr: ";
    Printer<double>::stream(s, indent + "  ", v.rr);
    s << indent << "rl: ";
    Printer<double>::stream(s, indent + "  ", v.rl);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HMCL_MSGS_MESSAGE_VEHICLEWHEELSPEED_H
