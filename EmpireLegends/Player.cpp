#include "Player.h"
#include "StartingPhase.h"
#include "Map.h"
#include "Cards.h"
#include <algorithm>
#include <vector>
#include <iostream>

#include "MapUtility.h"

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
	playerHand = new Hand();
}

string Player::getName() const {
	return playerName;
}

void Player::setName(string Name) {
	playerName = Name;
}

int Player::getCoins() const {
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
void Player::payCoin(const int price)
{
	if (price > -1 && (pResources->totalCoins - price) >= 0)
	{
		setBalance(pResources->totalCoins - price);
		std::cout << "Removed " << price << " coins from player total." << std::endl;
		std::cout << "New total: " << pResources->totalCoins << " coins" << std::endl;
	}
	else
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

/// <summary>
/// Takes care of changes that come from moving Armies
/// *** Since the travel cost is computed by the GameMap, MoveOverLand and MoveOverWater are in this method.
/// </summary>
/// <param name="number"></param>
/// <param name="from"></param>
/// <param name="to"></param>
/// <param name="map"></param>
void Player::moveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	// check that the action is performable
	if (number > 0 && number < pResources->unplacedArmies && map->getTravelCost(from, to) > 0)
	{
		if (from->removeArmies(number, this) && to->addArmies(number, this))
		{
			std::cout << "Moved " << number << " armies." << std::endl;
		} else
		{
			std::cout << "Could not perform action (MoveArmies)" << std::endl;
		}
	}
	else
	{
		std::cout << "Could not perform action (MoveArmies)" << std::endl;
	}
}

/// <summary>
/// Takes care of changes that come form Placing Armies
/// </summary>
/// <param name="number"></param>
/// <param name="location"></param>
void Player::placeNewArmies(int number, Territory<Region>* location, Territory<Region>* initialRegion)
{
	const bool ownsCity = std::find(playerTerritories.begin(), playerTerritories.end(), location) != playerTerritories.end();

	// check ownership of territory (can place ONLY if your own)
	if (number > 0 && pResources->unplacedArmies - number >= 0)
	{
		if (ownsCity || location == initialRegion)
		{
			pResources->unplacedArmies -= number;
			location->addArmies(number, this);
			std::cout << "You added " << number << " armies at " << location->getName() << std::endl;
		}
		else
		{
			std::cout << "You cannot add armies in " << location->getName() + " because you have no city in this region." << std::endl;
		}

	}
	else if (pResources->unplacedArmies - number < 0)
	{
		std::cout << "You do not have enough armies to perform this action (PlaceNewArmies)." << std::endl;
	}
	else
	{
		std::cout << "An error made it impossible to perform this action. (PlaceNewArmies)" << std::endl;
	}
}


/// <summary>
/// Takes cares of the changes that comes from Destroying Armies in a specific region
/// </summary>
/// <param name="number"></param>
/// <param name="location"></param>
/// <param name="player"></param>
void Player::destroyArmy(int number, Territory<Region>* location, Player* player)
{
	const bool ownsCity = std::find(playerTerritories.begin(), playerTerritories.end(), location) != playerTerritories.end();

	if (ownsCity || location->getTotalArmyCount() == 0)
	{
		std::cout << "Action not permissible (Destroy Armies at " << location->getName() << "). There is no army to destroy." << std::endl;
	}
	else if (location->getTotalArmyCount() - number > 0)
	{
		location->removeArmies(number, player);
		pResources->unplacedArmies += number;

		std::cout << "Successfully destroyed " << number << " armies owned by " << player->getName() << " at " << location->getName() << " ." << std::endl;
	}
	else
	{
		std::cout << "Action not permissible (Destroy Armies at " << location->getName() << "). There are not " << number << " armies to destroy " << std::endl;
	}
}


/// <summary>
/// Builds a city at the specified location
/// </summary>
/// <param name="location"></param>
void Player::buildCity(Territory<Region>* location)
{	
	if (location->getPlacedArmies(this) == 0)
	{
		std::cout << "Action not permissible (Build City at " << location->getName() << ")." << " You need at least 1 army in this region." << std::endl;
	}
	else if (pResources->unplacedCities - 1 >= 0 && TOTAL_NUM_CITIES - pResources->unplacedCities + 1 <= TOTAL_NUM_CITIES)
	{
		pResources->unplacedCities--;
		location->addCity(this);
		std::cout << "City built at " + location->getName() << std::endl;
	}
	else
	{
		std::cout << "Action not permissible (Build City at " << location->getName() << ")." << ". You don't have any city left to place or there is no more space for more cities in this region." << std::endl;
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

void Player::addCard(Card* card)
{
	playerHand->addCard(card);
	applyGood(card->getGood());
}

void Player::applyGood(Good* addedGood)
{
	addedGood->applyGood(pResources);
}

/// <summary>
/// Ask for Player for which action they will call
/// </summary>
/// <param name="cardTwoAction"></param>
/// <param name="gm"></param>
void Player::andOrAction(Card* card, GameMap* map) {

	Action* action1 = card->getAction();
	Action* action2 = card->getSecondAction();
	int option = 0;


	if (card->getAndOr() == AndOr::OR)
	{
		std::cout << "This card has two actions, " << *action1 << " and " << *action2 << std::endl;

		Action* chosenAction = nullptr;

		while (chosenAction == nullptr)
		{
			std::cout << "You must chose which action to use." << std::endl;
			std::cout << "Please enter the number next to the desired action:" << std::endl;
			std::cout << "1 : " << *action1 << std::endl;
			std::cout << "2 : " << *action2 << std::endl;
			std::cin >> option;

			if (std::cin.fail())
			{
				std::cout << "The value you entered isn't a valid option. Please input a valid option. \n(Make sure that it is an integer)" << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{

				switch (option) {
				case 1:
					chosenAction = action1;
					std::cout << "You have chosen " << *action1 << "." << std::endl;
					break;
				case 2:
					chosenAction = action2;
					std::cout << "You have chosen " << *action2 << "." << std::endl;
					break;
				default:
					std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
				}
			}
		}

		executeAction(chosenAction, map);
	}
	else if (card->getAndOr() == AndOr::AND)
	{
		std::cout << "This card has two actions, " << *action1 << " and " << *action2 << std::endl;

		executeAction(action1, map);
		executeAction(action2, map);
	} else
	{
		executeAction(action1, map);
	}
}

/// <summary>
/// Give the Player the ability to chose which region is affected by card action
/// </summary>
/// <param name="regions"></param>
/// <returns></returns>
Territory<Region>* Player::chooseTerritory(map<int, Territory<Region>*> regions)
{
	Territory<Region>* chosenRegion = nullptr;
	do
	{
		int optionChosen;
		std::cout << "Please enter the number associated to the wanted region: " << std::endl;

		std::cin >> optionChosen;

		if (std::cin.fail())
		{
			std::cout << "The value you entered isn't a valid option. Please input a valid option. \n(Make sure that it is an integer)" << std::endl;
			cin.clear();
		}
		else if (optionChosen > 0 && optionChosen <= regions.size())
		{
			chosenRegion = regions.at(optionChosen);
		}
		else
		{
			std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
		}

	} while (chosenRegion == nullptr);

	return chosenRegion;
}

void Player::executeAction(Action* action, GameMap* map)
{
	std::size_t build = action->getName().find("Build");
	std::size_t destroy = action->getName().find("Destroy");
	std::size_t place = action->getName().find("Place");
	std::size_t move = action->getName().find("Move");

	//Build City
	if (build != std::string::npos)
	{
		std::cout << "You may build a city in one of the regions with at least 1 army: " << std::endl;
		Territory<Region>* destination = chooseTerritory(MapUtility::printTerritoriesWithArmies(map, this));
		buildCity(destination);
	}
	//Move Armies
	else if (move != std::string::npos)
	{
		std::cout << "You may move" << action->getMultiplier() << " armies." << std::endl;
		std::cout << "Please choose the initial region: " << std::endl;

		Territory<Region>* from = chooseTerritory(MapUtility::printTerritoriesWithArmies(map, this));
		std::cout << "Please choose the destination region: " << std::endl;
		Territory<Region>* to = chooseTerritory(MapUtility::printTerritoriesWithMap(map));

		while (to == from)
		{
			std::cout << "Invalid. Please choose a destination other than the initial region: " << std::endl;
			to = chooseTerritory(MapUtility::printTerritoriesWithMap(map));
		}

		moveArmies(action->getMultiplier(), from, to, map);
	}
	//Destroy Armies
	else if (destroy != std::string::npos)
	{
		int numArmies = action->getMultiplier();
		std::cout << "You many destroy " << numArmies << " enemy armies. Please choose a region: \n";
		Territory<Region>* location = chooseTerritory(MapUtility::printTerritoriesWithEnemyArmies(map, this, numArmies));
		Player* enemyPlayer = chooseEnemy(location, numArmies);
		
		destroyArmy(numArmies, location, enemyPlayer);
	}
	//Place New Armies
	else if (place != std::string::npos)
	{
		// Place new army(ies) on the starting region or on a chosen region that has an owned city
		int numArmies = action->getMultiplier();
		std::cout << "You many place " << numArmies << " armies. Please choose a region: \n";
		Territory<Region>* destination = chooseTerritory(MapUtility::printTerritoriesWithMap(map));
		placeNewArmies(numArmies, destination, MapUtility::getStartingLocation(map));
	}
}

Player* Player::chooseEnemy(Territory<Region>* location, int numArmies)
{
	Player* choosePlayer = nullptr;
	vector<Player*> enemyPlayers;
	int num = 0;
	for (auto& armyPair : location->armies)
	{
		Player* player = armyPair.first;
		if (player != this && location->getPlacedArmies(player) >= numArmies)
		{
			++num;
			enemyPlayers.push_back(player);
			std::cout << num << "-" << player->getName() << std::endl;
		}
	}
	
	do
	{
		int optionChosen;
		std::cout << "Please enter the number associated to the wanted player " << std::endl;

		std::cin >> optionChosen;

		if (std::cin.fail())
		{
			std::cout << "The value you entered isn't a valid option. Please input a valid option. \n(Make sure that it is an integer)" << std::endl;
			cin.clear();
		}
		else if (optionChosen > 0 && optionChosen <= enemyPlayers.size())
		{
			choosePlayer = enemyPlayers.at(optionChosen -1);
		}
		else
		{
			std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
		}

	} while (choosePlayer == nullptr);

	return choosePlayer;
}
