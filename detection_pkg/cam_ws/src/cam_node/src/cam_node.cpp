#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cam_publisher");
    ros::NodeHandle nh;

    std::string frame_id_;
    std::string video_device_name_;
    int frame_rate_;

    nh.param("frame_id", frame_id_, std::string("front_cam"));
    nh.param("video_device", video_device_name_, std::string("/dev/video1"));
    nh.param("frame_rate", frame_rate_, 30);
    

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("image_raw", 1);
    std::string option = "v4l2src device=";
    option += video_device_name_;
    option += " ! video/x-raw, width=(int)1920, height=(int)1080 ! videoconvert ! appsink";
    // option += " ! appsink ";
    std::cout << option << std::endl;
    cv::VideoCapture cap(option);

    if(cap.isOpened()) return 1;

    cv::Mat frame;
    std_msgs::Header tmp_header;
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(frame_rate_);
    while (nh.ok())
    {
        cap >> frame;
        if(!frame.empty())
        {   
            ROS_INFO("A");
            tmp_header.stamp = ros::Time::now();
            tmp_header.frame_id = frame_id_;
            msg = cv_bridge::CvImage(tmp_header, "yuyv", frame).toImageMsg();
            pub.publish(msg);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
}

