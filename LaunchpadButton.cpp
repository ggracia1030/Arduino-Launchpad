#include "LaunchpadButton.h"

LaunchpadButton::LaunchpadButton() {
	sound = new BuzzerNotes();
}

LaunchpadButton::LaunchpadButton(int pin) {
    buttonPin = pin;
#if defined (__AVR__) || (__avr__)
    pinMode(pin, INPUT_PULLUP);
#endif
    sound = new BuzzerNotes();
}

LaunchpadButton::LaunchpadButton(int pin, BuzzerNotes::Notes _note, int octave) {
    buttonPin = pin;
#if defined (__AVR__) || (__avr__)
    pinMode(pin, INPUT_PULLUP);
#endif
    sound = new BuzzerNotes(_note, octave);
}

bool LaunchpadButton::IsButtonPressed() {
#if defined (__AVR__) || (__avr__)
    return digitalRead(buttonPin) == LOW;
#else
	return true;
#endif
}

LaunchpadButton::~LaunchpadButton() {
	if (sound)
        delete sound;
}