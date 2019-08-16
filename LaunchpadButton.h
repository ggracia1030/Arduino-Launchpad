#ifndef LAUNCHPAD_BUTTON_H
#define LAUNCHPAD_BUTTON_H

#include "BuzzerNotes.h"
//#include "Arduino.h"

class LaunchpadButton {
    public:
        LaunchpadButton();
        LaunchpadButton(int pin);
        LaunchpadButton(int pin, BuzzerNotes::Notes _note, int octave);
        ~LaunchpadButton();

		BuzzerNotes* GetNote() { return note; }
        int GetButtonPin() { return buttonPin; }

        bool IsButtonPressed();
    private:
        BuzzerNotes* note;
        int buttonPin;
};

#endif