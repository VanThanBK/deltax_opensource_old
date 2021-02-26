// LedConnect.h

#ifndef _CONNECTIONSTATE_h
#define _CONNECTIONSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "pin.h"
#include "enum.h"
#include "fastio.h"

#define TIME_DISCONNECT 60000

class ConnectionStateClass
{
 protected:

private:

	uint32_t LastTimeBlink;
	uint32_t LastTimeDisconnect;
	uint16_t TimeBlink;
	COLOR Color;
	void SetColor(COLOR color);
	void SetBlink(uint16_t ms);

 public:
	void Init();
	void Connect();
	void Disconnect();
	void Execute();
	void ResetTimeDisconnect();

};

extern ConnectionStateClass ConnectionState;

#endif

