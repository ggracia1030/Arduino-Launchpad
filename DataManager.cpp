#include "DataManager.h"

DataManager::DataManager(int csPin, int _length)
{
	notesLength = _length;

	notes = new Note *[_length];
	for (int i = 0; i < _length; i++) {
		notes[i] = new Note();
	}

	for (int i = 0; i < _length; i++) {
		notes[i]->SetNote(Note::Notes(Note::D + i), 3 + i >= 12);
	}

	LoadData(GetPathToLoad());

#if defined (__AVR__) || defined (__avr__)
	SD.begin(csPin);
#endif
}

DataManager::~DataManager()
{
}
#if defined (__AVR__) || defined (__avr__)
void DataManager::LoadData(String path)
{
	file = SD.open(path);
	String temp = "";
	char currentChar = '0';
	if (file) {
		for (int i = 0; y < notesLength; i++) {
			while (currentChar != '\n') {
				currentChar = (char)(file.read());
				if (currentChar != '\n')
					temp += currentChar;
			}
			notes[i]->SetNote(temp);
			temp = "";
		}
		file.close();
	}
}
void DataManager::SaveData(String path)
{
	SavePresetName(currentPreset);
	file = SD.open(path, FILE_WRITE);
	if (file) {
		for (int i = 0; i < notesLength; i++) {
			file.println(notes[i]->ToString());
		}
		file.close();
	}
}

String DataManager::GetPathToLoad()
{
	String path = "data/config/";
	String temp = "";
	char currentChar = '0';
	file = SD.open("data/data.wconf");
	if (file) {
		while (currentChar != '\n') {
			currentChar = (char)(file.read());
			if(currentChar != '\n')
				temp += currentChar;
		}
		path = "data/config/" + temp + ".wpad";
		temp = "";
		file.close();
	}

	return path;
}

void DataManager::SavePresetName(String name)
{
	SavePresetNames();
	file = SD.open(name, FILE_WRITE);
	if (file) {
		file.println(name);
		file.println("***************");
		file.close();
	}
}

#else
void DataManager::LoadData(std::string path)
{
	file.open(path, std::ios::in);
	std::string temp = "";
	if (file.is_open()) {
		for (int i = 0; i < notesLength; i++) {
			std::getline(file, temp);
			notes[i]->SetNote(temp);
		}
		file.close();
	}
	else {
		std::cout << "File: '" + path + "' not found" << std::endl;
	}
}
void DataManager::SaveData(std::string path)
{
	SavePresetName(currentPreset);
	file.open(path, std::ios::out | std::ios::trunc); 
	if (file.is_open()) {
		for (int i = 0; i < notesLength; i++) {
			file << notes[i]->ToString() + '\n';
		}
		std::cout << "Data saved!" << std::endl;
		file.close();
	}
}


std::string DataManager::GetPathToLoad()
{
	std::string path = "data/config/";
	std::string temp;
	
	file.open("data/data.wconf", std::ios::in);

	if (file.is_open()) {
		std::getline(file, temp);
		path = "data/config/" + temp + ".wpad";
		file.close();
	}
	return path;
}

void DataManager::SavePresetName(std::string name)
{
	SavePresetNames();

	file.open("data/data.wconf", std::ios::out | std::ios::trunc);

	if (file.is_open()) {
		file << name + "\n***************";
		file.close();
	}
}

void DataManager::LoadPresetsNames()
{
#if defined (__AVR__) || defined (__avr__)
	file = SD.open("data/list.wconf");
	String temp = "";
	char currentChar = '0';
	if (file) {
		for (int i = 0; i < 16; i++) {
			while (currentChar != '\n') {
				currentChar = (char)(file.read());
				if (currentChar != '\n')
					temp += currentChar;
			}
			presetNames[i] = temp;
			temp = "";
		}
		file.close();
	}
#else
	file.open("data/list.wconf", std::ios::in);
	if (file.is_open()) {
		for (int i = 0; i < 16; i++) {
			std::getline(file, presetNames[i]);
		}
		file.close();
	}
#endif
}
void DataManager::SavePresetNames()
{
#if defined (__AVR__) || defined (__avr__)
	file = SD.open("data/list.wconf", FILE_WRITE);
	if (file) {
		for (int i = 0; i < 16; i++) {
			file.println(presetNames[i]);
		}
		file.close();
	}
#else
	file.open("data/list.wconf", std::ios::out | std::ios::trunc);
	if (file.is_open()) {
		for (int i = 0; i < 16; i++) {
			file << presetNames[i];
		}
		file.close();
	}
#endif
}
#endif