#pragma once
#include "BiddingFacility.h"
#include "Player.h"

#ifndef COLOR_UTILITIES
#define COLOR_UTILITIES
struct ColorUtilities
{
	ColorUtilities() = default;

	bool yellow = true;
	bool blue = true;
	bool green = true;
	bool red = true;

	bool getColorAvailability(Color color);
	void setColorAvailability(Color color, bool isAvailable);
	Color getNewColor();
	Color getColor(int index);
};
#endif

class StartingPhase
{
public:
	StartingPhase();
	~StartingPhase();

	void startGame(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers);

private:
	void shuffleCardDeck() const;
	void assignPlayerResources();
	void setupStartingTerritories();
	void placeArmiesOnMap();
	void setupNonPlayers();
	void startBidding();
	void printTerritories();

	int setNumberOfCoins(int numofPlayers);
	Territory<Region>* getStartingLocation();

	int numOfPlayers = 0;
	Deck* cardDeck;
	vector<Player*> players;
	Player* nonPlayer1;
	Player* nonPlayer2;
	BiddingFacility* biddingFacility;
	GameMap* map;
	ColorUtilities* colorUtilities;
};