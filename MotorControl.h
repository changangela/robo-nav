#ifndef MotorControl_h
#define MotorControl_h
#include "Arduino.h"
class MotorControl
{
	public:
		
		/*
			Constructor, takes the pins used and sets the pinmode
			@param pwmPin: the pin used to control the motor speed
							for motor one pwmPin = 5
							for motor two pwmPin = 6
			@param dirPin: the pin used to control the direction
							for motor one dirPin = 4
							for motor two dirPin = 7
		*/
		MotorControl(int pwmPin,int dirPin); 
		
		/*
			Constructor, just takes what motor to use and sets up the pin
			One problem with using this is that if they dont realize the
			pins are already in use they might try to use them for something
			else
			@param motorNum: what motor the object will represent. Must be
							1 or two
		*/
		MotorControl(int motorNum);
		
		/*
			moves the motor forward
			@param speed: how fast the motor should go
		*/
		void forward(int speed);
		
		/*
			moves the motor backwards
			@param speed: how fast the motor should go
		*/
		void reverse(int speed);
		
		/*
			Halts the motor
		*/
		void halt	();
	private:
		//internal method that initalizes the motor. Is called by the constructor
		void init(int pwmPin,int dirPin); 
		
		int _pwmPin;
		int _dirPin;
};
#endif
