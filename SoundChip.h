#pragma once

#if defined (__AVR__) || defined (__avr__)
#include "Arduino.h"
#else
#include "Console.h"
#endif

#define SN76489_PULSE_WE 50

#define SN76489_CMD  0x8
#define SN76489_VOL  0x1
#define SN76489_TONE 0x0
#define SN76489_CHN0 0x0
#define SN76489_CHN1 0x1
#define SN76489_CHN2 0x2
#define SN76489_CHN3 0x3

#define SN76489_NIBBLE_VOL(chan) ((SN76489_CMD | ((chan&0b11)<<1) |SN76489_VOL) << 4)
#define SN76489_NIBBLE_TONE(chan) ((SN76489_CMD | ((chan&0b11)<<1) |SN76489_TONE) << 4)

class SoundChip
{
public:
	SoundChip(int firstDataPin, int WEPin);
	~SoundChip();
	

	void SendNoteValue(uint16_t noteValue, uint8_t channel);
	void SetVolume(uint8_t volume, uint8_t channel);

private:
	const int DATA_PINS_LENGTH = 8;
	int dataPins[8];
	int pinNotWE;

	void SendByte(byte _data);
	void PutByte(byte _data);
};



