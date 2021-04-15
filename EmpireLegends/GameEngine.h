#pragma once
#include "GameStart.h"

class GameEngine {

private:
	GameStart* gameStart; 


public:
	GameEngine();
	~GameEngine(); 
	void singleMode();
	void tournamentMode(); 
};
