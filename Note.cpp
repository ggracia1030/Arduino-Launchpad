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
