#pragma once
#include "Note.h"

#if !defined (__AVR__) && !defined (__avr__)
#include "Console.h"
#include <string>
#endif

#define	DATA			0b00111111	//0 0 dddddd	-->	 0 | 0			| DATA
#define LATCH			0b11111111	//1 CC T DDDD	-->  1 | CHANNEL	| TYPE	| DATA

#define BYTE_CHANNEL	0b01100000
#define BYTE_TYPE		0b00010000
#define BYTE_DATA		0b00001111

#define SN76489_CMD  0x8
#define SN76489_VOL  0x1
#define SN76489_TONE 0x0
#define SN76489_CHN0 0x0
#define SN76489_CHN1 0x1
#define SN76489_CHN2 0x2
#define SN76489_CHN3 0x3

#define SN76489_NIBBLE_VOL(chan) ((SN76489_CMD | ((chan&0b11)<<1) |SN76489_VOL) << 4)
#define SN76489_NIBBLE_TONE(chan) ((SN76489_CMD | ((chan&0b11)<<1) |SN76489_TONE) << 4)


class SoundManager
{
	
public:
	
	SoundManager(long _oscillatorFreq, int _channels);
#if !defined (__AVR__) && !defined (__avr__)
	SoundManager(long _oscillatorFreq, int _channels, Console* _console);
#endif
	~SoundManager();

	void PlayNote(int noteFreq, int channel);
	void PlayNote(Note* _note, int channel);
	void StopChannel(int channel);
	const uint16_t GetNoteValue(int noteFreq);
	const uint16_t GetNoteValue(Note* note);

	const bool isChannelFree(int _channel);
	const int GetFirstFreeChannel();



private:
	bool** channels;
	int channelsLength;

	int volume;
	int release;

	int oscillatorFreq;

	void SendNoteValue(uint16_t noteValue, uint8_t volume, uint8_t channel);
	void SendByte(byte _byte);

#if !defined (__AVR__) && !defined (__avr__)
	Console* console;
#endif
};


