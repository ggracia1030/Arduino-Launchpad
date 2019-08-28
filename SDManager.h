#pragma once
#include "Note.h"
#if defined (__AVR__) || defined (__avr__)
#include "Arduino.h"
#include "SD.h"
#else
#include <string>
#include <iostream>
#include <fstream>
#endif
class SDManager
{
public:
	SDManager(int csPin, int _length);
	~SDManager();

#if defined (__AVR__) || defined (__avr__)
	void LoadData(String path);
	void SaveData(String path);
	String GetPathToLoad();
#else
	void LoadData(std::string path);
	void SaveData(std::string path);
	std::string GetPathToLoad();
#endif

private:
	friend class OptionsManager;

	Note*** notes;
	int notesLength;
#if defined (__AVR__) || defined (__avr__)
	File file;
#else
	std::fstream file;
#endif
};

