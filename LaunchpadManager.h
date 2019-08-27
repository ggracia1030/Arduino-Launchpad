#ifndef LAUNCHPAD_MANAGER_H
#define LAUNCHPAD_MANAGER_H

#include "SoundManager.h"
#include "InputManager.h"
#include "LCDScreen.h"
#include "OptionsManager.h"

#if !defined (__AVR__) && !defined (__avr__)
#include <fstream>
#include "Console.h"
#include <string>
#endif

class LaunchpadManager {

    public:
		LaunchpadManager(InputManager* _input, SoundManager* _sound, LCDScreen* _lcd);
#if !defined(__AVR__) && !defined (__avr__)
		LaunchpadManager(InputManager* _input, SoundManager* _sound, LCDScreen* _lcd, Console* _console);
#endif
		//LaunchpadManager(int _length, int _firstPin, int _acceptBtnPin, int _cancelBtnPin);
        ~LaunchpadManager();
		

        void Update();

    private:
		void UpdateInput();
#if !defined (__AVR__) && !defined (__avr__)
		void Render();
#endif

		InputManager* inputManager;
		SoundManager*soundManager;
		LCDScreen* lcdScreen;
		OptionsManager* optionsManager;

        //int length;
#if !defined (__AVR__) && !defined (__avr__)
		friend class SoundManager;
		Console* console;
		
		Sprite LoadSprite(std::string SpriteAssetFileName);
		EBackColor AtoBackColor(char c);

		Sprite buttonPushSprite;
		Sprite buttonSoundSprite;
		Sprite buttonCancelSprite, buttonAcceptSprite;
		Sprite lcdScreenSprite;
		Sprite buttonSmall;

		const int PIXEL_SIZE_X = 16;
		const int PIXEL_SIZE_Y = 5;
		const int BUTTONS_MATRIX_OFFSET_X = 3;
		const int BUTTONS_MATRIX_OFFSET_Y = 6;
#endif
};

#endif