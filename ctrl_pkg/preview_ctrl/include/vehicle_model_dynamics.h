
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
#include <iostream>
#include <riccati_solver.h>
#include <ros/ros.h>
#include <time.h>

// #define PI 3.14159265358979323846264338

#define PRINT_MAT(X) std::cout << #X << ":\n" << X << std::endl << std::endl

class VehicleModel 
{  
private:
  double wheelbase_; //!< @brief wheelbase length [m]
  double lf_;        //!< @brief length from centor of mass to front wheel [m]
  double lr_;        //!< @brief length from centor of mass to rear wheel [m]
  double mass_;      //!< @brief total mass of vehicle [kg]
  double iz_;        //!< @brief moment of inertia [kg * m2]
  double cf_;        //!< @brief front cornering power [N/rad]
  double cr_;        //!< @brief rear cornering power [N/rad]
  double dt_;
  
  double sigma1, sigma2, sigma3;
  bool init_done = false;

  int delay_step;
  double tau;
  int dim_x_; // n
  int dim_u_; // p
  Eigen::MatrixXd mcQ, mcR;  

  Eigen::MatrixXd Abaroc, Bbaroc, Dbaroc;
  Eigen::MatrixXd Abarc, Bbarc, Dbarc;
  Eigen::MatrixXd Ad, Bd, Dd;
  

  Eigen::MatrixXd mcAd, mcBd, mcDd; 
  Eigen::MatrixXd mcP;

  Eigen::VectorXd Xk, Cr; // Xk contains states and deltas && Cr contains preview curvature 


public:


VehicleModel(){};
~VehicleModel(){};

void initModel(double& dt, double& wheelbase, double&  lf, double&  lr, double& mass);
void setDelayStep(int delay_step_);
void setLagTau(double tau_);
void setWeight(std::vector<double> q_weight, double r_weight);
void reintMatrices();
void computeMatrices(double vel);

bool solveRiccati();
double computeGain();
void setState(Eigen::VectorXd Xk,Eigen::VectorXd Cr);



};



