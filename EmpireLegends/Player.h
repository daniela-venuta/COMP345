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
static vector<Territory<Region>*> listRegion;

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

	int moveOverLand(Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void placeNewArmies(int number, Territory<Region>*destination, Territory<Region>* initialRegion);
	void moveArmies(int number, Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void destroyArmy(int number, Territory<Region>*location, Player* player);
	void buildCity(Territory<Region>*territory);
	void addOwnedTerritory(Territory<Region>*territory);
	void removeOwnedTerritory(Territory<Region>*territory);

	void applyGood(Good* addedGood);
	Resources* getResources() const;
	void andOrAction(Card* cardTwoAction, GameMap* gm);
	int MoveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap* map);
	void setListOfRegion(GameMap* gameMap);

private:
	string playerName;
	vector<Territory<Region>*> playerTerritories;
	Hand* playerHand;
	Resources* pResources;

	static const int TOTAL_NUM_ARMIES = 18;
	static const int TOTAL_NUM_CITIES = 3;
	static const int TOTAL_NUM_COINS = 9;
	
	Territory<Region>* chooseTerritory(map<int, Territory<Region>*> regions);
	void executeAction(Action* action, GameMap* map);
};
	