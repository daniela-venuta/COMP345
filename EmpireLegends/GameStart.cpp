#include "GameStart.h"
#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>

GameStart::GameStart() {
	mapType = 0;
	numOfPlayers = 0;
	p1 = nullptr;
	p2 = nullptr;
	p3 = nullptr;
	p4 = nullptr;
	biddingFacility = new BiddingFacility();
}

GameStart::~GameStart() {
	mapType = 0;
	numOfPlayers = 0;
	playerName1 = "";
	playerName2 = "";
	playerName3 = "";
	playerName4 = "";
	delete p1, p2, p3, p4;
	biddingFacility = nullptr;
}

void GameStart::loadMap() {

	MapLoader* mapLoader = new MapLoader();

	std::cout << "------------------------------" << std::endl;
	std::cout << "Eight-Minute-Empire: Legends" << std::endl;
	std::cout << "-----------------------------" << std::endl;

	std::cout << "Please enter the type of map you wish to play with." << std::endl;
	std::cout << "	- Enter 1 for a rectangular map (4 continents)." << std::endl;
	std::cout << "	- Enter 2 for an L-shaped map (3 continents)." << std::endl;
	std::cout << "	- Enter 3 for an T-shaped map (4 continents)." << std::endl;
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

	int playerCoins = 0;

	std::cout << "How many players will be playing? Please select a number between 2 and 4: ";
	std::cin >> numOfPlayers;

	// Assign coins according to numofPlayers
	switch (numOfPlayers) {
	case 2:

		playerCoins = 14;

		std::cout << "Enter player name 1: ";
		std::cin.ignore();
		getline(std::cin, playerName1);
		p1 = new Player(playerName1, playerCoins);
		std::cout << "Welcome " << playerName1 << " !" << std::endl;

		std::cout << "\nEnter player name 2: ";
		getline(std::cin, playerName2);
		p2 = new Player(playerName2, playerCoins);
		std::cout << "Welcome " << playerName2 << " !" << std::endl;

		std::cout << "\nEach player gets 14 coins." << std::endl;

		break;

	case 3:

		playerCoins = 11;

		std::cout << "Enter player name 1: ";
		std::cin.ignore();
		getline(std::cin, playerName1);
		p1 = new Player(playerName1, playerCoins);
		std::cout << "Welcome " << playerName1 << " !" << std::endl;

		std::cout << "\nEnter player name 2: ";
		getline(std::cin, playerName2);
		p2 = new Player(playerName2, playerCoins);
		std::cout << "Welcome " << playerName2 << " !" << std::endl;

		std::cout << "\nEnter player name 3: ";
		getline(std::cin, playerName3);
		p3 = new Player(playerName3, playerCoins);
		std::cout << "Welcome " << playerName3 << " !" << std::endl;

		std::cout << "\nEach player gets 11 coins." << std::endl;

		break;

	case 4:

		playerCoins = 9;

		std::cout << "Enter player name 1: ";
		std::cin.ignore();
		getline(std::cin, playerName1);
		p1 = new Player(playerName1, playerCoins);
		std::cout << "Welcome " << playerName1 << " !" << std::endl;

		std::cout << "\nEnter player name 2: ";
		getline(std::cin, playerName2);
		p2 = new Player(playerName2, playerCoins);
		std::cout << "Welcome " << playerName2 << " !" << std::endl;

		std::cout << "\nEnter player name 3: ";
		getline(std::cin, playerName3);
		p3 = new Player(playerName3, playerCoins);
		std::cout << "Welcome " << playerName3 << " !" << std::endl;

		std::cout << "\nEnter player name 4: ";
		getline(std::cin, playerName4);
		p4 = new Player(playerName4, playerCoins);
		std::cout << "Welcome " << playerName4 << " !" << std::endl;

		std::cout << "\nEach player gets 9 coins." << std::endl;

		break;

	default:
		while (numOfPlayers > 4 || numOfPlayers < 2) {
			std::cout << "INVALID number of players." << std::endl;
			std::cout << "Please select a number between 2 and 4: ";
			std::cin >> numOfPlayers;
		}
	}
}

void GameStart::playerBidding() {
	biddingFacility = new BiddingFacility();

	std::cout << "Entering the bidding phase with " << numOfPlayers << " players..." << std::endl;

	// Allow players to place their bids
	switch (numOfPlayers) {
	case 2:

		biddingPlayers.clear();
		biddingPlayers.push_back(p1);
		biddingPlayers.push_back(p2);

		biddingFacility->placeBids(biddingPlayers);

		break;

	case 3:

		biddingPlayers.clear();
		biddingPlayers.push_back(p1);
		biddingPlayers.push_back(p2);
		biddingPlayers.push_back(p3);

		biddingFacility->placeBids(biddingPlayers);

		break;

	case 4:

		biddingPlayers.clear();
		biddingPlayers.push_back(p1);
		biddingPlayers.push_back(p2);
		biddingPlayers.push_back(p3);
		biddingPlayers.push_back(p4);

		biddingFacility->placeBids(biddingPlayers);

		break;

	default:
		biddingPlayers.clear();
	}
}