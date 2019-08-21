#pragma once

#if defined(__AVR__) || (__avr__)
#include "Arduino.h"
#else
#include <iostream>
#include <string.h>
#include "Console.h"
#endif

class Component
{
public:
	enum PinMode {_OUTPUT_, _INPUT_, _INPUT_PULLUP_};

	Component();
	Component(unsigned int _pin, PinMode _pinMode);
	~Component();

	int GetPin() { return pin; }
	void SetPin(unsigned int value);

	bool DigitalRead(int _pin);
	bool DigitalRead();
	void DigitalWrite(bool value);
	void DigitalWrite(int _pin, bool value);
	int AnalogRead();
	void AnalogWrite(unsigned int value);

protected:
	int pin;
#if defined(__AVR__) || (__avr__)
	String componentName;
#else
	std::string componentName;
#endif
};

