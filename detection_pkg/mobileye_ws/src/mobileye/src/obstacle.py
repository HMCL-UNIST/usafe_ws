#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import ObstacleData
from custom_msg_pkg.msg import ObstacleStatus
from custom_msg_pkg.msg import MobileyeInfo_obstacle

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/obstacle_Info', MobileyeInfo_obstacle, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_obstacle()
        self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            

        if data.id == 0x738:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            if self.frame_data[0] > 13:
                obstacle_num = 13
            else:
                obstacle_num = self.frame_data[0]
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
        

    def data_pub(self, data):
        self.data_parser(data)
        if self.frame_ok == 1:
            self.mobmsg.obstacle_data = self.obstacle_data[:self.mobmsg.obstacle_status.number_of_obstacles]
            # self.mobmsg.next_lane = self.next_lane[:self.mobmsg.number_of_next_lane_markers]
            # self.mobmsg.tsr = self.tsr[:self.tsr_num]
        self.mobPub.publish(self.mobmsg)

    def listener(self):
        rospy.Subscriber("/data_info", first_msg, self.data_pub)
        rospy.spin()

if __name__=='__main__':
    rossub = mobileyeSub()
    rossub.listener()
