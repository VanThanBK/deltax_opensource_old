/*
 Name:		Delta_Firmware.ino
 Created:	6/22/2018 10:54:13 AM
 Author:	Than
*/

#include "WifiSettings.h"
#include <avr/interrupt.h>
#include <EEPROM.h>
#include "config.h"
#include "pin.h"
#include "enum.h"
#include "Geometry.h"
#include "Constants.h"
#include "fastio.h"
#include "Storage.h"
#include <ArduinoSTL.h>
#include <vector>
#include "GCodeReceiver.h"
#include "GCodeExecute.h"
#include "Planner.h"
#include "Control.h"
#include "Motion.h"
#include "Tool.h"
#include "DeltaKinematics.h"
#include "EndStops.h"
#include "EndEffector.h"
#include "Servo.h"
#include "MultiServo.h"
#include "Stepper.h"
#include "Temperature.h"
#include "ConnectionState.h"

using namespace std;

GCodeReceiverClass GcodeReceiver;
GCodeExecuteClass GcodeExecute;

vector<String> GCodeQueue;
vector<Segment> SegmentQueue;

void setup() {
	SERIAL_PORT.begin(BAUDRATE);
	Data.init();
	Storage.init();

	EndStops.init();
	Temperature.init();
	Planner.init(&SegmentQueue);
	Stepper.init(&SegmentQueue);
	MultiServo.init();
	ConnectionState.Init();

	GcodeReceiver.Init(&GCodeQueue, &SERIAL_PORT, BAUDRATE);
	GcodeExecute.Init(&GCodeQueue);

	Serial.println("Init Success!");
	Motion.G28();
}

void loop() {
	GcodeReceiver.Execute();
	GcodeExecute.Run();
	WhenFinishMove();
	ConnectionState.Execute();
}

void WhenFinishMove()
{
	if (Stepper.GetStateMotor() == true)
	{
		if (GcodeExecute.IsRunning == true)
		{
			
			if (Data.IsExecutedGcode == true)
			{
				Serial.println("Ok");	
			}
			else
			{
				if (!Tool.Wait())
				{
					return;
				}
			}
			ConnectionState.ResetTimeDisconnect();
			GcodeExecute.IsRunning = false;
			Data.IsExecutedGcode = false;
		}
	}
}

