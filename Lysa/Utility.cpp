#include "Utility.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void setCursorAt(int x, int y)
{
	COORD tileOnConsole;
	
	//sets COORDS to give x and y
	tileOnConsole.X = x;
	tileOnConsole.Y = y;

	SetConsoleCursorPosition(console, tileOnConsole);
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
	FillConsoleOutputCharacter(console, ' ', 1000, cords, (LPDWORD)&tempVar);
}

void setTextColor(int colorValue)
{
	SetConsoleTextAttribute(console, (WORD) colorValue);
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
