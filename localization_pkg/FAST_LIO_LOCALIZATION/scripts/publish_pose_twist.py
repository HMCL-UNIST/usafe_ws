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

localization_odom = None
prev_pose = None
prev_time = None
prev_x = None
prev_y = None
prev_z = None

def calculate_velocity(cur_pose, cur_time):
    global prev_pose, prev_time, prev_yaw, prev_x, prev_y, prev_z

    if prev_pose is None or prev_time is None or prev_yaw is None:
        # If this is the first pose received, initialize the previous pose, time, and yaw
        prev_pose = cur_pose
        prev_time = cur_time
        prev_yaw = 0.0
        prev_x = 0.0
        prev_y = 0.0
        prev_z = 0.0
        return 0.0, 0.0, 0.0, 0.0

    # Calculate the time difference between the current and previous poses
    dt = (cur_time - prev_time).to_sec()

    # Check if time difference is non-zero to avoid division by zero
    if dt == 0:
        return 0.0, 0.0, 0.0, 0.0

    # Calculate linear velocity
    dx = cur_pose.pose.position.x - prev_pose.pose.position.x
    dy = cur_pose.pose.position.y - prev_pose.pose.position.y
    dz = cur_pose.pose.position.z - prev_pose.pose.position.z
    linear_velocity_x = dx / dt
    linear_velocity_y = dy / dt
    linear_velocity_z = dz / dt

    if(np.sqrt(prev_x**2 + prev_y**2 + prev_z**2)>5 and np.sqrt(linear_velocity_x**2 + linear_velocity_y**2 + linear_velocity_z**2)<1):
        linear_velocity_x = prev_x
        linear_velocity_y = prev_y
        linear_velocity_z = prev_z

    # Calculate angular velocity
    quaternion_cur = (
        cur_pose.pose.orientation.x,
        cur_pose.pose.orientation.y,
        cur_pose.pose.orientation.z,
        cur_pose.pose.orientation.w
    )
    euler_cur = tf.transformations.euler_from_quaternion(quaternion_cur)
    yaw_cur = euler_cur[2]

    delta_yaw = yaw_cur - prev_yaw
    if delta_yaw > np.pi:
        delta_yaw -= 2 * np.pi
    elif delta_yaw < -np.pi:
        delta_yaw += 2 * np.pi

    angular_velocity = delta_yaw / dt

    # Update the previous pose, time, and yaw for the next iteration
    prev_pose = cur_pose
    prev_time = cur_time
    prev_yaw = yaw_cur
    prev_x = linear_velocity_x
    prev_y = linear_velocity_y
    prev_z = linear_velocity_z
    return linear_velocity_x, linear_velocity_y, linear_velocity_z, angular_velocity


def KR_twist():
    n = 0
    global localization_odom

    br = tf.TransformBroadcaster()
    while True:
        time.sleep(1 / FREQ_PUB_LOCALIZATION)

        if localization_odom is not None:
            local_twist = TwistStamped()

            # KR
            vx, vy, vz, omega = calculate_velocity(localization_odom.pose, localization_odom.header.stamp)
            # Assign velocity to the twist message
            local_twist.twist.linear.x = vx
            local_twist.twist.linear.y = vy
            local_twist.twist.linear.z = vz
            local_twist.twist.angular.z = omega

            local_twist.header.stamp = localization_odom.header.stamp
            local_twist.header.frame_id = 'base_link'
            pub_twist.publish(local_twist)
            

            total_speed = np.sqrt(vx**2 + vy**2 + vz**2)
            total_speed_kmh = total_speed * 3.6
            print("Speed:", total_speed_kmh, "km/h")
        # n = n + 1 


def local_cur_odom(odom_msg):
    global localization_odom
    localization_odom = odom_msg


if __name__ == '__main__':
    # tf and localization publishing frequency (HZ)
    # FREQ_PUB_LOCALIZATION = 50
    FREQ_PUB_LOCALIZATION = 5
    
    rospy.init_node('pub_pose_twist')

    # rospy.Subscriber('/localization', Odometry, local_cur_odom, queue_size=1)
    rospy.Subscriber('/aft_mapped_to_init', Odometry, local_cur_odom, queue_size=1)
    # rospy.Subscriber('/Odometry', Odometry, local_cur_odom, queue_size=1)

    # pub_pose = rospy.Publisher('/current_pose', PoseStamped, queue_size=1)
    pub_twist = rospy.Publisher('/current_velocity', TwistStamped, queue_size=1)

    # 发布定位消息
    # thread.start_new_thread(KR_twsist, ())
    threading.Thread(target=KR_twist).start()

    rospy.spin()
