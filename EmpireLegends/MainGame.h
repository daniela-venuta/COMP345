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
	Deck* deck;
	vector<Card*> cardDeck;
	string state;
	void startPlayerTurn(const Player* player);
	void SetupEndGame();

public:
	GameMap* map;
	PlayerRotation* players;
	explicit MainGame(GameMap* map, Deck* deck, vector<Player*>& players);
	~MainGame();
	void afterAction();
	Player* getCurrentPlayer();
	void mainGameloop(int numOfTurns);
	int pickACard();
	int botPickACard();
	void chooseWinner();
	bool doAction(Card* card, Player* player);
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

class GameStatisticsObserver : public Observer
{
public:
	GameStatisticsObserver(MainGame* s);
	~GameStatisticsObserver();
	void Update() override;
	void display();
private:
	MainGame* subject;
};
