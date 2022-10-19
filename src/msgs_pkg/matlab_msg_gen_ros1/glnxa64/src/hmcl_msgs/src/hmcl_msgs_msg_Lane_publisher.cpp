// Copyright 2019-2020 The MathWorks, Inc.
// Publisher for hmcl_msgs/Lane
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
#include "hmcl_msgs/Lane.h"
namespace hmcl_msgs {
namespace matlabhelper {
namespace Lane {
  void copy_from_arr(boost::shared_ptr<hmcl_msgs::Lane>& msg, const matlab::data::StructArray arr);
} //namespace Lane
} //namespace matlabhelper
} //namespace hmcl_msgs
class HMCL_MSGS_EXPORT hmcl_msgs_msg_Lane_publisher : public MATLABPublisherInterface {
    std::shared_ptr<ros::Publisher> mPub;
  public:
    hmcl_msgs_msg_Lane_publisher()
        : MATLABPublisherInterface() {
    }
    virtual ~hmcl_msgs_msg_Lane_publisher() {
    }
    virtual intptr_t createPublisher(const std::string& topic_name,
                                     bool latching,
                                    std::shared_ptr<ros::NodeHandle> n) {
        // Create a subscription to the topic which can be matched with one or more compatible ROS
        // publishers.
        // Note that not all publishers on the same topic with the same type will be compatible:
        // they must have compatible Quality of Service policies.
        mPub = std::make_shared<ros::Publisher>(n->advertise<hmcl_msgs::Lane>(topic_name, 1000,latching));
        return reinterpret_cast<intptr_t>(mPub.get());
    }
    virtual bool publish(const matlab::data::StructArray& arr) {
        auto msg = boost::make_shared<hmcl_msgs::Lane>();
        hmcl_msgs::matlabhelper::Lane::copy_from_arr(msg, arr);
        mPub->publish(msg);
        return true;
    }
};
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(hmcl_msgs_msg_Lane_publisher, MATLABPublisherInterface)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
