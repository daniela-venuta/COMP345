#pragma once
#include "GameStart.h"
#include "StartingPhase.h"
#include "MainGame.h"

class GameEngine {

private:
	GameStart* gameStart; 
	GameMap* gameMap;
	MainGame* mainGame; 
	StartingPhase* startPhase;
	Deck* deck;

public:
	GameEngine();
	~GameEngine(); 
	Deck* setDeck();
	void singleMode();
	void tournamentMode(); 
	//int numOfTurns(int size); 
};
