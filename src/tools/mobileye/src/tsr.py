#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import TSR
from custom_msg_pkg.msg import TSRVisionOnlySign
from custom_msg_pkg.msg import MobileyeInfo_tsr

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/tsr_Info', MobileyeInfo_tsr, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_tsr()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id >= 0x720 and data.id <= 0x726:
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

        

    def data_pub(self, data):
        self.data_parser(data)
        if self.frame_ok == 1:
            # self.mobmsg.obstacle_data = self.obstacle_data[:self.mobmsg.obstacle_status.number_of_obstacles]
            # self.mobmsg.next_lane = self.next_lane[:self.mobmsg.number_of_next_lane_markers]
            self.mobmsg.tsr = self.tsr[:self.tsr_num]
        self.mobPub.publish(self.mobmsg)

    def listener(self):
        rospy.Subscriber("/data_info", first_msg, self.data_pub)
        rospy.spin()

if __name__=='__main__':
    rossub = mobileyeSub()
    rossub.listener()
