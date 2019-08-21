#include "Component.h"

Component::Component()
{
	pin = -1;
	componentName = "Base Component";
}

Component::Component(unsigned int _pin, PinMode _pinMode) {
	pin = _pin;
#if defined(__AVR__) || (__avr__)
	switch (_pinMode) {
		case _OUTPUT_:
			pinMode(pin, OUTPUT);
			break;
		case _INPUT_:
			pinMode(pin, INPUT);
			break;
		case _INPUT_PULLUP_:
			pinMode(pin, INPUT_PULLUP);
			break;
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

bool Component::DigitalRead(int _pin)
{
#if defined(__AVR__) || (__avr__)
	return (digitalRead(pin) == HIGH);
#else 
	std::cout << "\n----------------------------------------" << std::endl;
	std::cout << "Digital Read of component " + componentName + " in pin : " << pin << std::endl;
	return 0;
#endif
}

bool Component::DigitalRead()
{
	return (Component::DigitalRead(pin));
}

void Component::DigitalWrite(bool value)
{
	Component::DigitalWrite(pin, value);
}

void Component::DigitalWrite(int _pin, bool value)
{
#if defined(__AVR__) || (__avr__)
	if (value)
		digitalWrite(_pin, HIGH);

	else digitalWrite(_pin, LOW);
#else
	std::cout << "\n----------------------------------------" << std::endl;
	std::cout << "Digital Write of component " + componentName + " in pin : " << _pin << " with value: " << value << std::endl;
#endif
}

int Component::AnalogRead()
{
#if defined(__AVR__) || (__avr__)
	return analogRead(pin);
#else
	std::cout << "\n----------------------------------------" << std::endl;
	std::cout << "Analog Read of component: " + componentName << " in pin : " << pin << std::endl;
	return 0;
#endif
}

void Component::AnalogWrite(unsigned int value)
{
#if defined(__AVR__) || (__avr__)
	analogWrite(pin, value);
#else
	std::cout << "\n----------------------------------------" << std::endl;
	std::cout << "Analog Write of component: " + componentName << " in pin : " << pin << " with value: " << value << std::endl;
#endif
}
