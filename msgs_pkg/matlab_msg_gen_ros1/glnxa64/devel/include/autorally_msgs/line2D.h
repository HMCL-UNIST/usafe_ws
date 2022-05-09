// Generated by gencpp from file autorally_msgs/line2D.msg
// DO NOT EDIT!


#ifndef AUTORALLY_MSGS_MESSAGE_LINE2D_H
#define AUTORALLY_MSGS_MESSAGE_LINE2D_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <autorally_msgs/point2D.h>
#include <autorally_msgs/point2D.h>

namespace autorally_msgs
{
template <class ContainerAllocator>
struct line2D_
{
  typedef line2D_<ContainerAllocator> Type;

  line2D_()
    : start()
    , end()  {
    }
  line2D_(const ContainerAllocator& _alloc)
    : start(_alloc)
    , end(_alloc)  {
  (void)_alloc;
    }



   typedef  ::autorally_msgs::point2D_<ContainerAllocator>  _start_type;
  _start_type start;

   typedef  ::autorally_msgs::point2D_<ContainerAllocator>  _end_type;
  _end_type end;





  typedef boost::shared_ptr< ::autorally_msgs::line2D_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autorally_msgs::line2D_<ContainerAllocator> const> ConstPtr;

}; // struct line2D_

typedef ::autorally_msgs::line2D_<std::allocator<void> > line2D;

typedef boost::shared_ptr< ::autorally_msgs::line2D > line2DPtr;
typedef boost::shared_ptr< ::autorally_msgs::line2D const> line2DConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autorally_msgs::line2D_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autorally_msgs::line2D_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace autorally_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/sensor_msgs/cmake/../msg'], 'autorally_msgs': ['/home/hmcl/usafe/src/msgs_pkg/matlab_msg_gen_ros1/glnxa64/src/autorally_msgs/msg'], 'std_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg', '/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::autorally_msgs::line2D_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autorally_msgs::line2D_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autorally_msgs::line2D_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autorally_msgs::line2D_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autorally_msgs::line2D_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autorally_msgs::line2D_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autorally_msgs::line2D_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7a338da65a86a1f736887760a0feaccd";
  }

  static const char* value(const ::autorally_msgs::line2D_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7a338da65a86a1f7ULL;
  static const uint64_t static_value2 = 0x36887760a0feaccdULL;
};

template<class ContainerAllocator>
struct DataType< ::autorally_msgs::line2D_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autorally_msgs/line2D";
  }

  static const char* value(const ::autorally_msgs::line2D_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autorally_msgs::line2D_<ContainerAllocator> >
{
  static const char* value()
  {
    return "point2D start\n"
"point2D end\n"
"\n"
"================================================================================\n"
"MSG: autorally_msgs/point2D\n"
"uint16 x\n"
"uint16 y\n"
;
  }

  static const char* value(const ::autorally_msgs::line2D_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autorally_msgs::line2D_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.start);
      stream.next(m.end);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct line2D_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autorally_msgs::line2D_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autorally_msgs::line2D_<ContainerAllocator>& v)
  {
    s << indent << "start: ";
    s << std::endl;
    Printer< ::autorally_msgs::point2D_<ContainerAllocator> >::stream(s, indent + "  ", v.start);
    s << indent << "end: ";
    s << std::endl;
    Printer< ::autorally_msgs::point2D_<ContainerAllocator> >::stream(s, indent + "  ", v.end);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTORALLY_MSGS_MESSAGE_LINE2D_H
