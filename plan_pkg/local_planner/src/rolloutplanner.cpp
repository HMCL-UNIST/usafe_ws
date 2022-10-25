#include "rolloutplanner.h"

rolloutPlanner::rolloutPlanner(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Local Rollout based Planner Initialize");
    
    //subscriber 
    sub_pos = nh_.subscribe("/pose_estimate", 1, &rolloutPlanner::poseCallback, this);
    sub_vel = nh_.subscribe("/vehicle_status", 1, &rolloutPlanner::wheelCallback, this);
    sub_traj = nh_.subscribe("/lane_in_range", 1, &rolloutPlanner::trajCallback, this);
    sub_flag = nh_.subscribe("/behavior_state", 1, &rolloutPlanner::flagCallback, this);
    sub_obs = nh_.subscribe("/detected_objs", 1, &rolloutPlanner::ObsCallback, this);
    
    //publisher 
    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 1);
    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1);
    pub_all = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_all", 1);
    pub_bool = nh_.advertise<std_msgs::Bool>("/local_return", 1);
    timer_ = nh_.createTimer(ros::Duration(0.1), &rolloutPlanner::connect_handler,this);

    // vehicle dynamics parameter
    nh_.param<double>("vehicle_mass_rear", veh_m,1500);
    nh_.param<double>("vehicle_mass_front", veh_mf,900);
    nh_.param<double>("vehicle_mass_rear", veh_mr, 600);
    nh_.param<double>("vehicle_length", veh_l, 2.7);
    nh_.param<double>("vehicle_length_front", veh_lf, veh_l/(1-veh_mf/veh_m));
    nh_.param<double>("vehicle_length_rear", veh_lr, veh_l/(1-veh_mr/veh_m));
    nh_.param<double>("vehicle_vel", vel_param, 5);
    nh_.param<double>("discretize_time", dt, 0.1);
    
    nh_.param<int>("Horizon_prepare", N_, 3);
    nh_.param<int>("Horizon", N, 20);
    nh_.param<int>("Horizon_Plus", M, 20);
    
    nh_.param<int>("number_of_samples", n_samples, 20);
    nh_.param<double>("max_angle_to_handle", ang_obs, M_PI/2);
    nh_.param<double>("max_angle_to_handle", ang_lc, M_PI/6);
    
    nh_.param<double>("minimum_lane_change_length", min_lc_len, 5.0);
    nh_.param<double>("minimum_lane_change_prepare_length", min_prepare_len, 0.5);

    nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 1.5);
    nh_.param<double>("lane_changing_duration", lc_duration, 3.0);
    nh_.param<double>("lane_width", lane_width, 3.0);
    nh_.param<double>("obstacle_length", obs_len, 8.00);
}

rolloutPlanner::~rolloutPlanner()
{}

void rolloutPlanner::poseCallback(const nav_msgs::Odometry& state_msg){
    pos_c.x = state_msg.pose.pose.position.x;
    pos_c.y = state_msg.pose.pose.position.y;
    
    pos_c.q_x = state_msg.pose.pose.orientation.x;
    pos_c.q_y = state_msg.pose.pose.orientation.y;
    pos_c.q_z = state_msg.pose.pose.orientation.z;
    pos_c.q_w = state_msg.pose.pose.orientation.w;

    st_flag = true;
}
void rolloutPlanner::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg){
    pos_c.vel = abs(state_msg.wheelspeed.wheel_speed);
    vel_flag =true;
}
void rolloutPlanner::flagCallback(const std_msgs::Int16ConstPtr& flag_msg){
    if ((BehaviorState)flag_msg->data == BehaviorState::LaneChange)lc_flag = true;
    else lc_flag = false;        

    if ((BehaviorState)flag_msg->data == BehaviorState::ObstacleLaneChange) obs_flag = true;
    else obs_flag = false;
}

void rolloutPlanner::trajCallback(const hmcl_msgs::LaneArray& lane_msg){   
    std::cout << "lane in range # " << lane_msg.lanes.size() <<std::endl;
    range_lane = lane_msg;
}
void rolloutPlanner::ObsCallback(const autoware_msgs::DetectedObjectArray& obs_msg){   
    if (obs_msg.objects.size() ==0) return;
    if (obs.exist == false){
        obs.x = obs_msg.objects[0].pose.position.x;
        obs.y = obs_msg.objects[0].pose.position.y;
        obs.length = obs_len;
        obs.exist = true;
    }
}

void rolloutPlanner::connect_handler(const ros::TimerEvent& time){
    if ( st_flag = false || vel_flag == false) return;
    else if(range_lane.lanes.size() == 0){
        ROS_INFO("Error");
        std::cout <<" no waypoints here with size : " << range_lane.lanes.size() << std::endl;
        return;
    }
    else if(range_lane.lanes[0].lane_id ==1000 && range_lane.lanes.size()==1){
        ROS_INFO("Error");
        std::cout <<" only "<< range_lane.lanes[0].lane_id <<"lane is here with size : "<< range_lane.lanes.size() << std::endl;
        return;
    }

    Eigen::Quaterniond q;
    q.x() = pos_c.q_x;
    q.y() = pos_c.q_y;
    q.z() = pos_c.q_z;
    q.w() = pos_c.q_w;
    Eigen::Vector3d t(pos_c.x, pos_c.y, 0);
    Eigen::Matrix3d tf3x3 = q.normalized().toRotationMatrix();
    pos_c.psi = atan2(tf3x3(1,0),tf3x3(0,0));

    // initialize 
    int nx =3;
    double x[3], x0[3], u;
    for (int k =0; k<nx; k++) x0[k]=0;
    pts_data.clear();
    angle = ang_lc;
    if (obs_flag ==true ){
        angle = ang_obs;
    }

    for (int i=0; i<n_samples+1; i++){
        for (int k =0; k<nx; k++) x[k]=x0[k];        
        pt_sample.clear();
        for (int j=0; j< N_+N+M; j++){
            if (j <N_) u = 0;
            else if (j >= N_ && j < N_+N) u = (angle/n_samples)*(i-n_samples/2);
            else if (j > N_+N) u = 0;

            diffequation_kin(x, u);
            Point pt = fill_out_state(x);
            pt_sample.push_back(pt);
        }
        pts_data.push_back(pt_sample);
    }
    hmcl_msgs::Lane lane;
    lane_all.lanes.clear();
    for (int i=0; i<n_samples+1; i++){
        lane.waypoints.clear();

        if (i< n_samples/3 ||  i> n_samples*2/3 ){
            lane.signal_id = range_lane.lanes[1].signal_id;
            lane.lane_id = range_lane.lanes[1].lane_id;
        }
        else{
            lane.signal_id = range_lane.lanes[0].signal_id;
            lane.lane_id = range_lane.lanes[0].lane_id;
        }


        for (int j=0; j < N_+N+M; j++){
            hmcl_msgs::Waypoint wpt;
            Eigen::Vector3d pt(pts_data.at(i).at(j).x, pts_data.at(i).at(j).y ,0);
            pt = tf3x3*pt + t;
            wpt.pose.pose.position.x = pt[0];
            wpt.pose.pose.position.y = pt[1];
            wpt.pose.pose.position.z = 0;
            lane.waypoints.push_back(wpt);
        }
        lane_all.lanes.push_back(lane);
    }

    int pub_idx = evaluatelane(lane_all);
    cout << "pub_idx" <<pub_idx <<endl;
    if (pub_idx<0){
        int lane_idx = 0;
        if (return_flag == true){
            for (int i=0; i<range_lane.lanes.size(); i++){
                if (range_lane.lanes[i].lane_id == 1000){
                    cout << "lane  id " << range_lane.lanes[i].lane_id <<endl;
                    lane_idx = i;
                    break;
                    }
                }
            } 
        hmcl_msgs::Lane pub_lane = range_lane.lanes[lane_idx];
        pub_lane = Cutofflane(pub_lane);
        pub_lane.signal_id = range_lane.lanes[0].signal_id;
        pub_lane.lane_id = range_lane.lanes[0].lane_id;
        pub_lane.speed_limit = 25;
        viz_local(pub_lane);
        pub_traj.publish(pub_lane);
    } 
    else{
        hmcl_msgs::Lane pub_lane = lane_all.lanes[pub_idx];
        pub_lane.speed_limit = 7.5;
        viz_local(pub_lane);
        pub_traj.publish(pub_lane);
    }
    viz_all(lane_all);
}

void rolloutPlanner::PreparePhase(){
    double vel = max(pos_c.vel,0.5);
    lc_prepare_dist = max(vel* lc_prepare_dur,0.5);
    lc_dist = max(vel * lc_duration , min_lc_len);
    return;
}

double rolloutPlanner::PurePursuit(double *x, int idx){
    double ld = vel_param*1.5;
    double dy =  (lane_width/n_samples)*(idx-n_samples/2) -x[1];
    return atan(2*veh_l *dy/(ld*ld));
}

void rolloutPlanner::diffequation_kin(double *x, double steer){
    double dr = veh_lr/(veh_lf+veh_lr);

    double psi = x[2];
    double vel = vel_param;
    double beta = atan(dr* tan(steer));

    x[0] = x[0] + vel*cos(psi +beta)*dt;
    x[1] = x[1] + vel*sin(psi +beta)*dt;
    x[2] = x[2] + vel*sin(beta)/veh_lr*dt;
}

Point rolloutPlanner::fill_out_state(const double *x){
    Point pt;
    pt.x = x[0];
    pt.y = x[1];
    pt.psi = x[2];
    pt.vel = vel_param;

    return pt;
}

int rolloutPlanner::evaluatelane(const hmcl_msgs::LaneArray& lane_arr){
    int idx = n_samples/2;
    hmcl_msgs::Lane lane_ref;
    std::vector<double> cost;
    
    if (lc_flag == false && obs_flag == false){
        lane_ref = range_lane.lanes[0];
        if (return_flag == true){
            for (int i=0; i<range_lane.lanes.size(); i++){
                if (range_lane.lanes[i].lane_id ==1000) {
                    lane_ref = range_lane.lanes[i];
                    break;
                }
            }   
        
            double dis = sqrt(pow(pos_c.x- obs.x,2) + pow(pos_c.y-obs.y,2));
            if (dis > 15){
                std_msgs::Bool msg;
                msg.data = true;
                pub_bool.publish(msg);
                obs.exist == false;
                return_flag = false;
            }
        }
        return -1;
    }

    if (lc_flag==true){
        if (range_lane.lanes[1].lane_id == 1000) lane_ref = range_lane.lanes[0];
        else  lane_ref = range_lane.lanes[1];
        obs.exist = false;
    }

    if (obs_flag ==true){
        ROS_WARN("OBSTACLE");
        return_flag = true;
        for (int i=0; i<range_lane.lanes.size(); i++){
            if (range_lane.lanes[i].lane_id ==1000) {
                lane_ref = range_lane.lanes[i];
                break;
            }
        }
    }
    
    int lane_idx = 0;
    for (int i=0; i <lane_arr.lanes.size(); i++){
        double lane_cost = calculate_dist_cost(lane_ref, lane_arr.lanes[i]);
        if (return_flag == true ){
            for (int i=0; i<range_lane.lanes.size(); i++){
                if (range_lane.lanes[i].lane_id =1000) {
                    lane_idx = i;
                }}}
        else lane_idx =0;

        cout << i << "th lane cost :: " << lane_cost << ",  handle cost " << sqrt(pow(i-n_samples/2,2)/pow(n_samples/2,2)) <<endl;
        lane_cost += sqrt(pow(i-n_samples/2,2)/pow(n_samples/2,2))*0.1*pos_c.vel;  // combine with velocity??
        if (obs_flag ==true){
            double obs_cost = calculate_min(lane_arr.lanes[i],obs.x,obs.y);
            if (obs_cost <lane_width) lane_cost += 10000000;
        }
        // need to add the cost for arriving the node

        cost.push_back(lane_cost);
    }
    if (obs_flag ==true){        
        double dx = range_lane.lanes[lane_idx].waypoints[10].pose.pose.position.x -pos_c.x;
        double dy = range_lane.lanes[lane_idx].waypoints[10].pose.pose.position.y - pos_c.y;
        double alpha = atan2(dy,dx);
        ROS_INFO("alpha 2 :: %.3f", alpha);
    }

    return min_element(cost.begin(), cost.end()) - cost.begin();  
}

hmcl_msgs::Lane rolloutPlanner::Cutofflane(const hmcl_msgs::Lane& lane){
    int idx = calculate_min_idx(lane, pos_c.x, pos_c.y);
    hmcl_msgs::Lane pub_lane;
    for (int i=idx; i<lane.waypoints.size(); i++){
        pub_lane.waypoints.push_back(lane.waypoints[i]);
    }
    return pub_lane;
}

double rolloutPlanner::calculate_min(const hmcl_msgs::Lane& lane, double x, double y ){

    double min =100;
    for (int i=N_; i< lane.waypoints.size(); i++){
        double x_ = lane.waypoints[i].pose.pose.position.x;
        double y_ = lane.waypoints[i].pose.pose.position.y;
        double dis = sqrt(pow(x_-x,2) + pow(y_ -y,2));
        
        if (min  > dis){
            min = dis;
        }
    }
    return min;
}

double rolloutPlanner::calculate_dist_cost(const hmcl_msgs::Lane& ref, const hmcl_msgs::Lane& lane){
    int idx=0;
    double dis =100;
    double x_, y_;

    double sum = 0;
    for (int i=(int)N/2; i<N ; i++){
        x_ = lane.waypoints[i].pose.pose.position.x;
        y_ = lane.waypoints[i].pose.pose.position.y;
        sum = sum + calculate_min(ref,x_,y_); //*pow(0.9,i);
    }
    return sum;
}

int rolloutPlanner::calculate_min_idx(const hmcl_msgs::Lane& ref, double x1, double y1){
    int idx=0;
    double min =100;
    for (int i = 0; i <ref.waypoints.size(); i++){   
        double x_ = ref.waypoints[i].pose.pose.position.x;
        double y_ = ref.waypoints[i].pose.pose.position.y;
        double dis_ = sqrt(pow(x_- x1,2) + pow(y_ -y1,2));
        if ( dis_< min){
            min = dis_;
            idx = i;
        }
    }
    return idx;
}

void rolloutPlanner::viz_local(const hmcl_msgs::Lane& lane){
    visualization_msgs::MarkerArray lane_markers;
    visualization_msgs::Marker lane_marker;
    lane_marker.header.frame_id = "map";
    lane_marker.header.stamp = ros::Time();
    lane_marker.ns = "local_markers";
    lane_marker.id = 2500;
    lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
    lane_marker.action = visualization_msgs::Marker::ADD;
    lane_marker.lifetime = ros::Duration(0.1);

    lane_marker.color.a = 1.0;
    lane_marker.color.r = 1.0;
    lane_marker.color.g = 1.0;
    lane_marker.color.b = 0.0;
    
    lane_marker.scale.x = 0.3;
    lane_marker.scale.y = 1.0;
    lane_marker.scale.z = 0.3;

    for (int i = 0; i < lane.waypoints.size(); i++){
        geometry_msgs::Point p;
        p.x = lane.waypoints[i].pose.pose.position.x;
        p.y = lane.waypoints[i].pose.pose.position.y;
        p.z = range_lane.lanes[0].waypoints[0].pose.pose.position.z;
        lane_marker.points.push_back(p);
    }
    lane_markers.markers.push_back(lane_marker);
    pub_viz.publish(lane_markers);
}

void rolloutPlanner::viz_all(const hmcl_msgs::LaneArray& lane_arr){
    visualization_msgs::MarkerArray lane_markers;
    for (int i=0; i< lane_arr.lanes.size(); i++){
        visualization_msgs::Marker lane_marker;
        lane_marker.header.frame_id = "map";
        lane_marker.header.stamp = ros::Time();
        lane_marker.ns = "local_sample";
        lane_marker.id = 17123+i;
        lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
        lane_marker.action = visualization_msgs::Marker::ADD;
        lane_marker.lifetime = ros::Duration(0.1);

        lane_marker.color.a = 0.5;
        lane_marker.color.r = 0.0;
        lane_marker.color.g = 1.0;
        lane_marker.color.b = 0.0;
        
        lane_marker.scale.x = 0.3;
        lane_marker.scale.y = 0.3;
        lane_marker.scale.z = 0.3;

        for (int j = 0; j < lane_arr.lanes[i].waypoints.size(); j++){
            geometry_msgs::Point p;
            p.x = lane_arr.lanes[i].waypoints[j].pose.pose.position.x;
            p.y = lane_arr.lanes[i].waypoints[j].pose.pose.position.y;
            p.z = range_lane.lanes[0].waypoints[0].pose.pose.position.z;
            lane_marker.points.push_back(p);
        }
    lane_markers.markers.push_back(lane_marker);
    }
    pub_all.publish(lane_markers);
}


int main(int argc, char** argv){
    ros::init(argc, argv, "rollout_planner");
    ros::NodeHandle nh;
    rolloutPlanner rolloutPlanner(nh);

    ros::spin();
    return 0;
}