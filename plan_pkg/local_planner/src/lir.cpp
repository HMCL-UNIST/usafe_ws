#include "lir.h"


lirplanner::lirplanner(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Lane in range Planner Initialize");

    sub_pos = nh_.subscribe("/pose_estimate", 1, &lirplanner::poseCallback, this);
    sub_global = nh_.subscribe("/global_traj", 1, &lirplanner::globalCallback, this);

    pub_lir = nh_.advertise<hmcl_msgs::LaneArray>("/lirs", 1);
    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/lirs_viz", 1);

    timer_ = nh_.createTimer(ros::Duration(0.1), &lirplanner::connect_handler,this);
}

lirplanner::~lirplanner()
{}

void lirplanner::connect_handler(const ros::TimerEvent& time){
  if(global_index.size()>0){
    lane_in_range();
    if(lir_available){
        pub_lir.publish(lir_array);
        viz_lir(global_lane);
    }
    else{
      ROS_INFO("No Lane in Range");
    }
  }
}

void lirplanner::findnearest_lane_and_point_idx(const hmcl_msgs::LaneArray &lanes, geometry_msgs::Pose& point_, int &closest_lane_idx, int &closest_point_idx){  
    //input is usually the center line
  closest_lane_idx = 0;
  closest_point_idx = 0;
  double min_dist_ = std::numeric_limits<double>::max();    
  for(int i=0; i < lanes.lanes.size(); i++){                
      for (int j = 0 ; j < lanes.lanes[i].waypoints.size(); j++){
      double dist_= sqrt(pow((lanes.lanes[i].waypoints[j].pose.pose.position.x-point_.position.x),2) + pow((lanes.lanes[i].waypoints[j].pose.pose.position.y-point_.position.y),2));      
      if(min_dist_ >= dist_){
          closest_lane_idx = i;
          closest_point_idx = j;
          min_dist_ =  dist_;        
        }  
    }
  }
  return;
}

bool lirplanner::calculate_distance_(hmcl_msgs::Waypoint &wp1, hmcl_msgs::Waypoint &wp2, double &dist, double &dist_cum){
  dist_cum = dist_cum + sqrt(pow((wp1.pose.pose.position.x-wp2.pose.pose.position.x),2) + pow((wp1.pose.pose.position.y-wp2.pose.pose.position.y),2));
  // std::cout << dist_cum << std::endl;
  if (dist_cum< dist){
    return true;
  }
  else{
    return false;
  }
}

void lirplanner::lane_in_range(){
    ROS_INFO("lane in range");
    hmcl_msgs::LaneArray tmp_array, tmp_array2;
    tmp_array = global_lane;
    int cur_lane_idx, cur_pt_idx;
    bool add_stop = false;

    findnearest_lane_and_point_idx(tmp_array, cur_pose, cur_lane_idx, cur_pt_idx);

    if (abs(cur_lane_idx - previous_idx) > 2){
      if (previous_idx != -1){
        previous_idx = cur_lane_idx;
        return;
      } 
    } 

    lir_array.lanes.clear();
    tmp_array2.lanes.clear();

    for (int k=0; k<6; k++){
      if (cur_lane_idx+k < tmp_array.lanes.size()){
        tmp_array2.lanes.push_back(tmp_array.lanes[cur_lane_idx+k]);    
        }
    }
    previous_idx = cur_lane_idx;
    findnearest_lane_and_point_idx(tmp_array2, cur_pose, cur_lane_idx, cur_pt_idx);
    current_id = tmp_array2.lanes[cur_lane_idx].lane_id;

    for(int i=0; i<cur_pt_idx; i++){
        tmp_array2.lanes[cur_lane_idx].waypoints.erase(tmp_array2.lanes[cur_lane_idx].waypoints.begin());
    }

    for(int i=0; i<cur_lane_idx; i++){
        tmp_array2.lanes.erase(tmp_array2.lanes.begin());
    }

    ROS_INFO("tmp_array length is: %d", tmp_array.lanes.size());
    ROS_INFO("current lane id: %d", current_id);
    ROS_INFO("tmp_array2 length is: %d", tmp_array2.lanes.size());

    hmcl_msgs::Lane ll;
    double dist_cum = 0;
    int lane_id = current_id;
    bool lc_flag = false;
    for(int i=0; i<tmp_array2.lanes.size(); i++){
    for(int j=0; j<tmp_array2.lanes[i].waypoints.size()-1; j++){
      if(!tmp_array2.lanes[i].lane_change_flag){
        if(lc_flag){
            ll.lane_id = lane_id;
            lir_array.lanes.push_back(ll);
            ll.waypoints.clear();
            lc_flag = false;
        }
        if(calculate_distance_(tmp_array2.lanes[i].waypoints[j+1],tmp_array2.lanes[i].waypoints[j], max_dist, dist_cum)){
          ll.waypoints.push_back(tmp_array2.lanes[i].waypoints[j]);
        }
        else{
          add_stop = true;
          break;
        }
      }
      else{
        if(calculate_distance_(tmp_array2.lanes[i].waypoints[j+1],tmp_array2.lanes[i].waypoints[j], max_dist, dist_cum)){
          ll.waypoints.push_back(tmp_array2.lanes[i].waypoints[j]);
          lc_flag = true;
        }
        else{ 
          lir_array.lanes.push_back(ll);
          ll.waypoints.clear();
          add_stop = true;
          break;
        }
      }
    }
    if(add_stop){
      lir_array.lanes.push_back(ll);
      ll.waypoints.clear();
      break;
    }
  }
  if(ll.waypoints.size()>0){
    lir_array.lanes.push_back(ll);
  }

  if(lir_array.lanes.size()>0){
    lir_available = true;
    viz_lir(lir_array);
  }
  else{
    lir_available = false;
  }
  for (int k=0; k<lir_array.lanes.size(); k++){
    ROS_INFO("lir array id %d, %d , wpts : %d", k, lir_array.lanes[k].lane_id, lir_array.lanes[k].waypoints.size());
  }

}

void lirplanner::poseCallback(const nav_msgs::OdometryConstPtr& msg){
    if(!pose_init){
        pose_init = true;
    }
    cur_pose = msg->pose.pose;
}

void lirplanner::globalCallback(const hmcl_msgs::LaneArray& msg){
    std::cout << " # lanes : " << msg.lanes.size() << std::endl;
    global_lane = msg;
    global_index = {};

    for (int i=0; i< msg.lanes.size(); i++){
        global_index.push_back(global_lane.lanes[i].lane_id);
    }

    std::cout << "global index = { ";
    for (int n : global_index) {
        std::cout << n << ", ";
    }
    std::cout << "}; \n";
}

void lirplanner::viz_lir(hmcl_msgs::LaneArray &lanes){
    if (!lir_available){
        return;
    }

    std_msgs::ColorRGBA lir_marker_color, lir_marker_even, junction_cl, crosswalk_cl, stopline_cl;
    setColor(&lir_marker_color, 0.0, 1.0, 1.0, 0.5);
    setColor(&lir_marker_even, 1.0, 0.0, 1.0, 0.5);
    setColor(&junction_cl, 0.0, 0.0, 1.0, 0.5);
    setColor(&crosswalk_cl, 1.0, 0.0, 0.0, 0.5);
    setColor(&stopline_cl, 1.0, 1.0, 0.0, 0.5);


    lir_marker_array.markers.clear();

    for(int i=0; i<lanes.lanes.size(); i++){
      for(int j=0; j<lanes.lanes[i].waypoints.size(); j++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
        marker_tmp.id = 20000+i*2000+j;
        marker_tmp.ns = "lirs";
        marker_tmp.text = std::to_string(lanes.lanes[i].waypoints[j].lane_id);
        // marker_tmp.type = visualization_msgs::Marker::ARROW;
        marker_tmp.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        marker_tmp.action = visualization_msgs::Marker::ADD;                  
        marker_tmp.pose.position.x = lanes.lanes[i].waypoints[j].pose.pose.position.x;
        marker_tmp.pose.position.y = lanes.lanes[i].waypoints[j].pose.pose.position.y;
        marker_tmp.pose.position.z = lanes.lanes[i].waypoints[j].pose.pose.position.z;
        marker_tmp.pose.orientation.x = lanes.lanes[i].waypoints[j].pose.pose.orientation.x;
        marker_tmp.pose.orientation.y = lanes.lanes[i].waypoints[j].pose.pose.orientation.y;
        marker_tmp.pose.orientation.z = lanes.lanes[i].waypoints[j].pose.pose.orientation.z;
        marker_tmp.pose.orientation.w = lanes.lanes[i].waypoints[j].pose.pose.orientation.w;
        if(lanes.lanes[i].waypoints[j].Crosswalk){
          marker_tmp.color = crosswalk_cl;
        }
        else if(lanes.lanes[i].waypoints[j].Junction){
          marker_tmp.color = junction_cl;
        }
        else if(lanes.lanes[i].waypoints[j].Stop_line){
          marker_tmp.color = stopline_cl;
        }
        else if(i%2 == 0){
          marker_tmp.color = lir_marker_color;  
        }
        else if(i%2 == 1){
          marker_tmp.color = lir_marker_even;
        }
        marker_tmp.lifetime = ros::Duration(0.1);
        // marker_tmp.scale.x = 1.2;
        // marker_tmp.scale.y = 0.6;
        marker_tmp.scale.z = 0.5;

        marker_tmp.color.a = 1.0;
        marker_tmp.color.r = 1.0;
        marker_tmp.color.g = 1.0;
        marker_tmp.color.b = 0.0;

        lir_marker_array.markers.push_back(marker_tmp);
      }
    }
    pub_viz.publish(lir_marker_array);
    return;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "lirplanner");
    ros::NodeHandle nh;
    lirplanner lirplanner(nh);

    ros::spin();
    return 0;
}