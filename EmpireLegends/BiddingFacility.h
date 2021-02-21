#pragma once
#include <string>
#include <vector>
#include "Player.h"

class BiddingFacility {

	int bid;
	std::map<Player*, int> bids;

	void addPlayerBid(Player* player, int playerBid);
	int getPlayerBid(Player* player);

public:
	
	void placeBids(vector <Player*> biddingPlayers);
	int getCurrentBid() const;
	void setCurrentBid(int bid);

	// default constructor 
	BiddingFacility();

	// copy constructor
	BiddingFacility(const BiddingFacility& obj);

	// stream insertion operator 
	friend ostream& operator<<(ostream& output, const BiddingFacility& BDF);

	// Assignment operator
	BiddingFacility& operator=(const BiddingFacility& rhs);
};