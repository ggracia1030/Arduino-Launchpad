#include "SoundButton.h"

SoundButton::SoundButton(SoundManager* _soundManager, int _xPin, int _yPin, char _keyboard) : LaunchpadButton(_keyboard) {
	componentName = "Sound Button";
	soundManager = _soundManager;
	xPin = _xPin;
	yPin = _yPin;

#if defined (__AVR__) || defined (__avr__)
	pinMode(_xPin, INPUT);
	pinMode(_yPin, OUTPUT);
#endif

	sound = new Note();
}

SoundButton::SoundButton(SoundManager* _soundManager, Note::Notes _note, int octave, char _keyboard) : LaunchpadButton(_keyboard) {
	componentName = "Sound Button";
	soundManager = _soundManager;
	sound = new Note(_note, octave);
}

SoundButton::~SoundButton()
{
	if (sound != nullptr)
		delete sound;
}

void SoundButton::Action() {
	soundManager->PlayNote(sound);
}

bool SoundButton::isButtonPressed()
{
#if defined (__AVR__) || (__avr__)
	//DigitalWrite(yPin, true);
	bool value = digitalRead(xPin) == HIGH && digitalRead(yPin) == HIGH;
	if (value) {
		String tempString = "Button Pressed | " + sound->ToString(); +" | Pin X = " + (String)xPin + " | Pin Y = " + (String)yPin;
		Serial.println(tempString);
	}
	//DigitalWrite(yPin, false);
	return value;
#else
	return LaunchpadButton::isButtonPressed();
#endif
}

