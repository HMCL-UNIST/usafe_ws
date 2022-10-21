#!/usr/bin/env python3

import glob
import os
import sys
import rospy
import shlex
import psutil
import signal
from std_msgs.msg import String, Bool, Float64
from can_msgs.msg import Frame
from sensor_msgs.msg import NavSatFix, Imu, PointCloud2
from nav_msgs.msg import Odometry
import subprocess
from geometry_msgs.msg import PoseStamped

from subprocess import Popen, PIPE, TimeoutExpired, call
from threading import Thread, Lock

import sys
from signal import SIGINT
from datetime import datetime
import os


from dynamic_reconfigure.server import Server
# from system_manager.cfg import sysConfig

sys.path.append('/home/hmcl/usafe/install/system_manager/lib/python2.7/dist-packages/system_manager')
from cfg import sysConfig


try:
    from queue import Queue, Empty
except ImportError:
    from Queue import Queue, Empty
mutex = Lock()
def enque_output_err(out,queue): 
    # print("start err iter")
    for line in iter(out.readline(), b''):
        # queue.put(line)
        rospy.loginfo(str(line[:-1].decode()))
        #print(line[:-1].decode())
        # print('get err line')
        print(line.decode('utf-8').rstrip())

    # print("end web iter")
    out.close()

def enque_output(out,queue): 
    # print("start iter")
    for line in iter(out.readline, b''):
        # queue.put(line)
        rospy.loginfo(str(line[:-1].decode()))
        #print(line[:-1].decode())
        # print('get line')
        print(line.decode('utf-8').rstrip())

    # print("end iter")
    out.close()


class SystemManager():
    def __init__(self) -> None:
        rospy.init_node('system_manager')

    
            
        
        self.power_switch = False
        self.stop_switch = False
        
                
        self.can_init = None
        self.can = None
        self.imu = None
        self.tdr = None
        self.pid = None
        self.preview = None
        self.usafe = None
        self.v2x = None
        self.fix2pose = None
        self.estimator = None
        self.lowlevel = None
        self.fast = None
        self.lidar = None

        self.imu_switch = False
        self.can_switch = False
        self.tdr_switch = False
        self.vel_switch = False
        self.preview_switch = False
        self.usafe_switch = False
        self.v2x_switch = False
        self.fix2pose_switch = False
        self.estimator_switch = False
        self.lowlevel_switch = False

        self.sensor_ready = False

        self.process_start_sub = rospy.Subscriber("/usafe/starter",Bool,self.startercallback)
        self.process_stop_sub = rospy.Subscriber("/usafe/stopper",Bool,self.stoppercallback)
        


        # self.main_timer = rospy.Timer(rospy.Duration(0.1), self.mainCallback)
        self.cleanROSLog()
        rospy.sleep(1)
        rospy.loginfo("cleaning ros log")
        self.init_process()

        #self.srv = Server(sysConfig, self.dyn_callback)
    
    # def dyn_callback(self,config, level):
    #     mutex.acquire()
    #     self.imu_switch = config.Power_imu
    #     self.can_switch = config.Power_can
    #     self.tdr_switch = config.Power_tdr
    #     self.vel_switch = config.Power_vel
    #     self.preview_switch = config.Power_preview
    #     self.usafe_switch = config.Power_usafe
    #     self.v2x_switch = config.Power_v2x
    #     self.fix2pose_switch = config.Power_fix2pose
    #     self.estimator_switch = config.Power_estimator
    #     self.lowlevel_switch = config.Power_lowlevel

    #     if self.lowlevel_switch:
    #         self.initLowCtrl()
    #     else:
    #         self.killLowCtrl()

    #     if self.estimator_switch:
    #         self.initEstimator()
    #     else:
    #         self.killEstimator()
        
    #     if self.fix2pose_switch:
    #         self.initFix2pose()
    #     else:
    #         self.killFix2pose()

    #     if self.imu_switch:
    #         self.initIMU()
    #     else:
    #         self.killIMU()

    #     if self.can_switch:
    #         self.initCAN()
    #     else:
    #         self.killCAN()

    #     if self.tdr_switch:
    #         self.initTDR()
    #     else:
    #         self.killTDR()

    #     if self.vel_switch:
    #         self.initPID()
    #     else:
    #         self.killPID()

    #     if self.preview_switch:
    #         self.initPREVIEW()
    #     else:
    #         self.killPREVIEW()

    #     if self.usafe_switch:
    #         self.initUSAFE()
    #     else:
    #         self.killUSAFE()

    #     if self.v2x_switch:
    #         self.initV2X()
    #     else:
    #         self.killV2X()

    #     mutex.release()
    #     return config
    def initLidar(self):
        self.qlidar=Queue()
        self.lidar = Popen(['/home/hmcl/commands/lidar_xavier3'],stdout=PIPE, stderr=PIPE)
        self.t_lidar= Thread(target=enque_output, args=(self.lidar.stdout,self.qlidar))
        self.t_lidar.daemon = True            
        self.t_lidar.start()            
        rospy.logwarn("Xavier Lidar process open")


    def initFastlio(self):
        self.qfast=Queue()
        self.fast = Popen(['roslaunch','fast_lio','high_mapping_ouster64.launch'])
        # self.t_fast= Thread(target=enque_output, args=(self.fast.stdout,self.qfast))
        # self.t_fast.daemon = True            
        # self.t_fast.start()            
        rospy.logwarn("Fastlio process power on")

    def cleanROSLog(self):
        self.qclean=Queue()
        self.clean = Popen(['rosclean','purge','-y'],stdout=PIPE, stderr=PIPE)
        self.t_clean= Thread(target=enque_output, args=(self.clean.stdout,self.qclean))
        self.t_clean.daemon = True            
        self.t_clean.start()            
        rospy.logwarn("ROS Log Clean process open")
    
    def initEstimator(self):
        if self.estimator is None:
            self.qestimator=Queue()
            # self.estimator = Popen(['roslaunch','gnss_estimator','gnss_stateEstimator.launch'],stdout=PIPE, stderr=PIPE)
            self.estimator = Popen(['roslaunch','speedy_estimator','high_newSE.launch'])
            # self.t_estimator= Thread(target=enque_output, args=(self.estimator.stdout,self.qestimator))
            # self.t_estimator.daemon = True            
            # self.t_estimator.start()            
            rospy.loginfo("Estimator process open")


    def initFix2pose(self):
        if self.fix2pose is None:
            self.qfix2pose=Queue()
            self.fix2pose = Popen(['roslaunch','gnss_fix2pose','gnss_fix2pose.launch'],stdout=PIPE, stderr=PIPE)
            self.t_fix2pose= Thread(target=enque_output, args=(self.fix2pose.stdout,self.qfix2pose))
            self.t_fix2pose.daemon = True            
            self.t_fix2pose.start()            
            rospy.loginfo("fix2pose process open")


    def initV2X(self):
        if self.v2x is None:
            self.qv2x=Queue()
            self.v2x = Popen(['roslaunch','hmcl_v2x','mission2.launch'],stdout=PIPE, stderr=PIPE)
            self.t_v2x= Thread(target=enque_output, args=(self.v2x.stdout,self.qv2x))
            self.t_v2x.daemon = True            
            self.t_v2x.start()            
            rospy.loginfo("V2X process open")


    def initUSAFE(self):
        if self.usafe is None:
            self.qusafe=Queue()
            self.usafe = Popen(['roslaunch','usafe','usafe.launch'],stdout=PIPE, stderr=PIPE)
            self.t_usafe= Thread(target=enque_output, args=(self.usafe.stdout,self.qusafe))
            self.t_usafe.daemon = True            
            self.t_usafe.start()            
            rospy.loginfo("Usafe process open")

    def initPREVIEW(self):
        if self.preview is None:
            self.qpreview=Queue()
            self.preview = Popen(['roslaunch','highspeed_ctrl','highspeed_ctrl.launch'],stdout=PIPE, stderr=PIPE)
            self.t_preview= Thread(target=enque_output, args=(self.preview.stdout,self.qpreview))
            self.t_preview.daemon = True            
            self.t_preview.start()            
            rospy.loginfo("Highspeed Ctrl process open")

    def initPID(self):
        if self.pid is None:
            self.qpid=Queue()
            self.pid = Popen(['roslaunch','pid','servo_sim.launch'],stdout=PIPE, stderr=PIPE)
            self.t_pid= Thread(target=enque_output, args=(self.pid.stdout,self.qpid))
            self.t_pid.daemon = True            
            self.t_pid.start()            
            rospy.loginfo("PID process open")
        
    def initCAN(self):
        if self.can is None:
            self.qcan_init=Queue()
            self.can_init = Popen(['bash','/home/hmcl/usafe/src/tools/canopen/socketcan_bridge/src/can2.sh'], stdout=PIPE)
            self.t_can_init= Thread(target=enque_output, args=(self.can_init.stdout,self.qcan_init))
            self.t_can_init.daemon = True            
            self.t_can_init.start()    
            rospy.loginfo("CAN Init process open")        
            
            self.qcan=Queue()
            self.can = Popen(['roslaunch','socketcan_bridge','socketcan_bridge.launch'],stdout=PIPE, stderr=PIPE)
            self.t_can= Thread(target=enque_output, args=(self.can.stdout,self.qcan))
            self.t_can.daemon = True            
            self.t_can.start()            
            rospy.loginfo("CAN process open")

    def initIMU(self):
        if self.imu is None:
            self.qimu=Queue()
            self.imu = Popen(['bash','/home/hmcl/usafe/src/tools/configs/microstrain_init.sh'],stdout=PIPE, stderr=PIPE)
            self.t_imu= Thread(target=enque_output, args=(self.imu.stdout,self.qimu))
            self.t_imu.daemon = True            
            self.t_imu.start()            
            rospy.loginfo("IMU process open")

    def initTDR(self):
        if self.tdr is None:
            self.qtdr=Queue()
            self.tdr = Popen(['roslaunch','tdr3000_driver','main.launch'],stdout=PIPE, stderr=PIPE)
            self.t_tdr= Thread(target=enque_output, args=(self.tdr.stdout,self.qtdr))
            self.t_tdr.daemon = True            
            self.t_tdr.start()            
            rospy.loginfo("TDR process open")

    def initLowCtrl(self):
        if self.lowlevel is None:
            self.qlowlevel=Queue()
            self.lowlevel = Popen(['roslaunch','highspeed_lowlevel_ctrl','highspeed_lowlevel_ctrl.launch'])
            # self.t_lowlevel= Thread(target=enque_output, args=(self.lowlevel.stdout,self.qlowlevel))
            # self.t_lowlevel.daemon = True            
            # self.t_lowlevel.start()            
            rospy.loginfo("lowlevel Ctrl process open")
    
        
    def killFastLio(self):
        if self.fast is not None:
            try:
                self.fast.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.fast.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.fast.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("Fastlio process END")
            self.fast = None

       
    def killLowCtrl(self):
        if self.lowlevel is not None:
            try:
                self.lowlevel.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.lowlevel.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.lowlevel.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("Lowlevel Ctrl process END")
            self.lowlevel = None
    
    def killFix2pose(self):
        if self.fix2pose is not None:
            try:
                self.fix2pose.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.fix2pose.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.fix2pose.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("Fix2pose process END")
            self.fix2pose = None


    def killEstimator(self):
        if self.estimator is not None:
            try:
                self.estimator.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.estimator.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.estimator.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("Estimator process END")
            self.estimator = None

    def killV2X(self):
        if self.v2x is not None:
            try:
                self.v2x.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.v2x.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.v2x.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("V2X process END")
            self.v2x = None

    def killUSAFE(self):
        if self.usafe is not None:
            try:
                self.usafe.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.usafe.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.usafe.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("USAFE process END")
            self.usafe = None

    def killPREVIEW(self):
        if self.preview is not None:
            try:
                self.preview.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.preview.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.preview.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("Highspeed Ctrl process END")
            self.preview = None

    def killPID(self):
        if self.pid is not None:
            try:
                self.pid.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.pid.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.pid.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("PID process END")
            self.pid = None

    def killCAN(self):
        if self.can is not None:
            try:
                self.can.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.can.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.can.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("CAN process END")
            self.can = None

    def killIMU(self):
        if self.imu is not None:
            try:
                self.imu.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.imu.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.imu.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("IMU process END")
            self.imu = None

    def killTDR(self):
        if self.tdr is not None:
            try:
                self.tdr.communicate(timeout=1)
            except TimeoutExpired:
                print('communicate pass')
            
            print('sending sigint',datetime.now().strftime("%H:%M:%S"))
            self.tdr.send_signal(SIGINT)
            print('subprocess.communicate',datetime.now().strftime("%H:%M:%S"))
            self.tdr.communicate()
            print('turned off!',datetime.now().strftime("%H:%M:%S"))      
            rospy.loginfo("TDR process END")
            self.tdr = None


    

    def startercallback(self,msg):
        if self.stop_switch is not True:
            self.power_switch = msg.data
            if self.power_switch:
                rospy.loginfo("Power swtich actiavted")                
                self.init_controller()                
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


    def init_controller(self):

        rospy.sleep(1)
        self.initPREVIEW()       

        preview_debug_msg = None
        while preview_debug_msg is None:
            try:
                preview_debug_msg = rospy.wait_for_message('/preview_debug', PoseStamped, timeout=1)
            except:
                pass
        rospy.logwarn("Preview Ctrl Activated")

        

        rospy.sleep(1)
        self.initLowCtrl()

        can_receive_msg = None
        while can_receive_msg is None:
            try:
                can_receive_msg = rospy.wait_for_message('/driving_gui', String, timeout=1)
            except:
                pass
        rospy.logwarn("Lowlevel received")
        rospy.logwarn("SYSTEM IS READY!!!!!!!!!!!!!!!!!!!")

    
    def init_process(self):
        
        self.initLidar()
        lidar_msg = None 
        while lidar_msg is None:
            try:
                lidar_msg = rospy.wait_for_message('/os_cloud_node/points', PointCloud2, timeout=1)
            except:
                pass
        
        rospy.logwarn("Lidar point cloud received")

        ## FAST LIO turn on 
        self.initFastlio()
        fastlio_msg = None 
        while fastlio_msg is None:
            try:
                fastlio_msg = rospy.wait_for_message('/Odometry', Odometry, timeout=1)
            except:
                pass
        
        rospy.logwarn("FastLio on")
        
        
        #######################################
        
        self.initTDR()        

        fix_msg = None
        while fix_msg is None:
            try:
                fix_msg = rospy.wait_for_message('/fix', NavSatFix, timeout=1)
            except:
                pass
            
        rospy.logwarn("GNSS received")
        rospy.sleep(1)
        
        self.initCAN()
        

        can_msg = None
        while can_msg is None:
            try:
                can_msg = rospy.wait_for_message('/a_can_l2h', Frame, timeout=1)
            except:
                pass

        rospy.logwarn("CAN received")

        
        
        rospy.sleep(1)
        self.initIMU()
        
        imu_msg = None
        while imu_msg is None:
            try:
                imu_msg = rospy.wait_for_message('/imu/data', Imu, timeout=1)
            except:
                pass
        rospy.logwarn("IMU received")
        rospy.sleep(1)



        self.initFix2pose()

        pose_msg = None
        while pose_msg is None:
            try:
                pose_msg = rospy.wait_for_message('/gnss_pose_world', PoseStamped, timeout=1)
            except:
                pass
        rospy.sleep(1)


        

        ## State estimator on 
        self.initEstimator()
        
        odom_msg = None
        while odom_msg is None:
            try:
                odom_msg = rospy.wait_for_message('/pose_estimate', Odometry, timeout=1)
            except:
                pass
        rospy.logwarn("Pose estimate received")
        


        rospy.sleep(1)
        self.initPID()
        control_effort_msg = None
        while control_effort_msg is None:
            try:
                control_effort_msg = rospy.wait_for_message('/control_effort', Float64, timeout=1)
            except:
                pass
        rospy.logwarn("PID Ctrl Activated")

        rospy.sleep(1)
        self.initV2X()
        pvd_status_msg = None
        while pvd_status_msg is None:
            try:
                pvd_status_msg = rospy.wait_for_message('/pvd_status', Float64, timeout=1)
            except:
                pass
        rospy.logwarn("V2X PVD Activated")

        v2x_status_msg = None
        while v2x_status_msg is None:
            try:
                v2x_status_msg = rospy.wait_for_message('/v2x_mission_status', Float64, timeout=1)
            except:
                pass
        rospy.logwarn("V2X Mission Node Activated")

        
        rospy.sleep(1)
        self.initUSAFE()
        usafe_light_msg = None
        while usafe_light_msg is None:
            try:
                usafe_light_msg = rospy.wait_for_message('/light_cmd', Float64, timeout=1)
            except:
                pass
        rospy.logwarn("USAFE Planner Activated")
            
        


        
        
        
    def killProcesses(self):
        self.killLowCtrl() 
        self.killTDR()
        self.killIMU()
        self.killCAN()
        self.killPID()
        self.killPREVIEW()
        self.killUSAFE()
        self.killV2X()
        self.killEstimator()
        self.killFix2pose()
        self.killFastLio()
        

    # def mainCallback(self, timer):

        # if self.sensor_ready is not True:
        #     self.init_setup():
        

  
if __name__ == "__main__":
    SysManager = SystemManager()
    try:
        rospy.spin()
    except rospy.ROSInterruptException:
        print("exception thrown")
        SysManager.killProcesses()


   