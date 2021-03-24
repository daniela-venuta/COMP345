#pragma once
#include "BiddingFacility.h"
#include "Player.h"

struct ColorUtilities
{
	ColorUtilities();

	static bool yellow;
	static bool blue;
	static bool green;
	static bool red;

	static bool getColorAvailability(string color);
	static void setColorAvailability(string color, bool isAvailable);
	static Color getNewColor();
	static Color parseColor(string color);
};

class StartingPhase
{
public:
	StartingPhase();
	~StartingPhase();

	void startGame();

private:
	void setupCardDeck();
	void populatePlayers();
	void setupStartingTerritories();
	void placeArmiesOnMap();
	void setupNonPlayer();
	void startBidding();

	int setNumberOfCoins(int numofPlayers);

	int numOfPlayers = 0;
	Deck* cardDeck;
	vector<Player*> players;
	Player* nonPlayer;
	BiddingFacility* biddingFacility;
	GameMap* map;
};