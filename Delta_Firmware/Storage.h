// Storage.h

#ifndef _STORAGE_h
#define _STORAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "EEPROM.h"
#include "Constants.h"

#define VELICITY_ADDRESS 0
#define ACCELERATION_ADDRESS 4

#define RD_F_ADDRESS 8
#define RD_E_ADDRESS 12

#define RD_RF_ADDRESS 16
#define RD_RE_ADDRESS 20

#define RD_W_ADDRESS 24
#define RD_U_ADDRESS 28
#define RD_V_ADDRESS 32

#define MOVE_AREA_X_ADDRESS 36
#define MOVE_AREA_Y_ADDRESS 40
#define MOVE_AREA_Z_ADDRESS 44

#define MOVE_AREA_LARGEST_DIAMETER_ADDRESS 48

#define MOVING_HOME_SPEED_ADDRESS 52

#define BEGIN_END_VELOCITY_ADDRESS 56

#define ENTRY_VELOCITY_ADDRESS 64
#define EXIT_VELOCITY_ADDRESS 68

#define MM_PER_LINEAR_SEGMENT_ADDRESS 72
#define MM_PER_ARC_SEGMENT_ADDRESS 76

class StorageClass
{
 protected:

 public:
	void init();
	void StorageSettings();
	void LoadSettings();
	void RestoreSettings();
 private:
};

extern StorageClass Storage;

#endif

