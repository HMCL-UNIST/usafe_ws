#include "local_planner.h"
#include "PolyfitBoost.hpp"

localplanner::localplanner(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Local Planner Initialize");
    sub_pos = nh_.subscribe("/pose_estimate", 1, &localplanner::poseCallback, this);
    sub_vel = nh_.subscribe("/vehicle_status", 1, &localplanner::wheelCallback, this);
   
    sub_traj = nh_.subscribe("/lane_in_range", 1, &localplanner::trajCallback, this);
    sub_flag = nh_.subscribe("/behavior_state", 1, &localplanner::flagCallback, this);
    sub_obj = nh_.subscribe("/behavior_factor", 1, &localplanner::objCallback, this);

    // sub_global = nh_.subscribe("/global_traj", 1, &localplanner::globalCallback, this);

    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 1);
    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1);
    pub_vizs = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_vizs", 1);
    timer_ = nh_.createTimer(ros::Duration(0.01), &localplanner::connect_handler,this);

    //parameter
    // nh_.param<int>("rollout_number", rollout_number, 10);
    // nh_.param<double>("rollout_delta", rollout_delta, 1);

    nh_.param<double>("minimum_lane_change_length", min_lc_len, 3.0);
    nh_.param<double>("minimum_lane_change_prepare_length", min_lc_pp_len, 1.0);
    nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 0.5);
    nh_.param<double>("lane_changing_duration", lc_duration, 1.5);
    nh_.param<double>("minimum_lane_change_length", lc_add, 3.0);
    nh_.param<double>("minimum_lane_change_velocity", min_lc_vel, 2.0);
    nh_.param<double>("path_length", path_len, 50);
}

localplanner::~localplanner()
{}

void localplanner::poseCallback(const nav_msgs::Odometry& state_msg){
    current_pos.section = state_msg.pose.pose;
    st_flag = true;
}
void localplanner::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg){
    current_pos.speed = abs(state_msg.wheelspeed.wheel_speed);
    vel_flag =true;
}
void localplanner::flagCallback(const std_msgs::Int16ConstPtr& flag_msg){
    //  rostopic pub -r 10 /behavior_state std_msgs/Int16 12
    if ((BehaviorState)flag_msg->data == BehaviorState::LaneChange){
        lc_flag = true;
    }
    else{
        lc_flag = false;        
    }
    //  rostopic pub -r 10 /behavior_state std_msgs/Int16 16
    if ((BehaviorState)flag_msg->data == BehaviorState::ObstacleLaneChange){
        obs_flag = true;
    }
    else{
        obs_flag = false;
    }
}
void localplanner::trajCallback(const hmcl_msgs::LaneArray& lane_msg){  
    range_lane = lane_msg;
    trj_flag = true;
}
void localplanner::objCallback(const hmcl_msgs::BehaviorFactor& obj_msg){
    obj.x = obj_msg.xObstacle;
    obj.y = obj_msg.yObstacle;
    obj.length = 8;
}

void localplanner::connect_handler(const ros::TimerEvent& time){
    // For feasibility
    if ( st_flag = false || vel_flag == false || trj_flag == false){
        return;      
    }
    if(range_lane.lanes.size() == 0){
        ROS_WARN("Error");
        std::cout <<" no waypoints here with size " << range_lane.lanes.size() << std::endl;
        return;
    }
    if (range_lane.lanes[0].lane_id == 1000){
        return;
    }

    Eigen::Quaterniond q;
    q.x() = current_pos.section.orientation.x;
    q.y() = current_pos.section.orientation.y;
    q.z() = current_pos.section.orientation.z;
    q.w() = current_pos.section.orientation.w;
    Eigen::Vector3d t(current_pos.section.position.x, current_pos.section.position.y, current_pos.section.position.z);
    Eigen::Matrix3d tf3x3 =  q.normalized().toRotationMatrix();
    double yaw = atan2( tf3x3(1,0),tf3x3(0,0));    
    int poly_index = 0;

    PreparePhase();
    CutoffTraj();

    if ((lc_flag ==false || range_lane.lanes.size()<2 ) && obs_flag ==false){
        ROS_INFO("One Lane");
        pub_lane = target_lane;
    }
    else if ( lc_flag == true && range_lane.lanes.size()>1  && obs_flag == false){
        ROS_INFO("Lane Change");
        int lane_idx=0;
        for (int i=1; i<range_lane.lanes.size(); i++){
            if (range_lane.lanes[i].lane_id !=1000){
                lane_idx = i;
            }
        }

        int prepareidx = FindIndex(range_lane.lanes[lane_idx],  lc_prepare_dist, current_pos.section);
        if (prepareidx ==0){
            cout << "outer " << endl;
            prepareidx = FindIndex(range_lane.lanes[0],  lc_prepare_dist, current_pos.section);    
        }
        int lcidx = FindIndex(range_lane.lanes[lane_idx],  lc_prepare_dist+lc_dist, current_pos.section);

        geometry_msgs::Pose pt1 = range_lane.lanes[lane_idx].waypoints[prepareidx].pose.pose;
        geometry_msgs::Pose pt2 = range_lane.lanes[lane_idx].waypoints[lcidx].pose.pose;

        std::vector<pair<double,double>> pts;
        geometry_msgs::Pose pt_ = current_pos.section;
        std::vector<double> x;
        std::vector<double> y;

        int nn = int(lc_prepare_dist)*2;
        double pt_x, pt_y;

        for (int i=0; i<nn; i++){
            pt_x = pt_.position.x * (1-i/nn) + pt1.position.x * (i/nn);
            pt_y = pt_.position.y * (1-i/nn) + pt1.position.y * (i/nn);
            x.push_back(pt_x);
            y.push_back(pt_y);
        }

        nn = int(lc_dist)*2;
        for (int i=0; i<nn; i++){
            pt_x = pt1.position.x * (i/nn) + pt2.position.x * (1-i/nn);
            pt_y = pt1.position.y * (i/nn) + pt2.position.y * (1-i/nn);
            x.push_back(pt_x);
            y.push_back(pt_y);
        }
        hmcl_msgs::Lane lane;
        try{
            std::vector<double> coeff = polyfit_boost(x, y, 3);
            std::vector<double> testValuesX(x);
            std::vector<double> testValuesY = polyval(coeff, testValuesX);
            
            for (int i=0; i<testValuesY.size(); i=i+2){
            hmcl_msgs::Waypoint wpt;
            wpt.pose.pose.position.x = testValuesX.at(i);
            wpt.pose.pose.position.y = testValuesY.at(i);
            lane.waypoints.push_back(wpt);
            cout << "poly nomial"<<endl;
            }
        }
        catch(std::exception& e){
            cout << "Error"<<endl;
            for (int i=0; i<x.size(); i++){
            hmcl_msgs::Waypoint wpt;
            wpt.pose.pose.position.x = x.at(i);
            wpt.pose.pose.position.y = y.at(i);
            lane.waypoints.push_back(wpt);
            }
        }
        poly_index = lane.waypoints.size();
        if (lcidx+1<target_lane.waypoints.size()){
            cout << target_lane.waypoints.size()<<endl;
            for (int i = lcidx+1; i<target_lane.waypoints.size(); i++){
            hmcl_msgs::Waypoint wpt;
            wpt = target_lane.waypoints[i];
            lane.waypoints.push_back(wpt);
            }   
        }
        pub_lane = lane;
    }
    else if(obs_flag == true){
        ROS_INFO("Obstacle Lane Change");
        int lane_idx=0;
        for (int i=0; i<range_lane.lanes.size(); i++){
            if (range_lane.lanes[i].lane_id =1000){
                lane_idx = i;
            }
        }

        int prepareidx = FindIndex(range_lane.lanes[lane_idx],  lc_prepare_dist, current_pos.section);
        int lcidx = FindIndex(range_lane.lanes[lane_idx],  min_lc_pp_len+min_lc_len, current_pos.section);

        geometry_msgs::Pose pt1 = range_lane.lanes[lane_idx].waypoints[prepareidx].pose.pose;
        geometry_msgs::Pose pt2 = range_lane.lanes[lane_idx].waypoints[lcidx].pose.pose;

        std::vector<pair<double,double>> pts;
        geometry_msgs::Pose pt_ = current_pos.section;
        std::vector<double> x;
        std::vector<double> y;

        int nn = int(lc_prepare_dist)*2;
        double pt_x, pt_y;
    
        for (int i=0; i<nn; i++){
            pt_x = pt_.position.x * (1-i/nn) + pt2.position.x * (i/nn);
            pt_y = pt_.position.y * (1-i/nn) + pt2.position.y * (i/nn);
            x.push_back(pt_x);
            y.push_back(pt_y);
        }

        nn = int(lc_dist)*2;
        for (int i=0; i<nn; i++){
            pt_x = pt1.position.x * (i/nn) + pt2.position.x * (1-i/nn);
            pt_y = pt1.position.y * (i/nn) + pt2.position.y * (1-i/nn);
            x.push_back(pt_x);
            y.push_back(pt_y);
        }
        hmcl_msgs::Lane lane;
        try{
            std::vector<double> coeff = polyfit_boost(x, y, 3);
            std::vector<double> testValuesX(x);
            std::vector<double> testValuesY = polyval(coeff, testValuesX);
            
            for (int i=0; i<testValuesY.size(); i++){
            hmcl_msgs::Waypoint wpt;
            wpt.pose.pose.position.x = testValuesX.at(i);
            wpt.pose.pose.position.y = testValuesY.at(i);
            lane.waypoints.push_back(wpt);
            }
        }
        catch(std::exception& e){
            cout << "Error"<<endl;
            for (int i=0; i<x.size(); i++){
            hmcl_msgs::Waypoint wpt;
            wpt.pose.pose.position.x = x.at(i);
            wpt.pose.pose.position.y = y.at(i);
            lane.waypoints.push_back(wpt);
            }
        }
        poly_index = lane.waypoints.size();
        if (lcidx+1<range_lane.lanes[lane_idx].waypoints.size()){
            for (int i = lcidx+1; i<range_lane.lanes[lane_idx].waypoints.size(); i++){
            hmcl_msgs::Waypoint wpt;
            wpt = range_lane.lanes[lane_idx].waypoints[i];
            lane.waypoints.push_back(wpt);
            }   
        }
\
        pub_lane = lane;
    }

    // if (poly_index !=0){
    //     ROS_INFO("Poly ");
    //     int st_index = (int)(poly_index/2);
    //     int end_index = poly_index;
    //     if (end_index < pub_lane.waypoints.size() ){
    //         end_index = max(pub_lane.waypoints.size(), pub_lane.waypoints.size()+5);
    //     }

    //     std::vector<double> X = {};
    //     std::vector<double> Y = {};

    //     for (int i = st_index; i < end_index; i++){
    //         X.push_back(pub_lane.waypoints[i].pose.pose.position.x);
    //         Y.push_back(pub_lane.waypoints[i].pose.pose.position.y);    
    //     } 

    //     hmcl_msgs::Lane lane;
    //     for (int i = 0; i < st_index; i++){
    //         hmcl_msgs::Waypoint wpt;
    //         wpt = pub_lane.waypoints[i];
    //         lane.waypoints.push_back(wpt);
    //     }
        
    //     std::vector<double> coeff = polyfit_boost(X, Y, 3);
    //     std::vector<double> polyValuesX(X);
    //     std::vector<double> polyValuesY = polyval(coeff, polyValuesX);
        
    //     for (int i=0; i<polyValuesY.size(); i++){
    //         hmcl_msgs::Waypoint wpt;
    //         wpt.pose.pose.position.x = polyValuesX.at(i);
    //         wpt.pose.pose.position.y = polyValuesY.at(i);
    //         lane.waypoints.push_back(wpt);
    //     }
    //     for (int i = end_index; i< pub_lane.waypoints.size(); i++){
    //         hmcl_msgs::Waypoint wpt;
    //         wpt = pub_lane.waypoints[i];
    //         lane.waypoints.push_back(wpt);
    //     }
        // pub_lane.clear();
        // pub_lane = lane;
    // }


    pub_lane.signal_id = range_lane.lanes[0].signal_id;
    pub_lane.lane_id = range_lane.lanes[0].lane_id;
    pub_traj.publish(pub_lane);
    viz_local(pub_lane);
    sample_local(all_lanes);
}

void localplanner::PreparePhase(){
    double current_vel = max(current_pos.speed,min_lc_vel);
    double deceleration = 0;
    if (current_vel > 5){
        deceleration = -current_vel/5;
    }
    lc_prepare_dist = max(current_vel * lc_prepare_dur , min_lc_pp_len);  
    lc_dist = max(current_vel * lc_duration,min_lc_len);
    return;
}

void localplanner::CutoffTraj(){
    hmcl_msgs::Lane lane;
    geometry_msgs::Pose pos = current_pos.section;

    int startidx = 0;
    int nn =0;
    int n = 0;
    for (int i=0; i< range_lane.lanes.size(); i++){        
        if(range_lane.lanes[i].lane_id != 1000){
            if (i==0){
                n = range_lane.lanes[i].waypoints.size()-1;
                startidx = FindIndex(range_lane.lanes[i], 0, pos);
            }
            if (i!=0){
                nn = lane.waypoints.size();
                pos = lane.waypoints[nn-1].pose.pose;
                n = range_lane.lanes[i].waypoints.size();
                startidx = FindIndex(range_lane.lanes[i], 0, pos);
                startidx +=1;
            }
            for (int j=startidx; j< range_lane.lanes[i].waypoints.size(); j++){
                lane.waypoints.push_back(range_lane.lanes[i].waypoints[j]);
            }
        
        }
    }
    target_lane = lane;
    return;
}

int localplanner::FindClosest(const hmcl_msgs::Lane& lane, geometry_msgs::Pose pose){
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

int localplanner::FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose){
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

void localplanner::viz_local(const hmcl_msgs::Lane& lane){
    visualization_msgs::MarkerArray lane_markers;

    visualization_msgs::Marker lane_marker;
    lane_marker.header.frame_id = "map";
    lane_marker.header.stamp = ros::Time();
    lane_marker.ns = "local_markers";
    lane_marker.id = 6000;
    lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
    lane_marker.action = visualization_msgs::Marker::ADD;

    lane_marker.color.a = 1.0;
    lane_marker.color.r = 0.0;
    lane_marker.color.g = 1.0;
    lane_marker.color.b = 0.0;
   
    lane_marker.scale.x = 0.3;
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

void localplanner::sample_local(const hmcl_msgs::LaneArray& lanearr){
    visualization_msgs::MarkerArray lane_markers;

    for (int i=0; i<lanearr.lanes.size(); i++){
        visualization_msgs::Marker lane_marker;
        lane_marker.header.frame_id = "map";
        lane_marker.header.stamp = ros::Time();
        lane_marker.ns = "local_sample_markers";
        lane_marker.id = 6100+i;
        lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
        lane_marker.action = visualization_msgs::Marker::ADD;

        lane_marker.color.a = 1.0;
        lane_marker.color.r = 1.0;
        lane_marker.color.g = 0.5;
        lane_marker.color.b = 0.0;
    
        lane_marker.scale.x = 0.2;
        lane_marker.scale.y = 0.1;
        lane_marker.scale.z = 0.1;

        for (int j = 0; j < lanearr.lanes[i].waypoints.size(); j++){
            geometry_msgs::Point p;
            p.x = lanearr.lanes[i].waypoints[j].pose.pose.position.x;
            p.y = lanearr.lanes[i].waypoints[j].pose.pose.position.y;
            lane_marker.points.push_back(p);
        }
        lane_markers.markers.push_back(lane_marker);
        }
    pub_vizs.publish(lane_markers);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "localplanner");
    ros::NodeHandle nh;
    localplanner localplanner(nh);

    ros::spin();
    return 0;
}
