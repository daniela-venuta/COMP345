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

	vector<Player*> startGame(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers);
	vector<Player*> startGamePlayerBot(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers);
	vector<Player*> startGameBot(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers);
	string getState() const { return state; };
	Player* currentPlayer;
	

private:
	void shuffleCardDeck() const;
	void assignPlayerResources();
	void setupStartingTerritories();
	void placeArmiesOnMap();
	void setupNonPlayers();
	void startBidding();
	void maxBidderFirst(string maxBidder);

	int setNumberOfCoins(int numofPlayers);

	int numOfPlayers = 0;
	Deck* cardDeck;
	vector<Player*> players;
	Player* nonPlayer1;
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
