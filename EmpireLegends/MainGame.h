#pragma once
#include "BiddingFacility.h"
#include "Cards.h"
#include "GameObserver.h"

class PlayerRotation
{
	vector<Player*>::iterator current;

public:
	vector<Player*> players;
	explicit PlayerRotation(const vector<Player*>& players);
	~PlayerRotation();
	void rotate();
	Player* getCurrentPlayer();
	int getNbPlayers();
};

class MainGame : public Observable
{
	GameMap* map;
	Deck* deck;
	PlayerRotation* players;
	vector<Card*> cardDeck;
	string state;
	Player* startPlayerTurn(const Player* player);
	void SetupEndGame();

public:

	explicit MainGame(GameMap* map, Deck* deck, vector<Player*>& players);
	~MainGame();
	void afterAction();
	Player* getCurrentPlayer();
	void mainGameloop(int numOfTurns);
	int pickACard();
	void chooseWinner();
	string getState() { return state; };
};

class MainGameObserver : public Observer
{
public:
	MainGameObserver(MainGame* s);
	~MainGameObserver();
	void Update() override;
	void display();
private:
	MainGame* subject;
};
