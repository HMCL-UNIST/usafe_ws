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
  nh_.param<double>("intersection_velocity", intersection_velocity, 7);
  nh_.param<double>("speedbump_velocity", speedbump_velocity, 10);
  nh_.param<double>("max_lateral_acc", max_lat_acc, 4.0);
  nh_.param<double>("max_longitudinal_acc", max_long_acc, 1.5);
  nh_.param<double>("stopline_margin", stopline_margin, 0);
  nh_.param<double>("mission_margin", mission_margin, 5);
  nh_.param<double>("crosswalk_margin", crosswalk_margin, 20);
  nh_.param<double>("stop_margin", stop_margin, 10);
   nh_.param<double>("judge_margin", judge_margin, 15);
  nh_.param<double>("vehicle_length", vehicle_length, 2);

  nh_.param<double>("delay_in_sec", delay_in_sec, 1);
  nh_.param<double>("dt", dt, 0.04); 
  nh_.param<double>("lag_tau", lag_tau, 0.6);
  nh_.param<double>("Q_vel", Q_vel, 20.0); 
  nh_.param<double>("Q_dis", Q_dis, 50.0); 
  nh_.param<double>("R_weight", r_weight, 1);
  nh_.param<double>("d_time", d_time, 4.0);
  nh_.param<double>("d_safe", d_safe, 15.0);
  delay_step = (int)(delay_in_sec/dt);
  runtime = 20;

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
  // predicted_objects_sub = nh_.subscribe("/tracking_car/object",1, &VelocityPlanner::PredictedObjectsCallback, this);
  target_sub = nh_.subscribe("/detected_objs",1, &VelocityPlanner::objectCallback,this);

  // traffic_sign_sub = nh_.subscribe("", 1, &VelocityPlanner::TrafficSignCallback, this);    
  behavior_state_sub = nh_.subscribe("/behavior_state", 1, &VelocityPlanner::BehaviorStateCallback, this);
  behavior_state_condition_sub = nh_.subscribe("/behavior_factor", 1, &VelocityPlanner::BehaviorStateFactorCallback, this);
  // lanelet_map_sub = nh_.subscribe("", 1, &VelocityPlanner::LaneletCallback, this);
  local_traj_sub =  nh_.subscribe("/local_traj", 1, &VelocityPlanner::trajCallback,this);
  start_end_sub =  nh_.subscribe("/start_goal_pose", 1, &VelocityPlanner::startendCallback,this);
  v2x_spat_sub = nh_.subscribe("/SPAT",1, &VelocityPlanner::v2xSPATCallback, this);
  // Publish
  vel_pub = nh_.advertise<std_msgs::Float64>("/setpoint", 2, true);
  vel_debug  = nh_.advertise<geometry_msgs::PoseStamped>("/acc_debug", 2);
  vel_vis_pub = nh_.advertise<visualization_msgs::Marker>( "/ref_vel_prof_viz", 1 );
  motionstate_vis_pub = nh_.advertise<visualization_msgs::MarkerArray>( "/motionstate_viz", 1 );

  boost::thread callbackhandler(&VelocityPlanner::callbackthread,this); 
}

void VelocityPlanner::callbackthread()
{   
    ros::Rate loop_rate(runtime); // rate  
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
  else if (!getBehavior){
    ROS_INFO("NO Behavior PLANNER");
    return;
  }
  else if (!getMission){
    ROS_INFO("NO MISSON NODE");
    return;
  }
  mob_tt ++;
  if (mob_tt >= 20){
    Mobileye = false;
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
  int s_idx, c_idx, j_idx;
  motionstate_debug = ".";
  Dis = 0.0;
  // ROS_INFO("frontdist: %f", LeadVehicleDist);
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
      // std::cout << "FAIL TO FIND CROSSWALK in Crosswalk" << std::endl;
      MotionMode = MotionState::FAIL;
      targetVel1 = speedbump_velocity/3.6;
      motionstate_debug = "FAIL TO FIND CROSSWALK in Crosswalk";
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

      if (Dis <= stop_margin && passcrosswalk){
        MotionMode = MotionState::STOP;
        motionstate_debug = "At the stop line";
        targetVel1 = speedbump_velocity/3.6;
        passcrosswalk = true;
      }
      else{
        // Dis = std::min(Dis, 15.0);
        MotionMode = MotionState::DECELERATE;
        motionstate_debug = "Before the stop line: Distance is" + to_string(Dis);
        targetVel1 = ACC();
      }
    }
    if (LeadVehicle){
      targetVel2 = CheckLeadVehicle();
      targetVel = std::min(targetVel1, targetVel2);
      if (targetVel2 <= targetVel1){
        MotionMode = MotionState::ACC;
        motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);
      }  
    }
    else{
      targetVel = targetVel1;
    }
  }
  else if (CurrentMode ==  BehaviorState::Pedestrian) {
    // 1) If ego vehicle does not reach to stop line, stop at stop line
    //    If ego vehicle pass the stop line, recalculate the stop line based on stop margin
    if (passcrosswalk){
      targetVel = 0;
      MotionMode = MotionState::STOP;
      motionstate_debug = "Pass the stop line: Just stop!";
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
        motionstate_debug = "FAIL TO FIND STOPLINE in Pedestrian: Just Stop!";
        // std::cout << "FAIL TO FIND STOPLINE in Pedestrian" << std::endl;
        passcrosswalk = true;
        targetVel = 0;
      }
      else{
        if (find_crosswalk){
          Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - crosswalk_margin;
        }
        else{
          Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - stopline_margin;
        }

        Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2)) - stopline_margin;
        Dis = std::min(Dis, 150.0); 
        DesiredDis = 0;
        DesiredVel = 0;

        if (Dis <= stop_margin){
          MotionMode = MotionState::STOP;
          motionstate_debug = "At the stopline: Distance is" + to_string(Dis);
          targetVel = 0;
          passcrosswalk = true;
        }
        else{
          // MotionMode = MotionState::DECELERATE;
          // motionstate_debug = "Before the stop line: Distance is" + to_string(Dis);
          // targetVel1 = ACC();
          targetVel = 0;
          MotionMode = MotionState::STOP;
        }
      }
    }
  }
  else if (CurrentMode ==  BehaviorState::TrafficLightStop) {
      //1) Find the stop line
      //2) Decelerate before Stop Line
    checkTrafficSignal(0);
    if (new_behavior_mode || !find_stopline){
      s_idx = FindStopLine();
      if (s_idx != -1){
        dis_x = traj.waypoints[s_idx].pose.pose.position.x;
        dis_y = traj.waypoints[s_idx].pose.pose.position.y;
        find_stopline = true;
      }
    }
    if (passcrosswalk){
      MotionMode = MotionState::STOP;
      targetVel = 0;
    }
    else if (!find_stopline){
      // std::cout << "FAIL TO FIND STOPLINE in TrafficLightStop" << std::endl;
      motionstate_debug = "FAIL TO FIND STOPLINE in TrafficLightStop";
      MotionMode = MotionState::FAIL;
      targetVel = 0;
    }
    else{
      Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2) ) - stopline_margin;
      Dis = std::min(Dis, 150.0); 
      DesiredDis = 0;
      DesiredVel = 0;   

      if (Dis <= stop_margin){
        MotionMode = MotionState::STOP;
        motionstate_debug = "Before the stop line: Distance is" + to_string(Dis)
        + ", Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
        targetVel1 = 0;
      }
      else{
        // Dis = std::min(Dis, 15.0);
        MotionMode = MotionState::DECELERATE;
        motionstate_debug = "Before the stop line: Distance is" + to_string(Dis)
        + ", Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
        targetVel1 = ACC();
      }
    }  
    if (LeadVehicle){
      targetVel2 = CheckLeadVehicle();
      targetVel = std::min(targetVel1, targetVel2);
      if (targetVel2 <= targetVel1){
        MotionMode = MotionState::ACC;
        motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);
      }  
    }
    else{
      targetVel = targetVel1;
    }
  }

  else if (CurrentMode ==  BehaviorState::SpeedBump) {
      // Reduce the velocity to 10km/h
      targetVel = speedbump_velocity/3.6;
      MaxVel = speedbump_velocity/3.6;
      MotionMode = MotionState::GO;
  }

  else if (CurrentMode ==  BehaviorState::Follow){
    //Adaptive Cruise Control
    double DesiredDis = current_vel*d_time + d_safe;
    if (Mobileye){
      ROS_INFO("********Mobileye************");
      Dis = LeadVehicleDist_m;
      DesiredVel = LeadVehicleVel_m + current_vel; //- current_vel; 
    }
    else{
      Dis = LeadVehicleDist;
      DesiredVel = 0.0; //- current_vel;  
    }
     
    
    Dis = std::min(Dis, 150.0); 

    ROS_INFO("-------Current Distance is %f", Dis);   
    ROS_INFO("-------Current velocity is %f", current_vel);
    ROS_INFO("--------Desired velocity is %f", DesiredVel);
    
    if (isinf(DesiredVel) || isnan(DesiredVel)){
      DesiredVel = 0.0;
    }
    if (DesiredVel <= 0.5){
      DesiredVel = 0.0;
    }
    // velocity difference is not greater than the speed limit ... 
    if(DesiredVel > 0){
      DesiredVel = std::min(DesiredVel, 15/3.6);
    }    
    if(DesiredVel < 0){
      DesiredVel = std::max(DesiredVel, -15/3.6);
    }


    if (Dis <= 15 && DesiredVel <= 0.8){
      targetVel = 0.0;
    }
    else{
      targetVel = ACC();
    }
    MotionMode = MotionState::ACC;
    motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);

  }
  else if (CurrentMode ==  BehaviorState::RightTurn){
     //1) If PreviousMode is TrafficLightStop, 
     //2) If PreviousMode is Forward, check the possibility to pass 
     //3) Check the lead vehicle existence
    
    checkTrafficSignal(0);
    double vel = intersection_velocity/3.6;
    // double vel = Curvature();

    if (eventState == -1 || timing_min_End_Time == -1){
      MotionMode = MotionState::GO;
      motionstate_debug = "No traffic light";
      targetVel1 = vel;
      if (lane_id == 7){
        targetVel1 = intersection_velocity/3.6;
      }
    }
    else{
      if (passcrosswalk){
        if (!find_judgeline){
          j_idx = FindJudgeLine();
          if (j_idx != -1){
            dis_x = traj.waypoints[j_idx].pose.pose.position.x;
            dis_y = traj.waypoints[j_idx].pose.pose.position.y;
            find_judgeline = true;
          }
        }
        if (!find_judgeline){
          // std::cout << "FAIL TO FIND Judgeline in Crosswalk" << std::endl;
          MotionMode = MotionState::FAIL;
          targetVel1 = vel;
        }
        else {
          Dis = sqrt( pow(current_x-dis_x,2) + pow(current_y-dis_y,2));
          // Dis = std::min(Dis, 150.0); 
          DesiredDis = 0;
          DesiredVel = speedbump_velocity/3.6;

          // if (!passjudgeline){
          //   if ( eventState != 5 || eventState != 6){
          //     MotionMode = MotionState::STOP;
          //     motionstate_debug = "Before the judge line: Distance is" + to_string(Dis);
          //     targetVel1 = 0;
          //   }
          //   else if (timing_min_End_Time <= 7) {
          //     MotionMode = MotionState::STOP;
          //     motionstate_debug = "Before the judge line: Distance is" + to_string(Dis);
          //     targetVel1 = 0;
          //   }
          // }

          if (Dis <= stop_margin || !passjudgeline){
            MotionMode = MotionState::GO;
            motionstate_debug = "After the judge line: Distance is" + to_string(Dis);
            targetVel1 = DesiredVel;
            passjudgeline = true;
          }
          else{
            // Dis = std::min(Dis, 15.0);
            MotionMode = MotionState::DECELERATE;
            motionstate_debug = "Before the judge line: Distance is" + to_string(Dis);
            targetVel1 = ACC();
          }
        }
      }
      else if (new_behavior_mode || !find_stopline){
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

      if (!passcrosswalk){
        if (!find_stopline){
          std::cout << "FAIL TO FIND Stopline in RightTurn" << std::endl;
          MotionMode = MotionState::FAIL;
          targetVel1 = vel;
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
          DesiredVel = speedbump_velocity/3.6;

          if (Dis <= judge_margin && eventState == 5 || eventState == 6){
            if (timing_min_End_Time >= 7) {
              passcrosswalk = true;
            }
          }

          if (Dis <= stop_margin && passcrosswalk != true){
            MotionMode = MotionState::STOP;
            targetVel1 = speedbump_velocity/3.6;
            motionstate_debug = "At the stop line: Distance is" + to_string(Dis)
            +" , Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
          }
          else if (passcrosswalk){
            MotionMode = MotionState::GO;
            targetVel1 = speedbump_velocity/3.6;
            motionstate_debug = "After the stop line: Distance is" + to_string(Dis);
          }
          else{
            // Dis = std::min(Dis, 15.0);
            MotionMode = MotionState::DECELERATE;
            targetVel1 = ACC();
            motionstate_debug = "Before the stop line: Distance is" + to_string(Dis)
            +" , Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
          }
          
        }
      }
    }
    if (targetVel1 >= speedbump_velocity/3.6)
    {
      targetVel1 = speedbump_velocity/3.6;
    }
    if (LeadVehicle){
      targetVel2 = CheckLeadVehicle();
      targetVel = std::min(targetVel1, targetVel2);
      if (targetVel2 <= targetVel1){
        MotionMode = MotionState::ACC;
        motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);
      }  
    }
    else{
      targetVel = targetVel1;
    }
  }
  else if (CurrentMode ==  BehaviorState::LeftTurn){
    //1) check the stop line (If there is no stop line, make stop line)  
    //2) Reduce the velocity before reaching the stopline

    // int eventState = -1; //red::3, green::5,6, yellow::7,8
    // int timing_min_End_Time = -1;
    // eventState = junc1Signal.States[0].eventState;
    // timing_min_End_Time = junc1Signal.States[0].timing_min_End_Time;

    checkTrafficSignal(1);
    double vel = intersection_velocity/3.6;
    // double vel = Curvature();
    // ROS_INFO ("desired velocity is %f", vel);

    // if ((7)/3.6 <= vel || isnan(vel)){
    //   vel = (7)/3.6;
    // }
    // else if (vel <= 3/3.6){
    //   vel = 3/3.6;
    // }

    if (eventState == -1 || timing_min_End_Time == -1){
      MotionMode = MotionState::GO;
      targetVel1 = vel;
      motionstate_debug = "No traffic light";
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

      if (!passcrosswalk){
        if (!find_stopline){
          // std::cout << "FAIL TO FIND Stopline in LeftTurn" << std::endl;
          motionstate_debug = "FAIL TO FIND Stopline in LeftTurn" + to_string(Dis);
          MotionMode = MotionState::FAIL;
          targetVel1 = speedbump_velocity/3.6;
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

          if (Dis <= judge_margin && eventState == 5 || eventState == 6){
            if (timing_min_End_Time >= 7) {
              passcrosswalk = true;
            }
          }

          if (Dis <= stop_margin && passcrosswalk != true || stop){
            motionstate_debug = "At the stop line: Distance is" + to_string(Dis)
            +" , Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
            MotionMode = MotionState::STOP;
            stop == true;
            targetVel1 = 0;
          }
          else if (passcrosswalk){
            MotionMode = MotionState::GO;
            motionstate_debug = "After the stop line: Distance is" + to_string(Dis)
            +" , Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
            targetVel1 = speedbump_velocity/3.6;
          }
          else{
            // Dis = std::min(Dis, 15.0);
            MotionMode = MotionState::DECELERATE;
            motionstate_debug = "Before the stop line: Distance is" + to_string(Dis) +" , Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
            targetVel1 = ACC();
          }
        }
      }
      else{
        MotionMode = MotionState::GO;  
        motionstate_debug = "After the stop line: Distance is" + to_string(Dis)+" , Status is" + stateToStringEvent(eventState) + " , Time is" + to_string(timing_min_End_Time);
        targetVel1 = speedbump_velocity/3.6;

      }

    }
    if (targetVel1 >= speedbump_velocity/3.6)
    {
      targetVel1 = speedbump_velocity/3.6;
    }
    if (LeadVehicle){
      targetVel2 = CheckLeadVehicle();
      targetVel = std::min(targetVel1, targetVel2);
      if (targetVel2 <= targetVel1){
        MotionMode = MotionState::ACC;
        motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);
      }  
    }
    else{
      targetVel = targetVel1;
    }
    

  }
  else if(CurrentMode ==  BehaviorState::Init){
    targetVel = 0;
    MotionMode = MotionState::STOP; 
  }
  else if(CurrentMode == BehaviorState::StartArrival || CurrentMode == BehaviorState::GoalArrival ||
    CurrentMode == BehaviorState::FrontCarStop || CurrentMode == BehaviorState::FrontLuggage){
    targetVel = 0;
    MotionMode = MotionState::STOP;       
  }
  else if(CurrentMode == BehaviorState::StopAtStartPos ){
    Dis = sqrt(pow(current_x-start.x,2) + pow(current_y-start.y,2));
    targetVel = 0;
    if (Dis <= mission_margin || mission_stop){
      MotionMode = MotionState::STOP;
      motionstate_debug = "At the start position";
      targetVel1 = 0;
      mission_stop = true;
    }
    else{
      Dis = std::min(Dis, 10.0);
      motionstate_debug = "Before the start position: Distance is" + to_string(Dis);
      MotionMode = MotionState::DECELERATE;
      targetVel1 = ACC();
    }
    // if (LeadVehicle){
    //   targetVel2 = CheckLeadVehicle();
    //   targetVel = std::min(targetVel1, targetVel2);
    //   if (targetVel2 <= targetVel1){
    //     MotionMode = MotionState::ACC;
    //     motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);
    //   }  
    // }
    // else{
    //   targetVel = targetVel1;
    // }
    
  }
  else if(CurrentMode == BehaviorState::StopAtGoalPos ){
    Dis = sqrt(pow(current_x-end.x,2) + pow(current_y-end.y,2));
    targetVel = 0;
    if (Dis <= mission_margin || mission_stop){
      MotionMode = MotionState::STOP;
      motionstate_debug = "At the goal position";
      targetVel1 = 0;
      mission_stop = true;
    }
    else{
      Dis = std::min(Dis, 10.0);
      MotionMode = MotionState::DECELERATE;
      motionstate_debug = "Before the goal position: Distance is" + to_string(Dis);
      targetVel1 = ACC();
    }

    // if (LeadVehicle){
    //   targetVel2 = CheckLeadVehicle();
    //   targetVel = std::min(targetVel1, targetVel2);
    //   if (targetVel2 <= targetVel1){
    //     MotionMode = MotionState::ACC;
    //     motionstate_debug = "Lead vehicle exists: Distance is" + to_string(Dis);
    //   }  
    // }
    // else{
    //   targetVel = targetVel1;
    // }
  }
  else if (CurrentMode ==  BehaviorState::LaneChange){
    targetVel = speedbump_velocity/3.6;
    MotionMode = MotionState::GO;   
  }
  else if (CurrentMode== BehaviorState::ObstacleLaneChange){
    targetVel = intersection_velocity/3.6;
    MotionMode = MotionState::GO;  
  }
  else{
    targetVel = MaxVel;
    MotionMode = MotionState::GO; 
  }
  viz_motionstate();
  // std::cout << "Distance" << Dis << std::endl;
}
void VelocityPlanner::checkTrafficSignal(const bool& leftTurn){

  // ROS_INFO("signal_id:  %d, leftTurn is: %d", signal_id, leftTurn);

    // if(!getSPAT1 || !getSPAT2 || !getSPAT3){
    //     ROS_INFO("Can not receive SPAT data");
    //     break;
    // }

  if(signal_id == 1 && leftTurn){
      eventState = junc1Signal.States[1].eventState;
      timing_min_End_Time = junc1Signal.States[1].timing_min_End_Time;
      // ROS_INFO("eventState:  %d, timing_min_End_Time is: %d", eventState, timing_min_End_Time);
  }
  else if(signal_id == 1){
      eventState = junc1Signal.States[0].eventState;
      timing_min_End_Time = junc1Signal.States[0].timing_min_End_Time;
  }
  else if(signal_id == 2 && leftTurn){
      eventState = junc1Signal.States[4].eventState;
      timing_min_End_Time = junc1Signal.States[4].timing_min_End_Time;
  }
  else if(signal_id == 2){
      eventState = junc1Signal.States[3].eventState;
      timing_min_End_Time = junc1Signal.States[3].timing_min_End_Time;
  }
  else if(signal_id == 3 && leftTurn){
      eventState = junc1Signal.States[7].eventState;
      timing_min_End_Time = junc1Signal.States[7].timing_min_End_Time;
  }
  else if(signal_id == 3){
      eventState = junc1Signal.States[6].eventState;
      timing_min_End_Time = junc1Signal.States[6].timing_min_End_Time;
  }
  else if(signal_id == 4 && leftTurn){
      eventState = junc1Signal.States[10].eventState;
      timing_min_End_Time = junc1Signal.States[10].timing_min_End_Time;
  }
  else if(signal_id == 4){
      eventState = junc1Signal.States[9].eventState;
      timing_min_End_Time = junc1Signal.States[9].timing_min_End_Time;
  }
  else if(signal_id == 5 && leftTurn){
      eventState = junc2Signal.States[1].eventState;
      timing_min_End_Time = junc2Signal.States[1].timing_min_End_Time;
  }
  else if(signal_id == 5){
      eventState = junc2Signal.States[0].eventState;
      timing_min_End_Time = junc2Signal.States[0].timing_min_End_Time;
  }
  else if(signal_id == 6 && leftTurn){
      eventState = junc2Signal.States[4].eventState;
      timing_min_End_Time = junc2Signal.States[4].timing_min_End_Time;
  }
  else if(signal_id == 6){
      eventState = junc2Signal.States[3].eventState;
      timing_min_End_Time = junc2Signal.States[3].timing_min_End_Time;
  }
  else if(signal_id == 7 && leftTurn){
      eventState = junc2Signal.States[7].eventState;
      timing_min_End_Time = junc2Signal.States[7].timing_min_End_Time;
  }
  else if(signal_id == 7){
      eventState = junc2Signal.States[6].eventState;
      timing_min_End_Time = junc2Signal.States[6].timing_min_End_Time;
  }
  else if(signal_id == 8 && leftTurn){
      eventState = junc2Signal.States[10].eventState;
      timing_min_End_Time = junc2Signal.States[10].timing_min_End_Time;
  }
  else if(signal_id == 8){
      eventState = junc2Signal.States[9].eventState;
      timing_min_End_Time = junc2Signal.States[9].timing_min_End_Time;
  }
  else if(signal_id == 9 & leftTurn){
      eventState = junc3Signal.States[0].eventState;
      timing_min_End_Time = junc3Signal.States[0].timing_min_End_Time;
  }
  else if(signal_id == 10){
      eventState = junc3Signal.States[1].eventState;
      timing_min_End_Time = junc3Signal.States[1].timing_min_End_Time;
  }
  else if(signal_id == 11 && leftTurn){
      eventState = junc3Signal.States[4].eventState;
      timing_min_End_Time = junc3Signal.States[4].timing_min_End_Time;
  }
  else if(signal_id == 11){
      eventState = junc3Signal.States[3].eventState;
      timing_min_End_Time = junc3Signal.States[3].timing_min_End_Time;
  }
  else
  {
    eventState = -1;
    timing_min_End_Time = -1;
  }

}

double VelocityPlanner::Curvature(){
  double dis = 0;
  double x, y, x_, y_, _x, _y;
  int target_id;

  if (traj.waypoints.size() <= 2){
    return MaxVel;
  }

  for (int i = 0; i < traj.waypoints.size()-2; i++){
    x = traj.waypoints[i].pose.pose.position.x;
    x_= traj.waypoints[i+1].pose.pose.position.x;
    y = traj.waypoints[i].pose.pose.position.y;
    y_= traj.waypoints[i+1].pose.pose.position.y;
    dis = dis + sqrt(pow(x-x_,2)+pow(y-y_,2));
    target_id = i;
    if (dis >= 5){
      break;
    }
  }

  if (target_id <= 1){
    x = traj.waypoints[target_id+2].pose.pose.position.x;
    x_= traj.waypoints[target_id+4].pose.pose.position.x;
    _x = traj.waypoints[target_id].pose.pose.position.x;
    y = traj.waypoints[target_id+2].pose.pose.position.y;
    y_= traj.waypoints[target_id+4].pose.pose.position.y;
    _y= traj.waypoints[target_id].pose.pose.position.y;
  }
  else{
    x = traj.waypoints[target_id].pose.pose.position.x;
    x_= traj.waypoints[target_id+2].pose.pose.position.x;
    _x = traj.waypoints[target_id-2].pose.pose.position.x;
    y = traj.waypoints[target_id].pose.pose.position.y;
    y_= traj.waypoints[target_id+2].pose.pose.position.y;
    _y= traj.waypoints[target_id-2].pose.pose.position.y;
  }

  double a = sqrt( pow(x - _x, 2) + pow(y - _y,2));
  double b = sqrt( pow( _x - x, 2) + pow(_y - y,2));
  double c = sqrt( pow( x_-_x, 2) + pow(y_ - _y,2));
  double q = (pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b);
  ROS_INFO("q is:: %f", q);
  if (q>=1){
    return speedbump_velocity /3.6;
  }

  double R = c/(2*sqrt(1-pow(q,2)));

  if (R <= 0.01 || isnan(R)){
    return speedbump_velocity/3.6;
  }
  double curv = 1/R;
  if (curv <= 0.0001){
    curv = 0.0001;
  }

  double vvel = sqrt(max_lat_acc/curv);

  ROS_INFO("current curv is %f", curv);
  ROS_INFO("current R is %f", R);
  ROS_INFO("current desired vel for curv is %f", vvel);
  

  return vvel;
}

//STOPLINE FUNCTION
int VelocityPlanner::FindStopLine(){
  bool b_stop;
  int stop_idx;
  for (int i = 0; i < traj.waypoints.size(); i++)
  {   
    b_stop = traj.waypoints[i].Stop_line;
    if (b_stop == true){
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

int VelocityPlanner::FindJudgeLine(){
  bool b_junction, pre_b_juction;
  int junction_start_idx = -1;
  int junction_end_idx = -1;
  for (int i = 0; i < traj.waypoints.size(); i++)
  {   
    b_junction = traj.waypoints[i].Junction;
    if (pre_b_juction == false && b_junction == true){
      junction_start_idx = i;
    }
    if (pre_b_juction == true && b_junction == false){
      junction_end_idx = i;
      break;
    }
    pre_b_juction = b_junction;
  }

  if (junction_start_idx == -1){
    for (int i = 0; i < traj.waypoints.size(); i++)
    { 
      b_junction = traj.waypoints[i].Junction;
      if (b_junction == true){
        junction_start_idx = i;
        break;
      }
    }
  }
  if (junction_end_idx == -1){
    if (junction_start_idx != -1){
      junction_end_idx = junction_start_idx;
    }
  }

  int judge_idx;
  if (junction_end_idx == -1 || junction_start_idx == -1){
    judge_idx = -1;
  }
  else{
    judge_idx = (junction_end_idx + junction_start_idx)/2;
  }

  return judge_idx;
}

double VelocityPlanner::CheckLeadVehicle(){
  //Adaptive Cruise Control
  
  double DesiredDis = current_vel*d_time + d_safe;
  if (Mobileye){
    ROS_INFO("********Mobileye************");
    Dis = LeadVehicleDist_m;
    DesiredVel = LeadVehicleVel_m + current_vel; //- current_vel; 
  }
  else{
    Dis = LeadVehicleDist;
    DesiredVel = 0.0; //- current_vel;  
  }
     
  Dis = std::min(Dis, 150.0); 


  ROS_INFO("-------Current Distance is %f", Dis);   
  ROS_INFO("-------Current velocity is %f", current_vel);
  ROS_INFO("--------Desired velocity is %f", DesiredVel);
  
  if (isinf(DesiredVel) || isnan(DesiredVel)){
    DesiredVel = 0.0;
  }
  if (DesiredVel <= 0.5){
    DesiredVel = 0.0;
  }

  // velocity difference is not greater than the speed
  if(DesiredVel > 0){
    DesiredVel = std::min(DesiredVel, 15/3.6);
  }    
  if(DesiredVel < 0){
    DesiredVel = std::max(DesiredVel, 15/3.6);
  }

  if (Dis <= 15 && DesiredVel <= 0.8){
    targetVel = 0.0;
  }
  else{
    targetVel = ACC();
  }
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
    vel_cmd = std::min(std::max(vel_cmd,0.0), MaxVel);    

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if ( elapsed_seconds.count() > dt){
      ROS_ERROR("computing control gain takes too much time");
      std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    if (vel_cmd >= 15/3.6){
      vel_cmd = 15/3.6;
    }
    else if(vel_cmd <= 0.5){
      vel_cmd = 0;
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
  geometry_msgs::PoseStamped debug;
  debug.header.stamp = ros::Time::now();
  debug.pose.position.x = Dis;
  debug.pose.position.y = targetVel;
  debug.pose.position.z = current_vel;
  debug.pose.orientation.x = current_acc;
  vel_debug.publish(debug);

  double v0 = current_vel;
  double a0 = current_acc;
  double time = 1.5;
  double P[3] = {1.0,1.0,5.0};
  double SF0;
  
  ref_speed = v0;
  if (MotionMode == MotionState::GO){
    SF0 = 12;
    if (targetVel <= 2){
      targetVel = 2.0;
    }
    ref_speed = targetVel;
    return;
    // if (abs(current_vel-targetVel) <= 2.5) {
    //   return;
    // } 

  }
  else if (MotionMode == MotionState::STOP){
    ref_speed = 0;
    return;
  }
  else if (MotionMode == MotionState::ACC){
    if (targetVel <= 0.8){
      targetVel = 0;
    }
    ref_speed = targetVel;
    return;
  }
  else{
    if (targetVel <= 2){
      targetVel = 2.0;
    }
    ref_speed = targetVel;
    return;
  }
  
  double xf[3] = {SF0, MaxVel, 0};
  if (previous_step) {
      // std::cout << "**Previous Status is FAIL**" << std::endl;
      xf[1] = xf[1]*0.5;
      if (fail2determine){
        current_vel = current_vel+0.5;
      }
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

        double N = P[2]/0.5;

        std::vector<double> profile{};
        double tt = 0.0;
        for (int i = 0; i < N; i++){
            profile.push_back(v0 + a0*tt + P[0]*pow(tt,2) + P[1]*pow(tt,3));
            tt = tt + 0.5;   
        }
        // std::cout << "Calculate the velocity: c_vel" << current_vel << "r_vel" << ref_speed << std::endl;
        if (visualize)
        {
            viz_vel_prof(profile);
        }
        previous_step = false;
        fail2determine = false; 

        if (ref_speed >= targetVel){
          ref_speed = targetVel;
        }
        else if (ref_speed <= 0 ){
          ref_speed = 0;
        }
        break;
      }
      else if (k >= 50 || fail2solve) {
        ref_speed = targetVel;
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

      if (abs(result) <= 0.0000001) {
        fail2solve = true;
        fail2determine = true; 
        std::cout << "**Determinant is ZERO**" << std::endl;

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
  ref_speed = std::max(ref_speed, 0.0);
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

  // if (LeadVehicle){
  //   if (LeadVehicleInd != 1000)
  //   {
  //     object_x = msg.objects[LeadVehicleInd].pose.position.x;
  //     object_y = msg.objects[LeadVehicleInd].pose.position.y;
  //     rel_vel = msg.objects[LeadVehicleInd].velocity.linear.x;
  //   }
  // }
  // if (Pedestrian){
  // }
  
}

void VelocityPlanner::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg)
{
  // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
  current_vel = abs(state_msg.wheelspeed.wheel_speed);
}

void VelocityPlanner::v2xSPATCallback(const v2x_msgs::SPAT& msg){
    //traffic_signal
    // if(traffic_signal)
    if(msg.id == 1){
        getSPAT1 = true;
        junc1Signal = msg;
    }
    else if(msg.id == 2){
        getSPAT2 = true;
        junc2Signal = msg;
    }
    else if(msg.id == 3){
        getSPAT3 = true;
        junc3Signal = msg;
    }
}


void VelocityPlanner::startendCallback(const hmcl_msgs::MissionWaypoint& msg)
{
  // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
  if (msg.node_wpts.size()<=1){
    return;
  }
  if(!getMission){
    getMission = true;
  }

  int start_id = msg.start.x;
  int end_id  = msg.end.x;
  
  start = msg.node_wpts[start_id];
  end = msg.node_wpts[end_id];
}

void VelocityPlanner::trajCallback(const hmcl_msgs::Lane& msg)
{  
  if(msg.waypoints.size() < 1){
      return;
  }
  getLocalTraj = true;
  MaxVel = 24/3.6;

  double dis = 0;
  double old_dis = 150;
  double current_idx = 0;
  // double total_dis = 0.0;
  if (msg.waypoints.size() == 0)
    return;

  // for (int i = 0; i < msg.waypoints.size(); i++)
  // {   
  //   double _x = msg.waypoints[i].pose.pose.position.x;
  //   double _y = msg.waypoints[i].pose.pose.position.y;


  //   dis = sqrt ( pow(current_x- _x,2) + pow(current_y -_y,2));
  //   if (dis < old_dis)
  //     current_idx = i;
  //   old_dis = dis;
  // }

  // for (int i = current_idx; i < msg.waypoints.size(); i++){
  //   traj.waypoints.push_back(msg.waypoints[i]);
  // }
  // std::copy(msg.waypoints.begin()+current_idx,msg.waypoints.end(),traj.waypoints.begin());

  signal_id = msg.signal_id;
  lane_id = msg.lane_id;
  traj.waypoints = msg.waypoints;
  // std::cout << "Get reference velocity: " << MaxVel << std::endl;
}

void VelocityPlanner::BehaviorStateCallback(const std_msgs::Int16& msg){
  
  if (!getBehavior){
    getBehavior = true;
  }
  eventState = -1;
  timing_min_End_Time = -1;

  CurrentMode =(BehaviorState)msg.data;
  if (CurrentMode == BehaviorState::Init){
    PreviousMode = CurrentMode;
    
  }
  else if (CurrentMode == BehaviorState::Pedestrian && PreviousMode != CurrentMode)
  { 
    //No initialize Paramter
    new_behavior_mode = true;
    PreviousMode = CurrentMode;
    mission_stop = false;
    return;
  }
  else if (CurrentMode == BehaviorState::FrontCarStop && PreviousMode != CurrentMode)
  { 
    //No initialize Paramter
    new_behavior_mode = true;
    PreviousMode = CurrentMode;
    mission_stop = false;
    return;
  }

  else if (PreviousMode == BehaviorState::FrontCarStop && PreviousMode != CurrentMode)
  { 
    //No initialize Paramter
    new_behavior_mode = true;
    PreviousMode = CurrentMode;
    mission_stop = false;
    return;
  }
  else if (PreviousMode == BehaviorState::Pedestrian && PreviousMode != CurrentMode){
    new_behavior_mode = true;
    PreviousMode = CurrentMode;
    mission_stop = false;
  }
  else if (PreviousMode == BehaviorState::StopAtStartPos && PreviousMode != CurrentMode){
    new_behavior_mode = true;
    find_stopline = false;
    find_crosswalk = false;
    find_judgeline = false;
    passcrosswalk = false;
    passjudgeline = false;
    wait_tt = 0;
    stop == false;
  }
  else if (PreviousMode == BehaviorState::StopAtGoalPos && PreviousMode != CurrentMode){
    new_behavior_mode = true;
    find_stopline = false;
    find_crosswalk = false;
    find_judgeline = false;
    passcrosswalk = false;
    passjudgeline = false;
    wait_tt = 0;
    stop == false;
  } 
  else if (PreviousMode != CurrentMode){
    new_behavior_mode = true;
    find_stopline = false;
    find_crosswalk = false;
    find_judgeline = false;
    passcrosswalk = false;
    passjudgeline = false;
    mission_stop = false;
    wait_tt = 0;
    stop == false;
  }
  else{
    new_behavior_mode = false;
  }
  PreviousMode = CurrentMode;
}

void VelocityPlanner::BehaviorStateFactorCallback(const hmcl_msgs::BehaviorFactor& msg){
  LeadVehicleVel = msg.front_vel;
  LeadVehicleDist = msg.front_dist;
  LeadVehicle = msg.transition_condition.frontCar;
  // PassStopLine = msg.stop_line_stop;
}


void VelocityPlanner::viz_motionstate()
{
  visualization_msgs::MarkerArray motionstates;
  
  visualization_msgs::Marker motionstate;

  motionstate.header.frame_id = "map";
  motionstate.header.stamp = ros::Time();
  motionstate.ns = "motionstate";
  motionstate.id = 0;
  motionstate.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  motionstate.action = visualization_msgs::Marker::ADD;

  motionstate.pose.position.x = current_x;
  motionstate.pose.position.y = current_y;
  motionstate.pose.position.z = 5;

  motionstate.scale.z = 7;
  motionstate.text = stateToStringMotion(MotionMode);

  motionstate.color.a = 1.0;
  motionstate.color.r = 0.0;
  motionstate.color.g = 1.0;
  motionstate.color.b = 1.0;
  
  motionstates.markers.push_back(motionstate);

  visualization_msgs::Marker behaviorstate;

  behaviorstate.header.frame_id = "map";
  behaviorstate.header.stamp = ros::Time();
  behaviorstate.ns = "behave";
  behaviorstate.id = 0;
  behaviorstate.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  behaviorstate.action = visualization_msgs::Marker::ADD;

  behaviorstate.pose.position.x = current_x;
  behaviorstate.pose.position.y = current_y;
  behaviorstate.pose.position.z = 11;

  behaviorstate.scale.z = 4;
  behaviorstate.text = stateToStringBehavior(CurrentMode);

  behaviorstate.color.a = 1.0;
  behaviorstate.color.r = 0.0;
  behaviorstate.color.g = 1.0;
  behaviorstate.color.b = 1.0;

  motionstates.markers.push_back(behaviorstate);

  visualization_msgs::Marker motion_debug;

  motion_debug.header.frame_id = "map";
  motion_debug.header.stamp = ros::Time();
  motion_debug.ns = "motion_debug";
  motion_debug.id = 0;
  motion_debug.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  motion_debug.action = visualization_msgs::Marker::ADD;

  motion_debug.pose.position.x = current_x;
  motion_debug.pose.position.y = current_y;
  motion_debug.pose.position.z = 0;

  motion_debug.scale.z = 3;
  motion_debug.text = motionstate_debug;

  motion_debug.color.a = 1.0;
  motion_debug.color.r = 0.0;
  motion_debug.color.g = 1.0;
  motion_debug.color.b = 1.0;

  motionstates.markers.push_back(motion_debug);


  motionstate_vis_pub.publish(motionstates);
}

void VelocityPlanner::viz_vel_prof(std::vector<double> profile)
{
  // visualization_msgs::MarkerArray vel_profs;
  visualization_msgs::Marker vel_prof;

  vel_prof.header.frame_id = "map";
  vel_prof.header.stamp = ros::Time();
  vel_prof.ns = "vel_prof";
  vel_prof.id = 1;
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
  
  // vel_profs.markers.push_back(vel_prof);
  vel_vis_pub.publish(vel_prof);
}

void VelocityPlanner::objectCallback(const autoware_msgs::DetectedObjectArray& msg)
{
  
  if( msg.objects.size() <= 0){    
    return;    
  }

  // ROS_INFO("Mobileye Detected!!!!!!");
  object_x = msg.objects[0].pose.position.x;
  object_y = msg.objects[0].pose.position.y;
  LeadVehicleDist_m = sqrt(pow((object_x - current_x),2)+pow((object_y - current_y),2));

  LeadVehicleVel_m = msg.objects[0].velocity.linear.x;
  // debug_msg.pose.position.z = LeadVehicleVel_m;

  if ( abs(LeadVehicleVel_m) <= 0.5 )
  {
    LeadVehicleVel_m = 0;
  } 
  Mobileye = true;
  mob_tt = 0;
}

int main (int argc, char** argv)
{

    ros::init(argc, argv, "velocity_planner");

    VelocityPlanner vel;

    ros::spin();
    
}