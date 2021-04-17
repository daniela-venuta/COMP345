#pragma once
#include "Player.h"
#include "BiddingFacility.h"
#include "GameObserver.h"

class GameStart : public Observable
{
public:
	GameStart();
	~GameStart();

	void loadMap();
	void detPlayerCount();
	void startGame();

	string state;

private:
	int mapType;
	int numOfPlayers;
	vector<Player*> players;
	vector<Player*> biddingPlayers;
};

class GameStartView : public Observer
{
public:
	GameStartView(GameStart* s);
	~GameStartView();
	void Update() override;
	void display();
private:
	GameStart* subject;
};