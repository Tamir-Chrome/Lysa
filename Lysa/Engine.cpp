#include "Engine.h"
#include "Utility.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;


Engine::Engine(string levelFileName)
{
	_player.init(1, 100, 5, 0, 0, PLAYER);
	_level.load(levelFileName, _player);


	// Get the standard input handle. 

	_consoleInput = GetStdHandle(STD_INPUT_HANDLE);
	if (_consoleInput == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	_consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_consoleInput == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(_consoleInput, &_fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 

	_fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(_consoleInput, _fdwMode))
		ErrorExit("SetConsoleMode");

}

void Engine::playGame()
{
	bool isDone = false;
	char keyPressed;

	while (isDone != true)
	{
		
		keyPressed = inputEventHandler();
		if (keyPressed)
			_level.movePlayer(keyPressed, _player);
		_level.updateEnemy(_player);
	}
}


////
char Engine::KeyEvent(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown)
		return ker.uChar.AsciiChar;
	
	//else
	return 0;
}


char Engine::inputEventHandler()
{
	DWORD cNumRead;
	INPUT_RECORD irInBuf[1];
	char keyPressed;


	// Wait for the events. 

	if (!ReadConsoleInput(
		_consoleInput,      // input buffer handle 
		irInBuf,     // buffer to read into 
		1,         // size of read buffer 
		&cNumRead)) // number of records read 
		ErrorExit("ReadConsoleInput");

	// Dispatch the events to the appropriate handler. 

	switch (irInBuf[0].EventType)
	{
	case KEY_EVENT: // keyboard input 
		keyPressed = KeyEvent(irInBuf[0].Event.KeyEvent);
		break;
	case MOUSE_EVENT: // mouse input 
		//MouseEventProc(irInBuf[i].Event.MouseEvent);
	case WINDOW_BUFFER_SIZE_EVENT: 
	case FOCUS_EVENT:  // disregard focus events 
	case MENU_EVENT:   // disregard menu events 
		keyPressed = 0;
		break;
	default:
		ErrorExit("Unknown event type");
		break;
	}
		
	return keyPressed;
}