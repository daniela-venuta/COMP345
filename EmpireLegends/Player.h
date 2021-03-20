#pragma once
#include "Map.h"
#include "Cards.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

enum class Colour { none, red, green, blue, yellow };

struct ColourAvailability
{
	ColourAvailability();
	
	static bool yellow;
	static bool blue;
	static bool green;
	static bool red;

	static bool getColourAvailability(Colour col);
	static void setColourAvailability(Colour col, bool isAvailable);
};

struct Resources
{
	// default constructor
	Resources() = default;

	// player resources
	Colour playerColour = Colour::none;
	int unplacedCities = 0;
	int unplacedArmies = 0;
	int totalCoins = 0;

	static Colour parseColour(string colour);
};

class Player
{
public:
	Player();
	Player(string name, int coins);
	Player(string username);
	
	~Player();

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

	Resources* getResources() const;

private:
	string playerName;
	vector<Territory<Region>> playerTerritories;
	Hand playerHand;

	Resources* pResources;

	static const int TOTAL_NUM_ARMIES = 18;
	static const int TOTAL_NUM_CITIES = 3;
	static const int TOTAL_NUM_COINS = 9;
};
	