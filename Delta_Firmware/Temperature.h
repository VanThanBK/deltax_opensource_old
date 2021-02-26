// Temperature.h

#ifndef _TEMPERATURE_h
#define _TEMPERATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <avr/interrupt.h>
#include "config.h"
#include "pin.h"
#include "Constants.h"
#include "thermistortables.h"

#define TurnOnTimer3 (TIMSK3 |= (1 << OCIE3A))
#define TurnOffTimer3 (TIMSK3 &= ~(1 << OCIE3A))
#define COMPARE_VALUE_TIMER3 OCR3A

#define INTERRUPT_CYCLE_TIMER3	10	//ms

#define DEFAULT_KP 22.2
#define DEFAULT_KI 0.2
#define DEFAULT_KD 65

#define TEMP_RESIDENCY_TIME 2  // (seconds)
#define TEMP_HYSTERESIS 5       // (degC) range of +/- temperatures considered "close" to the target one

#define HOTENDS  1
#define ARRAY_6(v1, v2, v3, v4, v5, v6, ...) { v1, v2, v3, v4, v5, v6 }
#define ARRAY_5(v1, v2, v3, v4, v5, ...)     { v1, v2, v3, v4, v5 }
#define ARRAY_4(v1, v2, v3, v4, ...)         { v1, v2, v3, v4 }
#define ARRAY_3(v1, v2, v3, ...)             { v1, v2, v3 }
#define ARRAY_2(v1, v2, ...)                 { v1, v2 }
#define ARRAY_1(v1, ...)                     { v1 }
#define _ARRAY_N(N, ...) ARRAY_ ##N(__VA_ARGS__)
#define ARRAY_N(N, ...) _ARRAY_N(N, __VA_ARGS__)
#define ARRAY_BY_HOTENDS(...) ARRAY_N(HOTENDS, __VA_ARGS__)
#define PGM_RD_W(x)   (short)pgm_read_word(&x)

static void* heater_ttbl_map[] = ARRAY_BY_HOTENDS((void*)HEATER_0_TEMPTABLE, (void*)HEATER_1_TEMPTABLE, (void*)HEATER_2_TEMPTABLE, (void*)HEATER_3_TEMPTABLE, (void*)HEATER_4_TEMPTABLE);
static uint8_t heater_ttbllen_map[] = ARRAY_BY_HOTENDS(HEATER_0_TEMPTABLE_LEN, HEATER_1_TEMPTABLE_LEN, HEATER_2_TEMPTABLE_LEN, HEATER_3_TEMPTABLE_LEN, HEATER_4_TEMPTABLE_LEN);

class TemperatureClass
{
 protected:
 

 public:
	void init();
	void SetHotendTemperature(float temperature);
	bool WaitForHotendTemperature();
	void Cooldown();

	void ISR_EXECUTE();
	bool IsWait;
private:
	float CurrentTemperature;
	float DesiredTemperature;

	void GetTemperature();
	
	float I;
	float LastError;
	uint32_t LastTime;
};

extern TemperatureClass Temperature;

#endif

