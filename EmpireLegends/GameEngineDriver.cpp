#include "GameEngine.h"
#include <iostream>

int main() {

	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Welcome to the Eight-Minute Empire Game " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;

	GameEngine* gameEngine = new GameEngine();
	int choice;

	std::cout << "\nPick a Game Mode " << std::endl;
	std::cout << "\t1- Single Mode " << std::endl;
	std::cout << "\t2- Tournament Mode " << std::endl;
	std::cout << "\nEnter choice here: ";
	std::cin >> choice;

	switch (choice) {
	case 1:
		gameEngine->singleMode();
		break;

	case 2:
		gameEngine->tournamentMode();
		break;
	}

	delete gameEngine;
	return 0;

}
