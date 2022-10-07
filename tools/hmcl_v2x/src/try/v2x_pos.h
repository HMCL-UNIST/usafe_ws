#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <cstring>

#include "sensor_msgs/NavSatFix.h"

using namespace std;

class V2XPos
{

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_pos;
    string line;

public:
    V2XPos(ros::NodeHandle& nh_);
    ~V2XPos();

};
