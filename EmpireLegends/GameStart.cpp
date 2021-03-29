#include "GameStart.h"
#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>

GameStart::GameStart() {
	mapType = 0;
	numOfPlayers = 0;
}

GameStart::~GameStart() {
	mapType = 0;
	numOfPlayers = 0;
	for (Player* player : players) {
		delete player;
	}
}

void GameStart::loadMap() {

	MapLoader* mapLoader = new MapLoader();

	std::cout << "------------------------------" << std::endl;
	std::cout << "Eight-Minute-Empire: Legends" << std::endl;
	std::cout << "-----------------------------" << std::endl;

	std::cout << "Please enter the type of map you wish to play with." << std::endl;
	std::cout << "	- Enter 1 for a rectangular map (4 continents)." << std::endl;
	std::cout << "	- Enter 2 for an L-shaped map (3 continents)." << std::endl;
	std::cout << "	- Enter 3 for a T-shaped map (4 continents)." << std::endl;
	std::cin >> mapType;

	// Choose which map type is being used
	switch (mapType) {
	case 1:
		mapLoader->load("map_rectangle.json");
		break;
	case 2:
		mapLoader->load("map_L.json");
		break;
	case 3:
		mapLoader->load("map_T.json");
		break;
	default:
		while (mapType < 1 || mapType > 3) {
			std::cout << "INVALID selection." << std::endl;
			std::cout << "Please enter the type of map you wish to play with." << std::endl;
			std::cout << "	- Enter 1 for a rectangular map (4 continents)." << std::endl;
			std::cout << "	- Enter 2 for an L-shaped map (3 continents)." << std::endl;
			std::cout << "	- Enter 3 for an T-shaped map (4 continents)." << std::endl;
			std::cin >> mapType;
		}
	}
}

void GameStart::detPlayerCount() {

	int playerCoins;
	string playerName;

	while (numOfPlayers < 2 || numOfPlayers > 4)
	{
		std::cout << "How many players will be playing? Please select a number between 2 and 4: ";
		std::cin >> numOfPlayers;
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

	players.clear();
	std::cin.ignore();

	for (auto i = 0; i < numOfPlayers; i++)
	{
		std::cout << "Enter player name " << i + 1 << ": ";
		getline(std::cin, playerName);
		players.push_back(new Player(playerName, playerCoins));
		std::cout << "Welcome " << playerName << " !" << std::endl;
	}

	std::cout << "\nEach player gets " << playerCoins << " coins." << std::endl;
}
