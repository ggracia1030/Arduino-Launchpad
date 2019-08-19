#pragma once
#include "Component.h"
class LCDScreen :
	public Component
{
public:
	LCDScreen();
	LCDScreen(int pin, PinMode _pinMode);
	~LCDScreen();


#if !defined (__AVR__) && !defined (__avr__)
	void SetLCDString(std::string msg, int row);
	std::string GetString(int row) { return lcdString[row]; }
#else
	void SetLCDString(String msg, int row);
	String GetString(int row) { return lcdString[row]; }
#endif
private:
#if !defined (__AVR__) && !defined (__avr__)
	std::string lcdString[2];
#else
String lcdString[2];
#endif
};

