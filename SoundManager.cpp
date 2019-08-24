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
#endif
SoundManager::~SoundManager()
{
	if (channels != nullptr) {
		delete[] channels;
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

	SendNoteValue(GetNoteValue(noteFreq), channel);
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
	std::cout << "Byte: " << 0b10000000 << std::endl;
	SendNoteValue(GetNoteValue(_note), channel);
}

void SoundManager::StopChannel(int channel)
{
	//Send byte to put the volume of the channel to 0
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

void SoundManager::SendNoteValue(uint16_t noteValue, uint8_t volume, uint8_t channel)
{
	SendByte(SN76489_NIBBLE_TONE(channel) | noteValue & 0b1111);
	if (noteValue > 0b1111) {
		SendByte((noteValue >> 4));
	}
	SendByte(SN76489_NIBBLE_VOL(channel) | volume);
}

void SoundManager::SendByte(byte _byte)
{
}
