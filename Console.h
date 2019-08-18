/*

MADE IN FRANCISCO ARIAS (c)

								FFFFFFFFFFFFFFFA
								FF			  A A
								FF			 A   A
								FF			A	  A
								FFFFFFFFFFFAAAAAAAAA
								FF		  A			A
								FF		 A			 A
								FF		A			  A
*/


#pragma once
#ifndef __AVR__ && __avr__
#include <Windows.h>
#include <iostream>
#include <string>

//Los colores para consola son 16 de fondo y 16 de texto
//Para dibujar un "pixel", Console dibuja un espacio con solo el color de fondo cambiado
//Para escribir un texto, solo se permite elegir el color del texto, de este modo un 
//pixel podría pasar "por debajo" del texto sin modificarlo (sería su color de fondo en ese momento).

//La consola windows se divide en una consola para el texto (char)
//y otra para los "atributos" del texto (WORD = 2 bytes = unsigned short int)
//El color está en el primer byte de este WORD  de esta forma:
//medio byte "más significativo" = color de fondo (back): 16 colores (de 0b0000xxxx a 0b1111xxxx)
//medio byte "menos significativo" = color del texto (fore): 16 colores  (de 0bxxxx0000 a 0bxxxx1111)
//Se han creado dos enumerates para dichos colores, y se la forzado a C++ a que esos enumerates
//sean internamente del tipo "unsigned short", que es el tipo de los atributos.
//Además, esos enumerates se han hecho "class" para poder tener las mismas etiquetas en los dos (Red, Blue...) sin
//que de error de símbolo duplicado. "class" También sirve para cuando se pida por parámetro EForeColor o
//EBackColor, de error si le pasas un tipo de color equivocado.

//Como el back color tiene que respetar el fore color, y no hay forma de acceder a medio byte directamente,
//(el tipo de datos mas corto es el char, que es un byte), y no queremos hacer operaciones & y | continuamente,
//Hacemos 3 buffers: el de fore color, el de back color y el buffer final de mezcla, que se informa
//con una operación | de los dos primeros buffers.

enum class EForeColor: unsigned short
{
	Black = 0x0,
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
	Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
	White = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN,
	LightBlack = Black | FOREGROUND_INTENSITY,
	LightRed = Red | FOREGROUND_INTENSITY,
	LightGreen = Green | FOREGROUND_INTENSITY,
	LightYellow = Yellow | FOREGROUND_INTENSITY,
	LightBlue = Blue | FOREGROUND_INTENSITY,
	LightMagenta = Magenta | FOREGROUND_INTENSITY,
	LightCyan = Cyan | FOREGROUND_INTENSITY,
	LightWhite = White | FOREGROUND_INTENSITY,
	Alpha0 = 0b100000000
};

enum class EBackColor : unsigned short
{
	Black = 0x00,
	Red = BACKGROUND_RED,
	Green = BACKGROUND_GREEN,
	Yellow = BACKGROUND_RED | BACKGROUND_GREEN,
	Blue = BACKGROUND_BLUE,
	Magenta = BACKGROUND_RED | BACKGROUND_BLUE,
	Cyan = BACKGROUND_BLUE | BACKGROUND_GREEN,
	White = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN,
	LightBlack = Black | BACKGROUND_INTENSITY,
	LightRed = Red | BACKGROUND_INTENSITY,
	LightGreen = Green | BACKGROUND_INTENSITY,
	LightYellow = Yellow | BACKGROUND_INTENSITY,
	LightBlue = Blue | BACKGROUND_INTENSITY,
	LightMagenta = Magenta | BACKGROUND_INTENSITY,
	LightCyan = Cyan | BACKGROUND_INTENSITY,
	LightWhite = White | BACKGROUND_INTENSITY,
	Alpha0 = 0b100000000
};

//Alienación de texto en pantalla (horizontal)
enum EAligned
{
	LEFT,
	CENTER,
	RIGHT
};

//La clase Console averigua el tamaño (alto x ancho) de la consola actual
//y crea dos buffers dinámicos, uno de tipo char para el texto, y otro de tipo unsigned short int para los colores
//El buffer es una zona de memoria que hemos reservado dinámicamente para ir escribiendo ahí (WriteBufer...) lo que, posteriormente,
//volcaremos de una sola vez en pantalla (RenderBuffers)

struct Sprite
{
	int width;
	int height;
	EBackColor *bufferColor;
};

struct Image
{
	int width;
	int height;
	EForeColor *bufferColor;
	char *bufferChar;
};


class Console
{
public:

	static inline int GetWidth() { return width; };
	static inline int GetHeight() { return height; };

	static int width, height;
private:

	friend class UnityEngine;
	friend class SpriteRenderer;
	friend class Text;
	friend class ImageRenderer;
	friend class LaunchpadManager;

	~Console();
	Console();


	int buffersSize;
	HANDLE hndl;
	char *charScreenBuffer;
	//unsigned short int *colorScreenBuffer;

	unsigned short int *backColorScreenBuffer;
	unsigned short int *foreColorScreenBuffer;
	unsigned short int *colorScreenBuffer;

	COORD zeroCOORD;

	void WritePixelBuffer(int x, int y, EBackColor color) const;
	void WritePixelBuffer(int x1, int y1, int x2, int y2, EBackColor color) const;
	void WriteCharBuffer(int x, int y, char _char, EForeColor color) const;
	void WriteStringBuffer(int x, int y, std::string _string, EForeColor color) const;
	void WriteStringBuffer(int y, EAligned aligned, std::string _string, EForeColor color) const;
	void WriteCharImageBuffer(int x, int y, const Image &image) const;
	void WriteSpriteBuffer(int x, int y, const Sprite &sprite) const;
	void ShowConsoleCursor(bool showFlag) const;

	void SetSymmetricalFontSize();


	void RenderBuffers() const;
	void CleanBuffers();
};

#endif

