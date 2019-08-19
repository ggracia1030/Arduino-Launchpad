#include "SoundManager.h"
#include "LaunchpadManager.h"
#if !defined (__AVR__) && !defined (__avr__)
#include <iostream>
#include <Windows.h>
#endif

SoundManager::SoundManager(long _oscillatorFreq, int _channels)
{
	oscillatorFreq = _oscillatorFreq;
	channelsLength = _channels;
	channels = new bool* [channelsLength];
	for (int i = 0; i < channelsLength; i++) {
		channels[i] = new bool;
		*(channels[i]) = true;
	}
	volume = 0;
	release = 0;
	
}
#if !defined (__AVR__) && !defined (__avr__)
SoundManager::SoundManager(long _oscillatorFreq, int _channels, Console* _console)
{
	oscillatorFreq = _oscillatorFreq;
	channelsLength = _channels;
	channels = new bool* [channelsLength];
	for (int i = 0; i < channelsLength; i++) {
		channels[i] = new bool;
		*(channels[i]) = true;
	}
	volume = 0;
	release = 0;

	console = _console;
}
#else
void SoundManager::SetLCDText(String msg, int row)
{
	manager->SetLCDString(msg, row);
}
#endif
SoundManager::~SoundManager()
{
	if (channels != nullptr) {
		delete[] channels;
	}
}

void SoundManager::SendNoteValue(uint16_t noteValue)
{
#if defined (__AVR__) || (__avr__)
	//Lo que tenga que hacer con el chip
#else
	
#endif
}

void SoundManager::PlayNote(int noteFreq)
{
#if !defined (__AVR__) && !defined (__avr__)
	Beep(noteFreq, 100);
#endif 

	SendNoteValue(GetNoteValue(noteFreq));
}

void SoundManager::PlayNote(Note* _note)
{
#if !defined (__AVR__) && !defined (__avr__)
	Beep(_note->GetFrequency(), 100);
#endif 
	SendNoteValue(GetNoteValue(_note));
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
