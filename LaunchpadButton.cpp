#include "LaunchpadButton.h"

LaunchpadButton::LaunchpadButton() {
	note = new BuzzerNotes();
}

LaunchpadButton::LaunchpadButton(int pin) {
    buttonPin = pin;
    //pinMode(pin, INPUT_PULLUP);
    note = new BuzzerNotes();
}

LaunchpadButton::LaunchpadButton(int pin, BuzzerNotes::Notes _note, int octave) {
    buttonPin = pin;
    //pinMode(pin, INPUT_PULLUP);
    note = new BuzzerNotes(_note, octave);
}

bool LaunchpadButton::IsButtonPressed() {
    //return digitalRead(buttonPin) == LOW;
	return true;
}

LaunchpadButton::~LaunchpadButton() {
    if(note)
        delete note;
}