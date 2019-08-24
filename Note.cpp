#include"Note.h"

Note Note::operator+(int semitones)
{
	Note temp = *this;

	if (temp.note + semitones > B) {
		temp.octave++;
	}
	temp.note = (Notes)((temp.note + semitones) % 12);
	

	return temp;
}

Note Note::operator=(Note other)
{
	this->SetNote(other.note, other.octave);
	return *this;
}

Note::Note() {
	Note(A, 4);
}

Note::Note(Notes _note, int _octave) {
    SetNote(_note);
    SetOctave(_octave);
}

void Note::SetOctave(int value) {

    if(value <	MIN_OCTAVE) { value = MIN_OCTAVE; }
    else if(value > 7) { value = 7; }

    octave = value;
    frequency = frequencies[12*(octave-1) + note];
}

void Note::SetNote(Notes _note) {
    note = _note;
}

void Note::SetNote(Notes _note, int octave)
{
	note = _note;
	SetOctave(octave);
}
#if !defined (__AVR__) && !defined (__avr__)
std::string Note::ToString()
{
	std::string temp = "";
	switch (note) {
	case C:
		temp = "C";
		break;
	case CS: 
		temp = "C#";
		break;
	case D:
		temp = "D";
		break;
	case DS:
		temp = "D#";
		break;
	case E:
		temp = "E";
		break;
	case F:
		temp = "F";
		break;
	case FS:
		temp = "F#";
		break;
	case G:
		temp = "G";
		break;
	case GS:
		temp = "G#";
		break;
	case A:
		temp = "A";
		break;
	case AS:
		temp = "A#";
		break;
	case B:
		temp = "B";
		break;
	}

	temp += std::to_string(octave);
	return temp;
}
#else 
String Note::ToString()
{
	String temp = "";
	switch (note) {
	case C:
		temp = "C";
		break;
	case CS:
		temp = "C#";
		break;
	case D:
		temp = "D";
		break;
	case DS:
		temp = "D#";
		break;
	case E:
		temp = "E";
		break;
	case F:
		temp = "F";
		break;
	case FS:
		temp = "F#";
		break;
	case G:
		temp = "G";
		break;
	case GS:
		temp = "G#";
		break;
	case A:
		temp = "A";
		break;
	case AS:
		temp = "A#";
		break;
	case B:
		temp = "B";
		break;
	}

	temp += String(octave);
	return temp;
}
#endif
