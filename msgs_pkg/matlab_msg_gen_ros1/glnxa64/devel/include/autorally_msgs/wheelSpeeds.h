// Generated by gencpp from file autorally_msgs/wheelSpeeds.msg
// DO NOT EDIT!


#ifndef AUTORALLY_MSGS_MESSAGE_WHEELSPEEDS_H
#define AUTORALLY_MSGS_MESSAGE_WHEELSPEEDS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace autorally_msgs
{
template <class ContainerAllocator>
struct wheelSpeeds_
{
  typedef wheelSpeeds_<ContainerAllocator> Type;

  wheelSpeeds_()
    : header()
    , lfSpeed(0.0)
    , rfSpeed(0.0)
    , lbSpeed(0.0)
    , rbSpeed(0.0)  {
    }
  wheelSpeeds_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , lfSpeed(0.0)
    , rfSpeed(0.0)
    , lbSpeed(0.0)
    , rbSpeed(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _lfSpeed_type;
  _lfSpeed_type lfSpeed;

   typedef double _rfSpeed_type;
  _rfSpeed_type rfSpeed;

   typedef double _lbSpeed_type;
  _lbSpeed_type lbSpeed;

   typedef double _rbSpeed_type;
  _rbSpeed_type rbSpeed;





  typedef boost::shared_ptr< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> const> ConstPtr;

}; // struct wheelSpeeds_

typedef ::autorally_msgs::wheelSpeeds_<std::allocator<void> > wheelSpeeds;

typedef boost::shared_ptr< ::autorally_msgs::wheelSpeeds > wheelSpeedsPtr;
typedef boost::shared_ptr< ::autorally_msgs::wheelSpeeds const> wheelSpeedsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autorally_msgs::wheelSpeeds_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace autorally_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'sensor_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/sensor_msgs/cmake/../msg'], 'autorally_msgs': ['/home/hmcl/usafe/src/msgs_pkg/matlab_msg_gen_ros1/glnxa64/src/autorally_msgs/msg'], 'std_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg', '/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c5c4a96a4e17d91e72a2f7397af4d720";
  }

  static const char* value(const ::autorally_msgs::wheelSpeeds_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc5c4a96a4e17d91eULL;
  static const uint64_t static_value2 = 0x72a2f7397af4d720ULL;
};

template<class ContainerAllocator>
struct DataType< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autorally_msgs/wheelSpeeds";
  }

  static const char* value(const ::autorally_msgs::wheelSpeeds_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"float64 lfSpeed\n"
"float64 rfSpeed\n"
"float64 lbSpeed\n"
"float64 rbSpeed\n"
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
;
  }

  static const char* value(const ::autorally_msgs::wheelSpeeds_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.lfSpeed);
      stream.next(m.rfSpeed);
      stream.next(m.lbSpeed);
      stream.next(m.rbSpeed);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct wheelSpeeds_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autorally_msgs::wheelSpeeds_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autorally_msgs::wheelSpeeds_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "lfSpeed: ";
    Printer<double>::stream(s, indent + "  ", v.lfSpeed);
    s << indent << "rfSpeed: ";
    Printer<double>::stream(s, indent + "  ", v.rfSpeed);
    s << indent << "lbSpeed: ";
    Printer<double>::stream(s, indent + "  ", v.lbSpeed);
    s << indent << "rbSpeed: ";
    Printer<double>::stream(s, indent + "  ", v.rbSpeed);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTORALLY_MSGS_MESSAGE_WHEELSPEEDS_H
