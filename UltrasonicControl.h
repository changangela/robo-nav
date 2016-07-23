#ifndef UltrasoncControl_h
#define UltrasoncControl_h


#include <arduino.h>
class UltrasonicControl{
	public:
		/*
			Constructor, creates sensor object
			@param trigPin: the trigger pin on the sensor
			@param echoPin: the echo pin on the sensor
		*/
		UltrasonicControl(int trigPin,int echoPin);
		
		/*
			determines the distance
			@return: distance in cm, -1 on error
		*/
		int getDistance();
		
		/*
			Determines if an objct is detected within the next square
			@return: true of an object is detected 
		*/
		boolean detect();
	private:
		int _trigPin;
		int _echoPin;
};
#endif
