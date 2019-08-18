#ifndef SOUND_BUTTON_H
#define SOUND_BUTTON_H

#include "LaunchpadButton.h"
#include "Note.h"
#include "SoundManager.h"

class SoundButton : public LaunchpadButton {
public:

	SoundButton(SoundManager* _soundManager, int _xPin, int _yPin, char _keyboard);
	SoundButton(SoundManager* _soundManager, Note::Notes _note, int octave, char _keyboard);
	~SoundButton();

	Note* GetSound() { return sound; }
	void Action();
	bool isButtonPressed();

	const int GetXPin() { return xPin; }
	const int GetYPin() { return yPin; }

private:
	Note* sound;
	int xPin, yPin;
	SoundManager* soundManager;
	
};

#endif