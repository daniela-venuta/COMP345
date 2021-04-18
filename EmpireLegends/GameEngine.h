#pragma once
#include "GameStart.h"
#include "StartingPhase.h"
#include "MainGame.h"

class GameEngine {

private:
	Deck* deck; 
	GameStart* gameStart; 
	MainGame* mainGame; 
	StartingPhase* startPhase;

	void setDeck();


public:
	GameEngine();
	~GameEngine(); 
	void singleMode();
	void tournamentMode(); 
};
