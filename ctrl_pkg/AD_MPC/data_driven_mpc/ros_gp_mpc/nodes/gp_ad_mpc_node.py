#!/usr/bin/env python3.6
""" ROS node for the data-augmented MPC, to use in the Gazebo simulator and real world experiments.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.
"""

import json
import time
import rospy
import threading
import numpy as np
import pandas as pd
import math 
from tqdm import tqdm
from std_msgs.msg import Bool, Empty, Float64
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from ackermann_msgs.msg import AckermannDrive, AckermannDriveStamped 
from autoware_msgs.msg import Lane, Waypoint
from carla_msgs.msg import CarlaEgoVehicleStatus
from ad_mpc.create_ros_ad_mpc import ROSGPMPC
from ad_mpc.ad_3d import AD3D
from utils.utils import jsonify, interpol_mse, quaternion_state_mse, load_pickled_models, v_dot_q, \
    separate_variables
from utils.visualization import trajectory_tracking_results, mse_tracking_experiment_plot, \
    load_past_experiments, get_experiment_files
from experiments.point_tracking_and_record import make_record_dict, get_record_file_and_dir, check_out_data
from model_fitting.rdrv_fitting import load_rdrv

from utils.utils import quaternion_to_euler, skew_symmetric, v_dot_q, unit_quat, quaternion_inverse, wrap_to_pi, euler_to_quaternion, bound_angle_within_pi
from ad_mpc.ref_traj import RefTrajectory

from visualization_msgs.msg import MarkerArray, Marker

def clamp(n, minn, maxn):
    return max(min(maxn, n), minn)

class GPMPCWrapper:
    def __init__(self,environment="carla"):
        
        self.ad = AD3D(noisy=False, noisy_input= False)
        # Control at 50 (sim) or 60 (real) hz. Use time horizon=1 and 10 nodes
        self.n_mpc_nodes = rospy.get_param('~n_nodes', default=20.0)
        self.t_horizon = rospy.get_param('~t_horizon', default=2.0)
        self.traj_resample_vel = rospy.get_param('~traj_resample_vel', default=True)        
        self.control_freq_factor = rospy.get_param('~control_freq_factor', default=5 if environment == "carla" else 5)
        self.dt = self.t_horizon / self.n_mpc_nodes
        self.opt_dt = self.t_horizon / (self.n_mpc_nodes * self.control_freq_factor)
#################################################################        
        # Initialize GP MPC for point tracking
        self.gp_mpc = ROSGPMPC(self.t_horizon, self.n_mpc_nodes, self.opt_dt)     
        self.mpc_ready = True   
#################################################################
        self.mpc_safe_count_threshold = 10  ## 
        self.mpc_safe_count = 0
        self.solver_status = 0 # 0= feasible, #else = error(infeasible)        
        # Last state obtained from odometry
        self.x = None
        self.velocity = None
        self.steering = None
        
        self.steering_min = self.ad.steering_min
        self.steering_max = self.ad.steering_max
        self.steering_rate_min = self.ad.steering_rate_min
        self.steering_rate_max = self.ad.steering_rate_max

        self.environment = environment
        # Elapsed time between two recordings
        self.last_update_time = time.time()

        # Last references. Use hovering activation as input reference
        self.last_x_ref = None
        self.last_u_ref = None

        self.odom_available = False  
        
        # Reference trajectory variables
        self.x_ref = None
        self.t_ref = None
        self.u_ref = None
        self.current_idx = 0
        # self.ad_trajectory = None
        # self.ad_controls = None
        # self.w_control = None
        
        # set up reference generator
        self.ref_gen = RefTrajectory(traj_horizon=self.n_mpc_nodes, traj_dt=self.t_horizon/self.n_mpc_nodes)

        # To measure optimization elapsed time
        self.optimization_dt = 0

        # Thread for MPC optimization
        self.mpc_thread = threading.Thread()

        # check topic availability
        self.vehicle_status_available = False
        self.pose_available = False 
        self.waypoint_available = False 
        # Binary variable to run MPC only once every other odometry callback
        self.optimize_next = True

        #  Remember the sequence number of the last odometry message received.
        self.last_odom_seq_number = 0

        # Setup node publishers and subscribers. The odometry (sub) and control (pub) topics will vary depending on
        # Assume Carla simulation environment         
        if self.environment == "carla":            
            # pose_topic = "/state_estimator/estimated_pose"
            pose_topic = "/current_pose"            
            vehicle_status_topic = "/carla/ego_vehicle/vehicle_status"
            control_topic = "/carla/ego_vehicle/ackermann_cmd"            
            waypoint_topic = "/final_waypoints"
            sim_odom_topic = "/carla/ego_vehicle/odometry"
        else:
            # Real world setup
            pose_topic = "/ndt_pose"
            vehicle_status_topic = "/hmcl_vehicle_status"
            control_topic = "/hmcl_ctrl_cmd"            
            waypoint_topic = "/final_waypoints"
        
        status_topic = "/is_mpc_busy"
        # Publishers
        self.control_pub = rospy.Publisher(control_topic, AckermannDrive, queue_size=1, tcp_nodelay=True)
        self.ref_puf_publisher = rospy.Publisher("/mpc_ref_trajectory", MarkerArray, queue_size=1)
        self.mpc_predicted_trj_publisher = rospy.Publisher("/mpc_pred_trajectory", MarkerArray, queue_size=1)
        self.final_ref_publisher = rospy.Publisher("/final_trajectory", MarkerArray, queue_size=1)
        self.status_pub = rospy.Publisher(status_topic, Bool, queue_size=1)
        self.steering_pub = rospy.Publisher("/mpc_steering", Float64, queue_size=1)
        # Subscribers
        self.pose_sub = rospy.Subscriber(pose_topic, PoseStamped, self.pose_callback)
        self.vehicle_status_sub = rospy.Subscriber(vehicle_status_topic, CarlaEgoVehicleStatus, self.vehicle_status_callback)
        self.waypoint_sub = rospy.Subscriber(waypoint_topic, Lane, self.waypoint_callback)
        self.odom_sub = rospy.Subscriber(sim_odom_topic, Odometry, self.odom_callback)
        self.blend_min = 3
        self.blend_max = 5

        rate = rospy.Rate(1)
     
        while not rospy.is_shutdown():
            # Publish if MPC is busy with a current trajectory
            msg = Bool()
            msg.data = not (self.x_ref is None and self.pose_available)
            self.status_pub.publish(msg)
            rate.sleep()

    def reset_mpc_optimizer(self):
        del self.gp_mpc
        self.mpc_ready = False
        self.gp_mpc = ROSGPMPC(self.t_horizon, self.n_mpc_nodes, self.opt_dt)        
        self.mpc_ready = True
    
    def run_mpc(self, odom, x_ref,y_ref,psi_ref,vel_ref, recording=True):
        """
        :param odom: message from subscriber.
        :type odom: Odometry
        :param recording: If False, some messages were skipped between this and last optimization. Don't record any data
        during this optimization if in recording mode.
        """
        if not self.pose_available or not self.vehicle_status_available:
            return
        if not self.waypoint_available:
            return
        # Measure time between initial state was checked in and now
        dt = odom.header.stamp.to_time() - self.last_update_time

        # model_data, x_guess, u_guess = self.set_reference()         --> previous call
        if len(x_ref) < self.n_mpc_nodes:
            ref = [x_ref[-1], y_ref[-1], psi_ref[-1], 0.0, 0.0, 0.0, 0.0]
            u_ref = [0.0, 0.0]   
            terminal_point = True               
        else:        
            ref = np.zeros([7,len(x_ref)])
            ref[0] = x_ref
            ref[1] = y_ref
            ref[2] = psi_ref
            ref[3] = vel_ref
            ref = ref.transpose()
            u_ref = np.zeros((len(vel_ref)-1,2))
            terminal_point = False
        
        model_data = self.gp_mpc.set_reference(ref,u_ref,terminal_point)        
    
        if self.mpc_ready is False: 
            return
        # Run MPC and publish control
        try:
            tic = time.time()            
            next_control, w_opt, x_opt, self.solver_status = self.gp_mpc.optimize(model_data)
            ####################################
            if x_opt is not None:                
                self.predicted_trj_visualize(x_opt)
            ####################################
            ## Check whether the predicted trajectory is close to the actual reference trajectory // if not apply auxillary control
            self.pred_trj_healthy = self.check_pred_trj(x_opt,ref)
            

            if self.solver_status > 0:                                
                self.mpc_safe_count = 0
                self.reset_mpc_optimizer()                
            else: 
                self.mpc_safe_count = self.mpc_safe_count + 1
            ###### check the number of success rounds of the MPC optimization
            if self.mpc_safe_count < self.mpc_safe_count_threshold:
                return

            if not self.pred_trj_healthy:
                return

            self.optimization_dt += time.time() - tic
            print("MPC thread. Seq: %d. Topt: %.4f" % (odom.header.seq, (time.time() - tic) * 1000))            
            control_msg = AckermannDrive()
            control_msg = next_control.drive                                                                     
            steering_val = max(min(self.steering_rate_max, next_control.drive.steering_angle_velocity), self.steering_rate_min)                        
            control_msg.steering_angle = max(min(self.steering_max, steering_val*0.1 + self.steering), self.steering_min)                        
            tt_steering = Float64()
            tt_steering.data = -1*control_msg.steering_angle            
            # control_msg.acceleration = -110.0
            self.steering_pub.publish(tt_steering)            
            self.control_pub.publish(control_msg)            
            

        except KeyError:
            self.recording_warmup = True
            # Should not happen anymore.
            rospy.logwarn("Tried to run an MPC optimization but MPC is not ready yet.")
            return

        if w_opt is not None:            
            self.w_opt = w_opt            

   
    def check_pred_trj(self,x_opt, ref):
        # the average distance between reference and the predicted trj le
        tmp_dist = np.zeros(len(ref))        
        for i in range(0,len(ref)-1):
            tmp_dist[i] = math.sqrt((ref[i,0] - x_opt[i,0])**2+(ref[i,1] - x_opt[i,1])**2)
    
        if np.mean(tmp_dist) < 3.0 and np.cov(tmp_dist) < 2 and np.max(tmp_dist) < 4:
            return True
        else:
            return False
        

    def vehicle_status_callback(self,msg):
        if msg.velocity is None:
            return
        self.velocity = msg.velocity
        self.steering = -msg.control.steer

        if self.vehicle_status_available is False:
            self.vehicle_status_available = True        

    def predicted_trj_visualize(self,predicted_state):
        
        marker_refs = MarkerArray() 
        for i in range(len(predicted_state[:,0])):
            marker_ref = Marker()
            marker_ref.header.frame_id = "map"  
            marker_ref.ns = "mpc_ref"+str(i)
            marker_ref.id = i
            marker_ref.type = Marker.ARROW
            marker_ref.action = Marker.ADD                
            marker_ref.pose.position.x = predicted_state[i,0] 
            marker_ref.pose.position.y = predicted_state[i,1]              
            quat_tmp = euler_to_quaternion(0.0, 0.0, predicted_state[i,2])     
            quat_tmp = unit_quat(quat_tmp)                 
            marker_ref.pose.orientation.w = quat_tmp[0]
            marker_ref.pose.orientation.x = quat_tmp[1]
            marker_ref.pose.orientation.y = quat_tmp[2]
            marker_ref.pose.orientation.z = quat_tmp[3]
            marker_ref.color.r, marker_ref.color.g, marker_ref.color.b = (255, 255, 0)
            marker_ref.color.a = 0.5
            marker_ref.scale.x, marker_ref.scale.y, marker_ref.scale.z = (0.6, 0.4, 0.3)
            marker_refs.markers.append(marker_ref)
            i+=1
        self.mpc_predicted_trj_publisher.publish(marker_refs)
        
    def waypoint_visualize(self,x_ref,y_ref,psi_ref):
        
        marker_refs = MarkerArray() 
        for i, xx in enumerate(x_ref):
            marker_ref = Marker()
            marker_ref.header.frame_id = "map"  
            marker_ref.ns = "mpc_ref"+str(i)
            marker_ref.id = i
            marker_ref.type = Marker.ARROW
            marker_ref.action = Marker.ADD                
            marker_ref.pose.position.x = x_ref[i] 
            marker_ref.pose.position.y = y_ref[i]              
            quat_tmp = euler_to_quaternion(0.0, 0.0, psi_ref[i])     
            quat_tmp = unit_quat(quat_tmp)                 
            marker_ref.pose.orientation.w = quat_tmp[0]
            marker_ref.pose.orientation.x = quat_tmp[1]
            marker_ref.pose.orientation.y = quat_tmp[2]
            marker_ref.pose.orientation.z = quat_tmp[3]
            marker_ref.color.r, marker_ref.color.g, marker_ref.color.b = (255, 0, 0)
            marker_ref.color.a = 0.5
            marker_ref.scale.x, marker_ref.scale.y, marker_ref.scale.z = (0.8, 0.3, 0.2)
            marker_refs.markers.append(marker_ref)
            i+=1
        self.ref_puf_publisher.publish(marker_refs)
    
    def final_waypoint_visualize(self):
        marker_refs = MarkerArray() 
        for i, x_ref in enumerate(self.x_ref):
            marker_ref = Marker()
            marker_ref.header.frame_id = "map"  
            marker_ref.ns = "mpc_ref"+str(i)
            marker_ref.id = i
            marker_ref.type = Marker.ARROW
            marker_ref.action = Marker.ADD                
            marker_ref.pose.position.x = self.x_ref[i] 
            marker_ref.pose.position.y = self.y_ref[i]              
            quat_tmp = euler_to_quaternion(0.0, 0.0, self.psi_ref[i])                      
            quat_tmp = unit_quat(quat_tmp)
            marker_ref.pose.orientation.w = quat_tmp[0]
            marker_ref.pose.orientation.x = quat_tmp[1]
            marker_ref.pose.orientation.y = quat_tmp[2]
            marker_ref.pose.orientation.z = quat_tmp[3]
            marker_ref.color.r, marker_ref.color.g, marker_ref.color.b = (0, 0, 255)
            marker_ref.color.a = 0.5
            marker_ref.scale.x, marker_ref.scale.y, marker_ref.scale.z = (0.5, 0.4, 0.3)
            marker_refs.markers.append(marker_ref)
            i+=1
        self.final_ref_publisher.publish(marker_refs)
    


    def waypoint_callback(self, msg):
        """
        :type msg: autoware_msgs/Lane 
        """                        
        msg.waypoints = msg.waypoints[1:-1]
        if not self.waypoint_available:
            self.waypoint_available = True
        
        self.x_ref = [msg.waypoints[i].pose.pose.position.x for i in range(len(msg.waypoints))]
        self.y_ref = [msg.waypoints[i].pose.pose.position.y for i in range(len(msg.waypoints))]                        
        quat_to_euler_lambda = lambda o: quaternion_to_euler([o[0], o[1], o[2], o[3]])            
        self.psi_ref = [wrap_to_pi(quat_to_euler_lambda([msg.waypoints[i].pose.pose.orientation.w,msg.waypoints[i].pose.pose.orientation.x,msg.waypoints[i].pose.pose.orientation.y,msg.waypoints[i].pose.pose.orientation.z])[2]) for i in range(len(msg.waypoints))]                                    
        
        self.vel_ref = [msg.waypoints[i].twist.twist.linear.x for i in range(len(msg.waypoints))]
 
        while len(self.x_ref) < self.n_mpc_nodes:
            self.x_ref.insert(-1,self.x_ref[-1])
            self.y_ref.insert(-1,self.y_ref[-1])
            self.psi_ref.insert(-1,self.psi_ref[-1])
            self.vel_ref.insert(-1,self.vel_ref[-1])

        self.ref_gen.set_traj(self.x_ref, self.y_ref, self.psi_ref, self.vel_ref)
        
        
    def odom_callback(self, msg):
        if self.odom_available is False:
            self.odom_available = True  
        self.v_x = msg.twist.twist.linear.x 
        self.v_y = msg.twist.twist.linear.y
        self.psi_dot = msg.twist.twist.angular.z
                

    def pose_callback(self, msg):
        """                
        :type msg: PoseStamped
        """      
        if self.velocity is None or not self.odom_available or not self.waypoint_available:
            return        

        self.cur_x = msg.pose.position.x
        self.cur_y = msg.pose.position.y
        self.cur_z = msg.pose.position.z                
        cur_euler = quaternion_to_euler([msg.pose.orientation.w,msg.pose.orientation.x,msg.pose.orientation.y,msg.pose.orientation.z])            
        self.cur_yaw = wrap_to_pi(cur_euler[2])        
        
        p_x = [self.cur_x]
        p_y = [self.cur_y]
        psi = [self.cur_yaw] 
        v_x = [self.v_x]
        v_y = [self.v_y]
        psi_dot = [self.psi_dot]        
        steering = [self.steering]

        self.x = p_x+p_y+psi+v_x+v_y+psi_dot+steering
        
        try:
            if self.mpc_ready:
                # Update the state estimate of the AD
                self.gp_mpc.set_state(self.x)
                # reset the reference traj 
                if not self.waypoint_available:
                    return
                
                waypoint_dict = self.ref_gen.get_waypoints(p_x[0], p_y[0], psi[0])
                
                x_ref    = waypoint_dict['x_ref']            
                y_ref    = waypoint_dict['y_ref']
                psi_ref = waypoint_dict['psi_ref']        
                vel_ref = waypoint_dict['v_ref']                  
                    
                self.waypoint_visualize(x_ref,y_ref,psi_ref)
            
        except AttributeError:
            rospy.loginfo("mpc_node......set_state fail")
            return

        if self.pose_available is False:
            self.pose_available = True        

        # run mpc 
        def _thread_func():
            self.run_mpc(msg,x_ref,y_ref,psi_ref,vel_ref)            
        
        self.mpc_thread = threading.Thread(target=_thread_func(), args=(), daemon=True)
        self.mpc_thread.start()
        self.mpc_thread.join()
        self.last_odom_seq_number = msg.header.seq
        self.optimize_next = False
        
        def _aux_thread_func():
                self.run_pure(msg,x_ref,y_ref,psi_ref,vel_ref)
        
        if self.mpc_safe_count < self.mpc_safe_count_threshold or not self.pred_trj_healthy:         
            # implement auxilary controller (e.g. PID)             
            self.pure_thread = threading.Thread(target=_aux_thread_func(), args=(), daemon=True)
            self.pure_thread.start()
            self.pure_thread.join()
    
    def run_pure(self, odom, x_ref,y_ref,psi_ref,vel_ref, recording=True):
        if not self.pose_available or not self.vehicle_status_available:
            return
        if not self.waypoint_available:
            return
        # Measure time between initial state was checked in and now
        dt = odom.header.stamp.to_time() - self.last_update_time        
        ref = np.zeros([7,len(x_ref)])
        ref[0] = x_ref
        ref[1] = y_ref
        ref[2] = psi_ref
        ref[3] = vel_ref
        ref = ref.transpose()
        
        # Run MPC and publish control
        try:
            tic = time.time()                        
            control_msg = AckermannDrive()                        
            control_msg.steering_angle =  self.steering 
            control_msg.acceleration = -1e5          
            self.control_pub.publish(control_msg)            
            

        except KeyError:            
            # Should not happen anymore.
            rospy.logwarn("Tried to run an auximlary controller is not ready yet.")
            return
    
        
###################################################################################

def main():
    rospy.init_node("gp_mpc")
    env = rospy.get_param('~environment', default='gazebo')
    GPMPCWrapper(env)

if __name__ == "__main__":
    main()
