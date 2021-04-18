#include "StartingPhase.h"
#include "MapLoader.h"
#include "MapUtility.h"
#include "BiddingFacility.h"

// Number of armies of non player colour that need to be placed on the map in a two player game
static const int NUM_ARMIES_TO_PLACE = 10;

// Method to check if a user has selected a color or if it is free
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

// Helper method to mark a color as free or taken
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

// Returns first color that is available
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

// Returns a color mapped to the Color enum found in Player
Color ColorUtilities::getColor(int index)
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

// Default constructor for the Starting Phase to initialize all pointers
StartingPhase::StartingPhase()
{
	nonPlayer1 = new Player("CPU1", 0);
	
	colorUtilities = new ColorUtilities();
	cardDeck = nullptr;
	numOfPlayers = 0;
}

// Destructor for the StartingPhase class for cleanup
StartingPhase::~StartingPhase()
{
	delete nonPlayer1;
	delete colorUtilities;
	delete map;
}

// Method to start the sequence of actions that are needed in the starting phase
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

// Retrieve number of starting coins per player
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

// Method to initiate shuffling of the current deck of cards (changes their order in the vector)
void StartingPhase::shuffleCardDeck() const
{
	std::cout << *cardDeck;

	cardDeck->shuffle();
	std::cout << *cardDeck;

	// Draw cards from deck and add them to the hand
	cardDeck->draw(6);
	std::cout << *cardDeck;
}

// Assigns colours to the players and provides coins, armies and cities
void StartingPhase::assignPlayerResources()
{
	std::cout << "\nColor options \n 1.Red \n 2.Green  \n 3.Blue \n 4. Yellow \n";
	
	// Assign number of coins based on players
	int playerCoins = setNumberOfCoins(numOfPlayers);

	for (int i = 0; i < numOfPlayers; i++)
	{
		bool isColorUnavailable = true;
		int colorNum;
		const Player* player = players[i];
		Resources* resources = players[i]->getResources();
		Color col = Color::none;

		while(isColorUnavailable)
		{
			std::cout << player->getName() << ", choose your color: ";
			std::cin >> colorNum;
			col = colorUtilities->getColor(colorNum);
			isColorUnavailable = !colorUtilities->getColorAvailability(col);

			if(isColorUnavailable)
			{
				std::cout << "\nColor unavailable, try again \n";
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

// Adds 4 armies to the starting location for each player
void StartingPhase::setupStartingTerritories()
{
	Territory<Region>* startingRegion = MapUtility::getStartingLocation(map);

	// place 4 armies to start
	for (Player* player : players)
	{
		player->placeNewArmies(4, startingRegion, startingRegion);
	}
}

// Allows players to take turns placing non player color armies on map
void StartingPhase::placeArmiesOnMap()
{
	string continentName;
	string territoryName;
	Territory<Region>* destination = nullptr;
	std::cin.ignore();

	MapUtility::printTerritories(map);

	for (int i = 0; i < NUM_ARMIES_TO_PLACE; i++)
	{
		int index = i % 2;

		Player* player = players[index];
		std::cout << "\n" << player->getName() << ", place the non player army on the board. \n";

		do
		{
			try
			{
				destination = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));
			}
			catch(TerritoryNotFoundException&){
				std::cout << (territoryName.empty() ? territoryName : continentName) << " does not exist. Try again. \n"; // Territory or region string was invalid
			}
		
		} while (destination == nullptr);
		
		nonPlayer1->placeNewArmies(1, destination, destination); // Bypassing initial region check
	}
}

// Assigns a remaining colour to a non-player and assigns them armies to be placed on the board
void StartingPhase::setupNonPlayers()
{
	Color color1 = colorUtilities->getNewColor();
	colorUtilities->setColorAvailability(color1, false);

	Resources* resources1 = nonPlayer1->getResources();
	
	resources1->playerColor = color1;
	resources1->unplacedCities = 3;
	resources1->unplacedArmies = 18;
}

// Initiates the bidding phase
void StartingPhase::startBidding()
{
	// Players place bids
	BiddingFacility::placeBids(players);
}
