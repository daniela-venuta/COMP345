#pragma once
#include "Player.h"
#include "BiddingFacility.h"

class GameStart
{
public:
	GameStart();
	~GameStart();

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