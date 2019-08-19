#include "LCDScreen.h"

#if !defined (__AVR__) && !defined (__avr__)
LCDScreen::LCDScreen() : Component::Component()
{
	lcdString[0] = "  ---";
	lcdString[1] = "--------";
}
LCDScreen::LCDScreen(int pin, PinMode _pinMode) : Component::Component(pin, _pinMode)
{
	lcdString[0] = "  ---";
	lcdString[1] = "--------";
}
LCDScreen::~LCDScreen()
{
}
void LCDScreen::SetLCDString(std::string msg, int row)
{
	if (row < 0) row = 0;
	else if (row > 1) row = 1;
	if (msg.size() > 16) {//16 is max value of chars in a row of the LCD screen
		std::string temp = "";
		for (int i = 0; i < 16; i++) {
			temp += msg[i];
		}
		msg = temp;
	}
	lcdString[row] = msg;
}
#else
void LCDScreen::SetLCDString(String msg, int row)
{
	if (row < 0) row = 0;
	else if (row > 1) row = 1;
	if (msg.size() > 16) {//16 is max value of chars in a row of the LCD screen
		String temp = "";
		for (int i = 0; i < 16; i++) {
			temp += msg[i];
		}
		msg = temp;
	}
	lcdString[row] = msg;
}
#endif