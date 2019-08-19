#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

#include "SoundManager.h"
#include "InputManager.h"
#include "LCDScreen.h"

#if !defined (__AVR__) && !defined (__avr__)
#include <fstream>
#include "Console.h"
#include <string>
#endif

class LaunchpadManager {

    public:
		LaunchpadManager(int _length, int _firstPin);
        ~LaunchpadManager();
		

        void Update();
		int GetButtonsLength() { return length; };

    private:
		void UpdateInput();
		void Render();

		InputManager* inputManager;
		SoundManager*soundManager;
		LCDScreen* lcdScreen;

        int length;
#if !defined (__AVR__) && !defined (__avr__)
		friend class SoundManager;
		Console* console;
		
		Sprite LoadSprite(std::string SpriteAssetFileName);
		EBackColor AtoBackColor(char c);
		Sprite buttonSpriteOff;
		Sprite buttonSpriteOn;
		Sprite lcdScreenSprite;

		const int PIXEL_SIZE_X = 16;
		const int PIXEL_SIZE_Y = 5;
		const int BUTTONS_MATRIX_OFFSET_X = 3;
		const int BUTTONS_MATRIX_OFFSET_Y = 6;
#endif
};

#endif