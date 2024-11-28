#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import SeeQ
from custom_msg_pkg.msg import MobileyeInfo_seeq

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/seeq_Info', MobileyeInfo_seeq, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_seeq()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id == 0x410:
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
