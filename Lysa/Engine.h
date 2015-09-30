#pragma once
#include <string>
#include <vector>

#include "Player.h"
#include "Level.h"
#include "Enemy.h"

class Engine
{
public:

	Engine(std::string levelFileName);
	void playGame();
	


private:
	void clearAndPrint();
	void playerMove();

	Player _player;
	Level _level;
};

