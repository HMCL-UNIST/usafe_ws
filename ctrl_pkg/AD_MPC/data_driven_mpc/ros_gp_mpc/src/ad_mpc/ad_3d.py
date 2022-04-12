""" Implementation of the Simplified Simulator and its quadrotor dynamics.

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


from math import sqrt
import numpy as np
from utils.utils import quaternion_to_euler, skew_symmetric, v_dot_q, unit_quat, quaternion_inverse


class AD3D:

    def __init__(self, noisy=False, noisy_input=False):
        """
        Initialization of the 2D Autonomous vehicle class -> (Extend to 3D in the future)
        :param noisy: Whether noise is used in the simulation
        :type noisy: bool
        :param drag: Whether to simulate drag or not.
        :type drag: bool
        :param payload: Whether to simulate a payload force in the simulation
        :type payload: bool
        :param motor_noise: Whether non-gaussian noise is considered in the motor inputs
        :type motor_noise: bool
        """
        
        # System state space
        # self.pos = np.zeros((2,))
        
        # self.vel = np.zeros((1,))      
        self.p_x= np.zeros((1,))       
        self.p_y= np.zeros((1,))      
        self.psi = np.zeros((1,))
        self.v_x = np.zeros((1,))      
        self.v_y = np.zeros((1,))      
        self.psi_dot = np.zeros((1,))      
        self.delta = np.zeros((1,))
        #vehicle Mass in kg 
        self.mass = 1500
        self.f_mass = 900
        self.r_mass = self.mass - self.f_mass
        self.L = 2.7
        self.L_F = self.L*(1-self.f_mass/self.mass)
        self.L_R = self.L*(1-self.r_mass/self.mass)
        
         #Moment of Inertia in z axis 
        self.Iz = self.L_F*self.L_R*(self.r_mass+self.f_mass)
                
        #Cornering Stiffness for single wheel(N/rad) 
        # Cx = total load * weight distribution on each wheel * g(Kg to Newton) * 16.5%(approximatio) * 57.3 (1/degree to radian) 
        self.Cf = self.f_mass*0.5*9.81*0.165*180/3.14195 
        self.Cr =  self.r_mass*0.5*9.81*0.165*180/3.14195 

        # blend velocity  for mixing dynamical and kinamatical model
        self.blend_max = 5
        self.blend_min = 3
        # Input constraints        
        self.steering_min = -0.52
        self.steering_max = 0.52
        self.steering_rate_min = -3 # rate of steering angle [rad/s]
        self.steering_rate_max = 3 # rate of steering angle [rad/s]
        self.acc_min = -10
        self.acc_max = 5

        self.noisy_input = False
        self.noisy = noisy
        
        
        # Input - > Accl + Steering angle rate
        self.u_noiseless = np.array([0.0, 0.0])
        self.u = np.array([0.0, 0.0])  # acceleration and angle rate 

        

    def set_state(self, *args, **kwargs):
        if len(args) != 0:
            assert len(args) == 1 and len(args[0]) == 7
            self.p_x[0], self.p_y[0], self.psi[0], self.v_x[0], self.v_y[0], self.psi_dot[0], self.delta[0] = args[0]            
        else:
            self.p_x = kwargs["p_x"]
            self.p_y = kwargs["p_y"]
            self.psi = kwargs["psi"]            
            self.v_x = kwargs["v_x"]            
            self.v_y = kwargs["v_y"]            
            self.psi_dot = kwargs["psi_dot"]            
            self.delta = kwargs["delta"]            


    def get_state(self, stacked=False):
        
        if stacked:
            return [self.p_x[0], self.p_y[0], self.psi[0], self.v_x[0], self.v_y[0], self.psi_dot[0], self.delta[0]] 
        return [self.p_x, self.p_y, self.psi, self.v_x, self.v_y, self.psi_dot, self.delta]
    
    def get_control(self, noisy=False):
        if not noisy:
            return self.u_noiseless
        else:
            return self.u

    # def update(self, u, dt):
    #     """
    #     Runge-Kutta 4th order dynamics integration
    #     :param u: 4-dimensional vector with components between [0.0, 1.0] that represent the activation of each motor.
    #     :param dt: time differential
    #     """

    #     # Clip inputs        
    #     self.u_noiseless[0] = max(min(u[0], self.acc_min), self.acc_max)
    #     self.u_noiseless[1] = max(min(u[1], self.steering_min), self.steering_max)

    #     # Apply noise to inputs (uniformly distributed noise with standard deviation proportional to input magnitude)
    #     if self.noisy_input:
    #         std = 0.02 * sqrt(self.u_noiseless[0])
    #         noise_u = np.random.normal(loc=0.1 * (self.u_noiseless[0] / 1.3) ** 2, scale=std)
    #         self.u[0] = max(min(self.u_noiseless[0] - noise_u, self.acc_min), self.acc_max)                                
    #         std = 0.02 * sqrt(self.u_noiseless[1])
    #         noise_u = np.random.normal(loc=0.1 * (self.u_noiseless[1] / 1.3) ** 2, scale=std)
    #         self.u[1] = max(min(self.u_noiseless[1] - noise_u, self.steering_min), self.steering_max)  
    #     else:
    #         self.u = self.u_noiseless


    #     if self.noisy:
    #         f_d = np.random.normal(size=(3, 1), scale=10 * dt)
    #         t_d = np.random.normal(size=(3, 1), scale=10 * dt)
    #     else:
    #         f_d = np.zeros((3, 1))
    #         t_d = np.zeros((3, 1))

    #     x = self.get_state(stacked=False)

    #     # RK4 integration
    #     k1 = [self.f_pos(x), self.f_psi(x), self.f_vel(x, self.u, f_d)]
    #     x_aux = [x[i] + dt / 2 * k1[i] for i in range(3)]
    #     k2 = [self.f_pos(x_aux), self.f_psi(x_aux), self.f_vel(x_aux, self.u, f_d)]
    #     x_aux = [x[i] + dt / 2 * k2[i] for i in range(3)]
    #     k3 = [self.f_pos(x_aux), self.f_psi(x_aux), self.f_vel(x_aux, self.u, f_d)]
    #     x_aux = [x[i] + dt * k3[i] for i in range(3)]
    #     k4 = [self.f_pos(x_aux), self.f_psi(x_aux), self.f_vel(x_aux, self.u, f_d)]
    #     x = [x[i] + dt * (1.0 / 6.0 * k1[i] + 2.0 / 6.0 * k2[i] + 2.0 / 6.0 * k3[i] + 1.0 / 6.0 * k4[i]) for i in
    #          range(4)]

        
    #     self.pos, self.psi, self.vel = x

    # def f_pos(self, x):
    #     """
    #     Time-derivative of the position vector
    #     :param x: 4-length array of input state with components: 3D pos, quaternion angle, 3D vel, 3D rate
    #     :return: position differential increment (vector): d[pos_x; pos_y]/dt
    #     """        
    #     vel = x[2]
    #     return vel

    # def f_att(self, x):
    #     """
    #     Time-derivative of the attitude in quaternion form
    #     :param x: 4-length array of input state with components: 3D pos, quaternion angle, 3D vel, 3D rate
    #     :return: attitude differential increment (quaternion qw, qx, qy, qz): da/dt
    #     """

    #     rate = x[3]
    #     angle_quaternion = x[1]

    #     return 1 / 2 * skew_symmetric(rate).dot(angle_quaternion)

    # def f_vel(self, x, u, f_d):
    #     """
    #     Time-derivative of the velocity vector
    #     :param x: 4-length array of input state with components: 3D pos, quaternion angle, 3D vel, 3D rate
    #     :param u: control input vector (4-dimensional): [trust_motor_1, ..., thrust_motor_4]
    #     :param f_d: disturbance force vector (3-dimensional)
    #     :return: 3D velocity differential increment (vector): d[vel_x; vel_y; vel_z]/dt
    #     """

    #     a_thrust = np.array([[0], [0], [np.sum(u)]]) / self.mass

    #     if self.drag:
    #         # Transform velocity to body frame
    #         v_b = v_dot_q(x[2], quaternion_inverse(x[1]))[:, np.newaxis]
    #         # Compute aerodynamic drag acceleration in world frame
    #         a_drag = -self.aero_drag * v_b ** 2 * np.sign(v_b) / self.mass
    #         # Add rotor drag
    #         a_drag -= self.rotor_drag * v_b / self.mass
    #         # Transform drag acceleration to world frame
    #         a_drag = v_dot_q(a_drag, x[1])
    #     else:
    #         a_drag = np.zeros((3, 1))

    #     angle_quaternion = x[1]

    #     a_payload = -self.payload_mass * self.g / self.mass

    #     return np.squeeze(-self.g + a_payload + a_drag + v_dot_q(a_thrust + f_d / self.mass, angle_quaternion))

    # def f_rate(self, x, u, t_d):
    #     """
    #     Time-derivative of the angular rate
    #     :param x: 4-length array of input state with components: 3D pos, quaternion angle, 3D vel, 3D rate
    #     :param u: control input vector (4-dimensional): [trust_motor_1, ..., thrust_motor_4]
    #     :param t_d: disturbance torque (3D)
    #     :return: angular rate differential increment (scalar): dr/dt
    #     """

    #     rate = x[3]
    #     return np.array([
    #         1 / self.J[0] * (u.dot(self.y_f) + t_d[0] + (self.J[1] - self.J[2]) * rate[1] * rate[2]),
    #         1 / self.J[1] * (-u.dot(self.x_f) + t_d[1] + (self.J[2] - self.J[0]) * rate[2] * rate[0]),
    #         1 / self.J[2] * (u.dot(self.z_l_tau) + t_d[2] + (self.J[0] - self.J[1]) * rate[0] * rate[1])
    #     ]).squeeze()
