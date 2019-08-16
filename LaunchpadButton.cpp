#include "LaunchpadButton.h"

LaunchpadButton::LaunchpadButton() : Component() {

}

LaunchpadButton::LaunchpadButton(unsigned int _pin, PinMode pinMode) : Component(_pin, pinMode) {

}

LaunchpadButton::~LaunchpadButton() {

}

bool LaunchpadButton::isButtonPressed() {
#if defined __ARDUINO__
	return DigitalRead();
#else
	return false;
#endif
}