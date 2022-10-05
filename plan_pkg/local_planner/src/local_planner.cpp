#include "local_planner.h"

localplanner::localplanner(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Local Planner Initialize");
    sub_pos = nh_.subscribe("/pose_estimate", 1, &localplanner::poseCallback, this);
    sub_vel = nh_.subscribe("/vehicle_status", 1, &localplanner::wheelCallback, this);

    sub_traj = nh_.subscribe("/lane_in_range", 1, &localplanner::trajCallback, this);
    sub_global = nh_.subscribe("/global_traj", 1, &localplanner::globalCallback, this);
    sub_flag = nh_.subscribe("/behavior_status", 1, &localplanner::flagCallback, this);

    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 1);
    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1);
    
    timer_ = nh_.createTimer(ros::Duration(0.1), &localplanner::connect_handler,this);    

    //parameter
    nh_.param<double>("minimum_lane_change_length", min_lc_len, 5.0);
    nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 0.5);
    nh_.param<double>("lane_changing_duration", lc_duration, 1.5);
    nh_.param<double>("lane_change_deceleration", lc_dec, -2.0);
    nh_.param<double>("minimum_lane_change_velocity", min_lc_vel, 1.0);

    // nh_.param<double>("maximum deceleration", max_decel, 5.0);
    // nh_.param<double>("lane change sampling number", lc_sampling_num, 5);
}

localplanner::~localplanner()
{}

void localplanner::connect_handler(const ros::TimerEvent& time){

    hmcl_msgs::Lane pub_lane;
    if(range_index.size() == 0 || st_flag == false){
        std::cout <<" no waypoints here " << std::endl;
        std::cout <<" range size " << range_index.size()<<std::endl;
        std::cout <<" st_flag " << st_flag <<std::endl;
        // std::cout <<" vel_flag " << vel_flag <<std::endl;
        return;
    }
    else if (lc_flag ==false){
        std::cout <<" one line " << std::endl;        
        // std::cout <<" waypoints number 1 : " <<  range_lane.lanes[0].waypoints.size()<<std::endl;
        // std::cout <<" waypoints number 2 : " <<  range_lane.lanes[1].waypoints.size()<<std::endl;
        
        if (range_lane.lanes[0].waypoints.size() > 5){
            for (int i=0; i<range_lane.lanes[0].waypoints.size(); i++){
            pub_lane.waypoints.push_back(range_lane.lanes[0].waypoints[i]);          
            }
        }
        else{
            for (int j=0; j<range_lane.lanes[1].waypoints.size(); j++){
            pub_lane.waypoints.push_back(range_lane.lanes[1].waypoints[j]);
            }
        }
        // std::cout <<" waypoints number : " <<  pub_lane.waypoints.size()<<std::endl;
    }
    else if (lc_flag ==true){
        std::cout <<" lane change " << std::endl;
        range_lane = cuttraj(range_lane);
        // std::cout <<" waypoints number 1 : " <<  range_lane.lanes[0].waypoints.size()<<std::endl;
        // std::cout <<" waypoints number 2 : " <<  range_lane.lanes[1].waypoints.size()<<std::endl;

        struct Point pts;
        PreparePhase(lc_dec);   // prepare_dist, lc_dist
        int startidx, lcidx_s, lcidx_t, endidx;
        startidx = FindIndex(range_lane.lanes[0], lc_prepare_dist, current_pos.section);
        pts.start.section = range_lane.lanes[0].waypoints[startidx].pose.pose;    
        pts.start.length =lc_prepare_dist;
        pts.start.speed = lc_prepare_vel;
        
        lcidx_t= FindIndex(range_lane.lanes[1], 0, pts.start.section);
        lcidx_s = FindIndex(range_lane.lanes[0], lc_dist, range_lane.lanes[0].waypoints[lcidx_t].pose.pose);
        
        endidx = FindIndex(range_lane.lanes[1], lc_dist, range_lane.lanes[1].waypoints[lcidx_t].pose.pose);
        pts.end.section = range_lane.lanes[1].waypoints[endidx].pose.pose;
        pts.end.length = lc_dist;
        pts.end.speed = lc_vel;

        pts.start.prepare_idx1 = 0;
        pts.start.prepare_idx2 = startidx;
        pts.start.lc_idx1 = startidx;
        pts.start.lc_idx2 = lcidx_s;

        pts.end.prepare_idx1 = endidx;
        pts.end.prepare_idx2 = range_lane.lanes[1].waypoints.size();
        pts.end.lc_idx1 = lcidx_t;
        pts.end.lc_idx2 = endidx;
        cout <<"start idx "<< startidx<< ",icidx_s : " << lcidx_s<< endl;
        cout << ",icidx_t : " << lcidx_t<< ", endidx : " << endidx << ", endidx2 : " << pts.end.prepare_idx2 << endl;

        hmcl_msgs::Lane lanechangeLane = getLaneChangePaths(range_lane, pts);
        pub_lane = lanechangeLane;
    }
    else{
        ROS_INFO("There should be error");
        return;
    }
    cout <<"Visualization"<<endl;
    viz_local(pub_lane);
    pub_traj.publish(pub_lane);
}

void localplanner::poseCallback(const nav_msgs::Odometry& state_msg){
    current_pos.section = state_msg.pose.pose;
    st_flag = true;
}

void localplanner::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg){
    current_pos.speed = abs(state_msg.wheelspeed.wheel_speed);
    vel_flag =true;
}

void localplanner::flagCallback(const std_msgs::Int16ConstPtr& flag_msg){
    std::cout << "flag callback" << std::endl;
    if ((BehaviorState)flag_msg->data == BehaviorState::LaneChange){
        lc_flag = true;
        std::cout << "lane change signal" << std::endl;
    }
    else{
        lc_flag = false;        
    }
}

void localplanner::trajCallback(const hmcl_msgs::LaneArray& lane_msg){   
    range_index = {};
    for (int i =0; i < lane_msg.lanes.size(); i++){
        range_index.push_back(lane_msg.lanes[i].lane_id);
    }

    // print
    std::cout << "lane in range index = { ";
    for (int n : range_index) {
        std::cout << n << ", ";
    }
    std::cout << "}; \n";

    range_lane = lane_msg;
}

void localplanner::PreparePhase(double deceleration){
    double current_vel = current_pos.speed;
    lc_prepare_vel = max(current_vel + deceleration * lc_prepare_dur,0.3);
    lc_prepare_dist = max(current_vel * lc_prepare_dur + 0.5 * deceleration * std::pow(lc_prepare_dur, 2), 0.5);  
    lc_vel = lc_prepare_vel + deceleration * lc_duration;
    lc_dist = max(lc_prepare_vel * lc_duration + 0.5 * deceleration * std::pow(lc_duration, 2), min_lc_len);  
    return;
}

int localplanner::FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose){
    double x_, y_;
    int wpt_idx=0;
    double dis_ = 0;
    double dis = 100;
    double _x = pose.position.x;
    double _y = pose.position.y;

    for (int i = 0; i < lane.waypoints.size(); i++){   
        x_ = lane.waypoints[i+1].pose.pose.position.x;
        y_ = lane.waypoints[i+1].pose.pose.position.y;
        dis_ = sqrt(pow(x_- _x,2) + pow(y_ -_y,2));

        if ( abs(dis_-dist) < dis){
            dis = abs(dis_-dist);
            wpt_idx = i;
        }
    }    
    return wpt_idx;
}

hmcl_msgs::LaneArray localplanner::cuttraj(const hmcl_msgs::LaneArray& msg){
    std::cout<< " Trajectory Cutting "  << std::endl;
    
    double dis = 0.0;
    double old_dis = 10.0;
    double current_idx = 0;
    double lane_idx = 0;
    double _x;
    double _y;
    double current_x = current_pos.section.position.x;
    double current_y = current_pos.section.position.y;
    
    hmcl_msgs::Lane lane;
    for (int t = 0; t < msg.lanes.size(); t++)
    {
        for (int i = 0; i < msg.lanes[t].waypoints.size(); i++){   
            _x = msg.lanes[t].waypoints[i].pose.pose.position.x;
            _y = msg.lanes[t].waypoints[i].pose.pose.position.y;
            dis = sqrt(pow(current_x- _x,2) + pow(current_y -_y,2));
        
            if (dis < old_dis){
                hmcl_msgs::Lane lane;
                current_idx = i;
                old_dis = dis;
                lane_idx = t;
            }
            lane.waypoints.push_back(msg.lanes[t].waypoints[i]);

            if(t >0 && i >20 ){
                break;
            }
        }
    }

    hmcl_msgs::LaneArray lane_arr;
    for (int j = lane_idx; j <msg.lanes.size(); j++){
        if (j ==lane_idx)
        {
            lane_arr.lanes.push_back(lane);
        }
        else{
            lane_arr.lanes.push_back(msg.lanes[j]);    
        }
    }
    return lane_arr;
}

hmcl_msgs::Lane localplanner::getLaneChangePathPrepareSegment(hmcl_msgs::Lane lane_data, Sector section){
    const double s_start = section.prepare_idx1;
    const double s_end = section.prepare_idx2;

    hmcl_msgs::Lane lane;

    for (int i=s_start; i < s_end; i++){
        lane.waypoints.push_back(lane_data.waypoints[i]);
    }
    return lane;
}

hmcl_msgs::Lane localplanner::getLaneChangePathSegment(hmcl_msgs::Lane lane_data, Sector section){
    const double s_start = section.lc_idx1;
    const double s_end = section.lc_idx2;
    hmcl_msgs::Lane lane;

    for (int i=s_start; i < s_end; i++){
        lane.waypoints.push_back(lane_data.waypoints[i]);
    }
    return lane; 
}

float localplanner::getPt(float n1 , float n2 , float perc ){
    float diff = n2 - n1;
    return n1 + ( diff * perc );
}    

hmcl_msgs::Lane localplanner::bezier(hmcl_msgs::Lane lane, geometry_msgs::Pose pos1, geometry_msgs::Pose pos2, geometry_msgs::Pose pos3, geometry_msgs::Pose pos4, double lc_dist, int nn){
    float x1 = pos1.position.x;
    float y1 = pos1.position.y;
    float x2 = pos2.position.x;
    float y2 = pos2.position.y;
    float x3 = pos3.position.x;
    float y3 = pos3.position.y;
    float x4 = pos4.position.x;
    float y4 = pos4.position.y;

    float dist = lc_dist/nn;
    float xa, ya, xb, yb, xc, yc, xm, ym, xn, yn, x, y;

    for(float i = 0 ; i < lc_dist ; i += dist ){

        // The Green Lines
        xa = getPt( x1 , x2 , i );
        ya = getPt( y1 , y2 , i );
        xb = getPt( x2 , x3 , i );
        yb = getPt( y2 , y3 , i );
        xc = getPt( x3 , x4 , i );
        yc = getPt( y3 , y4 , i );

        // The Blue Line
        xm = getPt( xa , xb , i );
        ym = getPt( ya , yb , i );
        xn = getPt( xb , xc , i );
        yn = getPt( yb , yc , i );

        // The Black Dot
        x = getPt( xm , xn , i );
        y = getPt( ym , yn , i );

        hmcl_msgs::Waypoint wpt;
        wpt.pose.pose.position.x = x;
        wpt.pose.pose.position.y = y;
        lane.waypoints.push_back(wpt);
    }
    return lane;
}

hmcl_msgs::Lane localplanner::constructCandidatePath(Point LC_Point, hmcl_msgs::Lane lane_prepare, hmcl_msgs::Lane lane_end){
    geometry_msgs::Pose lc_start_pose;
    if (lane_prepare.waypoints.size() >0){
        lc_start_pose = lane_prepare.waypoints[lane_prepare.waypoints.size()].pose.pose;    
    }
    else{
        lc_start_pose = current_pos.section;
        cout << "current pose : " << current_pos.section.position.x <<endl;
    }
    geometry_msgs::Pose lc_end_pose = lane_end.waypoints[0].pose.pose;
    geometry_msgs::Pose lc_mid_pose1;
    geometry_msgs::Pose lc_mid_pose2;
    cout << "start pose : " << lc_start_pose.position.x << lc_start_pose.position.y <<endl;
    cout << "end pose : " << lc_end_pose.position.x << lc_end_pose.position.y <<endl;
    lc_mid_pose1.position.x = lc_start_pose.position.x * 3/4 + lc_end_pose.position.x * 1/4;
    lc_mid_pose1.position.y = lc_start_pose.position.y * 3/4 + lc_end_pose.position.y * 1/4;
    lc_mid_pose2.position.x = lc_start_pose.position.x * 1/4 + lc_end_pose.position.x * 3/4;
    lc_mid_pose2.position.y= lc_start_pose.position.y * 1/4 + lc_end_pose.position.y * 3/4;

    int nn = max(LC_Point.start.prepare_idx2 -LC_Point.start.prepare_idx1, 10);
    hmcl_msgs::Lane lane = bezier(lane_prepare, lc_start_pose, lc_mid_pose1, lc_mid_pose2, lc_end_pose, LC_Point.end.length, nn);
    return lane;
}

hmcl_msgs::Lane localplanner::getLaneChangePaths(hmcl_msgs::LaneArray lane_msgs, Point LC_Point){
    hmcl_msgs::Lane prepare_lane = getLaneChangePathPrepareSegment(lane_msgs.lanes[0], LC_Point.start);
    hmcl_msgs::Lane lanechanged_lane  = getLaneChangePathPrepareSegment(lane_msgs.lanes[1],LC_Point.end);

    std::cout <<" 1 size  " << prepare_lane.waypoints.size()<< std::endl;
    std::cout <<" 2 size  " << lanechanged_lane.waypoints.size()<< std::endl;

    hmcl_msgs::Lane candidate_path = constructCandidatePath(LC_Point, prepare_lane, lanechanged_lane);
    for (int i=0; i<lanechanged_lane.waypoints.size(); i++){
        candidate_path.waypoints.push_back(lanechanged_lane.waypoints[i]);
    }
    candidate_path.speed_limit = LC_Point.end.speed;
    return candidate_path;
}

void localplanner::globalCallback(const hmcl_msgs::LaneArray& lane_msg){
    // std::cout << " # lanes : " << lane_msg.lanes.size() << std::endl;
    global_lane = lane_msg;
    global_index = {};

    // print
    // std::cout << "global index = { ";
    // for (int n : global_index) {
        // std::cout << n << ", ";
    // }
    // std::cout << "}; \n";

    // std::cout << "lane_change index = { ";
    // for (int n : global_change){
        // std::cout << n << ", ";
    // }
    // std::cout << "}; \n";
}

void localplanner::viz_local(const hmcl_msgs::Lane& lane){
    visualization_msgs::MarkerArray lane_markers;
    visualization_msgs::Marker lane_marker;
    lane_marker.header.frame_id = "map";
    lane_marker.header.stamp = ros::Time();
    lane_marker.ns = "local_traj_marker";
    lane_marker.id = 0;
    lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
    lane_marker.action = visualization_msgs::Marker::ADD;

    for (int i = 0; i < lane.waypoints.size(); i++){
        geometry_msgs::Point p;
        p.x = lane.waypoints[i].pose.pose.position.x;
        p.y = lane.waypoints[i].pose.pose.position.y;
        lane_marker.points.push_back(p);
    }

    lane_marker.scale.x = 1;
    lane_marker.scale.y = 0;
    lane_marker.scale.z = 0;
    
    lane_marker.color.a = 1.0;
    lane_marker.color.r = 1.0;
    lane_marker.color.g = 1.0;
    lane_marker.color.b = 0.0;
    
    lane_markers.markers.push_back(lane_marker);
    pub_viz.publish(lane_markers);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "localplanner");
    ros::NodeHandle nh;
    localplanner localplanner(nh);

    ros::spin();
    return 0;
}