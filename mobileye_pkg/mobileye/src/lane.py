#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import Lane
from custom_msg_pkg.msg import MobileyeInfo_lane

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/lane_Info', MobileyeInfo_lane, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_lane()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id == 0x737:
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
