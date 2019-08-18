#pragma once
#include "Note.h"
class SoundManager
{
public:
	SoundManager(long _oscillatorFreq, int _channels);
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
};

