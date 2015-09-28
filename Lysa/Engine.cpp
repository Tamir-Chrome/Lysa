#include "Engine.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;


Engine::Engine(string levelFileName)
{

	_player.init(1, 100, 5, 0, 0);
	_level.load(levelFileName, _player);
}

void Engine::playGame()
{
	bool isDone = false;

	while (isDone != true)
	{
		clearAndPrint();
		playerMove();
		clearAndPrint();
		_level.updateEnemy(_player);
	}
}

void Engine::clearAndPrint()
{
	system("cls");
	_level.print();
}

void Engine::playerMove()
{
	char in;
	in = _getch();
	_level.movePlayer(in, _player);
}

