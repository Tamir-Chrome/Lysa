#pragma once
#include <string>

// links between map to map by cords

class Linker
{
public:
	Linker(int x, int y, std::string);

	//Setters

	//Getters
	int getLinkX() { return _cordX; };
	int getLinkY() { return _cordY; };
	std::string getNameOfLinkedMap() { return _linkTo; };

private:
	int _cordX, _cordY;
	std::string _linkTo;
};