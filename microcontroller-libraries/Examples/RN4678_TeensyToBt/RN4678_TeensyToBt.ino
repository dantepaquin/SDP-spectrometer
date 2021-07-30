#define CTS_OUT 2
#define RTS_IN 3
#define BAUDRATE 115200

/*  The RN4678 will pull it's RTS output low when it is ready to receive data
 *  It will read from its CTS input to check if it can send data. Low indicates ready.
 *  Therefore, the TeensyLC will have a CTS_OUT, connected to the CTS input, that is pulled low 
 *  when the Teensy is ready to receive data.
 *  As well, the Teensy will have a RTS input, and will transmit data when the RN4678 pulls it low.
 */

 /* Load this onto the teensy
  * If you are using the arduino IDE, then you'd need teensyduino, which is on the teensy website
  * When loaded, open up the Serial Monitor (Ctrl+Shift+M)
  * You may see "%REBOOT%" in the return box
  * Make sure that the line ending option (bottom right) is set to "Carriage Return"
  * 
  * Send a test command!
  * In its default state, the module will automatically transfer any data it gets to the BT connection
  * So enter the "Command" moce by first typing in "$$$" (no quotes)
  * As a resonse, you should get "CMD>" as the response
  * From here, you can use any command in the command reference library to test arounbd with.
  * 
  * D    - Will get blutooth information
  * V    - Will get firmware version
  * F    - Will begin inquiry (If your phone is searching for devices, the module will print its info!)
  * ---  - Will exit command mode, and return to uart transfer
  */ 

void setup() {
  
  //  Set up Serial over USB
  Serial.begin(BAUDRATE);

  // Set up Serial port 1 (pins 0,1)
  Serial1.begin(BAUDRATE, SERIAL_8N1);
  Serial1.attachRts(RTS_IN);    // Any gpio can become RTS input
                                // Where RN4678 will pull its RTS output low to indicate ready to receive   
  pinMode(CTS_OUT, OUTPUT);     // Set pin 2 to be a CTS pin

//  Serial2.attachCts(); Supported only on 3.x and 4.x
}

int i = 0;

void loop() {  
  if (digitalRead(RTS_IN) == 0){
    if (Serial.available()){
      Serial1.write(Serial.read());
    }
    if (Serial1.available()){
      Serial.write(Serial1.read());
    }
    
  }
}
