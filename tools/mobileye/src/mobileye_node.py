#!/usr/bin/env python 

import rospy

from can_msgs.msg import Frame
# from custom_msg_pkg.msg import first_msg
# from custom_msg_pkg.msg import *
from mobileye.msg import MobileyeInfo, ObstacleData, LKAlane, TSR
from autoware_msgs.msg import DetectedObjectArray, DetectedObject
from visualization_msgs.msg import MarkerArray, Marker
from geometry_msgs.msg import PoseStamped, Pose, PoseWithCovariance
from nav_msgs.msg import Odometry
from tf.transformations import euler_from_quaternion, quaternion_from_euler, unit_vector
import math
from hmcl_msgs.msg import Lane

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/Mobileye_Info', MobileyeInfo, queue_size=20)
        self.objs_Pub = rospy.Publisher('/detected_objs', DetectedObjectArray, queue_size=10)
        self.objs_viz_Pub = rospy.Publisher('/detected_objs_viz', MarkerArray, queue_size=2)
        self.can_sub = rospy.Subscriber("/received_messages", Frame, self.data_pub)
        self.poseSub = rospy.Subscriber("/pose_estimate", Odometry, self.poseCallback)
        self.localPathSub = rospy.Subscriber("/local_traj", Lane, self.pathCallback)
        self.timerSub = rospy.Timer(rospy.Duration(0.1), self.detected_obj_timer)
        self.frame_ok = 0
        self.pose_ready = False
        self.ego_geo_pose = Pose()
        self.mobmsg = MobileyeInfo()
        self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        self.tsr_num = 0
        self.obj_num = 0
        self.local_trj =None

    

    def objs_marker_gen(self,objs):
        # objs is DetectedObjectArray msg
        markers = MarkerArray()
        for i in range(len(objs.objects)):
            obj = objs.objects[i]
            marker = self.obj_marker_gen(obj.pose,i)
            markers.markers.append(marker)
        return markers

    def obj_marker_gen(self,geo_pose,id):
        marker = Marker()
        marker.header.frame_id = "/map"
        marker.header.stamp = rospy.Time.now()
        # set shape, Arrow: 0; Cube: 1 ; Sphere: 2 ; Cylinder: 3
        marker.type = 1
        marker.id = id
        marker.lifetime =  rospy.Duration.from_sec(1)
        # Set the scale of the marker
        marker.scale.x = 1.0
        marker.scale.y = 1.0
        marker.scale.z = 1.0
        # Set the color
        marker.color.r = 1.0
        marker.color.g = 1.0
        marker.color.b = 0.0
        marker.color.a = 1.0

        # Set the pose of the marker
        marker.pose.position.x = geo_pose.position.x
        marker.pose.position.y = geo_pose.position.y
        marker.pose.position.z = geo_pose.position.z
        marker.pose.orientation.x = geo_pose.orientation.x
        marker.pose.orientation.y = geo_pose.orientation.y
        marker.pose.orientation.z = geo_pose.orientation.z
        marker.pose.orientation.w = geo_pose.orientation.w
        return marker

    def detected_obj_pub_callback(self):
        if(len(self.obstacle_data) < 1):
            print("No obstacle found")    
            return

        objs_msg = DetectedObjectArray()
        objs_msg.header.stamp = rospy.Time.now()
        objs_msg.header.frame_id = "map"
        
        for i in range(len(self.obstacle_data)):

            obj_msg  = DetectedObject()
            obj_msg.header.frame_id = "map"
            obj_msg.header.stamp = rospy.Time.now()
            obj_msg.angle = self.obstacle_data[i].obstacle_angle
            obj_msg.acceleration.linear.x = self.obstacle_data[i].obstacle_object_accel_x
            obj_msg.id = self.obstacle_data[i].obstacle_id    
            # if i < 1:
            #     print("init")
            #     if self.obstacle_data[i].obstacle_lane is not None:
            #         print("lane info " + str(self.obstacle_data[i].obstacle_lane))
                    

            
            self.ego_yaw = euler_from_quaternion([self.ego_geo_pose.orientation.x, self.ego_geo_pose.orientation.y,
                                                            self.ego_geo_pose.orientation.z, self.ego_geo_pose.orientation.w])[2]

            
            global_yaw = self.obstacle_data[i].obstacle_angle+self.ego_yaw
            obj_orientation_quat = quaternion_from_euler(0.0,0.0,global_yaw)
            obj_msg.pose.orientation.x= obj_orientation_quat[0]
            obj_msg.pose.orientation.y= obj_orientation_quat[1]
            obj_msg.pose.orientation.z= obj_orientation_quat[2]
            obj_msg.pose.orientation.w= obj_orientation_quat[3]
            
            local_delta_x = self.obstacle_data[i].obstacle_position_x
            local_delta_y = self.obstacle_data[i].obstacle_position_y
            dist_to_obj = math.sqrt(local_delta_x**2+local_delta_y**2)                
            
            add_obj =True
            if(dist_to_obj < 0.5):
                add_obj =False
            
            delta_x = local_delta_x*math.cos(self.ego_yaw)-local_delta_y*math.sin(self.ego_yaw)
            delta_y = local_delta_x*math.sin(self.ego_yaw)+local_delta_y*math.cos(self.ego_yaw)

            if self.pose_ready:
                obj_msg.pose.position.x = self.ego_geo_pose.position.x + delta_x
                obj_msg.pose.position.y = self.ego_geo_pose.position.y + delta_y            
            else:
                obj_msg.pose.position.x = local_delta_x
                obj_msg.pose.position.y = local_delta_y

            obj_msg.velocity.linear.x = self.obstacle_data[i].obstacle_relative_velocity_x
            
            if(add_obj):
                if(self.obj_inside_path(obj_msg)):
                    objs_msg.objects.append(obj_msg)
                if(self.obstacle_data[i].obstacle_lane == 1):
                    objs_msg.objects.append(obj_msg)

        self.objs_Pub.publish(objs_msg)
        # print("number of obj found = " + str(len(objs_msg.objects)))
        self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]

        ## Visualize detected obj
        viz_markers = self.objs_marker_gen(objs_msg)
        self.objs_viz_Pub.publish(viz_markers)

        
    def obj_inside_path(self,obj_msg):
        if self.local_trj is None: 
            return True
        if (self.local_trj.header.stamp - obj_msg.header.stamp).to_sec() > 0.5:
            return False
       
        # find min point 
        min_idx = 0
        min_dist = 1e4
        
        for i in range(len(self.local_trj.waypoints)):
            wp = self.local_trj.waypoints[i]
            dist_tmp = math.sqrt((wp.pose.pose.position.x-obj_msg.pose.position.x)**2+(wp.pose.pose.position.y-obj_msg.pose.position.y)**2)
            if dist_tmp < min_dist:
                min_dist = dist_tmp
                min_idx = i
        if(min_dist < 2.0):
            return True
        else:
            return False
                


            
    def pathCallback(self,path_msg):
        self.local_trj = path_msg

    def data_parser(self, data):
            
        if data.id == 0x766:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
        
            _data = self.frame_data[2]*256+self.frame_data[1]
            if _data > 32767:
                signed_data = (_data - 65536)
            else:
                signed_data = _data
            self.mobmsg.left_lane.position_parameter_c0 = float(signed_data)/256
            self.mobmsg.left_lane.curvature_parameter_c2 = float((self.frame_data[4]*256+self.frame_data[3])-0x7FFF)/1024/1000
            self.mobmsg.left_lane.curvature_derivative_c3 = float((self.frame_data[6]*256+self.frame_data[5])-0x7FFF)/(1<<28)
            self.mobmsg.left_lane.width_marking = self.frame_data[7]*0.01
            self.mobmsg.left_lane.model_degree = self.frame_data[0]//64
            self.mobmsg.left_lane.quality = (self.frame_data[0]%64)//16
            self.mobmsg.left_lane.lane_type = self.frame_data[0]%16
    
        elif data.id == 0x767:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.left_lane.heading_angle_parameter_c1 = float((self.frame_data[1]*256+self.frame_data[0])-0x7FFF)/1024
            self.mobmsg.left_lane.view_range = float((self.frame_data[3]%128)*256+self.frame_data[2])/256
            self.mobmsg.left_lane.view_range_availability = self.frame_data[3]//128

        elif data.id == 0x768:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            _data = self.frame_data[2]*256+self.frame_data[1]
            if _data > 32767:
                signed_data = (_data - 65536)
            else:
                signed_data = _data
            self.mobmsg.right_lane.position_parameter_c0 = float(signed_data)/256
            self.mobmsg.right_lane.curvature_parameter_c2 = float((self.frame_data[4]*256+self.frame_data[3])-0x7FFF)/1024/1000
            self.mobmsg.right_lane.curvature_derivative_c3 = float((self.frame_data[6]*256+self.frame_data[5])-0x7FFF)/(1<<28)
            self.mobmsg.right_lane.width_marking = self.frame_data[7]*0.01
            self.mobmsg.right_lane.model_degree = self.frame_data[0]//64
            self.mobmsg.right_lane.quality = (self.frame_data[0]%64)//16
            self.mobmsg.right_lane.lane_type = self.frame_data[0]%16
    
        elif data.id == 0x769:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.right_lane.heading_angle_parameter_c1 = float((self.frame_data[1]*256+self.frame_data[0])-0x7FFF)/1024
            self.mobmsg.right_lane.view_range = float((self.frame_data[3]%128)*256+self.frame_data[2])/256
            self.mobmsg.right_lane.view_range_availability = self.frame_data[3]//128

        elif data.id == 0x76a:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.reference_points.ref_point1_position = float((self.frame_data[1]*256+self.frame_data[0])-0x7FFF)/256
            self.mobmsg.reference_points.ref_point1_distance = float((self.frame_data[3]%128)*256+self.frame_data[2])/256
            self.mobmsg.reference_points.ref_point1_validity = self.frame_data[3]//128
            self.mobmsg.reference_points.ref_point2_position = float((self.frame_data[5]*256+self.frame_data[4])-0x7FFF)/256
            self.mobmsg.reference_points.ref_point2_distance = float((self.frame_data[7]%128)*256+self.frame_data[6])/256
            self.mobmsg.reference_points.ref_point2_validity = self.frame_data[7]//128

        elif data.id == 0x76b:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.number_of_next_lane_markers = self.frame_data[0]

        elif data.id >= 0x76c and data.id < 0x76c + 16:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            lane_index = (data.id - 0x76c)//2
            type_of_info = (data.id - 0x76c)%2
            if type_of_info == 0:
                _data = self.frame_data[2]*256+self.frame_data[1]
                if _data > 32767:
                    signed_data = (_data - 65536)
                else:
                    signed_data = _data
                self.next_lane[lane_index].position_parameter_c0 = float(signed_data)/256
                self.next_lane[lane_index].curvature_parameter_c2 = float((self.frame_data[4]*256+self.frame_data[3])-0x7FFF)/1024/1000
                self.next_lane[lane_index].curvature_derivative_c3 = float((self.frame_data[6]*256+self.frame_data[5])-0x7FFF)/(1<<28)
                self.next_lane[lane_index].width_marking = self.frame_data[7]*0.01
                self.next_lane[lane_index].model_degree = self.frame_data[0]//64
                self.next_lane[lane_index].quality = (self.frame_data[0]%64)//16
                self.next_lane[lane_index].lane_type = self.frame_data[0]%16
            else:
                self.next_lane[lane_index].heading_angle_parameter_c1 = float((self.frame_data[1]*256+self.frame_data[0])-0x7FFF)/1024
                self.next_lane[lane_index].view_range = float((self.frame_data[3]%128)*256+self.frame_data[2])/256
                self.next_lane[lane_index].view_range_availability = self.frame_data[3]//128

        elif data.id == 0x700:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.system_warnings.sound_type = self.frame_data[0]%8
            self.mobmsg.system_warnings.time_indicator = (self.frame_data[0]%32)//8
            self.mobmsg.system_warnings.zero_speed = (self.frame_data[1]%64)//32
            self.mobmsg.system_warnings.headway_valid = self.frame_data[2]%2
            self.mobmsg.system_warnings.error_valid = self.frame_data[3]%2
            self.mobmsg.system_warnings.error_code = self.frame_data[3]//2
            self.mobmsg.system_warnings.headway_measurement = (self.frame_data[2]//2)*0.1
            self.mobmsg.system_warnings.ldw_off = self.frame_data[4]%2
            self.mobmsg.system_warnings.left_ldw_on = (self.frame_data[4]%4)//2
            self.mobmsg.system_warnings.right_ldw_on = (self.frame_data[4]%8)//4
            self.mobmsg.system_warnings.fcw_on = (self.frame_data[4]%16)//8
            self.mobmsg.system_warnings.maintenance = (self.frame_data[4]%128)//64
            self.mobmsg.system_warnings.failsafe = self.frame_data[4]//128
            self.mobmsg.system_warnings.peds_fcw = (self.frame_data[5]%4)//2
            self.mobmsg.system_warnings.peds_in_dz = (self.frame_data[5]%8)//4
            self.mobmsg.system_warnings.tamper_alert = (self.frame_data[5]%64)//32
            self.mobmsg.system_warnings.tsr_enabled = self.frame_data[5]//128
            self.mobmsg.system_warnings.tsr_warning_level = self.frame_data[6]%8
            self.mobmsg.system_warnings.headway_warning_level = self.frame_data[7]%4
            self.mobmsg.system_warnings.hw_repeatable_enabled = (self.frame_data[7]%8)//4

        elif data.id == 0x760:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.car_info.high_beam = (self.frame_data[0]%64)//32
            self.mobmsg.car_info.low_beam = (self.frame_data[0]%32)//16
            self.mobmsg.car_info.wipers = (self.frame_data[0]%16)//8
            self.mobmsg.car_info.right_signal = (self.frame_data[0]%8)//4
            self.mobmsg.car_info.left_signal = (self.frame_data[0]%4)//2
            self.mobmsg.car_info.brake_signal = self.frame_data[0]%2
            self.mobmsg.car_info.high_beam_available = (self.frame_data[1]%64)//32
            self.mobmsg.car_info.low_beam_available = (self.frame_data[1]%32)//16
            self.mobmsg.car_info.wipers_available = (self.frame_data[1]%16)//8
            self.mobmsg.car_info.right_blink_available = (self.frame_data[1]%8)//4
            self.mobmsg.car_info.left_blink_available = (self.frame_data[1]%4)//2
            self.mobmsg.car_info.brake_available = self.frame_data[1]%2
            self.mobmsg.car_info.speed_available = self.frame_data[1]//128
            self.mobmsg.car_info.speed = self.frame_data[2]
            self.mobmsg.car_info.shield_plus_settings = self.frame_data[7]

        elif data.id == 0x737:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            _data = self.frame_data[1]*256+self.frame_data[0]
            if _data > 32767:
                signed_data = (_data - 65536)
            else:
                signed_data = _data
            self.mobmsg.lane.lane_curvature = signed_data*3.81*0.000001
            _data = (self.frame_data[3]%16)*256+self.frame_data[2]
            if _data > 2047:
                signed_data = (_data - 4096)
            else:
                signed_data = _data
            self.mobmsg.lane.lane_heading = signed_data*0.0005
            self.mobmsg.lane.ca = (self.frame_data[3]%32)//16
            self.mobmsg.lane.pitch_angle = float((self.frame_data[7]*256+self.frame_data[6])-0x7FFF)/1024/512
            self.mobmsg.lane.yaw_angle = float((self.frame_data[5]*256+self.frame_data[4])-0x7FFF)/1024
            self.mobmsg.lane.right_ldw_availability = (self.frame_data[3]%64)//32
            self.mobmsg.lane.left_ldw_availability = (self.frame_data[3]%128)//64

        elif data.id == 0x738:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            if self.frame_data[0] > 13:
                obstacle_num = 13                
            else:
                obstacle_num = self.frame_data[0]
        ############################
            self.obj_num = obstacle_num
        ############################
            self.mobmsg.obstacle_status.number_of_obstacles = obstacle_num
            self.mobmsg.obstacle_status.timestamp = self.frame_data[1]
            self.mobmsg.obstacle_status.left_close_rang_cut_in = (self.frame_data[2]%8)//4
            self.mobmsg.obstacle_status.right_close_rang_cut_in = (self.frame_data[2]%16)//8
            self.mobmsg.obstacle_status.go = self.frame_data[2]//16
            self.mobmsg.obstacle_status.close_car = self.frame_data[5]%2
            self.mobmsg.obstacle_status.failsafe = (self.frame_data[5]%32)//2

        elif data.id >= 0x739 and data.id <= 0x73b+(self.mobmsg.obstacle_status.number_of_obstacles-1)*3:
            
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            obstacle_idx = (data.id - 0x739)//3
            type_of_data = (data.id - 0x739)%3
            if type_of_data == 0:
                self.obstacle_data[obstacle_idx].obstacle_id = self.frame_data[0]
                self.obstacle_data[obstacle_idx].obstacle_position_x = ((self.frame_data[2]%16)*256+self.frame_data[1])*0.0625
                _data = (self.frame_data[4]%4)*256 + self.frame_data[3]
                if _data > 511:
                    signed_data = (_data - 1024)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].obstacle_position_y = signed_data*0.0625
                _data = (self.frame_data[6]%16)*256+self.frame_data[5]
                if _data > 2047:
                    signed_data = (_data - 4096)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].obstacle_relative_velocity_x = signed_data*0.0625
                self.obstacle_data[obstacle_idx].obstacle_type = (self.frame_data[6]%128)//16
                self.obstacle_data[obstacle_idx].obstacle_status = self.frame_data[7]%8
                self.obstacle_data[obstacle_idx].obstacle_brake_lights = (self.frame_data[7]%16)//8
                self.obstacle_data[obstacle_idx].cut_in_and_out = self.frame_data[4]//32
                self.obstacle_data[obstacle_idx].blinker_info = (self.frame_data[4]%32)//4
                self.obstacle_data[obstacle_idx].obstacle_valid = self.frame_data[7]//64
            elif type_of_data == 1:
                self.obstacle_data[obstacle_idx].obstacle_length = self.frame_data[0]*0.5
                self.obstacle_data[obstacle_idx].obstacle_width = self.frame_data[1]*0.05
                self.obstacle_data[obstacle_idx].obstacle_age = self.frame_data[2]
                self.obstacle_data[obstacle_idx].obstacle_lane = self.frame_data[3]%4
                self.obstacle_data[obstacle_idx].cipv_flag = (self.frame_data[3]%8)//4
                self.obstacle_data[obstacle_idx].radar_position_x = (self.frame_data[4]*16+self.frame_data[3]//16)*0.0625
                _data = (self.frame_data[6]%16)*256+self.frame_data[5]
                if _data > 2047:
                    signed_data = (_data - 4096)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].radar_velocity_x = signed_data*0.0625
                self.obstacle_data[obstacle_idx].radar_match_confidence = (self.frame_data[6]%128)//16
                self.obstacle_data[obstacle_idx].matched_radar_id = self.frame_data[7]%128
            else:
                _data = self.frame_data[1]*256+self.frame_data[0]
                if _data > 32767:
                    signed_data = (_data - 65536)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].obstacle_angle_rate = signed_data*0.01
                _data = self.frame_data[3]*256+self.frame_data[2]
                if _data > 32767:
                    signed_data = (_data - 65536)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].obstacle_scale_change = signed_data*0.0002
                _data = (self.frame_data[5]%4)*256+self.frame_data[4]
                if _data > 511:
                    signed_data = (_data - 1024)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].obstacle_object_accel_x = signed_data*0.03
                self.obstacle_data[obstacle_idx].obstacle_replaced = (self.frame_data[5]%32)//16
                _data = self.frame_data[7]*256+self.frame_data[6]
                if _data > 32767:
                    signed_data = (_data - 65536)
                else:
                    signed_data = _data
                self.obstacle_data[obstacle_idx].obstacle_angle = signed_data*0.01

        elif data.id == 0x703:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.gyro.gyro_sensor_data_available = self.frame_data[0]//128
            _data = self.frame_data[1]*256+self.frame_data[2]
            if _data > 32767:
                signed_data = (_data - 65536)
            else:
                signed_data = _data
            self.mobmsg.gyro.x_axis_data = signed_data*(-0.00875)

        elif data.id >= 0x720 and data.id <= 0x726:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            tsr_idx = data.id - 0x720
            self.tsr_num = tsr_idx
            self.tsr[tsr_idx].vision_only_sign_type = self.frame_data[0]
            self.tsr[tsr_idx].supplementary_sign_type = self.frame_data[1]
            self.tsr[tsr_idx].sign_position_x = self.frame_data[2]*0.5
            _data = self.frame_data[3]%128
            if _data > 63:
                signed_data = _data - 128
            else:
                signed_data = _data
            self.tsr[tsr_idx].sign_position_y = signed_data*0.5
            _data = self.frame_data[4]%64
            if _data > 31:
                signed_data = _data - 64
            else:
                signed_data = _data
            self.tsr[tsr_idx].sign_position_z = signed_data*0.5
            self.tsr[tsr_idx].filter_type = self.frame_data[5]

        elif data.id == 0x727:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.tsr_vision_only.vision_only_sign_type_display_1 = self.frame_data[0]
            self.mobmsg.tsr_vision_only.supplementary_sign_type_display_1 = self.frame_data[1]
            self.mobmsg.tsr_vision_only.vision_only_sign_type_display_2 = self.frame_data[2]
            self.mobmsg.tsr_vision_only.supplementary_sign_type_display_2 = self.frame_data[3]
            self.mobmsg.tsr_vision_only.vision_only_sign_type_display_3 = self.frame_data[4]
            self.mobmsg.tsr_vision_only.supplementary_sign_type_display_3 = self.frame_data[5]
            self.mobmsg.tsr_vision_only.vision_only_sign_type_display_4 = self.frame_data[6]
            self.mobmsg.tsr_vision_only.supplementary_sign_type_display_4 = self.frame_data[7]

        elif data.id == 0x400:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.smart_adas.persistent_on_off = (self.frame_data[0]%32)//8
            self.mobmsg.smart_adas.volume_level = self.frame_data[0]//32
            self.mobmsg.smart_adas.hmw_level = self.frame_data[1]%16
            self.mobmsg.smart_adas.ldw_volume_level = self.frame_data[2]%8
            self.mobmsg.smart_adas.hmw_volume_level = (self.frame_data[2]%64)//8
            self.mobmsg.smart_adas.ldw_level = self.frame_data[2]//64
            self.mobmsg.smart_adas.pedestrian_warning_level = self.frame_data[3]%4
            self.mobmsg.smart_adas.sli_warning_level = self.frame_data[4]%8
            self.mobmsg.smart_adas.blinker_reminder_level = self.frame_data[5]%8
            self.mobmsg.smart_adas.virtual_bumper_level = self.frame_data[6]%16
            self.mobmsg.smart_adas.hw_repeatable_level = self.frame_data[7]%16

        elif data.id == 0x401:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.smart_adas.buzzer_max_volume = self.frame_data[0]%8
            self.mobmsg.smart_adas.buzzer_min_volume = (self.frame_data[0]%64)//8
            self.mobmsg.smart_adas.ewiii_speed_indication = self.frame_data[0]//64
            self.mobmsg.smart_adas.buzzer_hmw_max_volume = self.frame_data[1]%8
            self.mobmsg.smart_adas.buzzer_hmw_min_volume = (self.frame_data[1]%64)//8
            self.mobmsg.smart_adas.disable_system_off = self.frame_data[1]//64
            self.mobmsg.smart_adas.buzzer_ldw_max_volume = self.frame_data[2]%8
            self.mobmsg.smart_adas.buzzer_ldw_min_volume = (self.frame_data[2]%64)//8
            self.mobmsg.smart_adas.calibration_source = self.frame_data[2]//64
            self.mobmsg.smart_adas.ldw_max_value = self.frame_data[3]%4
            self.mobmsg.smart_adas.ldw_min_value = (self.frame_data[3]%16)//4
            self.mobmsg.smart_adas.ldw_speed = (self.frame_data[3]%128)//16
            self.mobmsg.smart_adas.ped_max_value = self.frame_data[4]%4
            self.mobmsg.smart_adas.ped_min_value = (self.frame_data[4]%16)//4
            self.mobmsg.smart_adas.speed_for_high_low_beam_control = self.frame_data[4]//64
            self.mobmsg.smart_adas.virtual_bumper_max_value = self.frame_data[6]%16
            self.mobmsg.smart_adas.virtual_bumper_min_value = self.frame_data[6]//16
            self.mobmsg.smart_adas.blinker_reminder_max_value = self.frame_data[7]%16
            self.mobmsg.smart_adas.blinker_reminder_min_value = self.frame_data[7]//16

        elif data.id == 0x402:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.smart_adas.hmw_max_value = self.frame_data[0]%16
            self.mobmsg.smart_adas.hmw_min_value = self.frame_data[1]%16
            self.mobmsg.smart_adas.hmw_repeatable_max_value = self.frame_data[2]%16
            self.mobmsg.smart_adas.hmw_repeatable_min_value = self.frame_data[3]%16
            self.mobmsg.smart_adas.sli_max_value = self.frame_data[4]%8
            self.mobmsg.smart_adas.sli_min_value = (self.frame_data[4]%64)//8
            self.mobmsg.smart_adas.sli_delta_round_step = self.frame_data[5]%16
            self.mobmsg.smart_adas.sli_delta_round_upwards = (self.frame_data[5]%64)//16
            self.mobmsg.smart_adas.sli_unit_speed = (self.frame_data[6]%16)//4
            self.mobmsg.smart_adas.country_code = (self.frame_data[6]%64)//16
            self.mobmsg.smart_adas.tamper_alert_on_frames = self.frame_data[7]%4
            self.mobmsg.smart_adas.tamper_alert_off_frames = (self.frame_data[7]%16)//4
            self.mobmsg.smart_adas.tamper_alert_enable_j1939 = (self.frame_data[7]%64)//16

        elif data.id == 0x403:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            menuticks = self.frame_data[1]*256+self.frame_data[0]
            ad_menuticks = self.frame_data[3]*256+self.frame_data[2]
            for i in range(16):
                self.mobmsg.smart_adas.menu_ticks[i] = menuticks%2
                self.mobmsg.smart_adas.advanced_menu_ticks[i] = ad_menuticks%2
                menuticks = menuticks//2
                ad_menuticks = ad_menuticks//2

        elif data.id == 0x410:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.seeq.serial_number = self.frame_data[2]*256*256+self.frame_data[1]*256+self.frame_data[0]

        elif data.id == 0x411:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.seeq.production_date = self.frame_data[3]*256*256*256+self.frame_data[2]*256*256+self.frame_data[1]*256+self.frame_data[0]

        elif data.id == 0x412:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.seeq.brain_version_major = self.frame_data[0]
            self.mobmsg.seeq.brain_version_minor = self.frame_data[1]
            self.mobmsg.seeq.mest_version_major = self.frame_data[2]
            self.mobmsg.seeq.mest_version_minor = self.frame_data[3]
            self.mobmsg.seeq.mest_version_subminor = self.frame_data[4]
            self.mobmsg.seeq.mest_version_patch_number = self.frame_data[5]

        else:
            self.frame_ok = 0
        
        # print(self.mobmsg.lane.right_ldw_availability )

    def data_pub(self, data):
        self.data_parser(data)
        if self.frame_ok == 1:
            self.mobmsg.obstacle_data = self.obstacle_data[:self.mobmsg.obstacle_status.number_of_obstacles]
            self.mobmsg.next_lane = self.next_lane[:self.mobmsg.number_of_next_lane_markers]
            self.mobmsg.tsr = self.tsr[:self.tsr_num]
        self.mobPub.publish(self.mobmsg)
    
    def poseCallback(self,odom_msg):
        self.pose_ready = True
        self.ego_geo_pose = odom_msg.pose.pose
        
        
    
    def detected_obj_timer(self,data):        
        self.detected_obj_pub_callback()


    # def listener(self):
        
        
        

if __name__=='__main__':

    rossub = mobileyeSub()
    # rossub.listener()
    rospy.spin()
    pass
