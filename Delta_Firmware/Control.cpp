// 
// 
// 

#include "Control.h"

void ControlClass::init()
{


}

void ControlClass::G90()
{
	Data.IsMoveWithTheAbsoluteCoordinates = true;

	Data.IsExecutedGcode = true;
}

void ControlClass::G91()
{
	Data.IsMoveWithTheAbsoluteCoordinates = false;

	Data.IsExecutedGcode = true;
}

void ControlClass::G93()
{
	Serial.print(Data.CurrentPoint.X);
	Serial.print(",");
	Serial.print(Data.CurrentPoint.Y);
	Serial.print(",");
	Serial.println(Data.CurrentPoint.Z);
}

void ControlClass::M03(float s)
{
	EndEffector.TurnOnEndEffector((byte)s, 0);
	
	Data.IsExecutedGcode = true;
}

void ControlClass::M04(float s)
{
	EndEffector.TurnOnEndEffector((byte)s, 1);
	
	Data.IsExecutedGcode = true;
}

void ControlClass::M05()
{
	EndEffector.TurnOffEndEffector();

	Data.IsExecutedGcode = true;
}

void ControlClass::M84()
{
	Stepper.DisanableStepper();

	Data.IsExecutedGcode = true;
}

void ControlClass::M104(float s)
{
	Temperature.SetHotendTemperature(s);

	Data.IsExecutedGcode = true;
}

void ControlClass::M109()
{
	Temperature.IsWait = true;
}

void ControlClass::M203(float s)
{
	Planner.SetMaxVelocity(s);
	Data.IsExecutedGcode = true;
}

void ControlClass::M204(float a)
{
	Planner.SetAcceleration(a);
	Data.IsExecutedGcode = true;
}

void ControlClass::M206(float zPos)
{
	//CNCAxisDelta.SetZOffset(zPos);
	Data.ZOffset = zPos;
	Data.IsExecutedGcode = true;
}

void ControlClass::M360(float e)
{
	Data.End_Effector = (END_EFFECTOR)e;
	EndEffector.ResetEndEffectorOutput();

	Data.IsExecutedGcode = true;
}

void ControlClass::M361(float p)
{
	Data.MMPerLinearSegment = p;
	Data.IsExecutedGcode = true;
}

void ControlClass::M362(float p)
{

	Data.MMPerArcSegment = p;
	Data.IsExecutedGcode = true;
}

void ControlClass::M500()
{
	Storage.StorageSettings();

	Data.IsExecutedGcode = true;
}

void ControlClass::M501()
{
	Storage.RestoreSettings();

	Data.IsExecutedGcode = true;
}

void ControlClass::M502()
{
	Storage.LoadSettings();

	Data.IsExecutedGcode = true;
}

ControlClass Control;

