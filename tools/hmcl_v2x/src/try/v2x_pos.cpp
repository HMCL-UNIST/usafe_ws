#include "v2x_pos.h"

V2XPos::V2XPos(ros::NodeHandle& nh_): 
    nh_(nh_)
{
    pub_pos = nh_.advertise<sensor_msgs::NavSatFix>("Mission_pos", 10);
    ros::Rate loop_rate(1);
    ROS_INFO("V2X Pos Publisher Initialization");

    ifstream fin("/home/xavier2/v2x_ros/mission1_pos.txt");
    
    while (ros::ok())
    {
        while(getline(fin,line))
        {
            cout << line << endl;
        }
        
        loop_rate.sleep();        
    }
    fin.close();

}

V2XPos::~V2XPos()
{}

int main (int argc, char** argv)
{
    ros::init(argc, argv, "Mission_Pos_pub");
    ros::NodeHandle nh_;
    V2XPos V2XPos(nh_);

    return 0;
}
