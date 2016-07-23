#include <arduino.h>
#include <UltrasonicControl.h>
UltrasonicControl::UltrasonicControl(int trigPin,int echoPin){
	_trigPin = trigPin;
	_echoPin = echoPin;
  	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}
int UltrasonicControl::getDistance(){
	long duration, distance;
  	digitalWrite(_trigPin, LOW); //esure output to the sensor is clean
  	delayMicroseconds(2);
  	
	digitalWrite(_trigPin, HIGH); //trigger for 10 ms
	delayMicroseconds(10);
	
	digitalWrite(_trigPin, LOW); //end pulse
	
	
	duration = pulseIn(_echoPin, HIGH); //wait for return pulse for 1/4 second
	
	distance = (duration/2) / 29.1; //calculate distance
								//round trip so divide by two							
	if (distance>=200||distance<=0) return -1; //error state
	return (int)distance; //cast it to an int. I dont think a long is nessisary
}
boolean UltrasonicControl::detect(){
	int d = getDistance();
	return d!=-1 && d<=15; //should be about the distance of one square
}
