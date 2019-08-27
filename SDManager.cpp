#include "SDManager.h"

SDManager::SDManager(int csPin, int _length)
{
	notesLength = _length;

	notes = new Note **[_length];
	for (int i = 0; i < _length; i++) {
		notes[i] = new Note * [_length];
	}

	for (int y = 0; y < _length; y++) {
		for (int x = 0; x < _length; x++) {
			notes[x][y] = new Note();
		}
	}

	LoadData("Guitar.wpad");

#if defined (__AVR__) || defined (__avr__)
	SD.begin(csPin);
#endif
}

SDManager::~SDManager()
{
}
#if defined (__AVR__) || defined (__avr__)
void SDManager::LoadData(String path)
{
	file = SD.open(path);
	if (file) {


		file.close();
	}
	else {
		Serial.begin("File: '" + path + "' not found.")
	}
}
#else
void SDManager::LoadData(std::string path)
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
void SDManager::SaveData(std::string path)
{
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
#endif