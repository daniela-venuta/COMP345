#include "GameStart.h"
#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"
#include "PlayerStrategies.h"

#include <iostream>
#include <string>

GameMap* GameStart::loadMap() {

	startGame();

	state = "Map Selection";
	Notify();

	MapLoader* mapLoader = new MapLoader();

	string fileName = "";
	std::cout << "Please enter the name of the map you wish to play with." << std::endl;
	// Ignores the extra whitespace from previously required inputs
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, fileName);

	GameMap* gameMap = nullptr;
	while (gameMap == nullptr)
	{
		try
		{
			gameMap = mapLoader->load(fileName);
		}
		catch (InvalidMapFileException& imf)
		{
			std::cout << "This file does not contain a valid map." << std::endl;
			std::cout << imf << std::endl;

			std::cout << "Could not process map. Please enter a valid file name: ";
			std::getline(std::cin, fileName);
		}
		catch (MapException& me)
		{
			std::cout << "This map is invalid." << std::endl;
			std::cout << me << std::endl;

			std::cout << "Could not process map. Please enter a valid file name: ";
			std::getline(std::cin, fileName);
		}
	}

	delete mapLoader;
	return gameMap;
}

vector<Player*> GameStart::detPlayerCount() {

	startSetup();

	int playerCoins = 0;
	string playerName = "";
	int numOfPlayers = 0;
	vector<Player*> players = {};

	while (numOfPlayers < 2 || numOfPlayers > 4)
	{
		std::cout << "How many players will be playing? Please select a number between 2 and 4: ";
		std::cin >> numOfPlayers;

		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter a NUMBER: ";
			std::cin >> numOfPlayers;
		}
	}

	// Assign coins according to numOfPlayers
	switch (numOfPlayers) {

		case 2:
			playerCoins = 14;
			break;
		case 3:
			playerCoins = 11;
			break;
		default: //4
			playerCoins = 9;
			break;
	}

	std::cin.ignore();

	for (auto i = 0; i < numOfPlayers; i++)
	{
		std::cout << "\nEnter player name " << i + 1 << ": ";
		getline(std::cin, playerName);
		Player* temp = new Player(playerName, playerCoins);
		players.push_back(temp);
		std::cout << "Welcome " << playerName << " !" << std::endl;
	}

	std::cout << "\nEach player gets " << playerCoins << " coins." << std::endl;
	return players;
}

vector<Player*> GameStart::detPlayerBotCount()
{
	startSetup();

	int playerCoins = 0;
	string playerName;
	vector<Player*> players;
	int strategyOfBots = 0;

	std::cout << "You'll be playing against 1 bot." << std::endl;

	while (playerName.empty()) {
		std::cout << "\nEnter your player name : ";
		getline(std::cin, playerName);
	}

	players.push_back(new Player(playerName, playerCoins, new HumanStrategy()));
	std::cout << "Welcome " << playerName << " !" << std::endl;
	
	std::cout << "What type of bot do you want to play against:" << std::endl;
	while (strategyOfBots < 1 || strategyOfBots > 2)
	{
		std::cout << "What type of bot do you want to play against:" << std::endl;
		std::cout << "1 - Greedy" << std::endl;
		std::cout << "2 - Moderate" << std::endl;
		std::cin >> strategyOfBots;

		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter a NUMBER: ";
			std::cin >> strategyOfBots;
		}
	}

	std::cin.ignore();

	Player* bot = strategyOfBots == 1 ? new Player("GreedyBot", playerCoins, new GreedyStrategy()) : new Player("ModerateBot", playerCoins, new ModerateStrategy());
	players.push_back(bot);

	std::cout << "Human is playing against " + bot->getName() << std::endl;


	return players;
}

vector<Player*> GameStart::detBotCount() {

	int playerCoins = 14;
	vector<Player*> bots = {};
	int strategyOfBots = 0;

	while (strategyOfBots < 1 || strategyOfBots >4)
	{
		std::cout << "There will be two bots playing in the tournament. Choose the strategy you want the bot to play:" << std::endl;
		std::cout << "1 - Greedy vs Greedy" << std::endl;
		std::cout << "2 - Moderate vs Greedy" << std::endl;
		std::cout << "3 - Moderate vs Moderate" << std::endl;
		std::cin >> strategyOfBots;

		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter a NUMBER: ";
			std::cin >> strategyOfBots;
		}
	}

	// Assigning Bots to their strategies
	switch (strategyOfBots) {
		case 1:
			bots.push_back(new Player("GreedyBot1", playerCoins, new GreedyStrategy()));
			bots.push_back(new Player("GreedyBot2", playerCoins, new GreedyStrategy()));
			break;

		case 2:
			bots.push_back(new Player("ModerateBot", playerCoins, new ModerateStrategy()));
			bots.push_back(new Player("GreedyBot", playerCoins, new GreedyStrategy()));
			break;
		case 3:
			bots.push_back(new Player("ModerateBot1", playerCoins, new ModerateStrategy()));
			bots.push_back(new Player("ModerateBot2", playerCoins, new ModerateStrategy()));
			break;
		}
	std::cin.ignore();

	return bots;
}

void GameStart::startGame()
{
	state = "WELCOME TO EMPIRE LEGENDS. THE GAME IS ABOUT TO START.";
	Notify();
}

void GameStart::startSetup()
{
	state = "Setting Up Players.";
	Notify();
}

GameStartObserver::GameStartObserver(GameStart* s)
{
	subject = s;
	subject->Attach(this);
}

GameStartObserver::~GameStartObserver()
{
	subject->Detach(this);
}

void GameStartObserver::Update()
{
	display();
}

void GameStartObserver::display()
{
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "Game Start Phase: " << subject->getState() << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
}
