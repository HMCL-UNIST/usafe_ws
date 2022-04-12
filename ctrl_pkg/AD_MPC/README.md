# AD_MPC
MPC controller for Autonomous vehicle

Non-linear bicycle dynamics in Frenet–Serret formulas

![vehicle_dynamics1](https://user-images.githubusercontent.com/32535170/152135021-e2a64c43-9d42-44fa-ad94-7c335503462b.png)
![vehicle_dynamics2](https://user-images.githubusercontent.com/32535170/152135293-6faca7ed-c98c-425c-88d8-03ec7c3fb00f.png)
![vehicle_dynmaics3](https://user-images.githubusercontent.com/32535170/152135292-7089d7bc-0d19-49d3-835a-c439d2a3b70c.png)
![vehicle_dynamics4](https://user-images.githubusercontent.com/32535170/152135290-758b7ade-bf16-4648-a27a-fe6c1663c0cf.png)
![vehicle_dynamic5](https://user-images.githubusercontent.com/32535170/152135288-7ea9ced5-8211-4b6b-9ccd-1c3cc697aec3.png)
![vehicle_dynamics6](https://user-images.githubusercontent.com/32535170/152135286-fdf00505-9daa-43b2-b5e2-a174b651900a.png)
![vehicle_dynaamics7](https://user-images.githubusercontent.com/32535170/152135279-f5904dfe-4559-41fd-bd1d-42fa1a4a6768.png)
 
 ### Typical value for cornering stiffness 
 ![cornering_stiffness](https://user-images.githubusercontent.com/32535170/152141345-d32b0495-da7b-4a6f-980d-1236ecf07351.png)
 --> cornering stiffness per degree is 16~17% of load on tyre.. 
 e.g. 
 ![weight_distribution_eg](https://user-images.githubusercontent.com/32535170/152142116-4c346683-e26e-4292-834f-a44d37f0c70e.png)
 

Cornering Stiffness for single front wheel, Cf-> 1000*0.5 *9.81 * 0.165 = 10,000 *0.16 N/degree = 809 N/degree = 46365 N/rad 


Cornering Stiffness for single rear wheel, Cr-> 840*0.5 *9.81 * 0.165 = 10,000 *0.16 N/degree = 680 N/degree = 39000 N/rad 


 ## References
 
 ### Bicycle dyanmics (ETH Zurich Racecar) 
https://arxiv.org/pdf/1905.05150.pdf

https://github.com/alexliniger/MPCC/blob/master/C%2B%2B/Model/model.cpp
 
 ### Frenet frame dynamics
  Dabbene, Fabrizio, Martina Mammarella, and Ruotolo Vincenzo Pio. "Optimal Trajectory Generation via Robust Model Predictive Control for a Four-Wheel Steering Electric Unmanned Ground Vehicle."
 
 https://webthesis.biblio.polito.it/19284/1/tesi.pdf
 
 
 
 ### Frenet frame kinematics 
 file:///home/hojin/Downloads/Convoy-final-HAL.pdf
 
 ### Vehicle dynamics with pitch and roll 
 Wang, Junjie, et al. "Linear Time-Varying MPC-Based Steering Controller for Vehicle Trajectory Tracking Considering the Effect of Road Topography." 2020 5th International Conference on Control, Robotics and Cybernetics (CRC). IEEE, 2020.
 https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=9253449
 
 ### Steering by wire modeling and The Pacejka Tire Model
 
 https://ddl.stanford.edu/sites/g/files/sbiybj9456/f/publications/2005_Thesis_Yih_Steer_by_Wire_Implications_for_Vehicle_Handling_and_Safety.pdf

 ### Cornering Stiffness identification 
 https://www.ri.cmu.edu/pub_files/2009/2/Automatic_Steering_Methods_for_Autonomous_Automobile_Path_Tracking.pdf
 
