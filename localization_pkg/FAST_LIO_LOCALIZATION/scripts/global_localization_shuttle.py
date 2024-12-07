#!/usr/bin/env python3
# coding=utf8
from __future__ import print_function, division, absolute_import

import copy
import _thread
import time

import open3d as o3d
import rospy
import ros_numpy
from geometry_msgs.msg import PoseWithCovarianceStamped, Pose, Point, Quaternion, PoseStamped
from nav_msgs.msg import Odometry
from sensor_msgs.msg import PointCloud2
import numpy as np


global_map = None
initialized = False
reinitialized = True
stopinitialized = True
T_map_to_odom = np.eye(4)
cur_pose = np.eye(4)
cur_odom = None
cur_scan = None
ini_thres = 0.0

times = []

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



def registration_at_scale_coarse(pc_scan, pc_map, initial, scale):
    result_icp = o3d.pipelines.registration.registration_icp(
        voxel_down_sample(pc_scan, SCAN_VOXEL_SIZE * scale), voxel_down_sample(pc_map, MAP_VOXEL_SIZE * scale),
        1.0, initial,
        o3d.pipelines.registration.TransformationEstimationPointToPoint(),
        o3d.pipelines.registration.ICPConvergenceCriteria(max_iteration=20)
    )

    return result_icp.transformation, result_icp.fitness

def registration_at_scale_fine(pc_scan, pc_map, initial, scale):
    result_icp = o3d.pipelines.registration.registration_icp(
        voxel_down_sample(pc_scan, SCAN_VOXEL_SIZE * scale), voxel_down_sample(pc_map, MAP_VOXEL_SIZE * scale),
        0.5, initial,
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
    global global_map, cur_scan, cur_odom, T_map_to_odom, ini_thres, times
    # rospy.loginfo('Global localization by scan-to-map matching......')

    # Make a copy of the current scan for safety
    scan_tobe_mapped = copy.copy(cur_scan)

    tic = time.time()

    # Crop global map within FOV
    global_map_in_FOV = crop_global_map_in_FOV(global_map, pose_estimation, cur_odom)

    # Coarse registration
    transformation, _ = registration_at_scale_coarse(scan_tobe_mapped, global_map_in_FOV, initial=pose_estimation, scale=5)

    # Fine registration
    transformation, fitness = registration_at_scale_fine(scan_tobe_mapped, global_map_in_FOV, initial=transformation,
                                                    scale=1)
    toc = time.time()


    
    # Update map_to_odom only if global localization is successful
    if fitness > 0.8:
        ini_thres = 0.8

    else:
        b=1
    times.append(toc - tic)
    LOCALIZATION_TH = ini_thres

    print(fitness)

    # if fitness > LOCALIZATION_TH:
    if fitness > LOCALIZATION_TH and reinitialized and stopinitialized:
    # if True and reinitialized and stopinitialized:
        T_map_to_odom = transformation

        map_to_odom = Odometry()
        xyz = transformation[:3, 3]
        quat = quaternion_from_matrix(transformation)
        map_to_odom.pose.pose = Pose(Point(*xyz), Quaternion(*quat))
        map_to_odom.header.stamp = cur_odom.header.stamp
        map_to_odom.header.frame_id = 'map'
        pub_map_to_odom.publish(map_to_odom)

        # print(transformation)
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

def cb_save_init_pose(init_msg):
    global cur_odom, T_map_to_odom
    if initialized:
        cur_pose  = pose_to_mat(cur_odom.pose.pose.position, cur_odom.pose.pose.orientation)
        initial_pose = pose_to_mat(init_msg.pose.pose.position, init_msg.pose.pose.orientation)
        init_pose = initial_pose @ inverse_se3(cur_pose)
        T_map_to_odom = init_pose

        print("REINIT!!!!")

def cb_save_stop_init_pose(stop_init_msg):
    global stopinitialized
    if stopinitialized:
        stopinitialized = False
    else:
        stopinitialized = True


def cb_save_cur_scan(pc_msg):
    global cur_scan
    pc_msg.header.frame_id = 'camera_init'
    pc_msg.header.stamp = rospy.Time().now()
    pub_pc_in_map.publish(pc_msg)

    pc_msg.fields = [pc_msg.fields[0], pc_msg.fields[1], pc_msg.fields[2],
                     pc_msg.fields[4], pc_msg.fields[5], pc_msg.fields[6],
                     pc_msg.fields[3], pc_msg.fields[7]]
    pc = msg_to_array(pc_msg)

    cur_scan = o3d.geometry.PointCloud()
    cur_scan.points = o3d.utility.Vector3dVector(pc[:, :3])


def thread_localization():
    global T_map_to_odom
    while initialized:
        if reinitialized:
            rospy.sleep(1 / FREQ_LOCALIZATION)
            global_localization(T_map_to_odom)



if __name__ == '__main__':
    MAP_VOXEL_SIZE = 0.4
    SCAN_VOXEL_SIZE = 0.1

    # Global localization frequency (HZ)
    FREQ_LOCALIZATION = 0.5

    # The threshold of global localization,
    # only those scan2map-matching with higher fitness than LOCALIZATION_TH will be taken
    # LOCALIZATION_TH = 0.95
    LOCALIZATION_TH = 0.0

    # FOV(rad), modify this according to your LiDAR type
    FOV = 6.28319

    # The farthest distance(meters) within FOV
    FOV_FAR = 150

    rospy.init_node('fast_lio_localization')
    rospy.loginfo('Localization Node Inited...')

    # publisher
    pub_pc_in_map = rospy.Publisher('/cur_scan_in_map', PointCloud2, queue_size=1)
    pub_submap = rospy.Publisher('/submap', PointCloud2, queue_size=1)
    pub_map_to_odom = rospy.Publisher('/map_to_odom', Odometry, queue_size=1)

    rospy.Subscriber('/cloud_registered', PointCloud2, cb_save_cur_scan, queue_size=1)
    # rospy.Subscriber('/Odometry', Odometry, cb_save_cur_odom, queue_size=1)
    rospy.Subscriber('/aft_mapped_to_init', Odometry, cb_save_cur_odom, queue_size=1)
    rospy.Subscriber('/initialpose', PoseWithCovarianceStamped, cb_save_init_pose, queue_size=1)
    rospy.Subscriber('/global_stop', PoseStamped, cb_save_stop_init_pose, queue_size=1)

    # 初始化全局地图
    rospy.logwarn('Waiting for global map......')
    initialize_global_map(rospy.wait_for_message('/map', PointCloud2))

    # 初始化
    while not initialized:
        rospy.logwarn('Waiting for initial pose....')
        pose_msg = rospy.wait_for_message('/initialpose', PoseWithCovarianceStamped)

        cur_pose  = pose_to_mat(cur_odom.pose.pose.position, cur_odom.pose.pose.orientation)
        initial_pose = pose_to_mat(pose_msg.pose.pose.position, pose_msg.pose.pose.orientation)

        # init_pose = inverse_se3(cur_pose) @ initial_pose
        init_pose = initial_pose @ inverse_se3(cur_pose)

        if cur_scan:
            initialized = global_localization(init_pose)
        else:
            rospy.logwarn('First scan not received!!!!!')


    rospy.loginfo('')
    rospy.loginfo('Initialize successfully!!!!!!')
    rospy.loginfo('')
    # 开始定期全局定位
    _thread.start_new_thread(thread_localization, ())

    rospy.spin()
