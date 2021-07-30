#include "RN4678_Command.h"
#define DELAY_TIME 30
#define CTS_PIN 3

void setup() {
  int baudRate = 115200;
  
  Serial1.begin(baudRate, SERIAL_8N1);
  Serial1.attachRts(11);  // Any gpio will become RTS output
                          // Where pin will go low when ready to receive
                          
  pinMode(CTS_PIN, INPUT);   // Set pin 2 to be a CTS pin

//  Serial2.attachCts(); Supported only on 3.x and 4.x
}

int i = 0;

void loop() {
  delay(DELAY_TIME);
  
  i = (i + 1) % 20;
  
  if (digitalRead(CTS_PIN) == 0){
    if(i == 1) {
      Serial1.write("---\r");
      delay(DELAY_TIME);
      Serial1.write("$$$");
    }
    else {
      Serial1.write("D\r");   // Get device information  
    }
  }
}
