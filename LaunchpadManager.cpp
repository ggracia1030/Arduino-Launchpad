#include "LaunchpadManager.h"

LaunchpadManager::LaunchpadManager(InputManager* _input, SoundManager* _sound, LCDScreen* _lcd)
{
	lcdScreen = _lcd;
	soundManager = _sound;
	inputManager = _input;
}

LaunchpadManager::LaunchpadManager(InputManager* _input, SoundManager* _sound, LCDScreen* _lcd, Console* _console)
{
	lcdScreen = _lcd;
	soundManager = _sound;
	inputManager = _input;

#if !defined (__AVR__) && !defined (__avr__)
	console = _console;
	buttonPushSprite = LoadSprite("src/sprites/buttonPush.txt");
	buttonAcceptSprite = LoadSprite("src/sprites/buttonAccept.txt");
	buttonCancelSprite = LoadSprite("src/sprites/buttonCancel.txt");
	buttonSoundSprite = LoadSprite("src/sprites/buttonSound.txt");
	buttonSmall = LoadSprite("src/sprites/smallButton.txt");
	lcdScreenSprite = LoadSprite("src/sprites/lcdScreen.txt");
#endif
}

/*LaunchpadManager::LaunchpadManager(int _length, int _firstPin, int _acceptBtnPin, int _cancelBtnPin) {
	length = _length;
	lcdScreen = new LCDScreen();
	
#if !defined (__AVR__) && !defined (__avr__)
	console = new Console();
	soundManager = new SoundManager(4000000, 3, console);

	buttonPushSprite = LoadSprite("src/sprites/buttonPush.txt");
	buttonAcceptSprite = LoadSprite("src/sprites/buttonAccept.txt");
	buttonCancelSprite = LoadSprite("src/sprites/buttonCancel.txt");
	buttonSoundSprite = LoadSprite("src/sprites/buttonSound.txt");
	buttonSmall = LoadSprite("src/sprites/smallButton.txt");
	lcdScreenSprite = LoadSprite("src/sprites/lcdScreen.txt");
#else
	soundManager = new SoundManager(4000000, 3);
#endif

	inputManager = new InputManager(_firstPin, _acceptBtnPin, _cancelBtnPin, _length, soundManager);
}*/

void LaunchpadManager::Update() {
	inputManager->EarlyUpdate();

	UpdateInput();
#if !defined (__AVR__) && !defined (__avr__)
	Render();
#endif

	
}

void LaunchpadManager::UpdateInput() {
#if defined (__AVR__) || defined (__avr__)
	for (int y = 0; y < inputManager->GetSoundButtonsLength(); y++) {
		for (int x = 0; x < inputManager->GetSoundButtonsLength(); x++) {
			if (inputManager->GetSoundButton(x, y)->GetButtonDown()) {
				inputManager->GetSoundButton(x, y)->OnButtonDown();
			}
			else if (inputManager->GetSoundButton(x, y)->GetButtonUp()) {
				inputManager->GetSoundButton(x, y)->OnButtonUp();
			}
		}
	}
#if defined (BUZZER_TEST)
		
#endif
	}

#else
	for (int y = 0; y < inputManager->GetSoundButtonsLength(); y++) {
		for (int x = 0; x < inputManager->GetSoundButtonsLength(); x++) {
			if(inputManager->GetSoundButton(x, y)->GetButtonDown()) {
				inputManager->GetSoundButton(x, y)->OnButtonDown();
			}
		}
	}
#endif
}


void LaunchpadManager::Render()
{
#if !defined (__AVR__) && !defined (__avr__)
	console->CleanBuffers();
	std::string tempString = "";
	for (int y = 0; y < inputManager->GetSoundButtonsLength(); y++) {
		for (int x = 0; x < inputManager->GetSoundButtonsLength(); x++) {
			if (inputManager->GetSoundButton(x, y)->GetButton()) {
				console->WriteSpriteBuffer(BUTTONS_MATRIX_OFFSET_X + x * PIXEL_SIZE_X, BUTTONS_MATRIX_OFFSET_Y + y * PIXEL_SIZE_Y, buttonPushSprite);
			}
			else {
				console->WriteSpriteBuffer(BUTTONS_MATRIX_OFFSET_X + x * PIXEL_SIZE_X, BUTTONS_MATRIX_OFFSET_Y + y * PIXEL_SIZE_Y, buttonSoundSprite);
			}
			tempString = "Note: " + inputManager->GetSoundButton(x, y)->GetSound()->ToString();
			console->WriteStringBuffer(BUTTONS_MATRIX_OFFSET_X + x * PIXEL_SIZE_X, BUTTONS_MATRIX_OFFSET_Y + y * PIXEL_SIZE_Y, tempString, EForeColor::White);

			tempString = "Freq: " + std::to_string(inputManager->GetSoundButton(x, y)->GetSound()->GetFrequency());
			console->WriteStringBuffer(BUTTONS_MATRIX_OFFSET_X + x * PIXEL_SIZE_X, BUTTONS_MATRIX_OFFSET_Y +  y * PIXEL_SIZE_Y + 1, tempString, EForeColor::White);

			tempString = "Value: " + std::to_string(soundManager->GetNoteValue(inputManager->GetSoundButton(x, y)->GetSound()->GetFrequency()));
			console->WriteStringBuffer(BUTTONS_MATRIX_OFFSET_X + x * PIXEL_SIZE_X, BUTTONS_MATRIX_OFFSET_Y + y * PIXEL_SIZE_Y + 2, tempString, EForeColor::White);

			tempString = "Pins: [" + std::to_string(inputManager->GetSoundButton(x, y)->GetXPin()) + "," +
				std::to_string(inputManager->GetSoundButton(x, y)->GetYPin()) + "]";
			console->WriteStringBuffer(BUTTONS_MATRIX_OFFSET_X + x * PIXEL_SIZE_X, BUTTONS_MATRIX_OFFSET_Y + y * PIXEL_SIZE_Y + 3, tempString, EForeColor::White);
		}
	}
	console->WriteSpriteBuffer(3, 1, lcdScreenSprite);
	for (int i = 0; i < 2; i++) {
		console->WriteStringBuffer(4, 2 + i, lcdScreen->GetString(i), EForeColor::White);
	}

	if (inputManager->GetAcceptButton()->GetButton()) {
		console->WriteSpriteBuffer(25, 1, buttonAcceptSprite);
	}
	else {
		console->WriteSpriteBuffer(25, 1, buttonSmall);
	}
	
	if (inputManager->GetCancelButton()->GetButton()) {
		console->WriteSpriteBuffer(35, 1, buttonCancelSprite);
	}
	else {
		console->WriteSpriteBuffer(35, 1, buttonSmall);
	}

	tempString = " Accept";
	console->WriteStringBuffer(25, 2, tempString, EForeColor::White);
	tempString = " Cancel";
	console->WriteStringBuffer(35, 2, tempString, EForeColor::White);

	console->RenderBuffers();
#endif
}

LaunchpadManager::~LaunchpadManager() {
	if (inputManager != nullptr) 
		delete inputManager;

	if(soundManager != nullptr)
		delete soundManager;

	if (lcdScreen != nullptr)
		delete lcdScreen;

#if !defined (__AVR__) && !defined (__avr__)
	if (console != nullptr)
		delete console;
#endif
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