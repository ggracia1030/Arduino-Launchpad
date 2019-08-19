#ifndef LAUNCHPAD_BUTTON_H
#define LAUNCHPAD_BUTTON_H

#include "Note.h"
#include "Component.h"
#if !defined (__AVR__) && !defined (__avr__)
#include "Input.h"
#endif


class LaunchpadButton : public Component {
public:
    LaunchpadButton(char _keyboard);
	LaunchpadButton(unsigned int _pin, PinMode pinMode, char _keyboard);
    ~LaunchpadButton();

	//virtual bool isButtonPressed();

	bool GetButton();
	bool GetButtonDown();
	bool GetButtonUp();

	virtual void Action();
protected:
	friend class InputManager;
	char keyboard;
	bool lastState, currentState;

	virtual bool isButtonPressed();

	void Update();
};

#endif