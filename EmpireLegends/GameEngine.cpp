#include "GameEngine.h"

#include <iostream>

GameEngine::GameEngine()
{
	 gameStart = nullptr;
	 gameMap = nullptr;
}

void GameEngine::singleMode()
{
	std::cout << "\n-------------------" << std::endl;
	std::cout << "Single Game Mode" << std::endl; 
	std::cout << "------------------" << std::endl;
	
	gameStart->loadMap(); // throws an error
	gameStart->detPlayerCount(); // throws an error
}

void GameEngine::tournamentMode()
{
	std::cout << "\n----------------------" << std::endl;
	std::cout << "Tournament Game Mode" << std::endl;
	std::cout << "----------------------" << std::endl;
	
	gameStart->loadMap(); // throws an  error
	gameStart->detPlayerCount(); // throws an error
}
