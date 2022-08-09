#!/usr/bin/env python
from this import d
from cv2 import fastNlMeansDenoisingColored
import rospy

""" ROS node for path plan.
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.
"""

import json
import time
import threading
import numpy as np
import math 
import sys
from std_msgs.msg import Bool, Empty, Float64
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped, PoseWithCovarianceStamped 
from visualization_msgs.msg import MarkerArray, Marker
from hmcl_msgs.msg import Trafficlight, TrafficlightArray
# from hmcl_msgs import Lane
from traffic_sim.IntersectionLights import Intersection


def clamp(n, minn, maxn):
    return max(min(maxn, n), minn)

class TrafficSim:
    def __init__(self):
        
        
        self.intersection = Intersection()    
        self.intersection.reset_sequence_and_tic()
        self.tf_markers = MarkerArray()
        self.tf_msg = TrafficlightArray()
        # Thread for sim
        self.sim_thread = threading.Thread()        
        
        self.odom = Odometry()        
        self.debug_msg = PoseStamped()
        self.obs_pose = PoseWithCovarianceStamped()
        
        # Real world setup
        odom_topic = "/ground_truth/state"
        vehicle_status_topic = "/chassisState"                  
        goal_topic = "/move_base_simple/goal"                
        obs_topic = "/initialpose"       
        # map_topic = "/traversability_estimation/terrain_map"
        map_topic = "/traversability_estimation/global_map"        
        status_topic = "/planner_status"
        self.layer_name = "terrain_traversability"
        self.elevation_layer_name = "elevation"
        traffic_lights_topic = "/traffic_lights"

        # Publishers        
        self.traffic_lights_mareker_pub = rospy.Publisher("/traffic_lights_marker", MarkerArray, queue_size=2)                               
        self.debug_pub = rospy.Publisher("traffic_sim_debug", PoseStamped, queue_size=2)    
        self.status_pub = rospy.Publisher(status_topic, Bool, queue_size=2)    
        self.trafficlights_pub = rospy.Publisher(traffic_lights_topic, TrafficlightArray, queue_size=2)
        # Subscribers        
        self.trafficlight_handler = rospy.Timer(rospy.Duration(1), self.traffic_timer_callback)         
        # self.goal_sub = rospy.Subscriber(goal_topic, PoseStamped, self.goal_callback)        
        
        

        rate = rospy.Rate(10)     
        while not rospy.is_shutdown():
            # Publish if MPC is busy with a current trajectory
            msg = Bool()
            msg.data = True
            self.status_pub.publish(msg)
            
            
            
            rate.sleep()


   
    def traffic_timer_callback(self,timer):
        self.intersection.update_tic()
        self.tf_markers = self.intersection.get_trafficlight_markers()
        self.traffic_lights_mareker_pub.publish(self.tf_markers)
        tf_msg = self.intersection.get_intersection_msg()
        
            
        self.trafficlights_pub.publish(tf_msg)
          
        

     
###################################################################################

def main():
    rospy.init_node("traffic_sim")
    print("start node")
    TrafficSim()
  

if __name__ == "__main__":
    main()




 
    

        
        