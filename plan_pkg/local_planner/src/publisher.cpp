#include "publisher.h"

Publisher::Publisher(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Publisher Initialize"); 
    sub_pos = nh_.subscribe("/pose_estimate", 1, &Publisher::poseCallback, this);
    sub_traj = nh_.subscribe("/lane_in_range", 1, &Publisher::trajCallback, this);
    sub_global = nh_.subscribe("/global_traj", 1, &Publisher::globalCallback, this);
    
    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 10);
    pub_viz = nh_.advertise<visualization_msgs::Marker>("/local_traj_viz", 0);
}

Publisher::~Publisher()
{}

void Publisher::poseCallback(const nav_msgs::Odometry& state_msg)
{
  current_x = state_msg.pose.pose.position.x;
  current_y = state_msg.pose.pose.position.y;
}

void Publisher::trajCallback(const hmcl_msgs::LaneArray& lane_msg)
{   
    hmcl_msgs::Lane pub_lane;
    if (lane_msg.lanes.size()==1){
        std::cout <<" one line " << std::endl;   
        pub_lane = cuttraj(lane_msg.lanes[0]);
        viz_local(pub_lane);
        pub_traj.publish(pub_lane);
        return;
    }
    // Error 
    else if(lane_msg.lanes[0].waypoints.size()==0){ 
        std::cout << " error part" << std::endl;
        pub_lane = cuttraj(lane_msg.lanes[1]);
        viz_local(pub_lane);
        pub_traj.publish(pub_lane);
        return;
    }
    range_index = {};
    for (int i =0; i < lane_msg.lanes.size(); i++){
        range_index.push_back(lane_msg.lanes[i].lane_id);
    }
    if (pr_flag == true){
        std::cout << "lane in range index = { ";
        for (int n : range_index) {std::cout << n << ", ";}
        std::cout << "}; \n";
    }

    pub_lane = cuttraj(lane_msg.lanes[1]);
    // pub_lane = cuttraj(lane_msg.lanes[0]);
    viz_local(pub_lane);
    pub_traj.publish(pub_lane);
}

hmcl_msgs::Lane Publisher::cuttraj(const hmcl_msgs::Lane& msg)
{
    std::cout<< " Trajectory Cutting "  << std::endl;  
    double dis = 0;
    double old_dis = 150;
    double current_idx = 0;
    double _x;
    double _y;
    hmcl_msgs::Lane lane;
    
    for (int i = 0; i < msg.waypoints.size(); i++){   
        _x = msg.waypoints[i].pose.pose.position.x;
        _y = msg.waypoints[i].pose.pose.position.y;
        dis = sqrt(pow(current_x- _x,2) + pow(current_y -_y,2));
        
        if (dis < old_dis){
            hmcl_msgs::Lane lane;
            current_idx = i;
            old_dis = dis;
        }
        lane.waypoints.push_back(msg.waypoints[i]);
    }
    return lane;
}

void Publisher::globalCallback(const hmcl_msgs::LaneArray& lane_msg)
{
    std::cout << " # lanes : " << lane_msg.lanes.size() << std::endl;
    global_lane = lane_msg;

    global_index = {};
    global_change = {};
    for (int i =0; i < lane_msg.lanes.size(); i++){
        global_index.push_back(lane_msg.lanes[i].lane_id);
        global_change.push_back(lane_msg.lanes[i].lane_change_flag);
    }

    // print
    if (pr_flag == true ){
        std::cout << "global index = { ";
        for (int n : global_index) {
            std::cout << n << ", ";
        }
        std::cout << "}; \n";

        std::cout << "lane_change index = { ";
        for (int n : global_change){
            std::cout << n << ", ";
        }
        std::cout << "}; \n";
    }
}


void Publisher::viz_local(const hmcl_msgs::Lane& lane)
{
    visualization_msgs::Marker lane_marker;
    lane_marker.header.frame_id = "map";
    lane_marker.header.stamp = ros::Time();
    lane_marker.ns = "local_traj_marker";
    lane_marker.id = 0;
    lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
    lane_marker.action = visualization_msgs::Marker::ADD;

    for (int i = 0; i < lane.waypoints.size(); i++){
        geometry_msgs::Point p;
        p.x = lane.waypoints[i].pose.pose.position.x;
        p.y = lane.waypoints[i].pose.pose.position.y;
        p.z = 0;
        lane_marker.points.push_back(p);
    }

    lane_marker.scale.x = 1;
    lane_marker.scale.y = 0;
    lane_marker.scale.z = 0;
    
    lane_marker.color.a = 1.0;
    lane_marker.color.r = 1.0;
    lane_marker.color.g = 1.0;
    lane_marker.color.b = 0.0;
    pub_viz.publish(lane_marker);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    
    Publisher Publisher(nh);

    ros::spin();
    return 0;
}