#include "Player.h"
#include "Map.h"
#include <algorithm>

#include <iostream>

using namespace std; 


//default constructor 
Player::Player() {
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

int Player::getId() const
{
	return playerId;
}

void Player::setId() 
{
	idGenerator += 1;
	playerId = idGenerator;
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
	setId();
	
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
		std::cout << "Removed " << price << " coins from "+ getName() + "'s total." << std::endl;
		std::cout << "New total of coins of " + getName() + ": " << pResources->totalCoins << " coins" << std::endl;
	} else
	{
		std::cout << getName() + " cannot perform this action (PayCoin)." << std::endl;
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
	return travelCost;
	// check that travel points in cards are sufficient to move to destination
}

// Move specified number of armies from one territory to another
void Player::MoveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	// check that you can call MoveOverLand with the given territories
	int cost = MoveOverLand(from, to, map);
	int numOfArmy = 0;
	for (auto it : playerArmies) {
		if (it->getName()==from->getName())
		{
			numOfArmy++;
		}
	}

	if (number > 0 && number <= pResources->unplacedArmies && cost > 0)
	{		
		if (cost <= getCoins() && numOfArmy > 0)
		{
			from->removeArmies(number);
			to->addArmies(number);
			int count = 0;
			for (int it = 0; count != number && it<playerArmies.size(); ++it) {
				if (playerArmies[it]->getName() == from->getName())
				{
					playerArmies[it] = to;
					count++;
				}
			}
			std::cout << "This action will cost " << cost << " travel points" << std::endl;
			std::cout << getName() + " moved " << number << " armies." << std::endl;
		}
		else
		{
			std::cout << getName() + " couldn't move any armies due to a lack of coins or of armies" << std::endl;
		}

	}
	else
	{
		std::cout << "An error made it impossible to perform this action. (MoveArmies)" << std::endl;
	}
}

// Place armies at the specified location
void Player::PlaceNewArmies(int number, Territory<Region>* location)
{
	int unplacedArmies = pResources->unplacedArmies;
	bool ownsCity = false;

	for (auto value : playerTerritories)
	{
		if (location->getName() == value->getName())
		{
			ownsCity = true;
			break;
		}
	}

	// check ownership of territory (can place ONLY if your own)
	if (number > 0 && (unplacedArmies - number) >= 0)
	{

		if (ownsCity == true || location->getName() == originRegion)
		{
		    pResources->unplacedArmies -= number;
			location->addArmies(number);
			playerArmies.push_back(location);
			std::cout << getName() + " added " << number << " armies at " << location->getName() << std::endl;
		}
		else
		{
			std::cout << getName() + " cannot add armies at " << location->getName() + " because they have no city in this region." << std::endl;
		}

	}
	else if (unplacedArmies - number < 0)
	{
		std::cout << getName() + " does not have enough armies to perform this action (PlaceNewArmies)." << std::endl;
	}
	else
	{
		std::cout << "An error made it impossible to perform this action. (PlaceNewArmies)" << std::endl;
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
		int count = 0;
		for (auto it = 0; count <= number && it < playerArmies.size(); it++) {
			if (playerArmies[it]->getName() == location->getName())
			{
				playerArmies.erase(playerArmies.begin() + it);
				count += 1;
			}
		}
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
	// check ownership of region (MUST HAVE AT LEAST ONE OF YOUR ARMY THERE)
	const int unplacedCities = pResources->unplacedCities;
	bool haveOwnArmy = false;

	//auto check = *value;
	for (auto it : playerArmies) {
		if (it->getName() == location->getName())
		{
			haveOwnArmy = true;
			break;
		}
	}
	

	if (haveOwnArmy && unplacedCities - 1 >= 0 && (TOTAL_NUM_CITIES - unplacedCities + 1) <= TOTAL_NUM_CITIES && location->getArmyCount() > 0)
	{
		pResources->unplacedCities -= 1;
		// add city at specified location

		playerTerritories.push_back(location);

		std::cout << getName() + " built a city at " + location->getName() << std::endl;
	}
	else if (pResources->unplacedCities - 1 < 0 || (TOTAL_NUM_CITIES - unplacedCities + 1) > TOTAL_NUM_CITIES)
	{
		std::cout << "This action is not permissible due to errors (BuildCity)." << std::endl;
	}
	else
	{
		std::cout << getName() + " cannot built a city at " + location->getName() + " due to not having an army in this region." << std::endl;
	}
}

Resources* Player::getResources() const
{
	return pResources;
}

int Player::getNumofcards() {
	return NumCards;
}

void Player::setNumofcards() {
	NumCards++;
}

vector<Good*> Player::getListGoods()
{
	return playerGoods;
}

void Player::addGoods(Good* addedGood)
{
	playerGoods.push_back(addedGood);
}

//Give player the possible actions within their turn if they have an "And/Or" card
string Player::AndOrAction(Card* cardTwoAction) {

	string action1 = cardTwoAction->getAction();
	string action2 = cardTwoAction->getSecondAction();
	int option = 0;
	string chosenAction = "";

	if (action2 == "")
	{
		std::cout << "Error: The card entered isn't a card with two actions." << std::endl;
		return  chosenAction;
	}

	std::cout << "This card has two actions, " + action1 + " and " + action2 << std::endl;

	do
	{
		std::cout << "Please enter the number next to the action you would like to do :" << std::endl;
		std::cout << "1 : " + action1 << std::endl;
		std::cout << "2 : " + action2 << std::endl;
		std::cin >> option;

		switch (option) {
		case 1:
			chosenAction = action1;
			break;
		case 2:
			chosenAction = action2;
			break;
		default:
			std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
		}

	} while (chosenAction == "");


	if (chosenAction == "Build City")
	{
		std::cout << getName() + " have chosen to build a city." << std::endl;
	}
	else if (chosenAction == "Move Armies")
	{
		std::cout << getName() + " have chosen to move your armies." << std::endl;
	}
	else if (chosenAction == "Destroy Army")
	{
		std::cout << getName() + " have chosen to destroy an army" << std::endl;
	}
	else if (chosenAction == "Place New Armies")
	{
		std::cout << getName() + " have chosen to place new armies" << std::endl;
	}

	return chosenAction;
}
