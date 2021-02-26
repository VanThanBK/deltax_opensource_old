#pragma once

#include "config.h"

typedef enum AXIS
{
	THETA_1 = 0,
	THETA_2,
	THETA_3,
#ifdef DELTA_AXIS_4
	AXIS_4,
#endif // DELTA_AXIS_4
#ifdef DELTA_AXIS_5
	AXIS_5,
#endif // DELTA_AXIS_5
#ifdef CLIP
	CLAMP
#endif // CLIP
};

#ifdef REVERSE_DIRECTION
typedef enum VARIATION
{
	DECREASE = 0,
	INCREASE
};
#else
typedef enum VARIATION
{
	INCREASE = 0,
	DECREASE
};
#endif // reverse direction

typedef enum MOTIVE
{
	USE_STEPPER = 0,
	USE_SERVO
};

typedef enum END_EFFECTOR
{
	USE_VACUUM = 0,
	USE_CLIP,
	USE_PEN,
	USE_LASER,
	USE_PRINTER,
	USE_CUSTOM
};

typedef enum TYPE_SEGMENT
{
	BEGIN_SEG = 0,
	END_SEG,
	CHANGE_VELOCITY_SEG,
	FIXED_VELICITY_SEG,
	MOVING_HOME
};

typedef enum COLOR
{
	RED = 0,
	GREEN,
	BLUE,
};

//#define A(CODE) " " CODE "\n\t"
