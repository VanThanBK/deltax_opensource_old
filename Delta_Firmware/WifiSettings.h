// WifiSettings.h

#ifndef _WIFISETTINGS_h
#define _WIFISETTINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM.h>
#include "config.h"

class WifiSettingsClass
{
 protected:


 public:
	void init();
	void Save();
	void SaveIP();
	void IP();
	void GetSsid();
	void GetPswd();

	String SSIDWifi;
	String PSWDWifi;
	String IPWifi;
};

extern WifiSettingsClass WifiSettings;

#endif

