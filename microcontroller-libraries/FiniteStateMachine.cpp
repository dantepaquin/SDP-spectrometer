#include "FiniteStateMachine.h" 

//FINITE STATE
State::State( void (*updateFunction)() ){
  userEnter = 0;
  userUpdate = updateFunction;
  userExit = 0;
}

State::State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() ){
  userEnter = enterFunction;
  userUpdate = updateFunction;
  userExit = exitFunction;
}

//what to do when entering this state
void State::enter(){
  if (userEnter){
    userEnter();
  }
}

//what to do when this state updates
void State::update(){
  if (userUpdate){
    userUpdate();
  }
}

//what to do when exiting this state
void State::exit(){
  if (userExit){
    userExit();
  }
}
//END FINITE STATE


//FINITE STATE MACHINE
FiniteStateMachine::FiniteStateMachine(State& current){
  needToTriggerEnter = true;
  currentState = nextState = &current;
  stateChangeTime = 0;
}

FiniteStateMachine& FiniteStateMachine::update() {
  //simulate a transition to the first state
  //this only happens the first time update is called
  if (needToTriggerEnter) { 
    currentState->enter();
    needToTriggerEnter = false;
  } else {
    if (currentState != nextState){
      immediateTransitionTo(*nextState);
    }
    currentState->update();
  }
  return *this;
}

FiniteStateMachine& FiniteStateMachine::transitionTo(State& state){ //assigns the next state and updates time in state
  nextState = &state;
  stateChangeTime = millis();
  return *this;
}

FiniteStateMachine& FiniteStateMachine::immediateTransitionTo(State& state){ //assigns the next state if the state machine is just starting
  currentState->exit();
  currentState = nextState = &state;
  currentState->enter();
  stateChangeTime = millis();
  return *this;
}

FiniteStateMachine& FiniteStateMachine::selfTransitionTo(State& state){
   nextState = &state;
   return *this;
}

//return the current state, to mainly be used for debugging
State& FiniteStateMachine::getCurrentState() {
  return *currentState;
}

//check if state is equal to the currentState
boolean FiniteStateMachine::isInState( State &state ) const {
  if (&state == currentState) {
    return true;
  } else {
    return false;
  }
}

// creates variable that monitors how long time was spent in a state, millis() is the amount of milliseconds since the program started
unsigned long FiniteStateMachine::timeInCurrentState() { 
  millis() - stateChangeTime; 
}
//END FINITE STATE MACHINE
