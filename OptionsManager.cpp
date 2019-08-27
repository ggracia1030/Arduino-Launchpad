#include "OptionsManager.h"

OptionsManager::OptionsManager(SDManager* _sd)
{
	sdManager = _sd;
	notes = _sd->notes;
}
