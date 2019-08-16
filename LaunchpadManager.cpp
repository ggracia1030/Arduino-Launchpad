#include "LaunchpadManager.h"

LaunchpadManager::LaunchpadManager(int btns) {
	length = btns;
    buttons = new LaunchpadButton*[length];
	for (int i = 0; i < length; i++) {
		buttons[i] = new LaunchpadButton();
	}
}

LaunchpadButton* LaunchpadManager::GetButton(int btn) {
    return buttons[btn];
}

void LaunchpadManager::Update() {

}

LaunchpadManager::~LaunchpadManager() {
    if(buttons)
        delete[] buttons;
}