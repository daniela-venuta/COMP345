#pragma once
#include <string>
#include <vector>
#include "Player.h"

class BiddingFacility {

	static int bid;
	static std::map<Player*, int> bids;

	static void addPlayerBid(Player* player, int playerBid);
	static int getPlayerBid(Player* player);
	// default constructor 
	BiddingFacility() = default;

public:
	
	static void placeBids(vector <Player*> biddingPlayers);
	static int getCurrentBid();
	static void setCurrentBid(int bid);
};