#ifndef LAUNCHPAD_BUTTON_H
#define LAUNCHPAD_BUTTON_H

#include "BuzzerNotes.h"
#include "Component.h"

#if defined(__AVR__) || (__avr__)
	#include "Arduino.h"
#endif

class LaunchpadButton : public Component {
public:
    LaunchpadButton();
	LaunchpadButton(int _pin);
    ~LaunchpadButton();

	bool isButtonPressed();

private:

};

#endif