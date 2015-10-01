#pragma once
#include <string>
#include <Windows.h>

enum BioStatus // color
{
	PLAYER = 8,
	ENEMY = 12,
	PASSIVE = 9
};

enum Keys
{
	K_ENTER = 13,
	K_ESC = 27
};

//Console and Printing functions
void setCursorAt(int x, int y); // sets cursor at x, y in consloe

void putCharAt(int x, int y, char c);

void clearFrom(int y);

void setTextColor(int colorValue); // can set background and foreground color

int getMergedColor(int background, int foreground); // return a single value that presents the given background and foreground colors

void Pause(const char* printText = nullptr);

//Error
void ErrorExit(LPSTR lpszMessage);

void GameExit();

//Handler

void setConsole(HANDLE &output, HANDLE &input, DWORD oldMode);