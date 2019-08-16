#ifndef SOUND_BUTTON_H
#define SOUND_BUTTON_H

#include "LaunchpadButton.h"
#include "BuzzerNotes.h"

class SoundButton : public LaunchpadButton {
public:
	SoundButton();
	SoundButton(BuzzerNotes::Notes _note, int octave);
	BuzzerNotes* GetSound() { return sound; }


private:
	BuzzerNotes* sound;
};

#endif