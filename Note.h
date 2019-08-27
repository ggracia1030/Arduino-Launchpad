#ifndef NOTE_H
#define NOTE_H

#if !defined (__AVR__) && !defined (__avr__)
#include <iostream>
#include <string>
#else
#include "Arduino.h"
#include <String.h>
#include <WString.h>
#endif



class Note {
	const int MIN_OCTAVE = 3;
	const int MAX_0CTAVE = 7;
    public:

		enum Notes {
			C, CS, D, DS, E, F, FS, G, GS, A, AS, B, Noise
		};

		Notes GuitarTunningNotes[6] = { E, A, D, G, B, E };
		int GuitarTunningOctaves[6] = { 3, 3, 4, 4, 4, 5 };


        int frequencies [91] = {
            33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 0, 
            65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 1,
            131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 2,
            262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 3,
            523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 4, 
            1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 5, 
            2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 6
        };

		Note operator +(int semitones);
		Note operator = (Note other);

        Note();
        Note(Notes _note, int _ocatve);

        void SetOctave(int value);
        void SetNote(Notes _note);
		void SetNote(Notes _note, int octave);
#if defined (__AVR__) || defined (__avr__)
		void SetNote(String _note);
#else
		void SetNote(std::string _note);
#endif

        int GetFrequency() {
            return frequency;
        }
#if !defined (__AVR__) && !defined (__avr__)
		std::string ToString();
#else
		String ToString();
#endif
        
    private:
        Notes note;
        int octave;
        int frequency;
};

#endif