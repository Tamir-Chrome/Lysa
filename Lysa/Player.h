#pragma once

class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int exp);

	int takeDamage(int attack);

	//Setters
	void setPosition(int x, int y);
	void addExp(int exp);

	//Getters
	void getPosition(int &x, int &y);
	int attack() { return _attack; };

private:

	//Properties
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _exp;

	//Position
	int _x, _y;
};

