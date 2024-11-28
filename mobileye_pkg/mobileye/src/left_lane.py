#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import LKAlane
from custom_msg_pkg.msg import MobileyeInfo_left

class mobileyeSub():
    def __init__(self):
        rospy.init_node("left_lane_node")
        self.mobPub = rospy.Publisher('/left_lane_Info', MobileyeInfo_left, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_left()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

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
