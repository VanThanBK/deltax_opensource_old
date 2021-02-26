// MultiServo.h

#ifndef _MULTISERVO_h
#define _MULTISERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "enum.h"
#include "pin.h"
#include "Servo.h"

typedef struct Servo_t
{
	uint8_t lastPosition;
	uint8_t Desired;

	Servo servo;
	AXIS Name;
};

class MultiServoClass
{
 protected:


 public:
	void init();
	void CreateServo(AXIS axisname, uint8_t pin);
	void AddAngle(AXIS axisname, uint8_t angle);

	void Running();
protected:
	Servo_t *ServoArray;
	uint8_t NumberOfServoCreated;
	long LastTimer;
	void AddServo(Servo_t servo);
};

extern MultiServoClass MultiServo;

#endif

