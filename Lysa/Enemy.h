#pragma once
#include <string>

class Enemy
{
public:
	Enemy(std::string name, char tileSign, int lvl, int attack, int defense, int health, int exp);
	char getEnemyMove(int playerX, int playerY);
	int attack();
	int takeDamage(int attack);

	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int &x, int &y);
	char getTileSign();
	std::string getName();

private:
	std::string _name;
	char _tileSign;

	//Proprties
	int _level;
	int _attack;
	int _defense;
	int _health;
	int _expAmount;
	//TODO : vector of possible item drops

	//Position
	int _x;
	int _y;
};

