#!/usr/bin/env python
#-*- coding:utf-8 -*-


from canlib import canlib
from canlib.canlib import ChannelData

import time
import rospy
from custom_msg_pkg.msg import first_msg

def main(ch1,file_name):
    rospy.init_node('mobileye_data', anonymous=False)

    pub = rospy.Publisher('data_info', first_msg, queue_size=10)

    msg_1 = first_msg()
    count = 1

    f = open(file_name,"r")
    f.readline()
    for msg in f.readlines():
        print(msg)
        msg = msg.split(",")
        msg_1.id = int(msg[0],16)
        message =[int('0x'+msg[2][i:i+2],16) for i in range(0,len(msg[2]),2)]
        while len(message) < 8:
            message.append(0)
        print(message)
        msg_1.data = message
        msg_1.dlc = int(msg[1])
        # ch1.write_raw(int(msg[0],16),message,dlc=int(msg[1]))
        time.sleep(1/1000.0)
        input()
        pub.publish(msg_1)

        # rate.sleep()

        count += 1


if __name__ == '__main__':
    channel = 1
    chd = canlib.ChannelData(channel)

    file_name = '/home/buzz/mobileye_ws/src/mobileye/Mobileye_0126_150804.csv'
    print("CANlib version: v{}".format(chd.dll_product_version))
    print("canlib dll version: v{}".format(chd.dll_file_version))
    print("Using channel: {ch}, EAN: {ean}".format(ch=chd.device_name, ean=chd.card_upc_no))

    ch1 = canlib.openChannel(channel, canlib.canOPEN_ACCEPT_VIRTUAL)
    ch1.setBusOutputControl(canlib.canDRIVER_NORMAL)
    ch1.setBusParams(canlib.canBITRATE_500K)
    ch1.busOn()
    # sendEgoSpeed(ch1)
    #sendLane(ch1)
    #sendNextLane(ch1)
    #sendNumOfObs(ch1)
    ch1.busOff()
    try:
        main(ch1,file_name)
    except rospy.ROSInterruptException:
        pass


