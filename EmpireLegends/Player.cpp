#include "Player.h"

#include "Map.h"
#include "Cards.h"
#include <algorithm>
#include <vector>
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
void Player::payCoin(const int price)
{
	if (price > -1 && (pResources->totalCoins - price) >= 0)
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
	return travelCost;
	// check that travel points in cards are sufficient to move to destination
}

// Move specified number of armies from one territory to another
void Player::MoveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map)
{
	
		int cost = MoveOverLand(from, to, map);
		int numOfArmy = 0;
		for (auto it : playerArmies) {
			if (it->getName() == from->getName())
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
				for (int it = 0; it < playerArmies.size(); ++it) {
					if (count == number)
					{
						break;
					}
					if (playerArmies[it]->getName() == from->getName())
					{
						playerArmies[it] = to;
						count++;
					}
				}
				std::cout << "This action will cost " << cost << " travel points" << std::endl;
				payCoin(cost);
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

		if (ownsCity == true || location->getName() == initialRegion)
		{
		    pResources->unplacedArmies -= number;
			location->addArmies(number);
			for (int i = 0; i < number; i++) 
			{
				playerArmies.push_back(location);
			}
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
void Player::DestroyArmy(int number, Territory<Region>* location, vector<Player*> currentPlayers)
{
	// check that there are other armies at the specified location
	// destroy specified number of armies found at the specified location
	// identify original owner of territory and reduce number of placedArmies > increase number of unplacedArmies
	int numOfYourArmy = 0;

	//auto check = *value;
	for (auto it : playerArmies) {
		if (it->getName() == location->getName())
		{
			numOfYourArmy += 1;
		}
	}


	int check = location->getArmyCount() - number;
	if (numOfYourArmy > 0 && number > 0 && numOfYourArmy >= check && check > 0)
	{
		location->removeArmies(number);
		
		int armyLost = 0;
		

		//std::cout << "Hewwo" << std::endl;
		vector<Player*> otherPlayer;

		for (int n = 0; n < currentPlayers.size(); n++) {
			if (currentPlayers[n]->getName() != getName())
			{
				otherPlayer.push_back(currentPlayers[n]);
			}
		}

		for (auto ennemi : otherPlayer) {
			
			std::cout << ennemi->getName() + " has currently " << ennemi->playerArmies.size() << " armies." << std::endl;
			for (int i = 0; i < ennemi->playerArmies.size(); i++)
			{
				auto armyToDestroy = ennemi->playerArmies[i];
				if (armyToDestroy->getName() == location->getName())
				{
					number -=1;
					armyLost +=1;
					ennemi->playerArmies.erase(ennemi->playerArmies.begin() + i);
					
					if (i > 0) 
					{
						i -= 1;
					}
					
				}
				if (number == 0)
				{
					break;
				}
			}

			
			std::cout << ennemi->getName() + " lost " << armyLost << " armies." << std::endl;
			std::cout << ennemi->getName() + " has now " << ennemi->playerArmies.size() << " armies." << std::endl;

			if (number == 0)
			{
				break;
			}
		
		}
		
	}
		
	else 
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

		playerTerritories.push_back( location);

		std::cout << getName() + " built a city at " + location->getName() << std::endl;
	}
	else  
	{
		std::cout << getName() +  " cannot built a city at " + location->getName() + " due to not having an army in this region \nor not having any funds to built a new city." << std::endl;
	}

}

Resources* Player::getResources() const
{
	return pResources;
}


void Player::applyGood(Good* addedGood)
{
	addedGood->applyGood(pResources);
}

//Give player the possible actions within their turn if they have an "And/Or" card
void Player::andOrAction(Card* cardTwoAction, GameMap* gm) {

	string action1 = cardTwoAction->getAction();
	string action2 = cardTwoAction->getSecondAction();
	int option = 0;
	string chosenAction = "";

	if (action2 == "")
	{
		std::cout << "Error: The card entered isn't a card with two actions." << std::endl;
		return;
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
			std::cout << getName() + " have chosen " + action1 +"." << std::endl;
			break;
		case 2:
			chosenAction = action2;
			std::cout << getName() + " have chosen " + action2 + "." << std::endl;
			break;
		default:
			std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
		}

	} while (chosenAction == "");

	bool check = false;
	int notpossible = 0;
	bool canBuild, canMove, canDestroy, canPlace;
	canBuild = canMove = canDestroy = canPlace = true;

	do 
	{
		if (chosenAction == "Build City")
		{
			if (canBuild == true) 
			{
				std::cout << "You have chosen to build a city." << std::endl;

				if (BuildCity() == true)
				{
					check = true;
				}
				else
				{
					canBuild = false;
					notpossible += 1;
				}
			}
			else 
			{
				std::cout <<"You have already tried to build a city, but something made it impossible to be done. Please choose another option"<< std::endl;
			}
			
		}

		else if (chosenAction == "Move Armies")
		{
			if (canMove == true)
			{
				std::cout << "You have chosen to move some armies." << std::endl;

				if (MoveArmies() == true)
				{
					check = true;
				}
				else
				{
					canMove = false;
					notpossible += 1;
				}
			}
			else
			{
				std::cout << "You have already tried to move some armies, but something made it impossible to be done. Please choose another option." << std::endl;
			}


		}

		else if (chosenAction == "Destroy Army" )
		{
			if (canDestroy == true)
			{
				std::cout << "You have chosen to destroy some armies." << std::endl;

				if (DestroyArmy() == true)
				{
					check = true;
				}
				else
				{
					canDestroy = false;
					notpossible += 1;
				}
			}
			else
			{
				std::cout << "You have already tried to move some armies, but something made it impossible to be done. Please choose another option." << std::endl;
			}
		}

		else if (chosenAction == "Place New Armies")
		{
			std::cout << "You have chosen to place new armies." << std::endl;
			check = PlaceNewArmies(gm);
		}

	} while (check != true);
	
}

bool Player::PlaceNewArmies(GameMap* gm)
{
	std::cout << getName() + ": You try to PLACE NEW ARMIES." << std::endl;
	if (pResources->unplacedArmies == 0)
	{
		std::cout << "Unfortunataly, you cannot build a city due to having no armies on the map \n or you don't have enough material left to build a city." << std::endl;
		return false;
	}

	vector<Territory<Region>*> possibleRegions;
	Territory<Region>* originPoint = gm->findTerritory("Continent 1")->value->findTerritory("Region 1");
	possibleRegions.push_back(originPoint);
	int options = 0;
	for (auto reg : playerArmies)
	{
		auto it = find(possibleRegions.begin(), possibleRegions.end(), reg);
		if (it == possibleRegions.end())
		{
			options += 1;
			possibleRegions.push_back(reg);
		}
	}

	int numOfArmies = 0;
	Territory<Region>* armyReg = nullptr;
	if (options == 1)
	{
		armyReg = possibleRegions.at(0);
		std::cout << "As there is only one option, the city must be built in " + armyReg->getName() + "." << std::endl;
	}
	else 
	{
		do
		{
			int optionChosen;
			std::cout << "Here are the possible regions where you could add armies:" << std::endl;
			for (int i = 0; i < possibleRegions.size(); i++)
			{
				string optNum = to_string(i + 1);
				std::cout << optNum + ": " + possibleRegions.at(i)->getName() + ";" << std::endl;
			}
			std::cout << "Please enter the number next to the region you wish to add armies to: " << std::endl;

			std::cin >> optionChosen;
			if (optionChosen > 0 && optionChosen <= options)
			{
				int index = optionChosen - 1;
				armyReg = possibleRegions.at(index);
			}
			else
			{
				std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
			}

		} while (armyReg == nullptr);

	}

	do 
	{
		std::cout << "Please enter the number of armies you wish to put within : (You have a maximum of " << pResources->unplacedArmies + ")." << std::endl;

		std::cin >> numOfArmies;
		if (numOfArmies <= 0 || numOfArmies > pResources->unplacedArmies)
		{
			std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
		}

	} while (numOfArmies <= 0 || numOfArmies > pResources->unplacedArmies);


	std::cout << getName() + " added " << numOfArmies << " armies at " << armyReg->getName() << std::endl;

	return true;
}

bool Player::MoveArmies()
{
	return true;
}

bool Player::DestroyArmy()
{
	return true;
}

bool Player::BuildCity()
{
	std::cout << getName() + ": You try to BUILD A CITY." << std::endl;
	if (playerArmies.empty()||pResources->unplacedCities == 0)
	{
		std::cout << "Unfortunataly, you cannot build a city due to having no armies on the map \n or you don't have enough material left to build a city." << std::endl;
		return false;
	}

	vector<Territory<Region>*> possibleRegions;
	int options = 0;
	for (auto reg : playerArmies)
	{
		auto it = find(possibleRegions.begin(), possibleRegions.end(), reg);
		if (it == possibleRegions.end())
		{
			options += 1;
			possibleRegions.push_back(reg);
		}
	}

	Territory<Region>* cityReg = NULL;
	if (options == 1)
	{
		cityReg = possibleRegions.at(0);
		std::cout << "As there is only one option, the city must be built in " + cityReg->getName() + "." << std::endl;
	}
	else 
	{
		do
		{
			int optionChosen;
			std::cout << "Here are the possible regions where you could build a city:" << std::endl;
			for (int i = 0; i < possibleRegions.size(); i++)
			{
				string optNum = to_string(i + 1);
				std::cout << optNum + ": " + possibleRegions.at(i)->getName() + ";" << std::endl;
			}
			std::cout << "Please enter the number next to the region you wish to build a city in: " << std::endl;

			std::cin >> optionChosen;
			if (optionChosen > 0 && optionChosen <= options)
			{
				int index = optionChosen - 1;
				cityReg = possibleRegions.at(index);
			}
			else
			{
				std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
			}

		} while (cityReg == nullptr);

		std::cout << "You have chosen to built the city in " + cityReg->getName() + "." << std::endl;
	
	}

	pResources->unplacedCities -= 1;
	// add city at specified location

	playerTerritories.push_back(cityReg);

	std::cout << getName() + " built a city at " + cityReg->getName() << std::endl;

	return true;
}
	
