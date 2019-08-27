#pragma once
#include"SoundButton.h"
#include "OptionsManager.h"

class InputManager
{
public:

	enum KeyboardButtons {
		One, Two, Three, Four, Five, Six,
		Q, W, E, R, T, Y,
		A, S, D, F, G, H,
		Z, X, C, V, B, N
	};

	InputManager(int _firstPin, int _acceptBtnPin, int _cancelBtnPin, int _soundButtonsLength, SoundManager* soundManager, OptionsManager* optionsManager);
	~InputManager();

	SoundButton* GetSoundButton(int posX, int posY);
	LaunchpadButton* GetAcceptButton() { return acceptButton; }
	LaunchpadButton* GetCancelButton() { return cancelButton; }

	int GetSoundButtonsLength() { return soundButtonsLength; }

	const char KeyboardBtnToChar(KeyboardButtons btn);


private:
	friend class LaunchpadManager;
	void EarlyUpdate();

	SoundButton*** soundButtons;
	LaunchpadButton* acceptButton;
	LaunchpadButton* cancelButton;

	int soundButtonsLength;
	int firstSoundButtonPin;
};

