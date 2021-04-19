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
	StartingPhase(GameMap* map, Deck* deck, const vector<Player*>& playerVector);
	~StartingPhase();

	vector<Player*> startGame();

	string getState() const { return state; };
	Player* currentPlayer;

private:
	void shuffleCardDeck() const;
	void assignPlayerResources();
	void setupStartingTerritories();
	void placeArmiesOnMap();
	void startBidding();

	int setNumberOfCoins();

	int numOfPlayers = 0;
	Deck* cardDeck;
	vector<Player*> players;
	GameMap* map;
	ColorUtilities* colorUtilities;
	string state;
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