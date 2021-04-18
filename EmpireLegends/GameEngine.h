#pragma once
#include "GameStart.h"
#include "StartingPhase.h"
#include "MainGame.h"

class GameEngine {

private:
	GameStart* gameStart; 
	MainGame* mainGame; 
	StartingPhase* startPhase;

public:
	GameEngine();
	~GameEngine(); 
	Deck* setDeck();
	void singleMode();
	void tournamentMode(); 
};
