#include "Player.h"

#include "Map.h"

#include <iostream>

using namespace std; 

//default constructor 
Player::Player() {

	pResources = new Resources();
	
	playerName = "";
	pResources = new Resources;
	pResources->totalCoins = 0;
}

// parametrized constructor
Player::Player(string name, int coins) {
	playerName = name;
	pResources = new Resources;
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
	pResources = new Resources;
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
	delete playerHand;
	pResources = nullptr;
	playerHand = nullptr;
}

Resources::Resources(const Resources& otherResources)
{
	this->totalCoins = otherResources.totalCoins;
	this->unplacedCities = otherResources.unplacedCities;
	this->unplacedArmies = otherResources.unplacedArmies;
	this->extraMoves = otherResources.extraMoves;
	this->extraArmies = otherResources.extraArmies;
	this->flying = otherResources.flying;
	this->elixir = otherResources.elixir;
	this->coinVPs = otherResources.coinVPs;
	this->setNameVPs = otherResources.setNameVPs;
	this->completeSetVPs = otherResources.completeSetVPs;
	this->immune = otherResources.immune;
}

Resources& Resources::operator=(const Resources& resources)
{
	this->totalCoins = resources.totalCoins;
	this->unplacedCities = resources.unplacedCities;
	this->unplacedArmies = resources.unplacedArmies;
	this->extraMoves = resources.extraMoves;
	this->extraArmies = resources.extraArmies;
	this->flying = resources.flying;
	this->elixir = resources.elixir;
	this->coinVPs = resources.coinVPs;
	this->setNameVPs = resources.setNameVPs;
	this->completeSetVPs = resources.completeSetVPs;
	this->immune = resources.immune;

	return *this;
}

// Copy constructor
Player::Player(const Player& otherPlayer)
{
	this->playerName = otherPlayer.playerName;
	this->pResources = new Resources;
	*this->pResources = *otherPlayer.getResources();
}

// Assignment operator
Player& Player::operator=(const Player& player)
{
	this->setName(player.getName());
	this->pResources = new Resources;
	*this->pResources = *player.getResources();

	return *this;
}

// Stream insertion operator overload
ostream& operator<<(ostream& os, const Player& player)
{
	string s = "The following player remains in the game";

	s += player.getName() + " ";
	os << s << std::endl;

	return os;
}

ostream& operator>>(ostream& os, const Player& player)
{
	string s = "The following player remains in the game";

	s += player.getName() + " ";
	os << s << std::endl;

	return os;
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
int Player::moveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	// check that destination territory is valid (graph traversal + valid travel points)
	GameMap gameMap = *map;
	int travelCost = gameMap.getTravelCost(from, to);
	std::cout << "This action will cost " << travelCost << " travel points" << std::endl;
	return travelCost;
	// check that travel points in cards are sufficient to move to destination
}

// Move specified number of armies from one territory to another
void Player::moveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	// check that you can call MoveOverLand with the given territories
	if (number > 0 && number < pResources->unplacedArmies && moveOverLand(from, to, map) > 0)
	{
		from->removeArmies(number, this);
		to->addArmies(number, this);
		std::cout << "Moved " << number << " armies." << std::endl;
	} else
	{
		std::cout << "Could not perform action (MoveArmies)" << std::endl;
	}
}

// Place armies at the specified location
void Player::placeNewArmies(int number, Territory<Region>* location)
{
	const int unplacedArmies = pResources->unplacedArmies;
	// check ownership of territory (can place ONLY if your own)
	if (number > 0 && unplacedArmies - number >= 0 && (TOTAL_NUM_ARMIES - unplacedArmies + number) <= TOTAL_NUM_ARMIES)
	{
		pResources->unplacedArmies -= number;
		location->addArmies(number, this);
		std::cout << "Added " << number << " armies at " << location->getName() << std::endl;
	} else
	{
		std::cout << "You do not have enough armies to perform this action (PlaceNewArmies)." << std::endl;
	}
}

// Destroy all enemy armies found at the specified location
void Player::destroyArmy(int number, Territory<Region>* location, Player* player)
{
	// check that there are other armies at the specified location
	// destroy specified number of armies found at the specified location
	// identify original owner of territory and reduce number of placedArmies > increase number of unplacedArmies
	if (number > 0 && location->getTotalArmyCount() - number > 0)
	{
		location->removeArmies(number, player);
		pResources->unplacedArmies += number;
		
		std::cout << "Successfully destroyed " << number << " armies owned by" << player->getName() <<  " at " << location->getName() << " ." << std::endl;
	} else
	{
		std::cout << "Action not permissible (DestroyArmies at " << location->getName() << ")" << std::endl;
	}
}

// Builds a city at the specified location
void Player::buildCity(Territory<Region>* location)
{
	// check ownership of region (MUST HAVE AT LEAST ONE ARMY THERE)
	const int unplacedCities = pResources->unplacedCities;
	if (unplacedCities - 1 >= 0 && (TOTAL_NUM_CITIES - unplacedCities + 1) <= TOTAL_NUM_CITIES && location->getTotalArmyCount() > 0)
	{
		pResources->unplacedCities -= 1;
		// add city at specified location
		std::cout << "Built a city at " << location->getName() << std::endl;
	} else if (pResources->unplacedCities - 1 < 0 || (TOTAL_NUM_CITIES - unplacedCities + 1) > TOTAL_NUM_CITIES)
	{
		std::cout << "This action is not permissible (BuildCity)." << std::endl;
	}
}

void Player::addOwnedTerritory(Territory<Region>* territory)
{
	const auto itr = std::find(playerTerritories.begin(), playerTerritories.end(), territory);

	// Add to the vector only when it's not already present
	if (itr == playerTerritories.end())
	{
		playerTerritories.push_back(territory);
		std::cout << this->getName() << " now owns " << territory->getName() << "." << std::endl;
	}
}

void Player::removeOwnedTerritory(Territory<Region>* territory)
{
	const auto itr = std::find(playerTerritories.begin(), playerTerritories.end(), territory);

	// Remove from the vector only when it's present
	if (itr != playerTerritories.end())
	{
		playerTerritories.erase(itr);
		std::cout << this->getName() << " loses ownership over " << territory->getName() << "." << std::endl;
	}
}

Resources* Player::getResources() const
{
	return pResources;
}
