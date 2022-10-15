#include "v2x_pvd.h"

V2XPvd::V2XPvd(ros::NodeHandle& nh, ros::NodeHandle& nh_local): 
    nh_(nh), nh_local_(nh_local)
{
    pub_pvd = nh_.advertise<v2x_msgs::PVD>("/pvd", 10);
    sub_pos = nh_local_.subscribe("/fix", 1, &V2XPvd::pos_callback, this);
    sub_dir = nh_.subscribe("/heading_ned", 1, &V2XPvd::dir_callback, this);
    sub_veh = nh_.subscribe("/vehcle_status", 1, &V2XPvd::veh_callback,this);
    timer_ = nh_.createTimer(ros::Duration(0.1), &V2XPvd::connect_handler,this);    

    ROS_INFO("V2X PVD Publisher Node Initialize");
}

V2XPvd::~V2XPvd(){}

void V2XPvd::connect_handler(const ros::TimerEvent& time){
    // ROS_INFO("V2X PVD Pub");
    V2XPvd::publisher();
}


void V2XPvd::pos_callback(const sensor_msgs::NavSatFix::ConstPtr& nav_data){
    lat_c = nav_data -> latitude;
    lon_c = nav_data -> longitude;
    alt_c = nav_data -> altitude;
    lat_c = lat_c;
    lon_c = lon_c;
    alt_c = alt_c;
}

void V2XPvd::dir_callback(const std_msgs::Float64::ConstPtr& dir_data){
    dir_c = 90-(dir_data-> data - 0.3*180/M_PI);
    dir_c = dir_c/0.0125;
    // ROS_INFO("dir data %.2f", dir_c);
}

void V2XPvd::veh_callback(const hmcl_msgs::VehicleStatus::ConstPtr& veh_data){
    vel_c = veh_data->wheelspeed.wheel_speed;
    vel_c = vel_c/0.02;
    gear_c = veh_data->gear_info.gear;
}

void V2XPvd::publisher(){

    v2x_msgs::PVD V2X_pvd;
    V2X_pvd.lat = lat_c;
    V2X_pvd.lon = lon_c;
    V2X_pvd.alt = alt_c;
    V2X_pvd.dir = dir_c;
    V2X_pvd.vel = vel_c;
    V2X_pvd.gear = gear_c;

    // printf("pvd ::: lat : %f , lon : %f , alt : %f , dir %f, vel : %f , gear %d \n", lat_c,lon_c,alt_c,dir_c,vel_c,gear_c);
    pub_pvd.publish(V2X_pvd);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "pvd_pub");
    ros::NodeHandle nh, nhlocal;
    V2XPvd V2XPvd(nh, nhlocal);
    
    ros::CallbackQueue callback_queue_nh, callback_queue_nh_local_path;
    nh.setCallbackQueue(&callback_queue_nh);
    nhlocal.setCallbackQueue(&callback_queue_nh_local_path);

    std::thread spinner_thread_nh([&callback_queue_nh]()
    {
    ros::SingleThreadedSpinner spinner_nh;
    spinner_nh.spin(&callback_queue_nh);
    });

    std::thread spinner_thread_nh_local_path([&callback_queue_nh_local_path]() {
    ros::SingleThreadedSpinner spinner_nh_local_path;
    spinner_nh_local_path.spin(&callback_queue_nh_local_path);
    });

    ros::spin();

    spinner_thread_nh.join();
    spinner_thread_nh_local_path.join();

    return 0;
}
