/* LED.h

Header file that creates an LED class. 

More functions may be needed later on but I only included
these two because I thought that the LED would turn on in 
during the scan and off otherwise.
*/

#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED
{
public:
	LED(int pin); //Constructor, assigns pin to LED
	void LED_ON(bool value); //turns on LED
	void LED_OFF(bool value); //turns off LED
	
private:
	uint8_t pinNumber;
	
};

#endif