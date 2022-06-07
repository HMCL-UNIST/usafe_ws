#include "BehaviorStateMachine.h"
#include "DecisionMakerTest.h"
#include <iostream>
using namespace std;

int main(){
    BehaviorStateMachine behaviorfsm;
    BehaviorState current;
    DecisionMaker decisionMaker;
    current = decisionMaker.getCurrentBehavior();
    cout<<"currentbehavior : "<<current<<endl;
    behaviorfsm.updateBehaviorState(false, false, false, false, false, true);
    current = behaviorfsm.getCurrentBehavior();
    cout<<"currentbehavior : "<<current<<endl;
    return 0;
}