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
	char inputEventHandler(); // retruns the pressed key
	char KeyEvent(KEY_EVENT_RECORD ker); // retruns the pressed key

	Player _player;
	Level _level;

	//Input handler stuff
	DWORD _fdwMode; // new mode
	HANDLE _consoleOutput, _consoleInput;
	DWORD _fdwSaveOldMode; // old console mode
};

