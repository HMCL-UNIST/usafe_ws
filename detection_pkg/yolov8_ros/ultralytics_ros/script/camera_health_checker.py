#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int8MultiArray
from sensor_msgs.msg import CameraInfo

class CameraHealthChecker:
    def __init__(self):
        # Initialize the node
        rospy.init_node('camera_health_checker')

        # Initialize parameters for camera topics
        self.camera_topics = {
            'f': rospy.get_param('~camera_info_src_f', '/camera/front_60/camera/camera_info'),
            'l': rospy.get_param('~camera_info_src_l', '/camera/front_l/camera/camera_info'),
            'r': rospy.get_param('~camera_info_src_r', '/camera/front_r/camera/camera_info'),
            'b': rospy.get_param('~camera_info_src_b', '/camera/back/camera/camera_info')
        }

        # Dictionary to store the health status of each camera
        self.camera_health = {key: False for key in self.camera_topics}

        # Set up subscribers for each camera_info topic
        for key, topic in self.camera_topics.items():
            rospy.Subscriber(topic, CameraInfo, self.camera_info_callback, key)

        # Publisher for the health status of all cameras in a single topic
        self.health_pub = rospy.Publisher('/camera/health_status', Int8MultiArray, queue_size=10)

        # Timer to publish the health status every 0.5 seconds (2Hz)
        rospy.Timer(rospy.Duration(0.2), self.publish_health_status)

    def camera_info_callback(self, msg, camera_id):
        # When a message is received, set the corresponding camera's health to True
        self.camera_health[camera_id] = True

    def publish_health_status(self, event):
        # Create an Int8MultiArray message to represent the health status of all cameras
        health_status = Int8MultiArray()
        
        # Convert True/False values to 1/0 and append to the data field of the message
        health_status.data = [
            int(self.camera_health['f']),
            int(self.camera_health['l']),
            int(self.camera_health['r']),
            int(self.camera_health['b'])
        ]

        # Publish the health status message
        self.health_pub.publish(health_status)
        # rospy.loginfo(f"Published Camera Health Status: {health_status.data}")

        # Reset health status for the next check cycle
        self.camera_health = {key: False for key in self.camera_topics}

if __name__ == '__main__':
    try:
        checker = CameraHealthChecker()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
