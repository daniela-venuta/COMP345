#pragma once

#include <string>
#include <vector>
#include "BiddingFacility.h"


using std::string;


class Player
{
private: 
	BiddingFacility* BidFacility; 


public:
	Player();
	
	Player(string username, int coins);
	
	~Player();
	
	
};
	