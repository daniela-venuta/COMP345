#pragma once
#include "Player.h"
#include <string>
#include <vector>
using namespace std;

class BiddingFacility {

private: 
	int bidwinner; 

public: 

	// default constructor 
	BiddingFacility();

	// destructor 
	~BiddingFacility();

	// copy constructor
	BiddingFacility(const BiddingFacility& obj);

	// stream insertion operator 
	friend ostream& operator<<(ostream& output, const BiddingFacility& BDF);

	// Assignment operator
	BiddingFacility& operator=(const BiddingFacility& rhs);

	// method to place and compare bids per player
	int PlaceBid(vector <Player*> myPlayers);

	int getBids();
	
	void setBids(const int bids);

};