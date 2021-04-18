#include "GameStart.h"
#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"
#include "PlayerStrategies.h"

#include <iostream>
#include <fstream>
#include <string>

//Game Engine Commented
GameStart::GameStart() {
	//  typeMap = 0;
	  //numOfPlayers = 0;
	//players = {};
	//biddingPlayers = {};
}

GameStart::~GameStart() {
	//typeMap = 0;
	//numOfPlayers = 0;
	/*for (Player* player : players) {
		delete player;
	}*/
}

GameMap* GameStart::loadMap() {

	startGame();
	
	state = "Map Selection";
	Notify();
	
	MapLoader* mapLoader = new MapLoader();

	string fileName = "";
	std::cout << "Please enter the name of the map you wish to play with." << std::endl;
	std::getline(std::cin, fileName);

	// Choose which map type is being used
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

	//players.clear();
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

	std::cout << "You'll be playing against 1 bot."<<std::endl;

	while (playerName == "") {
		std::cout << "\nEnter your player name : ";
		std::cin >> playerName;
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
	};

	std::cin.ignore();

	Player* bot = new Player();
	
	switch (strategyOfBots) {
	case 1:
		bot= new Player("GreedyBot", playerCoins, new GreedyStrategy());
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

//vector<Player*> GameStart::getPlayers()
//{
//	return players;
//}

vector<Player*> GameStart::detBotCount() {

	int playerCoins = 14;
	vector<Player*> bots = {};
	int strategyOfBots = 0;

	while (strategyOfBots <1 || strategyOfBots >4)
	{
		std::cout << "There will be two bots playing in the tournament. Choose the strategy you want the bot to play:"<<std::endl;
		std::cout << "1 - Greedy vs Greedy" << std::endl;
		std::cout << "2 - Moderate vs Greedy" << std::endl;
		std::cout << "3 - Moderate vs Moderate" << std::endl;
		std::cin >> strategyOfBots;
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
