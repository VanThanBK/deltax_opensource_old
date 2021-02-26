// 
// 
// 

#include "EndEffector.h"

void EndEffectorClass::init()
{
	pinMode(VACCUM_PIN, OUTPUT);

	pinMode(SPINDLE_LASER_ENABLE_PIN, OUTPUT);
	pinMode(SPINDLE_LASER_PWM_PIN, OUTPUT);

	pinMode(CUSTOM_PWM_PIN, OUTPUT);
	pinMode(CUSTOM_DIR_PIN, OUTPUT);

	pinMode(EXTRUSDER_PULSE_PIN, OUTPUT);
	pinMode(EXTRUSDER_DIRECTION_PIN, OUTPUT);
	pinMode(EXTRUSDER_ENABLE_PIN, OUTPUT);

}

void EndEffectorClass::ResetEndEffectorOutput()
{
	analogWrite(VACCUM_PIN, 0);

	analogWrite(SPINDLE_LASER_ENABLE_PIN, 0);
	analogWrite(SPINDLE_LASER_PWM_PIN, 0);
	WRITE(CUSTOM_PWM_PIN, 0);
	analogWrite(CUSTOM_DIR_PIN, 0);

	WRITE(EXTRUSDER_ENABLE_PIN, 0);

	Data.ExtrustionPosition = 0;

	if (EndEffector == USE_LASER || EndEffector == USE_PRINTER)
	{
		analogWrite(SPINDLE_LASER_ENABLE_PIN, 255);
	}

	MultiServo.AddAngle(CLAMP, CLIP_OPEN_ANGLE_SERVO);
	MultiServo.Running();
}

void EndEffectorClass::ChangeEndEffector(uint8_t endeffector)
{
	if (endeffector > USE_CUSTOM)
	{
		endeffector = USE_CUSTOM;
	}

	EndEffector = (END_EFFECTOR)endeffector;

	ResetEndEffectorOutput();
}

void EndEffectorClass::TurnOffEndEffector()
{
	switch (EndEffector)
	{
	case USE_VACUUM:
		analogWrite(VACCUM_PIN, 0);
		break;
	case USE_LASER:
		//analogWrite(SPINDLE_LASER_ENABLE_PIN, 255);
		analogWrite(SPINDLE_LASER_PWM_PIN, 0);
		break;
	case USE_CLIP:
		MultiServo.AddAngle(CLAMP, CLIP_OPEN_ANGLE_SERVO);
		MultiServo.Running();
		break;
	case USE_PEN:
		break;
	case USE_CUSTOM:
		digitalWrite(CUSTOM_DIR_PIN, 0);
		analogWrite(CUSTOM_PWM_PIN, 0);
		break;
	case USE_PRINTER:
		digitalWrite(EXTRUSDER_ENABLE_PIN, 1);
		break;
	default:
		break;
	}
}

void EndEffectorClass::TurnOnEndEffector(byte eValue, bool iSw)
{
	switch (EndEffector)
	{
	case USE_VACUUM:
		analogWrite(VACCUM_PIN, 255);
		break;
	case USE_LASER:
		//analogWrite(SPINDLE_LASER_ENABLE_PIN, 255);
		//delayMicroseconds(50);
		analogWrite(SPINDLE_LASER_PWM_PIN, eValue);
		break;
	case USE_CLIP:
		if (eValue > 100)
		{
			MultiServo.AddAngle(CLAMP, CLIP_CLOSE_ANGLE_SERVO);
		}
		else
		{
			byte clipValue = eValue * (CLIP_OPEN_ANGLE_SERVO - CLIP_CLOSE_ANGLE_SERVO) / 100;
			MultiServo.AddAngle(CLAMP, CLIP_OPEN_ANGLE_SERVO - clipValue);
		}

		MultiServo.Running();
		break;
	case USE_PEN:
		break;
	case USE_CUSTOM:
		digitalWrite(CUSTOM_DIR_PIN, iSw);
		analogWrite(CUSTOM_PWM_PIN, eValue);
		break;
	case USE_PRINTER:
		digitalWrite(EXTRUSDER_ENABLE_PIN, 0);
		break;
	default:
		break;
	}
}

EndEffectorClass EndEffector;

