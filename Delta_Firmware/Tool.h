// Tool.h

#ifndef _TOOL_h
#define _TOOL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"
#include "Temperature.h"

class ToolClass
{
 protected:

 public:
	void init();
	Point ConvertToPoint(float xPos, float yPos, float zPos);
	bool CheckingDesiredPoint(Point point);
	bool CheckingDesiredAngle(Angle angle);
	Point GetPointInLine(Point currentP, Point desiredP, float t);
	Point GetPointInCircle(float ox, float oy, float desiredP, float angle);
	bool CheckFuplicatione(Point point1, Point point2);
	float CalDistance2Point(Point point1, Point point2);

	bool Wait();
	void SetTimeDelay(float timeDelay);

private:
	uint32_t TimeDelay;
	uint32_t LastTime;
};

extern ToolClass Tool;

#endif

