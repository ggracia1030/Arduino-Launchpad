#include "LaunchpadManager.h"

const char LaunchpadManager::KeyboardBtnToChar(KeyboardButtons btn) {
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

LaunchpadManager::LaunchpadManager(int _length) {
	length = _length;
	soundManager = new SoundManager(4000000, 3);
	soundButtons = new SoundButton**[length];

	for (int i = 0; i < length; i++) {
		soundButtons[i] = new SoundButton * [length];
	}

	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			soundButtons[x][y] = new SoundButton(soundManager, x, y, KeyboardBtnToChar((LaunchpadManager::KeyboardButtons)(y*length + x)));
			soundButtons[x][y]->GetSound()->SetNote((Note::Notes)x, y+3);
		}
	}
}

LaunchpadManager::LaunchpadManager(int _length, int _firstPin) {
	
}

LaunchpadButton* LaunchpadManager::GetButton(int _x, int _y) {
    return soundButtons[_x][_y];
}

void LaunchpadManager::Update() {
	UpdateInput();
}

void LaunchpadManager::UpdateInput() {
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			if (soundButtons[x][y]->isButtonPressed()) {
#ifndef __AVR__ && avr
				std::cout << "\nButton: " << KeyboardBtnToChar((LaunchpadManager::KeyboardButtons)(y * length + x)) << " CLICK!" << std::endl;
#endif
				soundButtons[x][y]->Action();
			}
		}
	}

}

LaunchpadManager::~LaunchpadManager() {
	if (soundButtons) {
		for (int y = 0; y < length; y++) {
			for (int x = 0; x < length; x++) {
				delete soundButtons[x][y];
			}
			delete soundButtons[y];
		}
	}
	delete[] soundButtons;
}