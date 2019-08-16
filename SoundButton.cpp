#include "SoundButton.h"

SoundButton::SoundButton() : LaunchpadButton() {
	sound = new BuzzerNotes();
}

SoundButton::SoundButton(BuzzerNotes::Notes _note, int octave) : LaunchpadButton() {
	sound = new BuzzerNotes(_note, octave);
}