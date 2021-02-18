#pragma once

#include <string>
#include <vector>
#include "BiddingFacility.h"

using std::string;


class Player
{
private: 
	BiddingFacility* BidFacility; 
	string name;


public:
	Player();
	
	Player(string username, int coins);
	
	~Player();

	string getName();

};
	