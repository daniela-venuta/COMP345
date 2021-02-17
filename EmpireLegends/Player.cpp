#include "Player.h"
#include "Map.h"

#include <iostream>

using std::cout;

//========= PLAYER METHODS =========//
// Instantiate a new Player object with a given player name
Player::Player(const string username)
{
	// verify that this is not a duplicate username for the current players in game
	playerName = username;
	totalCoins = 9;
	unplacedCities = 3;
	placedCities = 0;
	unplacedArmies = 18;
	placedArmies = 0;
	// define a bidingFacility
	cout << "Created new player: " << username;
}

// Player pays coins (to buy card)
void Player::PayCoin(const int price)
{
	if ((totalCoins - price) >= 0)
	{
		totalCoins = totalCoins - price;
		cout << "Removed " << price << "from player total.";
		cout << "New total: " << totalCoins << " coins";
	}
	else
	{
		cout << "Unsufficient funds.";
	}
}

// Player moves from one territory to another
int Player::MoveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap map)
{
	// check that destination territory is valid (graph traversal + valid travel points)
	int travelCost = map.getTravelCost(from, to);
	cout << "Moving from " << from << " to " << to << " will cost " << travelCost << " travel points";
	return travelCost;
	// check that travel points in cards are sufficient to move to destination
}

// Move specified number of armies from one territory to another
template <class T>
void Player::MoveArmies(int& number, Territory<T>* from, Territory<T>* to)
{
	// check that you can call MoveOverLand with the given territories
	// add armies to region
	if (number > 0 && MoveOverLand(from, to) > 0)
	{
		cout << "Moved " << number << " armies from " << from << " to " << to;
	}
	else
	{
		cout << "Could not perform action (MoveArmies)";
	}
}

// Place armies at the specified location
void Player::PlaceNewArmies(Territory<Region>* location, int& number)
{
	// check ownership of territory (can place ONLY if your own)
	if ((unplacedArmies - number >= 0) && (placedArmies + number <= 18))
	{
		unplacedArmies = unplacedArmies - number;
		placedArmies = placedArmies + number;
		// add specified number of armies to the specified region
		cout << "Added " << number << " armies at " << location;
	}
	else if ((unplacedArmies - number < 0) || (placedArmies + number > 18))
	{
		cout << "This action is not permissible.";
	};
}

// Destroy all enemy armies found at the specified location
template <class T>
void Player::DestroyArmy(Territory<T>* location, int& number)
{
	// check that there are other armies at the specified location
	// destroy specified number of armies found at the specified location
	// identify original owner of territory and reduce number of placedArmies > increase number of unplacedArmies
}

// Builds a city at the specified location
void Player::BuildCity(Territory<Region>* location)
{
	// check ownership of region (MUST HAVE AT LEAST ONE ARMY THERE)
	if ((unplacedCities - 1 >= 0) && (placedCities + 1 <= 3))
	{
		unplacedCities = unplacedCities - 1;
		placedCities = placedCities + 1;
		// add city at specified location
		cout << "Built a city at ${location}";
	}
	else if ((unplacedCities - 1 < 0) || (placedCities + 1 > 3))
	{
		cout << "This action is not permissible.";
	};
}