// Constants.h

#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#include "config.h"
#include "enum.h"
#include "Geometry.h"

typedef struct Point
{
	float X;
	float Y;
	float Z;

public:
	Point operator-(const Point& pointB)
	{
		Point pointBuffer;
		pointBuffer.X = this->X - pointB.X;
		pointBuffer.Y = this->Y - pointB.Y;
		pointBuffer.Z = this->Z - pointB.Z;
		return pointBuffer;
	}
};

typedef struct Angle
{
	float Theta1;
	float Theta2;
	float Theta3;

public:
	Angle operator-(const Angle& angleB)
	{
		Angle angleBuffer;
		angleBuffer.Theta1 = this->Theta1 - angleB.Theta1;
		angleBuffer.Theta2 = this->Theta2 - angleB.Theta2;
		angleBuffer.Theta3 = this->Theta3 - angleB.Theta3;
		return angleBuffer;
	}

	bool operator<(const Angle& angleB)
	{
		if (this->Theta1 >= angleB.Theta1) return false;
		if (this->Theta2 >= angleB.Theta2) return false;
		if (this->Theta3 >= angleB.Theta3) return false;
		return true;
	}

	bool operator>(const Angle& angleB)
	{
		if (this->Theta1 <= angleB.Theta1) return false;
		if (this->Theta2 <= angleB.Theta2) return false;
		if (this->Theta3 <= angleB.Theta3) return false;
		return true;
	}
};

class Constants
{
public:
	void	init();
	void ResetData();

	//

	float	RD_F;
	float	RD_E;
	float	RD_RF;
	float	RD_RE;

	float	RD_W;
	float	RD_U;
	float	RD_V;

	float	MOVING_AREA_X;
	float	MOVING_AREA_Y;
	float	MOVING_AREA_Z;

	float	MOVING_AREA_LARGEST_DIAMETER;
	//

	float	Velocity;			//mm/s
	float	Acceleration;		//mm/s^2

	float MovingHomeSpeed;

	float BeginEndVelocity;

	float EntryVelocity;
	float ExitVelocity;

	bool IsMoveWithTheAbsoluteCoordinates;

	bool IsExecutedGcode;

	END_EFFECTOR End_Effector;

	float MMPerLinearSegment;
	float MMPerArcSegment;

	Point CurrentPoint;
	Point DesiredPoint;

	Angle CurrentAngle;

	float ZOffset;

	float ExtrustionPosition;

	int WPosition;
private:

};

extern Constants Data;

#endif

