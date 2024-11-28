
#include "local_planners.h"
#include "hermite_curve.h"
#include <cmath>
int current_id = 0;
int left_num = 0;
int right_num = 0;
localplanners::localplanners(ros::NodeHandle& nh):
    nh_(nh)
{
    // ROS_INFO("Local Planner Initialize");
    sub_pos = nh_.subscribe("/current_pose", 1, &localplanners::poseCallback, this);
    sub_vel = nh_.subscribe("/current_velocity", 1, &localplanners::velCallback, this);
    // sub_vel = nh_.subscribe("/vehicle_status", 1, &localplanners::wheelCallback, this);
   
    sub_traj = nh_.subscribe("/global_traj", 1, &localplanners::globalCallback, this);
    sub_flag = nh_.subscribe("/behavior_state", 1, &localplanners::behaviorstateCallback, this);
    sub_bfac = nh_.subscribe("/behavior_factor", 1, &localplanners::behaviorfactorCallback, this);
    sub_obj = nh_.subscribe("/tracking_car/objects", 1, &localplanners::objCallback, this);

    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1);
    timer_ = nh_.createTimer(ros::Duration(0.1), &localplanners::local_handler,this);
    local_traj_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 2, true);
    target_pub = nh_.advertise<nav_msgs::Odometry>("/target_lane", 2, true);
    l_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1, true);

    //parameter
    nh_.param<double>("minimum_lane_change_length", min_lc_len, 5.0);
    nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 1.5);
    nh_.param<double>("lane_changing_duration", lc_duration, 3.0);
    nh_.param<double>("minimum_lane_change_velocity", min_lc_vel, 3.0);
    nh_.param<double>("lane_width", lane_width, 1.75);
   
    nh_.param<double>("Q_vel", Q_vel, 1.0); 
    
}

localplanners::~localplanners()
{}

void localplanners::poseCallback(const geometry_msgs::PoseStamped& state_msg){
    pose_init = true;
    pose_x = state_msg.pose.position.x;
    pose_y = state_msg.pose.position.y;
    current_pos.section = state_msg.pose;
    st_flag = true;
}
void localplanners::velCallback(const geometry_msgs::TwistStamped& state_msg){
    current_pos.speed = abs(state_msg.twist.linear.x);
    vel_flag =true;
}
// void localplanners::velCallback(const hmcl_msgs::VehicleStatus& state_msg){
//     current_pos.speed = abs(state_msg.wheelspeed.wheel_speed);
//     vel_flag =true;
// }
void localplanners::behaviorstateCallback(const std_msgs::Int16ConstPtr& flag_msg){
    //  rostopic pub -r 10 /behavior_state std_msgs/Int16 12
    if ((BehaviorState)flag_msg->data == BehaviorState::LeftLaneChange){
        right_num = 0;
        llc_flag = true;
        lc_flag = true;
        if (left_num ==0){
            current_id = current_lane_id;
        }

        if (current_lane_id ==0){
            llc_flag = false;
            lc_flag = false;

        }
        left_num = left_num + 1;
    }    
    else if ((BehaviorState)flag_msg ->data == BehaviorState::RightLaneChange){
        left_num = 0;
        rlc_flag = true;
        lc_flag = true;
        if (right_num ==0){
            current_id = current_lane_id;
        }

        if (current_lane_id==2){
            rlc_flag = false;
            lc_flag = false;

        }

        right_num = right_num + 1;

    }


    // llc_flag = true;
    // lc_flag = true;
    else{
        left_num = 0;
        right_num = 0;
        current_id = current_lane_id;

        lc_flag = false;
        llc_flag = false;
        rlc_flag = false;
    }
    // std::cout << "current_id" << std::endl;

    std::cout << current_id << std::endl;
    std::cout << current_id << std::endl;
    std::cout << current_id << std::endl;
}

void localplanners::behaviorfactorCallback(const hmcl_msgs::BehaviorFactor& factor_msg){
    behavior_factor_init = true;
    prefer_lane_id = factor_msg.prefer_lane_id;
    current_lane_id = factor_msg.current_lane_id;
    // LEGO = factor_msg.lEgo;
    
}

void localplanners::globalCallback(const hmcl_msgs::LaneArray& lane_msg){ 
    global_traj_available = true; 
    global_lane_array = lane_msg;
    
}
void localplanners::objCallback(const autoware_msgs::DetectedObjectArray& obj_msg){
    if(obs_flag == true){
        obj = obj_msg;
    }
}

void localplanners::local_handler(const ros::TimerEvent& time){
    if(!pose_init){
        // ROS_INFO("pose wasn't initialized!!");
        return;
    }
    if(!behavior_factor_init){
        // ROS_INFO("behavior factor wasn't initialized!!");
        return;
    }
    // ROS_INFO("%zu globalsize",global_lane_array.lanes.size());
    if(global_traj_available){
        if(global_lane_array.lanes.size()>0) compute_local_path();
    }
    // ROS_INFO("%d localavail",local_traj_available);
    if(local_traj_available){
        publish_local_path();
        // // ROS_INFO("LOCAL");
    }  

    if ( st_flag = false || vel_flag == false || global_traj_available == false){
        return;      
    }

    if(global_lane_array.lanes.size() == 0){
        ROS_WARN("Error");
        std::cout <<" no waypoints here with size " << global_lane_array.lanes.size() << std::endl;
        return;
    }

    if (global_lane_array.lanes[0].lane_id == 1000){
        return;
    }
    
    if (calculate_dist(global_lane_array.lanes[0], current_pos.section)){
        std::cout << "my lane " <<std::endl;
        lc_ing == false;
    }

    if (obs_flag == true){
        lc_ing =true;
    }

    pub_lane.waypoints.clear();
    pub_lane.signal_id = global_lane_array.lanes[0].signal_id;
    PreparePhase();
    Eigen::Quaterniond q;
    q.x() = current_pos.section.orientation.x;
    q.y() = current_pos.section.orientation.y;
    q.z() = current_pos.section.orientation.z;
    q.w() = current_pos.section.orientation.w;
    Eigen::Vector3d t(current_pos.section.position.x, current_pos.section.position.y, current_pos.section.position.z);
    Eigen::Matrix3d tf3x3 =  q.normalized().toRotationMatrix();
    double yaw_ = atan2( tf3x3(1,0),tf3x3(0,0));

    X.clear();
    Y.clear();
    pt_xy.clear();

    lane_index = 0;
    if (global_lane_array.lanes[0].lane_id == 1000){
        // need to fill out
        cout << "End Point" << endl;
        return;
    }
    else if (lc_flag ==false || global_lane_array.lanes.size()<2 || (global_lane_array.lanes[1].lane_id == 1000 && global_lane_array.lanes.size()==1)){
        // ROS_INFO("Free Drive");
        lane_index = 1;
    }
    else if ( lc_flag == true && global_lane_array.lanes.size()>1 && global_lane_array.lanes[1].lane_id != 1000 ){
        // ROS_INFO("Lane Change");
        lane_index = 1;
    }

    if (lc_ing == true){
        // ROS_INFO("Lane return");
        lane_index =0;
    }

    if (obs_flag == true){
        for (int i=0; i<global_lane_array.lanes.size();i++){
            if (global_lane_array.lanes[i].lane_id == 1000 ){
                lane_index = i;
            }
        }
        // ROS_INFO("Obstacle is Detected :: %d  lane is selected", lane_index);
        lc_flag = true;
    }

    try{
        int startidx_clost = FindClosest(global_lane_array.lanes[current_id], current_pos.section);

        int startidx = FindIndex(global_lane_array.lanes[current_id] , 1.0, current_pos.section);
        int endidx = FindIndex(global_lane_array.lanes[current_id], lc_dist +lc_prepare_dist+lane_width, current_pos.section);

        int startidx_q = FindIndex(global_lane_array.lanes[current_lane_id] , 1.0, current_pos.section);
        
        
        double y1, y2, x1, x2;
        const double max_y_shift = 3.5; 
        double min_scale = 0.5;
        double max_scale = 1.0;
        double speed_scale = max(min_scale, min(max_scale, 10 / current_pos.speed));
        // lane change method: shifting
        Eigen::Matrix4d shift_pt_m;

        if (llc_flag || rlc_flag) {
        // if (true) {
            X.push_back(0);


            
            Eigen::Vector3d ptpt_m1;
            Eigen::Vector3d ptpt_m2;

            ptpt_m1=Eigen::Vector3d(global_lane_array.lanes[current_id].waypoints[startidx].pose.pose.position.x,
            global_lane_array.lanes[current_id].waypoints[startidx].pose.pose.position.y,0);
            
            if(startidx == 949){
                ptpt_m2=Eigen::Vector3d(global_lane_array.lanes[current_id].waypoints[startidx+1].pose.pose.position.x,
                global_lane_array.lanes[current_id].waypoints[startidx+1].pose.pose.position.y,0);
            }
            else{
                ptpt_m2=Eigen::Vector3d(global_lane_array.lanes[current_id].waypoints[startidx+1].pose.pose.position.x,
                global_lane_array.lanes[current_id].waypoints[startidx+1].pose.pose.position.y,0);
            }

            double dx = ptpt_m2[0]-ptpt_m1[0];
            double dy = ptpt_m2[1]-ptpt_m1[1];

            double yaw = std::atan2(dy, dx);;
        
            yaw = yaw * M_PI / 180;
            if (yaw < 0){
                yaw = yaw + 180;
            }


            double q_x = global_lane_array.lanes[current_id].waypoints[startidx_clost].pose.pose.orientation.x;
            double q_y = global_lane_array.lanes[current_id].waypoints[startidx_clost].pose.pose.orientation.y;
            double q_z = global_lane_array.lanes[current_id].waypoints[startidx_clost].pose.pose.orientation.z;
            double q_w = global_lane_array.lanes[current_id].waypoints[startidx_clost].pose.pose.orientation.w;
            
            Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();
            


            double progress_ratio = current_pos.speed / 20;

            double max_shift = 3.5;
            double y_shift = max_shift -progress_ratio * max_shift;
            double pose_diff;
            double pose_diff_1;
            double pose_diff_2;
            Eigen::Vector3d shift_vec;
            Eigen::Vector3d pt;
            Eigen::Vector3d pt_m;
            Eigen::Vector3d pt_start;
            Eigen::Vector2d relativePosition;
            Eigen::Matrix4d pt_mat;
            Eigen::Matrix3d R;
            Eigen::Matrix4d shift_mat;
            
            double pose_head;
            double pose_head_y;
            pt_start = Eigen::Vector3d(global_lane_array.lanes[current_id].waypoints[startidx_clost].pose.pose.position.x,
            global_lane_array.lanes[current_id].waypoints[startidx_clost].pose.pose.position.y, 0);
            R << 1 - 2*q_y*q_y - 2*q_z*q_z, 2*q_x*q_y - 2*q_z*q_w, 2*q_x*q_z + 2*q_y*q_w,
                2*q_x*q_y + 2*q_z*q_w, 1 - 2*q_x*q_x - 2*q_z*q_z, 2*q_y*q_z - 2*q_x*q_w,
                2*q_x*q_z - 2*q_y*q_w, 2*q_y*q_z + 2*q_x*q_w, 1 - 2*q_x*q_x - 2*q_y*q_y;

            // for ( int i=startidx; i<=startidx + 101; i ++){
            for ( int i=startidx; i<startidx ; i ++){

                if (llc_flag){
     
                    pt_m = Eigen::Vector3d(global_lane_array.lanes[current_id].waypoints[i].pose.pose.position.x,
                    global_lane_array.lanes[current_id].waypoints[i].pose.pose.position.y, 0);

                    pt_mat << 1 - 2*q_y*q_y - 2*q_z*q_z, 2*q_x*q_y - 2*q_z*q_w, 2*q_x*q_y + 2*q_y*q_w, pt_m(0),
                                2*q_x*q_y + 2*q_z*q_w, 1 - 2*q_x*q_x - 2*q_z*q_z, 2*q_y*q_z + 2*q_x*q_w, pt_m(1),
                                2*q_x*q_z - 2*q_y*q_w, 2*q_y*q_z - 2*q_x*q_w, 1 - 2*q_x*q_x + 2*q_y*q_y, 0,
                                0, 0, 0, 1;

                    Eigen::Vector2d direction(R(0, 0), R(1, 0));
                    // Eigen::Vector2d direction = R.block<2,1>(0,0); 
                    relativePosition = Eigen::Vector2d((pose_x - pt_start(0)),(pose_y - pt_start(1)));
                    Eigen::Vector2d unitDirection = direction / direction.norm();
                    
                    // 점과 선 사이의 거리 계산 (외적의 크기)
                    pose_diff = std::abs(unitDirection.x() * relativePosition.y() - unitDirection.y() * relativePosition.x());                    
                    pose_head = direction.x() * relativePosition.y() - direction.y() * relativePosition.x();



                    pose_diff = sqrt((pose_x - pt_start(0)) * (pose_x - pt_start(0)) + (pose_y - pt_start(1))*(pose_y - pt_start(1)));
                    pose_head = (1 - 2*q_y*q_y - 2*q_z*q_z)*(pose_x - pt_start(0)) + (2*q_x*q_y - 2*q_z*q_w) * (pose_y - pt_start(1));

                    // // right
                    // // if(pose_head < 0){
                    // if(isnan(LEGO)){
                    //     y_shift = 3.5;
                    // }
                    // else if(LEGO > 0){
                    //     y_shift = 2 - pose_diff;

                    // }

                    // else{
                    //     y_shift = 2 + pose_diff;
                    // }

                    shift_mat << 1, 0, 0, 0,
                                    0, 1, 0, y_shift,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1;

                    // std::cout << "pose_diff : " << pose_diff << std::endl;
                    std::cout << "pose_head : " << pose_head << std::endl;

                } else if (rlc_flag){
                    pt_m = Eigen::Vector3d(global_lane_array.lanes[current_id].waypoints[i].pose.pose.position.x,
                    global_lane_array.lanes[current_id].waypoints[i].pose.pose.position.y, 0);

                    pt_mat << 1 - 2*q_y*q_y - 2*q_z*q_z, 2*q_x*q_y - 2*q_z*q_w, 2*q_x*q_y + 2*q_y*q_w, pt_m(0),
                                2*q_x*q_y + 2*q_z*q_w, 1 - 2*q_x*q_x - 2*q_z*q_z, 2*q_y*q_z + 2*q_x*q_w, pt_m(1),
                                2*q_x*q_z - 2*q_y*q_w, 2*q_y*q_z - 2*q_x*q_w, 1 - 2*q_x*q_x + 2*q_y*q_y, 0,
                                0, 0, 0, 1;



                    Eigen::Vector2d direction(R(0, 0), R(1, 0));
                    // Eigen::Vector2d direction = R.block<2,1>(0,0); 
                    relativePosition = Eigen::Vector2d((pose_x - pt_start(0)),(pose_y - pt_start(1)));
                    Eigen::Vector2d unitDirection = direction / direction.norm();
                    
                    // 점과 선 사이의 거리 계산 (외적의 크기)
                    pose_diff = std::abs(unitDirection.x() * relativePosition.y() - unitDirection.y() * relativePosition.x());                    
                    pose_head = direction.x() * relativePosition.y() - direction.y() * relativePosition.x();



                    pose_diff = sqrt((pose_x - pt_start(0)) * (pose_x - pt_start(0)) + (pose_y - pt_start(1))*(pose_y - pt_start(1)));
                    pose_head = (1 - 2*q_y*q_y - 2*q_z*q_z)*(pose_x - pt_start(0)) + (2*q_x*q_y - 2*q_z*q_w) * (pose_y - pt_start(1));

                    // // right
                    // // if(pose_head < 0){
                    // if(isnan(LEGO)){
                    //     y_shift = 3.5;
                    // }
                    // else if(LEGO > 0){
                    //     y_shift = 2 + pose_diff;

                    // }

                    // else{
                    //     y_shift = 2 - pose_diff;
                    // }

                    shift_mat << 1, 0, 0, 0,
                                    0, 1, 0, -y_shift,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1;
                    std::cout << "pose_head : " << pose_head << std::endl;

                }
                shift_pt_m = pt_mat * shift_mat;                

                hmcl_msgs::Waypoint wpt;


                wpt.pose.pose.position.x = shift_pt_m(0,3);
                wpt.pose.pose.position.y = shift_pt_m(1,3);
                wpt.pose.pose.position.z = 0;


                wpt.pose.pose.orientation.x = global_lane_array.lanes[current_id].waypoints[i].pose.pose.orientation.x;
                wpt.pose.pose.orientation.y = global_lane_array.lanes[current_id].waypoints[i].pose.pose.orientation.y;
                wpt.pose.pose.orientation.z = global_lane_array.lanes[current_id].waypoints[i].pose.pose.orientation.z;
                wpt.pose.pose.orientation.w = global_lane_array.lanes[current_id].waypoints[i].pose.pose.orientation.w;

                pub_lane.waypoints.push_back(wpt);

            }

            // if (true){
            if (llc_flag){
                int target_startidx = FindIndex(global_lane_array.lanes[current_id-1] , 40.0, current_pos.section);
                // int target_startidx = FindIndex(global_lane_array.lanes[current_id-1] , lc_dist +lc_prepare_dist+lane_width, current_pos.section);

                pub_target.header.frame_id = "map";
                pub_target.header.stamp = ros::Time::now();

                pub_target.pose.pose.position.x = global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.position.x;
                pub_target.pose.pose.position.y = global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.position.y;
                pub_target.pose.pose.position.z = 0;
                
                pub_target.pose.pose.orientation.x = global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.orientation.x;
                pub_target.pose.pose.orientation.y = global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.orientation.y;
                pub_target.pose.pose.orientation.z = global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.orientation.z;
                pub_target.pose.pose.orientation.w = global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.orientation.w;

                pub_target.twist.twist.linear.x = current_lane_id;

                std::cout << global_lane_array.lanes[current_id-1].waypoints[target_startidx].pose.pose.position.x << std::endl;

            }

            else if(rlc_flag){
                int target_startidx = FindIndex(global_lane_array.lanes[current_id+1] , 40.0, current_pos.section);
                // int target_startidx = FindIndex(global_lane_array.lanes[current_id+1] , lc_dist +lc_prepare_dist+lane_width, current_pos.section);

                pub_target.header.frame_id = "map";
                pub_target.header.stamp = ros::Time::now();

                pub_target.pose.pose.position.x = global_lane_array.lanes[current_id+1].waypoints[target_startidx].pose.pose.position.x;
                pub_target.pose.pose.position.y = global_lane_array.lanes[current_id+1].waypoints[target_startidx].pose.pose.position.y;
                pub_target.pose.pose.position.z = 0;
                
                pub_target.pose.pose.orientation.x = global_lane_array.lanes[current_id+1].waypoints[target_startidx].pose.pose.orientation.x;
                pub_target.pose.pose.orientation.y = global_lane_array.lanes[current_id+1].waypoints[target_startidx].pose.pose.orientation.y;
                pub_target.pose.pose.orientation.z = global_lane_array.lanes[current_id+1].waypoints[target_startidx].pose.pose.orientation.z;
                pub_target.pose.pose.orientation.w = global_lane_array.lanes[current_id+1].waypoints[target_startidx].pose.pose.orientation.w;

                pub_target.twist.twist.linear.x = current_lane_id;

            }
 

        }
        

    }catch(std::exception& e){
        pub_lane.waypoints.clear();
        int startidx = FindClosest(global_lane_array.lanes[lane_index], current_pos.section);
        for (int i = startidx; i <global_lane_array.lanes[lane_index].waypoints.size();i++){
            pub_lane.waypoints.push_back(global_lane_array.lanes[lane_index].waypoints[i]);          
        }

        int nn = global_lane_array.lanes[lane_index].waypoints.size();
        if ( lane_index ==0 && global_lane_array.lanes.size()>lane_index+1){
            if (global_lane_array.lanes[lane_index+1].lane_id != 1000){
            startidx = FindClosest(global_lane_array.lanes[lane_index+1], global_lane_array.lanes[lane_index].waypoints[nn].pose.pose);
            // ROS_INFO("straight added");
            for (int i = startidx+1; i <global_lane_array.lanes[lane_index+1].waypoints.size();i++){
                pub_lane.waypoints.push_back(global_lane_array.lanes[lane_index+1].waypoints[i]);
                }
            }
        }
    }
    
}


void localplanners::compute_local_path(){
  int local_size = 100;
  local_lane = global_lane_array.lanes[current_lane_id];
  int minidx = calculate_distance_pose2local();
  local_lane.waypoints.clear();
  local_lane.header.frame_id = "map";
  local_lane.header.stamp = ros::Time::now();
  for(int i=minidx+1; i<global_lane_array.lanes[current_lane_id].waypoints.size(); i++){
    if(global_lane_array.lanes[current_lane_id].waypoints.size()<minidx+2){
      // ROS_INFO("LACK OF POINTS FOR LOCAL");
      break;
    }
    hmcl_msgs::Waypoint wp;
    double wp1x = global_lane_array.lanes[current_lane_id].waypoints[i-1].pose.pose.position.x;
    double wp1y = global_lane_array.lanes[current_lane_id].waypoints[i-1].pose.pose.position.y;
    double wp2x = global_lane_array.lanes[current_lane_id].waypoints[i].pose.pose.position.x;
    double wp2y = global_lane_array.lanes[current_lane_id].waypoints[i].pose.pose.position.y;
    double dist = distance(wp1x,wp1y,wp2x,wp2y);
    if(dist > 0.5){
      int n = static_cast<int>(dist/0.5);
      // // ROS_INFO("ADD %d WAYPOINTS", n);
      for(int j = 0; j < n-1; j++){
        wp = global_lane_array.lanes[current_lane_id].waypoints[i-1];
        wp.pose.pose.position.x = wp1x+(wp2x-wp1x)/n*(j+1);
        wp.pose.pose.position.y = wp1y+(wp2y-wp1y)/n*(j+1);
        local_lane.waypoints.push_back(wp);
        if(local_lane.waypoints.size()>local_size) break;        
      }
    }
    wp = global_lane_array.lanes[current_lane_id].waypoints[i];
    local_lane.waypoints.push_back(wp);
    if(local_lane.waypoints.size()>local_size) break;        

  }
  local_traj_available = true;
  // ROS_INFO("local size: %zu",local_lane.waypoints.size());
}
void localplanners::publish_local_path() {
    // ROS_INFO("local pub");
    if (lc_flag) {
        target_pub.publish(pub_target);
        // local_traj_pub.publish(pub_lane);
        // local_traj_marker_array = visualize_local_path(pub_lane);
        // l_traj_viz_pub.publish(local_traj_marker_array);
    } else {
        local_traj_pub.publish(local_lane);
        local_traj_marker_array = visualize_local_path(local_lane);
        l_traj_viz_pub.publish(local_traj_marker_array);
    }
}

//   local_traj_pub.publish(local_lane);
//   local_traj_marker_array = visualize_local_path(local_lane);
//   l_traj_viz_pub.publish(local_traj_marker_array);

// }
void localplanners::setColor(std_msgs::ColorRGBA* cl, double r, double g, double b, double a)
{
  cl->r = r;
  cl->g = g;
  cl->b = b;
  cl->a = a;
}

visualization_msgs::MarkerArray localplanners::visualize_local_path(const hmcl_msgs::Lane local_lane){
  std_msgs::ColorRGBA traj_marker_color;
  setColor(&traj_marker_color, 1.0, 0.0, 0.0, 0.5);    
  std_msgs::ColorRGBA in_bank_color;
  setColor(&in_bank_color, 1.0, 1.0, 0.0, 0.5);
  // Construct Traj_marker               
  visualization_msgs::MarkerArray marker_array;
  marker_array.markers.clear();
  for( int j= 0 ; j <local_lane.waypoints.size() ; j++){
    visualization_msgs::Marker marker_tmp;
    marker_tmp.header.stamp = ros::Time::now();
    marker_tmp.header.frame_id = "map" ;
    marker_tmp.id = 50000+j;
    marker_tmp.ns = "ltraj";
    marker_tmp.type = visualization_msgs::Marker::ARROW;
    marker_tmp.action = visualization_msgs::Marker::ADD;                  
    marker_tmp.pose.position.x = local_lane.waypoints[j].pose.pose.position.x;
    marker_tmp.pose.position.y = local_lane.waypoints[j].pose.pose.position.y;
    marker_tmp.pose.position.z = local_lane.waypoints[j].pose.pose.position.z;
    marker_tmp.pose.orientation.x = local_lane.waypoints[j].pose.pose.orientation.x;
    marker_tmp.pose.orientation.y = local_lane.waypoints[j].pose.pose.orientation.y;
    marker_tmp.pose.orientation.z = local_lane.waypoints[j].pose.pose.orientation.z;
    marker_tmp.pose.orientation.w = local_lane.waypoints[j].pose.pose.orientation.w;
    if(local_lane.waypoints[j].bank){
      marker_tmp.color = in_bank_color;
    }
    else{
    marker_tmp.color = traj_marker_color;
    }
    marker_tmp.lifetime = ros::Duration(0.1);
    marker_tmp.scale.x = 0.7;
    marker_tmp.scale.y = 0.4;
    marker_tmp.scale.z = 0.1;                  
    marker_array.markers.push_back(marker_tmp);
  }
  return marker_array;
}
double localplanners::distance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
}

int localplanners::calculate_distance_pose2local(){
  float min_dist = 1000.0;
  float dist = 1000.0;
  int min_idx = 0;

  for(int i=0; i<local_lane.waypoints.size(); i++){
    dist = distance(local_lane.waypoints[i].pose.pose.position.x,local_lane.waypoints[i].pose.pose.position.y,pose_x,pose_y);
    if(min_dist > dist){
      min_dist = dist;
      min_idx=i;
    }
  }

  return min_idx;
}

double localplanners::calculateVLength(double current_speed) {
    // 현재 속도를 기반으로 Hermite curve의 길이를 조정
    double base_length = 20.0; // 기본 길이
    double speed_factor = current_speed / 10.0; // 속도에 따른 조정 비율
    return base_length + speed_factor; // 최종 길이
}



bool localplanners::valid_lane(const hmcl_msgs::Lane& lane, int lidx, int pidx){
    int nn = lane.waypoints.size();
    if (nn<30){
        return false;
    }
    double _x = lane.waypoints[nn].pose.pose.position.x;
    double _y = lane.waypoints[nn].pose.pose.position.y;
    double x_ = global_lane_array.lanes[lidx].waypoints[pidx].pose.pose.position.x;
    double y_ = global_lane_array.lanes[lidx].waypoints[pidx].pose.pose.position.y;

    double dis = sqrt(pow(x_- _x,2) + pow(y_ -_y,2));
   

    if (dis > 2){
        return false;
    }
    else{
        return true;
    }
}

bool localplanners::calculate_dist(const hmcl_msgs::Lane& lane, geometry_msgs::Pose pose){
    double dis_, x_,_x, _y, y_;
    _x = pose.position.x;
    _y = pose.position.y;

    for (int i = 0; i <lane.waypoints.size(); i++){  
        x_ = lane.waypoints[i].pose.pose.position.x;
        y_ = lane.waypoints[i].pose.pose.position.y;
        dis_ = sqrt(pow(x_- _x,2) + pow(y_ -_y,2));

        if(dis_ < 1.0){
            cout << "dist " <<dis_<<endl;
            return true;
            break;
        }
    }
    return false;    
}


void localplanners::print_XY(std::vector<double> X, std::vector<double> Y){
    // cout<<"X : ";
    for (int i = 0; i < X.size(); i++) {
        std::cout << X[i] << ' ';
    }
    // cout<<"  "<<endl;
    // cout<<"Y : ";
    for (int i = 0; i < Y.size(); i++) {
    std::cout << Y[i] << ' ';
    }
    // cout<<"  "<<endl;
}

void localplanners::PreparePhase(){
    double current_vel = max(current_pos.speed,1.0);
    double deceleration = 0;
    if (current_vel > 5){
        deceleration = -current_vel/5;
    }
    lc_prepare_vel = max(current_vel + deceleration * lc_prepare_dur,1.0);
    lc_prepare_dist = max(current_vel * lc_prepare_dur + 0.5 * deceleration * std::pow(lc_prepare_dur, 2), 1.0);  
    
    lc_vel = max(lc_prepare_vel + deceleration * lc_duration, 1.0);
    lc_dist = max(lc_prepare_vel * lc_duration + 0.5 * deceleration * std::pow(lc_duration, 2), min_lc_len);

    
    return;
}

int localplanners::FindClosest(const hmcl_msgs::Lane& lane, geometry_msgs::Pose pose){
    int idx=0;
    double dis =100;
    double dis_, x_,_x, _y, y_;
    _x = pose.position.x;
    _y = pose.position.y;

    for (int i = 0; i <lane.waypoints.size(); i++){  
        x_ = lane.waypoints[i].pose.pose.position.x;
        y_ = lane.waypoints[i].pose.pose.position.y;
        dis_ = sqrt(pow(x_- _x,2) + pow(y_ -_y,2));
        // cout<< "dist " << dis_ <<endl;
        if ( dis_< dis){
            dis = dis_;
            idx = i;
        }
    }
    return idx;
}

int localplanners::FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose){
    double dis =100;
    double dis_, x_,_x, _y, y_;

    int idx = FindClosest(lane, pose);
    _x = lane.waypoints[idx].pose.pose.position.x;
    _y = lane.waypoints[idx].pose.pose.position.y;

    for (int i =idx; i <lane.waypoints.size(); i++){
        x_ = lane.waypoints[i].pose.pose.position.x;
        y_ = lane.waypoints[i].pose.pose.position.y;
        dis_ = sqrt(pow(x_- _x,2) + pow(y_ -_y,2));
        if ( abs(dis_-dist) < dis){
            dis = abs(dis_-dist);
            idx = i;
            }
    }
    return idx;
}

void localplanners::viz_local(const hmcl_msgs::Lane& lane){
    visualization_msgs::MarkerArray lane_markers;

    visualization_msgs::Marker lane_marker;
    lane_marker.header.frame_id = "map";
    lane_marker.header.stamp = ros::Time();
    lane_marker.ns = "local_markers";
    lane_marker.id = 2500;
    lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
    lane_marker.action = visualization_msgs::Marker::ADD;

    lane_marker.color.a = 1.0;
    lane_marker.color.r = 0.0;
    lane_marker.color.g = 1.0;
    lane_marker.color.b = 0.0;
   
    lane_marker.scale.x = 1;
    lane_marker.scale.y = 0.1;
    lane_marker.scale.z = 0.1;

    for (int i = 0; i < lane.waypoints.size(); i++){
        geometry_msgs::Point p;
        p.x = lane.waypoints[i].pose.pose.position.x;
        p.y = lane.waypoints[i].pose.pose.position.y;
        lane_marker.points.push_back(p);
    }
    lane_markers.markers.push_back(lane_marker);
    pub_viz.publish(lane_markers);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "localplanners");
    ros::NodeHandle nh;
    localplanners localplanners(nh);

    ros::spin();
    return 0;
}
