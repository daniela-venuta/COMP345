#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Cards.h"

using std::string;
using std::vector;
using std::map;
using std::ostream;

class PlayerStrategy;

enum Color { none, red, green, blue, yellow };

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
	bool coinVPs = false;
	map<CardSet, bool> setNameVPs;
	map<CardSet, bool> completeSetVPs;
	bool immune = false;
};

class Player
{
	PlayerStrategy* strategy;
public:
	Player();
	Player(string name, int coins, PlayerStrategy* strategy = nullptr);
	Player(string username, PlayerStrategy* strategy = nullptr);
	
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

	void setStrategy(PlayerStrategy* strategy);
	PlayerStrategy* getStrategy();

	void payCoin(int price);
	int getBalance() const;
	void setBalance(int newBalance);

	bool moveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map);
	bool placeNewArmies(int number, Territory<Region>* destination, Territory<Region>* initialRegion);
	bool destroyArmy(int number, Territory<Region>* location, Player* player);
	bool buildCity(Territory<Region>* territory);
	void addOwnedTerritory(Territory<Region>*territory);
	void removeOwnedTerritory(Territory<Region>*territory);

	Resources* getResources() const;

	void countCardTypes();
	int computeScore();
	void addVictoryPoints(int pts);
	int getVictoryPoints();
	vector<Territory<Region>*> getTerritories();

	void addCard(Card* card);
	void applyGood(Good* addedGood);
	bool andOrAction(Card* cardTwoAction, GameMap* gm);
	Player* chooseEnemy(Territory<Region>* location, int numArmies);
	Territory<Region>* chooseTerritory(map<int, Territory<Region>*> regions);
private:
	string playerName;
	vector<Territory<Region>*> playerTerritories;
	Hand* playerHand;
	Resources* pResources;



	int victoryPoints;

	// Resources
	static const int TOTAL_NUM_ARMIES = 18;
	static const int TOTAL_NUM_CITIES = 3;
	static const int DEFAULT_NUM_COINS = 9;

	// Cardset types
	int forestCards{};
	int direCards{};
	int ancientCards{};
	int nobleCards{};
	int mountainCards{};
	int arcaneCards{};
	int cursedCards{};
	int nightCards{};

	// Total cards per set
	static const int MAX_NUM_FOREST_CARDS = 4;
	static const int MAX_NUM_DIRE_CARDS = 5;
	static const int MAX_NUM_ANCIENT_CARDS = 3;
	static const int MAX_NUM_NOBLE_CARDS = 3;
	static const int MAX_NUM_MOUNTAIN_CARDS = 2;
	static const int MAX_NUM_ARCANE_CARDS = 2;
	static const int MAX_NUM_CURSED_CARDS = 5;
	static const int MAX_NUM_NIGHT_CARDS = 2;
};
	