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

void Bio::draw()
{
	setCursorAt(_x, _y);
	setTextColor(_bio_status);
	putchar(_faceTile);
	//reset cursor
	setTextColor(7);
	setCursorAt(0, 0);
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
