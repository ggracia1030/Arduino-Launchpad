#include "Console.h"

int Console::width = 0;
int Console::height = 0;

Console::Console()
{
	hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hndl, &csbi);

	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	buffersSize = width * height;

	backColorScreenBuffer = new unsigned short[buffersSize];
	foreColorScreenBuffer = new unsigned short[buffersSize];
	colorScreenBuffer = new unsigned short[buffersSize];

	charScreenBuffer = new char[buffersSize];

	CleanBuffers();

	zeroCOORD.X = 0;
	zeroCOORD.Y = 0;
}

void Console::CleanBuffers()
{
	memset(backColorScreenBuffer, 0, buffersSize * sizeof(unsigned short));
	memset(foreColorScreenBuffer, 0, buffersSize * sizeof(unsigned short));
	memset(colorScreenBuffer, 0, buffersSize * sizeof(unsigned short));

	memset(charScreenBuffer, ' ', buffersSize);
}

void Console::WritePixelBuffer(int x, int y, EBackColor color) const
{
	int offset = y * width + x;
	if ((offset >= buffersSize) || (offset<0))
		return;

	*(backColorScreenBuffer + offset) = (unsigned short)color;
}

void Console::WritePixelBuffer(int x1, int y1, int x2, int y2, EBackColor color) const
{
	int from = y1 * width + x1 - 1;
	int to = y2 * width + x2;
	if ((from < 0) || (to >= buffersSize))
		return;

	while (((++from)<=to) && (from<buffersSize))
		*(backColorScreenBuffer + from) = (unsigned short)color;
}

void Console::WriteCharBuffer(int x, int y, char _char, EForeColor color) const
{
	int offset = y * width + x;
	if ((offset >= buffersSize) || (offset < 0))
		return;

	*(charScreenBuffer + offset) = _char;
	*(foreColorScreenBuffer + offset) = (unsigned short)color;
}

void Console::WriteStringBuffer(int x, int y, std::string _string, EForeColor color) const
{
	int offset = y * width + x;
	if ((offset < 0) || (offset + _string.size() >= buffersSize))
		return;

	for (int c = 0;c < _string.size(); c++)
	{
		*(charScreenBuffer + offset) = _string.at(c);
		*(foreColorScreenBuffer + offset++) = (unsigned short)color;
	}
}

void Console::WriteStringBuffer(int y, EAligned aligned, std::string _string, EForeColor color) const
{
	int x = 0;
	switch (aligned)
	{
		case EAligned::RIGHT:
			x = width - _string.size()-1;
			break;
		case EAligned::CENTER:
			x = width / 2 - _string.size() / 2;
			break;
	}

	WriteStringBuffer(x, y, _string, color);
}

void Console::WriteCharImageBuffer(int x, int y, const Image & image) const
{
	//Si la image está completamente fuera de pantalla
	if ((x >= width) || (y >= height) || (x<-image.width) || (y<-image.height))
		return;

	//Halla el (sub)rectangulo de la image que se encuentra dentro del buffer de pantalla,
	//pero en coordenadas LOCALES de la image
	int x_ini = max(-x, 0);
	int y_ini = max(-y, 0);
	int x_fin = min(x + image.width, this->width) - x;
	int y_fin = min(y + image.height, this->height) - y;

	int offset = (y<0?0:y) * width + x;
	int imageOffset = y_ini*image.width+x_ini;
	int deltaImageY = image.width - (x_fin - x_ini);
	int deltaY = width - (x_fin - x_ini);

	for (int cy = y_ini;cy < y_fin;cy++)
	{
		for (int cx = x_ini;cx < x_fin;cx++)
		{
			if (image.bufferColor[imageOffset] != EForeColor::Alpha0)
			{
				*(foreColorScreenBuffer + offset) = (unsigned short)image.bufferColor[imageOffset];
				*(charScreenBuffer + offset) = image.bufferChar[imageOffset];
			}
			imageOffset++;
			offset++;
		}
		imageOffset += deltaImageY;
		offset += deltaY;
	}
}

void Console::WriteSpriteBuffer(int x, int y, const Sprite &sprite) const
{
	int offset = y * width + x;
	int spriteOffset = 0;
	int deltaY = width - sprite.width;

	int ytot, xtot;
	ytot = y;
	

	for (int cy = 0;cy < sprite.height;cy++)
	{
		xtot = x;
		for (int cx = 0;cx < sprite.width;cx++)
		{
			if (!((xtot < 0) || (xtot >= width) || (ytot < 0) || (ytot >= height)))
			{

				if (sprite.bufferColor[spriteOffset] != EBackColor::Alpha0)
					*(backColorScreenBuffer + offset) = (unsigned short)sprite.bufferColor[spriteOffset];
			}
			spriteOffset++;
			offset++;
			xtot++;
		}
		offset += deltaY;
		ytot++;
	}
		
}

void Console::ShowConsoleCursor(bool showFlag) const
{
	CONSOLE_CURSOR_INFO ci;

	GetConsoleCursorInfo(hndl, &ci);
	ci.bVisible = showFlag;
	SetConsoleCursorInfo(hndl, &ci);
}

/*
Ratios disponibles:
4:6
6 : 8
8 : 8
16 : 8
5 : 12
7 : 12
16 : 12
12 : 16
10 : 18
*/
void Console::SetSymmetricalFontSize()
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hndl, 0, lpConsoleCurrentFontEx);

	lpConsoleCurrentFontEx->dwFontSize.X = 8;
	lpConsoleCurrentFontEx->dwFontSize.Y = 8;

	SetCurrentConsoleFontEx(hndl, 0, lpConsoleCurrentFontEx);
}

void Console::RenderBuffers() const
{
	unsigned long nw;


	//Mezcla back & fore color
	for (int i = 0;i < buffersSize;i++)
		colorScreenBuffer[i] = backColorScreenBuffer[i] | foreColorScreenBuffer[i];

	WriteConsoleOutputCharacterA(hndl, charScreenBuffer, buffersSize, zeroCOORD, &nw);
	WriteConsoleOutputAttribute( hndl, colorScreenBuffer, buffersSize, zeroCOORD, &nw);
}


Console::~Console()
{
	if (colorScreenBuffer!=nullptr)
		delete[] colorScreenBuffer;
	if (charScreenBuffer!=nullptr)
		delete[] charScreenBuffer;
	if (backColorScreenBuffer != nullptr)
		delete[] backColorScreenBuffer;
	if (foreColorScreenBuffer != nullptr)
		delete[] foreColorScreenBuffer;
}
