#pragma once
#include "GameStart.h"

class GameEngine {
private:
	GameStart* gameStart; 
	GameMap* gameMap; 

public:
	GameEngine();
	void singleMode();
	void tournamentMode(); 
};
