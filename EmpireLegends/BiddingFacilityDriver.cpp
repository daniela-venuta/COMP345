#include <iostream>
#include <vector>
#include "Player.h"
#include "BiddingFacility.h"
#include <algorithm>

using namespace std;

int main() {

	// variables 
	int numofPlayers;
	int PlayerCoins = 0;
	string username; 
	vector <Player*> myPlayers; 
	BiddingFacility* bidFac = new BiddingFacility();
	Player* pl = new Player(); 

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
	cout << "\nWho will be playing the game: " << endl; 
	for (auto i = 0; i < numofPlayers; i++) {
		cout << "Player: "; 
		cin >> username; 
		
		// creates a new pointer for each player object and adds it to the player vector
		myPlayers.push_back(new Player(username, PlayerCoins));
	}
	
	// Players place bids
	bidFac->placeBids(myPlayers);

	return 0; 
}