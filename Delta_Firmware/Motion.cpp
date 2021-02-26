// 
// 
// 

#include "Motion.h"

void MotionClass::init()
{


}

void MotionClass::G0(float xPos, float yPos, float zPos, float ewPos)
{
	Point pointBuffer = Tool.ConvertToPoint(xPos, yPos, zPos);

	if (Tool.CheckingDesiredPoint(pointBuffer) == false) return;
	
	if (LinearInterpolation() == false) return;

	if (Data.End_Effector == USE_PRINTER)
	{
	}
	else
	{
		if (ewPos != Data.WPosition)
		{
			MultiServo.AddAngle(AXIS_4, ewPos);
			Data.WPosition = ewPos;
			MultiServo.Running();
		}
	}

	Data.IsExecutedGcode = true;
	Stepper.Running();
	NumberSegment = 0;
}

void MotionClass::G1(float xPos, float yPos, float zPos, float ewPos)
{
	Data.IsExecutedGcode = true;

	Point pointBuffer = Tool.ConvertToPoint(xPos, yPos, zPos);

	if (Tool.CheckingDesiredPoint(pointBuffer) == false && Data.End_Effector != USE_PRINTER) return;

	if (LinearInterpolation() == false && Data.End_Effector != USE_PRINTER) return;

	if (Data.End_Effector == USE_PRINTER)
	{
		float offset = ewPos - Data.ExtrustionPosition;

		if (offset < 0.01 &&  offset > -0.01)
		{
			offset = 0;
		}

		Planner.AddExtrustionSegment(offset);

		Data.ExtrustionPosition = ewPos;
	}
	else
	{
		if (ewPos != Data.WPosition)
		{
			MultiServo.AddAngle(AXIS_4, ewPos);
			Data.WPosition = ewPos;
			MultiServo.Running();
		}
	}

	Stepper.Running();
	NumberSegment = 0;
}

void MotionClass::G2(float i, float j, float xPos, float yPos, float wPos)
{
	Data.IsExecutedGcode = true;

	Point pointBuffer = Tool.ConvertToPoint(xPos, yPos, Data.CurrentPoint.Z);

	if (Tool.CheckingDesiredPoint(pointBuffer) == false) return;

	if (CircleInterpolation(i, j, 0) == false) return;

	if (wPos != Data.WPosition)
	{
		MultiServo.AddAngle(AXIS_4, wPos);
		Data.WPosition = wPos;
		MultiServo.Running();
	}

	Stepper.Running();
	NumberSegment = 0;
}

void MotionClass::G3(float i, float j, float xPos, float yPos, float wPos)
{
	Data.IsExecutedGcode = true;

	Point pointBuffer = Tool.ConvertToPoint(xPos, yPos, Data.CurrentPoint.Z);

	if (Tool.CheckingDesiredPoint(pointBuffer) == false) return;

	if (CircleInterpolation(i, j, 1) == false) return;

	if (wPos != Data.WPosition)
	{
		MultiServo.AddAngle(AXIS_4, wPos);
		Data.WPosition = wPos;
		MultiServo.Running();
	}

	Stepper.Running();
	NumberSegment = 0;
}

void MotionClass::G4(float p)
{
	Tool.SetTimeDelay(p);
}

void MotionClass::G5(float i, float j, float p, float q, float x, float y, float wPos)
{
	Data.IsExecutedGcode = true;

	Point pointBuffer = Tool.ConvertToPoint(x, y, Data.CurrentPoint.Z);

	if (Tool.CheckingDesiredPoint(pointBuffer) == false) return;
	Point p1, p2;

	p1.X = i;
	p1.Y = j;
	p1.Z = Data.CurrentPoint.Z;

	p2.X = p;
	p2.Y = q;
	p2.Z = Data.CurrentPoint.Z;

	if (Bezier4PointInterpolation(p1, p2) == false) return;

	if (wPos != Data.WPosition)
	{
		MultiServo.AddAngle(AXIS_4, wPos);
		Data.WPosition = wPos;
		MultiServo.Running();
	}

	Stepper.Running();
}

void MotionClass::G6(float angle1, float angle2, float angle3, float distance)
{
	Data.IsExecutedGcode = true;

	Angle nextAngle;

	nextAngle.Theta1 = angle1;
	nextAngle.Theta2 = angle2;
	nextAngle.Theta3 = angle3;

	UploadSegment(Data.CurrentAngle, nextAngle, distance, 1);

	Data.CurrentAngle = nextAngle;

	Stepper.Running();
}

void MotionClass::G28()
{
	MultiServo.AddAngle(AXIS_4, 85);

	Planner.AddHomeSegment();
	Data.IsExecutedGcode = true;

	SetHomePosition();

	Stepper.EnableStepper();
	MultiServo.Running();
	Stepper.Homing();
}

bool MotionClass::LinearInterpolation()
{
	float distance2Point = Tool.CalDistance2Point(Data.CurrentPoint, Data.DesiredPoint);

	if (distance2Point == 0)
		return false;
	
	NumberSegment = floorf(distance2Point / Data.MMPerLinearSegment);

	if (NumberSegment < 1)
		NumberSegment = 1;

	float tbuffer;
	Angle lastAngle = Data.CurrentAngle;
	Angle currentAngle;

	float mm_per_seg = distance2Point / NumberSegment;

	for (uint16_t i = 1; i <= NumberSegment; i++)
	{
		tbuffer = (float)i / NumberSegment;
		Point pointBuffer = Tool.GetPointInLine(Data.CurrentPoint, Data.DesiredPoint, tbuffer);
		DeltaKinematics.InverseKinematicsCalculations(pointBuffer, currentAngle);

		UploadSegment(lastAngle, currentAngle, mm_per_seg, i - 1);
		lastAngle = currentAngle;
	}

	Data.CurrentPoint = Data.DesiredPoint;
	Data.CurrentAngle = currentAngle;

	return true;
}

bool MotionClass::CircleInterpolation(float i, float j, bool clockwise)
{
	if (i == 0 && j == 0)
		return;

	float o_x = Data.CurrentPoint.X + i,
		o_y = Data.CurrentPoint.Y + j,
		radius = sqrt(pow(i, 2) + pow(j, 2)),
		angle_Current, angle_Desired;

	angle_Current = acosf(-i / radius);
	if (j > 0)
		angle_Current = -angle_Current;

	angle_Desired = acosf((Data.DesiredPoint.X - o_x) / radius);
	if (Data.DesiredPoint.Y - o_y <= 0)
		angle_Desired = -angle_Desired;

	float angular_travel = angle_Desired - angle_Current;
	if (angular_travel < 0) angular_travel += 2.0 * PI;
	if (clockwise) angular_travel -= 2.0 * PI;

	if (angular_travel < 0.01)
		angular_travel = 0;

	if (angular_travel == 0 && Data.CurrentPoint.X == Data.DesiredPoint.X && Data.CurrentPoint.Y == Data.DesiredPoint.Y)
	{
		if (clockwise)
		{
			angular_travel = -2.0 * PI;
		}
		else
		{
			angular_travel = 2.0 * PI;
		}
	}

	float flat_mm = radius * abs(angular_travel);

	NumberSegment = floorf(flat_mm / Data.MMPerArcSegment);

	if (NumberSegment < 3)
	{
		return false;
	}

	float theta_per_segment = angular_travel / NumberSegment;
	float mm_per_seg = flat_mm / NumberSegment;

	Angle lastAngle = Data.CurrentAngle;
	Angle currentAngle;

	for (uint16_t i = 1; i <= NumberSegment; i++)
	{
		Point pointBuffer = Tool.GetPointInCircle(o_x, o_y, radius, angle_Current + (float)i * theta_per_segment);

		if (!DeltaKinematics.InverseKinematicsCalculations(pointBuffer, currentAngle)) return false;
		UploadSegment(lastAngle, currentAngle, mm_per_seg, i - 1);
		lastAngle = currentAngle;
	}

	Data.CurrentPoint = Data.DesiredPoint;
	Data.CurrentAngle = currentAngle;

	return true;
}

bool MotionClass::CircleInterpolation(float r, bool clockwise)
{

}

bool MotionClass::Bezier4PointInterpolation(Point p1, Point p2)
{
	if (Tool.CheckFuplicatione(p1, p2))
		return false;

	float tbuffer = 1.0 / NUMBER_PER_BEZIER_SEGMENT;
	float distanceBuffer;

	Angle lastAngle = Data.CurrentAngle;
	Angle currentAngle;

	Point lastPoint = Data.CurrentPoint;

	for (uint16_t i = 1; i <= NUMBER_PER_BEZIER_SEGMENT; i++)
	{
		Point a = Tool.GetPointInLine(Data.CurrentPoint, p1, i * tbuffer);
		Point b = Tool.GetPointInLine(p1, p2, i * tbuffer);
		Point c = Tool.GetPointInLine(p2, Data.DesiredPoint, i * tbuffer);

		Point d = Tool.GetPointInLine(a, b, i * tbuffer);
		Point e = Tool.GetPointInLine(b, c, i * tbuffer);

		Point f = Tool.GetPointInLine(d, e, i * tbuffer);

		if (!DeltaKinematics.InverseKinematicsCalculations(f, currentAngle)) return false;

		distanceBuffer = Tool.CalDistance2Point(f, lastPoint);
		UploadSegment(lastAngle, currentAngle, distanceBuffer, i - 1);

		lastPoint = f;
		lastAngle = currentAngle;
	}

	Data.CurrentPoint = Data.DesiredPoint;
	Data.CurrentAngle = currentAngle;

	return true;
}

void MotionClass::UploadSegment(Angle angle1, Angle angle2, float distance, uint8_t index)
{
	float offset[3];
	offset[0] = angle2.Theta1 - angle1.Theta1;
	offset[1] = angle2.Theta2 - angle1.Theta2;
	offset[2] = angle2.Theta3 - angle1.Theta3;

	if (NumberSegment == 1)
	{
		Planner.AddChangeSegment(offset, distance);
	}
	else if (index == 0)
	{
		Planner.AddBeginSegment(offset, distance);
	}
	else if (index == (NumberSegment - 1))
	{
		Planner.AddEndSegment(offset, distance);
	}
	else
	{
		Planner.AddFixedSegment(offset, distance);
	}
}

void MotionClass::SetHomePosition()
{
	Angle homeAngle;

	homeAngle.Theta1 = THETA1_HOME_POSITION;
	homeAngle.Theta2 = THETA2_HOME_POSITION;
	homeAngle.Theta3 = THETA3_HOME_POSITION;

	DeltaKinematics.ForwardKinematicsCalculations(homeAngle, Data.CurrentPoint);
	Data.DesiredPoint = Data.CurrentPoint;
	Data.CurrentAngle = homeAngle;

	Data.WPosition = 85;
}

MotionClass Motion;

