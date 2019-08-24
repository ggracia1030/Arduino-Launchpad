#include "LaunchpadButton.h"

LaunchpadButton::LaunchpadButton(char _keyboard) : Component() {
	componentName = "Launchpad Button";
	keyboard = _keyboard;
}

LaunchpadButton::LaunchpadButton(unsigned int _pin, PinMode pinMode, char _keyboard) : Component(_pin, PinMode::_INPUT_) {
	componentName = "Launchpad Button";
	keyboard = _keyboard;
}

LaunchpadButton::~LaunchpadButton() {

}

bool LaunchpadButton::GetButton()
{
	return currentState;
}

bool LaunchpadButton::GetButtonDown()
{
	return currentState && !lastState;
}

bool LaunchpadButton::GetButtonUp()
{
	return !currentState && lastState;
}

bool LaunchpadButton::isButtonPressed()
{
#if defined (__AVR__) || (__avr__)
	return DigitalRead();
#else
	return Input::GetKey(keyboard);
#endif
}

void LaunchpadButton::Update() {
	lastState = currentState;
	currentState = isButtonPressed();
}

void LaunchpadButton::OnButtonDown()
{
}
void LaunchpadButton::OnButtonUp()
{
}

