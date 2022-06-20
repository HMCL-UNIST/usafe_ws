
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


#include <iostream>
#include <iostream>

#include "kalman_filter.h"



KalmanFilter::KalmanFilter(
		const Eigen::MatrixXd& A,
		const Eigen::MatrixXd& B,
		const Eigen::MatrixXd& C,
		const Eigen::MatrixXd& Q,
		const Eigen::MatrixXd& R,
		const Eigen::MatrixXd& P)
	: A(A), B(B), C(C), Q(Q), R(R), P0(P),
		m(C.rows()), n(A.rows()), c(B.cols()), initialized(false),
		I(n, n), x_hat(n)
{
	I.setIdentity();
}



void KalmanFilter::init_kalman(
			const Eigen::MatrixXd& A,
			const Eigen::MatrixXd& B,
			const Eigen::MatrixXd& C,
			const Eigen::MatrixXd& Q,
			const Eigen::MatrixXd& R,
			const Eigen::MatrixXd& P
	){
    this->A = A;
    this->B = B;
    this->C = C;
    this->Q = Q;
    this->R = R;
    this->P = P;
  }


void KalmanFilter::init(const Eigen::VectorXd& x0) {

	x_hat = x0;
	P = P0;
	initialized = true;
}

void KalmanFilter::init() {

	x_hat.setZero();
	P = P0;
	initialized = true;
}

void KalmanFilter::predict(const Eigen::VectorXd& u) {

	if(!initialized) {
		std::cout << "Filter is not initialized! Initializing with trivial state.";
		init();
	}

	x_hat = A*x_hat + B*u;
	P = A*P*A.transpose() + Q;
}

void KalmanFilter::update(const Eigen::VectorXd& y) {

	K = P*C.transpose()*(C*P*C.transpose() + R).inverse();
	x_hat += K * (y - C*x_hat);
	P = (I - K*C)*P;
}

void KalmanFilter::update_dynamics(const Eigen::MatrixXd A) {

	this->A = A;
}

void KalmanFilter::update_output(const Eigen::MatrixXd C) {

	this->C = C;
}