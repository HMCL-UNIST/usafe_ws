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
#include "velocity_planner.h"

VelocityPlanner::VelocityPlanner()
{   
  ros::NodeHandle nh_;
  ROS_INFO("Behavior Velocity Planner initialize");

  // Prameter 
  nh_.param<double>("intersection_velocity", intersection_velocity, 10/3.6);
  nh_.param<double>("max_lateral_acc", max_lat_acc, 3.0);
  nh_.param<double>("max_longitudinal_acc", max_long_acc, 1.5);
  nh_.param<double>("stopline_margin", stopline_margin, 0);
  nh_.param<double>("crosswalk_margin", crosswalk_margin, 5);
  nh_.param<double>("stop_margin", stop_margin, 2);
  nh_.param<double>("vehicle_length", vehicle_length, 2);

  nh_.param<double>("delay_in_sec", delay_in_sec, 1);
  nh_.param<double>("dt", dt, 0.04); 
  nh_.param<double>("lag_tau", lag_tau, 0.6);
  nh_.param<double>("Q_vel", Q_vel, 10.0); 
  nh_.param<double>("Q_dis", Q_dis, 50.0); 
  nh_.param<double>("R_weight", r_weight, 1);
  nh_.param<double>("d_time", d_time, 2.0);
  nh_.param<double>("d_safe", d_safe, 15.0);
  delay_step = (int)(delay_in_sec/dt);


  new_behavior_mode = false;
  passcrosswalk = false;
  find_stopline = false;
  find_crosswalk = false;
  getLocalTraj = false;
  visualize = true;
  
  // Subscribe
  pose_sub = nh_.subscribe("/pose_estimate", 1, &VelocityPlanner::poseCallback, this);
  wheel_sub = nh_.subscribe("/vehicle_status", 1, &VelocityPlanner::wheelCallback, this);
  acc_sub = nh_.subscribe("/nav/filtered_imu/data", 1, &VelocityPlanner::accCallback, this);
  predicted_objects_sub = nh_.subscribe("/predicted_objs",1, &VelocityPlanner::PredictedObjectsCallback, this);

  // traffic_sign_sub = nh_.subscribe("", 1, &VelocityPlanner::TrafficSignCallback, this);    
  behavior_state_sub = nh_.subscribe("/behavior_state", 1, &VelocityPlanner::BehaviorStateCallback, this);
  behavior_state_condition_sub = nh_.subscribe("/behavior_factor", 1, &VelocityPlanner::BehaviorStateFactorCallback, this);
  // lanelet_map_sub = nh_.subscribe("", 1, &VelocityPlanner::LaneletCallback, this);
  local_traj_sub =  nh_.subscribe("/local_traj", 1, &VelocityPlanner::trajCallback,this);

  // Publish
  vel_pub = nh_.advertise<std_msgs::Float64>("/setpoint", 2, true);
  vel_debug  = nh_.advertise<geometry_msgs::PoseStamped>("/acc_debug", 2);
  vel_vis_pub = nh_.advertise<visualization_msgs::Marker>( "/ref_vel_prof_viz", 0 );
  motionstate_vis_pub = nh_.advertise<visualization_msgs::Marker>( "/motionstate_viz", 0 );

  boost::thread callbackhandler(&VelocityPlanner::callbackthread,this); 
}

void VelocityPlanner::callbackthread()
{   
    ros::Rate loop_rate(10); // rate  
    while(ros::ok()){
        PlanVel();
        loop_rate.sleep();
    }
}

void VelocityPlanner::PlanVel()
{
  // 1. Check the MOTIONSTATE
  // 2. Depending on the MOTIONSTATE, plan the velocity
  if (!getLocalTraj){
    ROS_INFO("NO LOCAL TRAJECTORY");
    return;
  }
  CheckMotionState();
  VelocitySmoother();

  std_msgs::Float64 vel_msg;
  vel_msg.data = ref_speed;
  vel_pub.publish(vel_msg);
}

void VelocityPlanner::CheckMotionState()
{ 
  double targetVel1,targetVel2;
  int s_idx, c_idx;

  if (CurrentMode ==  BehaviorState::Crosswalk) {
      // When Traffic sign is green or there is no trraffic sign, there is crosswalk in front of vehicle
      // 1) Check the stop line (If there is no stop line, make stop line)
      // 2) Reduce the velocity before reaching the stopline
      // 3) Check the stuck_vehicle in front of ego. 
    if (new_behavior_mode || !find_stopline){
      s_idx = FindStopLine();
      if (s_idx != -1){
        dis_x = traj.waypoints[s_idx].pose.pose.position.x;
        dis_y = traj.waypoints[s_idx].pose.pose.position.y;
        find_stopline = true;
      }
      else{
        c_idx = FindCrossWalk();
        if (c_idx != -1){
          dis_x = traj.waypoints[c_idx].pose.pose.position.x;
          dis_y = traj.waypoints[c_idx].pose.pose.position.y;
          find_stopline = true;
          find_crosswalk = true;
        }
      }
    }

    if (!find_stopline){
      std::cout << "FAIL TO FIND CROSSWALK in Crosswalk" << std::endl;
      MotionMode = MotionState::FAIL;
      targetVel1 = intersection_velocity;
    }
    else{
      if (find_crosswalk){
        Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - crosswalk_margin;
      }
      else{
        Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - stopline_margin;
      }

      Dis = std::min(Dis, 150.0); 
      DesiredDis = 0;
      DesiredVel = intersection_velocity;

      if (Dis <= stop_margin || passcrosswalk){
        MotionMode = MotionState::GO;
        targetVel1 = intersection_velocity;
        passcrosswalk = true;
      }
      else{
        MotionMode = MotionState::DECELERATE;
        targetVel1 = ACC();
      }
    }
    if (LeadVehicle){
      MotionMode = MotionState::ACC;
      targetVel2 = CheckLeadVehicle();
    }
    targetVel = std::min(targetVel1, targetVel2);
  }
  else if (CurrentMode ==  BehaviorState::Pedestrian) {
    // 1) If ego vehicle does not reach to stop line, stop at stop line
    //    If ego vehicle pass the stop line, recalculate the stop line based on stop margin
    if (passcrosswalk){
      targetVel = 0;
      MotionMode = MotionState::STOP;
    }
    else{
      if (new_behavior_mode || !find_stopline){
        s_idx = FindStopLine();
        if (s_idx != -1){
          dis_x = traj.waypoints[s_idx].pose.pose.position.x;
          dis_y = traj.waypoints[s_idx].pose.pose.position.y;
          find_stopline = true;
        }
        else{
          c_idx = FindCrossWalk();
          if (c_idx != -1){
            dis_x = traj.waypoints[c_idx].pose.pose.position.x;
            dis_y = traj.waypoints[c_idx].pose.pose.position.y;
            find_stopline = true;
            find_crosswalk = true;
          }
        }
      }
      if (!find_stopline){
        MotionMode = MotionState::FAIL;
        passcrosswalk = true;
        targetVel1 = 0;
      }
      else{
        if (find_crosswalk){
          Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - crosswalk_margin;
        }
        else{
          Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - stopline_margin;
        }

        Dis = std::min(Dis, 150.0); 
        DesiredDis = 0;
        DesiredVel = 0;

        if (Dis <= stop_margin){
          MotionMode = MotionState::STOP;
          targetVel1 = 0;
          passcrosswalk = true;
        }
        else{
          MotionMode = MotionState::DECELERATE;
          targetVel1 = ACC();
        }
      }
    }
  }
  else if (CurrentMode ==  BehaviorState::TrafficLightStop) {
      //1) Find the stop line
      //2) Decelerate before Stop Line
    if (new_behavior_mode || !find_stopline){
      s_idx = FindStopLine();
      if (s_idx != -1){
        dis_x = traj.waypoints[s_idx].pose.pose.position.x;
        dis_y = traj.waypoints[s_idx].pose.pose.position.y;
        find_stopline = true;
      }
    }
    if (!find_stopline){
      std::cout << "FAIL TO FIND STOPLINE in TrafficLightStop" << std::endl;
      MotionMode = MotionState::FAIL;
      targetVel = MaxVel;
    }
    else{
      Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2) ) - stopline_margin;
      Dis = std::min(Dis, 150.0); 
      DesiredDis = 0;
      DesiredVel = 0;   

      if (Dis <= stop_margin){
        MotionMode = MotionState::STOP;
        targetVel1 = 0;
      }
      else{
        MotionMode = MotionState::GO;
        targetVel1 = ACC();
      }
    }  
    if (LeadVehicle){
      MotionMode = MotionState::ACC;
      targetVel2 = CheckLeadVehicle();
    }
    targetVel = std::min(targetVel1, targetVel2);
    
  }
  else if (CurrentMode ==  BehaviorState::SpeedBump) {
      // Reduce the velocity to 10km/h
      targetVel = 10/3.6;
      MaxVel = 10/3.6;

  }
  else if (CurrentMode ==  BehaviorState::Follow){
    //Adaptive Cruise Control
    double DesiredDis = current_vel*d_time + d_safe;
    double Dis = sqrt( pow(current_x-object_x,2) + pow(current_y-object_y,2)) - stopline_margin;
    Dis = std::min(Dis, 150.0); 
    
    double DesiredVel = object_vel; //- current_vel;    

    // velocity difference is not greater than the speed limit ... 
    if(DesiredVel > 0){
      DesiredVel = std::min(DesiredVel, MaxVel);
    }    
    if(DesiredVel < 0){
      DesiredVel = std::max(DesiredVel, -MaxVel6);
    }
    targetVel = ACC();
    MotionMode = MotionState::ACC;

  }
  else if (CurrentMode ==  BehaviorState::LeftTurn){
     //1) If PreviousMode is TrafficLightStop, 
     //2) If PreviousMode is Forward, check the possibility to pass 
     //3) Check the lead vehicle existence
    targetVel = intersection_velocity ;
    MotionMode = MotionState::GO;
  }
  else if (CurrentMode ==  BehaviorState::RightTurn){
    //1) check the stop line (If there is no stop line, make stop line)  
    //2) Reduce the velocity before reaching the stopline

    targetVel = intersection_velocity; 
    MotionMode = MotionState::GO;
    // if (new_behavior_mode){
    //   s_idx = FindStopLine();
    //   if (s_idx != -1){
    //     dis_x = traj[s_idx].waypoints.pose.pose.position.x;
    //     dis_y = traj[s_idx].waypoints.pose.pose.position.y;
    //     find_stopline = true;
    //   }
    //   else{
    //     c_idx = FindCrossWalk();
    //     j_idx = FindJunction();
    //     if (c_idx != -1){
    //       dis_x = traj[c_idx].waypoints.pose.pose.position.x;
    //       dis_y = traj[c_idx].waypoints.pose.pose.position.y;
    //       find_stopline = true;
    //       find_crosswalk = true;
    //     }
    //     else if (j_idx != -1){
    //       dis_x = traj[j_idx].waypoints.pose.pose.position.x;
    //       dis_y = traj[j_idx].waypoints.pose.pose.position.y;
    //       find_stopline = true;
    //       find_junction = true;
    //     }
    //   }
    }
  else if(CurrentMode ==  BehaviorState::Init){
    targetVel = 0;
    MotionMode = MotionState::STOP; 
  }
  else{
    targetVel = MaxVel;
    MotionMode = MotionState::GO; 
  }
  viz_motionstate();
}
//STOPLINE FUNCTION
int VelocityPlanner::FindStopLine(){
  bool b_cross;
  int stop_idx;
  for (int i = 0; i < traj.waypoints.size(); i++)
  {   
      b_cross = traj.waypoints[i].Stop_line;
      if (b_cross == true){
        stop_idx = i;
        break;
      }
      else{
        stop_idx = -1;
      }
  }
  return stop_idx;
}

int VelocityPlanner::FindCrossWalk(){
  bool b_cross;
  int cross_idx;
  for (int i = 0; i < traj.waypoints.size(); i++)
  {   
      b_cross = traj.waypoints[i].Crosswalk;
      if (b_cross == true){
        cross_idx = i;
        break;
      }
      else{
        cross_idx = -1;
      }
  }
  return cross_idx;
}


double VelocityPlanner::CheckLeadVehicle(){
  //Adaptive Cruise Control
  
  double DesiredDis = current_vel*d_time + d_safe;
  double Dis = sqrt( pow(current_x-object_x,2) + pow(current_y-object_y,2) );
  Dis = std::min(Dis, 150.0); 
  double DesiredVel = object_vel; //- current_vel;    

  // velocity difference is not greater than the speed
  if(DesiredVel > 0){
    DesiredVel = std::min(DesiredVel, MaxVel/3.6);
  }    
  if(DesiredVel < 0){
    DesiredVel = std::max(DesiredVel, -MaxVel/3.6);
  }
  targetVel = ACC();
  return targetVel;
}
//ACC FUNCTION
double VelocityPlanner::ACC()
{ 
    auto start = std::chrono::steady_clock::now();

    Xk = Eigen::VectorXd::Zero(3,1);
    Xk(0) = DesiredDis - Dis;
    
    Xk(1) = DesiredVel;
    Xk(2) = current_acc;

    computeMatrices();

    double vel_cmd = current_vel + acc_cmd * dt;
    vel_cmd = std::min(std::max(vel_cmd,0.0), MaxVel/3.6);    

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if ( elapsed_seconds.count() > dt){
      ROS_ERROR("computing control gain takes too much time");
      std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    return vel_cmd;
}

void VelocityPlanner::computeMatrices(){
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

double VelocityPlanner::computeGain(){    

  Eigen::MatrixXd Kb = Eigen::MatrixXd::Zero(3,3);
  Eigen::MatrixXd invertMtx = (mcR+mcBd.transpose()*mcP*mcBd).inverse()*mcBd.transpose();

  Kb = invertMtx*mcP*mcAd;

  Eigen::MatrixXd cmd = -1*Kb*Xk;
  return cmd(0,0);
}

bool VelocityPlanner::solveRiccatiIterationD(const Eigen::MatrixXd &Ad,
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


//VELOCITY SMOOTHER FUNCTION
void VelocityPlanner::VelocitySmoother()
{
  double v0 = current_vel;
  double a0 = current_acc;
  ref_speed = v0;
  double time = 0.5;
  double P[3] = {1.0,1.0,5.0};
  double SF0;
  if (MotionMode == MotionState::GO){
    SF0 = 15;
  }
  else if (MotionMode == MotionState::STOP){
    ref_speed = 0;
    return;
  }
  else{
    SF0 = Dis;
  }
  double xf[3] = {SF0, MaxVel, 0};

  if (targetVel < MaxVel){
    xf[1] = targetVel;
  } 

  if (previous_step) {
      std::cout << "**Previous Status is FAIL**" << std::endl;
      xf[1] = xf[1]*0.5;
      xf[0] = 20;
  }
  
  bool fail2solve = false;  
  int k = 0;
  while(1)
  {   
      double sf = v0*P[2] + 1/2*a0*pow(P[2],2) + 1/3*P[0]*pow(P[2],3) + 1/4*P[1]*pow(P[2],4);
      double vf = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
      double af = a0 + 2*P[0]*P[2] + 3*P[1]*pow(P[2],2);
      
      double del_x[3] = {xf[0] - sf, xf[1]- vf, xf[2]- af};

      if (abs(del_x[0]) < 0.1 && abs(del_x[1]) < 0.1 && abs(del_x[2]) < 0.1) {        
        if (P[2] > time) {
          ref_speed = v0 + a0*time + P[0]*pow(time,2) + P[1]*pow(time,3);
        }
        else{
          ref_speed = v0 + a0*P[2] + P[0]*pow(P[2],2) + P[1]*pow(P[2],3);
        }
        if (xf[1] == 0 && current_vel < 1){
          ref_speed = 0;
        }

        double N = P[2]/0.2;

        std::vector<double> profile{};
        double tt = 0.0;
        for (int i = 0; i < N; i++){
            profile.push_back(v0 + a0*tt + P[0]*pow(tt,2) + P[1]*pow(tt,3));
            tt = tt + 0.2;   
        }
        // std::cout << "Calculate the velocity: c_vel" << current_vel << "r_vel" << ref_speed << std::endl;
        if (visualize)
        {
            viz_vel_prof(profile);
        }
        previous_step = false;
        break;
      }
      else if (k >= 50 || fail2solve) {
        ref_speed = xf[1];
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
  
  ref_speed = std::min(ref_speed, MaxVel);
}

//CALLBACK FUNCTION
void VelocityPlanner::poseCallback(const nav_msgs::Odometry& state_msg)
{
  current_x = state_msg.pose.pose.position.x;
  current_y = state_msg.pose.pose.position.y;
}

void VelocityPlanner::accCallback(const sensor_msgs::Imu& msg)
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

void VelocityPlanner::PredictedObjectsCallback(const autoware_msgs::DetectedObjectArray& msg)
{
  if( msg.objects.size() <= 0){    
    return;    
  }

  // ros::Duration tt_ = ros::Time::now() - obj_time;
  // obj_time = ros::Time::now();


  if (LeadVehicle){
    object_x = msg.objects[LeadVehicleInd].pose.position.x;
    object_y = msg.objects[LeadVehicleInd].pose.position.y;
    double rel_vel = msg.objects[0].velocity.linear.x;
  }
  // if (Pedestrian){
  // }
  
}

void VelocityPlanner::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg)
{
    // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
    current_vel = abs(state_msg.wheelspeed.wheel_speed);
}
void VelocityPlanner::trajCallback(const hmcl_msgs::Lane& msg)
{  
  if(msg.waypoints.size() < 1){
      return;
  }
  getLocalTraj = true;
  MaxVel = 30/3.6;

  double dis = 0;
  double old_dis = 150;
  double current_idx = 0;
  // double total_dis = 0.0;
  if (msg.waypoints.size() == 0)
    return;

  for (int i = 0; i < msg.waypoints.size(); i++)
  {   
    double _x = msg.waypoints[i].pose.pose.position.x;
    double _y = msg.waypoints[i].pose.pose.position.y;


    dis = sqrt ( pow(current_x- _x,2) + pow(current_y -_y,2));
    if (dis < old_dis)
      current_idx = i;
    old_dis = dis;
  }

  for (int i = current_idx; i < msg.waypoints.size(); i++){
    traj.waypoints.push_back(msg.waypoints[i]);
  }
  // std::copy(msg.waypoints.begin()+current_idx,msg.waypoints.end(),traj.waypoints.begin());

  
  std::cout << "Get reference velocity: " << MaxVel << std::endl;
}

void VelocityPlanner::BehaviorStateCallback(const std_msgs::Int16& msg){
  CurrentMode =(BehaviorState)msg.data;
  if (CurrentMode == BehaviorState::Init){
    PreviousMode = CurrentMode;
    return;
  }
  else if (PreviousMode == BehaviorState::Crosswalk && CurrentMode == BehaviorState::Pedestrian){
    new_behavior_mode = true;
    passcrosswalk = false;
    wait_tt = 0;
  }
  else if (PreviousMode != CurrentMode){
    new_behavior_mode = true;
    find_stopline = false;
    find_crosswalk = false;
    passcrosswalk = false;
    wait_tt = 0;
  }
  else{
    new_behavior_mode = false;
  }
  
  PreviousMode = CurrentMode;

}

void VelocityPlanner::BehaviorStateFactorCallback(const hmcl_msgs::BehaviorFactor& msg){
  LeadVehicleInd = msg.front_id;
  if (LeadVehicleInd != -1)
  {
    LeadVehicle = true;
  }
  // PassStopLine = msg.stop_line_stop;
}


void VelocityPlanner::viz_motionstate()
{

  visualization_msgs::Marker motionstate;

  motionstate.header.frame_id = "map";
  motionstate.header.stamp = ros::Time();
  motionstate.ns = "vel_prof";
  motionstate.id = 0;
  motionstate.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  motionstate.action = visualization_msgs::Marker::ADD;

  motionstate.pose.position.x = current_x;
  motionstate.pose.position.y = current_y;
  motionstate.pose.position.z = 2;

  motionstate.scale.z = 10;
  motionstate.text = stateToStringMotion(MotionMode);

  motionstate.color.a = 1.0;
  motionstate.color.r = 0.0;
  motionstate.color.g = 1.0;
  motionstate.color.b = 0.0;
  
  motionstate_vis_pub.publish(motionstate);
}

void VelocityPlanner::viz_vel_prof(std::vector<double> profile)
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


int main (int argc, char** argv)
{

    ros::init(argc, argv, "velocity_planner");

    VelocityPlanner vel;

    ros::spin();
    
}
