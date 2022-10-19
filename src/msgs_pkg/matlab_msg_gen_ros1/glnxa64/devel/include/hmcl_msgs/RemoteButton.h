// Generated by gencpp from file hmcl_msgs/RemoteButton.msg
// DO NOT EDIT!


#ifndef HMCL_MSGS_MESSAGE_REMOTEBUTTON_H
#define HMCL_MSGS_MESSAGE_REMOTEBUTTON_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace hmcl_msgs
{
template <class ContainerAllocator>
struct RemoteButton_
{
  typedef RemoteButton_<ContainerAllocator> Type;

  RemoteButton_()
    : button1(0)
    , button2(0)
    , button3(0)  {
    }
  RemoteButton_(const ContainerAllocator& _alloc)
    : button1(0)
    , button2(0)
    , button3(0)  {
  (void)_alloc;
    }



   typedef uint8_t _button1_type;
  _button1_type button1;

   typedef uint8_t _button2_type;
  _button2_type button2;

   typedef uint8_t _button3_type;
  _button3_type button3;





  typedef boost::shared_ptr< ::hmcl_msgs::RemoteButton_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hmcl_msgs::RemoteButton_<ContainerAllocator> const> ConstPtr;

}; // struct RemoteButton_

typedef ::hmcl_msgs::RemoteButton_<std::allocator<void> > RemoteButton;

typedef boost::shared_ptr< ::hmcl_msgs::RemoteButton > RemoteButtonPtr;
typedef boost::shared_ptr< ::hmcl_msgs::RemoteButton const> RemoteButtonConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hmcl_msgs::RemoteButton_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hmcl_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'hmcl_msgs': ['/home/hmcl/usafe/src/msgs_pkg/matlab_msg_gen_ros1/glnxa64/src/hmcl_msgs/msg'], 'geometry_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg', '/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg'], 'sensor_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/sensor_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::RemoteButton_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::RemoteButton_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::RemoteButton_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e0761a580fd3c116926a0b07701fd25f";
  }

  static const char* value(const ::hmcl_msgs::RemoteButton_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe0761a580fd3c116ULL;
  static const uint64_t static_value2 = 0x926a0b07701fd25fULL;
};

template<class ContainerAllocator>
struct DataType< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hmcl_msgs/RemoteButton";
  }

  static const char* value(const ::hmcl_msgs::RemoteButton_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# wirelessbutton -> 0 push off, 1 -> push on\n"
"uint8 button1\n"
"uint8 button2\n"
"uint8 button3\n"
;
  }

  static const char* value(const ::hmcl_msgs::RemoteButton_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.button1);
      stream.next(m.button2);
      stream.next(m.button3);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RemoteButton_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hmcl_msgs::RemoteButton_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hmcl_msgs::RemoteButton_<ContainerAllocator>& v)
  {
    s << indent << "button1: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.button1);
    s << indent << "button2: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.button2);
    s << indent << "button3: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.button3);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HMCL_MSGS_MESSAGE_REMOTEBUTTON_H
