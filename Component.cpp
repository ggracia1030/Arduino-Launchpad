#include "Component.h"

Component::Component()
{
	pin = -1;
}

Component::Component(unsigned int _pin, PinMode _pinMode) {
	pin = _pin;
#if defined(__AVR__) || (__avr__)
	if (_pinMode == _OUTPUT_) {
		pinMode(pin, OUTPUT);
	}
	else if (_pinMode == _INPUT_) {
		pinMode(pin, INPUT);
	}
	else if (_pinMode == _INPUT_PULLUP_) {
		pinMode(pin, INPUT_PULLUP);
	}
#endif
}

Component::~Component()
{

}

void Component::SetPin(unsigned int value)
{
	pin = value;
}

bool Component::DigitalRead()
{
#if defined(__AVR__) || (__avr__)
	return if digitalRead(pin) == HIGH;
#else
	return 0;
#endif
}

void Component::DigitalWrite(bool value)
{
#if defined(__AVR__) || (__avr__)
	if (value)
		digitalWrite(pin, HIGH);

	else digitalWrite(pin, LOW);
#endif
}

int Component::AnalogRead()
{
#if defined(__AVR__) || (__avr__)
	return analogRead(pin);
#else
	return 0;
#endif
}

void Component::AnalogWrite(unsigned int value)
{
#if defined(__AVR__) || (__avr__)
	analogWrite(pin, value);
#endif
}
