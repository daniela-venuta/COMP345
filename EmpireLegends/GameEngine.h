#pragma once
#include "GameStart.h"

class GameStart; 

class GameEngine {

private:
	
	GameStart* gameStart; 
	GameMap* gameMap; 

public:
	GameEngine();
	~GameEngine(); 
	void singleMode();
	void tournamentMode(); 
};
