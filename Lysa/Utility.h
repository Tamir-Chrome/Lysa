#pragma once
#include <string>

enum BioStatus // color
{
	PLAYER = 8,
	ENEMY = 12,
	PASSIVE = 9
};

void setCursorAt(int x, int y); // sets cursor at x, y in consloe

void putCharAt(int x, int y, char c);

void clearFrom(int y);

void setTextColor(int colorValue); // can set background and foreground color

int getMergedColor(int background, int foreground); // return a single value that presents the given background and foreground colors

void Pause(const char* printText = nullptr);

