#include "LaunchpadManager.h"

LaunchpadManager::LaunchpadManager(int _length) {
	length = _length;
	buttons = new LaunchpadButton**[length];
	for (int y = 0; y < length; y++) {
		buttons[y] = new LaunchpadButton*[length];
		for (int x = 0; x < length; x++) {
			buttons[x][y] = new LaunchpadButton();
		}
	}
}

LaunchpadManager::LaunchpadManager(int _length, int _firstPin) {
	
}

LaunchpadButton* LaunchpadManager::GetButton(int _x, int _y) {
    return buttons[_x][_y];
}

void LaunchpadManager::Update() {

}

LaunchpadManager::~LaunchpadManager() {
	if (buttons) {
		for (int y = 0; y < length; y++) {
			for (int x = 0; x < length; x++) {
				delete buttons[x][y];
			}
			delete buttons[y];
		}
	}
	delete[] buttons;
}