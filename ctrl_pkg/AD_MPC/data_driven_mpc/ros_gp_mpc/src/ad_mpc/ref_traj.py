import numpy as np
import math
import rosbag
import time
import rospy
import scipy.io as sio
from scipy.signal import filtfilt


def compute_curvature(cdists, psis):
	# This function estimates curvature using finite differences (curv = dpsi/dcdist).
	diff_dists = np.diff(cdists)
	diff_psis  = np.diff(np.unwrap(psis))

	assert np.max( np.abs(diff_psis) )  < np.pi, "Detected a jump in the angle difference."

	curv_raw = diff_psis / np.maximum(diff_dists, 0.1) # use diff_dists where greater than 10 cm	
	curv_raw = np.insert(curv_raw, len(curv_raw), curv_raw[-1]) # curvature at last waypoint	
	# if len(curv_raw) > 33:
	curv_filt = filtfilt(np.ones((11,))/11, 1, curv_raw) # curvature filter suggested by Jinkkwon Kim.
	# else:
	# 	curv_filt = filtfilt(np.ones((11,))/11, 1, curv_raw, padlen=min(len(cdists),3))		
	# Curvature Filtering: (https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.filtfilt.html)
	
	return curv_filt
	

def bound_angle_within_pi(angle):
	return (angle + np.pi) % (2.0 * np.pi) - np.pi # https://stackoverflow.com/questions/15927755/opposite-of-numpy-unwrap

def fix_angle_reference(angle_ref, angle_init):
	# This function returns a "smoothened" angle_ref wrt angle_init so there are no jumps.
	diff_angle = angle_ref - angle_init
	diff_angle = bound_angle_within_pi(diff_angle)
	diff_angle = np.unwrap(diff_angle) # removes jumps greater than pi
	return angle_init + diff_angle 

################################################
# RefTrajectory Class
################################################
class RefTrajectory():
	'''
	Class to load a matfile GPS trajectory and provide functions to obtain a
	local trajectory from the full trajectory for MPC using the current vehicle state.
	'''	
	def __init__(self, traj_horizon=10, traj_dt=0.2):
		
		self.traj_horizon = traj_horizon	# horizon (# time steps ahead) for trajectory reference
		self.traj_dt = traj_dt				# time discretization (s) for each time step in horizon

		# tms  = []		# ROS Timestamps (s)
		# lats = []		# Latitude (decimal degrees)
		# lons = []		# Longitude (decimal degrees)
		# psis = []		# yaw angle (radians ccw wrt East, i.e.global X-axis)
		# Xs   = []		# global X position (m, wrt to origin at LON0, LAT0)
		# Ys   = []		# global Y position (m, wrt to origin at LON0, LAT0)
		# cdists = []		# cumulative distance along path (m, aka "s" in Frenet formulation)

		self.x_ref = []
		self.y_ref = []
		self.psi_ref = []
		self.vel_ref = []
		self.trajectory = []
		self.access_map = []

	
	def set_traj(self,x_ref, y_ref, psi_ref, vel_ref):
		Xs = []
		Ys = []
		cdists = []
		for i in range(len(x_ref)):
			X = x_ref[i]; Y = y_ref[i]
			# X,Y = latlon_to_XY(0.0, 0.0, lat, lon)
			if len(Xs) == 0: 		# i.e. the first point on the trajectory
				cdists.append(0.0)	# s = 0
			else:					# later points on the trajectory
				d = math.sqrt( (X - Xs[-1])**2 + (Y - Ys[-1])**2 ) + cdists[-1]
				cdists.append(d) 	# s = s_prev + dist(z[i], z[i-1])
			Xs.append(X)
			Ys.append(Y)

		curvs = compute_curvature(cdists, psi_ref)
		self.trajectory =  np.column_stack((vel_ref, x_ref, y_ref, psi_ref, cdists, curvs)) 
		self.access_map = {key:index for index, key in \
		                   enumerate(['vel', 'x', 'y', 'psi', 'cdist', 'curv'])}
		return 
	
	# Main callback function to get the waypoints from the vehicle's initial pose and the prerecorded global trajectory.
	def get_waypoints(self, X_init, Y_init, psi_init):
		
		if self.access_map is None:
			rospy.loginfo("trajectory has not been set")
			return
		psi_init = bound_angle_within_pi(psi_init)

		waypoint_dict = {}
		xy_traj = self.trajectory[ :, [self.access_map['x'], self.access_map['y']] ] # XY trajectory
		xy_query = np.array([[X_init,Y_init]])	# the vehicle's current position (XY)
		# (1) Find the index of the closest point on the trajectory to the initial vehicle position.
		#     This could be sped up by restricting a search neighborhood of xy_traj or using a kd-tree.
		closest_index = np.argmin( np.linalg.norm(xy_traj - xy_query, axis=1) )

		# (2) Find error coordinates (aka road-aligned or Frenet frame):
		xy_waypoint  = self.trajectory[ closest_index, [self.access_map['x'], self.access_map['y']] ]
		psi_waypoint = self.trajectory[ closest_index, self.access_map['psi'] ]		
		vel_references = self.trajectory[ :, self.access_map['vel'] ]		
		
		rot_global_to_frenet = np.array([[ np.cos(psi_waypoint), np.sin(psi_waypoint)], \
			                             [-np.sin(psi_waypoint), np.cos(psi_waypoint)]])

		error_xy = xy_query - xy_waypoint # xy deviation (global frame)
		error_frenet = np.dot(rot_global_to_frenet, error_xy[0,:]) # e_s, e_y deviation (Frenet frame)

		waypoint_dict['s0']     = self.trajectory[ closest_index, self.access_map['cdist'] ] # we assume e_s is approx. 0.
		waypoint_dict['e_y0']   = error_frenet[1]
		waypoint_dict['e_psi0'] = bound_angle_within_pi(psi_init - psi_waypoint)

		# (3) Find the reference trajectory using distance or time interpolation.
		#     WARNING: this function does not handle well the case where the car is far from the recorded path!
		#     Ill-defined behavior/speed.
		#     Could use the actual minimum distance and add appropriate logic to handle this edge case.
		
			# Given a velocity reference, use the cumulative distance for interpolation.
		start_dist = self.trajectory[closest_index, self.access_map['cdist']]			
		interp_by_key = 'cdist'
		while len(vel_references) < self.traj_horizon+1:
			vel_references = np.concatenate((vel_references, [0.01]))
		
		interp_to_fit = [self.traj_dt*vel_references[0]]
		for h in range(1,self.traj_horizon):
			interp_to_fit.append(interp_to_fit[-1]+self.traj_dt*vel_references[h])
		# interp_to_fit = [h*self.traj_dt*vel_references[h] + start_dist for h in range(1, self.traj_horizon+1)]
		
		for waypoint_key in ['x', 'y', 'psi', 'cdist', 'curv']:
			if waypoint_key == 'psi':
				waypoint_dict[waypoint_key + '_ref'] = np.interp(interp_to_fit, \
				                                    self.trajectory[:, self.access_map[interp_by_key]], \
				                                    np.unwrap(self.trajectory[:, self.access_map[waypoint_key]]))
			else:				
				waypoint_dict[waypoint_key + '_ref'] = np.interp(interp_to_fit, \
														self.trajectory[:, self.access_map[interp_by_key]], \
														self.trajectory[:, self.access_map[waypoint_key]])
			if waypoint_key == 'psi':
				waypoint_dict['psi_ref'] = fix_angle_reference(waypoint_dict['psi_ref'], psi_init)
				waypoint_dict['psi_ref'] = bound_angle_within_pi(waypoint_dict['psi_ref'])

		# Reference velocity found by approximation using ds/dt finite differencing.
		waypoint_dict['v_ref'] = np.diff(waypoint_dict['cdist_ref']) / self.traj_dt
		waypoint_dict['v_ref'] = np.insert(waypoint_dict['v_ref'], len(waypoint_dict['v_ref']), waypoint_dict['v_ref'][-1]) # v_{N-1} = v_N

		waypoint_dict['stop'] = False
		if waypoint_dict['cdist_ref'][-1] == self.trajectory[:, self.access_map['cdist']][-1]:
			waypoint_dict['stop'] = True # reached the end of the trajectory, so give a stop command.
		
		
		
		points_from_init = np.linspace(X_init,waypoint_dict['x_ref'][1],3)		
		waypoint_dict['x_ref'] = np.hstack([points_from_init, waypoint_dict['x_ref'][2:-1]])

		points_from_init = np.linspace(Y_init,waypoint_dict['y_ref'][1],3)		
		waypoint_dict['y_ref'] = np.hstack([points_from_init, waypoint_dict['y_ref'][2:-1]])
		
		points_from_init = np.ones(3)*waypoint_dict['psi_ref'][0]		
		waypoint_dict['psi_ref'] = np.hstack([points_from_init, waypoint_dict['psi_ref'][2:-1]])

		points_from_init = np.ones(3)*waypoint_dict['v_ref'][2]		
		waypoint_dict['v_ref'] = np.hstack([points_from_init, waypoint_dict['v_ref'][2:-1]])

		

		return waypoint_dict # keys ['s0', 'e_y0, 'e_psi0', 'x_ref', 'y_ref', 'psi_ref', 'cdist_ref', 'curv_ref2