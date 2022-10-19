// Generated by gencpp from file hmcl_msgs/WaypointState.msg
// DO NOT EDIT!


#ifndef HMCL_MSGS_MESSAGE_WAYPOINTSTATE_H
#define HMCL_MSGS_MESSAGE_WAYPOINTSTATE_H


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
struct WaypointState_
{
  typedef WaypointState_<ContainerAllocator> Type;

  WaypointState_()
    : aid(0)
    , lanechange_state(0)
    , steering_state(0)
    , accel_state(0)
    , stop_state(0)
    , event_state(0)  {
    }
  WaypointState_(const ContainerAllocator& _alloc)
    : aid(0)
    , lanechange_state(0)
    , steering_state(0)
    , accel_state(0)
    , stop_state(0)
    , event_state(0)  {
  (void)_alloc;
    }



   typedef int32_t _aid_type;
  _aid_type aid;

   typedef uint8_t _lanechange_state_type;
  _lanechange_state_type lanechange_state;

   typedef uint8_t _steering_state_type;
  _steering_state_type steering_state;

   typedef uint8_t _accel_state_type;
  _accel_state_type accel_state;

   typedef uint8_t _stop_state_type;
  _stop_state_type stop_state;

   typedef uint8_t _event_state_type;
  _event_state_type event_state;



// reducing the odds to have name collisions with Windows.h 
#if defined(_WIN32) && defined(NULLSTATE)
  #undef NULLSTATE
#endif
#if defined(_WIN32) && defined(STR_LEFT)
  #undef STR_LEFT
#endif
#if defined(_WIN32) && defined(STR_RIGHT)
  #undef STR_RIGHT
#endif
#if defined(_WIN32) && defined(STR_STRAIGHT)
  #undef STR_STRAIGHT
#endif
#if defined(_WIN32) && defined(STR_BACK)
  #undef STR_BACK
#endif
#if defined(_WIN32) && defined(TYPE_STOPLINE)
  #undef TYPE_STOPLINE
#endif
#if defined(_WIN32) && defined(TYPE_STOP)
  #undef TYPE_STOP
#endif
#if defined(_WIN32) && defined(TYPE_EVENT_NULL)
  #undef TYPE_EVENT_NULL
#endif
#if defined(_WIN32) && defined(TYPE_EVENT_GOAL)
  #undef TYPE_EVENT_GOAL
#endif
#if defined(_WIN32) && defined(TYPE_EVENT_MIDDLE_GOAL)
  #undef TYPE_EVENT_MIDDLE_GOAL
#endif
#if defined(_WIN32) && defined(TYPE_EVENT_POSITION_STOP)
  #undef TYPE_EVENT_POSITION_STOP
#endif
#if defined(_WIN32) && defined(TYPE_EVENT_BUS_STOP)
  #undef TYPE_EVENT_BUS_STOP
#endif
#if defined(_WIN32) && defined(TYPE_EVENT_PARKING)
  #undef TYPE_EVENT_PARKING
#endif

  enum {
    NULLSTATE = 0u,
    STR_LEFT = 1u,
    STR_RIGHT = 2u,
    STR_STRAIGHT = 3u,
    STR_BACK = 4u,
    TYPE_STOPLINE = 1u,
    TYPE_STOP = 2u,
    TYPE_EVENT_NULL = 0u,
    TYPE_EVENT_GOAL = 1u,
    TYPE_EVENT_MIDDLE_GOAL = 2u,
    TYPE_EVENT_POSITION_STOP = 3u,
    TYPE_EVENT_BUS_STOP = 4u,
    TYPE_EVENT_PARKING = 5u,
  };


  typedef boost::shared_ptr< ::hmcl_msgs::WaypointState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hmcl_msgs::WaypointState_<ContainerAllocator> const> ConstPtr;

}; // struct WaypointState_

typedef ::hmcl_msgs::WaypointState_<std::allocator<void> > WaypointState;

typedef boost::shared_ptr< ::hmcl_msgs::WaypointState > WaypointStatePtr;
typedef boost::shared_ptr< ::hmcl_msgs::WaypointState const> WaypointStateConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hmcl_msgs::WaypointState_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hmcl_msgs::WaypointState_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::hmcl_msgs::WaypointState_<ContainerAllocator1> & lhs, const ::hmcl_msgs::WaypointState_<ContainerAllocator2> & rhs)
{
  return lhs.aid == rhs.aid &&
    lhs.lanechange_state == rhs.lanechange_state &&
    lhs.steering_state == rhs.steering_state &&
    lhs.accel_state == rhs.accel_state &&
    lhs.stop_state == rhs.stop_state &&
    lhs.event_state == rhs.event_state;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::hmcl_msgs::WaypointState_<ContainerAllocator1> & lhs, const ::hmcl_msgs::WaypointState_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace hmcl_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hmcl_msgs::WaypointState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hmcl_msgs::WaypointState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hmcl_msgs::WaypointState_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "623a0ffbb0a052490adc981c2a3e8edd";
  }

  static const char* value(const ::hmcl_msgs::WaypointState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x623a0ffbb0a05249ULL;
  static const uint64_t static_value2 = 0x0adc981c2a3e8eddULL;
};

template<class ContainerAllocator>
struct DataType< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hmcl_msgs/WaypointState";
  }

  static const char* value(const ::hmcl_msgs::WaypointState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 aid\n"
"uint8 NULLSTATE=0\n"
"\n"
"# lanechange\n"
"uint8 lanechange_state\n"
"\n"
"# bilinker\n"
"uint8 steering_state\n"
"uint8 STR_LEFT=1\n"
"uint8 STR_RIGHT=2\n"
"uint8 STR_STRAIGHT=3\n"
"uint8 STR_BACK=4\n"
"\n"
"uint8 accel_state\n"
"\n"
"uint8 stop_state\n"
"# 1 is stopline, 2 is stop which can only be released manually.\n"
"uint8 TYPE_STOPLINE=1\n"
"uint8 TYPE_STOP=2\n"
"\n"
"uint8 event_state\n"
"uint8 TYPE_EVENT_NULL = 0\n"
"uint8 TYPE_EVENT_GOAL = 1\n"
"uint8 TYPE_EVENT_MIDDLE_GOAL = 2\n"
"uint8 TYPE_EVENT_POSITION_STOP = 3\n"
"uint8 TYPE_EVENT_BUS_STOP = 4\n"
"uint8 TYPE_EVENT_PARKING = 5\n"
;
  }

  static const char* value(const ::hmcl_msgs::WaypointState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.aid);
      stream.next(m.lanechange_state);
      stream.next(m.steering_state);
      stream.next(m.accel_state);
      stream.next(m.stop_state);
      stream.next(m.event_state);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct WaypointState_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hmcl_msgs::WaypointState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hmcl_msgs::WaypointState_<ContainerAllocator>& v)
  {
    s << indent << "aid: ";
    Printer<int32_t>::stream(s, indent + "  ", v.aid);
    s << indent << "lanechange_state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.lanechange_state);
    s << indent << "steering_state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.steering_state);
    s << indent << "accel_state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.accel_state);
    s << indent << "stop_state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.stop_state);
    s << indent << "event_state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.event_state);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HMCL_MSGS_MESSAGE_WAYPOINTSTATE_H
