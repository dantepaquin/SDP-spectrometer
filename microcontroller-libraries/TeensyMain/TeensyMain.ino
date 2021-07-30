/*
 * TeensyMain
 * 
 * Chris Massiello
 * Last Update: 5/6/2021
 * 
 * Description: This program controls the state of a portable, PLA spectrometer by using a finite
 * state machine. This controls when the spectrometer performs a scan, when the spectrometer tries
 * to connect to a mobile app via bluetooth, and when it goes into power saving mode.
 * 
 */

/*libraries*/
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//
#include "FiniteStateMachine.h"
/*
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))//defining macro to change cpu clock speed
#define CPU_8MHz        0x01 //values over 8 MHz can be used but would cause the teensy LC to overclock, hence * MHz will be max value that we want to use
#define CPU_4MHz        0x02 //putting these here in case we want to change the cpu clock speed
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04

CPU_PRESCALE(CPU_8MHz);*/


/*creates list of State object that are a part of FSM class
  State STATE = State(method)
  being in the state, STATE, will cause the method passed in State(method) to execute*/
State IDLE_STATE = State(idle);
State POWER_SAVING = State(Power_saving);
State SCANNING = State(scanning);
State BL_SEARCHING = State(BL_search);
State TRANSMITTING = State(data_trans);


/*FSM SPEC = FSM(START), creates finite state machine class that starts in the state named START
  Creates FiniteStateMachine class that will start in the IDLE state*/
FSM SPEC = FSM(IDLE_STATE); 

//defining constants for pins

//UART pins
#define RX 0
#define TX 1
#define CTS 2
#define RTS 3

//pushbuttons
#define SW1 11 // Pin 11 for SW1, aka pushbutton to start bluetooth pairing
#define SW2 12 // Pin 12 for SW2, aka pushbutton to start plastic scan

//analog pins
#define A0 15 // Pin 15 for monitoring battery level
#define DET 14// Pin 14 for reading from detector

//digital pins controlling the LEDs
#define LED1 7 // Pin 7 for LED1
#define LED2 8 // Pin 8 for LED2
#define LED3 9 // Pin 9 for LED3
#define LED4 10 // Pin 10 for LED4
#define LED_pulse 6 // Pin 6 for controlling the BJTs that allow each LED to get current 

// digital pin for resetting the OLED display
#define OLED_RESET 4 // defines the reset pin for the OLED display
Adafruit_SSD1306 display( OLED_RESET); //creates instance of Adafruit_SSD1306 with reset pin OLED_RESET

// global constants
float timer_start = 0;

// timer_count is the counter value that is incremented whenever the timer interrupt overflows 
// needs to be volatile because it is passed into an interrupt
volatile uint8_t timer_count = 0;

void setup() {

  Serial.begin(115200); // setting baudrate for 115200 bits/s, 115200 is baudrate for RN4678

  //display defaults to using SDA0 and SCL0 which is pin 18 and 19
  // 0x3C is the screen address, currently 128x32 pixels. 0x3D is 128x64 pixels but am having trouble running that
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//sets display as 128x32 format

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.clearDisplay();

  // Enable entry into VLPR, LLS or VLLS modes.
  SMC_PMPROT |= SMC_PMPROT_AVLP | SMC_PMPROT_ALLS | SMC_PMPROT_AVLLS;
  
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED_pulse, OUTPUT);

  pinMode(20, OUTPUT);
  
  pinMode(DET, INPUT);

  cli(); //disables interrupts 
  // setup for interrupts and ISRs
  
  // initializing external pushbutton interrupts

  // attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
  // attaches an external interrupt to pin in digitalPinToInterrupt, 
  // ISR: the ISR to be called when the interrupt triggers
  // mode: defines when the interrupt should be triggered 
  //
  // possible values for mode: LOW(digital pin is low, CHANGE(when digital pin changes value), 
  // RISING(when digital pin goes from 0 to 1), FALLING(when digital pin goes from 1 to 0)
  attachInterrupt(digitalPinToInterrupt(SW2), SW2_check_state, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW1), SW1_check_state, FALLING);
  
  // initializing timer interrupt
  
  // Clear TPM0_SC(Status and Control) register 
  FTM0_SC = 0;
  
  // Reset the TPM0_CNT counter 
  // TPM0_CNT contains the current counter value of the timer
  FTM0_CNT = timer_start;
  
  // Set overflow value (modulo) (p.574 of FRM)
  // sets the value that the timer will overflow at, max value is 0xFFFF(65535) since 16 bit timer
  
  FTM0_MOD = 0xF423; //62499
  
  
  // Set TPM0_SC register (p. 572 of FRM)
  // Bits | Va1ue | Description
  //  8   |    0  | DMA: Disable DMA
  //  7   |    1  | TOF: Clear Timer Overflow Flag
  //  6   |    1  | TOIE: Enable Timer Overflow Interrupt
  //  5   |    0  | CPWMS: TPM in up counting mode
  // 4-3  |   01  | CMOD: Counter incrememnts every TPM clock
  // 2-0  |  111  | PS: Prescale = 128, ranges from 1-128
  FTM0_SC = 0b011001111;

  // sets the priority of the interrupt, lower value means higher priority
  // ranges from 0-192 with spacing between values of 64
  NVIC_SET_PRIORITY(IRQ_FTM0, 64);

  // enable the timer interrupt
  NVIC_ENABLE_IRQ(IRQ_FTM0);

  sei(); //enables all interrupts

}

// isr for SW2
void SW2_check_state(){
  //checks the state that the state machine was in when interrupt triggered
  if(SPEC.isInState(POWER_SAVING)){
    display.clearDisplay();
    SPEC.transitionTo(IDLE_STATE);
    display.fadein();
    
    // sets the Teensy to normal run mode
    SMC_PMCTRL |= (0 << 6);
    
    reset_timer();
  }else if(SPEC.isInState(IDLE_STATE)){
    SPEC.transitionTo(SCANNING);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("SCANNING");
    display.display();
  }
  
}

// isr for SW1
void SW1_check_state(){
  //checks the state that the state machine was in when interrupt triggered
  if(SPEC.isInState(POWER_SAVING)){
    //if in power_saving, set next state to idle state
    display.clearDisplay();
    SPEC.transitionTo(IDLE_STATE);
    display.fadein();

    // sets the Teensy to normal run mode
    SMC_PMCTRL |= (0 << 6);
    
    //reset interrupt timer value
    reset_timer();
  }else if(SPEC.isInState(IDLE_STATE)){
    SPEC.transitionTo(BL_SEARCHING);
    reset_timer();
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("BL SEARCHING");
    display.display();
  }//this interrupt should only trigger if it is in idle or power saving state, but just in case

}

void ftm0_isr(void) {

  // First, write a 1 to the TOF bit to clear the timer overflow flag
  FTM0_SC |= (1 << 7);

  // increment the counter
  timer_count++;

  
  if(SPEC.isInState(IDLE_STATE)){
    if(timer_count>=180){//timer has reached 15 minutes
      SPEC.transitionTo(POWER_SAVING);
      reset_timer();
      display.fadeout();

      // sets the Teensy to VLPR mode
      SMC_PMCTRL |= (1 << 6);

    }
  }else if(SPEC.isInState(BL_SEARCHING)){
    if(timer_count>=100){ //not sure if this is needed since it might be done by bluetooth state machine
      SPEC.transitionTo(IDLE_STATE);
      reset_timer();
      display.clearDisplay();
      display.setCursor(0,24);
      display.print("Pairing Failed");
      display.display();
      delay(100);
    }
  }
  
}

//loop that runs repeatedly
void loop() {

  SPEC.update(); // updates the current state of the state machine by setting the current state equal to the next state
}

// function for processes that happen in the IDLE state
void idle() { 

  //display.clearDisplay();
  display.setCursor(0,0);

  int sensorValue = analogRead(A0); //reads in analog value from battery, value will be between 0-8191 since teensy has default 13 bits resolution

  Serial.print("analog 0 is: ");
  Serial.println(sensorValue);
  delay(250);
  //delay(10); // let the ADC recover, arbitrary value
  float voltage = sensorValue*(4.2/8191); //4.2 V is mapped to max value since 3-4.2V is useable range, assumeing voltage will be at 3.3 reference voltage, 
  // safe battery threshold is when sensor value >= 6644
  
  /*if(voltage<3.6){
    display.print("Warning:Low Battery");
  }*/
  
  float Battery_life = ((voltage-3)/1.2); //converts voltage value to a percentage of battery life
  display.setCursor(0,8);
  //display.print(Battery_life); 
  //sensorValue = 97;
  display.print(sensorValue); 
  display.print("%"); 
  display.setCursor(0,16);
  display.print("Not Connected");
  display.display(); //display 
  delay(1); //let the display recover

}

//function for processes that happen in the POWER_SAVING state
void Power_saving(){ 
  //waits in the power_saving state until a pushbutton is pressed, otherwise does nothing
  /*display.clearDisplay();
  display.setCursor(0,0);
  display.print("Power saving");
  display.display();
  delay(1);*/

  //display.fadeout();

  
}
//function for processes that happen in the SCANNING state
void scanning(){ 
  
  //disables all interrupts by clearing the global interrupte mask
  // we disable all interrupts when we enter this state so that the scanning process won't be interrupted
  cli(); 

  //turn on LEDs one-by-one, reads analog value from photodiode for each LED and stores values

  //perform error detecting algorithm
  //   if error occurred
  //      print scanning error to OLED
  //      set next state to idle state
  //   else
  //      perform plastic classification algorithm
  //      print plastic class to OLED
  //      if connected to mobile app
  //         set next state to transmitting state 
  //      else
  //         set next state to idle state

  digitalWrite(20, HIGH);
  delay(6);
  digitalWrite(20,LOW);
  SPEC.transitionTo(IDLE_STATE);
  display.clearDisplay();
  display.setCursor(0,24);
  display.print("Error: No det value");
  display.display();
  delay(1);
  reset_timer();
  sei(); //re-enables interrupts
}

//function for processes that happen in the BL_SEARCHING state
void BL_search(){ 
  
}

//function for processes that happen in the TRANSMITTING state
void data_trans(){ 
  
}

//helper function that just resets the value of timer_count
void reset_timer(){
  timer_count=0;
}
