#pragma once
#include <string>

class Block
{
public:
	Block();

private:

	//Proprties
	bool _solid;
	bool _enterable;
	char _tileSign;
	std::string _name;
};

