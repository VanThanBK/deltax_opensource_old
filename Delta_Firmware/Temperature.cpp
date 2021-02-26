// 
// 
// 

#include "Temperature.h"

void TemperatureClass::init()
{
	pinMode(THERMISTOR_PIN, INPUT);
	pinMode(HEATER_PIN, OUTPUT);
	analogWrite(HEATER_PIN, 0);

	noInterrupts();
	// Reset register relate to Timer 3
	// Reset register relate
	TCCR3A = TCCR3B = TCNT3 = 0;
	// Set CTC mode to Timer 3
	TCCR3B |= (1 << WGM32);
	// Set prescaler 8 to Timer 3
	TCCR3B |= (1 << CS31);
	//Normal port operation, OCxA disconnected
	TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0) | (1 << COM3B1) | (1 << COM3B0));

	COMPARE_VALUE_TIMER3 = roundf(INTERRUPT_CYCLE_TIMER3 * F_CPU / (1000.0 * 8)) - 1;
	interrupts();
	TurnOffTimer3;
}

void TemperatureClass::GetTemperature()
{
	uint8_t e = 0;
	int raw = 0;
	for (int j = 1; j <= OVERSAMPLENR; j++) {
		raw += analogRead(THERMISTOR_PIN);
	}
	if (heater_ttbl_map[e] != NULL) {
		float celsius = 0;
		uint8_t i;
		short(*tt)[][2] = (short(*)[][2])(heater_ttbl_map[e]);
		for (i = 1; i < heater_ttbl_map[e]; i++) {
			if (PGM_RD_W((*tt)[i][0]) > raw) {
				celsius = PGM_RD_W((*tt)[i - 1][1]) +
					(raw - PGM_RD_W((*tt)[i - 1][0])) *
					(float)(PGM_RD_W((*tt)[i][1]) - PGM_RD_W((*tt)[i - 1][1])) /
					(float)(PGM_RD_W((*tt)[i][0]) - PGM_RD_W((*tt)[i - 1][0]));
				break;
			}
		}

		// Overflow: Set to last value in the table
		if (i == heater_ttbllen_map[e]) { celsius = PGM_RD_W((*tt)[i - 1][1]); }

		CurrentTemperature = celsius;
	}
}

void TemperatureClass::SetHotendTemperature(float temperature)
{
	if (Data.End_Effector != USE_PRINTER)
		return;

	DesiredTemperature = temperature;
	if (DesiredTemperature == 0)
	{
		Cooldown();
		TurnOffTimer3;
	}
	else
	{
		TurnOnTimer3;
	}
}

bool TemperatureClass::WaitForHotendTemperature()
{
	if (DesiredTemperature == 0)
	{
		return true;
	}

	if (CurrentTemperature < (DesiredTemperature - TEMP_HYSTERESIS) || CurrentTemperature > (DesiredTemperature + TEMP_HYSTERESIS))
	{
		LastTime = millis();
	}

	if (millis() - LastTime > (TEMP_RESIDENCY_TIME * 1000))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TemperatureClass::Cooldown()
{
	analogWrite(HEATER_PIN, 0);
}

void TemperatureClass::ISR_EXECUTE()
{
	if (Data.End_Effector != USE_PRINTER)
	{
		Cooldown();
		return;
	}

	GetTemperature();

	float error = DesiredTemperature - CurrentTemperature;
	if (error < 0)
	{
		analogWrite(HEATER_PIN, 0);
		return;
	}

	float dError = error - LastError;
	LastError = error;

	float P = error * DEFAULT_KP;
	I += error * DEFAULT_KI * ((float)INTERRUPT_CYCLE_TIMER3 / 1000);
	float D = (dError * DEFAULT_KD) / ((float)INTERRUPT_CYCLE_TIMER3 / 1000);

	float pwmValue = P + I + D;

	pwmValue = constrain(pwmValue, 0, 255);

	analogWrite(HEATER_PIN, pwmValue);
}

ISR(TIMER3_COMPA_vect)
{
	Temperature.ISR_EXECUTE();
}

TemperatureClass Temperature;

