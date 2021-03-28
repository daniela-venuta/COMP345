#include "StartingPhase.h"
#include <algorithm>
#include "MapLoader.h"
#include <stdlib.h>

static const int NUM_ARMIES_TO_PLACE = 10;

bool ColorUtilities::getColorAvailability(Color color)
{
	bool isAvailable;

	if (color == Color::blue)
	{
		isAvailable = blue;
	}
	else if (color == Color::yellow)
	{
		isAvailable = yellow;
	}
	else if (color == Color::red)
	{
		isAvailable = red;
	}
	else
	{
		isAvailable = green;
	}

	return isAvailable;
}

void ColorUtilities::setColorAvailability(string color, bool isAvailable)
{
	Color col = parseColor(color);

	if (col == Color::blue)
	{
		blue = isAvailable;
	}
	else if (col == Color::yellow)
	{
		yellow = isAvailable;
	}
	else if (col == Color::red)
	{
		red = isAvailable;
	}
	else
	{
		green = isAvailable;
	}
}

void ColorUtilities::setColorAvailability(Color color, bool isAvailable)
{
	if (color == Color::blue)
	{
		blue = isAvailable;
	}
	else if (color == Color::yellow)
	{
		yellow = isAvailable;
	}
	else if (color == Color::red)
	{
		red = isAvailable;
	}
	else
	{
		green = isAvailable;
	}
}

Color ColorUtilities::getNewColor()
{
	Color freeColor = Color::none;
	if (blue)
	{
		freeColor = Color::blue;
	}
	else if (yellow)
	{
		freeColor = Color::yellow;
	}
	else if (red)
	{
		freeColor = Color::yellow;
	}
	else if (green)
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

Color ColorUtilities::parseColor(int index)
{
	Color col = Color::none;

	if (index == Color::red)
	{
		col = Color::red;
		std::cout << "Selected Red\n";
	}
	else if (index == Color::green)
	{
		col = Color::green;
		std::cout << "Selected Green\n";
	}
	else if (index == Color::blue)
	{
		col = Color::green;
		std::cout << "Selected Blue\n";
	}
	else if (index == Color::yellow)
	{
		col = Color::yellow;
		std::cout << "Selected Yellow\n";
	}

	return col;
}

StartingPhase::StartingPhase()
{
	nonPlayer1 = new Player("CPU1", 0);
	nonPlayer2 = new Player("CPU2", 0);
	
	biddingFacility = new BiddingFacility();
	colorUtilities = new ColorUtilities();
	cardDeck = nullptr;
	numOfPlayers = 0;
}

StartingPhase::~StartingPhase()
{
	delete nonPlayer1;
	delete nonPlayer2;
	delete biddingFacility;
	delete colorUtilities;

	delete map;
}

void StartingPhase::startGame(GameMap* gameMap, const vector<Player*> playerVector, Deck* deck, int numPlayers)
{
	this->players = playerVector;
	this->cardDeck = deck;
	this->numOfPlayers = numPlayers;
	this->map = gameMap;
	
	shuffleCardDeck();
	assignPlayerResources();
	setupStartingTerritories();
	setupNonPlayers();
	placeArmiesOnMap();
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

Territory<Region>* StartingPhase::getStartingLocation()
{	
	Continent* continent = map->terrs.begin()->second->value;
	Territory<Region>* region = continent->terrs.begin()->second;
	
	return region;
}

void StartingPhase::shuffleCardDeck() const
{
	std::cout << *cardDeck;

	cardDeck->shuffle();
	std::cout << *cardDeck;

	// Draw cards from deck and add them to the hand
	cardDeck->draw(6);
	std::cout << *cardDeck;
}

void StartingPhase::assignPlayerResources()
{
	
	std::cout << "Color options \n 1.Red \n 2.Green  \n 3.Blue \n 4. Yellow \n";
	
	// Assign number of coins based on players
	int playerCoins = setNumberOfCoins(numOfPlayers);

	for (int i = 0; i < numOfPlayers; i++)
	{
		bool isAvailable = true;
		int colorNum;
		const Player* player = players[i];
		Resources* resources = players[i]->getResources();
		Color col = Color::none;

		while(isAvailable)
		{
			std::cout << player->getName() << ", choose your color: ";
			std::cin >> colorNum;
			col = colorUtilities->parseColor(colorNum);
			isAvailable = !colorUtilities->getColorAvailability(col);

			if(isAvailable)
			{
				std::cout << "Color unavailable, try again \n";
			}
		}
		
		resources->playerColor = col;
		
		// mark color as unavailable
		colorUtilities->setColorAvailability(col, false);

		// assign cities and armies
		resources->unplacedCities = 3;
		resources->unplacedArmies = 18;

		// assign coins
		resources->totalCoins = playerCoins;
	}
}

void StartingPhase::setupStartingTerritories()
{
	Territory<Region>* startingRegion = getStartingLocation();

	// place 4 armies to start
	for (Player* player : players)
	{
		player->PlaceNewArmies(4, startingRegion);
	}
}

void StartingPhase::placeArmiesOnMap()
{
	int num;
	string continentName;
	string territoryName;
	
	// place armies
	for (int i = 0; i < NUM_ARMIES_TO_PLACE; i++)
	{
		int index = i % 2;

		string name = players[i]->getName();

		std::cout << name << ", enter 1 or 2 for the additional army:";
		std::cin >> num;
		
		std::cout <<"Enter continent: ";
		std::cin >> continentName;

		std::cout << "Enter region: ";
		std::cin >> territoryName;

		Territory<Region>*  destination = map->findTerritory(continentName)->value->findTerritory(territoryName);

		if(num == 1)
		{
			nonPlayer1->PlaceNewArmies(1, destination);
		}
		else if(num == 2)
		{
			nonPlayer2->PlaceNewArmies(1, destination);
		}
			
	}
}

void StartingPhase::setupNonPlayers()
{
	Color color1 = colorUtilities->getNewColor();
	colorUtilities->setColorAvailability(color1, false);

	Color color2 = colorUtilities->getNewColor();
	colorUtilities->setColorAvailability(color2, false);
	
	nonPlayer1->getResources()->playerColor = color1;
	nonPlayer2->getResources()->playerColor = color2;
}

void StartingPhase::startBidding()
{
	// Players place bids
	biddingFacility->placeBids(players);
}
