
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

// #include <sstream>
// #include <string>
// #include <list>
// #include <iostream>
// #include <fstream>
// #include <queue>
// #include <boost/filesystem.hpp>
// #include <boost/thread/thread.hpp>

// #include <ros/ros.h>
// #include <ros/time.h>
// #include <std_msgs/Float64.h>
// #include <sensor_msgs/NavSatFix.h>

// #include <nav_msgs/Odometry.h>
// #include <geometry_msgs/PoseStamped.h>
// #include <geometry_msgs/Point.h>
// #include <geometry_msgs/PoseWithCovarianceStamped.h>
// #include <visualization_msgs/MarkerArray.h>
// #include <GeographicLib/LocalCartesian.hpp>
// #include <eigen3/Eigen/Geometry>

// #include <tf/tf.h>
// #include <tf/transform_broadcaster.h>
// #include <tf/transform_datatypes.h>
// #include <tf/transform_listener.h>

// #include <vector>

// #include <lanelet2_core/primitives/Lanelet.h>
// #include <lanelet2_io/Io.h>
// #include <lanelet2_io/io_handlers/Factory.h>
// #include <lanelet2_io/io_handlers/Writer.h>
// #include <lanelet2_projection/UTM.h>
// #include <lanelet2_routing/Route.h>
// #include <lanelet2_routing/RoutingCost.h>
// #include <lanelet2_routing/RoutingGraph.h>
// #include <lanelet2_routing/RoutingGraphContainer.h>
// #include <lanelet2_traffic_rules/TrafficRulesFactory.h>
// #include <tools/amathutils.hpp>


#define PI 3.14159265358979323846264338

namespace planner{

class RoutePlanner 
{
  
private:
    int tmp;
    
 
public:
RoutePlanner(); 
~RoutePlanner();


void load_map();
// void constrcut_viz();
// void viz_pub(const ros::TimerEvent& time);

// void get_distance_to_stop_line(poseition pose)


// void LocalCallback(geometry_msgs::PoseStampedConstPtr local_pose);


};

}


