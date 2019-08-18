#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

//#include "LaunchpadButton.h"
#include "SoundButton.h"
#include "SoundManager.h"
#include "Note.h"
#if !defined (__AVR__) && !defined (__avr__)
#include <fstream>
#include "Console.h"
#include <string>
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
#if !defined (__AVR__) && !defined (__avr__)
		friend class SoundManager;
		Console* console;
		
		Sprite LoadSprite(std::string SpriteAssetFileName);
		EBackColor AtoBackColor(char c);
		Sprite buttonSpriteOff;
		Sprite buttonSpriteOn;

		const int PIXEL_SIZE_X = 16;
		const int PIXEL_SIZE_Y = 5;

		std::string logString[2];
#endif
};

#endif