#include "SoundButton.h"

SoundButton::SoundButton(SoundManager* _soundManager, int _xPin, int _yPin, int _soundChannel, char _keyboard) : LaunchpadButton(_keyboard) {
	componentName = "Sound Button";
	soundManager = _soundManager;
	xPin = _xPin;
	yPin = _yPin;
	soundChannel = _soundChannel;

#if defined (__AVR__) || defined (__avr__)
	pinMode(_xPin, INPUT);
	pinMode(_yPin, OUTPUT);
#endif

	sound = new Note();
}

SoundButton::~SoundButton()
{
	if (sound != nullptr)
		delete sound;
}

void SoundButton::OnButtonDown() {
	soundManager->PlayNote(sound, soundChannel);
}
void SoundButton::OnButtonUp() {
	soundManager->StopChannel(soundChannel);
}

bool SoundButton::isButtonPressed()
{
#if defined (__AVR__) || (__avr__)
	bool value = digitalRead(xPin) == HIGH;
	if (value) {
		String tempString = "Button Pressed | " + sound->ToString(); +" | Pin X = " + (String)xPin + " | Pin Y = " + (String)yPin;
		Serial.println(tempString);
	}
	return value;
#else
	return LaunchpadButton::isButtonPressed();
#endif
}

