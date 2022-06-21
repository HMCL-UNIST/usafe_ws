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


#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "velocity_generator.h"

VelocityGenerator::VelocityGenerator()
{   
    ros::NodeHandle nh_;
    ROS_INFO("velocity profile generator initialize2");


    // Prameter
    local_traj_init = false;
    visualize = true;
    new_vel = false;
    previous_step = false;
    ttt = 0;

    // Subscribe
    local_traj_sub =  nh_.subscribe("/local_traj", 1, &VelocityGenerator::trajCallback,this);
    acc_target_vel_sub = nh_.subscribe("/acc_target_vel", 1, &VelocityGenerator::targetCallback, this);
    // vel_sub = nh_.subscribe("/pose_estimate", 1, &VelocityGenerator::velCallback, this);
    wheel_sub = nh_.subscribe("/vehicle_status", 1, &VelocityGenerator::wheelCallback, this);
    acc_sub = nh_.subscribe("/bias_acc", 1, &VelocityGenerator::accCallback, this);

    // Publish
    vel_pub = nh_.advertise<std_msgs::Float64>("/setpoint", 1, true);
    vel_vis_pub = nh_.advertise<visualization_msgs::Marker>( "/ref_vel_prof_viz", 0 );
    vel_debug  = nh_.advertise<geometry_msgs::PoseStamped>("/vel_debug", 2);

    // ros::Timer vel_timer = nh_.createTimer(ros::Duration(0.1), &VelocityGenerator::CalcVel,this);  
    boost::thread callbackhandler(&VelocityGenerator::callbackthread,this); 

}

void VelocityGenerator::callbackthread()
{   
    ros::Rate loop_rate(10); // rate  
    while(ros::ok()){
        CalcVel();
        loop_rate.sleep();
    }
}
void VelocityGenerator::CalcVel()
{

    std_msgs::Float64 vel_msg;

    double v0 = current_vel;
    double a0 = 0;
    double a_lon_lim = 1.5;
    double a_lat_lim = 4.0;
    double d_lon_lim = -2.0;

    double P[3] = {1.0,1.0,5.0};
    double xf[3] = {15, v0, 0};
    if (new_target_vel) {
        if (target_acc_vel > speed_limit)
            target_acc_vel = speed_limit;
        xf[0] = 10;
        xf[1] = target_acc_vel;
        xf[2] = 0;
        // double xf[3] = {10, target_acc_vel, 0};
        // std::cout << "Calculate the velocity: c_vel" << current_vel << " r_vel " << target_acc_vel << "acc" << current_acc << std::endl;
    } 
    else{
        // double xf[3] = {10, speed_limit, 0};
        xf[0] = 10;
        xf[1] = speed_limit;
        xf[2] = 0;
    }
    if (previous_step) {
        std::cout << "*********" << std::endl;
        xf[1] = xf[1]*0.5;
    }
    

    bool fail2solve = false;
    
    double ref_speed = v0;

    debug_msg.header.stamp = ros::Time::now(); 
    debug_msg.pose.position.x = v0;
    debug_msg.pose.position.y = xf[1];
    std::cout << "current_vel" << current_vel <<  std::endl;
    std::cout << "r_vel" << xf[1] <<  std::endl;
    

    int k = 0;
    while(1)
    {   
        // std::cout << "k is " << k << std::endl;
        double sf = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*P[0]*pow(P[2],3) + 1/4*P[1]*pow(P[2],4);
        double vf = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
        double af = a0 + 2*P[0]*P[2] + 3*P[1]*pow(P[2],2);

        
        double del_x[3] = {xf[0] - sf, xf[1]- vf, xf[2]- af};


        if (speed_limit <= 20/3.6)
        {
            if (current_vel < speed_limit)
                ref_speed = speed_limit;
                break;
        }

        if (abs(del_x[0]) < 0.1 && abs(del_x[1]) < 0.1 && abs(del_x[2]) < 0.1) {        
            
            double time = 1;

            if (abs(current_vel-xf[1]) > 8)
                time = P[2]*0.75;

            if (P[2] > time) {
                ref_speed = v0 + a0*time + P[0]*pow(time,2) + P[1]*pow(time,3);
            }
            else{
                ref_speed = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
            }

            if (xf[1] = 0 && current_vel < 1)
            {
                ref_speed = 0;
            }

            double N = P[2]/0.2;

            std::vector<double> profile{};
            double tt = 0.0;
            for (int i = 0; i < N; i++)
            {
                profile.push_back(v0 + a0*tt + P[0]*pow(tt,2) + P[1]*pow(tt,3));
                tt = tt + 0.2;   
            }
            std::cout << "Calculate the velocity: c_vel" << current_vel << "r_vel" << ref_speed << std::endl;
            if (visualize)
            {
                viz_vel_prof(profile);
            }
            // std::cout << "1 sbreak "  << std::endl;
            previous_step = false;
            break;
        }
        else if (k >= 50 || fail2solve) {
            ref_speed = v0;
            std::cout << "Fail" << std::endl;
            previous_step = true;
            break;
        }

        double DEL = 1e-1;

        double xh1 = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*(P[0]+DEL)*pow(P[2],3) +1/4*P[1]*pow(P[2],4);
        double x1 = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*P[0]*pow(P[2],3) +1/4*P[1]*pow(P[2],4);
        double J11 = (xh1-x1)/DEL;

        double xh2 = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*P[0]*pow(P[2],3) +1/4*(P[1]+DEL)*pow(P[2],4);
        double x2 = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*P[0]*pow(P[2],3) +1/4*P[1]*pow(P[2],4);
        double J12 = (xh2-x2)/DEL;            

        double xh3 = v0*(P[2]+DEL) + 1/2*a0*pow((P[2]+DEL),2) + 1/3*P[0]*pow((P[2]+DEL),3) +1/4*P[1]*pow((P[2]+DEL),4);
        double x3 = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*P[0]*pow(P[2],3) +1/4*P[1]*pow(P[2],4);
        double J13 = (xh3-x3)/DEL;    


        xh1 = v0 + a0*P[2] + (P[0]+DEL)*pow(P[2],2) + P[1]*pow(P[2],3);
        x1 = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
        double J21 = (xh1-x1)/DEL;

        xh2 = v0 + a0*P[2] + P[0]*pow(P[2],2) + (P[1]+DEL)*pow(P[2],3);
        x2 = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
        double J22 = (xh2-x2)/DEL;            

        xh3 = v0 + a0*(P[2]+DEL) + P[0]*pow(P[2]+DEL,2) + P[1]*pow(P[2]+DEL,3);
        x3 = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
        double J23 = (xh3-x3)/DEL;            

        xh1 = a0 + 2*(P[0]+DEL)*P[2] + 3*P[1]*pow(P[2],2);
        x1 = a0 + 2*P[0]*P[2] + 3*P[1]*pow(P[2],2);
        double J31 = (xh1-x1)/DEL;   

        xh2 = a0 + 2*P[0]*P[2] + 3*(P[1]+DEL)*pow(P[2],2);
        x2 = a0 + 2*P[0]*P[2] + 3*P[1]*pow(P[2],2);
        double J32 = (xh2-x2)/DEL;

        xh3 = a0 + 2*P[0]*(P[2]+DEL) + 3*P[1]*pow((P[2]+DEL),2);
        x3 = a0 + 2*P[0]*P[2] + 3*P[1]*pow(P[2],2);
        double J33 = (xh3-x3)/DEL;

        
        //Compute the inverse Matrix
        double a = J11; double b = J12; double c = J13; 
        double d = J21; double e = J22; double f = J23;
        double g = J31; double h = J32; double i = J33;

        float result = a*e*i - a*f*h - b*d*i + b*f*g +c*d*h -c*e*g;

        if (abs(result) <= 0.0001) {
            fail2solve = true;
        }
        else
        {
            double invJ[3][3];
            invJ[0][0] = (e*i-f*h)/result;
            invJ[0][1] = (c*h-b*i)/result;
            invJ[0][2] = (b*f-c*e)/result;
            invJ[1][0] = (g*f-d*i)/result;
            invJ[1][1] = (a*i-c*g)/result;
            invJ[1][2] = (c*d-a*f)/result;
            invJ[2][0] = (d*h-e*g)/result;
            invJ[2][1] = (b*g-a*h)/result;
            invJ[2][2] = (a*e-b*d)/result;
            
            double del_P[3] = {};
            for (int i = 0; i < 3; i++)
            {
                double x = invJ[i][0] * del_x[0];
                double y = invJ[i][1] * del_x[1];
                double z = invJ[i][2] * del_x[2];
                
                del_P[i] = x + y + z;
            } 
                
            P[0] = P[0]+del_P[0]; P[1]=P[1]+ del_P[1]; P[2] = P[2]+ del_P[2]; 
        }

        k = k+1;


    }

    double rref_speed = ref_speed*3.6;
    if (rref_speed >= 70) {
        rref_speed = 70;
    }
    vel_msg.data = rref_speed;
    
    vel_pub.publish(vel_msg);

    debug_msg.pose.position.z = ref_speed;
    vel_debug.publish(debug_msg);

    new_vel = false;
    
    if (ttt > 5){
        new_target_vel = false;
    }
    
    ttt++;
    // std::cout << "target" << new_target_vel << std::endl;


}

void VelocityGenerator::viz_vel_prof(std::vector<double> profile)
{

    visualization_msgs::Marker vel_prof;

    vel_prof.header.frame_id = "map";
    vel_prof.header.stamp = ros::Time();
    vel_prof.ns = "vel_prof";
    vel_prof.id = 0;
    vel_prof.type = visualization_msgs::Marker::LINE_STRIP;
    vel_prof.action = visualization_msgs::Marker::ADD;

    if (profile.size() != 0)
    {
        for (int i = 0; i < profile.size(); i++)
        {
            geometry_msgs::Point p;
            if (i < traj.waypoints.size())
            {
                p.x = traj.waypoints[i].pose.pose.position.x;
                p.y = traj.waypoints[i].pose.pose.position.y;
                p.z = profile[i];

                vel_prof.points.push_back(p);
            }
            
        }
    }

    vel_prof.scale.x = 1;
    vel_prof.scale.y = 0;
    vel_prof.scale.z = 0;

    vel_prof.color.a = 1.0;
    vel_prof.color.r = 0.0;
    vel_prof.color.g = 1.0;
    vel_prof.color.b = 0.0;
   
    vel_vis_pub.publish(vel_prof);
}
void VelocityGenerator::trajCallback(const hmcl_msgs::Lane& msg)
{  
    if (local_traj_init){
        local_traj_init = true;
    }
    if (visualize){
        traj = msg;
    }

    double total_dis = 0.0;
    for (int i = 0; i < msg.waypoints.size()-1; i++)
    {   
        double _x = msg.waypoints[i].pose.pose.position.x;
        double x_ = msg.waypoints[i+1].pose.pose.position.x;
        double _y = msg.waypoints[i].pose.pose.position.y;
        double y_ = msg.waypoints[i+1].pose.pose.position.y;

        double dis = sqrt ( pow(x_- _x,2) + pow(y_ -_y,2));
        total_dis = dis + total_dis;
        speed_limit = msg.waypoints[i+1].twist.twist.linear.x/3.6;
        if (total_dis >= 15)
            break;
    }
    std::cout << "Get reference velocity: " << speed_limit << std::endl;

    
}


void VelocityGenerator::velCallback(const nav_msgs::Odometry& state_msg)
{
    // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
    current_vel = abs(state_msg.twist.twist.linear.x);


}

void VelocityGenerator::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg)
{
    // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
    current_vel = abs(state_msg.wheelspeed.wheel_speed);


}

void VelocityGenerator::targetCallback(const std_msgs::Float64& msg)
{
//   std::cout << "Get target velocity: "  << std::endl;
  target_acc_vel = msg.data;
  new_target_vel = true;
  ttt = 0;
}


void VelocityGenerator::accCallback(const geometry_msgs::Point& msg)
{
  current_acc = msg.x;
}

int main (int argc, char** argv)
{

    ros::init(argc, argv, "velocity_generator");

    ROS_INFO("velocity profile generator initialize");
    VelocityGenerator vel;


    ros::spin();
    
}
