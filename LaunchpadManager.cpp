#include "LaunchpadManager.h"

const char LaunchpadManager::KeyboardBtnToChar(KeyboardButtons btn) {
	char temp = ' ';
	switch (btn) {
	case One:
		temp = '1';
		break;
	case Two:
		temp = '2';
		break;
	case Three:
		temp = '3';
		break;
	case Four:
		temp = '4';
		break;

	case Q:
		temp = 'Q';
		break;
	case W:
		temp = 'W';
		break;
	case E:
		temp = 'E';
		break;
	case R:
		temp = 'R';
		break;

	case A:
		temp = 'A';
		break;
	case S:
		temp = 'S';
		break;
	case D:
		temp = 'D';
		break;
	case F:
		temp = 'F';
		break;

	case Z:
		temp = 'Z';
		break;
	case X:
		temp = 'X';
		break;
	case C:
		temp = 'C';
		break;
	case V:
		temp = 'V';
		break;
	}

	return temp;
}

LaunchpadManager::LaunchpadManager(int _length) {
	length = _length;
	soundManager = new SoundManager(4000000, 3);
	soundButtons = new SoundButton**[length];
#if !defined (__AVR__) && !defined (__avr__)
	console = new Console();
	buttonSpriteOff = LoadSprite("src/sprites/buttonOff.txt");
	buttonSpriteOn = LoadSprite("src/sprites/buttonOn.txt");
#endif
	for (int i = 0; i < length; i++) {
		soundButtons[i] = new SoundButton * [length];
	}

	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			soundButtons[x][y] = new SoundButton(soundManager, x, y, KeyboardBtnToChar((LaunchpadManager::KeyboardButtons)(y*length + x)));
			soundButtons[x][y]->GetSound()->SetNote((Note::Notes)x, y+3);
		}
	}
}

LaunchpadManager::LaunchpadManager(int _length, int _firstPin) {
	
}

LaunchpadButton* LaunchpadManager::GetButton(int _x, int _y) {
    return soundButtons[_x][_y];
}

void LaunchpadManager::Update() {
	UpdateInput();
#if !defined (__AVR__) && !defined (__avr__)
	Render();
#endif
}

void LaunchpadManager::UpdateInput() {
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			if (soundButtons[x][y]->isButtonPressed()) {
				soundButtons[x][y]->Action();
			}
		}
	}
}
/******/


void LaunchpadManager::Render()
{
#if !defined (__AVR__) && !defined (__avr__)
	console->CleanBuffers();

	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			if (soundButtons[x][y]->isButtonPressed()) {
				console->WriteSpriteBuffer(x * PIXEL_SIZE_X, y * PIXEL_SIZE_Y, buttonSpriteOn);
			}
			else {
				console->WriteSpriteBuffer(x * PIXEL_SIZE_X, y * PIXEL_SIZE_Y, buttonSpriteOff);
			}
		}
	}

	console->RenderBuffers();
#endif
}

LaunchpadManager::~LaunchpadManager() {
	if (soundButtons) {
		for (int y = 0; y < length; y++) {
			for (int x = 0; x < length; x++) {
				delete soundButtons[x][y];
			}
			delete soundButtons[y];
		}
	}
	delete[] soundButtons;
}

#if !defined (__AVR__) && !defined (__avr__)

Sprite LaunchpadManager::LoadSprite(std::string SpriteAssetFileName)
{
	Sprite sprite;
	std::ifstream imageAssetFile;
	imageAssetFile.open(SpriteAssetFileName);

	if (imageAssetFile.is_open())
	{
		std::string widthHeigth;
		getline(imageAssetFile, widthHeigth);
		int colonPos = widthHeigth.find(',');
		if (!(colonPos == std::string::npos))
		{
			sprite.width = atoi(widthHeigth.substr(0, widthHeigth.find(',')).c_str());
			sprite.height = atoi(widthHeigth.substr(widthHeigth.find(',') + 1).c_str());
			if (sprite.width > 0 && sprite.height > 0)
			{
				sprite.bufferColor = new EBackColor[sprite.width * sprite.height];
				int h = 0, offset = 0;
				while (!imageAssetFile.eof() && h < sprite.height)
				{
					std::string line;
					getline(imageAssetFile, line);
					if (line.size() != sprite.width)
						throw std::runtime_error("fichero de sprite con formato invalido. Faltan columnas, linea " + h);
					for (unsigned int s = 0; s < line.size(); s++)
						* (sprite.bufferColor + offset++) = AtoBackColor(line.at(s));


					h++;
				}
				if (h < sprite.height)
					throw std::runtime_error("fichero de sprite con formato invalido. Faltan lineas.");
			}
			else
				throw std::runtime_error("fichero de sprite con formato invalido. Ancho y alto incorrecto.");
		}
		else
			throw std::runtime_error("fichero de sprite con formato invalido. Ancho y alto incorrecto.Falta coma.");

	}
	else
		throw std::runtime_error("File " + SpriteAssetFileName + " not found or is locked for read");

	return sprite;
}

EBackColor LaunchpadManager::AtoBackColor(char c)
{
	switch (c)
	{
	case '.':
		return EBackColor::Alpha0;
	case '0':
		return EBackColor::Black;
	case '1':
		return EBackColor::Red;
	case '2':
		return EBackColor::Green;
	case '3':
		return EBackColor::Yellow;
	case '4':
		return EBackColor::Blue;
	case '5':
		return EBackColor::Magenta;
	case '6':
		return EBackColor::Cyan;
	case '7':
		return EBackColor::White;
	case '8':
		return EBackColor::LightBlack;
	case '9':
		return EBackColor::LightRed;
	case 'A':
		return EBackColor::LightGreen;
	case 'B':
		return EBackColor::LightYellow;
	case 'C':
		return EBackColor::LightBlue;
	case 'D':
		return EBackColor::LightMagenta;
	case 'E':
		return EBackColor::LightCyan;
	case 'F':
		return EBackColor::LightWhite;
	default:
		return EBackColor::Alpha0;
		break;
	}
}

#endif