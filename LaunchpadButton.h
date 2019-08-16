#ifndef LAUNCHPAD_BUTTON_H
#define LAUNCHPAD_BUTTON_H

#include "BuzzerNotes.h"

#if defined(__AVR__) || (__avr__)
	#include "Arduino.h"
#endif

class LaunchpadButton {
    public:
        LaunchpadButton();
        LaunchpadButton(int pin);
        LaunchpadButton(int pin, BuzzerNotes::Notes _note, int octave);
        ~LaunchpadButton();

		BuzzerNotes* GetSound() { return sound; }
        int GetButtonPin() { return buttonPin; }
		void SetButtonPin(unsigned int value) { buttonPin = value; }

        bool IsButtonPressed();

    private:
        BuzzerNotes* sound;
        int buttonPin;
};

#endif