#include "v2x_viz.h"

V2X_viz::V2X_viz(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("V2X visualization Initialize");

    sub_spat = nh_.subscribe("/SPAT", 1, &V2X_viz::spatCallback, this);
    sub_mission1 = nh_.subscribe("/Mission1", 1, &V2X_viz::mission1Callback, this);
    sub_mission2 = nh_.subscribe("/Mission2", 1, &V2X_viz::mission2Callback, this);
    
    viz_spat = nh_.advertise<visualization_msgs::MarkerArray>("/SPAT_viz", 1);
    viz_mission1 = nh_.advertise<visualization_msgs::MarkerArray>("/Mission1_viz", 1);
    viz_mission2 = nh_.advertise<visualization_msgs::MarkerArray>("/Mission2_viz", 1);
    
    timer_ = nh_.createTimer(ros::Duration(0.1), &V2X_viz::connect_handler,this);  
}

V2X_viz::~V2X_viz()
{}

void V2X_viz::connect_handler(const ros::TimerEvent& time){
    if (spat_flag){
        viz_spat.publish(spat_marker_array);
    }
    if (mission1_flag){
        viz_mission1.publish(mission1_marker_array);
    }
    if (mission2_flag){
        viz_mission2.publish(mission2_marker_array);
    }
    return;
}

void V2X_viz::spatCallback(const v2x_msgs::SPAT& msg){
    ROS_INFO("SPAT callback");
    spat_flag = true;
    
    int id = msg.id;
    spat_marker_array.markers.clear();
    for(int i=0; i<msg.States.size(); i++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ;
        marker_tmp.id = 60000+100*id+i;
        marker_tmp.ns = "spat";
        marker_tmp.text = msg.States[i].movementName +" : "+std::to_string(msg.States[i].timing_min_End_Time);
        marker_tmp.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        marker_tmp.action = visualization_msgs::Marker::ADD;                  

        float a = 7.5;

        if (id == 1 ){
            marker_tmp.pose.position.x = -80.518;
            marker_tmp.pose.position.y = 86.401;
        }
        else if (id ==2){
            marker_tmp.pose.position.x = -165.194;
            marker_tmp.pose.position.y = 179.630;
        }
        else if (id ==3){
            marker_tmp.pose.position.x = -246.9;
            marker_tmp.pose.position.y = 269.520;
        }
        marker_tmp.pose.position.z = 10;

        if (msg.States[i].signalGroup == 16){
            marker_tmp.pose.position.x -= a;
            marker_tmp.pose.position.y += a;

        }
        else if (msg.States[i].signalGroup == 17 ){
            marker_tmp.pose.position.x -= a;
            marker_tmp.pose.position.y += a;
            marker_tmp.pose.position.z -= 1;
            
        }        
        else if (msg.States[i].signalGroup == 18 ){
            marker_tmp.pose.position.x -= a;
            marker_tmp.pose.position.y += a;
            marker_tmp.pose.position.z -= 2;
        }
        
        else if (msg.States[i].signalGroup == 19 ){
            marker_tmp.pose.position.x += a;
            marker_tmp.pose.position.y += a;

        }
        else if (msg.States[i].signalGroup == 20 ){
            marker_tmp.pose.position.x += a;
            marker_tmp.pose.position.y += a;
            marker_tmp.pose.position.z -= 1;
        }
        else if (msg.States[i].signalGroup == 21 ){
            marker_tmp.pose.position.x += a;
            marker_tmp.pose.position.y += a;
            marker_tmp.pose.position.z -= 2;
        }
        
        else if (msg.States[i].signalGroup == 22 ){
            marker_tmp.pose.position.x += a;
            marker_tmp.pose.position.y -= a;
        }
        else if (msg.States[i].signalGroup == 23 ){
            marker_tmp.pose.position.x += a;
            marker_tmp.pose.position.y -= a;
            marker_tmp.pose.position.z -= 1;
        }
        else if (msg.States[i].signalGroup == 24 ){
            marker_tmp.pose.position.x += a;
            marker_tmp.pose.position.y -= a;
            marker_tmp.pose.position.z -= 2;
        }

        else if (msg.States[i].signalGroup == 13 ){
            marker_tmp.pose.position.x -= a; 
            marker_tmp.pose.position.y -= a;
        }
        else if (msg.States[i].signalGroup == 14){
            marker_tmp.pose.position.x -= a;
            marker_tmp.pose.position.y -= a;
            marker_tmp.pose.position.z -= 1;
            
        }
        else if (msg.States[i].signalGroup == 15 ){
            marker_tmp.pose.position.x -= a; 
            marker_tmp.pose.position.y -= a;
            marker_tmp.pose.position.z -= 2;
        }

        marker_tmp.lifetime = ros::Duration(1.0);
        marker_tmp.color.a = 1.0;
        marker_tmp.scale.z = 1.0;

        if (msg.States[i].eventState == 3 ){
            marker_tmp.color.r = 1.0;
            marker_tmp.color.g = 0.0;
            marker_tmp.color.b = 0.0;            
        }
        else if (msg.States[i].eventState == 7 || msg.States[i].eventState == 8){
            marker_tmp.color.r = 1.0;
            marker_tmp.color.g = 1.0;
            marker_tmp.color.b = 0.0;            
        }
        else if (msg.States[i].eventState == 5 || msg.States[i].eventState == 6){
            marker_tmp.color.r = 0.0;
            marker_tmp.color.g = 0.0;
            marker_tmp.color.b = 1.0;            
        }
        else{
            marker_tmp.color.r = 1.0;
            marker_tmp.color.g = 1.0;
            marker_tmp.color.b = 1.0;            
        }
        spat_marker_array.markers.push_back(marker_tmp);
    }
    return;
}


void V2X_viz::mission1Callback(const v2x_msgs::Mission1& msg){    
    ROS_INFO("Mission1 callback");
    mission1_flag = true;
    mission1_marker_array.markers.clear();
    for(int i=0; i<msg.States.size(); i++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ;
        marker_tmp.id = 65000+i;
        marker_tmp.ns = "mission1";
        marker_tmp.text = std::to_string(msg.States[i].route_node_index);
        marker_tmp.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        marker_tmp.action = visualization_msgs::Marker::ADD;
        marker_tmp.pose.position.x = msg.States[i].route_node_pos_lat;
        marker_tmp.pose.position.y = msg.States[i].route_node_pos_lon;
        marker_tmp.pose.position.z = 0;
        marker_tmp.color.r = 1.0;
        marker_tmp.color.g = 1.0;
        marker_tmp.color.b = 1.0;

        marker_tmp.color.a = 1.0;
        marker_tmp.scale.z = 1.0;
        marker_tmp.lifetime = ros::Duration(1.0);


        if (msg.States[i].route_node_type == 1){
            marker_tmp.text = "start : "+std::to_string(msg.States[i].route_node_index);
        }
        else if (msg.States[i].route_node_type == 2){
            marker_tmp.text = "End : "+std::to_string(msg.States[i].route_node_index);
        }
        mission1_marker_array.markers.push_back(marker_tmp);

        marker_tmp.id = 65100+i;
        marker_tmp.type = visualization_msgs::Marker::SPHERE;
        if (msg.States[i].route_node_type == 1){
            marker_tmp.color.g = 0.0;
            marker_tmp.color.b = 0.0;
        }
        else if (msg.States[i].route_node_type == 2){
            marker_tmp.color.r = 0.0;
            marker_tmp.color.g = 0.0; 
        }
        
        marker_tmp.scale.x = 1;
        marker_tmp.scale.y = 1;

        marker_tmp.color.a = 0.3;
        mission1_marker_array.markers.push_back(marker_tmp);
    }
    return;
}

void V2X_viz::mission2Callback(const v2x_msgs::Mission2& msg){
    ROS_INFO("Mission2 callback");
    mission2_flag = true;
    mission2_marker_array.markers.clear();

    for(int i=0; i<msg.item_count; i++){
        visualization_msgs::Marker marker_tmp;
        marker_tmp.header.stamp = ros::Time::now();
        marker_tmp.header.frame_id = "map" ;
        marker_tmp.id = 66100+i;
        marker_tmp.ns = "mission2";

        if(msg.States[i].item_type== 1){
            marker_tmp.text = "ID : " + std::to_string(msg.States[i].item_id) + " , " + std::to_string(msg.States[i].score);
            marker_tmp.color.b = 1.0; // lap time plus ( good for us )
        }
        else if (msg.States[i].item_type == 2){
            marker_tmp.text = "ID : " + std::to_string(msg.States[i].item_id) + " , " + std::to_string(msg.States[i].score);
            marker_tmp.color.r = 1.0; // lap time plus ( bad for us )
        }
        else if (msg.States[i].item_type == 3 ){
            marker_tmp.text = "ID : " + std::to_string(msg.States[i].item_id) + " , " + std::to_string(msg.States[i].speed);
            marker_tmp.color.g = 1.0; // boost item ( good for us )
        }

        marker_tmp.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
        marker_tmp.action = visualization_msgs::Marker::ADD;
        marker_tmp.pose.position.x = msg.States[i].pos_lat;
        marker_tmp.pose.position.y = msg.States[i].pos_long;
        marker_tmp.pose.position.z = 5;
        
        marker_tmp.color.a = 1.0;
        marker_tmp.scale.z = 1.0;
        marker_tmp.lifetime = ros::Duration(0.1);
        mission2_marker_array.markers.push_back(marker_tmp);

        marker_tmp.id = 66200+i;
        marker_tmp.type = visualization_msgs::Marker::SPHERE;

        marker_tmp.color.r = 1.0;
        marker_tmp.color.g = 1.0;
        marker_tmp.color.b = 1.0;

        marker_tmp.scale.x = msg.States[i].extend;
        marker_tmp.scale.y = msg.States[i].extend;
        marker_tmp.scale.z = msg.States[i].extend;
        marker_tmp.color.a = 0.3;
        mission2_marker_array.markers.push_back(marker_tmp);
    }
    return;
}

int main (int argc, char** argv)
{
    ros::init(argc, argv, "viz_pub");
    ros::NodeHandle nh, nhlocal;
    
    V2X_viz V2X_viz(nh);

    ros::spin();

    return 0;
}
