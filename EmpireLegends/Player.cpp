#include "Player.h";
#include <iostream>;

// using std::cout;

//========= PLAYER METHODS =========//
// Instantiate a new Player object with a given player name
Player::Player(const string username)
{
	// verify that this is not a duplicate username for the current players in game
	playerName = username;
	totalCoins = 0;
    unplacedArmies = 18;
    placedArmies = 0;
	// define a bidingFacility
	// playerCities, playerArmies and playerTerritories should all be instantiated to empty vectors
}

Player::PayCoin(const int price)
{
	if ((totalCoins - price) > 0)
	{
		totalCoins = totalCoins - price;
	}
}

// Player moves from one territory to another
Player::MovesOverLand(const Territory from, const Territory to)
{
	// check current territory
	// check that destination territory is valid
	// check that travel can be done between both territories
	// move player to the specified territory
}

// Place armies at the specified location
Player::PlaceNewArmies(const Territory location, const int number)
{
	// check that the territory is valid
	// check that the territory is not already occupied TODO: read rules to see if this is necessary
	// add specified number of armies to the specified territory
	// add territory to vector<Territory> playerTerritories
	if ((unplacedArmies - number >= 0) && (placedArmies + number <= 18))
	{
		unplacedArmies = unplacedArmies - number;
		placedArmies = placedArmies + number;
	}
	else if ((unplacedArmies - number < 0) || (placedArmies + number > 18))
	{
		cout << "This action is not permissible.";
	};
}

// Move specified number of armies from one territory to another
Player::MoveArmies(const int number, const Territory to, const Territory from)
{
	// check that starting territory is valid
	// check that destination territory is valid
	// check that travel can be done between both territories
	// move specified number of armies to the specified territory
	// modify location of armies in vector<int, string> playerArmies
}

// Destroy all enemy armies found at the specified location
Player::DestroyArmy(const Territory location)
{
	// check that there are armies at the specified location
	// check that, if there are armies present, that they aren't the players' own armies
	// destroy specified number of armies found at the specified location
	// identify original owner of territory and reduce number of placedArmies > increase number of unplacedArmies
}

//========= CITY METHODS =========//
// Builds a city at the specified location
City::BuildCity(const Territory location)
{
	// add city at specified location (only one city/location?)
	// add city to vector<City> playerCities
}