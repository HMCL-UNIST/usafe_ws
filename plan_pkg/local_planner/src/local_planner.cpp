#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <cmath>
#include <chrono>

#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "local_planner.h"

LocalPlanner::LocalPlanner()
{ 
    ros::NodeHandle nh_;
    ROS_INFO("Local Planner initialize");

    pose_sub = nh_.subscribe("/pose_estimate", 1, &LocalPlanner::poseCallback, this);
    behavior_state_sub = nh_.subscribe("/behavior_state", 1, &LocalPlanner::BehaviorStateCallback, this);
    global_traj_sub =  nh_.subscribe("/global_traj", 1, &LocalPlanner::trajCallback,this);

    local_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 2, true);
    
    get_global = false;
    pose_init = false;
    boost::thread callbackhandler(&LocalPlanner::callbackthread,this);
}
void LocalPlanner::callbackthread()
{   
    ros::Rate loop_rate(10); // rate  
    while(ros::ok()){
        PlanLocalTraj();
        loop_rate.sleep();
    }
}

void LocalPlanner::PlanLocalTraj()
{   
    double dis = 0;
    double old_dis = 100;
    int current_idx = 0;
    int p_wpt_size;

    if (get_global && pose_init){
        hmcl_msgs::Lane local_traj;
        p_wpt_size = 0;
        for (int i = 0; i < global_traj.lanes.size(); i++ ){
            // std::cout << i << std::endl;

            for (int w =0; w <  global_traj.lanes[i].waypoints.size(); w++){
                // std::cout << w << std::endl;
                local_traj.waypoints.push_back(global_traj.lanes[i].waypoints[w]);
                // local_traj.waypoints[w] = global_traj.lanes[i].waypoints[w];
            }
            // std::copy(global_traj.lanes[i].waypoints.begin(), global_traj.lanes[i].waypoints.end(), local_traj.waypoints.begin()+p_wpt_size);
            p_wpt_size = global_traj.lanes[i].waypoints.size();
        }
        
        for (int j = 0; j < local_traj.waypoints.size(); j++ ){ 
            double _x = local_traj.waypoints[j].pose.pose.position.x;
            double _y = local_traj.waypoints[j].pose.pose.position.y;
            dis = sqrt ( pow(pose_x- _x,2) + pow(pose_y -_y,2));
            if (dis < old_dis){
                current_idx = j;
                old_dis = dis;
            }
        }
        hmcl_msgs::Lane c_local_traj;

        for (int i = current_idx; i <local_traj.waypoints.size(); i++){
            c_local_traj.waypoints.push_back(local_traj.waypoints[i]);
        }
        // std::copy(local_traj.waypoints.begin()+current_idx,local_traj.waypoints.end(),c_local_traj.waypoints.begin());
        local_traj.speed_limit = global_traj.lanes[0].speed_limit;
        local_traj.header = global_traj.lanes[0].header;
        local_pub.publish(c_local_traj);
    }
}


void LocalPlanner::poseCallback(const nav_msgs::OdometryConstPtr& msg){  
    if(!pose_init){
        pose_init = true;
    }
    cur_pose = msg->pose.pose;
    pose_x = msg->pose.pose.position.x;
    pose_y = msg->pose.pose.position.y;
    pose_z = msg->pose.pose.position.z;
}

void LocalPlanner::BehaviorStateCallback(const std_msgs::Int16& msg){
    CurrentMode =(BehaviorState)msg.data;
}

void LocalPlanner::trajCallback(const hmcl_msgs::LaneArray& msg)
{  
    if(msg.lanes.size() < 1){
        return;
    }   
    get_global = true; 
    global_traj = msg;
}


int main (int argc, char** argv)
{

    ros::init(argc, argv, "local_planner");
    LocalPlanner local;
    ros::spin();
    
}

