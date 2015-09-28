#pragma once
#include <string>
#include <vector>

#include "Linker.h"

class Map
{
public:
	Map();
	Map(std::string name);
	void initLinkers();

	//Setters
	void addLinker(int x, int y, std::string nameOfLinkedMap);

	//Getters
	int getNumOfLinkers() { return _linkers.size(); };
	Linker getLinkedMapAt(int index){ return _linkers[index]; };
	std::string getMapName() { return _name; };

private:
	std::string _name;
	std::vector<Linker> _linkers;
};
