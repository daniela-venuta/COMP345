#pragma once
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
	StartingPhase(GameMap* map, Deck* deck);
	~StartingPhase();

	vector<Player*> startGame(const vector<Player*>& playerVector);
	
private:
	void shuffleCardDeck() const;
	void assignPlayerResources();
	void setupStartingTerritories();
	void placeArmiesOnMap();
	void startBidding();
	void maxBidderFirst(string maxBidder);

	int setNumberOfCoins(int numPlayers);

	int numOfPlayers = 0;
	Deck* cardDeck;
	vector<Player*> players;
	GameMap* map;
	ColorUtilities* colorUtilities;
};