// EndEffector.h

#ifndef _ENDEFFECTOR_h
#define _ENDEFFECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "Constants.h"
#include "pin.h"
#include "enum.h"
#include "fastio.h"
#include "MultiServo.h"

class EndEffectorClass
{
 protected:


 public:
	END_EFFECTOR EndEffector;

	void init();
	void ResetEndEffectorOutput();
	void ChangeEndEffector(uint8_t endeffector);
	void TurnOffEndEffector();
	void TurnOnEndEffector(byte eValue, bool iSw);

private:

};

extern EndEffectorClass EndEffector;

#endif

