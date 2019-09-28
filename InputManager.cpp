#include "InputManager.h"

InputManager::InputManager(int _firstPin, int _acceptBtnPin, int _cancelBtnPin, int _soundButtonsLength, SoundManager* soundManager, OptionsManager* optionsManager)
{
	soundButtonsLength = _soundButtonsLength;

	soundButtons = new SoundButton *[_soundButtonsLength];

	for (int i = 0; i < _soundButtonsLength; i++) {
		soundButtons[i] = new SoundButton(soundManager, _firstPin + i, _firstPin + _soundButtonsLength + i, 0, KeyboardBtnToChar((KeyboardButtons)(i)));
		soundButtons[i]->SetSound(optionsManager->notes[i]);
	}
	firstSoundButtonPin = _firstPin;
	acceptButton = new LaunchpadButton(_acceptBtnPin, Component::PinMode::_INPUT_, '8');
	cancelButton = new LaunchpadButton(_cancelBtnPin, Component::PinMode::_INPUT_, '9');
}

InputManager::~InputManager()
{
	if (soundButtons != nullptr) {
		for (int i = 0; i < soundButtonsLength; i++) {
			delete soundButtons[i];
		}
		if (soundButtons != nullptr)
			delete[] soundButtons;
	}
}

void InputManager::EarlyUpdate()
{
	for (int i = 0; i < soundButtonsLength; i++) {
		soundButtons[i]->Update();
	}
	acceptButton->Update();
	cancelButton->Update();
}

SoundButton* InputManager::GetSoundButton(int i)
{
	if (i >= 0 && i < soundButtonsLength) {
		return soundButtons[i];
	}
	return nullptr;
}

const char InputManager::KeyboardBtnToChar(KeyboardButtons btn) {
	char temp = ' ';
	switch (btn) {

	case A:
		temp = 'A';
		break;
	case W:
		temp = 'W';
		break;
	case S:
		temp = 'S';
		break;
	case D:
		temp = 'D';
		break;
	case R:
		temp = 'R';
		break;
	case F:
		temp = 'F';
		break;
	case T:
		temp = 'T';
		break;
	case G:
		temp = 'G';
		break;
	case Y:
		temp = 'Y';
		break;
	case H:
		temp = 'H';
		break;
	case J:
		temp = 'J';
		break;
	case I:
		temp = 'I';
		break;
	case K:
		temp = 'K';
		break;
	case O:
		temp = 'O';
		break;
	case L:
		temp = 'L';
		break;

	}
	return temp;
}
