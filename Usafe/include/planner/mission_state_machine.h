
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

#include <sstream>
#include <string>
#include <queue>

#include <ros/ros.h>
#include <ros/time.h>
#include <vector>

#define PI 3.14159265358979323846264338

namespace planner{


class MissionStateMachine
{
  
private:

  double tmp;
  


public:
MissionStateMachine(); 
~MissionStateMachine();

void update_v2x_msg();
void update_vehicle_status();
void update_mission_state_flag();


};


}