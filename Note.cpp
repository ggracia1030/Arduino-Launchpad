#include"Note.h"

Note::Note() {
	Note(A, 4);
}

Note::Note(Notes _note, int _octave) {
    SetNote(_note);
    SetOctave(_octave);
}

void Note::SetOctave(int value) {

    if(value < 1) { value = 1; }
    else if(value > 7) { value = 7; }

    octave = value;
    frequency = frequencies[12*(octave-1) + note];
}

void Note::SetNote(Notes _note) {
    note = _note;
}

void Note::SetNote(Notes _note, int octave)
{
	SetNote(_note);
	SetOctave(octave);
}

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
