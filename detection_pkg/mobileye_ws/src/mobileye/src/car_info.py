#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import CarInfo
from custom_msg_pkg.msg import MobileyeInfo_car_info

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/car_Info', MobileyeInfo_car_info, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_car_info()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id == 0x760:
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

        

    def data_pub(self, data):
        self.data_parser(data)
        # if self.frame_ok == 1:
            # self.mobmsg.obstacle_data = self.obstacle_data[:self.mobmsg.obstacle_status.number_of_obstacles]
            # self.mobmsg.next_lane = self.next_lane[:self.mobmsg.number_of_next_lane_markers]
            # self.mobmsg.tsr = self.tsr[:self.tsr_num]
        self.mobPub.publish(self.mobmsg)

    def listener(self):
        rospy.Subscriber("/data_info", first_msg, self.data_pub)
        rospy.spin()

if __name__=='__main__':
    rossub = mobileyeSub()
    rossub.listener()
