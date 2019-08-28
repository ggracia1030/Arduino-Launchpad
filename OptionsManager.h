#pragma once
#include "SDManager.h"
#include "Note.h"
#include "LCDScreen.h"

class OptionsManager
{
public:
	OptionsManager(SDManager* _sd, LCDScreen* _lcd);
	~OptionsManager();

private:
	friend class InputManager;
	friend class LaunchpadManager;

	SDManager* sdManager;
	Note*** notes;
	LCDScreen* lcdScreen;
};

