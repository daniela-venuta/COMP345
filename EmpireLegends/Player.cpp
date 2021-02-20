#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>

using namespace std; 

//default constructor 
Player::Player() {
	name = name; 
	coins = coins;
}

Player::Player(string username, int PlayerCoins) {
	name = username; 
	coins = PlayerCoins;
	Bidding = new BiddingFacility();
}

string Player::getName() {
	return name;
}

void Player::setName(string Name) {
	name = Name; 
}

int Player::getCoins(){
	return coins; 
}
void Player::setCoins(int coins) {
	coins = coins; 
}

BiddingFacility* Player::getBidFac() {
	return Bidding;
}



