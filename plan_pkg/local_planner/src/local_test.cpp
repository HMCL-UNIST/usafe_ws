#include "local_test.h"

localtest::localtest(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Local Planner Initialize");
    sub_traj = nh_.subscribe("/lane_in_range", 1, &localtest::trajCallback, this);

    pub_traj = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 1);
    pub_viz = nh_.advertise<visualization_msgs::Marker>("/local_traj_viz", 1);
    pub_lir = nh_.advertise<visualization_msgs::MarkerArray>("/locals_viz", 1);
    pub_pts = nh_.advertise<visualization_msgs::MarkerArray>("/pts_viz", 1);

    timer_ = nh_.createTimer(ros::Duration(0.1), &localtest::connect_handler,this);    

    //parameter
    nh_.param<double>("minimum_lane_change_length", min_lc_len, 5.0);
    nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 0.5);
    nh_.param<double>("lane_changing_duration", lc_duration, 3.0);
    nh_.param<double>("lane_change_deceleration", lc_dec, -2.0);
    nh_.param<double>("minimum_lane_change_velocity", min_lc_vel, 5.0);
}

localtest::~localtest()
{}

void localtest::connect_handler(const ros::TimerEvent& time){
    hmcl_msgs::Lane pub_lane;
    if ( range_index.size() >1){
        // viz_lir(range_lane);
        std::cout <<" lane change " << std::endl;
        struct Point pts;
        PreparePhase(lc_dec);   // prepare_dist, lc_dist

        std::cout <<" wpts size " << range_lane.lanes[0].waypoints.size()  <<std::endl;
        // std::cout <<" pop out wpts size " << range_lane.lanes[0].waypoints.front()  <<std::endl;

        int startidx, lcidx_s, lcidx_t, endidx;
        current_pos.section = range_lane.lanes[0].waypoints[1].pose.pose;

        startidx = FindIndex(range_lane.lanes[0], lc_prepare_dist, current_pos.section); // lc start point

        pts.start.section = range_lane.lanes[0].waypoints[startidx].pose.pose;    

        pts.start.length =lc_prepare_dist;
        pts.start.speed = lc_prepare_vel;

        std::cout <<" lc prepare dist " << lc_prepare_dist << std::endl;
        std::cout <<" lc prepare vel " << lc_prepare_vel << std::endl;
        
        lcidx_t= FindIndex(range_lane.lanes[1], 0, pts.start.section);
        
        lcidx_s = FindIndex(range_lane.lanes[0], lc_dist, range_lane.lanes[0].waypoints[lcidx_t].pose.pose);
        endidx = FindIndex(range_lane.lanes[1], lc_dist, range_lane.lanes[1].waypoints[lcidx_t].pose.pose); // lc finish point

        pts.end.section = range_lane.lanes[1].waypoints[endidx].pose.pose;
        pts.end.length = lc_dist;
        pts.end.speed = lc_vel;

        pts.start.index = startidx;
        pts.end.index = endidx;
        cout <<"start idx "<< startidx<< ", end  : " << endidx<< endl;
        hmcl_msgs::Lane lanechangeLane = getLaneChangePaths(range_lane, pts);

        Eigen::Quaterniond q;
        q.x() = current_pos.section.orientation.x;
        q.y() = current_pos.section.orientation.y;
        q.z() = current_pos.section.orientation.z;
        q.w() = current_pos.section.orientation.w;
        Eigen::Vector3d t(current_pos.section.position.x, current_pos.section.position.y, current_pos.section.position.z);
        Eigen::Matrix3d tf3x3 =  q.normalized().toRotationMatrix();
        double yaw_ = atan2( tf3x3(1,0),tf3x3(0,0) );

        std::vector<double> X = {};
        std::vector<double> Y = {};
        std::vector<double> s_x = {};
        std::vector<double> s_y = {}; 
        std::vector<double> s_r = {};        
        hmcl_msgs::LaneArray lanes_trans;
        hmcl_msgs::Lane lanes;

        if (startidx==0){
            printf("start idx is zero");
            X.push_back(0);
            Y.push_back(0);
        }
        else{
            for (int i =0; i <startidx; i++){
                hmcl_msgs::Waypoint wpt;
                wpt.pose.pose.position.x = range_lane.lanes[0].waypoints[i].pose.pose.position.x;
                wpt.pose.pose.position.y = range_lane.lanes[0].waypoints[i].pose.pose.position.y;
                wpt.pose.pose.position.z = 0;
                wpt.pose.pose.orientation.x = range_lane.lanes[0].waypoints[i].pose.pose.orientation.x;
                wpt.pose.pose.orientation.y = range_lane.lanes[0].waypoints[i].pose.pose.orientation.y;
                wpt.pose.pose.orientation.z = range_lane.lanes[0].waypoints[i].pose.pose.orientation.z;
                wpt.pose.pose.orientation.w = range_lane.lanes[0].waypoints[i].pose.pose.orientation.w;
                lanes.waypoints.push_back(wpt);
                }

            for (int i =startidx; i <startidx+2; i++){
                geometry_msgs::Pose ppp = range_lane.lanes[0].waypoints[i].pose.pose;
                Eigen::Vector3d pt(ppp.position.x, ppp.position.y, ppp.position.z);
                pt = pt - t;
                Eigen::Vector3d ptss = tf3x3.inverse()*pt;
                X.push_back(ptss[0]);
                Y.push_back(ptss[1]);
                }
            }

        for (int i =endidx; i <endidx+2; i++){
            geometry_msgs::Pose ppp = range_lane.lanes[1].waypoints[i].pose.pose;
            Eigen::Vector3d pt(ppp.position.x, ppp.position.y, ppp.position.z);
            pt = pt - t;
            Eigen::Vector3d ptss = tf3x3.inverse()*pt;
            X.push_back(ptss[0]);
            Y.push_back(ptss[1]);
        }

        tk::spline::spline_type type = tk::spline::cspline;
        tk::spline s;
        s.set_boundary(tk::spline::second_deriv, 0.0,tk::spline::second_deriv, 0.0);
        s.set_points(X,Y,type);     // this calculates all spline coefficients
        // s.make_monotonic();     // adjusts spline coeffs to be monotonic
        
        int n = int(X.size()*4);    // number of grid points to plot the spline
        double xmin = X[0] - 0.5;
        double xmax = X.back() + 0.5;
        for(int i=0; i<n; i++) {
            double x = xmin + (double)i*(xmax-xmin)/(n-1);
            s_x.push_back(x);
            s_y.push_back(s(x));        
            s_r.push_back(atan2(fderiv(s,1,x), s.deriv(1,x)));
        }

        for (int j =0; j <s_x.size(); j++){
            hmcl_msgs::Waypoint wpt;
            Eigen::Vector3d pt(s_x[j], s_y[j],0);
            Eigen::Vector3d ptss = tf3x3*pt;
            ptss = ptss + t;
            wpt.pose.pose.position.x = ptss[0];
            wpt.pose.pose.position.y = ptss[1];
            wpt.pose.pose.position.z = 0;

            const auto yaw = (yaw_+s_r[j])*M_PI / 180;
            const auto pitch = 0;
            const auto roll = 0;

            Eigen::Quaternion<float> q_ = Eigen::AngleAxisf(roll, Eigen::Vector3f::UnitX()) *
                Eigen::AngleAxisf(pitch, Eigen::Vector3f::UnitY()) *
                Eigen::AngleAxisf(yaw, Eigen::Vector3f::UnitZ());

            wpt.pose.pose.orientation.x = q_.x();
            wpt.pose.pose.orientation.y = q_.y();
            wpt.pose.pose.orientation.z = q_.z();
            wpt.pose.pose.orientation.w = q_.w();
            lanes.waypoints.push_back(wpt);
        }

        for (int j = endidx+1; j <range_lane.lanes[1].waypoints.size(); j++){
            hmcl_msgs::Waypoint wpt;
            wpt.pose.pose.position.x = range_lane.lanes[1].waypoints[j].pose.pose.position.x;
            wpt.pose.pose.position.y = range_lane.lanes[1].waypoints[j].pose.pose.position.y;
            wpt.pose.pose.position.z = 0;
            
            wpt.pose.pose.orientation.x = range_lane.lanes[1].waypoints[j].pose.pose.orientation.x;
            wpt.pose.pose.orientation.y = range_lane.lanes[1].waypoints[j].pose.pose.orientation.y;
            wpt.pose.pose.orientation.z = range_lane.lanes[1].waypoints[j].pose.pose.orientation.z;
            wpt.pose.pose.orientation.w = range_lane.lanes[1].waypoints[j].pose.pose.orientation.w;
            lanes.waypoints.push_back(wpt);
        }
        lanes_trans.lanes.push_back(lanes);
        viz_lir(lanes_trans);
    }
}

void localtest::trajCallback(const hmcl_msgs::LaneArray& lane_msg){   
    range_index = {};
    for (int i =0; i < lane_msg.lanes.size(); i++){
        range_index.push_back(lane_msg.lanes[i].waypoints.size());
    }

    // print
    std::cout << "lane in range index = { ";
    for (int n : range_index) {
        std::cout << n << ", ";
    }
    std::cout << "}; \n";

    range_lane = lane_msg;
}

void localtest::PreparePhase(double deceleration){
    double current_vel = 8;
    lc_prepare_vel = max(current_vel + deceleration * lc_prepare_dur,0.3);
    lc_prepare_dist = max(current_vel * lc_prepare_dur + 0.5 * deceleration * std::pow(lc_prepare_dur, 2), 0.0);  
    lc_vel = max(lc_prepare_vel + deceleration * lc_duration,0.3);
    lc_dist = max(lc_prepare_vel * lc_duration + 0.5 * deceleration * std::pow(lc_duration, 2), min_lc_len);
    return;
}

int localtest::FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose){
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
            // cout << "dist :: " << abs(dis_-dist) << endl;
            dis = abs(dis_-dist);
            wpt_idx = i;
        }
    }    
    return wpt_idx;
}

hmcl_msgs::LaneArray localtest::cuttraj(const hmcl_msgs::LaneArray& msg){
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

hmcl_msgs::Lane localtest::getLaneChangePathPrepareSegment(hmcl_msgs::Lane lane_data, Sector section){
    const double s_start = 0;
    const double s_end = section.index;

    hmcl_msgs::Lane lane;
    for (int i=s_start; i < s_end; i++){
        lane.waypoints.push_back(lane_data.waypoints[i]);
    }
    return lane;
}


float localtest::getPt(float n1 , float n2 , float perc ){
    float diff = n2 - n1;
    return n1 + ( diff * perc );
}    
hmcl_msgs::Lane localtest::spline(hmcl_msgs::Lane lane, geometry_msgs::Pose pos1, geometry_msgs::Pose pos2, geometry_msgs::Pose pos3, geometry_msgs::Pose pos4, double lc_dist, int nn){

    std::vector<double> X = {}; // must be increasing
    std::vector<double> Y = {};

    tk::spline s(X,Y);
    double x=1.5, y=s(x), deriv=s.deriv(1,x);
}
hmcl_msgs::Lane localtest::straight(hmcl_msgs::Lane lane, geometry_msgs::Pose pos1, geometry_msgs::Pose pos2, geometry_msgs::Pose pos3, geometry_msgs::Pose pos4, double lc_dist, int nn){
    float x1 = pos1.position.x;
    float y1 = pos1.position.y;
    float x4 = pos4.position.x;
    float y4 = pos4.position.y;
    
    float x, y;
    float dist = lc_dist/nn;

    for(float i = 0 ; i < lc_dist ; i += dist ){

        x = getPt( x1 , x4 , i );
        y = getPt( y1 , y4 , i );
        hmcl_msgs::Waypoint wpt;
        wpt.pose.pose.position.x = x;
        wpt.pose.pose.position.y = y;
        lane.waypoints.push_back(wpt);
    }
    return lane;
}

// hmcl_msgs::Lane localtest::constructCandidatePath(Point LC_Point, hmcl_msgs::Lane lane_prepare, hmcl_msgs::Lane lane_end){
//     geometry_msgs::Pose lc_start_pose;
//     if (lane_prepare.waypoints.size() >0){
//         lc_start_pose = lane_prepare.waypoints[lane_prepare.waypoints.size()].pose.pose;    
//     }
//     else{
//         lc_start_pose = current_pos.section;
//         cout << "current pose : " << current_pos.section.position.x <<endl;
//     }
//     geometry_msgs::Pose lc_end_pose = lane_end.waypoints[0].pose.pose;
//     geometry_msgs::Pose lc_mid_pose1;
//     geometry_msgs::Pose lc_mid_pose2;
//     cout << "start pose : " << lc_start_pose.position.x << lc_start_pose.position.y <<endl;
//     cout << "end pose : " << lc_end_pose.position.x << lc_end_pose.position.y <<endl;
//     lc_mid_pose1.position.x = lc_start_pose.position.x * 3/4 + lc_end_pose.position.x * 1/4;
//     lc_mid_pose1.position.y = lc_start_pose.position.y * 3/4 + lc_end_pose.position.y * 1/4;
//     lc_mid_pose2.position.x = lc_start_pose.position.x * 1/4 + lc_end_pose.position.x * 3/4;
//     lc_mid_pose2.position.y= lc_start_pose.position.y * 1/4 + lc_end_pose.position.y * 3/4;
//     cout << "mid pose : " << lc_mid_pose2.position.x << lc_mid_pose2.position.y <<endl;

//     int nn = max(LC_Point.start.prepare_idx2 -LC_Point.start.prepare_idx1, 10);

//     hmcl_msgs::Lane lane = straight(lane_prepare, lc_start_pose, lc_mid_pose1, lc_mid_pose2, lc_end_pose, LC_Point.end.length, nn);
//     return lane;
// }

hmcl_msgs::Lane localtest::getLaneChangePaths(hmcl_msgs::LaneArray lane_msgs, Point LC_Point){

    hmcl_msgs::Lane prepare_lane = getLaneChangePathPrepareSegment(lane_msgs.lanes[0], LC_Point.start);
    std::cout <<" start lc point " << LC_Point.start.section.position.x<<" , " <<LC_Point.start.section.position.y <<std::endl;
    std::cout <<" end lc point " << LC_Point.end.section.position.x<< " , " <<LC_Point.end.section.position.y <<std::endl;

    return prepare_lane;
    // hmcl_msgs::Lane candidate_path = constructCandidatePath(LC_Point, prepare_lane, lanechanged_lane);
    // for (int i=0; i<lanechanged_lane.waypoints.size(); i++){
    //     candidate_path.waypoints.push_back(lanechanged_lane.waypoints[i]);
    // }
    // candidate_path.speed_limit = LC_Point.end.speed;section.prepare_idx2
    // return candidate_path;

}

void localtest::viz_local(const hmcl_msgs::Lane& lane){
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


void localtest::viz_lir(const hmcl_msgs::LaneArray& array){
    visualization_msgs::MarkerArray lane_markers;

    for (int i = 0; i < array.lanes.size(); i++){
        visualization_msgs::Marker lane_marker;
        lane_marker.header.frame_id = "map";
        lane_marker.header.stamp = ros::Time();
        lane_marker.ns = "local_markers";
        lane_marker.id = 2500+i;
        lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
        lane_marker.action = visualization_msgs::Marker::ADD;

        lane_marker.color.a = 1.0;
        lane_marker.color.r = 0.0;
        lane_marker.color.g = 0.0;
        lane_marker.color.b = 0.0;
        
        lane_marker.scale.x = 1;
        lane_marker.scale.y = 0.1;
        lane_marker.scale.z = 0.1;

        if (i == 0){
            lane_marker.color.g = 1.0;  
        }
        else if (i ==1){
            lane_marker.color.b = 1.0;
        }

        for (int j = 0; j < array.lanes[i].waypoints.size(); j++){
            geometry_msgs::Point p;
            p.x = array.lanes[i].waypoints[j].pose.pose.position.x;
            p.y = array.lanes[i].waypoints[j].pose.pose.position.y;
            lane_marker.points.push_back(p);
        }

    lane_markers.markers.push_back(lane_marker);
    }
    pub_lir.publish(lane_markers);
}
int main(int argc, char** argv){
    ros::init(argc, argv, "localtest");
    ros::NodeHandle nh;
    localtest localtest(nh);

    ros::spin();
    return 0;
}