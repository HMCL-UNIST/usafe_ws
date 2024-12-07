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
from geometry_msgs.msg import Pose, Point, Quaternion, PoseStamped
from nav_msgs.msg import Odometry

cur_odom_to_baselink = None
cur_map_to_odom = None


def pose_to_mat(pose_msg):
    return np.matmul(
        tf.listener.xyz_to_mat44(pose_msg.pose.pose.position),
        tf.listener.xyzw_to_mat44(pose_msg.pose.pose.orientation),
    )

def pose_to_mat_custom(x,y,z,qx,qy,qz,qw):
    # Convert position to 4x4 transformation matrix
    pos_mat = np.eye(4)
    pos_mat[:3, 3] = [x, y, z]

    rotation_mat = np.array([
        [1 - 2*qy**2 - 2*qz**2, 2*qx*qy - 2*qz*qw, 2*qx*qz + 2*qy*qw, 0],
        [2*qx*qy + 2*qz*qw, 1 - 2*qx**2 - 2*qz**2, 2*qy*qz - 2*qx*qw, 0],
        [2*qx*qz - 2*qy*qw, 2*qy*qz + 2*qx*qw, 1 - 2*qx**2 - 2*qy**2, 0],
        [0, 0, 0, 1]
    ])

    # Create 4x4 transformation matrix
    mat = np.matmul(pos_mat, rotation_mat)
    return mat

def transform_fusion():
    global cur_odom_to_baselink, cur_map_to_odom

    br = tf.TransformBroadcaster()
    while True:
        time.sleep(1 / FREQ_PUB_LOCALIZATION)

        # TODO 이 부분에 스레드 안전성을 고려하세요
        cur_odom = copy.copy(cur_odom_to_baselink)
        if cur_map_to_odom is not None:
            T_map_to_odom = pose_to_mat(cur_map_to_odom)
        else:
            T_map_to_odom = np.eye(4)

        br.sendTransform(tf.transformations.translation_from_matrix(T_map_to_odom),
                         tf.transformations.quaternion_from_matrix(T_map_to_odom),
                         rospy.Time.now(),
                         'camera_init', 'map')
        if cur_odom is not None:
            # 전역 위치 odometry를 게시합니다.
            localization = Odometry()


            T_odom_to_base_link = pose_to_mat(cur_odom)
            # 여기서 T_map_to_odom은 단기간 내에 느리게 변합니다. T_odom_to_base_link와의 시간 동기화를 고려하지 않습니다.
            T_map_to_base_link = np.matmul(T_map_to_odom, T_odom_to_base_link)
            xyz = tf.transformations.translation_from_matrix(T_map_to_base_link)
            quat = tf.transformations.quaternion_from_matrix(T_map_to_base_link)
            localization.pose.pose = Pose(Point(*xyz), Quaternion(*quat))


#######################################################################################################
            
            os_frame = pose_to_mat(localization)
            os2livox = pose_to_mat_custom(-1.044, -0.348, 0.140, -0.016, 0.010, 0.881, 0.472)
            output_result = tf.transformations.concatenate_matrices(os_frame, os2livox)
            # output_result = os_frame * os2livox
            # output_result = os2livox * os_frame
            result_trans = tf.transformations.translation_from_matrix(output_result)
            x, y, z = result_trans
            result_quat = tf.transformations.quaternion_from_matrix(output_result)
            qx, qy, qz ,qw = result_quat

            localization.pose.pose.position.x = x
            localization.pose.pose.position.y = y
            localization.pose.pose.position.z = z


            pose = PoseStamped()
            pose.pose = localization.pose.pose
            pose.header.stamp = cur_odom_to_baselink.header.stamp
            pose.header.frame_id = 'base_link'
            pub_pose.publish(pose)


            localization.pose.pose.orientation.x = qx
            localization.pose.pose.orientation.y = qy
            localization.pose.pose.orientation.z = qz
            localization.pose.pose.orientation.w = qw

#######################################################################################################


            localization.twist = cur_odom.twist

            localization.header.stamp = cur_odom.header.stamp
            localization.header.frame_id = 'map'
            localization.child_frame_id = 'body'
            pub_localization.publish(localization)

            # KR
            # pose = PoseStamped()
            # pose.pose = localization.pose.pose
            # pose.header.stamp = cur_odom.header.stamp
            # pose.header.frame_id = 'base_link'
            # pub_pose.publish(pose)

def cb_save_cur_odom(odom_msg):
    global cur_odom_to_baselink
    cur_odom_to_baselink = odom_msg


def cb_save_map_to_odom(odom_msg):
    global cur_map_to_odom
    cur_map_to_odom = odom_msg


if __name__ == '__main__':
    # tf and localization publishing frequency (HZ)
    FREQ_PUB_LOCALIZATION = 50

    rospy.init_node('transform_fusion')
    rospy.loginfo('Transform Fusion Node Inited...')

    rospy.Subscriber('/Odometry', Odometry, cb_save_cur_odom, queue_size=1)
    # rospy.Subscriber('/aft_mapped_to_init', Odometry, cb_save_cur_odom, queue_size=1)
    rospy.Subscriber('/map_to_odom', Odometry, cb_save_map_to_odom, queue_size=1)

    pub_localization = rospy.Publisher('/localization', Odometry, queue_size=1)
    pub_pose = rospy.Publisher('/current_pose_lidar', PoseStamped, queue_size=1)

    # 위치 메시지를 게시합니다.
    threading.Thread(target=transform_fusion).start()

    rospy.spin()
