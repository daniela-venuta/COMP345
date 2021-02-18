#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>

using namespace std; 


//default constructor 
Player::Player() {
	BidFacility = new BiddingFacility(); 
}

Player::Player(string username, int PlayerCoins) {
	BidFacility = new BiddingFacility();
}

string Player::getName() {
	return name; 
}
