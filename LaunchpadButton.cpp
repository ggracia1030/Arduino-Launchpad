#include "LaunchpadButton.h"

LaunchpadButton::LaunchpadButton(char _keyboard) : Component() {
	componentName = "Launchpad Button";
	keyboard = _keyboard;
}

LaunchpadButton::LaunchpadButton(unsigned int _pin, PinMode pinMode, char _keyboard) : Component(_pin, pinMode) {
	componentName = "Launchpad Button";
	keyboard = _keyboard;
}

LaunchpadButton::~LaunchpadButton() {

}

bool LaunchpadButton::isButtonPressed() {
#if defined (__AVR__) || (__avr__)
	return DigitalRead();
#else
	return Input::GetKey(keyboard);
#endif
}

void LaunchpadButton::Action()
{
}
