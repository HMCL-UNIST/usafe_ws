#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include "BehaviorStateMachine.h"
#include <cmath>


class DecisionMaker
{
    private:
        bool start, isFront, isLag, isLead, needLC, psbLC, doneLC, isEmergency;
        float gapFront, gapLead, gapLag;
        BehaviorStateMachine behaviorfsm;
        
    public:
        DecisionMaker(){
            this->start = true; // will update after mission planning is done
            this->isFront = false;
            this->isLag = false;
            this->isLead = false;
            this->needLC = false;
            this->psbLC = false;
            this->doneLC = false;
            this->isEmergency = false;
            this->gapFront = 100;
            this->gapLead = 100;
            this->gapLag = 100;
        }

        

        void updateBehaviorState(){
            this->behaviorfsm.updateBehaviorState(this->start, this->isFront, this->needLC, this->psbLC, this->doneLC, this->isEmergency);
        }

        BehaviorState getCurrentBehavior(){
            return this->behaviorfsm.getCurrentBehavior();
        }
};


