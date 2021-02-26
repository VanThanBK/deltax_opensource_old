// 
// 
// 

#include "GCodeReceiver.h"

void GCodeReceiverClass::Init(vector<String>* gCodeQueue, HardwareSerial* serial, unsigned long baudrate)
{
	ReceiveSerial = serial;
	ReceiveSerial->begin(baudrate);
	receiveString.reserve(100);

	isStringComplete = false;
	receiveString = "";

	this->GCodeQueue = gCodeQueue;
}

void GCodeReceiverClass::Execute()
{
	while (ReceiveSerial->available())
	{
		char inChar = (char)ReceiveSerial->read();

		if (inChar == '\n')
		{
			isStringComplete = true;
			break;
		}

		if (inChar != '\r')
		{
			receiveString += inChar;
		}
	}

	if (!isStringComplete)
		return;

	if (receiveString[0] == 'M' || receiveString[0] == 'G')
	{
		GCodeQueue->push_back(receiveString);
		receiveString = "";
		isStringComplete = false;
		return;
	}

	int index = receiveString.indexOf(':');

	if (index == -1)
	{
		if (receiveString == "IsDelta") ConnectionState.Connect();
		if (receiveString == "Disconnect") ConnectionState.Disconnect();
		if (receiveString == "SAVEWIFI") WifiSettings.Save();
		if (receiveString == "SAVEIP") WifiSettings.SaveIP();
		if (receiveString == "IP") WifiSettings.IP();
		if (receiveString == "gSsid") WifiSettings.GetSsid();
		if (receiveString == "gPswd") WifiSettings.GetPswd();
	}
	else
	{
		String keyString = receiveString.substring(0, index);
		String valueString = receiveString.substring(index + 1);
		if (keyString == "SSID") WifiSettings.SSIDWifi = valueString;
		if (keyString == "PSWD") WifiSettings.PSWDWifi = valueString;
		if (keyString == "ESPIP") WifiSettings.IPWifi = valueString;
	}

	receiveString = "";
	isStringComplete = false;
}