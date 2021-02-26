// GCodeExecute.h

#ifndef _GCODEEXECUTE_h
#define _GCODEEXECUTE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <vector>
#include "enum.h"
#include "Motion.h"
#include "Control.h"

#define NULL_NUMBER 98765

using namespace std;

class KeyValue
{
public:
	char Key;
	float Value;
};

class NoArgumentFunction
{
public:
	String Code;
	void(*Function)();
};

class GCodeExecuteClass
{
public:
	void Init(vector<String>*);
	void Add(String Code, void(*func)());
	void Run();

	vector<String>* GCodeQueue;
	bool IsRunning;

	float X, Y, Z, E, S, A, I, J, F, P, R, Q, W;
private:
	vector<KeyValue> getKeyValues(String code);
	void checkAndRunFunction(KeyValue keyValue);
	void ResetValue();
	vector <NoArgumentFunction> NoArgumentFunctions;
};


#endif

