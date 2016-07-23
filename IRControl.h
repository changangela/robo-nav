#ifndef IRControl_h
#define IRControl_h

#include <Arduino.h>
class IRControl{
	public:
		/*
		 Constructor to create "IR sensor" object
		 @parm pin: the analogPin that the sensor uses
		*/
		IRControl(int pin);
		
		/*
		Function that determines if the sensor is reading black
		@returns: true if black
		*/
		boolean isBlack();
	private:
		int _pin;
};

#endif
