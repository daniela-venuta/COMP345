#include <iostream>
#include <sstream>

#include "MapLoader.h"
#include "Player.h"
#include "BiddingFacility.h"

using namespace std;

int main() {

	// MAP VARIABLES
	int mapType;
	auto* mapLoader = new MapLoader();

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

	// PLAYER VARIABLES
	Player* p1, * p2, * p3, * p4;
	string playerName1, playerName2, playerName3, playerName4;
	int numofPlayers = 0, playerCoins = 0;

	std::cout << "How many players will be playing? Please select a number between 2 and 4: ";
	std::cin >> numofPlayers;

	// Assign coins according to numofPlayers
	switch (numofPlayers) {
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
		getline(cin, playerName1);
		p1 = new Player(playerName1, playerCoins);
		std::cout << "Welcome " << playerName1 << " !" << std::endl;

		std::cout << "\nEnter player name 2: ";
		getline(cin, playerName2);
		p2 = new Player(playerName2, playerCoins);
		std::cout << "Welcome " << playerName2 << " !" << std::endl;

		std::cout << "\nEnter player name 3: ";
		getline(cin, playerName3);
		p3 = new Player(playerName3, playerCoins);
		std::cout << "Welcome " << playerName3 << " !" << std::endl;

		std::cout << "\nEach player gets 11 coins." << std::endl;

		break;

	case 4:

		playerCoins = 9;

		std::cout << "Enter player name 1: ";
		std::cin.ignore();
		getline(cin, playerName1);
		p1 = new Player(playerName1, playerCoins);
		std::cout << "Welcome " << playerName1 << " !" << std::endl;

		std::cout << "\nEnter player name 2: ";
		getline(cin, playerName2);
		p2 = new Player(playerName2, playerCoins);
		std::cout << "Welcome " << playerName2 << " !" << std::endl;

		std::cout << "\nEnter player name 3: ";
		getline(cin, playerName3);
		p3 = new Player(playerName3, playerCoins);
		std::cout << "Welcome " << playerName3 << " !" << std::endl;

		std::cout << "\nEnter player name 4: ";
		getline(cin, playerName4);
		p4 = new Player(playerName4, playerCoins);
		std::cout << "Welcome " << playerName4 << " !" << std::endl;

		std::cout << "\nEach player gets 9 coins." << std::endl;

		break;

	default:
		while (numofPlayers > 4 || numofPlayers < 2) {
			std::cout << "INVALID number of players." << std::endl;
			std::cout << "Please select a number between 2 and 4: ";
			std::cin >> numofPlayers;
		}
	}

	// BIDING FACILITY VARIABLES
	BiddingFacility* biddingFacility = new BiddingFacility();
	vector <Player*> biddingPlayers;

	std::cout << "Entering the bidding phase with " << numofPlayers << " players..." << std::endl;

	// Allow players to place their bids
	switch (numofPlayers) {
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

	// CARD VARIABLES
	Card* card1 = new Card("Dire dragon", "Flying", "Place 3 armies and destroy one army");
	Card* card2 = new Card("Dire giant", "Immune to attack", "Place 3 armies and destroy army");
	Card* card3 = new Card("Dire eye", "Flying", "Place 4 armies");
	Card* card4 = new Card("Dire Goblin", " +1 elixer", "Move 5 armies");
	Card* card5 = new Card("Dire Ogre", " +1 VP per 3 coins", "Move 2 armies");
	Card* card6 = new Card("Lake", " +1 VP per Forest card", "Place 2 armies and move 3 armies");
	Card* card7 = new Card("Forest Elf", " +1 army", "Place 3 armies or movie 2 armies");
	Card* card8 = new Card("Forest Gnome", " +3 elixer", "Move 2 armies");
	Card* card9 = new Card("Forest Tree Town", "Move 1 army", "Place a city");
	Card* card10 = new Card("Graveyard", " +1VP per Cursed card", "Place 2 armies");
	Card* card11 = new Card("Noble Hills", " Three noble cards = 4 VP", "Place 3 armies");
	Card* card12 = new Card("Mountain Treasury", " +1 elixer and +2 coins", "Move 3 armies");
	Card* card13 = new Card("Castle", " +1 elixer", "Place 3 armies or build a city");

	// Add Cards to Deck
	vector<Card*> cardVector;
	cardVector.push_back(card1);
	cardVector.push_back(card2);
	cardVector.push_back(card3);
	cardVector.push_back(card4);
	cardVector.push_back(card5);
	cardVector.push_back(card6);
	cardVector.push_back(card7);
	cardVector.push_back(card8);
	cardVector.push_back(card9);
	cardVector.push_back(card10);
	cardVector.push_back(card11);
	cardVector.push_back(card12);
	cardVector.push_back(card13);

	std::cout << "Printing deck:" << std::endl;
	Deck* deck = new Deck(cardVector);
	std::cout << *deck;
}