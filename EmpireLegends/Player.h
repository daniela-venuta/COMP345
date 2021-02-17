#pragma once

#include <string>
#include <vector>

#include "Map.h"
#include "Cards.h"
#include "BiddingFacility.h"


using std::string;
using std::vector;

class Player
{
public:
	Player(string username);
	~Player();
	
	//----------- need to check this again ----------- 
	//BiddingFacility* getBidFacility() const;
	
	void PayCoin(int price);
	int MoveOverLand(Territory<Region>* from, Territory<Region>* to, GameMap map);
	void PlaceNewArmies(Territory<Region>* destination, int& number);
	template <class T>
	void MoveArmies(int& number, Territory<T>* from, Territory<T>* to);
	template <class T>
	void DestroyArmy(Territory<T>* location, int& number);
	void BuildCity(Territory<Region>* territory);

private:
	string playerName;
	int totalCoins;
	vector<Territory<Region>> playerTerritories;
	Hand playerHand;
	
	//----------- need to check this again ----------- 
	//BiddingFacility* BidFacility;
	
	int unplacedCities;
	int placedCities;
	int unplacedArmies;
	int placedArmies;
};