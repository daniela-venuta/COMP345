#pragma once
#include "BiddingFacility.h"
#include "Cards.h"

class PlayerRotation
{
	vector<Player*> players;
	vector<Player*>::iterator current;

public:

	explicit PlayerRotation(const vector<Player*>& players);
	void rotate();
	Player* getCurrentPlayer();

};

class MainGame
{
	BiddingFacility* biddingFacility;
	GameMap* map;
	Deck* deck;
	PlayerRotation* players;
	vector<Player*> myPlayers;
	vector<Card*> cardDeck; 

public:

	explicit MainGame(BiddingFacility* biddingFacility, GameMap* map, Deck* deck, vector<Player*> players);
	void afterAction();
	Player* getCurrentPlayer();
	void PlayerFaceCard(Card* facecard, Player* myPlayers);
	void maingameloop(vector<Card*> cardDeck, vector<Player*> myPlayers);
	int PickACard();
};