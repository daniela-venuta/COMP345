#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include "Player.h"
#include "MapUtility.h"
#include "PlayerStrategies.h"

using namespace std;

//default constructor 
Player::Player() {
	playerName = "";
	pResources = new Resources;
	pResources->unplacedArmies = TOTAL_NUM_ARMIES;
	pResources->unplacedCities = TOTAL_NUM_CITIES;
	pResources->totalCoins = 0;
	strategy = nullptr;
}

// parametrized constructor
Player::Player(string name, int coins, PlayerStrategy* strategy) {
	playerName = std::move(name);
	pResources = new Resources;
	pResources->totalCoins = coins;
	pResources->unplacedArmies = TOTAL_NUM_ARMIES;
	pResources->unplacedCities = TOTAL_NUM_CITIES;
	playerHand = new Hand();
	this->strategy = strategy;
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

void Player::setStrategy(PlayerStrategy* strategy)
{
	std::cout << playerName << " - setting strategy to " << *strategy << std::endl;
	this->strategy = strategy;
}

PlayerStrategy* Player::getStrategy()
{
	return this->strategy;
}

Player::Player(const string username, PlayerStrategy* strategy)
{
	// verify that this is not a duplicate username for the current players in game
	setName(username);
	pResources = new Resources;
	// set player resources to default values
	pResources->totalCoins = DEFAULT_NUM_COINS;
	pResources->unplacedCities = TOTAL_NUM_CITIES;
	pResources->unplacedArmies = TOTAL_NUM_ARMIES;
	
	this->strategy = strategy;

	// define a bidingFacility
	std::cout << "Created new player: " << getName() << std::endl;
}

Player::~Player()
{
	delete pResources;
	delete playerHand;
	delete strategy;
	pResources = nullptr;
	playerHand = nullptr;
	strategy = nullptr;
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

int Player::geNumOfOwnedCard()
{
	return numOwnedCard;
}

/// <summary>
/// Takes care of changes that come from moving Armies
/// *** Since the travel cost is computed by the GameMap, MoveOverLand and MoveOverWater are in this method.
/// </summary>
/// <param name="number"></param>
/// <param name="from"></param>
/// <param name="to"></param>
/// <param name="map"></param>
bool Player::moveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	bool moveDone = false;

	// check that the action is performable
	if (number > 0 && number < pResources->unplacedArmies && map->getTravelCost(from, to) > 0)
	{
		if (from->removeArmies(number, this) && to->addArmies(number, this))
		{
			moveDone = true;
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

	return moveDone;
}

/// <summary>
/// Takes care of changes that come form Placing Armies
/// </summary>
/// <param name="number"></param>
/// <param name="location"></param>
bool Player::placeNewArmies(int number, Territory<Region>* location, Territory<Region>* initialRegion)
{
	bool placeDone = false;

	const bool ownsCity = std::find(playerTerritories.begin(), playerTerritories.end(), location) != playerTerritories.end();

	// check ownership of territory (can place ONLY if your own)
	if (number > 0 && pResources->unplacedArmies - number >= 0)
	{
		if (ownsCity || location == initialRegion)
		{
			pResources->unplacedArmies -= number;
			location->addArmies(number, this);
			placeDone = true;
			int newArmyCount = this->geNumOfOwnedCard() + number;
			this->setNumArmy(newArmyCount);
			std::cout << playerName << " added " << number << " armies at " << location->getName() << std::endl;
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

	return placeDone;
}


/// <summary>
/// Takes cares of the changes that comes from Destroying Armies in a specific region
/// </summary>
/// <param name="number"></param>
/// <param name="location"></param>
/// <param name="player"></param>
bool Player::destroyArmy(int number, Territory<Region>* location, Player* player)
{
	bool destroyDone = false;


	if (location->getTotalArmyCount() == 0)
	{
		std::cout << "Action not permissible (Destroy Armies at " << location->getName() << "). There is no army to destroy." << std::endl;
	}
	else if (location->getTotalArmyCount() - number > 0)
	{
		location->removeArmies(number, player);
		pResources->unplacedArmies += number;
		destroyDone = true;
		int newArmyCount = player->geNumOfOwnedCard() - number;
		player->setNumArmy(newArmyCount);
		std::cout << "Successfully destroyed " << number << " armies owned by " << player->getName() << " at " << location->getName() << " ." << std::endl;
	}
	else
	{
		std::cout << "Action not permissible (Destroy Armies at " << location->getName() << "). There are not " << number << " armies to destroy " << std::endl;
	}
	
	return destroyDone;
}


/// <summary>
/// Builds a city at the specified location
/// </summary>
/// <param name="location"></param>
bool Player::buildCity(Territory<Region>* location)
{
	bool buildDone = false;
	if (location->getPlacedArmies(this) == 0)
	{
		std::cout << "Action not permissible (Build City at " << location->getName() << ")." << " You need at least 1 army in this region." << std::endl;
	}
	else if (pResources->unplacedCities - 1 >= 0 && TOTAL_NUM_CITIES - pResources->unplacedCities + 1 <= TOTAL_NUM_CITIES)
	{
		pResources->unplacedCities--;
		location->addCity(this);
		buildDone = true;
		std::cout << "City built at " + location->getName() << std::endl;
	}
	else
	{
		std::cout << "Action not permissible (Build City at " << location->getName() << ")." << ". You don't have any city left to place or there is no more space for more cities in this region." << std::endl;
	}

	return buildDone;
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
	numOwnedCard += 1;
	playerHand->addCard(card);
	applyGood(card->getGood());
}

// Tally card types
void Player::countCardTypes() {
	for (Card* card : playerHand->getCards()) {
		if (card->getName().find(CardSetMap::getString(CardSet::forest)) != string::npos) {
			forestCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::dire)) != string::npos) {
			direCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::ancient)) != string::npos) {
			ancientCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::noble)) != string::npos) {
			nobleCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::mountain)) != string::npos) {
			mountainCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::arcane)) != string::npos) {
			arcaneCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::cursed)) != string::npos) {
			cursedCards++;
		}
		if (card->getName().find(CardSetMap::getString(CardSet::night)) != string::npos) {
			nightCards++;
		}
	}
}

// Compute Victory Points (VPs)
int Player::computeScore() {
	// 1VP per owned region
	victoryPoints += playerTerritories.size();

	// 1VP per 3 coins
	int totalCoins = getResources()->totalCoins;

	if (getResources()->coinVPs) {
		victoryPoints += (totalCoins / 3);
	}
	
	// VP for set names
	for (auto& set : getResources()->setNameVPs) {
		// if boolean is TRUE
		if (set.second) {
			// allocate VP per card type
			switch (set.first) {
				case CardSet::forest:
					victoryPoints += forestCards;
					break;
				case CardSet::dire:
					victoryPoints += direCards;
					break;
				case CardSet::ancient:
					victoryPoints += ancientCards;
					break;
				case CardSet::noble:
					victoryPoints += nobleCards;
					break;
				case CardSet::mountain:
					victoryPoints += mountainCards;
					break;
				case CardSet::arcane:
					victoryPoints += arcaneCards;
					break;
				case CardSet::cursed:
					victoryPoints += cursedCards;
					break;
				case CardSet::night:
					victoryPoints += nightCards;
					break;
				default:
					victoryPoints;
			}
		}
	}

	//VP for complete sets
	for (auto& set : getResources()->completeSetVPs) {
		// if boolean is TRUE
		if (set.second) {
			// allocate VP per complete set
			switch (set.first) {
			case CardSet::forest:
				victoryPoints += 1;
				break;
			case CardSet::dire:
				victoryPoints += 1;
				break;
			case CardSet::ancient:
				victoryPoints += 1;
				break;
			case CardSet::noble:
				victoryPoints += 4;
				break;
			case CardSet::mountain:
				victoryPoints += 3;
				break;
			case CardSet::arcane:
				victoryPoints += 1;
				break;
			case CardSet::cursed:
				victoryPoints += 1;
				break;
			case CardSet::night:
				victoryPoints += 1;
				break;
			default:
				victoryPoints;
			}
		}
	}

	return victoryPoints;
}

void Player::addVictoryPoints(int pts) {
	victoryPoints += pts;
}

int Player::getVictoryPoints() {
	return victoryPoints;
}

vector < Territory<Region>*> Player::getTerritories() {
	return playerTerritories;
}

int Player::getNumArmy()
{
	return numArmy;
}

void Player::setNumArmy(int num)
{
	numArmy = num;
}

void Player::applyGood(Good* addedGood)
{
	addedGood->applyGood(pResources);
}



/// <summary>
/// Ask for Player for which action they will call
/// </summary>
/// <param name="card"></param>
/// <param name="map"></param>
bool Player::andOrAction(Card* card, GameMap* map) {

	bool actionDone = false;
	if (strategy == nullptr)
	{
		std::cout << "Cannot execute action(s). Player has no strategy." << std::endl;
		return false;
	}

	Action* action1 = card->getAction();
	Action* action2 = card->getSecondAction();

	if (card->getAndOr() == AndOr::OR)
	{
		std::cout << "This card has two actions, " << *action1 << " and " << *action2 << std::endl;

		Action* chosenAction = strategy->chooseAction(action1, action2);
		std::cout << std::endl << playerName << " chose: " << chosenAction->getName() << std::endl;

		actionDone = strategy->executeAction(chosenAction, this, map);
	}
	else if (card->getAndOr() == AndOr::AND)
	{
		bool a1, a2;
		a1 = a2 = false;
		std::cout << std::endl << "This card has two actions, " << *action1 << " and " << *action2 << std::endl;

		a1 = strategy->executeAction(action1, this, map);
		a2 = strategy->executeAction(action2, this, map);
		if (a1 == a2)
		{
			actionDone = true;
		}
	} else
	{
		actionDone = strategy->executeAction(action1, this, map);
	}
	return actionDone;
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
		std::vector<Player*, std::allocator<Player*>>::size_type optionChosen = 0;
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
