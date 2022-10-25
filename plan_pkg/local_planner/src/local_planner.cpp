#include "local_planner.h"

localplanners::localplanners(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Local Planner Initialize");
    sub_pos = nh_.subscribe("/pose_estimate", 1, &localplanners::poseCallback, this);
    sub_vel = nh_.subscribe("/vehicle_status", 1, &localplanners::wheelCallback, this);
    
    sub_traj = nh_.subscribe("/lane_in_range", 1, &localplanners::trajCallback, this);
    sub_flag = nh_.subscribe("/behavior_state", 1, &localplanners::flagCallback, this);
    sub_obs = nh_.subscribe("/behavior_factor", 1, &localplanners::ObsCallback, this);

    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 1);
    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1);
    pub_bool = nh_.advertise<std_msgs::Bool>("/local_return", 1);
    timer_ = nh_.createTimer(ros::Duration(0.05), &localplanners::connect_handler,this);

    //parameter
    nh_.param<double>("minimum_lane_change_length", min_lc_len, 5.0);
    nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 1.5);
    nh_.param<double>("lane_changing_duration", lc_duration, 3.0);
    nh_.param<double>("minimum_lane_change_velocity", min_lc_vel, 3.0);
    nh_.param<double>("lane_width", lane_width, 1.75);
    nh_.param<double>("obstacle_length", obs_len, 8.00);
}

localplanners::~localplanners()
{}

void localplanners::poseCallback(const nav_msgs::Odometry& state_msg){
    current_pos.section = state_msg.pose.pose;
    st_flag = true;
}
void localplanners::wheelCallback(const hmcl_msgs::VehicleStatus& state_msg){
    current_pos.speed = abs(state_msg.wheelspeed.wheel_speed);
    vel_flag =true;
}
void localplanners::flagCallback(const std_msgs::Int16ConstPtr& flag_msg){
    if ((BehaviorState)flag_msg->data == BehaviorState::LaneChange){
        lc_flag = true;
    }
    else{
        lc_flag = false;        
    }

    if ((BehaviorState)flag_msg->data == BehaviorState::ObstacleLaneChange){
        obs_flag = true;
    }
    else{
        obs_flag = false;
    }
}
void localplanners::trajCallback(const hmcl_msgs::LaneArray& lane_msg){   
    std::cout << "lane in range # " << lane_msg.lanes.size() <<std::endl;
    range_index = {};
    for (int i =0; i < lane_msg.lanes.size(); i++){
        range_index.push_back(lane_msg.lanes[i].lane_id);
    }
    range_lane = lane_msg;
}
void localplanners::ObsCallback(const hmcl_msgs::BehaviorFactor& obs_msg){   
    if (obs_flag == true)
    {
        obs.x = obs_msg.xObstacle;
        obs.y = obs_msg.yObstacle;
        obs.length = obs_msg.front_dist;
        obs.exist =true;
    }
}

void localplanners::connect_handler(const ros::TimerEvent& time){
    if ( st_flag = false || vel_flag == false){
        return;       
    }

    PreparePhase();
    Eigen::Quaterniond q;
    q.x() = current_pos.section.orientation.x;
    q.y() = current_pos.section.orientation.y;
    q.z() = current_pos.section.orientation.z;
    q.w() = current_pos.section.orientation.w;
    Eigen::Vector3d t(current_pos.section.position.x, current_pos.section.position.y, current_pos.section.position.z);
    Eigen::Matrix3d tf3x3 =  q.normalized().toRotationMatrix();
    double yaw_ = atan2( tf3x3(1,0),tf3x3(0,0));

    std::vector<double> X = {};
    std::vector<double> Y = {};
    std::vector<tuple<double,double,double>> pt_xy = {};

    if(range_index.size() == 0){
        ROS_INFO("Error");
        std::cout <<" no waypoints here with size " << range_index.size() << std::endl;
        return;
    }
    else if(range_lane.lanes[0].lane_id ==1000 && range_lane.lanes.size()==1){
        return;
    }

    if (return_flag == true){
        ROS_INFO("RETURN Flag");
    }

    if ((lc_flag ==false || range_lane.lanes.size()<2 ) && obs_flag ==false && return_flag==false){
        ROS_INFO("One Lane");
        pub_lane = CutoffTraj();

        // int startidx = FindClosest(range_lane.lanes[0], current_pos.section);
        // cout << "wpt size :: " << range_lane.lanes[0].waypoints.size() - startidx<< ", st : " << startidx <<",  size:" << range_lane.lanes[0].waypoints.size() << endl;
        // for (int i = startidx; i <range_lane.lanes[0].waypoints.size();i++){
        //     pub_lane.waypoints.push_back(range_lane.lanes[0].waypoints[i]);          
        // }
    }
    else if (return_flag ==true && obs_flag == false){
        pub_lane.waypoints.clear();

        int lane_idx = 0;
        for (int i=0; i< range_lane.lanes.size();i++){
            if (range_lane.lanes[i].lane_id =1000){
                lane_idx = i;
            }
        }
        int startidx = FindIndex(range_lane.lanes[lane_idx], 0, current_pos.section);
        
        for (int i=startidx; i<range_lane.lanes[lane_idx].waypoints.size(); i++){
            hmcl_msgs::Waypoint wpt;
            wpt = range_lane.lanes[lane_idx].waypoints[i];
            pub_lane.waypoints.push_back(wpt);
        }

        double dis = sqrt(pow(current_pos.section.position.x- obs.x,2) + pow(current_pos.section.position.y-obs.y,2));
        ROS_WARN("DIST :: %.4f", dis);
        if (dis > 13){
            std_msgs::Bool msg;
            msg.data = true;
            pub_bool.publish(msg);
        }
        if (dis > 15){
            return_flag = false;
        }
    }
    else if ( lc_flag == true && range_lane.lanes.size()>1  || obs_flag == true){
        pub_lane.waypoints.clear();
        ROS_INFO("Lane Change");
        int lane_idx=1;
        if (obs_flag ==true){
            for (int i=0; i<range_lane.lanes.size(); i++){
            if (range_lane.lanes[i].lane_id =1000){
                lane_idx = i;
                if (return_flag == false && obs.exist == true){
                    double min1 = calculate_min(range_lane.lanes[lane_idx],obs.x,obs.y);
                    double min2 = calculate_min(range_lane.lanes[0],obs.x,obs.y);
                    
                    if (min1 > min2){
                        return_flag = true;
                    }
                    else{
                        return_flag = false;
                    }
                }
            }}
        }
        else if(range_lane.lanes[1].lane_id ==1000){
            lane_idx = 0;
        }
        
        int endidx = FindIndex(range_lane.lanes[lane_idx], lc_dist +lc_prepare_dist+lane_width, current_pos.section);
        Eigen::Vector3d pt_e(range_lane.lanes[lane_idx].waypoints[endidx].pose.pose.position.x, range_lane.lanes[lane_idx].waypoints[endidx].pose.pose.position.y, 0);
        pt_e = tf3x3.inverse()*(pt_e - t);
        int nn = abs(int(pt_e[0]));
        double factor = 1.0;
        if (obs_flag ==true) factor =1.2;
        X.push_back(0);
        Y.push_back(0);
        
        X.push_back(lc_prepare_dist);
        Y.push_back(pt_e[1]/nn);

        X.push_back(lc_prepare_dist+lc_dist);
        Y.push_back((pt_e[1]- pt_e[1]/nn)*factor);

        X.push_back(max(lc_prepare_dist+lc_dist+2, pt_e[0]));
        Y.push_back(pt_e[1]*factor);

        tk::spline::spline_type type = tk::spline::cspline;
        tk::spline s;
        s.set_boundary(tk::spline::second_deriv, 0.0,tk::spline::second_deriv, 0.0);
        s.set_points(X, Y, type);     // this calculates all spline coefficients
        s.make_monotonic();     // adjusts spline coeffs to be monotonic
        
        int n = int(X.size()*4);    // number of grid points to plot the spline
        double xmin = X[0] - 0.5;
        double xmax = X.back() + 0.5;

        for(int i=0; i<n; i++) {
            double x = xmin + (double)i*(xmax-xmin)/(n-1);
            pt_xy.push_back(make_tuple(x,s(x),atan2(fderiv(s,1,x), s.deriv(1,x))));
        }

        for (int j =0; j <pt_xy.size(); j++){
            hmcl_msgs::Waypoint wpt;
            Eigen::Vector3d pt(get<0>(pt_xy[j]), get<1>(pt_xy[j]),0);
            pt = tf3x3*pt + t ;
            wpt.pose.pose.position.x = pt[0];
            wpt.pose.pose.position.y = pt[1];
            wpt.pose.pose.position.z = 0;
            
            const auto yaw = (yaw_+get<2>(pt_xy[j]))*M_PI / 180;
            const auto pitch = 0;
            const auto roll = 0;
            Eigen::Quaternion<float> q_ = Eigen::AngleAxisf(roll, Eigen::Vector3f::UnitX()) *
                                            Eigen::AngleAxisf(pitch, Eigen::Vector3f::UnitY()) *
                                            Eigen::AngleAxisf(yaw, Eigen::Vector3f::UnitZ());

            wpt.pose.pose.orientation.x = q_.x();
            wpt.pose.pose.orientation.y = q_.y();
            wpt.pose.pose.orientation.z = q_.z();
            wpt.pose.pose.orientation.w = q_.w();
            pub_lane.waypoints.push_back(wpt);
        }
        for (int j = endidx+1; j <range_lane.lanes[lane_idx].waypoints.size(); j++){
            hmcl_msgs::Waypoint wpt;
            wpt.pose.pose.position.x = range_lane.lanes[lane_idx].waypoints[j].pose.pose.position.x;
            wpt.pose.pose.position.y = range_lane.lanes[lane_idx].waypoints[j].pose.pose.position.y;
            wpt.pose.pose.position.z = 0;
            
            wpt.pose.pose.orientation.x = range_lane.lanes[lane_idx].waypoints[j].pose.pose.orientation.x;
            wpt.pose.pose.orientation.y = range_lane.lanes[lane_idx].waypoints[j].pose.pose.orientation.y;
            wpt.pose.pose.orientation.z = range_lane.lanes[lane_idx].waypoints[j].pose.pose.orientation.z;
            wpt.pose.pose.orientation.w = range_lane.lanes[lane_idx].waypoints[j].pose.pose.orientation.w;
            pub_lane.waypoints.push_back(wpt);
        }
    }

    pub_lane.signal_id = range_lane.lanes[0].signal_id;
    pub_lane.lane_id = range_lane.lanes[0].lane_id;
    if (lc_flag == true  || obs_flag ==true ){
        pub_lane.speed_limit = 7.5;
    }
    else{
        pub_lane.speed_limit = 25;
    }
    viz_local(pub_lane);
    pub_traj.publish(pub_lane);
}

void localplanners::PreparePhase(){
    double current_vel = max(current_pos.speed,1.0);
    double deceleration = 0;
    if (current_vel > 5){
        deceleration = -current_vel/5;
    }
    lc_prepare_vel = max(current_vel + deceleration * lc_prepare_dur,0.3);
    lc_prepare_dist = max(current_vel * lc_prepare_dur + 0.5 * deceleration * std::pow(lc_prepare_dur, 2), 0.0);  
    lc_vel = max(lc_prepare_vel + deceleration * lc_duration,0.3);
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

double localplanners::calculate_min(const hmcl_msgs::Lane& lane, double x, double y ){

    double min =100;
    for (int i=0; i< lane.waypoints.size(); i++){
        double x_ = lane.waypoints[i].pose.pose.position.x;
        double y_ = lane.waypoints[i].pose.pose.position.y;
        double dis = sqrt(pow(x_-x,2) + pow(y_ -y,2));
        
        if (min  > dis){
            min = dis;
        }
    }
    return min;
}


hmcl_msgs::Lane localplanners::CutoffTraj(){
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
    return lane;
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