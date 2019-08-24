#include "SoundManager.h"
#include "LaunchpadManager.h"
#if !defined (__AVR__) && !defined (__avr__)
#include <iostream>
#include <Windows.h>
#endif

SoundManager::SoundManager(long _oscillatorFreq, int _channels, SoundChip* _soundChip)
{
	oscillatorFreq = _oscillatorFreq;
	channelsLength = _channels;
	channels = new bool* [channelsLength];
	for (int i = 0; i < channelsLength; i++) {
		channels[i] = new bool;
		*(channels[i]) = true;
	}

	generalVolume = MAX_VOLUME;

	for (int i = 0; i < 4; i++) {
		channelVolume[i] = MAX_VOLUME;
	}
	release = 0;
	soundChip = _soundChip;
	
}
#if !defined (__AVR__) && !defined (__avr__)
SoundManager::SoundManager(long _oscillatorFreq, int _channels, SoundChip* _soundChip, Console* _console)
{
	oscillatorFreq = _oscillatorFreq;
	channelsLength = _channels;
	channels = new bool* [channelsLength];
	for (int i = 0; i < channelsLength; i++) {
		channels[i] = new bool;
		*(channels[i]) = true;
	}

	generalVolume = MAX_VOLUME;

	for (int i = 0; i < 4; i++) {
		channelVolume[i] = MAX_VOLUME;
	}

	generalVolume = MAX_VOLUME;
	release = 0;

	console = _console;
	soundChip = _soundChip;
}
#endif
SoundManager::~SoundManager()
{
	if (channels != nullptr) {
		delete[] channels;
	}
	if (soundChip != nullptr) {
		delete soundChip;
	}
}

void SoundManager::PlayNote(int noteFreq, int channel)
{
#if !defined (__AVR__) && !defined (__avr__)
	Beep(noteFreq, 100);
#elif defined BUZZER_TEST
	tone(7, noteFreq);
	Serial.println("Sound");
#endif 
	soundChip->SendNoteValue(GetNoteValue(noteFreq), channel);
}

void SoundManager::PlayNote(Note* _note, int channel)
{
#if !defined (__AVR__) && !defined (__avr__)
	Beep(_note->GetFrequency(), 100);
#endif
//#if defined (BUZZER_TEST)
	/*Serial.println("Sound");
	tone(7, _note->GetFrequency());*/
	
//#endif 

	soundChip->SendNoteValue(GetNoteValue(_note), channel);
}

void SoundManager::SetVolume(uint8_t volume, uint8_t channel)
{
	channelVolume[channel] = volume;
	volume = MAX_VOLUME - volume;
	soundChip->SetVolume(volume, channel);
}

void SoundManager::StopChannel(int channel)
{
	soundChip->SetVolume(15, channel);
}

void SoundManager::StopAllChannels()
{
	for (int i = 0; i < channelsLength; i++) {
		StopChannel(i);
	}
}

void SoundManager::MuteChannel(int channel)
{
	SetVolume(0, channel);
}

void SoundManager::MuteAllChannels()
{
	for (int i = 0; i < channelsLength; i++) {
		MuteChannel(i);
	}
}

const uint16_t SoundManager::GetNoteValue(int noteFreq)
{
	return (uint16_t)((float)oscillatorFreq / (float)(2 * 16 * noteFreq));
}

const uint16_t SoundManager::GetNoteValue(Note* note)
{
	return GetNoteValue(note->GetFrequency());
}

const bool SoundManager::isChannelFree(int _channel)
{
	if (_channel >= 0 && _channel < channelsLength)
		return *(channels[_channel]);
	else return false;
}

const int SoundManager::GetFirstFreeChannel()
{
	for (int i = 0; i < channelsLength; i++) {
		if (*(channels[i])) return i;
	}
	return 0;
}


