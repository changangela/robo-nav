#include "Arduino.h"
#include "MotorControl.h"
MotorControl::MotorControl(int pwmPin,int dirPin)
{
	init(pwmPin,dirPin); 
}

MotorControl::MotorControl(int motorNum)
{
	if (motorNum==1){
		init(5,4); //we gave the pins now just call the other constructor
	}
	else if (motorNum==2){
		init(6,7);
	}
}
void MotorControl::init(int pwmPin,int dirPin)
{
	_pwmPin = pwmPin;
	_dirPin = dirPin;
	pinMode(pwmPin,OUTPUT);
	pinMode(dirPin,OUTPUT);
}
void MotorControl::forward(int speed)
{
	digitalWrite(_dirPin,HIGH); //set direction
	analogWrite(_pwmPin,speed); //set speed
}

void MotorControl::reverse(int speed)
{
	digitalWrite(_dirPin,LOW); //set direction
	analogWrite(_pwmPin,speed); //set speed
}
void MotorControl::halt(){
	analogWrite(_pwmPin,0); //stops the motor by setting spped to zero
	//Brake would also go here but is not supported by this motor
}
