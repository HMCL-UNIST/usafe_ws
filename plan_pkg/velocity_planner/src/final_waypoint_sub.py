#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import Float64
from geometry_msgs.msg import TwistStamped
from sensor_msgs.msg import Imu
import matplotlib.pyplot as plt

# 데이터 저장을 위한 리스트 초기화
setpoint_velocities = []
current_velocities = []
current_accel = []
curvature_values = []

# 콜백 함수
def setpoint_callback(data):
    global setpoint_velocities
    setpoint_velocities.append(data.data)

def current_velocity_callback(data):
    global current_velocities
    
    current_velocities.append(data.twist.linear.x)
    
def curvature_callback(data):
    global curvature_values
    global current_accel 
    curvature_values.append(data.linear_acceleration.x)
    current_accel(data.linear_acceleration.y)
def plot_data(event):
    rospy.loginfo("Plotting data")

    if len(current_velocities) > 1000:
        plt.figure()
        
        plt.subplot(3, 1, 1)
        plt.plot(setpoint_velocities, label='Setpoint Velocities')
        plt.title('Setpoint Velocities')
        plt.xlabel('Index')
        plt.ylabel('Velocity (km/h)')
        plt.legend()
        
        plt.subplot(3, 1, 2)
        plt.plot(current_velocities, 'r', label='Current Velocity')
        plt.title('Current Velocity')
        plt.xlabel('Index')
        plt.ylabel('Velocity (km/h)')
        plt.legend()
        
        # plt.subplot(3, 1, 3)
        # plt.plot(curvature_values, 'g', label='Curvature Values')
        # plt.title('Curvature Values')
        # plt.xlabel('Index')
        # plt.ylabel('Curvature (1/m)')
        # plt.legend()
        
        plt.tight_layout()
        plt.show()
        rospy.signal_shutdown("Plot generated")

def listener():
    rospy.init_node('setpoint_listener', anonymous=True)
    rospy.Subscriber('/setpoint', Float64, setpoint_callback)
    rospy.Subscriber('/current_velocity', TwistStamped, current_velocity_callback)
    rospy.Subscriber('/ouster/imu', Imu, curvature_callback)
    
    # Start the timer to periodically check and plot data
    rospy.Timer(rospy.Duration(1.0), plot_data)
    
    rospy.spin()

if __name__ == '__main__':
    listener()
