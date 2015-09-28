#include "Enemy.h"
#include <string>
#include <random>
#include <ctime>

using namespace std;

Enemy::Enemy(string name, char tileSign, int lvl, int attack, int defense, int health, int exp)
{
	_name = name;
	_tileSign = tileSign;
	_level = lvl;
	_attack = attack;
	_defense = defense;
	_health = health;
	_exp = exp;
}


char Enemy::getEnemyMove(int playerX, int playerY)
{
	static default_random_engine randomNum(time(0));
	uniform_int_distribution<int> direction(0, 6);

	int distance;
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx); // abs for dx
	int ady = abs(dy); // abs for dy

	distance = adx + ady;
	if (distance <= 5) {
		// Moving along x
		if (adx > ady)
		{
			if (dx > 0)
				return 'a';
			else
				return 'd';
		}
		// Moving along y
		else if (adx < ady)
		{
			if (dy > 0)
				return 'w';
			else
				return 's';
		}
		// Moving along x & y
		else { // adx == ady
			if (dx > 0 && dy > 0) {
				return 'q'; // move top left
			}
			else if (dx < 0 && dy > 0) {
				return 'e'; // move top right
			}
			else if (dx < 0 && dy < 0) {
				return 'z'; // bottom left
			}
			else { // dx > 0 && dy < 0
				return 'c'; // bottom right
			}
		}
	}
	else
	{
		int diraction = direction(randomNum);

		switch (diraction)
		{
		case 0: // up
			return 'w';
		case 1: // left
			return 'a';
		case 2: // down
			return 's';
		case 3: // right
			return 'd';
		default:
			return '.';
		}
	}

}