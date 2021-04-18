#include "GameStart.h"
#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"
#include "PlayerStrategies.h"
#include <iostream>


GameMap* GameStart::loadMap() {

	startGame();

	state = "Map Selection";
	Notify();

	MapLoader* mapLoader = new MapLoader();
	int x = 0;
	std::cout << "Please enter the type of map you wish to play with." << std::endl;
	std::cout << "	- Enter 1 for a rectangular map (4 continents)." << std::endl;
	std::cout << "	- Enter 2 for an L-shaped map (3 continents)." << std::endl;
	std::cout << "	- Enter 3 for a T-shaped map (4 continents)." << std::endl;
	std::cin >> x;

	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Bad entry.  Enter a NUMBER: ";
		std::cin >> x;
	}

	GameMap* gameMap = nullptr;
	switch (x) {
	case 1:
		gameMap = mapLoader->load("map_rectangle.json");
		break;
	case 2:
		gameMap = mapLoader->load("map_L.json");
		break;
	case 3:
		gameMap = mapLoader->load("map_T.json");
		break;
	default:
		while (x < 1 || x > 3) {
			std::cout << "INVALID selection." << std::endl;
			std::cout << "Please enter the type of map you wish to play with." << std::endl;
			std::cout << "	- Enter 1 for a rectangular map (4 continents)." << std::endl;
			std::cout << "	- Enter 2 for an L-shaped map (3 continents)." << std::endl;
			std::cout << "	- Enter 3 for an T-shaped map (4 continents)." << std::endl;
			std::cin >> x;
		}
	}

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
	string playerName = "";
	int numOfPlayers = 2;
	vector<Player*> players = {};
	int strategyOfBots = 0;

	std::cout << "You'll be playing against 1 bot." << std::endl;

	while (playerName == "") {
		std::cout << "\nEnter your player name : ";
		getline(std::cin, playerName);
		Player* temp = new Player(playerName, playerCoins, new HumanStrategy());
		players.push_back(temp);
		std::cout << "Welcome " << playerName << " !" << std::endl;
	};

	std::cout << "What type of bot do you want to play against:" << std::endl;
	while (strategyOfBots < 1 || strategyOfBots > 3)
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
	};

	std::cin.ignore();

	Player* bot = new Player();

	switch (strategyOfBots) {
	case 1:
		bot = new Player("GreedyBot", playerCoins, new GreedyStrategy());
		players.push_back(bot);
		break;

	case 2:
		bot = new Player("ModerateBot", playerCoins, new ModerateStrategy());
		players.push_back(bot);
		break;
	}

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

	// Assign Bots to their strategies
	Player* greedy1 = new Player("GreedyBot1", playerCoins, new GreedyStrategy());
	Player* greedy2 = new Player("GreedyBot2", playerCoins, new GreedyStrategy());
	Player* moderate1 = new Player("ModerateBot1", playerCoins, new ModerateStrategy());
	Player* moderate2 = new Player("ModerateBot2", playerCoins, new ModerateStrategy());

	switch (strategyOfBots) {
	case 1:
		bots.push_back(greedy1);
		bots.push_back(greedy2);
		break;

	case 2:
		bots.push_back(moderate1);
		bots.push_back(greedy2);
		break;

	case 3:
		bots.push_back(moderate1);
		bots.push_back(moderate2);
		break;
	}

	std::cin.ignore();

	return bots;
}

GameStart::GameStart()
{
	state = "";
}

GameStart::~GameStart()
{
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
