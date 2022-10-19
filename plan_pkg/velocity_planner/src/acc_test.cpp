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
#include "acc_test.h"

ACC::ACC()
{   
  ros::NodeHandle nh_;
  ROS_INFO("Adaptive Cruise Control initialize");

  nh_.param<double>("delay_in_sec", delay_in_sec, 1);
  nh_.param<double>("dt", dt, 0.04); 
  nh_.param<double>("lag_tau", lag_tau, 0.6);
  nh_.param<double>("Q_vel", Q_vel, 20.0); 
  nh_.param<double>("Q_dis", Q_dis, 50.0); 
  nh_.param<double>("R_weight", r_weight, 1);
  nh_.param<double>("d_time", d_time, 2.0);
  nh_.param<double>("d_safe", d_safe, 12.0);
  nh_.param<bool>("simulation", simulation, true);
  delay_step = (int)(delay_in_sec/dt);
  runtime = 20;

  // Subscribe
  pose_sub = nh_.subscribe("/pose_estimate", 1, &ACC::poseCallback, this);
  wheel_sub = nh_.subscribe("/vehicle_status", 1, &ACC::wheelCallback, this);
  acc_sub = nh_.subscribe("/nav/filtered_imu/data", 1, &ACC::accCallback, this);
  
  if (simulation){
    predicted_objects_sub = nh_.subscribe("/detected_objs",1, &ACC::PredictedObjectsCallback, this);
  }
  else{
    predicted_objects_sub = nh_.subscribe("/tracking_car/object",1, &ACC::PredictedObjectsCallback, this);
  }
  vel_pub = nh_.advertise<std_msgs::Float64>("/setpoint", 2, true);
  vel_debug  = nh_.advertise<geometry_msgs::PoseStamped>("/acc_debug", 2);
 
  boost::thread callbackhandler(&ACC::callbackthread,this); 

  f = boost::bind(&ACC::dyn_callback,this, _1, _2);
	srv.setCallback(f);

}

void ACC::dyn_callback(velocity_planner::testConfig &config, uint32_t level)
{
  ROS_INFO("Reconfigure Request");
  lag_tau = config.lag_tau;
  Q_vel = config.Q_vel;
  Q_dis = config.Q_dis;
  r_weight = config.R_weight;
  d_time = config.d_time;
  d_safe = config.d_safe;
}

void ACC::callbackthread()
{   
    ros::Rate loop_rate(runtime); // rate  
    while(ros::ok()){
        CheckLeadVehicle();
        
        loop_rate.sleep();
    }
}


void ACC::CheckLeadVehicle(){
  //Adaptive Cruise Control
  
  obj_time += 1;
  if (obj_time >= 100){
    ROS_INFO("NO OBJECT HERE");
    std_msgs::Float64 vel_msg;
    // vel_msg.data = 22/3.6;
    vel_pub.publish(vel_msg);
    return;
  }

  
  DesiredDis = current_vel*d_time + d_safe;
  Dis = LeadVehicleDist;
  Dis = std::min(Dis, 150.0); 
  double DesiredVel = rel_vel; //- current_vel;   
  

  // velocity difference is not greater than the speed
  if(DesiredVel > 0){
    DesiredVel = std::min(DesiredVel, 5/3.6);
  }    
  if(DesiredVel < 0){
    DesiredVel = std::max(DesiredVel, 0.0);
  }
  double targetVel = vel_acc();
  ROS_INFO(":::::::::::OBJECT HERE:::   dis: %f, vel: %f, Desired: %f", Dis,rel_vel,targetVel); 

  if (targetVel < 0.8 || isnan(targetVel)){
    targetVel = 0;
  }
  else if (targetVel > 5/3.6){
    targetVel=5/3.6;
  }

  std_msgs::Float64 vel_msg;
  vel_msg.data = targetVel;
  vel_pub.publish(vel_msg);
}

//ACC FUNCTION
double ACC::vel_acc()
{ 
    auto start = std::chrono::steady_clock::now();

    Xk = Eigen::VectorXd::Zero(3,1);
    Xk(0) = DesiredDis - Dis;
    
    Xk(1) = DesiredVel;
    Xk(2) = current_acc;

    computeMatrices();

    double vel_cmd = current_vel + acc_cmd * dt;
    vel_cmd = std::min(std::max(vel_cmd,0.0), 5/3.6);    

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if ( elapsed_seconds.count() > dt){
      ROS_ERROR("computing control gain takes too much time");
      std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    return vel_cmd;
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


//CALLBACK FUNCTION
void ACC::poseCallback(const nav_msgs::Odometry& state_msg)
{
  current_x = state_msg.pose.pose.position.x;
  current_y = state_msg.pose.pose.position.y;
}

void ACC::accCallback(const sensor_msgs::Imu& msg)
{ 
  current_acc = msg.linear_acceleration.x;
    // Physically our vehicle shouldnt move above or below threadhold acc +-5m/s^2
  if (current_acc > 0){
      current_acc  = std::min(current_acc,5.0);
  }
  if (current_acc < 0){
    current_acc  = std::max(current_acc,-5.0);
  }
}

void ACC::PredictedObjectsCallback(const autoware_msgs::DetectedObjectArray& msg)
{
  if( msg.objects.size() <= 0){    
    return;    
  }

  obj_time = 0;
  // ROS_INFO("DETECT!!!");
  // ros::Duration tt_ = ros::Time::now() - obj_time;
  // obj_time = ros::Time::now();

  object_x = msg.objects[0].pose.position.x;
  object_y = msg.objects[0].pose.position.y;
  LeadVehicleDist = sqrt(pow((object_x - current_x),2)+pow((object_y - current_y),2));
  // double vel_ = dist_/(tt_.toSec()+1e-9);
  // if(abs(vel_) < 1.0){
  //   vel_ = 0.0;
  // }
  prev_object_x = object_x;
  prev_object_y = object_y;

  double obj_vel = msg.objects[0].velocity.linear.x;

  rel_vel = obj_vel;

}
void ACC::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg)
{
  // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
  current_vel = abs(state_msg.wheelspeed.wheel_speed);
}



int main (int argc, char** argv)
{

    ros::init(argc, argv, "acc_test");

    ACC acc;

    ros::spin();
    
}