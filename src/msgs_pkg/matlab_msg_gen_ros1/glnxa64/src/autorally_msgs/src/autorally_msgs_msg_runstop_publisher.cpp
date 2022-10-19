// Copyright 2019-2020 The MathWorks, Inc.
// Publisher for autorally_msgs/runstop
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
#include "MATLABPublisherInterface.hpp"
#include "visibility_control.h"
#include "autorally_msgs/runstop.h"
namespace autorally_msgs {
namespace matlabhelper {
namespace runstop {
  void copy_from_arr(boost::shared_ptr<autorally_msgs::runstop>& msg, const matlab::data::StructArray arr);
} //namespace runstop
} //namespace matlabhelper
} //namespace autorally_msgs
class AUTORALLY_MSGS_EXPORT autorally_msgs_msg_runstop_publisher : public MATLABPublisherInterface {
    std::shared_ptr<ros::Publisher> mPub;
  public:
    autorally_msgs_msg_runstop_publisher()
        : MATLABPublisherInterface() {
    }
    virtual ~autorally_msgs_msg_runstop_publisher() {
    }
    virtual intptr_t createPublisher(const std::string& topic_name,
                                     bool latching,
                                    std::shared_ptr<ros::NodeHandle> n) {
        // Create a subscription to the topic which can be matched with one or more compatible ROS
        // publishers.
        // Note that not all publishers on the same topic with the same type will be compatible:
        // they must have compatible Quality of Service policies.
        mPub = std::make_shared<ros::Publisher>(n->advertise<autorally_msgs::runstop>(topic_name, 1000,latching));
        return reinterpret_cast<intptr_t>(mPub.get());
    }
    virtual bool publish(const matlab::data::StructArray& arr) {
        auto msg = boost::make_shared<autorally_msgs::runstop>();
        autorally_msgs::matlabhelper::runstop::copy_from_arr(msg, arr);
        mPub->publish(msg);
        return true;
    }
};
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(autorally_msgs_msg_runstop_publisher, MATLABPublisherInterface)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
