#include "OptionsManager.h"

OptionsManager::OptionsManager(SDManager* _sd, LCDScreen* _lcd)
{
	sdManager = _sd;
	lcdScreen = _lcd;
	notes = _sd->notes;
}
