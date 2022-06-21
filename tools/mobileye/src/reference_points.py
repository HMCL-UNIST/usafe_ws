#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import ReferencePoints
from custom_msg_pkg.msg import MobileyeInfo_referencepoints

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/reference_points_Info', MobileyeInfo_referencepoints, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_referencepoints()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id == 0x76a:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.reference_points.ref_point1_position = float((self.frame_data[1]*256+self.frame_data[0])-0x7FFF)/256
            self.mobmsg.reference_points.ref_point1_distance = float((self.frame_data[3]%128)*256+self.frame_data[2])/256
            self.mobmsg.reference_points.ref_point1_validity = self.frame_data[3]//128
            self.mobmsg.reference_points.ref_point2_position = float((self.frame_data[5]*256+self.frame_data[4])-0x7FFF)/256
            self.mobmsg.reference_points.ref_point2_distance = float((self.frame_data[7]%128)*256+self.frame_data[6])/256
            self.mobmsg.reference_points.ref_point2_validity = self.frame_data[7]//128

        

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