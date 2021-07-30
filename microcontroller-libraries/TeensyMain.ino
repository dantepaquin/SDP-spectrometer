/*
 * TeensyMain
 * 
 * Chris Massiello
 * Last Update: 3/5/2021
 * 
 * Description: This program controls the functions of a portable, PLA spectrometer by using a finite
 * state machine. This controls when the spectrometer performs a scan, when the spectrometer tries
 * to connect to a mobile app via bluetooth, and when it goes into power saving mode.
 * 
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

#include "FiniteStateMachine.h"

// creates list of States that are a part of FSM class
State IDLE_STATE = State(idle);
State POWER_SAVING = State(Power_saving);
State SCANNING = State(scanning);
State BL_SEARCHING = State(BL_search);
State BL_PAIRING = State(BL_pairing);
State PROCESSING = State(data_proc);
State TRANSMITTING = State(data_trans);
State OFF = State(turn_off);

FSM SPEC = FSM(IDLE_STATE); //creates finite state machine class

#define SW1 11 // Pin 11 for SW1, aka pushbutton to start bluetooth pairing
#define SW2 12 // Pin 12 for SW2, aka pushbutton to start plastic scan
#define A0 14 // Pin 14 for monitoring battery level

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  // Pins 0 and 1 for connection to bluetooth. 0 is RX1, 1 is TX1.
  // Pin 14 for receiving from detector.
  // Pins 18 and 19 for connection to OLED. Pin 18 is SDA0, Pin 19 is SCL0.
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(SPEC.isInState(IDLE_STATE)){ //if current state is idle
    if(digitalRead(SW2)){ //if SW2 is high, user wants to take a scan, set next state to be SCANNING
      SPEC.transitionTo(SCANNING); 
    }else if(digitalRead(SW1)){ //if SW1 is high, user wants to bluetooth pair, set next state to be 
      SPEC.transitionTo(BL_SEARCHING);
    }else if(SPEC.timeInCurrentState()>=90000){ //if it has been in the idle state for more than 15 minutes (900000 ms), go to power saving state
      // transition to VLPR
      SPEC.transitionTo(POWER_SAVING);
    }else{
      SPEC.selfTransitionTo(IDLE_STATE); // stays in idle state if no button is pressed and it hasn't been 15 minutes in idle state
    }
    
  }else if(SPEC.isInState(POWER_SAVING)){ //if in power saving state
    if(SPEC.timeInCurrentState()>=180000){ //if it has been in the power saving state for more than 30 minutes (1800000 ms), go to power saving state
      SPEC.transitionTo(OFF); // turn off
    }else if(digitalRead(SW2)||digitalRead(SW1)){  // if user presses a button, go back to idle
      SPEC.transitionTo(IDLE_STATE);
    }else{
      SPEC.selfTransitionTo(POWER_SAVING);  // if nothing happens, stay in POWER_SAVING
    }
  
  }else if(SPEC.isInState(SCANNING)){
    
  }else if(SPEC.isInState(BL_SEARCHING)){
    
  }else if(SPEC.isInState(BL_PAIRING)){
    
  }else if(SPEC.isInState(PROCESSING)){
    
  }else if(SPEC.isInState(TRANSMITTING)){
    
  }
  SPEC.update(); // causes state machine to update and go to next state
}


void idle() { //function for processes that happen in the IDLE state
  int sensorValue = analogRead(A0); //reads in analog value from battery, value will be between 0-8191 since teensy has default 13 bits resolution
  // might need to make sensorValue a global variable
  float voltage = sensorValue*(3.7/8191); //3.7 V is mapped to max value since 3-3.7V is useable range, assumeing voltage will be at 3.3 reference voltage, 
  // safe battery threshold is when sensor value >= 6644
  float Battery_life = ((voltage-3)/0.7)*100; //converts voltage value to a percentage of battery life
  display.print(Battery_life); 

  
}
void Power_saving(){ //function for processes that happen in the POWER_SAVING state
  
}

void scanning(){ //function for processes that happen in the SCANNING state
  
}

void BL_search(){ //function for processes that happen in the BL_SEARCHING state
  
}

void BL_pairing(){ //function for processes that happen in the BL_PAIRING state
  
}

void data_proc(){ //function for processes that happen in the PROCESSING state
  
}

void data_trans(){ //function for processes that happen in the TRANSMITTING state
  
}
void turn_off(){

}
