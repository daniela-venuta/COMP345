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

	string state;
	
	GameMap* loadMap();
	vector<Player*> detPlayerCount();
	vector<Player*> detPlayerBotCount();
	vector<Player*> detBotCount();
	//vector<Player*> getPlayers();
	
//private:
	//int typeMap;
	//int numOfPlayers;
	//vector<Player*> players;
	//vector<Player*> biddingPlayers;
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