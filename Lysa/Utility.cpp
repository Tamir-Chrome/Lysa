#include "Utility.h"
#include <conio.h>
#include <iostream>

HANDLE consoleOutput, consoleInput;
DWORD fdwSaveOldMode; // old console mode

void setConsole(HANDLE &output, HANDLE &input, DWORD oldMode)
{
	consoleInput = input;
	consoleOutput = output;
	fdwSaveOldMode = oldMode;
}

void setCursorAt(int x, int y)
{
	COORD tileOnConsole;
	//sets COORDS to give x and y
	tileOnConsole.X = x;
	tileOnConsole.Y = y;

	SetConsoleCursorPosition(consoleOutput, tileOnConsole);
}

void putCharAt(int x, int y, char c)
{
	setCursorAt(x, y);
	putchar(c);
	setCursorAt(0, 0); // reset
}

void clearFrom(int y)
{
	COORD cords;
	int tempVar;
	cords.X = 0;
	cords.Y = y;
	FillConsoleOutputCharacter(consoleOutput, ' ', 1000, cords, (LPDWORD)&tempVar);
}

void setTextColor(int colorValue)
{
	SetConsoleTextAttribute(consoleOutput, (WORD)colorValue);
}

int getMergedColor(int backgroundColor, int foregroundColor)
{//           0000 0110 -> 0110 0000 | 0000 1000 -> 0110 1000
	return ((backgroundColor << 4) | foregroundColor);
}

void Pause(const char* printText)
{
	if (printText)
		std::cout << printText;
	_getch();
}

//Error

void ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	GameExit();
	
}

void GameExit()
{
	SetConsoleMode(consoleOutput, fdwSaveOldMode);
	SetConsoleMode(consoleInput, fdwSaveOldMode);
	exit(1);
}