#include <iostream>
#include "Utility.h"
#include "Engine.h"
#include <Windows.h>
#include <string>

using namespace std;

int main()
{
	Engine game("First_Map");
	game.playGame();
	Pause();
	return 0;
}
