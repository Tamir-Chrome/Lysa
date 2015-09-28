#include <string>


#include "Linker.h"

using namespace std;

Linker::Linker(int x, int y, string nameOfLinkedMap)
{
	_cordX = x;
	_cordY = y;
	_linkTo = nameOfLinkedMap;
}