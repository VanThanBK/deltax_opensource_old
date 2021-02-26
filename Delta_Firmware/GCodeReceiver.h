// GCodeReceiver.h

#ifndef _GCODERECEIVER_h
#define _GCODERECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <vector>
#include "ConnectionState.h"
#include "WifiSettings.h"

using namespace std;

class GCodeReceiverClass
{
public:
	void Init(vector<String>* gCodeQueue, HardwareSerial* serial, unsigned long baudrate);

	void Execute();

	HardwareSerial* ReceiveSerial;
	unsigned long Baudrate;

	vector<String>* GCodeQueue;

private:
	
	String receiveString;
	bool isStringComplete;
};

#endif

