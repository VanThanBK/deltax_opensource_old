// Stepper.h

#ifndef _STEPPER_h
#define _STEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <vector>

#include <avr/interrupt.h>
#include "config.h"
#include "Constants.h"
#include "pin.h"
#include "enum.h"
#include "fastio.h"
#include "EndStops.h"
#include "Planner.h"

using namespace std;

#define COMPARE_VALUE_TIMER5 OCR5A
#define COMPARE_VALUE_TIMER2 OCR2A

#define TurnOnTimer2 (TIMSK2 |= (1 << OCIE2A))
#define TurnOffTimer2 (TIMSK2 &= ~(1 << OCIE2A))

#define TurnOnTimer5 (TIMSK5 |= (1 << OCIE5A))
#define TurnOffTimer5 (TIMSK5 &= ~(1 << OCIE5A))

#ifdef SMOOTHSTEP

#endif // SMOOTHSTEP

#if SMOOTHSTEP == 0
#define SmoothStep(x) (x)
#endif

#if SMOOTHSTEP == 1
#define SmoothStep(x) (x*x*(3 - 2*x))
#endif

#if SMOOTHSTEP == 2
#define SmoothStep(x) (x*x*x*(10 + x*(6*x - 15)))
#endif

#if SMOOTHSTEP == 3
#define SmoothStep(x) (x*x*x*x*(35 + x*(x*(70 - 20*x) - 84)))
#endif

typedef struct Motor
{
	float InterruptNumberNextStep;
	AXIS Name;
	float NumberInterrupt2Step;
};

class StepperClass
{
 protected:

 public:
	void init(vector<Segment>* SegmentQueue);
	void CreateMotor();

	bool GetStateMotor();

	void Running();
	void Homing();

	void Isr_Execute_Velocity();
	void Isr_Execute_Movinghome();
	void Isr_Turn_Pulse_Pin();

	void DisanableStepper();
	void EnableStepper();

	vector<Segment>* SegmentQueue;

 private:
	 Motor ThetaStepMotor[3];
	 Motor ExtrustionStepMotor;

	 Segment CurrentMoveSegment;

	 bool	IsStoppedMoving;

	 float Timer;
	 uint32_t NumberTnterrupt;
	 uint32_t TotalTnterruptNumber;
	 uint32_t NumberTnterruptAtMinCycle;

	 uint8_t IsRunningHome;

	 float CurrentCycle;
	 float MaxCycle;

	 void setPinMode(AXIS axisname);
	 void UpdateMoveSegment();
	 void SetIntCycle(float intCycle);
	 void ClearMotorArray();

	 void setMotorDirection(AXIS axisname, bool variation);
	 void writePulsePin(AXIS axisname, bool ison);
};

extern StepperClass Stepper;

#endif

