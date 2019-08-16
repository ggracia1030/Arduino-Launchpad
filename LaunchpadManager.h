#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

#include "LaunchpadButton.h"
#include "BuzzerNotes.h"

class LaunchpadManager {

    public:
        LaunchpadManager(int btns);
        ~LaunchpadManager();

        void Update();
        int GetButtonsLength() { return length; }
        LaunchpadButton* GetButton(int btn);
    
    private:
		LaunchpadButton** buttons;
        int length;
};

#endif