#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import Gyro
from custom_msg_pkg.msg import MobileyeInfo_gryo

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/gyro_Info', MobileyeInfo_gryo, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_gryo()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id == 0x703:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.gyro.gyro_sensor_data_available = self.frame_data[0]//128
            _data = self.frame_data[1]*256+self.frame_data[2]
            if _data > 32767:
                signed_data = (_data - 65536)
            else:
                signed_data = _data
            self.mobmsg.gyro.x_axis_data = signed_data*(-0.00875)

        

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
