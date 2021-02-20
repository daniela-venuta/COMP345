#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>

using namespace std; 

//default constructor 
Player::Player() {
	playerName = playerName;
	totalCoins = totalCoins;
}

// parametrized constructor
Player::Player(string username, int PlayerCoins) {
	playerName = username;
	totalCoins = PlayerCoins;
	Bidding = new BiddingFacility();
}

string Player::getName() {
	return playerName;
}

void Player::setName(string Name) {
	playerName = Name;
}

int Player::getCoins(){
	return totalCoins;
}
void Player::setCoins(int coins) {
	totalCoins = coins;
}

BiddingFacility* Player::getBidFac() {
	return Bidding;
}



