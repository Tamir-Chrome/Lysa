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
				_enemies.push_back(Enemy("Avv Bait", 'A', 1, 3, 1, 10, 30));
				_enemies[_enemies.size() - 1].setPosition(j, i);
				break;
			case 'S':
				_enemies.push_back(Enemy("Sachena", 'S', 2, 6, 2, 15, 50));
				_enemies[_enemies.size() - 1].setPosition(j, i);
				break;
			case 'M':
				_enemies.push_back(Enemy("Madregot Naot", 'M', 100, 200, 100, 0, 200));
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
	string address = string("gameDataFiles\\mapList\\").append(mapName).append(".txt");
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

	processLevel(player); // init level: enemies, NPCs, player...
}

void Level::print()
{
	string line;
	for (int i = 0; i < _levelData.size(); i++)
	{
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
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
	case 13: // ENTER
		processPlayerMove(player, playerX, playerY, '.');
		break;
	default:
		printf("Wrong input\n");
		system("PAUSE");
		break;
	}

}

void Level::processPlayerMove(Player &player, int targetX, int targetY, char playerFace)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case ' ':
		setTile(targetX, targetY, playerFace);
		if (getTile(playerX, playerY) != '\\')
			setTile(playerX, playerY, ' ');
		player.setPosition(targetX, targetY);
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
			if (getTile(playerX, playerY) != '\\')
				setTile(playerX, playerY, ' ');
			player.setPosition(targetX, targetY);
		}
	default:
		battleMonster(player, targetX, targetY);
	}
}

void Level::updateEnemy(Player &player)
{
	char enemyMove;
	int playerX, playerY;
	int enemyX, enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {

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
		setTile(targetX, targetY, _enemies[enemyIndex].getTileSign());
		setTile(enemyX, enemyY, ' ');
		_enemies[enemyIndex].setPosition(targetX, targetY);
	case '^':
	case '>':
	case '<':
	case 'v':
		battleMonster(player, enemyX, enemyY);
		break;
	}

}

void Level::battleMonster(Player &player, int targetX, int targetY)
{
	int playerX, enemyX;
	int playerY, enemyY;
	int attackRoll, attackResluts;

	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);
		if (targetX == enemyX && targetY == enemyY)
		{
			//battle
			attackRoll = player.attack();
			printf("Player attacked %s by %d damage\n", _enemies[i].getName().c_str(), attackRoll);
			attackResluts = _enemies[i].takeDamage(attackRoll);
			if (attackResluts != 0)
			{
				printf("Enemy died. You got %d EXP\n", attackResluts);

				_enemies[i] = _enemies.back(); //copies the last enemy to the enemy that just died
				_enemies.pop_back(); // pops the last enemy that we just copied
				i--; // so we dont the skip the enemy we just copied

				system("PAUSE");
				player.addExp(attackResluts); // adds exp for killing the enemy
				setTile(targetX, targetY, ' ');
				return;
			}

			//Enemy turn
			attackRoll = _enemies[i].attack();
			attackResluts = player.takeDamage(attackRoll);
			printf("%s attacked Player by %d damage\n", _enemies[i].getName().c_str(), attackRoll);
			system("PAUSE");
			if (attackResluts != 0)
			{
				setTile(playerX, playerY, 'X');
				printf("You died. You collected %d EXP\n", attackResluts);
				//TODO: Handle player's death(and ask for save)
				system("PAUSE");
				exit(1);
			}
		}
	}

}

//Setters
void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}
/*
void setNameMaps()
{
ifstream mapsNamesFile;
string nameMap;
mapsNamesFile.open("gameData\\mapList\\MapList.txt");
if (mapsNamesFile.fail())
{
perror("gameData\\mapList\\MapList.txt");
system("PAUSE");
exit(1);
}
while (getline(mapsNamesFile, nameMap))
{
_levelData.push_back(line);
}
}*/

//Getters
char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}