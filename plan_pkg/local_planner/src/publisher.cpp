#include "publisher.h"



Publisher::Publisher(ros::NodeHandle& nh):

    nh_(nh)

{

    ROS_INFO("Publisher Initialize");   

    sub_traj = nh_.subscribe("/lane_in_range", 1, &Publisher::trajCallback, this);

    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 10);

}



Publisher::~Publisher()

{}



void Publisher::trajCallback(const hmcl_msgs::LaneArray& lane_msg)

{

    std::cout << " # lanes : " << lane_msg.lanes.size() << std::endl;

    hmcl_msgs::Lane lane;

    lane = lane_msg.lanes[0];

    

    if (lane.waypoints.size()==0)

    {

        lane = lane_msg.lanes[1];

        std::cout << "waypoints number: " << lane.waypoints.size() << std::endl;

    }

    pub_traj.publish(lane);  



    // for (int i =0; i < lane_msg.lanes.size(); i++)

    // {

        // lane = lane_msg.lanes[i];

        // std::cout << "lane id : " << lane.lane_id << std::endl;

        // std::cout << "waypoints number: " << lane.waypoints.size() << std::endl;

    // }



}



int main(int argc, char** argv)

{

    ros::init(argc, argv, "publisher");

    ros::NodeHandle nh;

    

    Publisher Publisher(nh);



    ros::spin();

    return 0;

}