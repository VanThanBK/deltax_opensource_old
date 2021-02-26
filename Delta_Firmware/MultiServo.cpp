// 
// 
// 

#include "MultiServo.h"

void MultiServoClass::init()
{
	CreateServo(AXIS_4, AXIS_4_SERVO_PIN);
	CreateServo(CLAMP, CLIP_SERVO_PIN);
}

void MultiServoClass::CreateServo(AXIS axisname, uint8_t pin)
{
	Servo_t buffer;

	buffer.lastPosition = 0;
	buffer.Desired = 0;
	buffer.servo.attach(pin);
	buffer.servo.write(90);
	buffer.Name = axisname;

	AddServo(buffer);
}

void MultiServoClass::AddAngle(AXIS axisname, uint8_t angle)
{
	for (uint8_t i = 0; i < NumberOfServoCreated; i++)
	{
		if (ServoArray[i].Name != axisname)
		{
			continue;
		}
		else
		{
			ServoArray[i].Desired = angle;
			break;
		}	
	}
}

void MultiServoClass::Running()
{
	for (uint8_t i = 0; i < NumberOfServoCreated; i++)
	{
		if (ServoArray[i].lastPosition != ServoArray[i].Desired)
		{
			ServoArray[i].lastPosition = ServoArray[i].Desired;
			ServoArray[i].servo.write(ServoArray[i].lastPosition);
		}
	}
}

void MultiServoClass::AddServo(Servo_t servo)
{
	NumberOfServoCreated++;
	Servo_t *buffer = new Servo_t[NumberOfServoCreated];
	for (uint8_t i = 0; i < NumberOfServoCreated - 1; i++)
	{
		buffer[i] = ServoArray[i];
	}

	buffer[NumberOfServoCreated - 1] = servo;

	if (ServoArray != NULL)
	{
		delete[] ServoArray;
	}

	ServoArray = buffer;
}

MultiServoClass MultiServo;

