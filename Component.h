#pragma once

#if defined(__AVR__) || (__avr__)
#include "Arduino.h"
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

	bool DigitalRead();
	void DigitalWrite(bool value);
	int AnalogRead();
	void AnalogWrite(unsigned int value);

private:
	int pin;
};

