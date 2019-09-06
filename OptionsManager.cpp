#include "OptionsManager.h"

OptionsManager::OptionsManager(DataManager* _sd, LCDScreen* _lcd, SoundManager* _sound)
{
	dataManager = _sd;
	lcdScreen = _lcd;
	notes = _sd->notes;
	soundManager = _sound;
}
OptionsManager::~OptionsManager()
{
}
#if defined (__AVR__) || defined (__avr__)
void OptionsManager::ChangePreset(String name)
{
	//Do Something
	dataManager->SavePresetName(name);
}
#else
void OptionsManager::ChangePreset(std::string name)
{
	//Do something
	dataManager->SavePresetName(name);
}
#endif