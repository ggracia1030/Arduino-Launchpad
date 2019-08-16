#include"BuzzerNotes.h"

BuzzerNotes::BuzzerNotes() {
    BuzzerNotes(A, 4);
}

BuzzerNotes::BuzzerNotes(Notes _note, int _octave) {
    SetNote(_note);
    SetOctave(_octave);
}

void BuzzerNotes::SetOctave(int value) {

    if(value < 1) { value = 1; }
    else if(value > 7) { value = 7; }

    octave = value;
    frequency = frequencies[12*(octave-1) + note];
}

void BuzzerNotes::SetNote(Notes _note) {
    note = _note;
}

void BuzzerNotes::SetNote(Notes _note, int octave)
{
	SetNote(_note);
	SetOctave(octave);
}
