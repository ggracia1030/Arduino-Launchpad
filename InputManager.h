#pragma once
#include"SoundButton.h"

class InputManager
{
public:

	enum KeyboardButtons {
		One, Two, Three, Four,
		Q, W, E, R,
		A, S, D, F,
		Z, X, C, V
	};

	InputManager(int _firstPin, int _acceptBtnPin, int _cancelBtnPin, int _soundButtonsLength, SoundManager* soundManager);
	~InputManager();

	SoundButton* GetSoundButton(int posX, int posY);
	LaunchpadButton* GetAcceptButton() { return acceptButton; }
	LaunchpadButton* GetCancelButton() { return cancelButton; }

	const char KeyboardBtnToChar(KeyboardButtons btn);


private:
	friend class LaunchpadManager;
	void EarlyUpdate();

	SoundButton*** soundButtons;
	LaunchpadButton* acceptButton;
	LaunchpadButton* cancelButton;

	int soundButtonsLength;
};

