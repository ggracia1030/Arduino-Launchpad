#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

//#include "LaunchpadButton.h"
#include "SoundButton.h"
#include "SoundManager.h"
#include "Note.h"
#ifndef __AVR__ && __avr__
#include <fstream>
#include "Console.h"
#endif

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
		void Render();
		SoundButton*** soundButtons;
		SoundManager* soundManager;
        int length;
#ifndef __AVR__ && __avr__
		Console* console;
		Sprite LoadSprite(std::string SpriteAssetFileName);
		EBackColor AtoBackColor(char c);
		Sprite buttonSpriteOff;
		Sprite buttonSpriteOn;

		const int PIXEL_SIZE_X = 16;
		const int PIXEL_SIZE_Y = 4;
#endif
};

#endif