#pragma once
#include "Player.h"
#include "BiddingFacility.h"
#include "GameObserver.h"

class GameStart : public Observable
{
public:
	GameStart();
	~GameStart();
	void startGame();
	void startSetup();
	string getState() { return state; };

	GameMap* loadMap();
	vector<Player*> detPlayerCount();
	vector<Player*> detPlayerBotCount();
	vector<Player*> detBotCount();
	string state;
private:
	
};

class GameStartObserver : public Observer
{
public:
	GameStartObserver(GameStart* s);
	~GameStartObserver();
	void Update() override;
	void display();

private:
	GameStart* subject;
};