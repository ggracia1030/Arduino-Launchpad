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
class DataManager
{
public:
	DataManager(int csPin, int _length);
	~DataManager();

#if defined (__AVR__) || defined (__avr__)
	void LoadData(String path);
	void SaveData(String path);
	String GetPathToLoad();
	void SavePresetName(String name);
#else
	void LoadData(std::string path);
	void SaveData(std::string path);
	std::string GetPathToLoad();
	void SavePresetName(std::string name);
#endif

	void LoadPresetsNames();
	void SavePresetNames();

private:
	friend class OptionsManager;

	Note*** notes;
	int notesLength;
#if defined (__AVR__) || defined (__avr__)
	File file;
	String presetNames[16];
	String currentPreset;
#else
	std::fstream file;
	std::string presetNames[16];
	std::string currentPreset;
#endif
};

