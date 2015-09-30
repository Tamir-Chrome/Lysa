#pragma once
#include <string>
#include "Utility.h"

class Bio
{
public:
	Bio();

	bool takeDamage(int attack);
	void draw();

	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int &x, int &y);
	int getAttack() { return _attack; };
	std::string getName(){ return _name; };
	int getExp() { return _exp; };
	char getTileSign() { return _faceTile; };

protected:

	std::string _name;
	char _faceTile; // how he would look on the board

	//Properties
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _exp;
	BioStatus _bio_status;
	//TODO : vector of possible item drops
	
	//Position
	int _x, _y;
};
