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

SDManager::~SDManager()
{
}
#if defined (__AVR__) || defined (__avr__)
void SDManager::LoadData(String path)
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
			}
		}
		file.close();
	}
}
void SDManager::SaveData(String path)
{
	file = SD.open(path, FILE_WRITE);
	if (file) {
		for (int y = 0; y < notesLength; y++) {
			for (int x = 0; x < notesLength; x++) {
				file.println(notes[x][y]->ToString() + '\n');
			}
		}
		file.close();
	}
}

String SDManager::GetPathToLoad()
{
	String path = "config/";
	String temp = "";
	char currentChar = '0';
	file = SD.open("data.wconf");
	if (file) {
		while (currentChar != '\n') {
			currentChar = (char)(file.read());
			if(currentChar != '\n')
				temp += currentChar;
		}
		path = "config/" + temp + ".wpad";
		file.close();
	}

	return path;
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


std::string SDManager::GetPathToLoad()
{
	std::string path = "config/";
	std::string temp;
	
	file.open("data.wconf", std::ios::in);

	if (file.is_open()) {
		std::getline(file, temp);
		path = "config/" + temp + ".wpad";
	}
	file.close();
	return path;
}
#endif