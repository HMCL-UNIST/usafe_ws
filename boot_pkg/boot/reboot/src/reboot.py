#!/usr/bin/env python3

import glob
import os
import sys
import rospy

# from . import config
import subprocess
from std_msgs.msg import String

class reboot():
    def __init__(self) -> None:
        rospy.init_node('reboot', anonymous=True)
        # rospy.Subscriber("/global_waypoints_rviz", MarkerArray, self.tarjCallback)
        self.pub = rospy.Publisher('/this', String, queue_size=10)
        pkg = "preview_ctrl"
        launchfile = "preview_ctrl.launch"
        command = "roslaunch {0} {1}".format(pkg, launchfile)
        my_env = os.environ.copy()
        p = subprocess.Popen(command, shell=True, env=my_env)

    def main(self):
        r = rospy.Rate(10) # 10hz
        while not rospy.is_shutdown():
            self.pub.publish("hello world")
            r.sleep()


if __name__ == "__main__":
    b = reboot()
    b.main()