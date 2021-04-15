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

	vector<Player*> startGame(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers);

private:
	void shuffleCardDeck() const;
	void assignPlayerResources();
	void setupStartingTerritories();
	void placeArmiesOnMap();
	void setupNonPlayers();
	void startBidding();

	int setNumberOfCoins(int numofPlayers);

	int numOfPlayers = 0;
	Deck* cardDeck;
	vector<Player*> players;
	Player* nonPlayer1;
	GameMap* map;
	ColorUtilities* colorUtilities;
};