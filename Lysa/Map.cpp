#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Map.h"
#include "Linker.h"
#include <string>
#include <fstream>

using namespace std;

#define MAX_NAME_LEN 16

Map::Map()
{

}

Map::Map(string nameMap)
{
	_name = nameMap;
	initLinkers();
}

void Map::initLinkers()
{
	int x, y;
	ifstream linkerInfoFile;
	string address = "gameDataFiles\\mapList\\" + _name + ".linkers";
	char linkedMapName[MAX_NAME_LEN] = { 0 };
	string line;
	linkerInfoFile.open(address); // opens linker file info
	if (linkerInfoFile.fail())
	{
		perror(address.c_str());
		system("PAUSE");
		exit(1);
	}
	linkerInfoFile.ignore(256, ' '); // skips first row
	while (getline(linkerInfoFile, line))
	{
		sscanf(line.c_str(), "%s %d %d", linkedMapName, &y, &x);
		addLinker(x, y, string(linkedMapName));
	}
	linkerInfoFile.close();
}

void Map::addLinker(int x, int y, std::string nameOfLinkedMap)
{
	_linkers.push_back(Linker(x, y, nameOfLinkedMap));
}

