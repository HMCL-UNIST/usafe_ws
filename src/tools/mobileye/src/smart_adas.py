#!/usr/bin/env python 

import rospy

# from can_msgs.msg import Frame
from custom_msg_pkg.msg import first_msg
from custom_msg_pkg.msg import SmartADAS
from custom_msg_pkg.msg import MobileyeInfo_smart_adas

class mobileyeSub():
    def __init__(self):
        rospy.init_node("dbw_mobileye_node")
        self.mobPub = rospy.Publisher('/smart_adas_Info', MobileyeInfo_smart_adas, queue_size=20)
        self.frame_ok = 0
        self.mobmsg = MobileyeInfo_smart_adas()
        # self.obstacle_data = [ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData(),ObstacleData()]
        # self.next_lane = [LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane(),LKAlane()]
        # self.tsr = [TSR(),TSR(),TSR(),TSR(),TSR(),TSR(),TSR()]
        # self.tsr_num = 0

    def data_parser(self, data):
            
        if data.id == 0x400:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.smart_adas.persistent_on_off = (self.frame_data[0]%32)//8
            self.mobmsg.smart_adas.volume_level = self.frame_data[0]//32
            self.mobmsg.smart_adas.hmw_level = self.frame_data[1]%16
            self.mobmsg.smart_adas.ldw_volume_level = self.frame_data[2]%8
            self.mobmsg.smart_adas.hmw_volume_level = (self.frame_data[2]%64)//8
            self.mobmsg.smart_adas.ldw_level = self.frame_data[2]//64
            self.mobmsg.smart_adas.pedestrian_warning_level = self.frame_data[3]%4
            self.mobmsg.smart_adas.sli_warning_level = self.frame_data[4]%8
            self.mobmsg.smart_adas.blinker_reminder_level = self.frame_data[5]%8
            self.mobmsg.smart_adas.virtual_bumper_level = self.frame_data[6]%16
            self.mobmsg.smart_adas.hw_repeatable_level = self.frame_data[7]%16

        elif data.id == 0x401:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.smart_adas.buzzer_max_volume = self.frame_data[0]%8
            self.mobmsg.smart_adas.buzzer_min_volume = (self.frame_data[0]%64)//8
            self.mobmsg.smart_adas.ewiii_speed_indication = self.frame_data[0]//64
            self.mobmsg.smart_adas.buzzer_hmw_max_volume = self.frame_data[1]%8
            self.mobmsg.smart_adas.buzzer_hmw_min_volume = (self.frame_data[1]%64)//8
            self.mobmsg.smart_adas.disable_system_off = self.frame_data[1]//64
            self.mobmsg.smart_adas.buzzer_ldw_max_volume = self.frame_data[2]%8
            self.mobmsg.smart_adas.buzzer_ldw_min_volume = (self.frame_data[2]%64)//8
            self.mobmsg.smart_adas.calibration_source = self.frame_data[2]//64
            self.mobmsg.smart_adas.ldw_max_value = self.frame_data[3]%4
            self.mobmsg.smart_adas.ldw_min_value = (self.frame_data[3]%16)//4
            self.mobmsg.smart_adas.ldw_speed = (self.frame_data[3]%128)//16
            self.mobmsg.smart_adas.ped_max_value = self.frame_data[4]%4
            self.mobmsg.smart_adas.ped_min_value = (self.frame_data[4]%16)//4
            self.mobmsg.smart_adas.speed_for_high_low_beam_control = self.frame_data[4]//64
            self.mobmsg.smart_adas.virtual_bumper_max_value = self.frame_data[6]%16
            self.mobmsg.smart_adas.virtual_bumper_min_value = self.frame_data[6]//16
            self.mobmsg.smart_adas.blinker_reminder_max_value = self.frame_data[7]%16
            self.mobmsg.smart_adas.blinker_reminder_min_value = self.frame_data[7]//16

        elif data.id == 0x402:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            self.mobmsg.smart_adas.hmw_max_value = self.frame_data[0]%16
            self.mobmsg.smart_adas.hmw_min_value = self.frame_data[1]%16
            self.mobmsg.smart_adas.hmw_repeatable_max_value = self.frame_data[2]%16
            self.mobmsg.smart_adas.hmw_repeatable_min_value = self.frame_data[3]%16
            self.mobmsg.smart_adas.sli_max_value = self.frame_data[4]%8
            self.mobmsg.smart_adas.sli_min_value = (self.frame_data[4]%64)//8
            self.mobmsg.smart_adas.sli_delta_round_step = self.frame_data[5]%16
            self.mobmsg.smart_adas.sli_delta_round_upwards = (self.frame_data[5]%64)//16
            self.mobmsg.smart_adas.sli_unit_speed = (self.frame_data[6]%16)//4
            self.mobmsg.smart_adas.country_code = (self.frame_data[6]%64)//16
            self.mobmsg.smart_adas.tamper_alert_on_frames = self.frame_data[7]%4
            self.mobmsg.smart_adas.tamper_alert_off_frames = (self.frame_data[7]%16)//4
            self.mobmsg.smart_adas.tamper_alert_enable_j1939 = (self.frame_data[7]%64)//16

        elif data.id == 0x403:
            self.frame_ok = 1
            self.frame_data = bytearray(data.data)
            menuticks = self.frame_data[1]*256+self.frame_data[0]
            ad_menuticks = self.frame_data[3]*256+self.frame_data[2]
            for i in range(16):
                self.mobmsg.smart_adas.menu_ticks[i] = menuticks%2
                self.mobmsg.smart_adas.advanced_menu_ticks[i] = ad_menuticks%2
                menuticks = menuticks//2
                ad_menuticks = ad_menuticks//2

        

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
