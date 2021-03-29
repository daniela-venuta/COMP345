#include "Player.h"

#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	vector<Player*> players{};
	players.push_back(new Player("p1"));
	players.push_back(new Player("p2"));

	// Compute individual VPs
	for (Player* player : players) {
		player->computeScore();
	}

	std::cout << "Determining the winner...";

	// 2VP for max elixir
	Player* mostElixirs{};
	for (int i = 0; i < players.size() - 1; i++) {
		if (players.at(i)->getResources()->elixir > players.at(i+1)->getResources()->elixir) {
			mostElixirs = players.at(i);
		}
		else {
			mostElixirs = players.at(i+1);
		}
	}

	mostElixirs->addVictoryPoints(2);

	// Determine winner
	vector<Player*> highestVPplayers;
	int highestVP = 0;
	for (Player* player : players) {
		int playerVP = player->getVictoryPoints();
		if (playerVP <= highestVP) {
			// New highest VP count
			if (highestVP < playerVP)
			{
				highestVP = playerVP;
				highestVPplayers.clear(); // Clearing highest VP player vector for new highest
			}
			highestVPplayers.push_back(player);
		}
	}

	// Tie on most VPs (most coins owned wins)
	vector<Player*> richestPlayers;
	int highestCoins = 0;

	if (highestVPplayers.size() > 1) {
		std::cout << "\nThere is a tie for victory points." << std::endl;
		std::cout << "\nSorting by number of coins..." << std::endl;

		for (Player* player : players) {
			int playerCoins = player->getCoins();
			if (playerCoins <= highestCoins) {
				// New highest coin count
				if (highestCoins < playerCoins)
				{
					highestCoins = playerCoins;
					richestPlayers.clear(); // Clearing highest coin count vector for new highest
				}
				richestPlayers.push_back(player);
			}
		}

		// Tie on most coins (most armies owned wins)
		vector<Player*> mostArmiesPlayers;
		int highestArmyCount = 0;

		if (richestPlayers.size() > 1) {
			std::cout << "\nThere is a tie for number of coins." << std::endl;
			std::cout << "\nSorting by number of armies..." << std::endl;

			for (Player* player : players) {
				int playerArmies = 18 - player->getResources()->unplacedArmies;
				if (playerArmies <= highestArmyCount) {
					// New highest army count
					if (highestArmyCount < playerArmies)
					{
						highestArmyCount = playerArmies;
						mostArmiesPlayers.clear(); // Clearing highest army count vector for new highest
					}
					mostArmiesPlayers.push_back(player);
				}
			}

			// Tie on most armies (most regions owned wins)
			Player* mostRegionsOwnedPlayer;
			int highestNumberOfRegions = 0;

			if (mostArmiesPlayers.size() > 1) {
				std::cout << "\nThere is a tie for number of armies." << std::endl;
				std::cout << "\nSorting by number of region..." << std::endl;

				for (Player* player : players) {
					int playerRegions = player->getTerritories().size();
					if (highestNumberOfRegions < playerRegions) {
						highestNumberOfRegions = playerRegions;
						mostRegionsOwnedPlayer = player;
					}
				}
			}
			else {
				std::cout << "The winner is " << mostRegionsOwnedPlayer->getName() << "!" << std::endl;
			}
		}
		else {
			std::cout << "The winner is " << mostArmiesPlayers.back() << "!" << std::endl;
		}
	}
	else {
		std::cout << "The winner is " << richestPlayers.back() << "!" << std::endl;
	}
}