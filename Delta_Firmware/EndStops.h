// EndStops.h

#ifndef _ENDSTOPS_h
#define _ENDSTOPS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "pin.h"
#include "enum.h"
#include "fastio.h"

class EndStopsClass
{
 protected:


 public:
	void init();
	void UpdateStates();
	bool HomingCheck();
	void ReportStates();
	bool States(AXIS axis);
	void ClearEndstopState();

private:
	bool Theta1State;
	bool Theta2State;
	bool Theta3State;

#ifdef ENDSTOP_FOR_CHECK_Z_AREA
	bool ZAreaState;
#endif
	//uint8_t HomePhase;
};

extern EndStopsClass EndStops;

#endif

