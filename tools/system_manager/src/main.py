#!/usr/bin/env python3

import glob
import os
import sys
import rospy
import shlex
import psutil
import signal
from std_msgs.msg import String, Bool


import subprocess

from subprocess import Popen, PIPE, TimeoutExpired
from threading import Thread
import sys
from signal import SIGINT
from datetime import datetime
import os

try:
    from queue import Queue, Empty
except ImportError:
    from Queue import Queue, Empty

def enque_output_err(out,queue): 
    # print("start err iter")
    for line in iter(out.readline(), b''):
        # queue.put(line)
        pub_syslog.publish(String(str(line[:-1].decode())))
        #print(line[:-1].decode())
        # print('get err line')
        print(line.decode('utf-8').rstrip())

    print("end web iter")
    out.close()

def enque_output(out,queue): 
    # print("start iter")
    for line in iter(out.readline, b''):
        # queue.put(line)
        pub_syslog.publish(String(str(line[:-1].decode())))
        #print(line[:-1].decode())
        # print('get line')
        print(line.decode('utf-8').rstrip())

    # print("end iter")
    out.close()


class SystemManager():
    def __init__(self) -> None:
        rospy.init_node('system_manager')

        self.process_start_sub = rospy.Subscriber("/usafe/starter",Bool,self.startercallback)
        self.process_stop_sub = rospy.Subscriber("/usafe/stopper",Bool,self.stoppercallback)
        self.main_timer = rospy.Timer(rospy.Duration(0.1), self.mainCallback)
        self.power_switch = False
        self.stop_switch = False
        
        self.tdr = None
        self.imu = None
        self.q=Queue()

    

    def initProcesses(self):
        if self.tdr is None:
            self.tdr = Popen(['roslaunch','tdr3000_driver','main.launch'],stdout=PIPE, stderr=PIPE)
            
            # q2=Queue()
            self.t_tdr= Thread(target=enque_output, args=(self.tdr.stdout,self.q))

            # roslaunch_subprocess.stdout.
            # t2= Thread(target=enque_output_err, args=(roslaunch_subprocess.stderr,q))

            self.t_tdr.daemon = True
            # t2.daemon = True
            self.t_tdr.start()
            # self.tdr = subprocess.Popen(['gnome-terminal -- source ~/usafe/install/setup.bash && roslaunch /home/hmcl/usafe/src/tools/tdr3000_driver/launch/main.launch'], shell=True)
            rospy.loginfo("TDR process open")
        # if self.imu is None:
        #     self.imu = subprocess.Popen(['gnome-terminal -- source ~/usafe/src/tools/configs/microstrain_init.sh'], shell=True)
        #     rospy.loginfo("IMU process open")

    def killProcesses(self):
        if self.tdr is not None:
            if psutil.pid_exists(self.tdr.pid):
                print("TDR process with pid %d exists" % self.tdr.pid)
                os.kill(self.tdr.pid, signal.SIGKILL)   
                rospy.loginfo("TDR process Kill")
            else:
                print("TDR process with pid %d does not exist" % self.tdr.pid)
            
        if self.imu is not None:
            if psutil.pid_exists(self.imu.pid):
                print("IMU process with pid %d exists" % self.imu.pid)
                os.kill(self.imu.pid, signal.SIGKILL) 
                rospy.loginfo("IMU process Kill")
            else:
                print("IMU process with pid %d does not exist" % self.imu.pid)
              

    def startercallback(self,msg):
        if self.stop_switch is not True:
            self.power_switch = msg.data
            if self.power_switch:
                rospy.loginfo("Power swtich actiavted")
                self.initProcesses()
            else:
                rospy.loginfo("Power swtich de-actiavted")
        else:
            rospy.loginfo("Stop switch activated")

    def stoppercallback(self,msg):
        self.stop_switch = msg.data
        if self.stop_switch:
            rospy.loginfo("Stop swtich actiavted")
            self.killProcesses()
        else:
            rospy.loginfo("Stop swtich de-activated")


    def mainCallback(self, timer):
        self.a = 2

  
if __name__ == "__main__":
    SysManager = SystemManager()
    try:
        rospy.spin()
    except rospy.ROSInterruptException:
        print("exception thrown")
        SysManager.killProcesses()


   