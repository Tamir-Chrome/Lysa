#include "Player.h"
#include <random>
#include <ctime>

using namespace std;

Player::Player()
{

}

void Player::init(int level, int health, int attack, int defense, int exp)
{
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_exp = exp;
}

int Player::takeDamage(int attack)
{
	attack -= _defense;
	if (attack > 0)
	{
		_health -= attack;
		if (_health <= 0)
			return (_exp + _level * 50);
	}
	return 0;
}

//Setters
void Player::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::addExp(int exp)
{
	_exp += exp;
	while (_exp >= 50) // level up
	{
		_exp -= 50;
		_attack += 10;
		_defense += 10;
		_health += 20;
		_level++;
		printf("Leveled up to lvl.%d\n", _level);
		system("PAUSE");
	}
}

//Getters
void Player::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}
