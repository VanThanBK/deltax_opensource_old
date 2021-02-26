// Control.h

#ifndef _CONTROL_h
#define _CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"
#include "Storage.h"
#include "EndEffector.h"
#include "Planner.h"
#include "Temperature.h"
#include "Stepper.h"
#include "GCodeReceiver.h"

class ControlClass
{
 protected:


 public:
	void init();
	void G90();//Absolute Positioning
	void G91();//Relative Positioning
	void G93();

	void M03(float s);//Set spindle cw or lazer on
	void M04(float s);//Set spindle ccw or lazer on
	void M05();//Set spindle off or lazer off

	void M84();//Disanable Step

	void M104(float s); //Set Hotend Temperature
	void M109();//Wait for Hotend Temperature

	void M203(float s);//Set Max Feedrate
	void M204(float a);//Set acceleration
	void M206(float zPos);//Set Offset

	void M360(float e);//set end effector
	void M361(float p);//Set mm per linear segment
	void M362(float p);//Set mm per arc segment

	void M500();//Storage Settings
	void M501();//Restore Settings
	void M502();//Load Settings
};

extern ControlClass Control;

#endif

