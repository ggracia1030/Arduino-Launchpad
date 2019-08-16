#ifndef LAUNCHPAD_BUTTON_H
#define LAUNCHPAD_BUTTON_H

#include "BuzzerNotes.h"
#include "Component.h"



class LaunchpadButton : public Component {
public:
    LaunchpadButton();
	LaunchpadButton(unsigned int _pin, PinMode pinMode);
    ~LaunchpadButton();

	bool isButtonPressed();

private:

};

#endif