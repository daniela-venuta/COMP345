#pragma once
#include "BiddingFacility.h"
#include "Cards.h"

class PlayerRotation
{
	vector<Player*> players;
	vector<Player*>::iterator current;

public:
	
	explicit PlayerRotation(const vector<Player*>& players);
	~PlayerRotation();
	void rotate();
	Player* getCurrentPlayer();
	int getNbPlayers();

};

class MainGame
{
	GameMap* map;
	Deck* deck;
	PlayerRotation* players;
	vector<Card*> cardDeck;

public:

	explicit MainGame(GameMap* map, Deck* deck, vector<Player*>& players);
	~MainGame();
	void afterAction();
	Player* getCurrentPlayer();
	void mainGameloop(int numOfTurns);
	int pickACard();
};