#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Linker.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

Level::Level()
{

}

void Level::processLevel(Player &player)
{
	char tile;
	_enemies.clear();
	for (int i = 0; i < (int)_levelData.size(); i++)
	{
		for (int j = 0; j < (int)_levelData[i].size(); j++)
		{
			tile = _levelData[i][j];
			switch (tile)
			{
			case '^': // PLAYER
				player.setPosition(j, i);
				break;
			case 'A': // AV BAIT
				_enemies.push_back(Enemy("Avv Bait", 'A', 1, 3, 1, 10, 30, ENEMY));
				_enemies[_enemies.size() - 1].setPosition(j, i);
				break;
			case 'S':
				_enemies.push_back(Enemy("Sachena", 'S', 2, 6, 2, 15, 50, ENEMY));
				_enemies[_enemies.size() - 1].setPosition(j, i);
				break;
			case 'M':
				_enemies.push_back(Enemy("Madregot Naot", 'M', 100, 200, 100, 0, 200, ENEMY));
				_enemies[_enemies.size() - 1].setPosition(j, i);
				break;
			}
		}
	}
}

void Level::load(string mapName, Player &player)
{
	ifstream inputFile;
	string line;
	string address = string("gameDataFiles\\mapList\\" + mapName + ".txt");
	inputFile.open(address); // file opens correctly
	if (inputFile.fail())
	{
		perror(address.c_str());
		system("PAUSE");
		exit(1);
	}
	_levelData.clear();
	while (getline(inputFile, line))
	{
		_levelData.push_back(line);
	}

	inputFile.close();

	processLevel(player); // init level: enemies, NPCs, player...

	bool isMapListed = false; // is map in mapList in vector

	for (int i = 0; i < (int)_mapList.size(); i++)
	{
		if (mapName == _mapList[i].getMapName())
		{
			isMapListed = true;
			_loadedMap = _mapList[i];
			break;
		}
	}
	if (isMapListed == false)
	{
		_loadedMap = Map(mapName);
		_mapList.push_back(_loadedMap);
	}

	//DRAW MAP HERE
	system("cls");
	for (int i = 0; i < (int)_levelData.size(); i++)
	{
		printf("%s\n", _levelData[i].c_str());
	}
	drawBio(player);
}

void Level::drawBio(Player &player)
{
	player.draw();
	for (int i = 0; i < (int)_enemies.size(); i++)
		_enemies[i].draw();
}

void Level::movePlayer(char in, Player &player)
{
	int playerX;
	int playerY;
	bool correctMove = false;

	player.getPosition(playerX, playerY);

	switch (in)
	{
	case 'w':
	case 'W':
		processPlayerMove(player, playerX, playerY - 1, '^');
		break;
	case 'a':
	case 'A':
		processPlayerMove(player, playerX - 1, playerY, '<');
		break;
	case 's':
	case 'S':
		processPlayerMove(player, playerX, playerY + 1, 'v');
		break;
	case 'd':
	case 'D':
		processPlayerMove(player, playerX + 1, playerY, '>');
		break;
	case K_ENTER: // ENTER
		processPlayerMove(player, playerX, playerY, '.');
		break;
	case K_ESC:
		GameExit();
		break;
	default:
		break;
	}

}

void Level::processPlayerMove(Player &player, int targetX, int targetY, char playerFace)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char targetTile = getTile(targetX, targetY);
	
	switch (targetTile)
	{
	case ' ':
		setTile(targetX, targetY, '^'); // sets player in map vector
		if (getTile(playerX, playerY) != '\\') {
			setTile(playerX, playerY, ' '); // remove last tile
			putCharAt(playerX, playerY, ' '); // remove last tile from console
		}
		player.setPosition(targetX, targetY);
		player.setFaceDirection(playerFace);
		player.draw();
		//battleMonster(player, targetX, targetY);
		break;
	case '#':
		break;
	case '\\':
		if (playerFace == '.')
		{
			int linkX, linkY;
			string mapNameLinked;
			for (int i = 0; i < _loadedMap.getNumOfLinkers(); i++)
			{
				// gets the cords for the linker at index 'i' in vector
				linkX = _loadedMap.getLinkedMapAt(i).getLinkX();
				linkY = _loadedMap.getLinkedMapAt(i).getLinkY();

				if (playerX == linkX && playerY == linkY)
				{
					mapNameLinked = _loadedMap.getLinkedMapAt(i).getNameOfLinkedMap(); // gets name of the linked map at this cords
					load(mapNameLinked, player); // LOADS NEW MAP
					break;
				}
			}
		}
		else {
			if (getTile(playerX, playerY) != '\\') { // only if he didnt enter a door from another door
				setTile(playerX, playerY, ' '); // remove last tile
				putCharAt(playerX, playerY, ' ');
			}
			player.setPosition(targetX, targetY);
		}
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void Level::updateEnemy(Player &player)
{
	char enemyMove;
	int playerX, playerY;
	int enemyX, enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < (int)_enemies.size(); i++) {

		enemyMove = _enemies[i].getEnemyMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (enemyMove)
		{
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
			// move in a cross
		case 'q': // move top left
			processEnemyMove(player, i, enemyX - 1, enemyY - 1);
			break;
		case 'e': // move top right
			processEnemyMove(player, i, enemyX + 1, enemyY - 1);
			break;
		case 'z': // move bottom left
			processEnemyMove(player, i, enemyX - 1, enemyY + 1);
			break;
		case 'c': // move bottom right
			processEnemyMove(player, i, enemyX + 1, enemyY + 1);
			break;
		}
	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int enemyX, enemyY;
	char moveTile = getTile(targetX, targetY);
	_enemies[enemyIndex].getPosition(enemyX, enemyY);

	switch (moveTile)
	{
	case ' ':
		// remove last enemy position
		setTile(enemyX, enemyY, ' ');
		putCharAt(enemyX, enemyY, ' '); 

		// set new enemy position
		setTile(targetX, targetY, _enemies[enemyIndex].getTileSign());
		_enemies[enemyIndex].setPosition(targetX, targetY); 
		_enemies[enemyIndex].draw(); // draw new position on console
		break;
	case '^':
		battleMonster(player, targetX, targetY, enemyIndex);
		break;
	}

}

void Level::battleMonster(Player &player, int targetX, int targetY, int enemyIndex)
{
	int playerX, enemyX;
	int playerY, enemyY;
	int attackRoll;
	bool attackResluts;

	player.getPosition(playerX, playerY);

	if (enemyIndex != -1) // fight from enemy to player
	{
		_enemies[enemyIndex].getPosition(enemyX, enemyY);
		if (targetX == playerX && targetY == playerY)
		{
			//battle
			//Enemy turn
			attackRoll = _enemies[enemyIndex].getAttack();
			attackResluts = player.takeDamage(attackRoll);
			setCursorAt(0, _levelData.size());
			printf("%s attacked %s by %d damage\n", _enemies[enemyIndex].getName().c_str(), player.getName().c_str(), attackRoll);
			if (attackResluts)// if attackResluts is true, player is dead
			{
				putCharAt(playerX, playerY, 'X'); // clears the enemy
				printf("You died. You collected %d EXP\n", player.getExp());
				//TODO: Handle player's death(and ask for save)
				Pause();
				GameExit();
			}

			//Player turn
			attackRoll = player.getAttack();
			printf("%s attacked %s by %d damage\n", player.getName().c_str(), _enemies[enemyIndex].getName().c_str(), attackRoll);
			Pause();
			attackResluts = _enemies[enemyIndex].takeDamage(attackRoll);
			if (attackResluts) // if attackResluts is true, enemy is dead
			{
				printf("Enemy died. You got %d EXP\n", _enemies[enemyIndex].getExp());

				Pause();
				player.addExp(_enemies[enemyIndex].getExp()); // adds exp for killing the enemy
				// clears the enemy
				setTile(enemyX, enemyY, ' ');
				putCharAt(enemyX, enemyY, ' '); 
				_enemies[enemyIndex] = _enemies.back(); //copies the last enemy to the enemy that just died
				_enemies.pop_back(); // pops the last enemy that we just copied

				//continue;
				//return;
			}
		}
	}
	else // fight from player to enemy
	{
		for (int i = 0; i < (int)_enemies.size(); i++)
		{
			_enemies[i].getPosition(enemyX, enemyY);
			if (targetX == enemyX && targetY == enemyY)
			{
				//battle
				//Player turn
				attackRoll = player.getAttack();
				setCursorAt(0, _levelData.size());
				printf("%s attacked %s by %d damage\n", player.getName().c_str(), _enemies[i].getName().c_str(), attackRoll);
				attackResluts = _enemies[i].takeDamage(attackRoll);
				if (attackResluts) // if attackResluts is true, enemy is dead
				{
					printf("Enemy died. You got %d EXP\n", _enemies[i].getExp());

					Pause();
					player.addExp(_enemies[i].getExp()); // adds exp for killing the enemy
					// clears the enemy
					setTile(enemyX, enemyY, ' ');
					putCharAt(enemyX, enemyY, ' ');
					_enemies[i] = _enemies.back(); //copies the last enemy to the enemy that just died
					_enemies.pop_back(); // pops the last enemy that we just copied
					i--; // so we dont the skip the enemy we just copied

					//continue;
					break;
				}

				//Enemy turn
				attackRoll = _enemies[i].getAttack();
				attackResluts = player.takeDamage(attackRoll);
				printf("%s attacked %s by %d damage\n", _enemies[i].getName().c_str(), player.getName().c_str(), attackRoll);
				Pause();
				if (attackResluts)// if attackResluts is true, player is dead
				{
					putCharAt(playerX, playerY, 'X'); // clears the enemy
					printf("You died. You collected %d EXP\n", player.getExp());
					//TODO: Handle player's death(and ask for save)
					Pause();
					GameExit();
				}
			}
		}
	}
	clearFrom(_levelData.size());
}
