#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

#include "LaunchpadButton.h"
#include "BuzzerNotes.h"

class LaunchpadManager {

    public:
        LaunchpadManager(int _length);
		LaunchpadManager(int _length, int _firstPin);
        ~LaunchpadManager();

        void Update();
        int GetButtonsLength() { return length; }
        LaunchpadButton* GetButton(int _x, int _y);
    
    private:
		LaunchpadButton*** buttons;
		int** xPins;
		int** yPins;
        int length;
};

#endif