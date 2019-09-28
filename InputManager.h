#pragma once
#include"SoundButton.h"
#include "OptionsManager.h"

class InputManager
{
public:

	enum KeyboardButtons {
		A, W, S, D, R, F, T, G, Y, H, J, I, K, O, L
	};

	InputManager(int _firstPin, int _acceptBtnPin, int _cancelBtnPin, int _soundButtonsLength, SoundManager* soundManager, OptionsManager* optionsManager);
	~InputManager();

	SoundButton* GetSoundButton(int i);
	LaunchpadButton* GetAcceptButton() { return acceptButton; }
	LaunchpadButton* GetCancelButton() { return cancelButton; }

	int GetSoundButtonsLength() { return soundButtonsLength; }

	const char KeyboardBtnToChar(KeyboardButtons btn);


private:
	friend class LaunchpadManager;
	void EarlyUpdate();

	SoundButton** soundButtons;
	LaunchpadButton* acceptButton;
	LaunchpadButton* cancelButton;

	int soundButtonsLength;
	int firstSoundButtonPin;
};

