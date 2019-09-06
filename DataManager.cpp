#include "DataManager.h"

DataManager::DataManager(int csPin, int _length)
{
	notesLength = _length;

	notes = new Note **[_length];
	for (int i = 0; i < _length; i++) {
		notes[i] = new Note * [_length];
	}

	for (int y = 0; y < _length; y++) {
		for (int x = 0; x < _length; x++) {
			notes[x][y] = new Note();

			if (x == _length - 1) {
				notes[x][y]->SetNote(Note::Noise, y);
			}
			else {
				//soundButtons[x][y]->GetSound()->SetNote((Note::Notes)((x + _soundButtonsLength * y) % 12), (x + _soundButtonsLength * y) / 12 + 1);
				notes[x][y]->SetNote((Note::Notes)(notes[x][y]->GuitarTunningNotes[x]), notes[x][y]->GuitarTunningOctaves[x]);
				*(notes[x][y]) = *(notes[x][y]) + y;
			}
		}
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
		for (int y = 0; y < notesLength; y++) {
			for (int x = 0; x < notesLength; x++) {
				while (currentChar != '\n') {
					currentChar = (char)(file.read());
					if (currentChar != '\n')
						temp += currentChar;
				}
				notes[x][y]->SetNote(temp);
				temp = "";
			}
		}
		file.close();
	}
}
void DataManager::SaveData(String path)
{
	SavePresetName(currentPreset);
	file = SD.open(path, FILE_WRITE);
	if (file) {
		for (int y = 0; y < notesLength; y++) {
			for (int x = 0; x < notesLength; x++) {
				file.println(notes[x][y]->ToString());
			}
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
		for (int y = 0; y < notesLength; y++) {
			for (int x = 0; x < notesLength; x++) {
				std::getline(file, temp);
				notes[x][y]->SetNote(temp);
			}
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
		for (int y = 0; y < notesLength; y++) {
			for (int x = 0; x < notesLength; x++) {
				file << notes[x][y]->ToString() + '\n';
			}
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