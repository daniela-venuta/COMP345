#include <iostream>

using namespace std;

int main() {


	int numofPlayers;
	int PlayerCoins;

	// determines how many coins per player
	cout << "\n Number of players in the game (2-4): ";
	cin >> numofPlayers;

	while (numofPlayers > 4 || numofPlayers < 2) {
		cout << "Invalid number of players";
		cout << "\nNumber of players in the game (2-4): ";
		cin >> numofPlayers;
	}

	if (numofPlayers == 2) {
		PlayerCoins = 14;
		cout << " Each player gets 14 coins" << endl;

	}
	else if (numofPlayers == 3) {
		PlayerCoins = 11;
		cout << " Each player gets 11 coins" << endl;

	}
	else if (numofPlayers == 4) {
		PlayerCoins = 9;
		cout << " Each player gets 9 coins" << endl;
	}

	// enable the player objects 


	// compare the bids 

}