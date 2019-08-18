#include "SoundButton.h"

SoundButton::SoundButton(SoundManager* _soundManager, int _xPin, int _yPin, char _keyboard) : LaunchpadButton(_keyboard) {
	componentName = "Sound Button";
	soundManager = _soundManager;
	xPin = _xPin;
	yPin = _yPin;
	sound = new Note();
}

SoundButton::SoundButton(SoundManager* _soundManager, Note::Notes _note, int octave, char _keyboard) : LaunchpadButton(_keyboard) {
	componentName = "Sound Button";
	soundManager = _soundManager;
	sound = new Note(_note, octave);
}

void SoundButton::Action() {
	soundManager->PlayNote(sound);
}

bool SoundButton::isButtonPressed()
{
#if defined (__AVR__) || (__avr__)
	return DigitalRead(xPin) && DigitalRead(yPin);
#else
	return LaunchpadButton::isButtonPressed();
#endif
}

