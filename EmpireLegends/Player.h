#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Cards.h"

using std::string;
using std::vector;
using std::map;
using std::ostream;

enum Color { none, red, green, blue, yellow };
static vector<Player*> currentPlayers;
static string initialContinent= "Continent 1";
static string initialRegion = "Region 1";

struct Resources
{
	// default constructor
	Resources() = default;

	// Copy constructor
	Resources(const Resources& otherResources);

	Resources& operator=(const Resources& resources);

	// player resources
	Color playerColor = none;
	int unplacedCities{};
	int unplacedArmies{};
	int totalCoins{};
	
	
	// Abilities
	int extraMoves{};
	int extraArmies{};
	int flying{};
	int elixir{};
	int coinVPs{};
	map<CardSet, bool> setNameVPs;
	map<CardSet, bool> completeSetVPs;
	bool immune = false;

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

	void payCoin(int price);
	int getBalance() const;
	void setBalance(int newBalance);

	//Original Version of Player Actions
	void PlaceNewArmies(int number, Territory<Region>*destination);
	void MoveArmies(int number, Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void DestroyArmy(int number, Territory<Region>*location, vector<Player*> currentPlayers);
	void BuildCity(Territory<Region>*territory);

	//"Ask Prompt to Player" of Player Actions
	bool PlaceNewArmies(GameMap* gm);
	bool MoveArmies();
	bool DestroyArmy();
	bool BuildCity();

	void applyGood(Good* addedGood);
	Resources* getResources() const;
	void andOrAction(Card* cardTwoAction, GameMap* gm);
	int MoveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap* map);

private:
	string playerName;
	vector<Territory<Region>*> playerTerritories;
	Hand* playerHand;
	vector<Territory<Region>*> playerArmies;
	Resources* pResources;

	static const int TOTAL_NUM_ARMIES = 18;
	static const int TOTAL_NUM_CITIES = 3;
	static const int TOTAL_NUM_COINS = 9;
	
};
	