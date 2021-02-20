#include "Player.h"
#include "BiddingFacility.h"
#include "Map.h"
#include "MapUtility.h"
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

yer(const string username)
{
	// verify that this is not a duplicate username for the current players in game
	setName(username);
	totalCoins = 9;
	unplacedCities = 3;
	placedCities = 0;
	unplacedArmies = 18;
	placedArmies = 0;
	// define a bidingFacility
	std::cout << "Created new player: " << getName() << std::endl;
}

// Copy constructor
Player::Player(const Player& otherPlayer)
{
	setName(otherPlayer.playerName);
	this->totalCoins = otherPlayer.totalCoins;
	this->unplacedCities = otherPlayer.unplacedCities;
	this->placedCities = otherPlayer.placedArmies;
	this->unplacedArmies = otherPlayer.unplacedArmies;
	this->placedArmies = otherPlayer.placedArmies;
	// this.bidingFacility = otherPlayer.bidingFacility
}

// Stream insertion operator overload
ostream& operator<<(ostream& os, Player& player)
{
	string s = "The following player remains in the game";

	s += player.getName() + " ";
	os << s << std::endl;

	return os;
}

ostream& operator>>(ostream& os, Player& player)
{
	string s = "The following player remains in the game";

	s += player.getName() + " ";
	os << s << std::endl;

	return os;
}

// Assignment operator
Player& Player::operator=(Player& player)
{
	setName(player.playerName);
	this->totalCoins = player.totalCoins;
	this->unplacedCities = player.unplacedCities;
	this->placedCities = player.placedArmies;
	this->unplacedArmies = player.unplacedArmies;
	this->placedArmies = player.placedArmies;
	// this.bidingFacility = player.bidingFacility

	return *this;
}


// Player pays coins (to buy card)
void Player::PayCoin(const int price)
{
	if (price > 0 && (totalCoins - price) >= 0)
	{
		setBalance(totalCoins - price);
		std::cout << "Removed " << price << " coins from player total." << std::endl;
		std::cout << "New total: " << totalCoins << " coins" << std::endl;
	}
	else
	{
		std::cout << "Cannot perform this action (PayCoin)." << std::endl;
	}
}

// Get player balance
int Player::getBalance()
{
	return totalCoins;
}

// Set player balance
void Player::setBalance(int newBalance)
{
	totalCoins = newBalance;
}

// Player moves from one territory to another
int Player::MoveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	// check that destination territory is valid (graph traversal + valid travel points)
	GameMap gameMap = *map;
	int travelCost = gameMap.getTravelCost(from, to);
	std::cout << "This action will cost " << travelCost << " travel points" << std::endl;
	return travelCost;
	// check that travel points in cards are sufficient to move to destination
}

// Move specified number of armies from one territory to another
void Player::MoveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	// check that you can call MoveOverLand with the given territories
	if (number > 0 && number < unplacedArmies && MoveOverLand(from, to, map) > 0)
	{
		unplacedArmies = unplacedArmies - number;
		placedArmies = placedArmies + number;
		from->removeArmies(number);
		to->addArmies(number);
		std::cout << "Moved " << number << " armies." << std::endl;
	}
	else
	{
		std::cout << "Could not perform action (MoveArmies)" << std::endl;
	}
}

// Place armies at the specified location
void Player::PlaceNewArmies(int number, Territory<Region>* location)
{
	// check ownership of territory (can place ONLY if your own)
	if (number > 0 && unplacedArmies - number >= 0 && placedArmies + number <= 18)
	{
		unplacedArmies = unplacedArmies - number;
		placedArmies = placedArmies + number;
		location->addArmies(number);
		std::cout << "Added " << number << " armies at " << *location << std::endl;
	}
	else
	{
		std::cout << "You do not have enough armies to perform this action (PlaceNewArmies)." << std::endl;
	};
}

// Destroy all enemy armies found at the specified location
void Player::DestroyArmy(int number, Territory<Region>* location)
{
	// check that there are other armies at the specified location
	// destroy specified number of armies found at the specified location
	// identify original owner of territory and reduce number of placedArmies > increase number of unplacedArmies
	if (number > 0 && location->getArmyCount() - number > 0)
	{
		location->removeArmies(number);
		std::cout << "Successfully destroyed " << number << " armies at " << *location << " ." << std::endl;
	}
	else
	{
		std::cout << "Action not permissible (DestroyArmies at " << *location << ")" << std::endl;
	}
}

// Builds a city at the specified location
void Player::BuildCity(Territory<Region>* location)
{
	// check ownership of region (MUST HAVE AT LEAST ONE ARMY THERE)
	if (unplacedCities - 1 >= 0 && placedCities + 1 <= 3 && location->getArmyCount() > 0)
	{
		unplacedCities = unplacedCities - 1;
		placedCities = placedCities + 1;
		// add city at specified location
		std::cout << "Built a city at " << *location << std::endl;
	}
	else if ((unplacedCities - 1 < 0) || (placedCities + 1 > 3))
	{
		std::cout << "This action is not permissible (BuildCity)." << std::endl;
	};
}

