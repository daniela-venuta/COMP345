#include "Player.h"

//========= PLAYER METHODS =========//
// Instantiate a new Player object with a given player name
Player::Player(string username)
{
	// verify that this is not a duplicate username for the current players in game
	playerName = username;
	totalCoins = 0; // players start off with no coins
	// define an empty vector<Territory>
	// define an empty vector<Card> hand
	// define a bidingFacility
	// define an empty vector<City>
	// define an empty vectory<Army>
}

Player::PayCoin(int price)
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
	// move player to the specified territory
}

//========= ARMY METHODS =========//
// Place armies at the specified location
Army::PlaceNewArmies(const Territory location, const int number)
{
	// check that territory is valid
	// check that the terriroty is not already occupied (?)
	// add specified number of armies to the specified terriroty
	// add territory to vector<Territory> playerTerritories
	// reduce total number of available armies vector<Army> playerArmies
}

// Move specified number of armies from one territory to another
Army::MoveArmies(const int number, const Territory to, const Territory from)
{
	// check that starting territory is valid
	// check that destination territory is valid
	// move specified number of armies to the specified territory
}

// Destroy all enemy armies found at the specified location
Army::DestroyArmy(const Territory location)
{
	// check that there are armies at the specified location
	// check that, if there are armies present, that they aren't the players' own armies
	// destroy specified number of armies found at the specified location
	// check original owner of territory and reduce number of armies
}

//========= CITY METHODS =========//
// Builds a city at the specified location
City::BuildCity(const Territory location)
{
	// add city at specified location (only one city/location?)
	// add city to vector<City> playerCities
}