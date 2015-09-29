#pragma once
#include "Bio.h"

class Player : public Bio
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int exp);

	//Setters
	void addExp(int exp);

	//Getters


};

