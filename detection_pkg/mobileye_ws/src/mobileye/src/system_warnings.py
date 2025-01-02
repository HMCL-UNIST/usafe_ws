#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import SystemWarnings
from custom_msg_pkg.msg import MobileyeInfo_system_warnings

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/system_warnings_Info', MobileyeInfo_system_warnings, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_system_warnings()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            

        if data.id == 0x700:
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
