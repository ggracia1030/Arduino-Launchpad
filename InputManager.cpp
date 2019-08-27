#include "InputManager.h"

InputManager::InputManager(int _firstPin, int _acceptBtnPin, int _cancelBtnPin, int _soundButtonsLength, SoundManager* soundManager, OptionsManager* optionsManager)
{
	soundButtonsLength = _soundButtonsLength;

	soundButtons = new SoundButton **[_soundButtonsLength];
	for (int i = 0; i < _soundButtonsLength; i++) {
		soundButtons[i] = new SoundButton * [_soundButtonsLength];
	}

	for (int y = 0; y < _soundButtonsLength; y++) {
		for (int x = 0; x < _soundButtonsLength; x++) {
			soundButtons[x][y] = new SoundButton(soundManager, _firstPin + x, _firstPin + _soundButtonsLength + y, 0, KeyboardBtnToChar((KeyboardButtons)(y * _soundButtonsLength + x)));
			soundButtons[x][y]->SetSound(optionsManager->notes[x][y]);

			/*if (x == _soundButtonsLength - 1) {
				soundButtons[x][y]->GetSound()->SetNote(Note::Noise, y);
			}
			else {
				//soundButtons[x][y]->GetSound()->SetNote((Note::Notes)((x + _soundButtonsLength * y) % 12), (x + _soundButtonsLength * y) / 12 + 1);
				soundButtons[x][y]->GetSound()->SetNote((Note::Notes)(soundButtons[x][y]->GetSound()->GuitarTunningNotes[x]), soundButtons[x][y]->GetSound()->GuitarTunningOctaves[x]);
				*(soundButtons[x][y]->GetSound()) = *(soundButtons[x][y]->GetSound()) + y;
			}*/
		}
	}
	firstSoundButtonPin = _firstPin;
	acceptButton = new LaunchpadButton(_acceptBtnPin, Component::PinMode::_INPUT_, 'U');
	cancelButton = new LaunchpadButton(_cancelBtnPin, Component::PinMode::_INPUT_, 'I');
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
#if defined (__AVR__) || defined (__avr__)
		digitalWrite(firstSoundButtonPin + soundButtonsLength + y, HIGH);
#endif
		for (int x = 0; x < soundButtonsLength; x++) {
			soundButtons[x][y]->Update();
		}
#if defined (__AVR__) || defined (__avr__)
		digitalWrite(firstSoundButtonPin + soundButtonsLength + y, LOW);
#endif
	}
	acceptButton->Update();
	cancelButton->Update();
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
	case Five:
		temp = '5';
		break;
	case Six:
		temp = '6';
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
	case T:
		temp = 'T';
		break;
	case Y:
		temp = 'Y';
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
	case G:
		temp = 'G';
		break;
	case H:
		temp = 'H';
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
	case B:
		temp = 'B';
		break;
	case N:
		temp = 'N';
		break;
	}

	return temp;
}
