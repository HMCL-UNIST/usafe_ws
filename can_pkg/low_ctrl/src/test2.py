import numpy as np
import time
import can
import rospy
from std_msgs.msg import Float64

a = np.array([1,2,3,0,5])
b = np.array([1,2,3,0,0])

value = a/b

def talker():
    rospy.init_node('test_node', anonymous=True)
    pub = rospy.Publisher('control_effort', Float64, queue_size=10)
    
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        pub.publish(20)
        # pub.publish(value[3])
        rate.sleep()

def send_can_message(channel, message_id, data):
    bus = can.interface.Bus(channel=channel, bustype='socketcan')

    message = can.Message(
        arbitration_id=message_id,
        data=data,
        is_extended_id=False
    )

    try:
        bus.send(message)
        print(f"Message sent on {channel}: {message}")
    except can.CanError:
        print("Message failed to send")

if __name__ == "__main__":
    # while True:
    #     send_can_message('can0', 0x157, [value[3], 0x02, 0x03])
    #     time.sleep(1)

    try:
        talker()
    except rospy.ROSInterruptException:
        pass
# print(value[3])
