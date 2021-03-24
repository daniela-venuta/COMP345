#include "StartingPhase.h"
#include <algorithm>
#include "MapLoader.h"

static const int NUM_ARMIES_TO_PLACE = 10;

ColorUtilities::ColorUtilities()
{
	yellow = true;
	green = true;
	blue = true;
	red = true;
}

bool ColorUtilities::getColorAvailability(string color)
{
	bool isAvailable = false;
	Color col = ColorUtilities::parseColor(color);

	if (col == Color::blue)
	{
		isAvailable = ColorUtilities::blue;
	}
	else if (col == Color::yellow)
	{
		isAvailable = ColorUtilities::yellow;
	}
	else if (col == Color::red)
	{
		isAvailable = ColorUtilities::red;
	}
	else
	{
		isAvailable = ColorUtilities::green;
	}

	return isAvailable;
}

void ColorUtilities::setColorAvailability(string color, bool isAvailable)
{
	Color col = ColorUtilities::parseColor(color);

	if (col == Color::blue)
	{
		ColorUtilities::blue = isAvailable;
	}
	else if (col == Color::yellow)
	{
		ColorUtilities::yellow = isAvailable;
	}
	else if (col == Color::red)
	{
		ColorUtilities::red = isAvailable;
	}
	else
	{
		ColorUtilities::green = isAvailable;
	}
}

Color ColorUtilities::getNewColor()
{
	Color freeColor = Color::none;
	if (ColorUtilities::blue)
	{
		freeColor = Color::blue;
	}
	else if (ColorUtilities::yellow)
	{
		freeColor = Color::yellow;
	}
	else if (ColorUtilities::red)
	{
		freeColor = Color::yellow;
	}
	else if (ColorUtilities::green)
	{
		freeColor = Color::green;
	}

	return freeColor;
}

Color ColorUtilities::parseColor(string color)
{
	// set string to lower case
	std::transform(color.begin(), color.end(), color.begin(),
		[](unsigned char c) { return std::tolower(c); });

	Color col = Color::none;

	if (color.compare("blue") == 0)
	{
		col = Color::blue;
	}
	else if (color.compare("red") == 0)
	{
		col = Color::red;
	}
	else if (color.compare("green") == 0)
	{
		col = Color::green;
	}
	else if (color.compare("yellow") == 0)
	{
		col = Color::yellow;
	}

	return col;
}

StartingPhase::StartingPhase()
{
	nonPlayer = new Player("CPU", 0);
	biddingFacility = new BiddingFacility();
	cardDeck = nullptr;
	numOfPlayers = 0;

	// get map
	MapLoader* mapLoader = new MapLoader();
	map = mapLoader->load("valid_map_1.json");
}

StartingPhase::~StartingPhase()
{
	delete nonPlayer;
	delete biddingFacility;

	delete map;
}

void StartingPhase::startGame()
{
	setupCardDeck();
	populatePlayers();
	setupStartingTerritories();
	placeArmiesOnMap();
	setupNonPlayer();
	startBidding();
}

int StartingPhase::setNumberOfCoins(int numofPlayers)
{
	int playerCoins;
	switch (numofPlayers) {

	case 2:
		playerCoins = 14;
		std::cout << "Each player gets 14 coins" << std::endl;
		break;

	case 3:
		playerCoins = 11;
		std::cout << "Each player gets 11 coins" << std::endl;
		break;

	case 4:
		playerCoins = 9;
		std::cout << "Each player gets 9 coins" << std::endl;
		break;

	default: playerCoins = 0;
	}

	return playerCoins;
}

void StartingPhase::setupCardDeck()
{
	// set up cards
	Card* cardOne = new Card("Dire dragon", "", "Place 3 armies and destroy one army");
	Card* cardTwo = new Card("Dire giant", "Immune to attack", "Place 3 armies and destroy army");
	Card* cardThree = new Card("Dire eye", "", "Place 4 armies");
	Card* cardFour = new Card("Dire Ogre", " +1 VP per 3 coins", "Move 2 armies");
	Card* cardFive = new Card("Lake", " +1 VP per Forest card", "Place 2 armies and move 3 armies");
	Card* cardSix = new Card("Noble Hills", " Three noble cards = 4 VP", "Place 3 armies");

	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(cardOne);
	cardVector.push_back(cardTwo);
	cardVector.push_back(cardThree);
	cardVector.push_back(cardFour);
	cardVector.push_back(cardFive);
	cardVector.push_back(cardSix);

	// Create deck and add cards (this creates a card hand as well)
	cardDeck = new Deck(cardVector);

	std::cout << *cardDeck;

	cardDeck->shuffle();
	std::cout << *cardDeck;

	// Draw cards from deck and add them to the hand
	cardDeck->draw(6);
	std::cout << *cardDeck;
}

void StartingPhase::populatePlayers()
{
	string username;
	string color;
	
	// determines how many coins per player
	std::cout << "\nNumber of players in the game (2-4): ";
	std::cin >> numOfPlayers;

	// Assign number of coins based on players
	int playerCoins = setNumberOfCoins(numOfPlayers);

	// Get players
	for (int i = 0; i < 2; i++) {
		std::cout << "Type player name: ";
		std::cin >> username;

		// creates a new pointer for each player object and adds it to the player vector
		players.push_back(new Player(username, playerCoins));
	}

	// select colors
	for (int i = 0; i < numOfPlayers; i++)
	{
		const Player* player = players[i];
		Resources* resources = players[i]->getResources();

		std::cout << player->getName() << "Choose your color: ";
		std::cin >> color;


		Color col = ColorUtilities::parseColor(color);
		resources->playerColor = col;
	}
}

void StartingPhase::setupStartingTerritories()
{
	Territory<Region>* startingRegion = map->findTerritory("Continent 1")->value->findTerritory("Region 1");

	// place 4 armies to start
	for (Player* player : players)
	{
		// edit
		player->PlaceNewArmies(4, startingRegion);
	}

	// get unassigned color
	// assign CPU color
	nonPlayer->getResources()->playerColor = ColorUtilities::getNewColor();
}

void StartingPhase::placeArmiesOnMap()
{
	// get unassigned color
	// assign CPU color
	nonPlayer->getResources()->playerColor = ColorUtilities::getNewColor();

	string continentName;
	string territoryName;

	// place armies
	for (int i = 0; i < NUM_ARMIES_TO_PLACE; i++)
	{
		int index = i % 4;

		if (index == 3)
		{
			nonPlayer->PlaceNewArmies(1, nullptr);
		}
		else
		{
			std::cout << "Enter continent: ";
			std::cin >> continentName;

			std::cout << "Enter region: ";
			std::cin >> territoryName;

			Territory<Region>* destination = map->findTerritory(continentName)->value->findTerritory(territoryName);
			players[i]->PlaceNewArmies(1, destination);
		}
	}
}

void StartingPhase::setupNonPlayer()
{
	// get unassigned color
	// assign CPU color
	nonPlayer->getResources()->playerColor = ColorUtilities::getNewColor();
}

void StartingPhase::startBidding()
{
	// Players place bids
	biddingFacility->placeBids(players);
}
