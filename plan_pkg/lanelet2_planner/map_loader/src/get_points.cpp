#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include<iostream>

class Points{

  private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher pub;
    visualization_msgs::MarkerArray markers;
    std::vector<std::pair<float,float>> checkpoints;
    int count=0;

  public:
    Points(){
      sub = n.subscribe("/move_base_simple/goal", 1, &Points::chatterCallback,this);
      pub = n.advertise<visualization_msgs::MarkerArray>("/checkpoints", 1, true);
      markers.markers.clear();
    }
    visualization_msgs::MarkerArray getMarkers(){
      return markers;
    }

    void addMarkers(visualization_msgs::Marker marker){
      markers.markers.push_back(marker);
    }

    visualization_msgs::Marker points2marker(float x, float y){
      visualization_msgs::Marker marker_tmp;
      marker_tmp.header.stamp = ros::Time::now();
      marker_tmp.header.frame_id = "map" ; //global_lane_array.header.frame_id;
      marker_tmp.id = count;
      marker_tmp.ns = "checkpoints";
      marker_tmp.type = visualization_msgs::Marker::SPHERE;
      marker_tmp.action = visualization_msgs::Marker::ADD;                  
      marker_tmp.pose.position.x = x;
      marker_tmp.pose.position.y = y;
      marker_tmp.pose.position.z = 0;
      marker_tmp.color.r = 1.0;
      marker_tmp.color.g = 0.0;
      marker_tmp.color.b = 0.0;
      marker_tmp.color.a = 1.0;
      marker_tmp.lifetime = ros::Duration();
      marker_tmp.scale.x = 1.0;
      marker_tmp.scale.y = 1.0;
      marker_tmp.scale.z = 1.0;                  
      count++;        
      return marker_tmp;
    }
  
    void chatterCallback(const geometry_msgs::PoseStamped& msg)
    {
      checkpoints.push_back({msg.pose.position.x,msg.pose.position.y});
      for(int i=0;i<checkpoints.size();i++){
        std::cout<<"{"<<checkpoints[i].first<<","<<checkpoints[i].second<<"},";
      }
      std::cout<<""<<std::endl;
      ROS_INFO("{%f,%f},",msg.pose.position.x,msg.pose.position.y);
      
      addMarkers(points2marker(msg.pose.position.x,msg.pose.position.y));
      pub.publish(markers);
    }

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "get_points");

  Points points;
  ros::spin();

  return 0;
}
