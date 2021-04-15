#pragma once
#include "GameStart.h"
#include "StartingPhase.h"

class GameEngine {

private:
	GameStart* gameStart; 
	GameMap* gameMap;
	vector<Player*> players;
	StartingPhase* startPhase;
	Deck* deck;

public:
	GameEngine();
	~GameEngine(); 
	Deck* setDeck();
	void singleMode();
	void tournamentMode(); 
};
