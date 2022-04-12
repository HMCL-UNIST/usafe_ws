""" Class for interfacing the data-augmented MPC with ROS.

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

from numpy.lib import add_docstring
from rospy.core import add_preshutdown_hook
from utils.utils import parse_xacro_file
from ad_mpc.ad_3d import AD3D
from ad_mpc.ad_3d_mpc import AD3DMPC
import numpy as np
import std_msgs.msg
import rospy
import os
from ackermann_msgs.msg import AckermannDrive, AckermannDriveStamped


def custom_ad_param_loader(ad_name):

    # this_path = os.path.dirname(os.path.realpath(__file__))
    # params_file = os.path.join(this_path, '..', '..', 'config', ad_name + '.xacro')
    # # Get parameters for AD
    # attrib = parse_xacro_file(params_file)
    ad = AD3D(noisy=False, noisy_input= False)
    # ad.mass = float(attrib['mass']) + float(attrib['mass_rotor']) * 4
    # ad.J = np.array([float(attrib['body_inertia'][0]['ixx']),
    #                    float(attrib['body_inertia'][0]['iyy']),
    #                    float(attrib['body_inertia'][0]['izz'])])
    
    return ad


class ROSGPMPC:
    def __init__(self, t_horizon, n_mpc_nodes, opt_dt, ad_name = "sim_car", point_reference=False):

        ad = custom_ad_param_loader(ad_name)  

        # Initialize quad MPC
        if point_reference:
            acados_config = {
                "solver_type": "SQP",
                "terminal_cost": True
            }
        else:
            acados_config = {
                "solver_type": "SQP_RTI",
                "terminal_cost": False
            }
                            #  p_x,  p_y, psi, v_x, v_y, psi_dot, delta 
        q_diagonal = np.array([10.0, 10.0,  500.0, 0.0, 0.0, 0.0,   10.0])
        r_diagonal = np.array([1, 5.0])   

        ad_mpc = AD3DMPC(ad, t_horizon=t_horizon, optimization_dt=opt_dt, n_nodes=n_mpc_nodes, 
                            model_name=ad_name, solver_options=acados_config, q_cost=q_diagonal, r_cost=r_diagonal)

        self.ad_name = ad_name
        self.ad = ad
        self.ad_mpc = ad_mpc

        # Last optimization
        self.last_w = None

    def set_state(self, x):
        """
        Set state estimate from an odometry measurement
        :param x: measured state from odometry. List with 13 components with the format: [p_xyz, q_wxyz, v_xyz, w_xyz]
        """
        self.ad.set_state(x)

    def set_reference(self, x_ref, u_ref, terminal_point = False):
        """
        Set a reference state for the optimizer.
        :param x_ref: list with 4 sub-components (position, angle quaternion, velocity, body rate). If these four
        are lists, then this means a single target point is used. If they are Nx3 and Nx4 (for quaternion) numpy arrays,
        then they are interpreted as a sequence of N tracking points.
        :param u_ref: Optional target for the optimized control inputs
        """
        return self.ad_mpc.set_reference(x_reference=x_ref, u_reference=u_ref, terminal_point = terminal_point)

    def optimize(self, model_data):
        w_opt, x_opt, solver_status = self.ad_mpc.optimize(use_model=model_data, return_x=True)
        # Remember solution for next optimization
        # self.last_w = self.ad_mpc.reshape_input_sequence(w_opt)
        next_control_with_stamp = AckermannDriveStamped()                
        next_control_with_stamp.header = std_msgs.msg.Header()
        next_control_with_stamp.header.stamp = rospy.Time.now()        
        next_control_with_stamp.drive.steering_angle = x_opt[0,6]
        next_control_with_stamp.drive.steering_angle_velocity = w_opt[1]        
        next_control_with_stamp.drive.speed = x_opt[0,3]                
        next_control_with_stamp.drive.acceleration =  w_opt[0]        
        # next_control_with_stamp.jerk = 

        return next_control_with_stamp, w_opt, x_opt, solver_status
