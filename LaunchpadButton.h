#ifndef LAUNCHPAD_BUTTON_H
#define LAUNCHPAD_BUTTON_H

#include "Note.h"
#include "Component.h"
#ifndef __AVR__ && __avr__
#include "Input.h"
#endif


class LaunchpadButton : public Component {
public:
    LaunchpadButton(char _keyboard);
	LaunchpadButton(unsigned int _pin, PinMode pinMode, char _keyboard);
    ~LaunchpadButton();

	virtual bool isButtonPressed();
	virtual void Action();
protected:
	
	char keyboard;
};

#endif