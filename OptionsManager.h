#pragma once
#include "SDManager.h"
#include "Note.h"

class OptionsManager
{
public:
	OptionsManager(SDManager* _sd);
	~OptionsManager();

private:
	friend class InputManager;
	friend class LaunchpadManager;

	SDManager* sdManager;
	Note*** notes;
};

