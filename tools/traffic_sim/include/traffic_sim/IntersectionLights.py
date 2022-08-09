import numpy as np
import sys
import os
import math
# from heapq import heappush, heappop
# from traffic_sim.utils import dist2d, dist3d
from traffic_sim.trafficLight import TrafficLight
import rospy
from visualization_msgs.msg import MarkerArray, Marker
from hmcl_msgs.msg import TrafficlightArray, Trafficlight

class Intersection:
    def __init__(self,n_ways = 4):
            
        # x, y, heading (heading relate to map north)
        self.intersection_pose = np.array([-151.9, 75.2, 5.43])     
        # in metre
        self.center_to_trfficlight = 7
        # self.distance_between_lights = 0.5
        # self.stopline_pose = np.array([0.0, 0.0])
        # self.crosswork_pose = np.array([0.0, 0.0])
        
        self.north_light_sequence = np.array([# north south straight start 
                                            [0,     1,   1],                                        
                                            [0,     0.5,   1],                                        
                                            [1,     0,   1],
                                            [0.5,   0,   1],
                                            # east west straight start                                         
                                            [0,     0,   1],
                                            [0,     0,   1],                                        
                                            [0,     0,   1],                                        
                                            [0,     0,   1]])        

        self.east_light_sequence = np.array([# north south straight start
                                            [0,     0,   1],                                        
                                            [0,     0,   1],                                        
                                            [0,     0,   1],
                                            [0,     0,   1], 
                                            # east west straight start                                           
                                            [0,     1,   1],                                        
                                            [0,     0.5, 1],                                        
                                            [1,     0,   1],
                                            [0.5,   0,   1]])        

        self.south_light_sequence = self.north_light_sequence     
        self.west_light_sequence = self.east_light_sequence 

        self.scenario_tic_periods = np.array([2,1,2,1,2,1,2,1])*1
        assert len(self.north_light_sequence) == len(self.east_light_sequence), "different number of light sequcnes are not allowed atm"
        assert len(self.north_light_sequence) == len(self.scenario_tic_periods), "different number of light sequcnes and tic periods"

                # 4 ways intersetion , [north , east, south, west]
        if n_ways == 4:            
            self.trafficlights = [TrafficLight(self.north_light_sequence), TrafficLight(self.east_light_sequence), TrafficLight(self.south_light_sequence), TrafficLight(self.west_light_sequence)]
            self.trafficlights[0].set_light_sequence(self.north_light_sequence, reset= True)            
            self.trafficlights[1].set_light_sequence(self.east_light_sequence, reset= True)
            self.trafficlights[2].set_light_sequence(self.south_light_sequence, reset= True)
            self.trafficlights[3].set_light_sequence(self.west_light_sequence, reset= True)
            for trafficlights in self.trafficlights:
                trafficlights.set_light_period_tic(self.scenario_tic_periods)                        
            self.set_trafficlights_pose()
            print("set pose complete")

        elif n_ways == 3:
            # 3 ways not implemented yet
            assert 1==2, "Not implemented yet"

        self.current_scenario_idx = 0                
        self.tic = 0
        self.intersection_traffic_status = None 
        self.remaining_tic = None 

    def set_trafficlights_pose(self):        
        for i in range(len(self.trafficlights)):
            x_tmp = 0
            y_tmp = self.center_to_trfficlight
            x_tmp2 = math.cos(np.pi/2-i*np.pi/2+self.intersection_pose[2])*x_tmp - math.sin(np.pi/2-i*np.pi/2+self.intersection_pose[2])*y_tmp
            y_tmp2 = math.sin(np.pi/2-i*np.pi/2+self.intersection_pose[2])*x_tmp + math.cos(np.pi/2-i*np.pi/2+self.intersection_pose[2])*y_tmp
            pose_tmp = np.array([self.intersection_pose[0] + x_tmp2, self.intersection_pose[1] + y_tmp2, -i*np.pi/2+self.intersection_pose[2]])        
            self.trafficlights[i].set_pose(pose_tmp)

    def reset_sequence_and_tic(self):
        for trafficlights in self.trafficlights:
                trafficlights.reset_sequence_tic()

    def reset_tic(self):
        self.tic = 0

    def get_lights_status(self):
        self.intersection_traffic_status = []
        for trafficlights in self.trafficlights:
                self.intersection_traffic_status.append(trafficlights.get_lights_status())                    
        return self.intersection_traffic_status

    def get_remaining_tic(self):                
        return self.scenario_tic_periods[self.current_scenario_idx] - self.tic


    def update_tic(self):
        if self.tic >= self.scenario_tic_periods[self.current_scenario_idx]:
            self.tic = 0
            for trafficlights in self.trafficlights:
                trafficlights.update_tic()            
        self.tic+=1
    
            


    def get_intersection_msg(self):
        tf_array_msg = TrafficlightArray()
        
        tf_array_msg.header.frame_id = "map"
        tf_array_msg.header.stamp = rospy.Time.now()

        for i in range(len(self.trafficlights)):               
            tf_tmp = self.trafficlights[i].get_traffic_msg()
            tf_array_msg.trafficlights.append(tf_tmp)

        return tf_array_msg
            


    def get_trafficlight_markers(self):
        markers = MarkerArray()
        count = 0
        for i in range(len(self.trafficlights)):
                count+=1
                marker_tmp = self.trafficlights[i].get_trafficlight_markers(ns = str(count))       
                         
                for i in range(len(marker_tmp.markers)):                    
                    markers.markers.append(marker_tmp.markers.pop())    
                # if count > 1:
                #     return markers
        return markers


# Intersection4way = Intersection()
# for i in range(20):
#     Intersection4way.update_tic()
#     print(Intersection4way.get_lights_status())
