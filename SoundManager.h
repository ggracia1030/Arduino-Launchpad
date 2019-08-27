#pragma once

#include "SoundChip.h"
#include "Note.h"
#if !defined (__AVR__) && !defined (__avr__)
#include "Console.h"
#include <string>
#endif


const int MIN_VOLUME = 0;
const int MAX_VOLUME = 15;

class SoundManager
{
	
public:
	
	SoundManager(long _oscillatorFreq, int _channels, SoundChip* _soundChip);
#if !defined (__AVR__) && !defined (__avr__)
	SoundManager(long _oscillatorFreq, int _channels, SoundChip* _soundChip, Console* _console);
#endif
	~SoundManager();
	void PlayNote(int noteFreq);
	void PlayNote(int noteFreq, int channel);
	void PlayNote(Note* _note, int channel);
	void PlayNote(Note* note);
	void PlayNoise(int noise);

	void SetVolume(uint8_t volume, uint8_t channel);

	void StopChannel(int channel);
	void StopAllChannels();

	void MuteChannel(int channel);
	void MuteAllChannels();

	const uint16_t GetNoteValue(int noteFreq);
	const uint16_t GetNoteValue(Note* note);

	const bool isChannelFree(int _channel);
	const int GetFirstFreeChannel();



private:
	SoundChip* soundChip;
	
	bool** channels;
	int channelsLength;

	int generalVolume;
	int channelVolume[4];
	int release;

	int oscillatorFreq;

#if !defined (__AVR__) && !defined (__avr__)
	Console* console;
#endif
};


