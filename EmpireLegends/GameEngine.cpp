#include "GameEngine.h"

#include <iostream>

GameEngine::GameEngine()
{
	 gameStart = nullptr;
	// gameMap = nullptr;
}

GameEngine::~GameEngine()
{

}

void GameEngine::singleMode()
{
	std::cout << "\n-------------------" << std::endl;
	std::cout << "Single Game Mode" << std::endl; 
	std::cout << "------------------" << std::endl;
	//gameStart->loadMap(); 
}

void GameEngine::tournamentMode()
{
	std::cout << "\n----------------------" << std::endl;
	std::cout << "Tournament Game Mode" << std::endl;
	std::cout << "----------------------" << std::endl;
	gameStart->loadMap();
}
	