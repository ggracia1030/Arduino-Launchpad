#include "InputManager.h"

InputManager::InputManager(int _firstPin, int _soundButtonsLength, SoundManager* soundManager)
{
	soundButtonsLength = _soundButtonsLength;

	soundButtons = new SoundButton **[_soundButtonsLength];
	for (int i = 0; i < _soundButtonsLength; i++) {
		soundButtons[i] = new SoundButton * [_soundButtonsLength];
	}

	for (int y = 0; y < _soundButtonsLength; y++) {
		for (int x = 0; x < _soundButtonsLength; x++) {
			soundButtons[x][y] = new SoundButton(soundManager, _firstPin + x, _firstPin + _soundButtonsLength + y, KeyboardBtnToChar((KeyboardButtons)(y * _soundButtonsLength + x)));
			soundButtons[x][y]->GetSound()->SetNote((Note::Notes)((x + _soundButtonsLength * y) % 12), (x + _soundButtonsLength * y) / 12 + 4);
		}
	}
}

InputManager::~InputManager()
{
	if (soundButtons != nullptr) {
		for (int y = 0; y < soundButtonsLength; y++) {
			for (int x = 0; x < soundButtonsLength; x++) {
				delete soundButtons[x][y];
			}
		}
		if (soundButtons != nullptr)
			delete[] soundButtons;
	}
}

void InputManager::EarlyUpdate()
{
	for (int y = 0; y < soundButtonsLength; y++) {
		for (int x = 0; x < soundButtonsLength; x++) {
			soundButtons[x][y]->Update();
		}
	}
}

SoundButton* InputManager::GetSoundButton(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < soundButtonsLength && posY < soundButtonsLength) {
		return soundButtons[posX][posY];
	}
	return nullptr;
}

const char InputManager::KeyboardBtnToChar(KeyboardButtons btn) {
	char temp = ' ';
	switch (btn) {
	case One:
		temp = '1';
		break;
	case Two:
		temp = '2';
		break;
	case Three:
		temp = '3';
		break;
	case Four:
		temp = '4';
		break;

	case Q:
		temp = 'Q';
		break;
	case W:
		temp = 'W';
		break;
	case E:
		temp = 'E';
		break;
	case R:
		temp = 'R';
		break;

	case A:
		temp = 'A';
		break;
	case S:
		temp = 'S';
		break;
	case D:
		temp = 'D';
		break;
	case F:
		temp = 'F';
		break;

	case Z:
		temp = 'Z';
		break;
	case X:
		temp = 'X';
		break;
	case C:
		temp = 'C';
		break;
	case V:
		temp = 'V';
		break;
	}

	return temp;
}
