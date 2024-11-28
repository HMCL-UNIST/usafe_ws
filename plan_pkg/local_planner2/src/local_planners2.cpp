
#include "local_planners2.h"

localplanners2::localplanners2(ros::NodeHandle& nh):
    nh_(nh)
{
    ROS_INFO("Local Planner Initialize");
    sub_pos = nh_.subscribe("/current_pose", 1, &localplanners2::poseCallback, this);
    // sub_vel = nh_.subscribe("/current_velocity", 1, &localplanners2::velCallback, this);
    sub_vel = nh_.subscribe("/CAN_VehicleStatus", 1, &localplanners2::velCallback, this);
   
    sub_traj = nh_.subscribe("/global_traj", 1, &localplanners2::globalCallback, this);
    sub_opt = nh_.subscribe("/optimal_traj", 1, &localplanners2::optimalCallback, this);
    mission_sub = nh_.subscribe("/mission_state", 1, &localplanners2::missionCallback, this);
    sub_flag = nh_.subscribe("/behavior_state", 1, &localplanners2::behaviorstateCallback, this);
    sub_bfac = nh_.subscribe("/behavior_factor", 1, &localplanners2::behaviorfactorCallback, this);
    sub_obj = nh_.subscribe("/tracking_car/objects", 1, &localplanners2::objCallback, this);

    pub_viz = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1);
    timer_ = nh_.createTimer(ros::Duration(0.1), &localplanners2::local_handler,this);
    // local_traj_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj_kr", 2, true);
    local_traj_pub = nh_.advertise<hmcl_msgs::Lane>("/local_traj", 2, true);
    flag_pub = nh_.advertise<std_msgs::Int8>("/overtaking", 2, true);
    aeb_pub = nh_.advertise<std_msgs::Int8>("/aeb_flag", 2, true);
    l_traj_viz_pub = nh_.advertise<visualization_msgs::MarkerArray>("/local_traj_viz", 1, true);

    //parameter
    // nh_.param<double>("minimum_lane_change_length", min_lc_len, 5.0);
    // nh_.param<double>("lane_change_prepare_duration", lc_prepare_dur, 1.5);
    // nh_.param<double>("lane_changing_duration", lc_duration, 3.0);
    // nh_.param<double>("minimum_lane_change_velocity", min_lc_vel, 3.0);
    // nh_.param<double>("lane_width", lane_width, 1.75);
   
    // nh_.param<double>("Q_vel", Q_vel, 1.0); 
    prev_lane_id = -1;
    current_lane_id = -1;
    llc_flag = false;
    rlc_flag = false;
    keep_flag = false;
    lc_flag = false;
    can_aeb = false;
    acc = false;
    wLane = 3.4;
    
}

localplanners2::~localplanners2()
{}
void localplanners2::subtypeCallback(const hmcl_msgs::PolygonFlag::ConstPtr& msg) {
    area = 0;
    if(pose_init){
      if(msg->isinBank){
        if(pose_x > 500) area = 1;
        else area = 2;
      }
      else if(msg->isinCrosswalk){
        area = 0;
      }
      else if(msg->isinTrafficIsland){
        if(msg->isinBuilding){
          if(pose_x > 500) area = 3;
          else area = 4;
        }
        else{
          area = 0;
        }
      }
      else if(msg->isinBuilding){
          if(pose_x > 500) area = 3;
          else area = 4;
      }
    }
}
void localplanners2::poseCallback(const geometry_msgs::PoseStamped& state_msg){
    pose_init = true;
    pose_x = state_msg.pose.position.x;
    pose_y = state_msg.pose.position.y;
    current_pos.section = state_msg.pose;
    st_flag = true;
}
// void localplanners2::velCallback(const geometry_msgs::TwistStamped& state_msg){
//     current_pos.speed = abs(state_msg.twist.linear.x);
//     vel_flag =true;
// }
void localplanners2::velCallback(const hmcl_msgs::VehicleStatus& state_msg){
    current_pos.speed = abs(state_msg.wheelspeed.wheel_speed);
    vel_flag =true;
}
void localplanners2::behaviorstateCallback(const std_msgs::Int16ConstPtr& flag_msg){
    //  rostopic pub -r 10 /behavior_state std_msgs/Int16 12
    // ROS_INFO("check");
    // ROS_INFO("curlane : %d", current_lane_id);
    // if ((BehaviorState)flag_msg->data == BehaviorState::LeftLaneChange){
    //     if(llc_flag == false){
    //       prev_lane_id = current_lane_id;
    //       llc_flag = true;
    //       lc_flag = true;
    //       rlc_flag = false;

    //     }
    //     if (current_lane_id ==0){
    //         lc_flag = false;
    //         llc_flag = false;
    //     }
    // }    
    // else if ((BehaviorState)flag_msg ->data == BehaviorState::RightLaneChange){
    //     if(rlc_flag == false){
    //       prev_lane_id = current_lane_id;
    //       rlc_flag = true;
    //       lc_flag = true;
    //       llc_flag = false;

    //     }
    //     if (current_lane_id==2){
    //         lc_flag = false;
    //         rlc_flag = false;
    //     }
    // }

    // // llc_flag = true;
    // // lc_flag = true;
    // else{
    //     lc_flag = false;
    //     llc_flag = false;
    //     rlc_flag = false;
    // }
}

void localplanners2::behaviorfactorCallback(const hmcl_msgs::BehaviorFactor& factor_msg){
    behavior_factor_init = true;
    sEgo = factor_msg.sEgo;
    lEgo = factor_msg.lEgo;
    dsEgo = factor_msg.dsEgo;
    dlEgo = factor_msg.dlEgo;
    sOpt = factor_msg.sOpt;
    lOpt = factor_msg.lOpt;
    sObj = factor_msg.sObj;
    lObj = factor_msg.lObj;    
    dsObj = factor_msg.dsObj;
    dlObj = factor_msg.dlObj; 
    lOptFar = factor_msg.lOptFar;
    prefer_lane_id = factor_msg.prefer_lane_id;
    current_lane_id = factor_msg.current_lane_id;
    isInBank = factor_msg.isInBank;
    if(prev_lane_id == -1) prev_lane_id = current_lane_id;
}
void localplanners2::missionCallback(const std_msgs::Int16::ConstPtr& msg){
    getMission = true;
    currentMission = (MissionState)msg->data;
    if (currentMission == MissionState::StartFromPitStop || currentMission == MissionState::Lap1) firstlap_flag = true;
    else firstlap_flag = false;
}
void localplanners2::globalCallback(const hmcl_msgs::LaneArray& lane_msg){ 
    global_traj_available = true; 
    global_lane_array = lane_msg;
    
}
void localplanners2::optimalCallback(const hmcl_msgs::LaneArray& lane_msg){ 
    optimal_traj_available = true; 
    optimal_lane_array = lane_msg;
    
}
void localplanners2::objCallback(const autoware_msgs::DetectedObjectArray& obj_msg){
    if(obs_flag == true){
        obj = obj_msg;
    }
}

void localplanners2::local_handler(const ros::TimerEvent& time){
    if(!pose_init){
        ROS_INFO("pose wasn't initialized!!");
        return;
    }
    if(!behavior_factor_init){
        ROS_INFO("behavior factor wasn't initialized!!");
        return;
    }
    if(!getMission){
        ROS_INFO("mission wasn't initialized!!");
        return;
    }
    // ROS_INFO("%zu globalsize",global_lane_array.lanes.size());
    if(global_traj_available){
        if(global_lane_array.lanes.size()>0){
            decide_shift();
            if(llc_flag) compute_left_local_path();
            else if(rlc_flag) compute_right_local_path();
            else if(keep_flag) compute_keep_local_path();
            else compute_local_path();
            // compute_local_path();
        }
    }
    // ROS_INFO("%d localavail",local_traj_available);
    if(local_traj_available){
        publish_local_path();
        // ROS_INFO("LOCAL");
    }  

    if ( st_flag = false || vel_flag == false || global_traj_available == false){
        return;      
    }

    
}

void localplanners2::decide_shift(){
  lowSpeedBank = false;
  float dFront = 200;
  float dRear = 30;
  float dClose = 30;
  float dSide = 30;
  // float dMin = 100;
  float dAEB = 10;
  //############################### kt
  float dACC = current_pos.speed*1.5; // 저속일때는 현재 차량 속도 *2.0 + 20, 60 ~ 70  이상 현재 차량 속도 * 2.5 + 20// 옆차선은 기존 그대로 하던가 될거같음 아니면 현재차량 속도*1.0+ 10 정도
  if(current_pos.speed>100/3.6){
    dACC= current_pos.speed*2.5+30;
  } else if(current_pos.speed>70/3.6){
    dACC = current_pos.speed*1.5+25;
  } else if (current_pos.speed>40/3.6){
    dACC = current_pos.speed*1.5 +10;
  } else {
    dACC = current_pos.speed*1.5;
  }
  /////##############################3
  
  float desVel = 30 / 3.6;
  if(firstlap_flag) desVel = 30 / 3.6;
  else if(area == 0) desVel = 80 / 3.6;
  else if(area == 1 || area == 2) desVel = 60 / 3.6;
  else if(area == 3 || area == 4) desVel = 60 / 3.6;
  else desVel = 100 / 3.6;
  float dLC = 80;
  float ttcLC = 15;
  float ttcAEB = 3.0;
  float ttcACC = 5;
  float carWidth = 2.0;
  int iFront = -1, iLeftFront = -1, iRightFront = -1, iRear = -1, iLeftRear = -1, iRightRear = -1, iCloseFront = -1, iLeftCloseFront = -1, iRightCloseFront = -1;
  bool front = false, leftFront = false, rightFront = false, closeFront = false, leftCloseFront = false, rightCloseFront = false, leftRear = false, rightRear = false, rear = false;
  bool rightOpponent = false, leftOpponent = false, rightSide = false, leftSide = false, rightSideFar = false, leftSideFar = false;
  bool objOnOpt = false;
  bool obsAvoid = false;
  can_aeb = false;
  float dBack2opt = 0.7;
  bool ot_flag = false;
  float aeb_width = 3.4;
  float aeb_ttc = 3.0;
  acc = false;
  aeb = false;
  llc_flag = false;
  rlc_flag = false;
  keep_flag = false;
  float dist2aebobj = 100.0;
  int nObj = sObj.size();
  float lObjOpt[nObj];
  if(sObj.size()>0){
    for(int i = 0; i < sObj.size(); i++){
      if(sObj[i]-sEgo < dClose && sObj[i]-sEgo > -dRear && lObj[i]-lEgo < wLane+carWidth && lObj[i]-lEgo > carWidth){
        rightOpponent = true;
      }
      else if(sObj[i]-sEgo < dClose && sObj[i]-sEgo > -dRear && lObj[i]-lEgo > -(wLane+carWidth)&& lObj[i]-lEgo < -carWidth){
        leftOpponent = true;
      }
      // ROS_INFO("lObj[i]-lEgo: %f", lObj[i]-lEgo);
      if(abs(sObj[i]-sEgo) < dSide){
        if(lObj[i]-lEgo > carWidth && lObj[i]-lEgo < wLane*1.1) rightSide = true;
        else if(lObj[i]-lEgo < -carWidth && lObj[i]-lEgo > -wLane*1.1) leftSide = true;
        else if(lObj[i]-lEgo > carWidth && lObj[i] < wLane*1.5) rightSideFar = true;
        else if(lObj[i]-lEgo < -carWidth && lObj[i] > -wLane*1.5) leftSideFar = true;
      }
      lObjOpt[i] = lObj[i]-(lEgo-lOpt);
        // ROS_INFO("TTC : %f", (sObj[i]-sEgo)/(dsEgo-dsObj[i]));
      if(abs(lObjOpt[i])< wLane && sObj[i]-sEgo < dFront && sObj[i]-sEgo > 0){ //ttc
        // ROS_INFO("TTC : %f", (sObj[i]-sEgo)/(dsEgo-dsObj[i]));
        if(sObj[i]-sEgo < dLC || (sObj[i]-sEgo)/(dsEgo-dsObj[i]) > 0 && (sObj[i]-sEgo)/(dsEgo-dsObj[i]) < 10) ot_flag =true; 
        objOnOpt = true;
      }
      else if(prev_llc_flag || prev_rlc_flag || prev_keep_flag) ot_flag =true; 
    }
    if(ot_flag){
      for(int i = 0; i < sObj.size(); i++){
        if(sObj[i]-sEgo < 0 && sObj[i]-sEgo > -dRear){
          if(abs(lObj[i]) < (wLane-carWidth)*0.5){
            rear = true;
            if(iRear != -1){
              if(sObj[i] > sObj[iRear]) iRear = i;
            }
            else iRear = i;
          }
          else if(lObj[i] > 0 && abs(lObj[i]) < wLane*1.5){
            rightRear = true;
            if(iRightRear != -1){
              if(sObj[i] > sObj[iRightRear]) iRightRear = i;
            }
            else iRightRear = i;
          }
          else if(lObj[i] < 0 && abs(lObj[i]) < wLane*1.5)
          {
            leftRear = true;
            if(iLeftRear != -1){
              if(sObj[i] > sObj[iLeftRear]) iLeftRear = i;
            }
            else iLeftRear = i;            
          }
        }
        else if(sObj[i]-sEgo > 0 && sObj[i]-sEgo < dFront){
          if(abs(lObj[i]) < (wLane)*0.5){
            front = true;
            if(iFront != -1){
              if(sObj[i] < sObj[iFront]) iFront = i;
            }
            else iFront = i;
          }
          else if(lObj[i] > 0 && abs(lObj[i]) < wLane*1.5){
            rightFront = true;
            if(iRightFront != -1){
              if(sObj[i] < sObj[iRightFront]) iRightFront = i;
            }
            else iRightFront = i;
          }
          else if(lObj[i] < 0 && abs(lObj[i]) < wLane*1.5)
          {
            leftFront = true;
            if(iLeftFront != -1){
              if(sObj[i] < sObj[iLeftFront]) iLeftFront = i;
            }
            else iLeftFront = i;
          }
          if(sObj[i]-sEgo > 0 && sObj[i]-sEgo < dClose){
            if(abs(lObj[i]) < (wLane-carWidth)*0.5){
              closeFront = true;
              if(iCloseFront != -1){
                if(sObj[i] < sObj[iCloseFront]) iCloseFront = i;
              }
              else iCloseFront = i;
            }
            else if(lObj[i] > 0 && abs(lObj[i]) < wLane*1.5){
              rightCloseFront = true;
              if(iRightCloseFront != -1){
                if(sObj[i] < sObj[iRightCloseFront]) iRightCloseFront = i;
              }
              else iRightCloseFront = i;
            }
            else if(lObj[i] < 0 && abs(lObj[i]) < wLane*1.5)
            {
              leftCloseFront = true;
              if(iLeftCloseFront != -1){
                if(sObj[i] < sObj[iLeftCloseFront]) iLeftCloseFront = i;
              }
              else iLeftCloseFront = i;
            }
          }
        }
      }
      // ROS_INFO("front: %d, rightFront: %d, leftFront: %d",front,rightFront,leftFront);
      // ROS_INFO("rear: %d, rightRear: %d, leftRear: %d",rear,rightRear,leftRear);
      // ROS_INFO("leftOpponent: %d, rightOpponent: %d",leftOpponent,rightOpponent);
      if(front || leftFront || rightFront){

        if(rightFront){
          // if(abs(lObj[iRightFront]-lEgo) < wLane*0.8 && sObj[iRightFront]-sEgo < dAEB){
          //   ROS_INFO("AEB :: RIGHT FRONT OBJECT %fM AHEAD", sObj[iRightFront]-sEgo);
          //   aeb = true;
          // }
          // else 
          if(abs(lObj[iRightFront]-lEgo) < wLane*0.8 && (sObj[iRightFront]-sEgo < dLC || (dsEgo > dsObj[iRightFront] && (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) > 0 && (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) < ttcLC)) && dsObj[iRightFront] > 0){
            obsAvoid = true;
            ROS_INFO("RIGHT FRONT TTC : %f", (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]));
            ROS_INFO("r dsObj %f", dsObj[iRightFront]);
            if(sObj[iRightFront]-sEgo < dAEB){
              ROS_INFO("AEB :: RIGHT FRONT OBJECT %fM AHEAD", sObj[iRightFront]-sEgo);
              aeb = true;
              aeb_width = abs(lObj[iRightFront]-lEgo);
              aeb_ttc = (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]);
              dist2aebobj = sObj[iRightFront]-sEgo;
            } 
            else if((sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) > 0 && (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) < ttcAEB){
              ROS_INFO("AEB :: RIGHT FRONT OBJECT WITH TTC %f", (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]));
              aeb = true;
              aeb_width = abs(lObj[iRightFront]-lEgo);
              aeb_ttc = (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]);
              dist2aebobj = sObj[iRightFront]-sEgo;
            }
            else if(sObj[iRightFront]-sEgo < dACC && leftOpponent){
              ROS_INFO("ACC :: RIGHT FRONT OBJECT %fM AHEAD", sObj[iRightFront]-sEgo);
              acc = true;
            }
            else if((sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) > 0 && (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) < ttcACC && leftOpponent){
              ROS_INFO("ACC :: RIGHT FRONT OBJECT WITH TTC %f", (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]));
              acc = true;
            }
            else if(!leftOpponent && (prev_llc_flag || (desVel-dsObj[iRightFront] > 2)) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
            // else if(!leftOpponent && (prev_llc_flag || (desVel-dsObj[iRightFront] > 2 && dsEgo-dsObj[iRightFront] > 2)) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
              if(front){
                if((sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) > (sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront])){
                  ROS_INFO("GO TO LEFT :: LEFT HIGH TTC");
                  llc_flag = true;
                }
                else{
                  acc = true;
                  ROS_INFO("ACC :: RIGHT FRONT OBJECT LEFT LOW TTC");
                }
              }
              else{
                ROS_INFO("GO TO LEFT :: RIGHT FRONT OBJECT");
                llc_flag = true;                
              }
            }
            else{
              ROS_INFO("ACC :: RIGHT FRONT OBJECT WITH LEFT OBJECT");
              acc = true;
            } 
          }
        }
        if(leftFront){
          // if(abs(lObj[iLeftFront]-lEgo) < wLane*0.8 && sObj[iLeftFront]-sEgo < dAEB){
          //   ROS_INFO("AEB :: LEFT FRONT OBJECT %fM AHEAD", sObj[iLeftFront]-sEgo);
          //   aeb = true;
          // }
          // else 
          if(abs(lObj[iLeftFront]-lEgo) < wLane*0.8 && (sObj[iLeftFront]-sEgo < dLC || (dsEgo > dsObj[iLeftFront] && (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) > 0 && (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) < ttcLC)) && dsObj[iLeftFront] > 0){
            obsAvoid = true;
            ROS_INFO("LEFT FRONT TTC: %f", (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]));
            ROS_INFO("l dsObj %f", dsObj[iLeftFront]);
            if(sObj[iLeftFront]-sEgo < dAEB){
              ROS_INFO("AEB :: LEFT FRONT OBJECT %fM AHEAD", sObj[iLeftFront]-sEgo);
              aeb = true;
              aeb_width = abs(lObj[iLeftFront]-lEgo);
              aeb_ttc = (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]);
              dist2aebobj = sObj[iLeftFront]-sEgo;
            }
            else if((sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) > 0 && (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) < ttcAEB){
              ROS_INFO("AEB :: LEFT FRONT OBJECT WITH TTC %f", (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]));
              aeb = true;
              aeb_width = abs(lObj[iLeftFront]-lEgo);
              aeb_ttc = (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]);
              dist2aebobj = sObj[iLeftFront]-sEgo;
            }
            else if(sObj[iLeftFront]-sEgo < dACC && rightOpponent){
              ROS_INFO("ACC :: LEFT FRONT OBJECT %fM AHEAD", sObj[iLeftFront]-sEgo);
              acc = true;
            }
            else if((sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) > 0 && (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) < ttcACC && rightOpponent){
              ROS_INFO("ACC :: LEFT FRONT OBJECT WITH TTC %f", (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]));
              acc = true;
            }
            else if(!rightOpponent && (prev_rlc_flag || (desVel-dsObj[iLeftFront] > 2))){
            // else if(!rightOpponent && (prev_rlc_flag || (desVel-dsObj[iLeftFront] > 2 && dsEgo-dsObj[iLeftFront] > 2))){
              if(front){
                if((sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) > (sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront])){
                  ROS_INFO("GO TO RIGHT :: RIGHT HIGH TTC");
                  rlc_flag = true;
                }
                else{
                  acc = true;
                  ROS_INFO("ACC :: LEFT FRONT OBJECT RIGHT LOW TTC");
                }
              }
              else{
                ROS_INFO("GO TO RIGHT :: LEFT FRONT OBJECT");
                rlc_flag = true;                
              }

            }
            else{
              ROS_INFO("ACC :: LEFT FRONT OBJECT WITH RIGHT OBJECT");
              acc = true;
            } 
          }
        }         
        if(front){
          // if(abs(lObj[iFront]-lEgo) < wLane*0.8 && sObj[iFront]-sEgo < dAEB){
          //   ROS_INFO("AEB :: FRONT OBJECT %fM AHEAD", sObj[iFront]-sEgo);
          //   aeb = true;
          // }
          // else 
          if(abs(lObj[iFront]-lEgo) < wLane*0.8 && (sObj[iFront]-sEgo < dLC || (dsEgo > dsObj[iFront] && (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) > 0 && (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) < ttcLC)) && dsObj[iFront] > 0){
            obsAvoid = true;
            ROS_INFO("FRONT TTC : %f", (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]));
            ROS_INFO("f dsObj %f", dsObj[iFront]);
            if(sObj[iFront]-sEgo < dAEB){
              ROS_INFO("AEB :: FRONT OBJECT %fM AHEAD", sObj[iFront]-sEgo);
              aeb = true;
              aeb_width = abs(lObj[iFront]-lEgo);
              aeb_ttc = (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]);
              dist2aebobj = sObj[iFront]-sEgo;
            }
            else if((sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) > 0 && (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) < ttcAEB){
              ROS_INFO("AEB :: FRONT OBJECT WITH TTC %f", (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]));
              aeb = true;
              aeb_width = abs(lObj[iFront]-lEgo);
              aeb_ttc = (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]);
              dist2aebobj = sObj[iFront]-sEgo;
            }
            else if(sObj[iFront]-sEgo < dACC  && leftOpponent && rightOpponent){
              ROS_INFO("ACC :: FRONT OBJECT %fM AHEAD", sObj[iFront]-sEgo);
              acc = true;
            }
            else if((sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) > 0 && (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]) < ttcACC  && leftOpponent && rightOpponent){
              ROS_INFO("ACC :: FRONT OBJECT WITH TTC %f", (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront]));
              acc = true;
            }
            else if(!leftOpponent && rightFront && !leftFront && (desVel-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
            // else if(!leftOpponent && rightFront && !leftFront && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
              llc_flag = true;
              ROS_INFO("GO TO LEFT :: FRONT OBJECT WITH RIGHT OBJECT");
            }
            else if(!rightOpponent && leftFront && !rightFront && (desVel-dsObj[iFront] > 2)){
            // else if(!rightOpponent && leftFront && !rightFront && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2)){
              rlc_flag = true;
              ROS_INFO("GO TO RIGHT :: FRONT OBJECT WITH LEFT OBJECT");
            } 
            else if(!leftOpponent && rightOpponent && (desVel-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
            // else if(!leftOpponent && rightOpponent && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){              
              if(leftFront){
                if((sObj[iLeftFront]-sEgo)/(dsEgo-dsObj[iLeftFront]) > (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront])){
                  ROS_INFO("GO TO LEFT :: LEFT HIGH TTC");
                  llc_flag = true;
                }
                else{
                  acc = true;
                  ROS_INFO("ACC :: FRONT OBJECT LEFT LOW TTC");
                }
              }
              else{
                llc_flag = true;
                ROS_INFO("GO TO LEFT :: FRONT OBJECT WITH RIGHT OBJECT");                
              }
            }
            else if(!rightOpponent && leftOpponent && (desVel-dsObj[iFront] > 2)){
            // else if(!rightOpponent && leftOpponent && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2)){
              if(rightFront){
                if((sObj[iRightFront]-sEgo)/(dsEgo-dsObj[iRightFront]) > (sObj[iFront]-sEgo)/(dsEgo-dsObj[iFront])){
                  ROS_INFO("GO TO RIGHT :: RIGHT HIGH TTC");
                  rlc_flag = true;
                }
                else{
                  acc = true;
                  ROS_INFO("ACC :: FRONT OBJECT RIGHT LOW TTC");
                }
              }
              else{
                rlc_flag = true;
                ROS_INFO("GO TO RIGHT :: FRONT OBJECT WITH LEFT OBJECT");
              }
            }            
            // else if(prev_llc_flag && !leftOpponent){
            else if(prev_llc_flag && !leftOpponent && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
              llc_flag = true;
              ROS_INFO("GO TO LEFT :: FRONT OBJECT KEEP PREVIOUS FLAG");
            }
            else if(prev_rlc_flag && !rightOpponent){
              rlc_flag = true;
              ROS_INFO("GO TO RIGHT :: FRONT OBJECT KEEP PREVIOUS FLAG");
            }
            else if(lEgo <= 0 && !leftOpponent  && (desVel-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
            // else if(lEgo <= 0 && !leftOpponent  && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
              ROS_INFO("GO TO LEFT :: FRONT OBJECT EGO ON LEFT");
              llc_flag = true;
            } 
            else if(lEgo > 0 && !rightOpponent && (desVel-dsObj[iFront] > 2)){
            // else if(lEgo > 0 && !rightOpponent && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2)){
              ROS_INFO("GO TO RIGHT :: FRONT OBJECT EGO ON RIGHT");
              rlc_flag = true;
            }
            else if(lObj[iFront] >= 0 && !leftOpponent && (desVel-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
            // else if(lObj[iFront] >= 0 && !leftOpponent && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2) && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
              ROS_INFO("GO TO LEFT :: FRONT OBJECT ON SLIGHT RIGHT");
              llc_flag = true;
            }
            else if(lObj[iFront] < 0 && !rightOpponent && (desVel-dsObj[iFront] > 2)){
            // else if(lObj[iFront] < 0 && !rightOpponent && (desVel-dsObj[iFront] > 2 && dsEgo-dsObj[iFront] > 2)){
              ROS_INFO("GO TO RIGHT :: FRONT OBJECT ON SLIGHT LEFT");
              rlc_flag = true;
            }
            else{
              ROS_INFO("ACC :: FRONT OBJECT WITH LEFT OBJECT");
              acc = true;
            }
          }
        }
      }
    }
  }
  if((prev_llc_flag || prev_rlc_flag) && acc) keep_flag = true;
  if(!llc_flag && !rlc_flag && !acc){
    if(leftSide && rightSide){
      ROS_INFO("KEEP LANE :: OBJECT ON LEFT AND RIGHT SIDE");
      keep_flag = true;
    }
    else if(leftSide){
      if(!rightOpponent){
        ROS_INFO("GO TO RIGHT :: OBJECT ON LEFT SIDE");
        rlc_flag = true;
        keep_flag = false;
      }
      else{
        ROS_INFO("KEEP LANE :: OBJECT ON LEFT AND RIGHT SIDE");
        keep_flag = true;
      }
    }
    else if(rightSide){
      // if(!leftOpponent){
      if(!leftOpponent && !(lEgo < 0 && firstlap_flag) && !(isInBank && lEgo < -3.0)){
        ROS_INFO("GO TO LEFT :: OBJECT ON RIGHT SIDE");
        llc_flag = true;
        keep_flag = false;
      }
      else{
        ROS_INFO("KEEP LANE :: OBJECT ON LEFT AND RIGHT SIDE");
        keep_flag = true;
      }
    }
    // else if(leftSideFar){
    //   ROS_INFO("KEEP LANE :: OBJECT ON FAR LEFT SIDE");
    //   keep_flag = true;
    // }
    // else if(rightSideFar){
    //   ROS_INFO("KEEP LANE :: OBJECT ON FAR RIGHT SIDE");
    //   keep_flag = true;
    // }
    else if(abs(lOpt) > dBack2opt){
      if(lOptFar - lEgo > 0 && -lOpt < 0){
        ROS_INFO("KEEP LANE :: NOT GOOD TO BACK TO OPTIMAL");
        keep_flag = true; 
      }
      else if(lOptFar - lEgo < 0 && -lOpt > 0){
        ROS_INFO("KEEP LANE :: NOT GOOD TO BACK TO OPTIMAL");
        keep_flag = true; 
      } 
      // else if(abs(lOptFar-lEgo) < abs(lOpt)){
      //   ROS_INFO("KEEP LANE :: NOT GOOD TO BACK TO OPTIMAL");
      //   keep_flag = true;
      // }
      else if(lOpt >= 0){
        if(!leftOpponent && !objOnOpt){
          ROS_INFO("GO TO LEFT :: BACK TO OPTIMAL");
          llc_flag = true;
        } 
        else{
          ROS_INFO("KEEP LANE :: OBJECT ON OPTIMAL");
          keep_flag = true;
        }
      }
      else{
        if(!rightOpponent && !objOnOpt){
          ROS_INFO("GO TO RIGHT :: BACK TO OPTIMAL");
          rlc_flag = true;
        } 
        else{
          ROS_INFO("KEEP LANE :: OBJECT ON OPTIMAL");
          keep_flag = true;
        } 
      }
    }
    else if(objOnOpt){
      ROS_INFO("KEEP LANE :: OBJECT ON OPTIMAL");
      keep_flag = true;
    }
    // else if(!firstlap_flag && current_pos.speed < 85/3.6 && isInBank && current_lane_id == 0 && !rlc_flag){
    //   llc_flag = true;
    //   lowSpeedBank = true;
    //   ROS_INFO("LEFT TRAJ :: LOW SPEED IN BANK");
    // }
    else{
      ROS_INFO("FOLLOW OPTIMAL :: NO CRITICAL OBJECT");
    }
  }
  // if(acc) keep_flag = true;
  // ROS_INFO("prev_llc_flag: %d, prev_rlc_flag: %d",prev_llc_flag,prev_rlc_flag);
  // ROS_INFO("llc_flag: %d, rlc_flag: %d",llc_flag,rlc_flag);
  // ROS_INFO("prev_keep_flag: %d, keep_flag: %d",prev_keep_flag,keep_flag);
  
  
  if(abs(lOpt) > 0.7 && acc) keep_flag = true;
  prev_llc_flag = llc_flag;
  prev_rlc_flag = rlc_flag;
  prev_keep_flag = keep_flag;
  std_msgs::Int8 ot_msg;
  if(aeb) ot_msg.data = 4;
  else if(acc) ot_msg.data = 2;
  else if(obsAvoid) ot_msg.data = 3;
  else if(llc_flag || rlc_flag || keep_flag) ot_msg.data = 1;
  else ot_msg.data = 0;
  // ot_msg.data = 0;
  flag_pub.publish(ot_msg);
  ROS_INFO("AEB %f  %f" ,dist2aebobj, current_pos.speed*current_pos.speed/(2*4.5)+dAEB);
  if(aeb && dist2aebobj < current_pos.speed*current_pos.speed/(2*4.5)+dAEB && current_pos.speed > 60/3.6 && aeb_ttc < 1.5 && aeb_width < carWidth){
    can_aeb = true;
    ROS_INFO("!!!!!!!!!!!!!AEB!!!!!!!AEB!!!!!!!!!!!!!");
  }
  std_msgs::Int8 aeb_msg;
  if(can_aeb){
    aeb_msg.data = 1;
  }
  else{
    aeb_msg.data = 0;
  }
  aeb_pub.publish(aeb_msg);
}

void localplanners2::compute_local_path(){
  int local_size = 100;
  local_lane = optimal_lane_array.lanes[0];
  int minidx = calculate_distance_pose2local();
  local_lane.waypoints.clear();
  local_lane.header.frame_id = "map";
  local_lane.header.stamp = ros::Time::now();
  for(int i=minidx+1; i<optimal_lane_array.lanes[0].waypoints.size(); i++){
    if(optimal_lane_array.lanes[0].waypoints.size()<minidx+2){
      ROS_INFO("LACK OF POINTS FOR LOCAL");
      break;
    }
    hmcl_msgs::Waypoint wp;
    // double wp1x = optimal_lane_array.lanes[0].waypoints[i-1].pose.pose.position.x;
    // double wp1y = optimal_lane_array.lanes[0].waypoints[i-1].pose.pose.position.y;
    // double wp2x = optimal_lane_array.lanes[0].waypoints[i].pose.pose.position.x;
    // double wp2y = optimal_lane_array.lanes[0].waypoints[i].pose.pose.position.y;
    // double dist = distance(wp1x,wp1y,wp2x,wp2y);
    // if(dist > 0.5){
    //   int n = static_cast<int>(dist/0.5);
    //   // ROS_INFO("ADD %d WAYPOINTS", n);
    //   for(int j = 0; j < n-1; j++){
    //     wp = optimal_lane_array.lanes[0].waypoints[i-1];
    //     wp.pose.pose.position.x = wp1x+(wp2x-wp1x)/n*(j+1);
    //     wp.pose.pose.position.y = wp1y+(wp2y-wp1y)/n*(j+1);
    //     local_lane.waypoints.push_back(wp);
    //     if(local_lane.waypoints.size()>local_size) break;        
    //   }
    // }
    // if(i%2 == 1){
    wp = optimal_lane_array.lanes[0].waypoints[i];
    local_lane.waypoints.push_back(wp);
    // }
    if(local_lane.waypoints.size()>=local_size) break;        

  }
  for(int i=0; i<local_size-2; i++){
    float yaw_tmp = get_yaw(local_lane.waypoints[i].pose.pose.position,local_lane.waypoints[i+2].pose.pose.position);
    tf2::Quaternion q;
    q.setRPY(0, 0, yaw_tmp);
    q=q.normalize();
    local_lane.waypoints[i].pose.pose.orientation.x = q[0];
    local_lane.waypoints[i].pose.pose.orientation.y = q[1];
    local_lane.waypoints[i].pose.pose.orientation.z = q[2];
    local_lane.waypoints[i].pose.pose.orientation.w = q[3];
    double dx1 = local_lane.waypoints[i+1].pose.pose.position.x-local_lane.waypoints[i].pose.pose.position.x;
    double dy1 = local_lane.waypoints[i+1].pose.pose.position.y-local_lane.waypoints[i].pose.pose.position.y;
    double dx2 = local_lane.waypoints[i+2].pose.pose.position.x-local_lane.waypoints[i+1].pose.pose.position.x;
    double dy2 = local_lane.waypoints[i+2].pose.pose.position.y-local_lane.waypoints[i+1].pose.pose.position.y;
    double ddx = dx2-dx1;
    double ddy = dy2-dy1;
    local_lane.waypoints[i].curvature = std::sqrt(std::pow(ddx,2)+std::pow(ddy,2));
  }
  local_lane.waypoints[local_size-2].curvature = local_lane.waypoints[local_size-3].curvature;
  local_lane.waypoints[local_size-1].curvature = local_lane.waypoints[local_size-3].curvature;
  local_traj_available = true;
  // ROS_INFO("local size: %zu",local_lane.waypoints.size());
}

void localplanners2::compute_keep_local_path(){
  float l_shift = 0.3;
  int local_size = 100;
  // ROS_INFO("LEFT");
  // ROS_INFO("%d",current_lane_id);
  local_lane = global_lane_array.lanes[1];
  int minidx = calculate_distance_pose2local();
  local_lane.waypoints.clear();
  local_lane.header.frame_id = "map";
  local_lane.header.stamp = ros::Time::now();
  cur_local_lane = global_lane_array.lanes[1];
  int minleftidx;
  if(lEgo<0){
    left_local_lane = global_lane_array.lanes[0];
    minleftidx = calculate_distance_pose2leftlocal();
  }
  else{
    left_local_lane = global_lane_array.lanes[2];
    minleftidx = calculate_distance_pose2leftlocal();
  }
  int midsize = cur_local_lane.waypoints.size();
  int leftsize = left_local_lane.waypoints.size();
  local_size = std::min(std::min(local_size,midsize-minidx),leftsize-minleftidx);
  for(int i=0; i<local_size; i++){
    // if(i%2 == 1) continue;
    if(global_lane_array.lanes[1].waypoints.size()<minidx+2){
      ROS_INFO("LACK OF POINTS FOR LOCAL");
      break;
    }
    hmcl_msgs::Waypoint wp;
    double wp1x = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.x;
    double wp1y = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.y;
    double wp2x;
    double wp2y;
    if(lEgo<0){
      wp2x = global_lane_array.lanes[0].waypoints[minleftidx+i].pose.pose.position.x;
      wp2y = global_lane_array.lanes[0].waypoints[minleftidx+i].pose.pose.position.y;
    }
    else{
      wp2x = global_lane_array.lanes[2].waypoints[minleftidx+i].pose.pose.position.x;
      wp2y = global_lane_array.lanes[2].waypoints[minleftidx+i].pose.pose.position.y;
    }
    double dist = distance(wp1x,wp1y,wp2x,wp2y);
    // double dist2curpose = distance(wp1x,wp1y,pose_x,pose_y);
    // l_shift = min(max(0.5-lEgo/dist,0.0),1.0);
    double dist2curpose = lEgo;
    if(lEgo<0) l_shift = min(max(-dist2curpose/dist,0.0),1.0);
    else l_shift = min(max(dist2curpose/dist,0.0),1.0);
    wp = global_lane_array.lanes[1].waypoints[minidx+i];
    wp.pose.pose.position.x = wp1x+(wp2x-wp1x)*(l_shift);
    wp.pose.pose.position.y = wp1y+(wp2y-wp1y)*(l_shift);
    // wp.pose.pose.position.x = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.x;
    // wp.pose.pose.position.y = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.y;
    local_lane.waypoints.push_back(wp);
  }
  for(int i=0; i<local_size-2; i++){
    float yaw_tmp = get_yaw(local_lane.waypoints[i].pose.pose.position,local_lane.waypoints[i+2].pose.pose.position);
    tf2::Quaternion q;
    q.setRPY(0, 0, yaw_tmp);
    q=q.normalize();
    local_lane.waypoints[i].pose.pose.orientation.x = q[0];
    local_lane.waypoints[i].pose.pose.orientation.y = q[1];
    local_lane.waypoints[i].pose.pose.orientation.z = q[2];
    local_lane.waypoints[i].pose.pose.orientation.w = q[3];
    double dx1 = local_lane.waypoints[i+1].pose.pose.position.x-local_lane.waypoints[i].pose.pose.position.x;
    double dy1 = local_lane.waypoints[i+1].pose.pose.position.y-local_lane.waypoints[i].pose.pose.position.y;
    double dx2 = local_lane.waypoints[i+2].pose.pose.position.x-local_lane.waypoints[i+1].pose.pose.position.x;
    double dy2 = local_lane.waypoints[i+2].pose.pose.position.y-local_lane.waypoints[i+1].pose.pose.position.y;
    double ddx = dx2-dx1;
    double ddy = dy2-dy1;
    local_lane.waypoints[i].curvature = std::sqrt(std::pow(ddx,2)+std::pow(ddy,2));
  }
  local_lane.waypoints[local_size-2].curvature = local_lane.waypoints[local_size-3].curvature;
  local_lane.waypoints[local_size-1].curvature = local_lane.waypoints[local_size-3].curvature;
  local_lane.waypoints[local_size-2].pose.pose.orientation.x = local_lane.waypoints[local_size-3].pose.pose.orientation.x;
  local_lane.waypoints[local_size-2].pose.pose.orientation.y = local_lane.waypoints[local_size-3].pose.pose.orientation.y;
  local_lane.waypoints[local_size-2].pose.pose.orientation.z = local_lane.waypoints[local_size-3].pose.pose.orientation.z;
  local_lane.waypoints[local_size-2].pose.pose.orientation.w = local_lane.waypoints[local_size-3].pose.pose.orientation.w;
  local_lane.waypoints[local_size-1].pose.pose.orientation.x = local_lane.waypoints[local_size-3].pose.pose.orientation.x;
  local_lane.waypoints[local_size-1].pose.pose.orientation.y = local_lane.waypoints[local_size-3].pose.pose.orientation.y;
  local_lane.waypoints[local_size-1].pose.pose.orientation.z = local_lane.waypoints[local_size-3].pose.pose.orientation.z;
  local_lane.waypoints[local_size-1].pose.pose.orientation.w = local_lane.waypoints[local_size-3].pose.pose.orientation.w;
  local_traj_available = true;
  // ROS_INFO("left local size: %zu",local_lane.waypoints.size());
}
void localplanners2::compute_left_local_path(){
  float l_shift = 0.3;
  int local_size = 100;
  // ROS_INFO("LEFT");
  // ROS_INFO("%d",current_lane_id);
  local_lane = global_lane_array.lanes[1];
  int minidx = calculate_distance_pose2local();
  local_lane.waypoints.clear();
  local_lane.header.frame_id = "map";
  local_lane.header.stamp = ros::Time::now();
  cur_local_lane = global_lane_array.lanes[1];
  int minleftidx;
  if(lEgo<0){
    left_local_lane = global_lane_array.lanes[0];
    minleftidx = calculate_distance_pose2leftlocal();
  }
  else{
    left_local_lane = global_lane_array.lanes[2];
    minleftidx = calculate_distance_pose2leftlocal();
  }
  int midsize = cur_local_lane.waypoints.size();
  int leftsize = left_local_lane.waypoints.size();
  local_size = std::min(std::min(local_size,midsize-minidx),leftsize-minleftidx);
  for(int i=0; i<local_size; i++){
    // if(i%2 == 1) continue;
    if(global_lane_array.lanes[1].waypoints.size()<minidx+2){
      ROS_INFO("LACK OF POINTS FOR LOCAL");
      break;
    }
    hmcl_msgs::Waypoint wp;
    double wp1x = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.x;
    double wp1y = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.y;
    double wp2x;
    double wp2y;
    if(lEgo<0){
      wp2x = global_lane_array.lanes[0].waypoints[minleftidx+i].pose.pose.position.x;
      wp2y = global_lane_array.lanes[0].waypoints[minleftidx+i].pose.pose.position.y;
    }
    else{
      wp2x = global_lane_array.lanes[2].waypoints[minleftidx+i].pose.pose.position.x;
      wp2y = global_lane_array.lanes[2].waypoints[minleftidx+i].pose.pose.position.y;
    }
    double dist = distance(wp1x,wp1y,wp2x,wp2y);
    // double dist2curpose = distance(wp1x,wp1y,pose_x,pose_y);
    // l_shift = min(max(0.5-lEgo/dist,0.0),1.0);
    double dist2curpose = lEgo;
    if(lowSpeedBank && current_pos.speed < 93/3.6){
      if(lEgo<0) l_shift = min(max(0.2-dist2curpose/dist,0.0),0.9);
      else l_shift = min(-0.2+dist2curpose/dist,1.0);
    }
    else if(lowSpeedBank && current_pos.speed < 108/3.6){
      if(lEgo<0) l_shift = min(max(0.2-dist2curpose/dist,0.0),0.9);
      else l_shift = min(-0.2+dist2curpose/dist,1.0);
    }
    else if(current_pos.speed > 95/3.6){
      if(lEgo<0) l_shift = min(max(0.2-dist2curpose/dist,0.0),1.0);
      else if(firstlap_flag) l_shift = min(max(-0.2+dist2curpose/dist,0.0),1.0);
      else l_shift = min(-0.2+dist2curpose/dist,1.0);
    }
    else{
      if(lEgo<0) l_shift = min(max(0.3-dist2curpose/dist,0.0),1.0);
      else if(firstlap_flag) l_shift = min(max(-0.3+dist2curpose/dist,0.0),1.0);
      else l_shift = min(-0.3+dist2curpose/dist,1.0);
    }
    
    wp = global_lane_array.lanes[1].waypoints[minidx+i];
    wp.pose.pose.position.x = wp1x+(wp2x-wp1x)*(l_shift);
    wp.pose.pose.position.y = wp1y+(wp2y-wp1y)*(l_shift);
    local_lane.waypoints.push_back(wp);
  }
  for(int i=0; i<local_size-2; i++){
    float yaw_tmp = get_yaw(local_lane.waypoints[i].pose.pose.position,local_lane.waypoints[i+2].pose.pose.position);
    tf2::Quaternion q;
    q.setRPY(0, 0, yaw_tmp);
    q=q.normalize();
    local_lane.waypoints[i].pose.pose.orientation.x = q[0];
    local_lane.waypoints[i].pose.pose.orientation.y = q[1];
    local_lane.waypoints[i].pose.pose.orientation.z = q[2];
    local_lane.waypoints[i].pose.pose.orientation.w = q[3];
    double dx1 = local_lane.waypoints[i+1].pose.pose.position.x-local_lane.waypoints[i].pose.pose.position.x;
    double dy1 = local_lane.waypoints[i+1].pose.pose.position.y-local_lane.waypoints[i].pose.pose.position.y;
    double dx2 = local_lane.waypoints[i+2].pose.pose.position.x-local_lane.waypoints[i+1].pose.pose.position.x;
    double dy2 = local_lane.waypoints[i+2].pose.pose.position.y-local_lane.waypoints[i+1].pose.pose.position.y;
    double ddx = dx2-dx1;
    double ddy = dy2-dy1;
    local_lane.waypoints[i].curvature = std::sqrt(std::pow(ddx,2)+std::pow(ddy,2));
  }
  local_lane.waypoints[local_size-2].curvature = local_lane.waypoints[local_size-3].curvature;
  local_lane.waypoints[local_size-1].curvature = local_lane.waypoints[local_size-3].curvature;  local_lane.waypoints[local_size-2].pose.pose.orientation.x = local_lane.waypoints[local_size-3].pose.pose.orientation.x;
  local_lane.waypoints[local_size-2].pose.pose.orientation.y = local_lane.waypoints[local_size-3].pose.pose.orientation.y;
  local_lane.waypoints[local_size-2].pose.pose.orientation.z = local_lane.waypoints[local_size-3].pose.pose.orientation.z;
  local_lane.waypoints[local_size-2].pose.pose.orientation.w = local_lane.waypoints[local_size-3].pose.pose.orientation.w;
  local_lane.waypoints[local_size-1].pose.pose.orientation.x = local_lane.waypoints[local_size-3].pose.pose.orientation.x;
  local_lane.waypoints[local_size-1].pose.pose.orientation.y = local_lane.waypoints[local_size-3].pose.pose.orientation.y;
  local_lane.waypoints[local_size-1].pose.pose.orientation.z = local_lane.waypoints[local_size-3].pose.pose.orientation.z;
  local_lane.waypoints[local_size-1].pose.pose.orientation.w = local_lane.waypoints[local_size-3].pose.pose.orientation.w;
  local_traj_available = true;
  // ROS_INFO("left local size: %zu",local_lane.waypoints.size());
}
void localplanners2::compute_right_local_path(){
  float l_shift = 0.3;
  int local_size = 100;
  // ROS_INFO("LEFT");
  // ROS_INFO("%d",current_lane_id);
  local_lane = global_lane_array.lanes[1];
  int minidx = calculate_distance_pose2local();
  local_lane.waypoints.clear();
  local_lane.header.frame_id = "map";
  local_lane.header.stamp = ros::Time::now();
  cur_local_lane = global_lane_array.lanes[1];
  int minleftidx;
  if(lEgo<0){
    left_local_lane = global_lane_array.lanes[0];
    minleftidx = calculate_distance_pose2leftlocal();
  }
  else{
    left_local_lane = global_lane_array.lanes[2];
    minleftidx = calculate_distance_pose2leftlocal();
  }
  int midsize = cur_local_lane.waypoints.size();
  int leftsize = left_local_lane.waypoints.size();
  local_size = std::min(std::min(local_size,midsize-minidx),leftsize-minleftidx);
  for(int i=0; i<local_size; i++){
    // if(i%2 == 1) continue;
    if(global_lane_array.lanes[1].waypoints.size()<minidx+2){
      ROS_INFO("LACK OF POINTS FOR LOCAL");
      break;
    }
    hmcl_msgs::Waypoint wp;
    double wp1x = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.x;
    double wp1y = global_lane_array.lanes[1].waypoints[minidx+i].pose.pose.position.y;
    double wp2x;
    double wp2y;
    if(lEgo<0){
      wp2x = global_lane_array.lanes[0].waypoints[minleftidx+i].pose.pose.position.x;
      wp2y = global_lane_array.lanes[0].waypoints[minleftidx+i].pose.pose.position.y;
    }
    else{
      wp2x = global_lane_array.lanes[2].waypoints[minleftidx+i].pose.pose.position.x;
      wp2y = global_lane_array.lanes[2].waypoints[minleftidx+i].pose.pose.position.y;
    }
    double dist = distance(wp1x,wp1y,wp2x,wp2y);
    // double dist2curpose = distance(wp1x,wp1y,pose_x,pose_y);
    // l_shift = min(max(0.5-lEgo/dist,0.0),1.0);
    double dist2curpose = lEgo;
    if(dsEgo > 95/3.6){
      if(lEgo<0) l_shift = min(-0.2-dist2curpose/dist,1.0);
      else l_shift = min(max(0.2+dist2curpose/dist,0.0),1.0);
    }
    else{
      if(lEgo<0) l_shift = min(-0.3-dist2curpose/dist,1.0);
      else l_shift = min(max(0.3+dist2curpose/dist,0.0),1.0);      
    }
    wp = global_lane_array.lanes[1].waypoints[minidx+i];
    wp.pose.pose.position.x = wp1x+(wp2x-wp1x)*(l_shift);
    wp.pose.pose.position.y = wp1y+(wp2y-wp1y)*(l_shift);
    local_lane.waypoints.push_back(wp);
  }
  for(int i=0; i<local_size-2; i++){
    float yaw_tmp = get_yaw(local_lane.waypoints[i].pose.pose.position,local_lane.waypoints[i+2].pose.pose.position);
    tf2::Quaternion q;
    q.setRPY(0, 0, yaw_tmp);
    q=q.normalize();
    local_lane.waypoints[i].pose.pose.orientation.x = q[0];
    local_lane.waypoints[i].pose.pose.orientation.y = q[1];
    local_lane.waypoints[i].pose.pose.orientation.z = q[2];
    local_lane.waypoints[i].pose.pose.orientation.w = q[3];
    double dx1 = local_lane.waypoints[i+1].pose.pose.position.x-local_lane.waypoints[i].pose.pose.position.x;
    double dy1 = local_lane.waypoints[i+1].pose.pose.position.y-local_lane.waypoints[i].pose.pose.position.y;
    double dx2 = local_lane.waypoints[i+2].pose.pose.position.x-local_lane.waypoints[i+1].pose.pose.position.x;
    double dy2 = local_lane.waypoints[i+2].pose.pose.position.y-local_lane.waypoints[i+1].pose.pose.position.y;
    double ddx = dx2-dx1;
    double ddy = dy2-dy1;
    local_lane.waypoints[i].curvature = std::sqrt(std::pow(ddx,2)+std::pow(ddy,2));
  }
  local_lane.waypoints[local_size-2].curvature = local_lane.waypoints[local_size-3].curvature;
  local_lane.waypoints[local_size-1].curvature = local_lane.waypoints[local_size-3].curvature;  local_lane.waypoints[local_size-2].pose.pose.orientation.x = local_lane.waypoints[local_size-3].pose.pose.orientation.x;
  local_lane.waypoints[local_size-2].pose.pose.orientation.y = local_lane.waypoints[local_size-3].pose.pose.orientation.y;
  local_lane.waypoints[local_size-2].pose.pose.orientation.z = local_lane.waypoints[local_size-3].pose.pose.orientation.z;
  local_lane.waypoints[local_size-2].pose.pose.orientation.w = local_lane.waypoints[local_size-3].pose.pose.orientation.w;
  local_lane.waypoints[local_size-1].pose.pose.orientation.x = local_lane.waypoints[local_size-3].pose.pose.orientation.x;
  local_lane.waypoints[local_size-1].pose.pose.orientation.y = local_lane.waypoints[local_size-3].pose.pose.orientation.y;
  local_lane.waypoints[local_size-1].pose.pose.orientation.z = local_lane.waypoints[local_size-3].pose.pose.orientation.z;
  local_lane.waypoints[local_size-1].pose.pose.orientation.w = local_lane.waypoints[local_size-3].pose.pose.orientation.w;
  local_traj_available = true;
  // ROS_INFO("left local size: %zu",local_lane.waypoints.size());
}
void localplanners2::publish_local_path() {
    // ROS_INFO("local pub");

    local_traj_pub.publish(local_lane);
    local_traj_marker_array = visualize_local_path(local_lane);
    l_traj_viz_pub.publish(local_traj_marker_array);
}

//   local_traj_pub.publish(local_lane);
//   local_traj_marker_array = visualize_local_path(local_lane);
//   l_traj_viz_pub.publish(local_traj_marker_array);

// }
void localplanners2::setColor(std_msgs::ColorRGBA* cl, double r, double g, double b, double a)
{
  cl->r = r;
  cl->g = g;
  cl->b = b;
  cl->a = a;
}

visualization_msgs::MarkerArray localplanners2::visualize_local_path(const hmcl_msgs::Lane local_lane){
  std_msgs::ColorRGBA traj_marker_color;
  setColor(&traj_marker_color, 1.0, 0.0, 0.0, 0.5);    
  std_msgs::ColorRGBA in_bank_color;
  setColor(&in_bank_color, 1.0, 1.0, 0.0, 0.5);
  // Construct Traj_marker               
  visualization_msgs::MarkerArray marker_array;
  marker_array.markers.clear();
  for( int j= 0 ; j <local_lane.waypoints.size() ; j++){
    visualization_msgs::Marker marker_tmp;
    marker_tmp.header.stamp = ros::Time::now();
    marker_tmp.header.frame_id = "map" ;
    marker_tmp.id = 50000+j;
    marker_tmp.ns = "ltraj";
    marker_tmp.type = visualization_msgs::Marker::ARROW;
    marker_tmp.action = visualization_msgs::Marker::ADD;                  
    marker_tmp.pose.position.x = local_lane.waypoints[j].pose.pose.position.x;
    marker_tmp.pose.position.y = local_lane.waypoints[j].pose.pose.position.y;
    marker_tmp.pose.position.z = local_lane.waypoints[j].pose.pose.position.z;
    marker_tmp.pose.orientation.x = local_lane.waypoints[j].pose.pose.orientation.x;
    marker_tmp.pose.orientation.y = local_lane.waypoints[j].pose.pose.orientation.y;
    marker_tmp.pose.orientation.z = local_lane.waypoints[j].pose.pose.orientation.z;
    marker_tmp.pose.orientation.w = local_lane.waypoints[j].pose.pose.orientation.w;
    if(local_lane.waypoints[j].bank){
      marker_tmp.color = in_bank_color;
    }
    else{
    marker_tmp.color = traj_marker_color;
    }
    marker_tmp.lifetime = ros::Duration(0.1);
    marker_tmp.scale.x = 0.7;
    marker_tmp.scale.y = 0.4;
    marker_tmp.scale.z = 0.1;                  
    marker_array.markers.push_back(marker_tmp);
  }
  return marker_array;
}
double localplanners2::get_yaw(const geometry_msgs::Point & _from, const geometry_msgs::Point &_to ){
    double _angle = std::atan2(_to.y - _from.y, _to.x - _from.x);
    
    while(_angle > M_PI){
      _angle = _angle - 2*M_PI;
    }
    while(_angle < M_PI){
      _angle = _angle + 2*M_PI;
    }
  return _angle;
}
double localplanners2::distance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
}

int localplanners2::calculate_distance_pose2local(){
  float min_dist = 1000.0;
  float dist = 1000.0;
  int min_idx = 0;

  for(int i=0; i<local_lane.waypoints.size(); i++){
    dist = distance(local_lane.waypoints[i].pose.pose.position.x,local_lane.waypoints[i].pose.pose.position.y,pose_x,pose_y);
    if(min_dist > dist){
      min_dist = dist;
      min_idx=i;
    }
  }

  return min_idx;
}

int localplanners2::calculate_distance_pose2leftlocal(){
  float min_dist = 1000.0;
  float dist = 1000.0;
  int min_idx = 0;

  for(int i=0; i<left_local_lane.waypoints.size(); i++){
    dist = distance(left_local_lane.waypoints[i].pose.pose.position.x,left_local_lane.waypoints[i].pose.pose.position.y,pose_x,pose_y);
    if(min_dist > dist){
      min_dist = dist;
      min_idx=i;
    }
  }

  return min_idx;
}
int localplanners2::calculate_distance_pose2rightlocal(){
  float min_dist = 1000.0;
  float dist = 1000.0;
  int min_idx = 0;

  for(int i=0; i<right_local_lane.waypoints.size(); i++){
    dist = distance(right_local_lane.waypoints[i].pose.pose.position.x,right_local_lane.waypoints[i].pose.pose.position.y,pose_x,pose_y);
    if(min_dist > dist){
      min_dist = dist;
      min_idx=i;
    }
  }

  return min_idx;
}


void localplanners2::viz_local(const hmcl_msgs::Lane& lane){
    visualization_msgs::MarkerArray lane_markers;

    visualization_msgs::Marker lane_marker;
    lane_marker.header.frame_id = "map";
    lane_marker.header.stamp = ros::Time();
    lane_marker.ns = "local_markers";
    lane_marker.id = 2500;
    lane_marker.type = visualization_msgs::Marker::LINE_STRIP;
    lane_marker.action = visualization_msgs::Marker::ADD;

    lane_marker.color.a = 1.0;
    lane_marker.color.r = 0.0;
    lane_marker.color.g = 1.0;
    lane_marker.color.b = 0.0;
   
    lane_marker.scale.x = 1;
    lane_marker.scale.y = 0.1;
    lane_marker.scale.z = 0.1;

    for (int i = 0; i < lane.waypoints.size(); i++){
        geometry_msgs::Point p;
        p.x = lane.waypoints[i].pose.pose.position.x;
        p.y = lane.waypoints[i].pose.pose.position.y;
        lane_marker.points.push_back(p);
    }
    lane_markers.markers.push_back(lane_marker);
    pub_viz.publish(lane_markers);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "localplanners2");
    ros::NodeHandle nh;
    localplanners2 localplanners2(nh);

    ros::spin();
    return 0;
}
