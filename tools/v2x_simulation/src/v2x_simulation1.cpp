
//   Copyright (c) 2022 Ulsan National Institute of Science and Technology (UNIST)
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

//   Authour : Hojin Lee, hojinlee@unist.ac.kr


#include "v2x_simulation1.h"
using namespace std;

V2xSimulation1::V2xSimulation1(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p):  
  nh_(nh),nh_p_(nh_p)
{
  nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
  nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
  // nh_p_.param<double>("map_origin_att", origin_att, 0.0);
  v2xPub = nh_.advertise<v2x_msgs::Mission1>("/Mission1", 2);  
  v2xVizPub = nh_.advertise<visualization_msgs::MarkerArray>("/Mission1_Viz", 2);  

  lanelet::GPSPoint originGps{origin_lat, origin_lon, 0.};    
  projector = new lanelet::projection::UtmProjector(lanelet::Origin{originGps});     
  point_sub = nh_.subscribe("move_base_simple/goal", 1, &V2xSimulation1::callbackGetGoalPose, this);
  
  
  

  boost::thread simulation_loop(&V2xSimulation1::simulationCallback,this); 
   
  add_mission_waypoints();
  

  f = boost::bind(&V2xSimulation1::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

V2xSimulation1::~V2xSimulation1()
{}


void V2xSimulation1::add_mission_waypoints(){
 

  std::vector<double> wp_lat, wp_lon, score;

  wp_lon.push_back(128.4013386);
  wp_lon.push_back(128.4001426);
  wp_lon.push_back(128.3938531);
  wp_lon.push_back(128.3919018);
  wp_lon.push_back(128.3948077);
  wp_lon.push_back(128.3970079);
  wp_lon.push_back(128.3970374);
  wp_lon.push_back(128.3970722);
  wp_lon.push_back(128.3989831);
  wp_lon.push_back(128.3979354);
  wp_lon.push_back(128.3959423);
  wp_lon.push_back(128.3958819);
  wp_lon.push_back(128.3981997);



  wp_lat.push_back(35.6491704);
  wp_lat.push_back(35.6501853);
  wp_lat.push_back(35.6549743);
  wp_lat.push_back(35.6564015);
  wp_lat.push_back(35.6552222);
  wp_lat.push_back(35.6531639);
  wp_lat.push_back(35.6531859);
  wp_lat.push_back(35.6532066);
  wp_lat.push_back(35.6512138);
  wp_lat.push_back(35.6522498);
  wp_lat.push_back(35.6542104);
  wp_lat.push_back(35.6541667);
  wp_lat.push_back(35.6522011);
  
  score.push_back(5.0);
  score.push_back(5.0);
  score.push_back(5.0);
  score.push_back(10.0);
  score.push_back(5.0);
  score.push_back(10.0);
  score.push_back(8.0);
  score.push_back(5.0);
  score.push_back(-5.0);
  score.push_back(-5.0);
  score.push_back(-5.0);
  score.push_back(-10.0);
  score.push_back(0.0);



  mission_wp_viz.markers.clear();    
  for(int i=0; i< wp_lon.size(); i++){
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time();
        marker.ns = "waypoint";
        marker.id = i;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::ADD;
          lanelet::GPSPoint tmp_gnss{wp_lat[i], wp_lon[i], 0.};
        lanelet::BasicPoint3d converted_point = projector->forward(tmp_gnss);        
        marker.pose.position.x = converted_point.x();
        marker.pose.position.y = converted_point.y();
        marker.pose.position.z = 0.0;        
        marker.pose.orientation.w = 1.0;        
        marker.scale.x = 2;
        marker.scale.y = 2;
        marker.scale.z = 2;
        marker.color.a = 0.5; // Don't forget to set the alpha!        
        if (score[i] > 0){
            marker.color.r = 0.0;
            marker.color.g = 1;
            marker.color.b = 0.0;
        }else if(score[i] < 0){
            marker.color.r = 1.0;
            marker.color.g = 0.0;
            marker.color.b = 0.0;
        }
        else{
            marker.color.r = 0.0;
            marker.color.g = 0.0;
            marker.color.b = 1.0;
        }                    
        mission_wp_viz.markers.push_back(marker);        
    }
  
        


}

void V2xSimulation1::constructViz(){
  mission_wp_viz.markers.clear();    
  for(int i=0; i< mission_waypoints.size(); i++){
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time();
        marker.ns = "waypoint";
        marker.id = i;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::ADD;
        lanelet::GPSPoint tmp_gnss{mission_waypoints[i].route_node_pos_lat, mission_waypoints[i].route_node_pos_lon, 0.};
        lanelet::BasicPoint3d converted_point = projector->forward(tmp_gnss);        
        marker.pose.position.x = converted_point.x();
        marker.pose.position.y = converted_point.y();
        marker.pose.position.z = 0.0;        
        marker.pose.orientation.w = 1.0;        
        marker.scale.x = 2;
        marker.scale.y = 2;
        marker.scale.z = 2;
        marker.color.a = 0.5; // Don't forget to set the alpha!        
        marker.color.r = 0.0;
        marker.color.g = 1;
        marker.color.b = 0.0;
        mission_wp_viz.markers.push_back(marker);        
    }
}


void V2xSimulation1::insertWaypoint(const geometry_msgs::PoseStamped &msg){

    v2x_msgs::Mission1data tmp_data;    
    if(waypoint_select == 0){
      // Normal Node     
        tmp_data.route_node_type = 0;
      
    }else if(waypoint_select == 1){
      // Start Node
        tmp_data.route_node_type = 1;
    }
    else if(waypoint_select == 2){
      // Goal Node
      tmp_data.route_node_type = 2;
    }

    lanelet::BasicPoint3d tmp_point{msg.pose.position.x,msg.pose.position.y,0.0};
    lanelet::GPSPoint tmp_gps =  projector->reverse(tmp_point);
    tmp_data.route_node_pos_lat = tmp_gps.lat;
    tmp_data.route_node_pos_lon = tmp_gps.lon;
    mission_waypoints.push_back(tmp_data);

  for(int i=0; i < mission_waypoints.size(); i++){
    mission_waypoints[i].route_node_index = i;
  }

  return;
}

void V2xSimulation1::deleteWaypoint(const geometry_msgs::PoseStamped &msg){
  
  for(int i=0; i< mission_waypoints.size(); i++)
  {
    lanelet::GPSPoint tmp_gnss{mission_waypoints[i].route_node_pos_lat, mission_waypoints[i].route_node_pos_lon, 0.};
    lanelet::BasicPoint3d converted_point = projector->forward(tmp_gnss);        
    
    double dist_tmp = sqrt(pow((msg.pose.position.x-converted_point.x()),2)+pow((msg.pose.position.y-converted_point.y()),2));
    if(dist_tmp < 2.0){
      mission_waypoints.erase(mission_waypoints.begin()+i);      
      break; // we only delete one single point
    }
    
  }
  return;
}



void V2xSimulation1::callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg){
    if(waypoint_edit == 0 ){
      insertWaypoint(*msg);
    }
    else{
      deleteWaypoint(*msg);
    }

}

void V2xSimulation1::simulationCallback(){
    ros::Rate loop_rate(1); // rate  
      while (ros::ok()){
              v2x_msgs::Mission1 v2x_msgs_;
              v2x_msgs_.header.stamp = ros::Time::now();
              v2x_msgs_.mission_id = 3;
              v2x_msgs_.status = 1;
              v2x_msgs_.event_count = 0;
              v2x_msgs_.route_count= mission_waypoints.size();
              for(int i=0; i < mission_waypoints.size(); i++){
                v2x_msgs_.States.push_back(mission_waypoints[i]);                
              }
               v2xPub.publish(v2x_msgs_);
               
               constructViz();
               v2xVizPub.publish(mission_wp_viz);
            loop_rate.sleep();
      }
      ROS_INFO("simulation end");
}



void V2xSimulation1::dyn_callback(v2x_simulation::test1Config &config, uint32_t level)
{
   Mission_status    =  config.Mission_Status;
   waypoint_select   = config.Waypoint_Select;
   waypoint_edit     = config.Waypoint_editting;
  //  boost_duration = config.Boost_duration;
  
}




int main (int argc, char** argv)
{
  ros::init(argc, argv, "V2xSimulation1");
  
  

  ros::NodeHandle nh_;
  ros::NodeHandle nh_p("~");
  V2xSimulation1 V2xSimulation1_(nh_,nh_p);


    ros::spin();



  return 0;

}
 