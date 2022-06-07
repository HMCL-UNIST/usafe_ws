#ifndef BEHAVIORSTATEMACHINE_H
#define BEHAVIORSTATEMACHINE_H



typedef enum{Init, Cruise, Follow, DecelerationLC, LaneChange, EmergencyBrake} BehaviorState;

class BehaviorStateMachine
{
    private:
        BehaviorState currentBehavior;
    public:
        BehaviorStateMachine(){
            currentBehavior = Init;
        }
        BehaviorStateMachine(BehaviorState state){
            currentBehavior = state;
        }
        BehaviorState getCurrentBehavior(){
            return currentBehavior;
        }
        void updateBehaviorState(bool start, bool isFront, bool needLC, bool psbLC, bool doneLC, bool emergency)
        {   
            if (emergency){
                currentBehavior = EmergencyBrake;
                return;
            }
            switch(currentBehavior)
            {
                case Init:
                    if(start){
                        currentBehavior = Cruise;
                    }
                    break;
                case Cruise:
                    if(isFront){
                        currentBehavior = Follow;
                    }
                    break;
                case Follow:
                    if(needLC){
                        if(psbLC){
                            currentBehavior = LaneChange;
                        }
                        else{
                            currentBehavior = DecelerationLC;
                        }
                    }
                    break;
                case DecelerationLC:
                    if(psbLC){
                        currentBehavior = LaneChange;
                    }
                case LaneChange:
                    if(doneLC){
                        currentBehavior = Cruise;
                    }
                case EmergencyBrake:
                    return;
            }
        }
};


#endif
