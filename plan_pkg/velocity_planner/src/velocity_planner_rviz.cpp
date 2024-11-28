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
int left_num = 0;
int right_num = 0;
VelocityPlanner::VelocityPlanner()
{   
  ros::NodeHandle nh_;
 
  ROS_INFO("Behavior Velocity Planner initialize");

  //Racing Parameter
  nh_.param<double>("first_lane_speed", first_lane_speed, 50);
  nh_.param<double>("second_lane_speed", second_lane_speed, 50);
  nh_.param<double>("third_lane_speed", third_lane_speed, 50);
  nh_.param<double>("first_bank_lane_speed", first_bank_lane_speed, 40);
  nh_.param<double>("second_bank_lane_speed", second_bank_lane_speed, 40);
  nh_.param<double>("third_bank_lane_speed", third_bank_lane_speed, 40);

  // Prameter 
  nh_.param<double>("intersection_velocity", intersection_velocity, 7);
  nh_.param<double>("speedbump_velocity", speedbump_velocity, 10);
  nh_.param<double>("max_lateral_acc", max_lat_acc, 4.0);
  nh_.param<double>("max_longitudinal_acc", max_long_acc, 1.5);
  nh_.param<double>("stopline_margin", stopline_margin, 0);
  nh_.param<double>("crosswalk_margin", crosswalk_margin, 15);
  nh_.param<double>("stop_margin", stop_margin, 10);
  nh_.param<double>("vehicle_length", vehicle_length, 2);
  
  nh_.param<double>("delay_in_sec", delay_in_sec, 1);
  nh_.param<double>("dt", dt, 0.04); 
  nh_.param<double>("lag_tau", lag_tau, 0.6);
  nh_.param<double>("Q_vel", Q_vel, 20); 
  nh_.param<double>("Q_dis", Q_dis, 20); 
  nh_.param<double>("R_weight", r_weight, 2);
  nh_.param<double>("d_time", d_time, 3.0);
  nh_.param<double>("d_safe", d_safe, 50.0);
  delay_step = (int)(delay_in_sec/dt);
  runtime = 20;

  new_behavior_mode = false;
  passcrosswalk = false;
  find_stopline = false;
  find_crosswalk = false;
  getLocalTraj = false;
  visualize = true;
  stop_flag = false;
  

  // In your class constructor or initialization method
  curvature_pub = nh_.advertise<std_msgs::Float64>("/curvature", 2, true);
  // Subscribe
  //pose_sub = nh_.subscribe("/pose_estimate", 1, &VelocityPlanner::poseCallback, this);
  pose_sub = nh_.subscribe("/current_pose", 1, &VelocityPlanner::poseCallback, this);

  wheel_sub = nh_.subscribe("/CAN_VehicleStatus", 1, &VelocityPlanner::wheelCallback, this);
  // acc_sub = nh_.subscribe("/control_effort", 1, &VelocityPlanner::accCallback, this);
  predicted_objects_sub = nh_.subscribe("/tracking_car/object",1, &VelocityPlanner::PredictedObjectsCallback, this);
  velocity_sub = nh_.subscribe("/current_velocity", 1, &VelocityPlanner::velCallback, this);
  odom_sub = nh_.subscribe("/imu/data", 1, &VelocityPlanner::odomCallback, this);
  sub_canAcc_sub = nh_.subscribe("/control_effort", 1, &VelocityPlanner::canAccCallback, this);

  // traffic_sign_sub = nh_.subscribe("", 1, &VelocityPlanner::TrafficSignCallback, this);    
  behavior_state_sub = nh_.subscribe("/behavior_state", 1, &VelocityPlanner::BehaviorStateCallback, this);
  behavior_state_condition_sub = nh_.subscribe("/behavior_factor", 1, &VelocityPlanner::BehaviorStateFactorCallback, this);
  // lanelet_map_sub = nh_.subscribe("", 1, &VelocityPlanner::LaneletCallback, this);
  local_traj_sub =  nh_.subscribe("/local_traj", 1, &VelocityPlanner::trajCallback,this);
  start_end_sub =  nh_.subscribe("/start_end_pose", 1, &VelocityPlanner::startendCallback,this);
  //v2x_spat_sub = nh_.subscribe("/SPAT",1, &VelocityPlanner::v2xSPATCallback, this);
  // Publish
  
  vel_pub = nh_.advertise<std_msgs::Float64>("/setpoint", 2, true);
  vel_debug  = nh_.advertise<geometry_msgs::PoseStamped>("/acc_debug", 2);
  vel_vis_pub = nh_.advertise<visualization_msgs::MarkerArray>( "/ref_vel_prof_viz", 1, true );
  motionstate_vis_pub = nh_.advertise<visualization_msgs::MarkerArray>( "/motionstate_viz", 1 );
  boost::thread callbackhandler(&VelocityPlanner::callbackthread,this); 
  // boost::thread callbackhandler(&VelocityPlanner::callbackthread,this); 
  f = boost::bind(&VelocityPlanner::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}




// void VelocityPlanner::callbackthread()
// {   
//     ros::Rate loop_rate(runtime); // rate  
//     while(ros::ok()){
//         PlanVel();
//         loop_rate.sleep();
//     }
// }

// void VelocityPlanner::PlanVel()
// {
//   // 1. Check the MOTIONSTATE
//   // 2. Depending on the MOTIONSTATE, plan the velocity
//   if (!getLocalTraj){
//     ROS_INFO("NO LOCAL TRAJECTORY");
//     return;
//   }
  

//   // Publish the curvature value
//   // std_msgs::Float64 curv_msg;
//   // curv_msg.data = CalculateCurveDebug();
//   // curvature_pub.publish(curv_msg);


//   double planned_velocity = Curvature();
//   // double ggv_safe_velocity = GGV();
//   // ROS_INFO("Curv velocity: %f", planned_velocity);

//   // planned_velocity = std::min(planned_velocity, ggv_safe_velocity);
  
//   double lead_vehicle_velocity = planned_velocity;
//   if (acc_flag) {
//     // ROS_INFO("ACC MODE ACTIVATE!!!");
//     lead_vehicle_velocity = CheckLeadVehicle();
//     // ROS_INFO("ACCVEL: %f",lead_vehicle_velocity);
//     planned_velocity = std::min(planned_velocity, lead_vehicle_velocity);
//   }else{
//     planned_velocity = Curvature();
//   }
  

//   // planned_velocity=AdjustVelocityForLcFlag(planned_velocity,currentVel);
//   // ROS_INFO("Desired velocity after adjustment: %f",planned_velocity);

//   // planned_velocity =AdjustVelocityForSlip(planned_velocity);
//   // ROS_INFO("Desired velocity after slip adjustment: %f", planned_velocity);
//   // planned_velocity=AdjustVelocityForSlip(planned_velocity);
//   // std::cout<<"The real planned Velocity = "<<planned_velocity << std::endl;
//   std_msgs::Float64 vel_msg;
//   // if(stop_flag){
//   //   vel_msg.data = 0.0;
//   // }
//   // else if(slow_flag){
//   //   vel_msg.data = 5.0;
//   // }
//   // else{
//   //   vel_msg.data = planned_velocity;
//   // }
//   vel_msg.data = planned_velocity;
//   vel_pub.publish(vel_msg);
//   visualizeGGVset();
// }

/**
 * @brief Checks if there is a lead vehicle and performs necessary actions.
 */


void VelocityPlanner::dyn_callback(velocity_planner::testConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request");
  lag_tau = config.lag_tau;
  Q_vel = config.Q_vel;
  Q_dis = config.Q_dis;
  r_weight = config.R_weight;
  d_time = config.d_time;
  d_safe = config.d_safe;
  max_speed = config.max_speed;
  Activate = config.Activate;
  control_mode = static_cast<ControlMode>(config.dynamic_control_mode);
  
  
  if (Activate && control_mode == CONTROL_MODE_ACC) {
    ROS_INFO("Activate ACC");
    CheckLeadVehicle();
  } else if (Activate && (control_mode == CONTROL_MODE_LaneChange || control_mode == CONTROL_MODE_OPTIMAL)) {
    ROS_INFO("Activate Velocity Planner");
    callbackthread(); // Call the same thread for both cases
  } else if (Activate && control_mode == CONTROL_MODE_GGV) {
    ROS_INFO("Activate GGV");
    publishGGVSpeed();
  }
}


void VelocityPlanner::callbackthread()
{   
    ros::Rate loop_rate(runtime); // rate

    while(ros::ok()){
        if (control_mode == CONTROL_MODE_OPTIMAL) {
            publishCurvatureSpeed();
        } else if (control_mode == CONTROL_MODE_LaneChange) {
            publishLocalTrajSpeed();
        }
        loop_rate.sleep();
    }
}
void VelocityPlanner::publishCurvatureSpeed()
{
  // 1. Check the MOTIONSTATE
  // 2. Depending on the MOTIONSTATE, plan the velocity
  if (!getLocalTraj){
    // ROS_INFO("NO LOCAL TRAJECTORY");
    return;
  }

  double speed = Curvature(); // Function to calculate the speed using curvature
  std_msgs::Float64 speed_msg;
  speed_msg.data = speed;
  vel_pub.publish(speed_msg);
  ROS_INFO("curv vel %f", speed_msg);
}



bool VelocityPlanner::calcNearestPose(unsigned int &nearest_index, double &min_dist_error) 
{
    int nearest_index_tmp = -1;
    double min_dist_squared = std::numeric_limits<double>::max();

    for (unsigned int i = 0; i < traj.waypoints.size(); ++i) {
        const double dx = current_x - traj.waypoints[i].pose.pose.position.x;
        const double dy = current_y - traj.waypoints[i].pose.pose.position.y;
        const double dist_squared = dx * dx + dy * dy;

        
        if (dist_squared < min_dist_squared) {
            min_dist_squared = dist_squared;
            nearest_index_tmp = i;
        }
    }
    

   
    nearest_index = nearest_index_tmp;
    min_dist_error = std::sqrt(min_dist_squared);

    
    return true;
}



double VelocityPlanner::Curvature() {
    double dis = 0;
    double x, y, x_, y_, _x, _y, k, R;
    int target_id;
    double velocity = 0;
    double min_speed = 60 / 3.6;
    

    for (int i = 0; i < traj.waypoints.size() - 2; i++) {
        // If curvature is empty or zero, calculate it
        if (traj.waypoints[i].curvature == 0 || std::isnan(traj.waypoints[i].curvature)) { 
            x = traj.waypoints[i].pose.pose.position.x;
            x_ = traj.waypoints[i + 1].pose.pose.position.x;
            y = traj.waypoints[i].pose.pose.position.y;
            y_ = traj.waypoints[i + 1].pose.pose.position.y;
            dis = dis + sqrt(pow(x - x_, 2) + pow(y - y_, 2));
            target_id = i;
            if (dis >= 5) {
                break;
            }

            if (target_id <= 1) {
                x = traj.waypoints[target_id + 2].pose.pose.position.x;
                x_ = traj.waypoints[target_id + 4].pose.pose.position.x;
                _x = traj.waypoints[target_id].pose.pose.position.x;
                y = traj.waypoints[target_id + 2].pose.pose.position.y;
                y_ = traj.waypoints[target_id + 4].pose.pose.position.y;
                _y = traj.waypoints[target_id].pose.pose.position.y;
            } else {
                x = traj.waypoints[target_id].pose.pose.position.x;
                x_ = traj.waypoints[target_id + 2].pose.pose.position.x;
                _x = traj.waypoints[target_id - 2].pose.pose.position.x;
                y = traj.waypoints[target_id].pose.pose.position.y;
                y_ = traj.waypoints[target_id + 2].pose.pose.position.y;
                _y = traj.waypoints[target_id - 2].pose.pose.position.y;
            }

            // Calculate the curvature using the circumcircle formula
            double a = sqrt(pow(x - _x, 2) + pow(y - _y, 2));
            double b = sqrt(pow(_x - x_, 2) + pow(_y - y_, 2));
            double c = sqrt(pow(x_ - x, 2) + pow(y_ - y, 2));
            double s = (a + b + c) / 2.0; // semi-perimeter
            double area = sqrt(s * (s - a) * (s - b) * (s - c)); // area of triangle
            R = (a * b * c) / (4.0 * area); // circumradius

           

            double curv = 1 / R;
            

            traj.waypoints[i].curvature = curv; // Store calculated curvature in the waypoint
        } else {
            k = traj.waypoints[i].curvature;
            R = 1 / k;
        }

        // Handle cases where the curvature radius is very small
        

        // Determine the appropriate velocity based on curvature radius
        
        velocity = std::max(std::min((max_speed*(1- abs(traj.waypoints[i].curvature/0.014)) / 3.6 ) , max_speed/ 3.6), min_speed);        
    }

    return velocity;
}

/**
 * @brief Publishes the speed value from the local_traj topic.
 */
void VelocityPlanner::publishLocalTrajSpeed() {
  // if (traj.waypoints.empty()) {
  //       ROS_WARN("Trajectory waypoints are empty. Publishing 0 velocity.");
  //       std_msgs::Float64 speed_msg;
  //       speed_msg.data = 0.0;
  //       vel_pub.publish(speed_msg);
  //       return;
  //   }
  if (!getLocalTraj){
    // ROS_INFO("NO LOCAL TRAJECTORY");
    return;
  }
  
  double dis = 0;
  double x, y, x_, y_, _x, _y, k, R;
  int target_id;
  double velocity = 0;
  
  // 현재 차량 위치에 가장 가까운 웨이포인트를 찾음
  geometry_msgs::Pose nearest_pose;
  unsigned int nearest_index;
  double min_dist_error;

  bool found_nearest = calcNearestPose(nearest_index, min_dist_error);


  if (!found_nearest) {
        ROS_WARN("No nearest waypoint found. Publishing 0 velocity.");
        std_msgs::Float64 speed_msg;
        speed_msg.data = 0.0;  // 가장 가까운 웨이포인트를 찾지 못한 경우, 0 속도를 퍼블리시
        vel_pub.publish(speed_msg);
        return;
  }


    // Assuming traj is a topic that publishes the trajectory information
    double speed = traj.waypoints[nearest_index].speed.twist.linear.x; // Get the speed from traj topic
    std_msgs::Float64 speed_msg;
    speed_msg.data = speed;
    vel_pub.publish(speed_msg);
  }
  


double VelocityPlanner::publishGGVSpeed(){
  double speed = 0;
  // Calculate the speed using the GGV algorithm
  speed = GGVAlgorithm();
  std_msgs::Float64 speed_msg;
  speed_msg.data = speed;
  vel_pub.publish(speed_msg);
  return speed;
}

double VelocityPlanner::GGVAlgorithm() {
  double speed = 0;
  // Implement the GGV algorithm here
  return speed;
}

void VelocityPlanner::canAccCallback(const std_msgs::Float64& acc_msg){
  can_acc = acc_msg.data;
}

void VelocityPlanner::visualizeGGVset() {
    // ROS_INFO("Visualizing the GGV set");

    // Define the GGV data points
    std::vector<double> axacc = {
        3.958333, 5.758271, 7.445242, 7.748459, 5.640546
    };
    
    std::vector<double> axdec = {
        -9.618708, -9.742766, -10.112455, -10.720322, -11.553943
    };
    
    std::vector<double> ay = {
        11.709732, 11.817735, 12.138720, 12.663613, 13.377290
    };

    // aydec: absolute values of ay but negative
    std::vector<double> aydec;
    for (const auto& val : ay) {
        aydec.push_back(-std::abs(val));
    }
    
    std::vector<double> vxvect = {
        0.000000, 9.322222, 18.644444, 27.966667, 37.288889
    };

    visualization_msgs::MarkerArray ggv_markers;
    int marker_id = 0; // Unique marker ID for each marker

    // Process both acceleration and deceleration
    for (int mode = 0; mode < 4; ++mode) {
        std::vector<double>& ax = (mode < 2) ? ((mode == 0) ? axacc : axdec) : ((mode == 2) ? axacc : axdec);
        std::vector<double>& ay_vec = (mode % 2 == 0) ? ay : aydec;

        for (size_t i = 0; i < vxvect.size() - 1; ++i) {
            double ax1 = ax[i];
            double ay1 = ay_vec[i];
            double v1 = vxvect[i];
            
            double ax2 = ax[i + 1];
            double ay2 = ay_vec[i + 1];
            double v2 = vxvect[i + 1];

            visualization_msgs::Marker ggv_marker;
            ggv_marker.header.frame_id = "map";
            ggv_marker.header.stamp = ros::Time::now();
            ggv_marker.ns = (mode < 2) ? 
                            ((mode == 0) ? "ggv_surface_acceleration" : "ggv_surface_deceleration") :
                            ((mode == 2) ? "ggv_surface_acceleration_aydec" : "ggv_surface_deceleration_aydec");
            ggv_marker.type = visualization_msgs::Marker::TRIANGLE_LIST;
            ggv_marker.action = visualization_msgs::Marker::ADD;

            // Set the bright pink color
            ggv_marker.scale.x = 50.0;
            ggv_marker.scale.y = 50.0;
            ggv_marker.scale.z = 50.0;
            ggv_marker.color.a = 1.0;  // Fully opaque
            ggv_marker.color.r = 1.0;  // Red
            ggv_marker.color.g = 0.2;  // Small amount of Green to make pink
            ggv_marker.color.b = 0.8;  // Blue

            int num_interpolated_points = 10;

            for (int j = 0; j < num_interpolated_points; ++j) {
                double t = static_cast<double>(j) / num_interpolated_points;

                double interpolated_ax = ax1 + t * (ax2 - ax1);
                double interpolated_ay = ay1 + t * (ay2 - ay1);
                double interpolated_v = v1 + t * (v2 - v1);

                ggv_marker.pose.position.x = interpolated_ax;
                ggv_marker.pose.position.y = interpolated_ay;
                ggv_marker.pose.position.z = interpolated_v;
                ggv_marker.pose.orientation.w = 1.0;

                geometry_msgs::Point p1, p2, p3;

                p1.x = interpolated_ax;
                p1.y = interpolated_ay;
                p1.z = interpolated_v;

                p2.x = interpolated_ax + 0.1;
                p2.y = interpolated_ay;
                p2.z = interpolated_v;

                p3.x = interpolated_ax;
                p3.y = interpolated_ay + 0.1;
                p3.z = interpolated_v;

                ggv_marker.points.push_back(p1);
                ggv_marker.points.push_back(p2);
                ggv_marker.points.push_back(p3);

                // ROS_INFO("Interpolated Pose for Marker %d: x=%f, y=%f, z=%f", marker_id, interpolated_ax, interpolated_ay, interpolated_v);
            }

            ggv_marker.id = marker_id++;
            ggv_marker.lifetime = ros::Duration(1.0);
            ggv_markers.markers.push_back(ggv_marker);
        }
    }

    // ROS_INFO("Publishing GGV marker with %lu points", ggv_markers.markers.size());
    vel_vis_pub.publish(ggv_markers);
}
// double VelocityPlanner::GGV() {
//     geometry_msgs::PoseStamped debug;
//     debug.header.stamp = ros::Time::now();
//     debug.header.frame_id = "map";  // Adjust based on your frame ID (e.g., "map", "odom")
//     debug.pose.position.x = current_x;
//     debug.pose.position.y = current_y;
//     debug.pose.position.z = abs_speed;
//     debug.pose.orientation.x = 1;
//     vel_debug.publish(debug);

//     // GGV Lookup Table
//     std::vector<std::map<std::string, double>> ggv_data = {
//       {{"velocity", 0}, {"ax_max", 3.96}, {"ay_max", 11.71}, {"ax_dec", -9.618708}},
//       {{"velocity", 9.32}, {"ax_max", 5.64}, {"ay_max", 13.38}, {"ax_dec", -9.742766}},
//       {{"velocity", 18.64}, {"ax_max", 7.75}, {"ay_max", 15.28}, {"ax_dec", -10.112455}},
//       {{"velocity", 27.97}, {"ax_max", 5.64}, {"ay_max", 17.61}, {"ax_dec", -10.720322}},
//       {{"velocity", 37.29}, {"ax_max", 4.01}, {"ay_max", 18.82}, {"ax_dec", -11.553943}},
//     };

//     double vx = currentvx;
//     double vy = currentvy;
//     double ax = currentax;
//     double ay = currentay;
//     double current_velocity = abs_speed;

//     double max_ax = 0.0;
//     double max_ay = 0.0;
//     double deceleration = 0.0;

//     // Find the interpolated max_ax and max_ay based on current_velocity
//     for (size_t i = 0; i < ggv_data.size() - 1; ++i) {
//         double v1 = ggv_data[i].at("velocity");
//         double v2 = ggv_data[i + 1].at("velocity");

//         if (current_velocity >= v1 && current_velocity <= v2) {
//             double ax1 = ggv_data[i].at("ax_max");
//             double ax2 = ggv_data[i + 1].at("ax_max");
//             double ay1 = ggv_data[i].at("ay_max");
//             double ay2 = ggv_data[i + 1].at("ay_max");
//             double dec1 = ggv_data[i].at("ax_dec");
//             double dec2 = ggv_data[i + 1].at("ax_dec");
            
//             // Linear interpolation
//             double t = (current_velocity - v1) / (v2 - v1);
//             max_ax = ax1 + t * (ax2 - ax1);
//             max_ay = ay1 + t * (ay2 - ay1);
//             deceleration = dec1 + t * (dec2 - dec1);

//             break;
//         }
//     }

//     // Check if the current state is within the safe limits
//     bool within_ax_limit = (std::abs(ax) <= max_ax) && (ax >= deceleration);
//     bool within_ay_limit = std::abs(ay) <= max_ay;

//     if (within_ax_limit && within_ay_limit) {
//         // If within limits, return the current velocity (no need to reduce speed)
//         return current_velocity;
//     } else {
//         // If any acceleration exceeds the limit, reduce speed

//         // Calculate safe speed in x and y directions
//         double safe_speed_x = (max_ax > std::abs(ax)) ? std::sqrt(max_ax * max_ax - ax * ax) : 0;
//         double safe_speed_y = (max_ay > std::abs(ay)) ? std::sqrt(max_ay * max_ay - ay * ay) : 0;

//         // Combine the safe speeds
//         double final_safe_speed = std::sqrt(std::pow(safe_speed_x, 2) + std::pow(safe_speed_y, 2));

//         // Ensure a minimum safe speed (e.g., to avoid stopping the vehicle completely)
//         double min_safe_speed = current_vel*0.8;
//         final_safe_speed = std::max(final_safe_speed, min_safe_speed);

//         return final_safe_speed;
//     }
// }



   

double VelocityPlanner::AdjustVelocityForSlip(double current_velocity){
  double dis = 0;
  double x, y, x_, y_, _x, _y;
  int closest_idx = FindClosest(traj.waypoints, current_pos.section);
  // std::cout << "closest_idx"<< closest_idx << std::endl;

  if (traj.waypoints.size() <= 2) {
        return 0.0;
    }
  x_ = traj.waypoints[closest_idx].pose.pose.position.x;
  y_ = traj.waypoints[closest_idx].pose.pose.position.y;

  dis = sqrt(pow(current_x - x_, 2) + pow(current_y - y_, 2));
  
  if (dis >= 2) {
      current_velocity -= current_velocity/5 ;
      // ROS_INFO("Adjusting velocity due to slip: %f", current_velocity);
  }
  
    return current_velocity;
}

int VelocityPlanner::FindClosest(const std::vector<hmcl_msgs::Waypoint>& waypoints,
geometry_msgs::Pose pose){
  int idx=0;
  double dis =100;
  double dis_, x_,_x,_y,y_;
  _x = pose.position.x;
  _y = pose.position.y;

  for (int i=0; i < waypoints.size(); i++){
    x_ = waypoints[i].pose.pose.position.x;
    y_ = waypoints[i].pose.pose.position.y;
    dis_ = sqrt(pow(x_ - _x,2) + pow(y_ - _y,2));
    if ( dis_ < dis){
      dis = dis_;
      idx = i;

    }
  }
  return idx;
}
double VelocityPlanner::AdjustVelocityForLcFlag(double current_desired_velocity, double current_velocity) {
  
  // lc_flag가 true일 때 속도를 감속
  if (lc_flag) {
    // 현재 속도를 5로 나누고 그 값을 뺌
    double deceleration_amount = current_desired_velocity / 5.0;
    current_desired_velocity -= deceleration_amount;
  }
  if (!lc_flag){
    current_desired_velocity = current_desired_velocity;
  }
  // // 현재 속도와 목표 속도 간의 차이를 사용하여 속도 조정
  // double velocity_difference = current_velocity - current_desired_velocity;
  // double adjustment_factor = 0.5; // 조정 비율을 정의 (예: 10% 비율로 조정)

  // if (velocity_difference > 0) {
  //   current_desired_velocity += velocity_difference * adjustment_factor;
  // } else {
  //   current_desired_velocity -= (-velocity_difference) * adjustment_factor;
  // }
  // } else{
  //   current_desired_velocity = current_velocity;
  // }
  return current_desired_velocity;
}


// double VelocityPlanner::CalculateCurveDebug(){
//     double dis = 0;
//     double x, y, x_, y_, _x, _y;
//     int target_id=0;

//     if (traj.waypoints.size() <= 2) {
//         return 0.0;
//     }

//     for (int i = 0; i < traj.waypoints.size() - 2; i++) {
//         x = traj.waypoints[i].pose.pose.position.x;
//         x_ = traj.waypoints[i+1].pose.pose.position.x;
//         y = traj.waypoints[i].pose.pose.position.y;
//         y_ = traj.waypoints[i+1].pose.pose.position.y;
//         dis = dis + sqrt(pow(x - x_, 2) + pow(y - y_, 2));
//         target_id = i;
//         if (dis >= 5) {
//             break;
//         }
//     }

//     if (target_id <= 1  && target_id + 4 < traj.waypoints.size()) {
//         x = traj.waypoints[target_id + 2].pose.pose.position.x;
//         x_ = traj.waypoints[target_id + 4].pose.pose.position.x;
//         _x = traj.waypoints[target_id].pose.pose.position.x;
//         y = traj.waypoints[target_id + 2].pose.pose.position.y;
//         y_ = traj.waypoints[target_id + 4].pose.pose.position.y;
//         _y = traj.waypoints[target_id].pose.pose.position.y;
//     } else if(target_id + 2 < traj.waypoints.size() && target_id - 2 >= 0) {
//         x = traj.waypoints[target_id].pose.pose.position.x;
//         x_ = traj.waypoints[target_id + 2].pose.pose.position.x;
//         _x = traj.waypoints[target_id - 2].pose.pose.position.x;
//         y = traj.waypoints[target_id].pose.pose.position.y;
//         y_ = traj.waypoints[target_id + 2].pose.pose.position.y;
//         _y = traj.waypoints[target_id - 2].pose.pose.position.y;
//     } else {
//         ROS_WARN("Target ID out of bounds: %d", target_id);
//         return 0.0;
//     }

//     double a = sqrt(pow(x - _x, 2) + pow(y - _y, 2));
//     double b = sqrt(pow(_x - x_, 2) + pow(_y - y_, 2));
//     double c = sqrt(pow(x_ - x, 2) + pow(y_ - y, 2));
//     double q = (pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b);
//     // ROS_INFO("a: %f, b: %f, c: %f, q: %f", a, b, c, q);

    

    

    

//     return curv; // Return the curvature value
// }





double VelocityPlanner::CheckLeadVehicle(){
  //Adaptive Cruise Control
  
  DesiredDis = current_vel*d_time + d_safe;
  // std::cout << "Desired Dis" << DesiredDis << std::endl;
  Dis = LeadVehicleDist;
  Dis = std::min(Dis, 150.0); 
  // std::cout << "LeadVehicleVel" << LeadVehicleVel << std::endl;

  DesiredVel = LeadVehicleVel; //- current_vel;    

  // velocity difference is not greater than the speed
  // if(DesiredVel > 0){
  //   DesiredVel = std::min(DesiredVel, planned_velocity);
  // }    
  // if(DesiredVel < 0){
  //   DesiredVel = std::max(DesiredVel, 0.0);
  // }
  targetVel = ACC();
  return targetVel;
}
// ACC FUNCTION
double VelocityPlanner::ACC()
{ 
    auto start = std::chrono::steady_clock::now();

    Xk = Eigen::VectorXd::Zero(3,1);
    Xk(0) = std::max((DesiredDis - Dis), 0.0);
    std::cout << "Desired_dis : " << DesiredDis << std::endl;
    std::cout << "Current_dis : " << Dis << std::endl;
    std::cout << "Desired_vel : " << DesiredVel << std::endl;
    std::cout << "Current_vel : " << current_vel << std::endl;
    Xk(1) = current_vel - DesiredVel;
    Xk(2) = can_acc;
    // std::cout << "error_dist"<<Xk(0) << std::endl;
    // std::cout << "error_vel"<< Xk(1) << std::endl;
    // std::cout << "accel"<<Xk(2) << std::endl;
    computeMatrices();
    // std::cout << "acc_cmd" << acc_cmd <<std::endl;

    double vel_cmd = current_vel + acc_cmd * dt;
    vel_cmd = std::min(std::max(vel_cmd,0.0), static_cast<double> (planned_velocity));    

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if ( elapsed_seconds.count() > dt){
      ROS_ERROR("computing control gain takes too much time");
      // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    return static_cast<float>(vel_cmd);
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
  // ROS_INFO("Q_dis: %f",Q_dis);
  // ROS_INFO("Q_vel: %f",Q_vel);
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




//CALLBACK FUNCTION
void VelocityPlanner::poseCallback(const geometry_msgs::PoseStamped& state_msg)
{
  current_x = state_msg.pose.position.x;
  current_y = state_msg.pose.position.y;
}

void VelocityPlanner::accCallback(const sensor_msgs::Imu& msg)
{ 
  current_acc = msg.linear_acceleration.x;
    // Physically our vehicle shouldnt move above or below threadhold acc +-5m/s^2
  if (current_acc > 0){
      current_acc  = std::min(currentAcc,5.0);
  }
  if (current_acc < 0){
    current_acc  = std::max(current_acc,-5.0);
  }
  // ROS_INFO("Get accelaration", current_acc);
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

void VelocityPlanner::odomCallback(const sensor_msgs::Imu& msg){
  currentax = msg.linear_acceleration.x;
  currentay = msg.linear_acceleration.y;
}
void VelocityPlanner::velCallback(const geometry_msgs::TwistStamped& state_msg){
  
    currentvx = abs(state_msg.twist.linear.x);
    currentvy = abs(state_msg.twist.linear.y);

    // current_vel = state_msg;
    abs_speed = sqrt(pow(state_msg.twist.linear.x, 2) +
                     pow(state_msg.twist.linear.y, 2) +
                     pow(state_msg.twist.linear.z, 2));
    // std::cout << "cur_vel"<<abs_speed << std::endl;
    // vel_flag =true;
  // currentvx = state_msg.twist.linear.x;
  // currentvy = state_msg.twist.linear.y;
  // currentax = state_msg.twist.angular.x;
  // currentay = state_msg.twist.angular.y;
  // std::cout << "Get velocity: " << currentVel << std::endl;

//   ros::Time current_time = ros::Time::now();
//   // Initialize previous_time if it's zero
//   if (previous_time.isZero()) {
//       previous_time = current_time;
//       previous_vel = currentVel;
//       ROS_INFO("Initializing previous_time and previous_vel");
//       return; // Skip calculation on the first call
//   }

//   double ddt = (current_time - previous_time).toSec();
//   double min_dt = 0.01; // Minimum time difference threshold
//   double min_vel_change = 0.01; // Minimum velocity change threshold

//   if (ddt > min_dt) { // Apply time threshold
//       double vel_change = currentVel - previous_vel;
//       if (std::abs(vel_change) > min_vel_change) { // Apply velocity change threshold
//           double new_acc = vel_change / ddt;
//           // ROS_INFO("Current Velocity: %f, Previous Velocity: %f, ddt: %f", currentVel, previous_vel, ddt);
//           // ROS_INFO("NEW_ACC %f", new_acc);
//           if (new_acc == 0) {
//               // ROS_WARN("Calculated acceleration value is 0. Using default value.");
//               new_acc = 1.0;
//           }
//           current_acc = new_acc;
//       } else {
//           // ROS_WARN("Velocity change is too small. vel_change: %f", vel_change);
//       }
//       previous_vel = currentVel; // Update previous_vel only if dt > min_dt
//       previous_time = current_time; // Update previous_time only if dt > min_dt
//   } else {
//       // ROS_WARN("Time difference dt is too small. dt: %f", ddt);
//   }
// }
}

void VelocityPlanner::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg)
{
  
  
  // std::cout << "Get velocity: " << state_msg.wheelspeed.wheel_speed << std::endl;
  current_vel = abs(state_msg.wheelspeed.wheel_speed);
  // std::cout << "wheel speed" << current_vel << std::endl;
  
  // ros::Time current_time = ros::Time::now();
  // // Initialize previous_time if it's zero
  // if (previous_time.isZero()) {
  //       previous_time = current_time;
  //       previous_vel = current_vel;
  //       ROS_INFO("Initializing previous_time and previous_vel");
  //       return; // Skip calculation on the first call
  //   }
  // double dt = (current_time - previous_time).toSec();

  // double min_dt = 0.01; // Minimum time difference threshold
  // double min_vel_change = 0.01; // Minimum velocity change threshold
    
  // if (dt > min_dt) { // Apply time threshold
  //       double vel_change = current_vel - previous_vel;
  //       if (std::abs(vel_change) > min_vel_change) { // Apply velocity change threshold
  //           double new_acc = vel_change / dt;
  //           ROS_INFO("Current Velocity: %f, Previous Velocity: %f, dt: %f", current_vel, previous_vel, dt);
  //           ROS_INFO("NEW_ACC %f", new_acc);
  //           if (new_acc == 0) {
  //               ROS_WARN("Calculated acceleration value is 0. Using default value.");
  //               new_acc = 1.0;
  //           }
  //           current_acc = new_acc;
  //       } else {
  //           ROS_WARN("Velocity change is too small. vel_change: %f", vel_change);
  //       }
  //       previous_vel = current_vel; // Update previous_vel only if dt > min_dt
  //       previous_time = current_time; // Update previous_time only if dt > min_dt
  //   } else {
  //       ROS_WARN("Time difference dt is too small. dt: %f", dt);
  //   } 
}



void VelocityPlanner::startendCallback(const hmcl_msgs::MissionWaypoint& msg)
{
  // std::cout << "Get velocity: " << state_msg.twist.twist.linear.x << std::endl;
  int start_id = msg.start.x;
  int end_id  = msg.end.x;

  start = msg.node_wpts[start_id];
  end = msg.node_wpts[end_id];
}

void VelocityPlanner::trajCallback(const hmcl_msgs::Lane& msg)
{  
    if (msg.waypoints.empty()) {
        ROS_WARN("Received an empty trajectory from /local_traj.");
        getLocalTraj = false;
        return;
    }
    ROS_INFO("Received trajectory with %lu waypoints from /local_traj.", msg.waypoints.size());
    // Update the trajectory
    traj.waypoints = msg.waypoints;
    getLocalTraj = true;

    ROS_INFO("Updated trajectory with %lu waypoints.", msg.waypoints.size());
}

void VelocityPlanner::BehaviorStateCallback(const std_msgs::Int16ConstPtr& flag_msg){
  
  //  rostopic pub -r 10 /behavior_state std_msgs/Int16 12
  if ((BehaviorState)flag_msg->data == BehaviorState::LeftLaneChange){
      right_num = 0;
      lc_flag = true;
      // ROS_INFO("LeftLANECHAGE!");
      left_num = left_num +1;
  }
  else if ((BehaviorState)flag_msg->data == BehaviorState::RightLaneChange){
      left_num = 0;
      lc_flag = true;   
      // ROS_INFO("RLANECHAGE!");    
      right_num = right_num +1;
  }
  else if ((BehaviorState)flag_msg->data == BehaviorState::MissionEndStop || (BehaviorState)flag_msg->data == BehaviorState::MissionEnd){
    stop_flag = true;
  }
  else if((BehaviorState)flag_msg->data == BehaviorState::ACC){
    acc_flag = true;
          // std::cout <<" acc work!!!" << std::endl;   


  }
  // else if ((BehaviorState)flag_msg->data == BehaviorState::SlowDown){
  //   stop_flag = true;
  // }
  else {
      left_num = 0;
      right_num = 0;
      lc_flag = false;
      acc_flag = false;
      // ROS_INFO("STRAIGHT");
      // std::cout <<" acc false!!!" << std::endl;   
      // std::cout <<" work!!!" << std::endl;
      // std::cout << " work!!!" << std::endl;
      // std::cout << " work!!!" << std::endl; 
  }
}

  




void VelocityPlanner::BehaviorStateFactorCallback(const hmcl_msgs::BehaviorFactor& msg){
  lane_id = msg.current_lane_id;
  // ROS_INFO("Received lane_id: %d", lane_id);
  
  
  // std::cout << "front_vel  " << LeadVehicleVel << std::endl;
  float minidx =1000;
  for (int i=0 ; i<msg.dsObj.size(); i++){
    if (msg.dsObj[i]< minidx) {
      minidx = msg.dsObj[i];
    } 
  }
  LeadVehicleVel = minidx;

  LeadVehicleDist = msg.front_dist;
  // std::cout << "front_distance " << LeadVehicleDist << std::endl;

}


// void VelocityPlanner::viz_motionstate()
// {
//   visualization_msgs::MarkerArray motionstates;
  
//   visualization_msgs::Marker motionstate;

//   motionstate.header.frame_id = "map";
//   motionstate.header.stamp = ros::Time();
//   motionstate.ns = "motionstate";
//   motionstate.id = 0;
//   motionstate.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
//   motionstate.action = visualization_msgs::Marker::ADD;

//   motionstate.pose.position.x = current_x;
//   motionstate.pose.position.y = current_y;
//   motionstate.pose.position.z = 5;

//   motionstate.scale.z = 7;
//   motionstate.text = stateToStringMotion(MotionMode);

//   motionstate.color.a = 1.0;
//   motionstate.color.r = 0.0;
//   motionstate.color.g = 1.0;
//   motionstate.color.b = 1.0;
  
//   motionstates.markers.push_back(motionstate);

//   visualization_msgs::Marker behaviorstate;

//   behaviorstate.header.frame_id = "map";
//   behaviorstate.header.stamp = ros::Time();
//   behaviorstate.ns = "behave";
//   behaviorstate.id = 0;
//   behaviorstate.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
//   behaviorstate.action = visualization_msgs::Marker::ADD;

//   behaviorstate.pose.position.x = current_x;
//   behaviorstate.pose.position.y = current_y;
//   behaviorstate.pose.position.z = 11;

//   behaviorstate.scale.z = 4;
//   behaviorstate.text = stateToStringBehavior(CurrentMode);

//   behaviorstate.color.a = 1.0;
//   behaviorstate.color.r = 0.0;
//   behaviorstate.color.g = 1.0;
//   behaviorstate.color.b = 1.0;

//   motionstates.markers.push_back(behaviorstate);

//   visualization_msgs::Marker motion_debug;

//   motion_debug.header.frame_id = "map";
//   motion_debug.header.stamp = ros::Time();
//   motion_debug.ns = "motion_debug";
//   motion_debug.id = 0;
//   motion_debug.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
//   motion_debug.action = visualization_msgs::Marker::ADD;

//   motion_debug.pose.position.x = current_x;
//   motion_debug.pose.position.y = current_y;
//   motion_debug.pose.position.z = 0;

//   motion_debug.scale.z = 3;
//   motion_debug.text = motionstate_debug;

//   motion_debug.color.a = 1.0;
//   motion_debug.color.r = 0.0;
//   motion_debug.color.g = 1.0;
//   motion_debug.color.b = 1.0;

//   motionstates.markers.push_back(motion_debug);


//   motionstate_vis_pub.publish(motionstates);
// }

// void VelocityPlanner::viz_vel_prof(std::vector<double> profile)
// {
//   // visualization_msgs::MarkerArray vel_profs;
//   visualization_msgs::Marker vel_prof;

//   vel_prof.header.frame_id = "map";
//   vel_prof.header.stamp = ros::Time();
//   vel_prof.ns = "vel_prof";
//   vel_prof.id = 1;
//   vel_prof.type = visualization_msgs::Marker::LINE_STRIP;
//   vel_prof.action = visualization_msgs::Marker::ADD;

//   if (profile.size() != 0)
//   {
//     for (int i = 0; i < profile.size(); i++)
//     {
//         geometry_msgs::Point p;
//         if (i < traj.waypoints.size())
//         {
//             p.x = traj.waypoints[i].pose.pose.position.x;
//             p.y = traj.waypoints[i].pose.pose.position.y;
//             p.z = profile[i];

//             vel_prof.points.push_back(p);
//         }  
//     }
//   }

//   vel_prof.scale.x = 1;
//   vel_prof.scale.y = 0;
//   vel_prof.scale.z = 0;

//   vel_prof.color.a = 1.0;
//   vel_prof.color.r = 0.0;
//   vel_prof.color.g = 1.0;
//   vel_prof.color.b = 0.0;
  
//   // vel_profs.markers.push_back(vel_prof);
//   vel_vis_pub.publish(vel_prof);
// }


int main (int argc, char** argv)
{

    ros::init(argc, argv, "velocity_planner");

    VelocityPlanner vel;

    ros::spin();
    
}