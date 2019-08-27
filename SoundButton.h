#ifndef SOUND_BUTTON_H
#define SOUND_BUTTON_H

#include "LaunchpadButton.h"
#include "Note.h"
#include "SoundManager.h"

class SoundButton : public LaunchpadButton {
public:

	SoundButton(SoundManager* _soundManager, int _xPin, int _yPin, int soundChannel, char _keyboard);
	~SoundButton();

	Note* GetSound() { return sound; }
	void SetSound(Note* note) { sound = note; }
	void OnButtonUp();
	virtual void OnButtonDown();

	const int GetXPin() { return xPin; }
	const int GetYPin() { return yPin; }
	void SetSoundChannel(int _channel);

	const int GetSoundChannel() { return soundChannel; }

protected:
	bool isButtonPressed();

	Note* sound;
	int soundChannel;
	int xPin, yPin;
	SoundManager* soundManager;
	
};

#endif