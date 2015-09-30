#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{

}

void Player::init(int level, int health, int attack, int defense, int exp, BioStatus bio_status)
{
	cout << "Enter name: ";
	cin >> _name;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_exp = exp;
	_bio_status = bio_status;
	_faceTile = '^';
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
