#include "SoundManager.h"
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

SoundManager::~SoundManager()
{
}

void SoundManager::SendNoteValue(short noteValue)
{
#if defined (__AVR__) || (__avr__)
	//Lo que tenga que hacer con el chip
#else
	//std::cout << " | Note Value: " << noteValue << std::endl;
#endif
}

void SoundManager::PlayNote(int noteFreq)
{
#if !defined (__AVR__) && !defined (__avr__)
	//std::cout << "Playing Note with freq: " << noteFreq << std::endl;
	Beep(noteFreq, 100);
#endif 

	SendNoteValue(GetNoteValue(noteFreq));
}

void SoundManager::PlayNote(Note* _note)
{
#if !defined (__AVR__) && !defined (__avr__)
	//std::cout << "Playing Note with freq: " << _note->GetFrequency() << std::endl;
	Beep(_note->GetFrequency(), 100);
#endif 
	SendNoteValue(GetNoteValue(_note));
}

const short SoundManager::GetNoteValue(int noteFreq)
{
	return (short)((float)oscillatorFreq / (float)(2 * 16 * noteFreq));
}

const short SoundManager::GetNoteValue(Note* note)
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
