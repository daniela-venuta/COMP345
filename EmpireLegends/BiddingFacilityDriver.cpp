#include <iostream>
#include <vector>
#include "Player.h"
#include "BiddingFacility.h"

using namespace std;

int main() {

	// variables 
	int numofPlayers;
	int PlayerCoins;
	string username; 
	vector <Player*> myPlayers; 
	BiddingFacility BiddingFacility(); 

	cout << "--------------------------" << endl;
	cout << "Eight-Minute-Empire Game" << endl; 
	cout << "--------------------------" << endl;
	
	// determines how many coins per player
	cout << "\nNumber of players in the game (2-4): ";
	cin >> numofPlayers;

	switch (numofPlayers) {

	case 2:
		PlayerCoins = 14;
		cout << "Each player gets 14 coins" << endl;
		break;

	case 3:
		PlayerCoins = 11;
		cout << "Each player gets 11 coins" << endl;
		break;

	case 4:
		PlayerCoins = 9;
		cout << "Each player gets 9 coins" << endl;
		break;

	default:
		while (numofPlayers > 4 || numofPlayers < 2) {
			cout << "Invalid number of players";
			cout << "\nNumber of players in the game (2-4): ";
			cin >> numofPlayers;
		}
	}
	
	// enable the player objects and store in vector 
	cout << "Who will be playing the game: " << endl; 
	for (int i = 0; i < numofPlayers; i++) {
		cout << "Player: "; 
		cin >> username; 
		
		// creates a new pointer for each player object
		Player* p = NULL;

		// Loads the vector with Player objects
		p = new Player(username, PlayerCoins);
		myPlayers.push_back(p);
	}
	
	// place bid 
	int a = BiddingFacility::PlaceBid(myPlayers);
		
	
	
	
	// compare the bids 

	return 0; 
}