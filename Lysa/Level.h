#pragma once
#include <string>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Map.h"

class Level
{
public:
	Level();
	void load(std::string mapName, Player &player);
	void drawBio(Player &player);
	void movePlayer(char in, Player &player);
	void updateEnemy(Player &player);


	//Setters
	void setTile(int x, int y, char tile) { _levelData[y][x] = tile; };
	void processLevel(Player &player);

	//Getters
	char getTile(int x, int y) { return _levelData[y][x]; };


private:
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void processPlayerMove(Player &player, int targetX, int targetY, char playerFace);
	void battleMonster(Player &player, int targetX, int targetY, int enemyIndex = -1);

	Map _loadedMap;
	std::vector <std::string> _levelData; // the loaded map
	std::vector <Enemy> _enemies;
	std::vector <Map> _mapList; // name of all the maps to load
};

