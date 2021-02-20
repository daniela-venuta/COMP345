#pragma once
#include "BiddingFacility.h"
#include "Map.h"
#include "Cards.h"
#include <string>
#include <vector>

using std::string;

class Player
{
private: 
	
	string playerName;
	int totalCoins;
	BiddingFacility* Bidding;
	vector<Territory<Region>> playerTerritories;
	Hand playerHand;
	int unplacedCities;
	int placedCities;
	int unplacedArmies;
	int placedArmies;

public:

	Player();

	Player(string username, int coins);

	string getName();
	
	void setName(string name); 

	int getCoins(); 
	
	void setCoins(int coins); 

	BiddingFacility* getBidFac();

	Player(string username);
	
	~Player() = default;

	// copy constructor
	Player(const Player & otherPlayer);

	// stream insertion operator overload
	friend ostream& operator<<(ostream & os, const Player & player);
	friend ostream& operator>>(ostream & os, const Player & player);

	// assignment operator
	Player& operator = (Player & player);


	void PayCoin(int price);
	int getBalance();
	void setBalance(int newBalance);

	int MoveOverLand(Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void PlaceNewArmies(int number, Territory<Region>*destination);
	void MoveArmies(int number, Territory<Region>*from, Territory<Region>*to, GameMap * map);
	void DestroyArmy(int number, Territory<Region>*location);
	void BuildCity(Territory<Region>*territory);



};
	