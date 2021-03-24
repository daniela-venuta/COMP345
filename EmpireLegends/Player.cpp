#include "Player.h"

#include "Map.h"

#include <iostream>

using namespace std; 

//default constructor 
Player::Player() {

	pResources = new Resources();
	
	playerName = "";
	pResources->totalCoins = 0;
}

// parametrized constructor
Player::Player(string name, int coins) {
	playerName = name;
	pResources->totalCoins = coins;
}

string Player::getName() const{
	return playerName;
}

void Player::setName(string Name) {
	playerName = Name;
}

int Player::getCoins() const{
	return pResources->totalCoins;
}
void Player::setCoins(int coins) {
	pResources->totalCoins = coins;
}

Player::Player(const string username)
{
	// verify that this is not a duplicate username for the current players in game
	setName(username);

	// set player resources to default values
	pResources->totalCoins = TOTAL_NUM_COINS;
	pResources->unplacedCities = TOTAL_NUM_CITIES;
	pResources->unplacedArmies = TOTAL_NUM_ARMIES;
	
	// define a bidingFacility
	std::cout << "Created new player: " << getName() << std::endl;
}

Player::~Player()
{
	delete pResources;
	pResources = nullptr;
}

// Copy constructor
Player::Player(const Player& otherPlayer)
{
	const Resources* playerResources = otherPlayer.getResources();
	
	this->playerName = otherPlayer.playerName;
	this->pResources->totalCoins = playerResources->totalCoins;
	this->pResources->unplacedCities = playerResources->unplacedCities;
	this->pResources->unplacedArmies = playerResources->unplacedArmies;
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
Player& Player::operator=(const Player& player)
{
	const Resources* playerResources = player.getResources();
	
	setName(player.playerName);
	
	this->pResources->totalCoins = playerResources->totalCoins;
	this->pResources->unplacedCities = playerResources->unplacedCities;
	this->pResources->unplacedArmies = playerResources->unplacedArmies;

	return *this;
}

// Player pays coins (to buy card)
void Player::PayCoin(const int price)
{
	if (price > 0 && (pResources->totalCoins - price) >= 0)
	{
		setBalance(pResources->totalCoins - price);
		std::cout << "Removed " << price << " coins from player total." << std::endl;
		std::cout << "New total: " << pResources->totalCoins << " coins" << std::endl;
	} else
	{
		std::cout << "Cannot perform this action (PayCoin)." << std::endl;
	}
}

// Get player balance
int Player::getBalance() const
{
	return pResources->totalCoins;
}

// Set player balance
void Player::setBalance(int newBalance)
{
	pResources->totalCoins = newBalance;
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
	if (number > 0 && number < pResources->unplacedArmies && MoveOverLand(from, to, map) > 0)
	{
		from->removeArmies(number);
		to->addArmies(number);
		std::cout << "Moved " << number << " armies." << std::endl;
	} else
	{
		std::cout << "Could not perform action (MoveArmies)" << std::endl;
	}
}

// Place armies at the specified location
void Player::PlaceNewArmies(int number, Territory<Region>* location)
{
	const int unplacedArmies = pResources->unplacedArmies;
	// check ownership of territory (can place ONLY if your own)
	if (number > 0 && unplacedArmies - number >= 0 && (TOTAL_NUM_ARMIES - unplacedArmies + number) <= TOTAL_NUM_ARMIES)
	{
		pResources->unplacedArmies -= number;
		location->addArmies(number);
		std::cout << "Added " << number << " armies at " << location->getName() << std::endl;
	} else
	{
		std::cout << "You do not have enough armies to perform this action (PlaceNewArmies)." << std::endl;
	}
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
		pResources->unplacedArmies += number;
		
		std::cout << "Successfully destroyed " << number << " armies at " << location->getName() << " ." << std::endl;
	} else
	{
		std::cout << "Action not permissible (DestroyArmies at " << location->getName() << ")" << std::endl;
	}
}

// Builds a city at the specified location
void Player::BuildCity(Territory<Region>* location)
{
	// check ownership of region (MUST HAVE AT LEAST ONE ARMY THERE)
	const int unplacedCities = pResources->unplacedCities;
	if (unplacedCities - 1 >= 0 && (TOTAL_NUM_CITIES - unplacedCities + 1) <= TOTAL_NUM_CITIES && location->getArmyCount() > 0)
	{
		pResources->unplacedCities -= 1;
		// add city at specified location
		std::cout << "Built a city at " << location->getName() << std::endl;
	} else if (pResources->unplacedCities - 1 < 0 || (TOTAL_NUM_CITIES - unplacedCities + 1) > TOTAL_NUM_CITIES)
	{
		std::cout << "This action is not permissible (BuildCity)." << std::endl;
	}
}

Resources* Player::getResources() const
{
	return pResources;
}