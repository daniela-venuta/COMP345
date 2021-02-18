#pragma once

#include <string>
#include <vector>

using std::string;

class Player
{
private: 
	
	string name;
	int coins; 
	BiddingFacility* BiddingFac;

public:
	Player();

	Player(string username, int coins);

	string getName();

	int getCoins(); 

	BiddingFacility* getBidFacility();

};
	