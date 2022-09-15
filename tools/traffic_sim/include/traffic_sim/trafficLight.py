from this import d
import numpy as np
import sys
import os
import math


import rospy
from visualization_msgs.msg import MarkerArray, Marker
from traffic_sim.utils import euler_to_quaternion, unit_quat
from hmcl_msgs.msg import Trafficlight, TrafficlightBulb

class TrafficLight:
    def __init__(self,light_sequence):
        
        # x, y, heading (heading is face to straight lane direction)
        self.trafficlight_pose = np.array([0.0, 0.0, 0.0])
        self.distance_between_lights = 2
        self.offset_to_right = 2.5
        self.stopline_pose = np.array([0.0, 0.0])
        self.crosswork_pose = np.array([0.0, 0.0])        
        # self.light_status = [self.left_status, self.straight_status, self.right_status]                
        self.light_status = [0, 0, 0]                
        self.light_sequence = light_sequence 
        # np.array([[0,     1,   1],                                        
        #                                 [1,     1,   1],
        #                                 [0.5, 0.5,   1],                                        
        #                                 [0,     0,   1]])        
        self.current_status_idx = 0
        self.ligth_tic_period = np.ones(len(self.light_sequence))*4
        self.ligth_tic_period[2] = 2
        self.tic = 0
        for i in range(len(self.light_status)):
            self.light_status[i] = self.light_sequence[self.current_status_idx][i]    
        
    def set_pose(self,pose):
        self.trafficlight_pose = pose
        
    def reset_sequence_tic(self):
        self.reset_sequence()
        self.reset_tic()

    def reset_sequence(self):
        self.current_status_idx = 0

    def reset_tic(self):
        self.tic = 0

    def set_light_sequence(self,new_sequence,reset= True):
        self.light_sequence = new_sequence       
        if reset:
            self.reset_sequence() 
            self.reset_tic()
        
    def get_lights_status(self):
        return self.light_status

    def get_remaining_tic(self):        
        return self.ligth_tic_period[self.current_status_idx] - self.tic

    def set_light_period_tic(self,ligth_tic_period):
        self.ligth_tic_period = ligth_tic_period

    def light_update(self):
        self.current_status_idx+=1
        if self.current_status_idx >= len(self.light_sequence):
            self.current_status_idx = 0
        for i in range(len(self.light_status)):
            self.light_status[i] = self.light_sequence[self.current_status_idx][i]    
        
        
    def update_tic(self):
        
        if self.tic >= self.ligth_tic_period[self.current_status_idx]:
            self.tic = 0
            self.light_update()
        self.tic+=1
    
    def get_traffic_msg(self):
        tf_msg = Trafficlight()        
        left_bulb = TrafficlightBulb()
        straight_bulb = TrafficlightBulb()
        right_bulb = TrafficlightBulb()
        left_bulb.light_status = self.light_status[0]        
        straight_bulb.light_status = self.light_status[1]        
        right_bulb.light_status = self.light_status[2]
        tf_msg.header.frame_id = "map"
        tf_msg.header.stamp = rospy.Time.now()
        tf_msg.pose.position.x = self.trafficlight_pose[0]
        tf_msg.pose.position.y = self.trafficlight_pose[1]
        tf_msg.pose.position.z = 3.0
        quat_tmp  =  unit_quat(euler_to_quaternion(0,0,self.trafficlight_pose[2]))            
        tf_msg.pose.orientation.w = quat_tmp[0]
        tf_msg.pose.orientation.x = quat_tmp[1]
        tf_msg.pose.orientation.y = quat_tmp[2]
        tf_msg.pose.orientation.z = quat_tmp[3]
        tf_msg.left_light = left_bulb
        tf_msg.straight_light = straight_bulb
        tf_msg.right_light = right_bulb
        tf_msg.valid_stop_line = True
        tf_msg.stop_line = tf_msg.pose
        return tf_msg



    def get_trafficlight_markers(self,ns):
        tf_marker = Marker()
        tf_markers = MarkerArray()
        for i in range(len(self.light_status)):        
            tf_marker = Marker()           
            x_tmp = 0
            y_tmp = 0
            if i == 0 :
                # - math.sin(np.pi/2-i*np.pi/2+self.intersection_pose[2])*y_tmp
                # + math.cos(np.pi/2-i*np.pi/2+self.intersection_pose[2])*y_tmp                
                x_tmp = -math.sin(self.trafficlight_pose[2])*self.distance_between_lights
                y_tmp = math.cos(self.trafficlight_pose[2])*self.distance_between_lights                     
            elif i == 2:
                x_tmp = -math.sin(self.trafficlight_pose[2])*self.distance_between_lights*-1
                y_tmp = math.cos(self.trafficlight_pose[2])*self.distance_between_lights*-1                     
            xoffset = -math.sin(self.trafficlight_pose[2])*self.offset_to_right*-1
            yoffset = math.cos(self.trafficlight_pose[2])*self.offset_to_right*-1                     

            tf_marker.pose.position.x = self.trafficlight_pose[0] + x_tmp + xoffset
            tf_marker.pose.position.y = self.trafficlight_pose[1] + y_tmp + yoffset
            tf_marker.pose.position.z = 2.0
            yaw = self.trafficlight_pose[2]            
            if i== 0:
                yaw = self.trafficlight_pose[2] + np.pi/2
            elif i== 2:
                yaw = self.trafficlight_pose[2] - np.pi/2
            quat_tmp  =  unit_quat(euler_to_quaternion(0,0,yaw))
            
            tf_marker.pose.orientation.w = quat_tmp[0]
            tf_marker.pose.orientation.x = quat_tmp[1]
            tf_marker.pose.orientation.y = quat_tmp[2]
            tf_marker.pose.orientation.z = quat_tmp[3]
            
            tf_marker.id = i*int(ns)
            tf_marker.ns = ns+"_light"            
            # tf_marker.lifetime = rospy.Duration(1.0)
            tf_marker.header.frame_id = "map"
            tf_marker.header.stamp = rospy.Time.now()
            tf_marker.type = 0    #  SPHERE
            tf_marker.scale.x = 1
            tf_marker.scale.y = 0.5
            tf_marker.scale.z = 0.5
            tf_marker.color.a = 1.0
            if self.light_status[i] > 0.5:            
                tf_marker.color.r = 0
                tf_marker.color.g = 1
            elif self.light_status[i] < 0.5:
                tf_marker.color.r = 1
                tf_marker.color.g = 0 
            else:
                tf_marker.color.r = 1
                tf_marker.color.g = 1 
            tf_marker.color.b = 0.0
            tf_markers.markers.append(tf_marker)        
        return tf_markers


     
# t1 = TrafficLight()
# for i in range(20):
#     t1.update_tic()
#     print(t1.get_lights_status())
    
    
