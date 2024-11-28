#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import LKAlane
from custom_msg_pkg.msg import MobileyeInfo_number_of_next_lane_markers
# from custom_msg_pkg.msg import MobileyeInfo_referencepoints

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/number_of_next_lane_markers_Info', MobileyeInfo_number_of_next_lane_markers, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_number_of_next_lane_markers()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            

        if data.id == 0x76b:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.number_of_next_lane_markers = self.frame_data[0]
            # print(data.id)

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
        

    def data_pub(self, data):
        self.data_parser(data)
        if self.frame_ok == 1:
            # self.mobmsg.obstacle_data = self.obstacle_data[:self.mobmsg.obstacle_status.number_of_obstacles]
            self.mobmsg.next_lane = self.next_lane[:self.mobmsg.number_of_next_lane_markers]
            # self.mobmsg.tsr = self.tsr[:self.tsr_num]
        self.mobPub.publish(self.mobmsg)

    def listener(self):
        rospy.Subscriber("/data_info", first_msg, self.data_pub)
        rospy.spin()

if __name__=='__main__':
    rossub = mobileyeSub()
    rossub.listener()
