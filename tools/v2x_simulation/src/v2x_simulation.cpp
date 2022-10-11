
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


#include "v2x_simulation.h"



using namespace std;

V2xSimulation::V2xSimulation(const ros::NodeHandle& nh,const ros::NodeHandle& nh_p):  
  nh_(nh),nh_p_(nh_p)
{
  nh_p_.param<double>("map_origin_lat", origin_lat, 0.0);
  nh_p_.param<double>("map_origin_lon", origin_lon, 0.0);
  // nh_p_.param<double>("map_origin_att", origin_att, 0.0);
  v2xPub = nh_.advertise<v2x_msgs::Mission2>("/Mission2", 2);  
  v2xVizPub = nh_.advertise<visualization_msgs::MarkerArray>("/Mission2_Viz", 2);  

  lanelet::GPSPoint originGps{origin_lat, origin_lon, 0.};    
  projector = new lanelet::projection::UtmProjector(lanelet::Origin{originGps});     
  point_sub = nh_.subscribe("move_base_simple/goal", 1, &V2xSimulation::callbackGetGoalPose, this);
  
  
  

  boost::thread simulation_loop(&V2xSimulation::simulationCallback,this); 
   
  

  f = boost::bind(&V2xSimulation::dyn_callback,this, _1, _2);
	srv.setCallback(f);
}

V2xSimulation::~V2xSimulation()
{}

void V2xSimulation::constructViz(){
  mission_wp_viz.markers.clear();    
  for(int i=0; i< mission_waypoints.size(); i++){
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time();
        marker.ns = "waypoint";
        marker.id = i;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::ADD;
        lanelet::GPSPoint tmp_gnss{mission_waypoints[i].pos_lat, mission_waypoints[i].pos_long, 0.};
        lanelet::BasicPoint3d converted_point = projector->forward(tmp_gnss);        
        marker.pose.position.x = converted_point.x();
        marker.pose.position.y = converted_point.y();
        marker.pose.position.z = 0.0;        
        marker.pose.orientation.w = 1.0;        
        marker.scale.x = 2;
        marker.scale.y = 2;
        marker.scale.z = 2;
        marker.color.a = 0.5; // Don't forget to set the alpha!        
        if (mission_waypoints[i].score < 0){
            marker.color.r = 0.0;
            marker.color.g = 1;
            marker.color.b = 0.0;
        }else if(mission_waypoints[i].score > 0){
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

void V2xSimulation::insertWaypoint(const geometry_msgs::PoseStamped &msg){

    v2x_msgs::Mission2data tmp_data;    
    if(waypoint_select == 0){
      // Good item         
        tmp_data.item_type = 1;
        tmp_data.speed = 80;
        tmp_data.score = -20;
        tmp_data.duration = 0.0;
      
    }else if(waypoint_select == 1){
      // Bad item
        tmp_data.item_type = 2;
        tmp_data.speed = 80;
        tmp_data.score = 20;
        tmp_data.duration = 0.0;
    }
    else if(waypoint_select == 2){
      // Boost item
        tmp_data.item_type = 3;
        tmp_data.speed = 100; 
        tmp_data.score = 0;
        tmp_data.duration = boost_duration;
    }

    lanelet::BasicPoint3d tmp_point{msg.pose.position.x,msg.pose.position.y,0.0};
    lanelet::GPSPoint tmp_gps =  projector->reverse(tmp_point);
    tmp_data.pos_lat = tmp_gps.lat;
    tmp_data.pos_long = tmp_gps.lon;
    tmp_data.extend = 2.0;

  mission_waypoints.push_back(tmp_data);

  for(int i=0; i < mission_waypoints.size(); i++){
    mission_waypoints[i].item_id = i;
  }

  return;
}

void V2xSimulation::deleteWaypoint(const geometry_msgs::PoseStamped &msg){
  
  for(int i=0; i< mission_waypoints.size(); i++)
  {
    lanelet::GPSPoint tmp_gnss{mission_waypoints[i].pos_lat, mission_waypoints[i].pos_long, 0.};
    lanelet::BasicPoint3d converted_point = projector->forward(tmp_gnss);        
    
    double dist_tmp = sqrt(pow((msg.pose.position.x-converted_point.x()),2)+pow((msg.pose.position.y-converted_point.y()),2));
    if(dist_tmp < 2.0){
      mission_waypoints.erase(mission_waypoints.begin()+i);      
      break; // we only delete one single point
    }
    
  }
  return;
}



void V2xSimulation::callbackGetGoalPose(const geometry_msgs::PoseStampedConstPtr &msg){
    if(waypoint_edit == 0 ){
      insertWaypoint(*msg);
    }
    else{
      deleteWaypoint(*msg);
    }

}

void V2xSimulation::simulationCallback(){
    ros::Rate loop_rate(1); // rate  
      while (ros::ok()){
               v2x_msgs::Mission2 v2x_msgs_;
               v2x_msgs_.header.stamp = ros::Time::now();
               v2x_msgs_.mission_status = Mission_status;
               v2x_msgs_.item_count = mission_waypoints.size();
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



void V2xSimulation::dyn_callback(v2x_simulation::testConfig &config, uint32_t level)
{
   Mission_status    =  config.Mission_Status;
   waypoint_select   = config.Waypoint_Select;
   waypoint_edit     = config.Waypoint_editting;
   boost_duration = config.Boost_duration;
  
}




int main (int argc, char** argv)
{
  ros::init(argc, argv, "V2xSimulation");
  
  

  ros::NodeHandle nh_;
  ros::NodeHandle nh_p("~");
  V2xSimulation v2xSimulation_(nh_,nh_p);


    ros::spin();



  return 0;

}
 