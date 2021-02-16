#include "Player.h";
#include <iostream>;

using std::cout;

//========= PLAYER METHODS =========//
// Instantiate a new Player object with a given player name
Player::Player(const string username)
{
	// verify that this is not a duplicate username for the current players in game
	playerName = username;
	totalCoins = 0;
	unplacedCities = 3;
	placedCities = 0;
    unplacedArmies = 18;
    placedArmies = 0;
	// define a bidingFacility
}

void Player::PayCoin(const int price)
{
	if ((totalCoins - price) > 0)
	{
		totalCoins = totalCoins - price;
	}
}

// Player moves from one territory to another
template <class T>
void Player::MoveOverLand(const Territory<T> from, const Territory<T> to)
{
	// check current territory
	// check that destination territory is valid (valid travel points)
	// check that travel can be done between both territories (graph traversal)
	// move player to the specified territory
}

// Place armies at the specified location
void Player::PlaceNewArmies(const Territory<Region> location, const int number)
{
	// check that the territory is valid
	// check that the territory is not already occupied TODO: read rules to see if this is necessary
	// add specified number of armies to the specified territory
	// add number of armies to specified regions
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
template <class T>
void Player::MoveArmies(const int number, const Territory<T> to, const Territory<T> from)
{
	// check that you can call MoveOverLand with the given territories
	// modify location of armies in vector<int, string> playerArmies
}

// Destroy all enemy armies found at the specified location
template <class T>
void Player::DestroyArmy(const Territory<T> location, const int number)
{
	// check that there are armies at the specified location
	// check that, if there are armies present, that they aren't the players' own armies
	// destroy specified number of armies found at the specified location
	// identify original owner of territory and reduce number of placedArmies > increase number of unplacedArmies
}

//========= CITY METHODS =========//
// Builds a city at the specified location
void City::BuildCity(const Territory<Region> location)
{
	// add city at specified location (only one city/location?)
	// add city to vector<City> playerCities
}