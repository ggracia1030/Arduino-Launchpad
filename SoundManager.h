#pragma once
#include "Note.h"

#if !defined (__AVR__) && !defined (__avr__)
#include "Console.h"
#endif

class SoundManager
{
public:
	SoundManager(long _oscillatorFreq, int _channels);
#if !defined (__AVR__) && !defined (__avr__)
	SoundManager(long _oscillatorFreq, int _channels, Console* _console);
#endif
	~SoundManager();

	void PlayNote(int noteFreq);
	void PlayNote(Note* _note);
	const short GetNoteValue(int noteFreq);
	const short GetNoteValue(Note* note);

	const bool isChannelFree(int _channel);
	const int GetFirstFreeChannel();

private:
	bool** channels;
	int channelsLength;

	int volume;
	int release;

	int oscillatorFreq;

	void SendNoteValue(short noteValue);

#if !defined (__AVR__) && !defined (__avr__)
	Console* console;
#endif
};


