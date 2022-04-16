#!/usr/bin/env python
# license removed for brevity
# ====================================================== #
# Yonsei University - Seamless Transportation Laboratory #
# Ho Suk                                                 #
# sukho93@yonsei.ac.kr                                   #
# ====================================================== #
# Edited by hojinlee@unist.ac.kr #
# ====================================================== #
import threading
# import serial # library download is needed, https://pypi.org/project/pyserial/
import socket
import math 
import rospy
from std_msgs.msg import String, Header
from sensor_msgs.msg import NavSatFix 
import numpy as np
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped
from tf.transformations import euler_from_quaternion, quaternion_from_euler
import time
IP_ADDRS = '192.168.0.3'
PORT = 4000 

class TcpCommunicator(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        # self.ser = serial.Serial(port=PORT, baudrate=BAUD_RATE, parity=PARITY, stopbits=STOP_BITS)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
        self.server_socket.bind((IP_ADDRS, PORT)) 
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.listen(4)
        self.client_soc, self.addr = self.server_socket.accept()

        self.UTC_time = 0.0 
        self.activity_status = ""
        self.latitude = 0.0
        self.latitude_NS_indicator = ""
        self.longitude = 0.0
        self.longitude_EW_indicator = ""
        self.gnss_health = 0
        self.num_gnss = 0
        self.altitude = 0.0
        self.speed_knot = 0.0
        self.compass_degree = None
        self.heading = 0.0  # in degree
        self.UTC_date = 0
        self.magnetic_variation = None
        self.magnetic_variation_EW_indicator = None
        
    def run(self):
        self._readData(self.client_soc)

    def _readData(self, client_socket):
        while True:
            time.sleep(0.02)
            try:
                data = client_socket.recv(10000)                
                line = str(data)
                #line = line[2:] # discard b' at start and ' at end
                item_list = line.split(',')
                
                if item_list[0] == '$GNRMC': # for GNSS   or   '$INRMC' for INS
                    self.UTC_time = float(item_list[1]) # hhmmss.sss
                    self.activity_status = item_list[2] # A : Active , V : Void
                    self.latitude = float(item_list[3]) # ddmm.mmmm                    
                    self.latitude_NS_indicator = item_list[4] # N : North, S : South                    
                    self.longitude = float(item_list[5]) # dddmm.mmmm                    
                    self.longitude_EW_indicator = item_list[6] # E : East, W : West

                    self.latitude = int(self.latitude/100) + (self.latitude/100 - int(self.latitude/100))/0.6
                    self.longitude = int(self.longitude/100) + (self.longitude/100 - int(self.longitude/100))/0.6

                    self.speed_knot = float(item_list[7]) # 1knot = 1.852km/h
                    if item_list[8] != '':
                        self.compass_degree = float(item_list[8]) # WGS-84 standard
                    else:
                        self.compass_degree = None
                    self.UTC_date = int(item_list[9]) # ddmmyy
                    if item_list[10] != '':
                        self.magnetic_variation = float(item_list[10]) # angle difference
                    else:
                        self.magnetic_variation = None
                    if item_list[11] != '':
                        self.magnetic_variation_EW_indicator = item_list[11]
                    else:
                        self.magnetic_variation_EW_indicator = None
                elif item_list[0] == '$GNGGA': # for GNSS   or   '$INRMC' for INS
                    self.UTC_time = float(item_list[1]) # hhmmss.sss                    
                    self.latitude = float(item_list[2]) # ddmm.mmmm
                    self.latitude_NS_indicator = item_list[3] # N : North, S : South
                    self.longitude = float(item_list[4]) # dddmm.mmmm
                    self.longitude_EW_indicator = item_list[5] # E : East, W : West
                    self.latitude = int(self.latitude/100) + (self.latitude/100 - int(self.latitude/100))/0.6
                    self.longitude = int(self.longitude/100) + (self.longitude/100 - int(self.longitude/100))/0.6
                    self.gnss_health = int(item_list[6])   # 0 - fix not available, 1 - GPS fix, 2 - Differential GPS fix, 
                    self.num_gnss = int(item_list[7])
                    self.altitude = float(item_list[9])  
                elif item_list[0] == '$GNHDT':
                    self.heading = float(item_list[1])*math.pi/180
                    while self.heading > math.pi:
                        self.heading -= 2.0 * math.pi                        
                    while self.heading < -math.pi:
                        self.heading += 2.0 * math.pi

            except (ValueError, IndexError):
                pass

                
    # ================================================== #
    def getGNSSData(self):
        return self.activity_status, self.gnss_health, self.latitude, self.longitude, self.altitude, self.heading
    def getEntireGNRMCData(self):
        return self.UTC_time, self.activity_status, self.latitude, self.latitude_NS_indicator, self.longitude, self.longitude_EW_indicator, \
        self.speed_knot, self.compass_degree, self.UTC_date, self.magnetic_variation, self.magnetic_variation_EW_indicator
        
    def getPartialGNRMCData(self):
        return self.UTC_time, self.activity_status, self.latitude, self.longitude, self.speed_knot, self.compass_degree, self.UTC_date

if __name__ == '__main__':
    fix_pub = rospy.Publisher('fix', NavSatFix, queue_size=10)
    viz_fix_pub = rospy.Publisher('viz_fix', Path, queue_size=1)
    rospy.init_node('tdr3000', anonymous=True)
    rate = rospy.Rate(20) # 100hz
    fix_msg = NavSatFix()
    fix_viz_msg = Path()
    init_update = True
    try:        
        MyTcpCommunicator = TcpCommunicator()
        MyTcpCommunicator.start()          
        while not rospy.is_shutdown():
            activity_status, gnss_health, latitude, longitude, altitude, heading = MyTcpCommunicator.getGNSSData()                        
            fix_msg.header = Header()
            fix_msg.header.stamp = rospy.Time.now()
            fix_msg.header.frame_id = "gnss"            
            fix_msg.latitude = latitude
            fix_msg.longitude = longitude
            fix_msg.altitude = altitude
            if gnss_health == 0:
                fix_msg.position_covariance = [10] * 9
            elif gnss_health == 1:
                fix_msg.position_covariance = [1] * 9
            elif gnss_health == 2:
                fix_msg.position_covariance = [0.5] * 9
            elif gnss_health == 3:
                fix_msg.position_covariance = [0.2] * 9
            elif gnss_health > 3:
                fix_msg.position_covariance = [0.05] * 9       
            
            if activity_status !='A':
                fix_msg.position_covariance = [1000] * 9

            fix_pub.publish(fix_msg)
            
            if heading == 0.0:
                continue

            
           
            

            # fix_viz_msg.header = fix_msg.header
            # pose_tmp = PoseStamped()
            # pose_tmp.header = fix_msg.header
            # pose_tmp.pose.position.x = longitude
            # pose_tmp.pose.position.y = latitude
            # pose_tmp.pose.position.z = altitude
            # quat = quaternion_from_euler (0.0, 0.0,heading)            
            # pose_tmp.pose.orientation.x = quat[0]
            # pose_tmp.pose.orientation.y = quat[1]
            # pose_tmp.pose.orientation.z = quat[2]
            # pose_tmp.pose.orientation.w = quat[3]
            # dist_tmp = math.sqrt((prev_x - pose_tmp.pose.position.x)**2+(prev_y - pose_tmp.pose.position.y)**2)
            # if init_update:                
            #     prev_x = pose_tmp.pose.position.x
            #     prev_y = pose_tmp.pose.position.y    
            #     fix_viz_msg.poses.append(pose_tmp)
            #     init_update = False
            # if(dist_tmp > 0.2):
            #     prev_x = pose_tmp.pose.position.x
            #     prev_y = pose_tmp.pose.position.y    
            #     fix_viz_msg.poses.append(pose_tmp)
            # viz_fix_pub.publish(fix_viz_msg)

            
         
            rate.sleep()
            
    except rospy.ROSInterruptException:
        MyTcpCommunicator.server_socket.close()
        pass
    
        
       