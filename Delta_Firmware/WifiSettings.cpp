// 
// 
// 

#include "WifiSettings.h"

void WifiSettingsClass::init()
{


}

void WifiSettingsClass::Save()
{
	char ssidWifi[32] = "";
	char pswdWifi[32] = "";
	SSIDWifi.toCharArray(ssidWifi, 32);
	PSWDWifi.toCharArray(pswdWifi, 32);

	EEPROM.put(133, ssidWifi);
	EEPROM.put(167, pswdWifi);

	delay(1);
}

void WifiSettingsClass::SaveIP()
{
	char ipWifi[32] = "";
	IPWifi.toCharArray(ipWifi, 32);
	EEPROM.put(100, ipWifi);
	delay(1);
}

void WifiSettingsClass::IP()
{
	char ipWifi[32] = "";
	EEPROM.get(100, ipWifi);
	delay(1);
	SERIAL_PORT.println(ipWifi);
}

void WifiSettingsClass::GetSsid()
{
	char ssidWifi[32] = "";
	EEPROM.get(133, ssidWifi);

	SERIAL_PORT.println("SSID:" + SSIDWifi);
}

void WifiSettingsClass::GetPswd()
{
	char pswdWifi[32] = "";
	EEPROM.get(167, pswdWifi);

	SERIAL_PORT.println("PSWD:" + PSWDWifi);
}





WifiSettingsClass WifiSettings;

