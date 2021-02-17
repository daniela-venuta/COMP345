#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

int main() {


	int numofPlayers;
	int PlayerCoins;
	vector <Player> myPlayers; 

	// determines how many coins per player
	cout << "\n Number of players in the game (2-4): ";
	cin >> numofPlayers;

	switch (numofPlayers) {

	case 2:
		PlayerCoins = 14;
		cout << " Each player gets 14 coins" << endl;
		break;

	case 3:
		PlayerCoins = 11;
		cout << " Each player gets 11 coins" << endl;
		break;

	case 4:
		PlayerCoins = 9;
		cout << " Each player gets 9 coins" << endl;
		break;

	default:
		while (numofPlayers > 4 || numofPlayers < 2) {
			cout << "Invalid number of players";
			cout << "\nNumber of players in the game (2-4): ";
			cin >> numofPlayers;
		}
	}
	
	// enable the player objects 


	// compare the bids 

}