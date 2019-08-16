#include "LaunchpadButton.h"

LaunchpadButton::LaunchpadButton() : Component() {

}

LaunchpadButton::LaunchpadButton(int _pin) : Component(_pin) {

}

LaunchpadButton::~LaunchpadButton() {

}

bool LaunchpadButton::isButtonPressed() {
#if defined __ARDUINO__
	return DigitalRead();
#else
	return false;
#endif;
}