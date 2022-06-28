#!/usr/bin/env python
try:
  from jsk_rviz_plugins.msg import *
except:
  import roslib;roslib.load_manifest("jsk_rviz_plugins")
  from jsk_rviz_plugins.msg import *

from sensor_msgs.msg import NavSatFix 

from std_msgs.msg import ColorRGBA, Float32, String, Bool
from hmcl_msgs.msg import VehicleStatus
import rospy
import math




class hmclGUI():
  def __init__(self):
    rospy.init_node("hmcl_gui")
    self.fix_pub = rospy.Publisher("/fix_gui", OverlayText, queue_size=2)
    self.gear_pub = rospy.Publisher("/gear_gui", OverlayText, queue_size=2)
    self.lc_pub = rospy.Publisher("/lc_gui", OverlayText, queue_size=2)
    # self.mission_status_pub = rospy.Publisher("/mission_gui", OverlayText, queue_size=1)
    # self.driving_status_pub = rospy.Publisher("/driving_gui", OverlayText, queue_size=1)
    
    self.gnss_sub = rospy.Subscriber("/fix", NavSatFix, self.gnss_callback)
    self.driving_sub =  rospy.Subscriber("/driving_state", String, self.driving_callback)
    self.mission_sub =  rospy.Subscriber("/mission_state", String, self.mission_callback)
    self.vehicle_sub =  rospy.Subscriber("/vehicle_status", VehicleStatus, self.vehicleStatusCallback)

    self.left_change_sub =  rospy.Subscriber("/left_lanechange", Bool, self.left_lc_callback)
    self.right_change_sub =  rospy.Subscriber("/right_lanechange", Bool, self.right_lc_callback)
    

    self.left_lc = False
    self.right_lc = False
    self.timerSub = rospy.Timer(rospy.Duration(0.1), self.guiTimer)
    self.Localization_state = None
    self.Ctrl_state = None
    self.CAN_state = None
    self.vehicle_state = None
    self.fix_msg = NavSatFix()
    self.mission_state = None
    self.driving_state = None
    self.ego_status = VehicleStatus()
    self.gear_value = 0
    self.gear_text = " " 


  def guiTimer(self,data):    
    # GNSS Status GUI     
    gnss_text = " " 
    if self.fix_msg is None:
      gnss_text = "GNSS topic is not available"
    else:
      if self.fix_msg.position_covariance[0] > 5:
        gnss_text = "GNSS bad"
      else: 
        gnss_text = "GNSS Working, COV = " + str(self.fix_msg.position_covariance[0])
    gnss_overlay = OverlayText()
    gnss_overlay.width = 300
    gnss_overlay.height = 25
    gnss_overlay.left = 50
    gnss_overlay.top = 80
    gnss_overlay.text_size = 15
    gnss_overlay.line_width = 2
    gnss_overlay.font = "DejaVu Sans Mono"
    gnss_overlay.text = gnss_text
    if self.fix_msg.position_covariance[0] > 3:
      gnss_overlay.fg_color = ColorRGBA(255.0 , 0.0, 0.0 / 0.0, 1.0)
      gnss_overlay.bg_color = ColorRGBA(0.0, 0.0, 0.0, 0.2)
    else:
      gnss_overlay.fg_color = ColorRGBA(125 / 255.0, 1.0, 240.0 / 255.0, 1.0)
      gnss_overlay.bg_color = ColorRGBA(0.0, 0.0, 0.0, 0.2)
    
    self.fix_pub.publish(gnss_overlay)

    gear_overlay = OverlayText()
    
    gear_overlay.bg_color = ColorRGBA(0.0, 0.0, 0.0, 0.1)
    self.gear_text = " "
    if self.gear_value == 0:
      self.gear_text = "Park"
      gear_overlay.fg_color = ColorRGBA(0 / 255.0, 255.0/ 255.0, 209 / 255.0, 1.0)
    elif self.gear_value == 1:
      self.gear_text = "Drive"
      gear_overlay.fg_color = ColorRGBA(255 / 255.0, 0.0, 0.0 / 255.0, 1.0)
    
    elif self.gear_value == 2:
      self.gear_text = "Neutral"
      gear_overlay.fg_color = ColorRGBA(0.1 / 255.0, 0.1, 0.1 / 255.0, 1.0)

    elif self.gear_value == 3:
      self.gear_text = "Reverse"
      gear_overlay.fg_color = ColorRGBA(125 / 255.0, 1.0, 125.0 / 255.0, 1.0)
      
    else:
      self.gear_text = "NA_GEAR"
      gear_overlay.fg_color = ColorRGBA(255 / 255.0, 0.0, 0.0 / 255.0, 1.0)
    gear_overlay.width = 120
    gear_overlay.height = 25
    gear_overlay.left = 50
    gear_overlay.top = 110
    gear_overlay.text_size = 15
    gear_overlay.line_width = 1
    gear_overlay.font = "DejaVu Sans Mono"
    gear_overlay.text = self.gear_text
      
    self.gear_pub.publish(gear_overlay)
    

  
    lc_overlay = OverlayText()
    if self.left_lc and not self.right_lc:
      lc_text = "Left lane Change activated"
      lc_overlay.fg_color = ColorRGBA(0.0 / 255.0, 1.0, 0.0 / 255.0, 1.0)
    elif not self.left_lc and self.right_lc:
      lc_text = "Right lane Change activated"
      lc_overlay.fg_color = ColorRGBA(255 / 255.0, 0.0, 0.0 / 255.0, 1.0)
    else:
      lc_text = "No Lane change activated"
      lc_overlay.fg_color = ColorRGBA(255.0 / 255.0, 1.0, 0.0 / 255.0, 1.0)
      
    lc_overlay.width = 250
    lc_overlay.height = 25
    lc_overlay.left = 50
    lc_overlay.top = 140
    lc_overlay.text_size = 15
    lc_overlay.line_width = 2
    lc_overlay.font = "DejaVu Sans Mono"
    lc_overlay.text = lc_text
    lc_overlay.bg_color = ColorRGBA(0.0, 0.0, 0.0, 0.2)

    self.lc_pub.publish(lc_overlay)


  def left_lc_callback(self,data):
    self.left_lc = data.data

  def right_lc_callback(self,data):
    self.right_lc = data.data


  def gnss_callback(self,data):
    self.fix_msg = data
    

  def driving_callback(self,data):
    self.driving_state = data.data

  def mission_callback(self,data):
    self.mission_state = data.data 


  def vehicleStatusCallback(self,data):
    self.ego_status = data
    if self.ego_status.gear_info.gear is not None:
      
      self.gear_value = int(self.ego_status.gear_info.gear)
    
    




if __name__=='__main__':

    rossub = hmclGUI()
    # rossub.listener()
    rospy.spin()
    pass