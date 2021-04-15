#include "GameStart.h"
#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"
#include "PlayerStrategies.h"
#include <iostream>

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

	MapLoader* mapLoader = new MapLoader();
	int x = 0;
	std::cout << "Please enter the type of map you wish to play with." << std::endl;
	std::cout << "	- Enter 1 for a rectangular map (4 continents)." << std::endl;
	std::cout << "	- Enter 2 for an L-shaped map (3 continents)." << std::endl;
	std::cout << "	- Enter 3 for a T-shaped map (4 continents)." << std::endl;
	std::cin >>x;

	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Bad entry.  Enter a NUMBER: ";
		std::cin >> x;
	}

	//typeMap = x;
	// Choose which map type is being used
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
	Player* greedy1 = new Player("Greedy 1", playerCoins, new GreedyStrategy());
	Player* greedy2 = new Player("Greedy 2", playerCoins, new GreedyStrategy());
	Player* moderate1 = new Player("Moderate 1", playerCoins, new ModerateStrategy());
	Player* moderate2 = new Player("Moderate 2", playerCoins, new ModerateStrategy());

	switch (strategyOfBots) {
	case 1:
		bots.push_back(greedy1);
		bots.push_back(greedy2);
		break;

	case 2:
		bots.push_back(moderate1);
		bots.push_back(greedy1);
		break;

	case 3:
		bots.push_back(moderate1);
		bots.push_back(moderate2);
		break;
	}
	
	std::cin.ignore();

	return bots;	
}
