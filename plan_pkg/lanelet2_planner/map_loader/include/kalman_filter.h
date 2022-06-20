
//   Copyright (c) 2022 Ulsan National Institute of Science and Technology (UNIST)
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

//   Authour : Hojin Lee, hojinlee@unist.ac.kr


#include <eigen3/Eigen/Geometry>

#define PI 3.14159265358979323846264338
// #include <Eigen/Dense>

// #pragma once

class KalmanFilter {

public:

	/**
	* Create a Kalman filter with the specified matrices.
	*   A - System dynamics matrix
	*   B - Input matrix
	*   C - Output matrix
	*   Q - Process noise covariance
	*   R - Measurement noise covariance
	*   P - Estimate error covariance
	*/
	KalmanFilter(
			const Eigen::MatrixXd& A,
			const Eigen::MatrixXd& B,
			const Eigen::MatrixXd& C,
			const Eigen::MatrixXd& Q,
			const Eigen::MatrixXd& R,
			const Eigen::MatrixXd& P
	);


	/**
	* Initialize the filter with initial states as zero.
	*/
	void init();

	/**
	* Initialize the filter with a guess for initial states.
	*/
	void init(const Eigen::VectorXd& x0);

	/**
	* Update the prediction based on control input.
	*/
	void predict(const Eigen::VectorXd& u);

	/**
	* Update the estimated state based on measured values.
	*/
	void update(const Eigen::VectorXd& y);

	/**
	* Update the dynamics matrix.
	*/
	void update_dynamics(const Eigen::MatrixXd A);

	/**
	* Update the output matrix.
	*/
	void update_output(const Eigen::MatrixXd C);

	/**
	* Return the current state.
	*/
	Eigen::VectorXd state() { return x_hat; };

private:

	// Matrices for computation
	Eigen::MatrixXd A, B, C, Q, R, P, K, P0;

	// System dimensions
	int m, n, c;

	// Is the filter initialized?
	bool initialized = false;

	// n-size identity
	Eigen::MatrixXd I;

	// Estimated states
	Eigen::VectorXd x_hat;
};