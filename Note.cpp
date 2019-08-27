#include"Note.h"

Note Note::operator+(int semitones)
{
	Note temp = *this;

	if (temp.note + semitones > B) {
		temp.octave += (semitones / 12) + 1;
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
	if (note == Noise) {
		octave = value;
		frequency = frequencies[13 * octave + note];
		return;
	}

    if(value <	MIN_OCTAVE) { value = MIN_OCTAVE; }
    else if(value > 7) { value = 7; }

    octave = value;
    frequency = frequencies[13*(octave-1) + note];
}

void Note::SetNote(Notes _note) {
    note = _note;
}

void Note::SetNote(Notes _note, int octave)
{
	note = _note;
	SetOctave(octave);
}

Note::Notes CharToNotes(char c) {
	Note::Notes temp = Note::C;
	switch (c) {
	case 'C':
		temp = Note::C;
		break;
	case 'D':
		temp = Note::D;
		break;
	case 'E':
		temp = Note::E;
		break;
	case 'F':
		temp = Note::F;
		break;
	case 'G':
		temp = Note::G;
		break;
	case 'A':
		temp = Note::A;
		break;
	case 'B':
		temp = Note::B;
		break;
	}
	return temp;
}

#if defined (__AVR__) || defined (__avr__)
void Note::SetNote(String _note)
{
	Notes tempNote = CharToNotes(_note.charAt(0));
	int tempOctave;

	if (_note.length() > 3) {
		tempNote = Noise;
		tempOctave = _note.charAt(_note.length() - 1) - '0';
	}
	else {

		if (_note.charAt(1) >= '0' && _note.charAt(1) <= '9') {
			tempOctave = _note.charAt(1) - '0';
		}
		else {
			tempNote = (Notes)(tempNote + 1);
			tempOctave = _note.charAt(2) - '0';
		}
	}
	SetNote(tempNote, tempOctave);
}
#else
void Note::SetNote(std::string _note)
{
	Notes tempNote = CharToNotes(_note[0]);
	int tempOctave;

	if (_note.size() > 3) {
		tempNote = Noise;
		tempOctave = _note.at(_note.size() - 1) - '0';
	}
	else {

		if (_note.at(1) >= '0' && _note.at(1) <= '9') {
			tempOctave = _note.at(1) - '0';
		}
		else {
			tempNote = (Notes)(tempNote + 1);
			tempOctave = _note.at(2) - '0';
		}
	}
	SetNote(tempNote, tempOctave);
}
#endif
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
	case Noise:
		temp = "Noise";
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
	case Noise:
		temp = "Noise";
		break;
	}

	temp += String(octave);
	return temp;
}
#endif
