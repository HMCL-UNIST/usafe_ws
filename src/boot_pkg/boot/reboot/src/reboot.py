#!/usr/bin/env python3

import glob
import os
import sys
import rospy
import shlex
import psutil
import subprocess, signal
from std_msgs.msg import String

class reboot():
    def __init__(self) -> None:
        rospy.init_node('reboot', anonymous=True)
        # pkg = "preview_ctrl"
        # launchfile = "preview_ctrl.launch"
        # command = "roslaunch {0} {1}".format(pkg, launchfile)
        # my_env = os.environ.copy()
        # self.p = subprocess.Popen(command, shell=True, env=my_env)

        # pkg = "pid"
        # launchfile = "servo_sim.launch"
        # command = "roslaunch {0} {1}".format(pkg, launchfile)
        # my_env = os.environ.copy()
        # scc = subprocess.Popen(command, shell=True, env=my_env)


        self.scc=subprocess.Popen(['gnome-terminal -- roslaunch pid servo_sim.launch'], shell=True)
        self.preview=subprocess.Popen(['gnome-terminal -- roslaunch preview_ctrl preview_ctrl.launch'], shell=True)
        self.scc=subprocess.Popen(['gnome-terminal -- roslaunch lowlevel_ctrl lowlevel_ctrl.launch'], shell=True)
        self.preview=subprocess.Popen(['gnome-terminal -- roslaunch preview_ctrl preview_ctrl.launch'], shell=True)

        # os.system('gnome-terminal -- roslaunch pid servo_sim.launch')
        # os.system("gnome-terminal -- roslaunch preview_ctrl preview_ctrl.launch")


        

    def main(self):
        r = rospy.Rate(10) # 10hz
        cnt = 0
        while not rospy.is_shutdown():
            # if (cnt == 20):
            #     os.kill(self.scc.pid, signal.SIGKILL)
    
            if psutil.pid_exists(self.preview.pid):
                print("a process with pid %d exists" % self.preview.pid)
            else:
                print("a process with pid %d does not exist" % self.preview.pid)
            
            if psutil.pid_exists(self.scc.pid):
                print("a process with pid %d exists" % self.scc.pid)
            else:
                print("a process with pid %d does not exist" % self.scc.pid)
 
            cnt+=1
            # print(cnt)
            r.sleep()


if __name__ == "__main__":
    b = reboot()
    b.main()