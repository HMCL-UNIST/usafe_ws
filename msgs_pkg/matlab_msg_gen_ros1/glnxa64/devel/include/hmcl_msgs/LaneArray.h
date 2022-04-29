// Generated by gencpp from file hmcl_msgs/LaneArray.msg
// DO NOT EDIT!


#ifndef HMCL_MSGS_MESSAGE_LANEARRAY_H
#define HMCL_MSGS_MESSAGE_LANEARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <hmcl_msgs/Lane.h>

namespace hmcl_msgs
{
template <class ContainerAllocator>
struct LaneArray_
{
  typedef LaneArray_<ContainerAllocator> Type;

  LaneArray_()
    : header()
    , id(0)
    , lanes()  {
    }
  LaneArray_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , id(0)
    , lanes(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int32_t _id_type;
  _id_type id;

   typedef std::vector< ::hmcl_msgs::Lane_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::hmcl_msgs::Lane_<ContainerAllocator> >::other >  _lanes_type;
  _lanes_type lanes;





  typedef boost::shared_ptr< ::hmcl_msgs::LaneArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hmcl_msgs::LaneArray_<ContainerAllocator> const> ConstPtr;

}; // struct LaneArray_

typedef ::hmcl_msgs::LaneArray_<std::allocator<void> > LaneArray;

typedef boost::shared_ptr< ::hmcl_msgs::LaneArray > LaneArrayPtr;
typedef boost::shared_ptr< ::hmcl_msgs::LaneArray const> LaneArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hmcl_msgs::LaneArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hmcl_msgs::LaneArray_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::LaneArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::LaneArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::LaneArray_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "efe9adac565c883a229a06cb8197687e";
  }

  static const char* value(const ::hmcl_msgs::LaneArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xefe9adac565c883aULL;
  static const uint64_t static_value2 = 0x229a06cb8197687eULL;
};

template<class ContainerAllocator>
struct DataType< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hmcl_msgs/LaneArray";
  }

  static const char* value(const ::hmcl_msgs::LaneArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"int32 id\n"
"Lane[] lanes\n"
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
"MSG: hmcl_msgs/Lane\n"
"Header header\n"
"int32 lane_id\n"
"bool lane_change_flag\n"
"float32 speed_limit \n"
"Waypoint[] waypoints\n"
"Trafficlight[] trafficlights\n"
"Waypoint[] speedbumps\n"
"================================================================================\n"
"MSG: hmcl_msgs/Waypoint\n"
"# global id\n"
"int32 gid \n"
"# local id\n"
"int32 lid\n"
"geometry_msgs/PoseStamped pose\n"
"geometry_msgs/TwistStamped twist\n"
"uint32 lane_id\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/TwistStamped\n"
"# A twist with reference coordinate frame and timestamp\n"
"Header header\n"
"Twist twist\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Twist\n"
"# This expresses velocity in free space broken into its linear and angular parts.\n"
"Vector3  linear\n"
"Vector3  angular\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"================================================================================\n"
"MSG: hmcl_msgs/Trafficlight\n"
"Header header\n"
"int32 id\n"
"geometry_msgs/Point32 pose\n"
"bool valid_stop_line\n"
"geometry_msgs/Point32 stop_line\n"
"================================================================================\n"
"MSG: geometry_msgs/Point32\n"
"# This contains the position of a point in free space(with 32 bits of precision).\n"
"# It is recommeded to use Point wherever possible instead of Point32.  \n"
"# \n"
"# This recommendation is to promote interoperability.  \n"
"#\n"
"# This message is designed to take up less space when sending\n"
"# lots of points at once, as in the case of a PointCloud.  \n"
"\n"
"float32 x\n"
"float32 y\n"
"float32 z\n"
;
  }

  static const char* value(const ::hmcl_msgs::LaneArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.id);
      stream.next(m.lanes);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LaneArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hmcl_msgs::LaneArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hmcl_msgs::LaneArray_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.id);
    s << indent << "lanes[]" << std::endl;
    for (size_t i = 0; i < v.lanes.size(); ++i)
    {
      s << indent << "  lanes[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::hmcl_msgs::Lane_<ContainerAllocator> >::stream(s, indent + "    ", v.lanes[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // HMCL_MSGS_MESSAGE_LANEARRAY_H
