/* LED.cpp

*/ 
#include <Arduino.h>
#include "LED.h"

LED::LED(int pin){
   pinMode(pin, OUTPUT);
   pinNumber = pin;
}

void LED::LED_ON(bool value){
	if(value==1){
		digitalWrite(pinNumber, HIGH);
	}else{
		digitalWrite(pinNumber, LOW);
	}
	return;
}

void LED::LED_OFF(bool value){
	if(value==1){
		digitalWrite(pinNumber, LOW);
	}else{
		digitalWrite(pinNumber, HIGH);
	}
	return;
}