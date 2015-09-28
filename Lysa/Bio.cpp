#include "Bio.h"


Bio::Bio()
{
}

bool Bio::takeDamage(int attack)
{
	attack -= _defense;
	if (attack > 0)
	{
		_health -= attack;
		if (_health <= 0)
			return true;
	}
	return false;
}

//Setters
void Bio::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

//Getters
void Bio::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}
