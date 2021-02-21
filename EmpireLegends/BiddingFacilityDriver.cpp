//#include <iostream>
//#include <vector>
//#include "Player.h"
//#include "BiddingFacility.h"
//#include <algorithm>
//
//int main() {
//	// variables 
//	int numofPlayers;
//	int PlayerCoins = 0;
//	string username; 
//	vector <Player*> myPlayers; 
//	auto* bidFac = new BiddingFacility();
//
//	std::cout << "--------------------------" << std::endl;
//	std::cout << "Eight-Minute-Empire Game" << std::endl;
//	std::cout << "--------------------------" << std::endl;
//	
//	// determines how many coins per player
//	std::cout << "\nNumber of players in the game (2-4): ";
//	std::cin >> numofPlayers;
//
//	switch (numofPlayers) {
//
//	case 2:
//		PlayerCoins = 14;
//		std::cout << "Each player gets 14 coins" << std::endl;
//		break;
//
//	case 3:
//		PlayerCoins = 11;
//		std::cout << "Each player gets 11 coins" << std::endl;
//		break;
//
//	case 4:
//		PlayerCoins = 9;
//		std::cout << "Each player gets 9 coins" << std::endl;
//		break;
//
//	default:
//		while (numofPlayers > 4 || numofPlayers < 2) {
//			std::cout << "Invalid number of players";
//			std::cout << "\nNumber of players in the game (2-4): ";
//			std::cin >> numofPlayers;
//		}
//	}
//	
//	// enable the player objects and store in vector 
//	std::cout << "\nWho will be playing the game: " << std::endl; 
//	for (auto i = 0; i < numofPlayers; i++) {
//		std::cout << "Player: ";
//		std::cin >> username; 
//		
//		// creates a new pointer for each player object and adds it to the player vector
//		myPlayers.push_back(new Player(username, PlayerCoins));
//	}
//	
//	// Players place bids
//	bidFac->placeBids(myPlayers);
//
//	return 0; 
//}