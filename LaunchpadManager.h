#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

//#include "LaunchpadButton.h"
#include "SoundButton.h"
#include "SoundManager.h"
#include "Note.h"

class LaunchpadManager {

    public:

		enum KeyboardButtons {  
			One, Two, Three, Four,
			Q, W, E, R,
			A, S, D, F,
			Z, X, C, V
		};

        LaunchpadManager(int _length);
		LaunchpadManager(int _length, int _firstPin);
        ~LaunchpadManager();
		const char KeyboardBtnToChar(KeyboardButtons btn);

        void Update();
        int GetButtonsLength() { return length; }
        LaunchpadButton* GetButton(int _x, int _y);
    
    private:
		void UpdateInput();
		SoundButton*** soundButtons;
		SoundManager* soundManager;
        int length;
};

#endif