
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


#include "vehicle_model_dynamics.h"


void VehicleModel::init(double& dt, double&  wheelbase, double& lf, double& lr, double& mass, int delay_step_){
        
        dt_ = dt;
        wheelbase_ = wheelbase;
        lf_ = lf; 
        lr_ = lr;
        mass_ = mass;
        //  Moment of Inertia in z axis         
        iz_ = lf_*lr_*(mass_);
        //  Cornering Stiffness for single wheel(N/rad) 
        //  Cx = total load * weight distribution on each wheel * g(Kg to Newton) * 16.5%(approximatio) * 57.3 (1/degree to radian) 
        cf_ = mass_*(lf_/(lf_+lr_))*0.5*9.81*0.165*180/3.14195 ;
        cr_ = mass_*(lr_/(lf_+lr_))*0.5*9.81*0.165*180/3.14195 ;
        sigma1 = 2.0*(cf_+cr_);
        sigma2 = -2.0*(lf_ * cf_ - lr_ * cr_);
        sigma3 = -2.0*(lf_* lf_ * cf_ + lr_* lr_ * cr_);
        mcQ    = Eigen::MatrixXd::Zero(delay_step_+5,delay_step_+5);     
        mcR    = Eigen::MatrixXd::Zero(1,1);
        init_done = true;
        
};

void VehicleModel::setDelayStep(int delay_step_){
    delay_step = delay_step_;
}

void VehicleModel::setLagTau(double tau_){
    tau = tau_;    
}

void VehicleModel::setWeight(std::vector<double> q_weight, double r_weight){
    if(q_weight.size() > delay_step+5){
        ROS_ERROR("q weight is too large, Q weight is not updated");
        return;
    }
    for(int i =0; i< q_weight.size(); i++){
        mcQ(i,i) = q_weight[i];
    }
    mcR(0,0) = r_weight; 
}

void VehicleModel::reintMatrices(){
     if(delay_step < 1){
         ROS_ERROR("delay step is less than 1");
         return; 
     }
     Abaroc = Eigen::MatrixXd::Zero(4,4);    
     Bbaroc = Eigen::MatrixXd::Zero(4,1);
     Dbaroc = Eigen::MatrixXd::Zero(4,1);
     Abarc  = Eigen::MatrixXd::Zero(5,5);
     Bbarc  = Eigen::MatrixXd::Zero(5,1);
     Dbarc  = Eigen::MatrixXd::Zero(5,1);
     Ad     = Eigen::MatrixXd::Zero(5,5);
     Bd     = Eigen::MatrixXd::Zero(5,1);
     Dd     = Eigen::MatrixXd::Zero(5,1);
     mcAd   = Eigen::MatrixXd::Zero(delay_step+5,delay_step+5);
     mcBd   = Eigen::MatrixXd::Zero(delay_step+5,1);
     mcDd   = Eigen::MatrixXd::Zero(delay_step+5,1);
    
}

void VehicleModel::computeMatrices(double vel){
    if(!init_done){
        return;
    }
    if(delay_step <1 ){
        std::cout<<"delay step = " << delay_step << " should be greater than 1" << std::endl;
        return;
    }
    if(fabs(mcQ(0,0)) < 1e-7){
        ROS_WARN("mcQ ey is too small");
        return;
    }
    if(fabs(mcQ(2,2)) < 1e-7){
        ROS_WARN("mcQ epsi is too small");
        return;
    }

    reintMatrices();

    Abaroc(0, 1) = 1.0;
    Abaroc(1, 1) = -1*(sigma1) / (mass_ * vel);
    Abaroc(1, 2) = sigma1 / mass_;
    Abaroc(1, 3) = (sigma2) / (mass_ * vel);
    Abaroc(2, 3) = 1.0;
    Abaroc(3, 1) = (sigma2) / (iz_ * vel);
    Abaroc(3, 2) = -1*(sigma2) / iz_;
    Abaroc(3, 3) = (sigma3) / (iz_ * vel);

   
    Bbaroc(0,0) = 0.0;
    Bbaroc(1,0) = 2*cf_/mass_;
    Bbaroc(2,0) = 0.0;
    Bbaroc(3,0) = 2*lf_*cf_/iz_;
    

    Dbaroc(0,0) = 0.0;
    Dbaroc(1,0) = sigma2/mass_-vel*vel;
    Dbaroc(2,0) = 0.0;
    Dbaroc(3,0) = sigma3/iz_;
    

    Abarc.block<4,4>(0,0) = Abaroc;
    Abarc.block<4,1>(0,4) = Bbaroc;
    Abarc.block<1,4>(4,0) = Eigen::MatrixXd::Zero(1,4);
    Abarc(4,4) = -1/tau;    
    
    Bbarc(4,0) = 1/tau;

    Dbarc.block<4,1>(0,0) = Dbaroc;

    // Bilinear transform , continuous to discrete 
    Eigen::MatrixXd Ix = Eigen::MatrixXd::Identity(5,5);
    Eigen::MatrixXd Ad_inverse = (Ix - dt_ * 0.5 * Abarc).inverse();
    Ad =  Ad_inverse * (Ix + dt_ * 0.5 * Abarc);
    Bd = Ad_inverse * dt_ *Bbarc;
    Dd = Ad_inverse * dt_ *Dbarc;

    int tmp_size = delay_step-1;
    mcAd.block<5,5>(0,0) = Ad;
    mcAd.block<5,1>(0,5) = Bd;
    mcAd.block(5,6,tmp_size,tmp_size) = Eigen::MatrixXd::Identity(delay_step-1,delay_step-1);
    mcBd(tmp_size+5,0) = 1.0;
    mcDd.block<5,1>(0,0) = Dd;
    

}

void VehicleModel::solveRiccati(){
    mcP = Eigen::MatrixXd::Zero(delay_step+5, delay_step+5);
    solveRiccatiIterationD(mcAd, mcBd, mcQ, mcR, mcP);

    PRINT_MAT(mcP);
}