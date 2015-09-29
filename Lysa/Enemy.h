#pragma once
#include "Bio.h"

class Enemy : public Bio
{
public:
	Enemy(std::string name, char tileSign, int lvl, int attack, int defense, int health, int exp);
	char getEnemyMove(int playerX, int playerY);

	//Setters

	//Getters
	char getTileSign() { return _tileSign; };

private:
	char _tileSign; // the face of the monster

};

