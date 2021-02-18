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
}

string Player::getName() {
	return name;
}

int Player::getCoins(){
	return coins; 
}

BiddingFacility* Player::getBidFacility() {
	return BiddingFac;
}