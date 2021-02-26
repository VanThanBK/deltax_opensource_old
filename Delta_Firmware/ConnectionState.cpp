// 
// 
// 

#include "ConnectionState.h"

void ConnectionStateClass::Init()
{
	pinMode(LED_G_PIN, OUTPUT);
	pinMode(LED_R_PIN, OUTPUT);
	pinMode(LED_B_PIN, OUTPUT);

	WRITE(LED_G_PIN, 1);
	WRITE(LED_R_PIN, 1);
	WRITE(LED_B_PIN, 1);

	LastTimeBlink = millis();
	LastTimeDisconnect = millis();

	SetColor(RED);
	SetBlink(100);
}

void ConnectionStateClass::SetColor(COLOR color)
{
	Color = color;
	WRITE(LED_G_PIN, 1);
	WRITE(LED_R_PIN, 1);
	WRITE(LED_B_PIN, 1);
}

void ConnectionStateClass::SetBlink(uint16_t ms)
{
	TimeBlink = ms;
	if (TimeBlink == 0)
	{
		switch (Color)
		{
		case RED:
			WRITE(LED_R_PIN, 0);
			break;
		case GREEN:
			WRITE(LED_G_PIN, 0);
			break;
		case BLUE:
			WRITE(LED_B_PIN, 0);
			break;
		default:
			break;
		}
	}
}

void ConnectionStateClass::Execute()
{
	if (millis() - LastTimeBlink < TimeBlink || TimeBlink == 0)
	{
		return;
	}

	if (millis() - LastTimeDisconnect > TIME_DISCONNECT)
	{
		Disconnect();
		LastTimeDisconnect = millis();
	}

	LastTimeBlink = millis();

	switch (Color)
	{
	case RED:
		WRITE(LED_R_PIN, !READ(LED_R_PIN));
		break;
	case GREEN:
		WRITE(LED_G_PIN, !READ(LED_G_PIN));
		break;
	case BLUE:
		WRITE(LED_B_PIN, !READ(LED_B_PIN));
		break;
	default:
		break;
	}
}

void ConnectionStateClass::ResetTimeDisconnect()
{
	LastTimeDisconnect = millis();
}

void ConnectionStateClass::Connect()
{
	SERIAL_PORT.println("YesDelta");
	LastTimeDisconnect = millis();
	SetColor(BLUE);
	SetBlink(1000);
}

void ConnectionStateClass::Disconnect()
{
	SetColor(RED);
	SetBlink(100);
}

ConnectionStateClass ConnectionState;

