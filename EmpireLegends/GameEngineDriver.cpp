//#include "GameEngine.h"
//#include <iostream>
//#include <fstream>
//
//int main() {
//	std::cout << "-----------------------------------------" << std::endl;
//	std::cout << "Welcome to the Eight-Minute Empire Game " << std::endl;
//	std::cout << "-----------------------------------------" << std::endl;
//
//	GameEngine* gameEngine = new GameEngine();
//	
//	int choice = 0;
//
//	std::cout << "\nPick a Game Mode " << std::endl;
//	std::cout << "\t1- Single Mode " << std::endl;
//	std::cout << "\t2- Tournament Mode " << std::endl;
//	std::cout << "\nEnter choice here: ";
//
//	while (choice < 1 || choice > 2)
//	{
//		std::cin >> choice;
//
//		if (std::cin.fail()) {
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			std::cout << "Bad entry. Enter a NUMBER: ";
//		} else if (choice < 1 || choice > 2) {
//			std::cin.clear();
//			std::cout << "Not a valid choice. Please try again: ";
//		}
//	}
//
//	choice == 1 ? gameEngine->singleMode() : gameEngine->tournamentMode();
//
//	delete gameEngine;
//	
//	return 0;
//}
