#pragma once
#include "GameObserver.h"
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

class StartingPhase : public Observable
{
public:
	StartingPhase();
	~StartingPhase();

	void startGame(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers);

	Player* currentPlayer;
	string currentAction;

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

class StartingPhaseObserver : public Observer
{
public:
	StartingPhaseObserver(StartingPhase* s);
	~StartingPhaseObserver();
	
	void Update() override;
	void display();

private:
	StartingPhase* subject;
};
