#pragma once
#include <string>

class Bio
{
public:
	Bio();

	bool takeDamage(int attack);

	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int &x, int &y);
	int getAttack() { return _attack; };
	std::string getName(){ return _name; };
	int getExp() { return _exp; };

protected:

	std::string _name;

	//Properties
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _exp;
	//TODO : vector of possible item drops
	
	//Position
	int _x, _y;
};
