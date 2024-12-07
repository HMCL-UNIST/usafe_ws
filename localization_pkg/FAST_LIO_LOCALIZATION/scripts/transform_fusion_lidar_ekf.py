#!/usr/bin/env python3
# coding=utf8
from __future__ import print_function, division, absolute_import

import copy
import threading
import time

import numpy as np
import rospy
import tf
import tf.transformations
from geometry_msgs.msg import Pose, Point, Quaternion, PoseStamped, TwistStamped
from nav_msgs.msg import Odometry
cur_odom_to_baselink_ekf = None
cur_odom_to_baselink = None
total_speed = None


def transform_fusion():

    global cur_odom_to_baselink, cur_odom_to_baselink_ekf, total_speed

    br = tf.TransformBroadcaster()
    while True:
        time.sleep(1 / FREQ_PUB_LOCALIZATION)

        # TODO 这里注意线程安全
        cur_odom = copy.copy(cur_odom_to_baselink)
        ekf_odom = copy.copy(cur_odom_to_baselink_ekf)

        if cur_odom is not None and ekf_odom is not None and total_speed is not None: 
            quaternion = (
                cur_odom.pose.pose.orientation.x,
                cur_odom.pose.pose.orientation.y,
                cur_odom.pose.pose.orientation.z,
                cur_odom.pose.pose.orientation.w
            )

            euler = tf.transformations.euler_from_quaternion(quaternion)
            yaw = euler[2]

            vx = total_speed * np.cos(yaw)
            vy = total_speed * np.sin(yaw)

            local_twist = TwistStamped()
            # Assign velocity to the twist message
            local_twist.twist.linear.x = vx
            local_twist.twist.linear.y = vy
            local_twist.twist.linear.z = 0
            local_twist.twist.angular.z = ekf_odom.twist.twist.angular.z
            
            local_twist.header.stamp = ekf_odom.header.stamp
            local_twist.header.frame_id = 'base_link'
            pub_twist.publish(local_twist)
            
            # Pose pub
            local_pose = PoseStamped()
            local_pose.pose.position = ekf_odom.pose.pose.position
            local_pose.pose.orientation = cur_odom.pose.pose.orientation
            local_pose.header.stamp = ekf_odom.header.stamp
            local_pose.header.frame_id = 'map'
            pub_pose.publish(local_pose)

            odom = Odometry()
            odom.header.stamp = ekf_odom.header.stamp
            odom.header.frame_id = 'map'
            odom.pose.pose  = local_pose.pose
            odom.twist.twist  = local_twist.twist
            pub_odometry.publish(odom)

def cb_save_cur_odom(odom_msg):
    global cur_odom_to_baselink, total_speed
    cur_odom_to_baselink = odom_msg



def cb_save_cur_odom_ekf(ekf_msg):
    global cur_odom_to_baselink_ekf, total_speed
    cur_odom_to_baselink_ekf = ekf_msg
    total_speed = np.sqrt(ekf_msg.twist.twist.linear.x**2 + ekf_msg.twist.twist.linear.y**2 + ekf_msg.twist.twist.linear.z**2)


if __name__ == '__main__':
    # tf and localization publishing frequency (HZ)
    FREQ_PUB_LOCALIZATION = 100

    rospy.init_node('transform_fusion')
    rospy.loginfo('Transform Fusion Node Inited...')

    rospy.Subscriber('/localization', Odometry, cb_save_cur_odom, queue_size=1)
    rospy.Subscriber('/nav_odom_ekf', Odometry, cb_save_cur_odom_ekf, queue_size=1)

    pub_pose = rospy.Publisher('/current_pose', PoseStamped, queue_size=1)
    pub_twist = rospy.Publisher('/current_velocity', TwistStamped, queue_size=1)
    pub_odometry = rospy.Publisher('/current_odometry', Odometry, queue_size=1)

    # 发布定位消息
    # thread.start_new_thread(transform_fusion, ())
    threading.Thread(target=transform_fusion).start()

    rospy.spin()
