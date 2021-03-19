#pragma once
#include "Map.h"
#include "Cards.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

enum Colour { none, red, green, blue, yellow };

struct Resources
{
	// default constructor
	Resources() = default;

	// player resources
	Colour playerColour = none;
	int unplacedCities;
	int unplacedArmies;
	int totalCoins;
};

class Player
{
public:
	Player();
	Player(string name, int coins);
	Player(string username);
	
	~Player() = default;

	// copy constructor
	Player(const Player & otherPlayer);

	// stream insertion operator overload
	friend ostream& operator<<(ostream & os, const Player & player);
	friend ostream& operator>>(ostream & os, const Player & player);

	// assignment operator
	Player& operator=(const Player& player);

	string getName() const;

	void setName(string name);

	int getCoins() const;

	void setCoins(int coins);

	void PayCoin(int price);
	int getBalance() const;
	void setBalance(int newBalance);

	int MoveOverLand(Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void PlaceNewArmies(int number, Territory<Region>*destination);
	void MoveArmies(int number, Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void DestroyArmy(int number, Territory<Region>*location);
	void BuildCity(Territory<Region>*territory);

	const Resources getResources() const;
	void setNumofcards();
	int  getNumofcards();

private:
	string playerName;
	vector<Territory<Region>> playerTerritories;
	Hand playerHand;
	int NumCards; 

	Resources pResources;

	static const int TOTAL_NUM_ARMIES = 18;
	static const int TOTAL_NUM_CITIES = 3;
	static const int TOTAL_NUM_COINS = 9;
};
	