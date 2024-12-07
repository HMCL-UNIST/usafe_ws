#!/usr/bin/env python3
# coding=utf8
from __future__ import print_function, division, absolute_import

import copy
import _thread
import time

import open3d as o3d
import rospy
import ros_numpy
from geometry_msgs.msg import PoseWithCovarianceStamped, Pose, Point, Quaternion
from nav_msgs.msg import Odometry
from sensor_msgs.msg import PointCloud2
import numpy as np
# import tf
# import tf.transformations

global_map = None
initialized = False
T_map_to_odom = np.eye(4)
cur_odom = None
cur_scan = None
init_thres = 0.0

def quaternion_multiply(q1, q2):
    """
    Multiplies two quaternions.
    """
    w1, x1, y1, z1 = q1
    w2, x2, y2, z2 = q2
    w = w1*w2 - x1*x2 - y1*y2 - z1*z2
    x = w1*x2 + x1*w2 + y1*z2 - z1*y2
    y = w1*y2 - x1*z2 + y1*w2 + z1*x2
    z = w1*z2 + x1*y2 - y1*x2 + z1*w2
    return [x, y, z, w]


def pose_to_mat(position, orientation):
    # Convert position to 4x4 transformation matrix
    pos_mat = np.eye(4)
    pos_mat[:3, 3] = [position.x, position.y, position.z]

    # Convert quaternion to rotation matrix
    qw = orientation.w
    qx = orientation.x
    qy = orientation.y
    qz = orientation.z

    rotation_mat = np.array([
        [1 - 2*qy**2 - 2*qz**2, 2*qx*qy - 2*qz*qw, 2*qx*qz + 2*qy*qw, 0],
        [2*qx*qy + 2*qz*qw, 1 - 2*qx**2 - 2*qz**2, 2*qy*qz - 2*qx*qw, 0],
        [2*qx*qz - 2*qy*qw, 2*qy*qz + 2*qx*qw, 1 - 2*qx**2 - 2*qy**2, 0],
        [0, 0, 0, 1]
    ])

    # Create 4x4 transformation matrix
    mat = np.matmul(pos_mat, rotation_mat)
    return mat


def msg_to_array(pc_msg):
    pc_array = ros_numpy.numpify(pc_msg)
    pc = np.zeros([len(pc_array), 3])
    pc[:, 0] = pc_array['x']
    pc[:, 1] = pc_array['y']
    pc[:, 2] = pc_array['z']
    return pc


def registration_at_scale(pc_scan, pc_map, initial, scale):
    result_icp = o3d.pipelines.registration.registration_icp(
        voxel_down_sample(pc_scan, SCAN_VOXEL_SIZE * scale), voxel_down_sample(pc_map, MAP_VOXEL_SIZE * scale),
        1.0 * scale, initial,
        o3d.pipelines.registration.TransformationEstimationPointToPoint(),
        o3d.pipelines.registration.ICPConvergenceCriteria(max_iteration=20)
    )

    return result_icp.transformation, result_icp.fitness


def inverse_se3(trans):
    trans_inverse = np.eye(4)
    # R
    trans_inverse[:3, :3] = trans[:3, :3].T
    # t
    trans_inverse[:3, 3] = -np.matmul(trans[:3, :3].T, trans[:3, 3])
    return trans_inverse


def publish_point_cloud(publisher, header, pc):
    data = np.zeros(len(pc), dtype=[
        ('x', np.float32),
        ('y', np.float32),
        ('z', np.float32),
        ('intensity', np.float32),
    ])
    data['x'] = pc[:, 0]
    data['y'] = pc[:, 1]
    data['z'] = pc[:, 2]
    if pc.shape[1] == 4:
        data['intensity'] = pc[:, 3]
    msg = ros_numpy.msgify(PointCloud2, data)
    msg.header = header
    publisher.publish(msg)


def crop_global_map_in_FOV(global_map, pose_estimation, cur_odom):
    # 当前scan原点的位姿
    # T_odom_to_base_link = pose_to_mat(cur_odom)
    T_odom_to_base_link = pose_to_mat(cur_odom.pose.pose.position, cur_odom.pose.pose.orientation)
    T_map_to_base_link = np.matmul(pose_estimation, T_odom_to_base_link)
    T_base_link_to_map = inverse_se3(T_map_to_base_link)

    # 把地图转换到lidar系下
    global_map_in_map = np.array(global_map.points)
    global_map_in_map = np.column_stack([global_map_in_map, np.ones(len(global_map_in_map))])
    global_map_in_base_link = np.matmul(T_base_link_to_map, global_map_in_map.T).T

    # 将视角内的地图点提取出来
    if FOV > 3.14:
        # 环状lidar 仅过滤距离
        indices = np.where(
            (global_map_in_base_link[:, 0] < FOV_FAR) &
            (np.abs(np.arctan2(global_map_in_base_link[:, 1], global_map_in_base_link[:, 0])) < FOV / 2.0)
        )
    else:
        # 非环状lidar 保前视范围
        # FOV_FAR>x>0 且角度小于FOV
        indices = np.where(
            (global_map_in_base_link[:, 0] > 0) &
            (global_map_in_base_link[:, 0] < FOV_FAR) &
            (np.abs(np.arctan2(global_map_in_base_link[:, 1], global_map_in_base_link[:, 0])) < FOV / 2.0)
        )
    global_map_in_FOV = o3d.geometry.PointCloud()
    global_map_in_FOV.points = o3d.utility.Vector3dVector(np.squeeze(global_map_in_map[indices, :3]))

    # 发布fov内点云
    header = cur_odom.header
    header.frame_id = 'map'
    publish_point_cloud(pub_submap, header, np.array(global_map_in_FOV.points)[::10])

    return global_map_in_FOV


# def global_localization(pose_estimation):
#     global global_map, cur_scan, cur_odom, T_map_to_odom
#     # 用icp配准
#     # print(global_map, cur_scan, T_map_to_odom)
#     rospy.loginfo('Global localization by scan-to-map matching......')

#     # TODO 这里注意线程安全
#     scan_tobe_mapped = copy.copy(cur_scan)

#     tic = time.time()

#     global_map_in_FOV = crop_global_map_in_FOV(global_map, pose_estimation, cur_odom)

#     # 粗配准
#     transformation, _ = registration_at_scale(scan_tobe_mapped, global_map_in_FOV, initial=pose_estimation, scale=5)

#     # 精配准
#     transformation, fitness = registration_at_scale(scan_tobe_mapped, global_map_in_FOV, initial=transformation,
#                                                     scale=1)
#     toc = time.time()
#     rospy.loginfo('Time: {}'.format(toc - tic))
#     rospy.loginfo('')

#     # 当全局定位成功时才更新map2odom
#     if fitness > LOCALIZATION_TH:
#         # T_map_to_odom = np.matmul(transformation, pose_estimation)
#         T_map_to_odom = transformation

#         # 发布map_to_odom
#         map_to_odom = Odometry()
#         xyz = tf.transformations.translation_from_matrix(T_map_to_odom)
#         quat = tf.transformations.quaternion_from_matrix(T_map_to_odom)
#         map_to_odom.pose.pose = Pose(Point(*xyz), Quaternion(*quat))
#         map_to_odom.header.stamp = cur_odom.header.stamp
#         map_to_odom.header.frame_id = 'map'
#         pub_map_to_odom.publish(map_to_odom)
#         return True
#     else:
#         rospy.logwarn('Not match!!!!')
#         rospy.logwarn('{}'.format(transformation))
#         rospy.logwarn('fitness score:{}'.format(fitness))
#         return False
def quaternion_from_matrix(matrix):
    """
    Compute quaternion from rotation matrix.

    Parameters:
    - matrix: 3x3 rotation matrix

    Returns:
    - quaternion: Quaternion in the form [x, y, z, w]
    """
    # Extract rotation matrix components
    m00 = matrix[0, 0]
    m01 = matrix[0, 1]
    m02 = matrix[0, 2]
    m10 = matrix[1, 0]
    m11 = matrix[1, 1]
    m12 = matrix[1, 2]
    m20 = matrix[2, 0]
    m21 = matrix[2, 1]
    m22 = matrix[2, 2]

    # Compute quaternion elements
    qw = np.sqrt(1 + m00 + m11 + m22) / 2.0
    qx = (m21 - m12) / (4.0 * qw)
    qy = (m02 - m20) / (4.0 * qw)
    qz = (m10 - m01) / (4.0 * qw)

    return [qx, qy, qz, qw]

def global_localization(pose_estimation):
    global global_map, cur_scan, cur_odom, T_map_to_odom, init_thres
    rospy.loginfo('Global localization by scan-to-map matching......')

    # Make a copy of the current scan for safety
    scan_tobe_mapped = copy.copy(cur_scan)

    tic = time.time()

    # Crop global map within FOV
    global_map_in_FOV = crop_global_map_in_FOV(global_map, pose_estimation, cur_odom)

    # Coarse registration
    transformation, _ = registration_at_scale(scan_tobe_mapped, global_map_in_FOV, initial=pose_estimation, scale=5)

    # Fine registration
    transformation, fitness = registration_at_scale(scan_tobe_mapped, global_map_in_FOV, initial=transformation,
                                                    scale=1)
    toc = time.time()
    rospy.loginfo('Time: {}'.format(toc - tic))
    rospy.loginfo('')
    if fitness > 0.9:
        init_thres = 0.9
    else:
        print(" ")
    print(init_thres)

    LOCALIZATION_TH = init_thres
    # Update map_to_odom only if global localization is successful
    if fitness > LOCALIZATION_TH:
        # Update T_map_to_odom
        T_map_to_odom = transformation

        # Publish map_to_odom
        map_to_odom = Odometry()
        # Extract translation and quaternion from the transformation matrix
        xyz = transformation[:3, 3]
        quat = quaternion_from_matrix(transformation)
        map_to_odom.pose.pose = Pose(Point(*xyz), Quaternion(*quat))
        map_to_odom.header.stamp = cur_odom.header.stamp
        map_to_odom.header.frame_id = 'map'
        pub_map_to_odom.publish(map_to_odom)
        return True
    else:
        rospy.logwarn('Not match!!!!')
        rospy.logwarn('{}'.format(transformation))
        rospy.logwarn('fitness score:{}'.format(fitness))
        return False


def voxel_down_sample(pcd, voxel_size):
    try:
        pcd_down = pcd.voxel_down_sample(voxel_size)
    except:
        # for opend3d 0.7 or lower
        pcd_down = o3d.geometry.voxel_down_sample(pcd, voxel_size)
    return pcd_down


def initialize_global_map(pc_msg):
    global global_map

    global_map = o3d.geometry.PointCloud()
    global_map.points = o3d.utility.Vector3dVector(msg_to_array(pc_msg)[:, :3])
    global_map = voxel_down_sample(global_map, MAP_VOXEL_SIZE)
    rospy.loginfo('Global map received.')


def cb_save_cur_odom(odom_msg):
    global cur_odom
    cur_odom = odom_msg


def cb_save_cur_scan(pc_msg):
    global cur_scan
    # 注意这里fastlio直接将scan转到odom系下了 不是lidar局部系
    pc_msg.header.frame_id = 'camera_init'
    pc_msg.header.stamp = rospy.Time().now()
    pub_pc_in_map.publish(pc_msg)

    # 转换为pcd
    # fastlio给的field有问题 处理一下
    pc_msg.fields = [pc_msg.fields[0], pc_msg.fields[1], pc_msg.fields[2],
                     pc_msg.fields[4], pc_msg.fields[5], pc_msg.fields[6],
                     pc_msg.fields[3], pc_msg.fields[7]]
    pc = msg_to_array(pc_msg)

    cur_scan = o3d.geometry.PointCloud()
    cur_scan.points = o3d.utility.Vector3dVector(pc[:, :3])


def thread_localization():
    global T_map_to_odom
    while True:
        # 每隔一段时间进行全局定位
        rospy.sleep(1 / FREQ_LOCALIZATION)
        # TODO 由于这里Fast lio发布的scan是已经转换到odom系下了 所以每次全局定位的初始解就是上一次的map2odom 不需要再拿odom了
        global_localization(T_map_to_odom)


if __name__ == '__main__':
    MAP_VOXEL_SIZE = 0.4
    SCAN_VOXEL_SIZE = 0.1

    # Global localization frequency (HZ)
    FREQ_LOCALIZATION = 0.5

    # The threshold of global localization,
    # only those scan2map-matching with higher fitness than LOCALIZATION_TH will be taken
    LOCALIZATION_TH = 0.8

    # FOV(rad), modify this according to your LiDAR type
    # FOV = 1.6
    FOV = 6.283

    # The farthest distance(meters) within FOV
    FOV_FAR = 50

    rospy.init_node('fast_lio_localization')
    rospy.loginfo('Localization Node Inited...')

    # publisher
    pub_pc_in_map = rospy.Publisher('/cur_scan_in_map', PointCloud2, queue_size=1)
    pub_submap = rospy.Publisher('/submap', PointCloud2, queue_size=1)
    pub_map_to_odom = rospy.Publisher('/map_to_odom', Odometry, queue_size=1)

    rospy.Subscriber('/cloud_registered', PointCloud2, cb_save_cur_scan, queue_size=1)
    # rospy.Subscriber('/Odometry', Odometry, cb_save_cur_odom, queue_size=1)
    rospy.Subscriber('/aft_mapped_to_init', Odometry, cb_save_cur_odom, queue_size=1)

    # 初始化全局地图
    rospy.logwarn('Waiting for global map......')
    initialize_global_map(rospy.wait_for_message('/map', PointCloud2))

    # 初始化
    while not initialized:
        rospy.logwarn('Waiting for initial pose....')

        # 等待初始位姿
        pose_msg = rospy.wait_for_message('/initialpose', PoseWithCovarianceStamped)
        # orientation = pose_msg.pose.pose.orientation

        # # Convert the orientation to a numpy array
        # initial_orientation = [orientation.x, orientation.y, orientation.z, orientation.w]

        # # Define the rotation quaternion
        # rotation_quaternion = [-0.016, 0.010, 0.881, 0.472]

        # # Normalize the rotation quaternion
        # rotation_quaternion = rotation_quaternion / np.linalg.norm(rotation_quaternion)

        # # Multiply the initial orientation by the rotation quaternion
        # new_orientation = quaternion_multiply(initial_orientation, rotation_quaternion)

        # # Update the pose message with the new orientation
        # pose_msg.pose.pose.orientation.x = new_orientation[0]
        # pose_msg.pose.pose.orientation.y = new_orientation[1]
        # pose_msg.pose.pose.orientation.z = new_orientation[2]
        # pose_msg.pose.pose.orientation.w = new_orientation[3]

        initial_pose = pose_to_mat(pose_msg.pose.pose.position, pose_msg.pose.pose.orientation)
        if cur_scan:
            initialized = global_localization(initial_pose)
        else:
            rospy.logwarn('First scan not received!!!!!')

    rospy.loginfo('')
    rospy.loginfo('Initialize successfully!!!!!!')
    rospy.loginfo('')
    # 开始定期全局定位
    _thread.start_new_thread(thread_localization, ())

    rospy.spin()
