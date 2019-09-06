#pragma once
#include "DataManager.h"
#include "Note.h"
#include "LCDScreen.h"
#include "SoundManager.h"

#if defined (__AVR__) || defined (__avr__)
#include "Arduino.h"
#else
#include <string>
#endif

class OptionsManager
{
public:
	OptionsManager(DataManager* _sd, LCDScreen* _lcd, SoundManager* _sound);
	~OptionsManager();
#if defined (__AVR__) || defined (__avr__)
	void ChangePreset(String name);
#else
	void ChangePreset(std::string name);
#endif

private:
	friend class InputManager;
	friend class LaunchpadManager;

	DataManager* dataManager;
	Note*** notes;
	LCDScreen* lcdScreen;
	SoundManager* soundManager;
};

