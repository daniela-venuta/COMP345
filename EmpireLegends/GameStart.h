#pragma once
#include "Player.h"
#include "BiddingFacility.h"

class GameStart
{
public:
	GameStart() = default;
	~GameStart() = default;

	GameMap* loadMap();
	vector<Player*> detPlayerCount();
	vector<Player*> detPlayerBotCount();
	vector<Player*> detBotCount();
	
};