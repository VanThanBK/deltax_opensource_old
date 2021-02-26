// Servo.h

#ifndef _SERVO_h
#define _SERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MIN_PULSE_WIDTH       544	//the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400	//the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH   1500	//default pulse width when servo is attached
#define MAX_TIMER_COUNT		20000	//the timer TOP value (for creating 50Hz)

#define MAX_SERVOS				2	//2 Servos can be attached

class Servo
{
 protected:


 public:
	Servo();
	void attach(int pin);				//attach the given pin
	void detach();						//detach the used pin
	void write(int value);             // if value is < 200 it is treated as an angle, otherwise as pulse width in microseconds
	void writeMicroseconds(int value); // write pulse width in microseconds
private:
	int servoPin = 0;					//pin number of the attached Servo
};

#endif

