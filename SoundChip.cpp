#include "SoundChip.h"

SoundChip::SoundChip(int firstDataPin, int WEPin)
{
	pinNotWE = WEPin;
#if defined (__AVR__) || defined (__avr__)
	pinMode(pinNotWE, OUTPUT);
#endif

	for (int i = 0; i < DATA_PINS_LENGTH; i++) {
		dataPins[i] = firstDataPin + i;
#if defined (__AVR__) || defined (__avr__)
		pinMode(dataPins[i], OUTPUT);
#endif
	}
}

SoundChip::~SoundChip()
{
}

void SoundChip::SendByte(byte _data)
{
#if defined (__AVR__) || defined (__avr__)
	Serial.println("Sound");
	digitalWrite(pinNotWE, HIGH);
	PutByte(_data);
	digitalWrite(pinNotWE, LOW);
	delayMicroseconds(SN76489_PULSE_WE);
	digitalWrite(pinNotWE, HIGH);
#endif
}

void SoundChip::PutByte(byte _data) {
#if defined (__AVR__) || defined (__avr__)
	digitalWrite(pinNotWE, HIGH);
	digitalWrite(dataPins[0], (_data & 1) ? HIGH : LOW);
	digitalWrite(dataPins[1], (_data & 2) ? HIGH : LOW);
	digitalWrite(dataPins[2], (_data & 4) ? HIGH : LOW);
	digitalWrite(dataPins[3], (_data & 8) ? HIGH : LOW);
	digitalWrite(dataPins[4], (_data & 16) ? HIGH : LOW);
	digitalWrite(dataPins[5], (_data & 32) ? HIGH : LOW);
	digitalWrite(dataPins[6], (_data & 64) ? HIGH : LOW);
	digitalWrite(dataPins[7], (_data & 128) ? HIGH : LOW);

	digitalWrite(pinNotWE, HIGH);
	digitalWrite(pinNotWE, LOW);
	delay(1);
	digitalWrite(pinNotWE, HIGH);
#endif
	
}

void SoundChip::SendNoteValue(uint16_t noteValue, uint8_t channel)
{
	SendByte(SN76489_NIBBLE_TONE(channel) | (noteValue & 0b1111));
	if (noteValue > 0b1111) {
		SendByte((noteValue >> 4));
	}
}

void SoundChip::SetVolume(uint8_t volume, uint8_t channel)
{
	SendByte(SN76489_NIBBLE_VOL(channel) | (volume & 0b1111));
}
