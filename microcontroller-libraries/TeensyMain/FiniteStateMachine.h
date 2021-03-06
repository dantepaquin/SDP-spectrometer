/*
 * FiniteStateMachine.h
 * 
 * Chris Massiello
 * 5/4/2021
 * 
 * Description: Makes a finite state machine class that makes it easy to make and switch between states
 * 
 * References: https://github.com/kurimawxx00/FiniteStateMachine/blob/master/FiniteStateMachine.h
*/

#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <Arduino.h>

#define NO_ENTER (0)
#define NO_UPDATE (0)
#define NO_EXIT (0)

#define FSM FiniteStateMachine

//define the functionality of the states
class State {
  public:
    State( void (*updateFunction)() );
    State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );
    //State( byte newId, void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );
    
    //void getId();
    void enter();
    void update();
    void exit();
  private:
    //byte id;
    void (*userEnter)();
    void (*userUpdate)();
    void (*userExit)();
};

//define the finite state machine functionality
class FiniteStateMachine {
  public:
    FiniteStateMachine(State& current);
    
    FiniteStateMachine& update();
    FiniteStateMachine& transitionTo( State& state );
    FiniteStateMachine& immediateTransitionTo( State& state );
    FiniteStateMachine& selfTransitionTo( State& state );
    
    State& getCurrentState();
    boolean isInState( State &state ) const;
    
    unsigned long timeInCurrentState();
    
  private:
    bool  needToTriggerEnter;
    State*  currentState;
    State*  nextState;
    unsigned long stateChangeTime;
};

#endif
