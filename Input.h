#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>


class Input
{
private:
	friend class LaunchpadManager;
	static RECT rc;

	static void Update()
	{
		if (_kbhit() > 0)
		{
			inputString = _getch();
			anyString = true;
		}
		else
		{
			inputString = '\0';
			anyString = false;
		}
	}

public:

	static bool anyString;
	static char inputString;

	static bool GetKey(char key)
	{
		key = toupper(key);
		return GetAsyncKeyState(key) & 0x8000;
	}
	static bool GetKeyDown(char key)
	{
		key = toupper(key);
		return GetAsyncKeyState(key) & 0x0001;
	}

	static bool GetMouseButtonDown(int i)
	{
		if ((i != 2) && (i != 1))
			return false;

		if (GetKeyState(i) & 0x8000)
			return true;
		return false;
	}
};
