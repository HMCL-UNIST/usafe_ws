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
#include "acc_node.h"


ACC::ACC()
{   
    ros::NodeHandle nh_;
    ROS_INFO("Adaptive Cruise Control initialize");

    // Prameter 
    nh_.param<double>("delay_in_sec", delay_in_sec, 1);
    nh_.param<double>("dt", dt, 0.04); 
    nh_.param<double>("lag_tau", lag_tau, 0.6);
    nh_.param<double>("Q_vel", Q_vel, 10.0); 
    nh_.param<double>("Q_dis", Q_dis, 0.6); 
    nh_.param<double>("R_weight", r_weight, 3000);

    nh_.param<double>("d_time", d_time, 2.0);
    nh_.param<double>("d_safe", d_safe, 10.0);

    delay_step = (int)(delay_in_sec/dt);

    // Subscribe
    target_sub = nh_.subscribe("/detected_objs",1, &ACC::objectCallback,this);
    pose_sub = nh_.subscribe("/pose_estimate", 1, &ACC::poseCallback, this);
    acc_sub = nh_.subscribe("/bias_acc", 1, &ACC::accCallback, this);

    // Publish
    target_vel_pub = nh_.advertise<std_msgs::Float64>("/acc_target_vel", 1, true);
    vel_debug  = nh_.advertise<geometry_msgs::PoseStamped>("/acc_debug", 2);



}

void ACC::CalcVel()
{ 
    auto start = std::chrono::steady_clock::now();

    double safe_dis = current_vel*d_time + d_safe;
    double dis2obj = sqrt( pow(current_x-object_x,2) + pow(current_y-object_y,2) );

    double diffvel = object_vel - current_vel;

    Xk = Eigen::VectorXd::Zero(3,1);
    Xk(0) = safe_dis + dis2obj;
    Xk(1) = diffvel;
    Xk(2) = current_acc;


    computeMatrices();


    double vel_cmd = current_vel + acc_cmd * dt;

    //Publish
    std_msgs::Float64 target_vel;
    target_vel.data = vel_cmd;
    target_vel_pub.publish(target_vel);
  


    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if ( elapsed_seconds.count() > dt){
      ROS_ERROR("computing control gain takes too much time");
      std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    debug_msg.header.stamp = ros::Time::now();
    debug_msg.pose.position.x = safe_dis + dis2obj;
    debug_msg.pose.position.y = diffvel;
    vel_debug.publish(debug_msg);


}

void ACC::computeMatrices(){

  if(delay_step < 1){
      ROS_ERROR("delay step is less than 1");
      return; 
  }

  Abaroc = Eigen::MatrixXd::Zero(2,2);    
  Bbaroc = Eigen::MatrixXd::Zero(2,1);

  Abarc  = Eigen::MatrixXd::Zero(3,3);
  Bbarc  = Eigen::MatrixXd::Zero(3,1);

  mcAd     = Eigen::MatrixXd::Zero(3,3);
  mcBd     = Eigen::MatrixXd::Zero(3,1);

  mcQ    = Eigen::MatrixXd::Zero(3,3);     
  mcR    = Eigen::MatrixXd::Zero(1,1);

  std::vector<double> q_weight = {Q_dis, Q_vel};
  for(int i =0; i< q_weight.size(); i++){
    mcQ(i,i) = q_weight[i];
  }
  mcR(0,0) = r_weight; 


  Abaroc(1, 1) = -1;

  Bbaroc(0,0) = d_time;
  Bbaroc(1,0) = 1;

  Abarc.block<2,2>(0,0) = Abaroc;
  Abarc.block<2,1>(0,2) = Bbaroc;
  Abarc.block<1,2>(2,0) = Eigen::MatrixXd::Zero(1,2);
  Abarc(2,2) = -1/lag_tau;

  Bbarc(2,0) = 1/lag_tau;

  // Bilinear transform , continuous to discrete 
  Eigen::MatrixXd Ix = Eigen::MatrixXd::Identity(3,3);
  Eigen::MatrixXd Ad_inverse = (Ix - dt * 0.5 * Abarc).inverse();
  mcAd =  Ad_inverse * (Ix + dt * 0.5 * Abarc);
  mcBd = Ad_inverse * dt *Bbarc;

  mcP = Eigen::MatrixXd::Zero(3, 3);
  bool riccati_solved = solveRiccatiIterationD(mcAd, mcBd, mcQ, mcR, mcP);

  if (!riccati_solved){
    ROS_WARN("-----------solution not found------------control lost"); 
  }

  acc_cmd = computeGain();
}

double ACC::computeGain(){    
 
  
  Eigen::MatrixXd Kb = Eigen::MatrixXd::Zero(3,3);
  Eigen::MatrixXd invertMtx = (mcR+mcBd.transpose()*mcP*mcBd).inverse()*mcBd.transpose();

  Kb = invertMtx*mcP*mcAd;

  Eigen::MatrixXd cmd = -1*Kb*Xk;

  
  return cmd(0,0);
}

bool ACC::solveRiccatiIterationD(const Eigen::MatrixXd &Ad,
                            const Eigen::MatrixXd &Bd, const Eigen::MatrixXd &Q,
                            const Eigen::MatrixXd &R, Eigen::MatrixXd &P,
                            const double &tolerance,
                            const uint iter_max) {
  P = Q; // initialize

  Eigen::MatrixXd P_next;

  Eigen::MatrixXd AdT = Ad.transpose();
  Eigen::MatrixXd BdT = Bd.transpose();
  Eigen::MatrixXd Rinv = R.inverse();

  double diff;
  for (uint i = 0; i < iter_max; ++i) {
    // -- discrete solver --
    P_next = AdT * P * Ad -
             AdT * P * Bd * (R + BdT * P * Bd).inverse() * BdT * P * Ad + Q;

    diff = fabs((P_next - P).maxCoeff());
    P = P_next;
    if (diff < tolerance) {
    //   std::cout << "iteration mumber = " << i << std::endl;
      return true;
    }
  }
  return false;
}




void ACC::poseCallback(const nav_msgs::Odometry& state_msg)
{
  current_vel = abs(state_msg.twist.twist.linear.x);
  current_x = state_msg.pose.pose.position.x;
  current_y = state_msg.pose.pose.position.y;


}

void ACC::accCallback(const geometry_msgs::Point& msg)
{
  current_acc = msg.x;
}

void ACC::objectCallback(const autoware_msgs::DetectedObjectArray& msg)
{
  
  object_x = msg.objects[0].pose.position.x;
  object_y = msg.objects[0].pose.position.y;
  object_vel = msg.objects[0].velocity.linear.x;

  CalcVel();
  
}

int main (int argc, char** argv)
{

    ros::init(argc, argv, "acc_node");

    ros::Rate loop_rate(20);
    ROS_INFO("Adaptive Cruise Control Initialize");
    ACC acc;

    ros::spin();
    
}
