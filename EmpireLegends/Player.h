#pragma once

#include <string>;
#include <vector>;

#include "Map.h";
#include "Cards.h";

using std::string;
using std::vector;

class Player
{
public:
	Player(string username);
	~Player();
	PayCoin(int price);
	MovesOverLand(const Territory from, const Territory to);
	PlaceNewArmies(const Territory destination, const int number);
	MoveArmies(const int number, const Territory from, const Territory to);
	DestroyArmy(const Territory location, const int number);

private:
	string playerName;
	int totalCoins;
	vector<Territory> playerTerritories;
	Hand playerHand;
	//BidingFacility bidingFacility;
	vector<City> playerCities;
	vector<int, string> playerArmies;
	int unplacedArmies;
	int placedArmies;
};

class City
{
public:
	BuildCity(const Territory territory);
};
