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

	void PayCoin(int price);
	template <class T>
	void MoveOverLand(const Territory<T> from, const Territory<T> to);
	void PlaceNewArmies(const Territory<Region> destination, const int number);
	template <class T>
	void MoveArmies(const int number, const Territory<T> from, const Territory<T> to);
	template <class T>
	void DestroyArmy(const Territory<T> location, const int number);

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

class City
{
public:
	void BuildCity(const Territory<Region> territory);
};
