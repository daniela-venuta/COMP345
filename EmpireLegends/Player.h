#pragma once

#include <string>
#include <vector>

#include "Map.h"
#include "Cards.h"

using std::string;
using std::vector;

class Player
{
public:
	Player(string username);
	~Player();

	void PayCoin(int price);
	int getBalance();
	int MoveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap* map);
	void PlaceNewArmies(int number, Territory<Region>* destination);
	void MoveArmies(int number, Territory<Region>* from, Territory<Region>* to, GameMap* map);
	void DestroyArmy(int number, Territory<Region>* location);
	void BuildCity(Territory<Region>* territory);

private:
	string playerName;
	int totalCoins;
	vector<Territory<Region>> playerTerritories;
	Hand playerHand;
	//BidingFacility bidingFacility;
	int unplacedCities;
	int placedCities;
	int unplacedArmies;
	int placedArmies;
};