#pragma once
#include "BiddingFacility.h"
#include <string>
#include <vector>

using std::string;

class Player
{
private: 
	
	string name;
	int coins; 
	BiddingFacility* Bidding;

public:

	Player();

	Player(string username, int coins);

	string getName();
	void setName(string name); 

	int getCoins(); 
	

	void setCoins(int coins); 

	BiddingFacility* getBidFac();

};
	