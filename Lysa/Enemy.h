#pragma once
#include "Bio.h"

class Enemy : public Bio
{
public:
	Enemy(std::string name, char faceTile, int lvl, int attack, int defense, int health, int exp, BioStatus bio_status);
	char getEnemyMove(int playerX, int playerY);

	//Setters

	//Getters

private:

};

