//#include <iostream>
//#include "Player.h"
//#include "MapUtility.h"
//
//int main() {
//	// Create player pointers
//	auto* p1 = new Player("player1");
//	auto* p2 = new Player("player2");
//	auto* p3 = new Player("player3");
//	auto* p4 = new Player("player4");
//
//	std::cout << std::endl;
//	std::cout << "P1 balance: " << p1->getBalance() << " coins." << std::endl;
//	std::cout << "P2 balance: " << p2->getBalance() << " coins." << std::endl;
//	std::cout << "P3 balance: " << p3->getBalance() << " coins." << std::endl;
//	std::cout << "P4 balance: " << p4->getBalance() << " coins." << std::endl;
//
//	std::cout << std::endl;
//	p1->PayCoin(2);
//	p2->PayCoin(0);
//	p3->PayCoin(9);
//	p4->PayCoin(-5); // should output error message claiming unsufficient funds
//
//	std::cout << std::endl;
//	std::cout << "P1 balance: " << p1->getBalance() << " coins." << std::endl;
//	std::cout << "P2 balance: " << p2->getBalance() << " coins." << std::endl;
//	std::cout << "P3 balance: " << p3->getBalance() << " coins." << std::endl;
//	std::cout << "P4 balance: " << p4->getBalance() << " coins." << std::endl;
//
//	// create game map
//	GameMap* gameMap = MapUtility::createValidMap();
//	try
//	{
//		auto* t1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
//		auto* t3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
//		auto* t4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");
//		auto* t8 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 8");
//
//		std::cout << std::endl;
//		std::cout << "preliminary placement of armies...." << std::endl;
//		p1->PlaceNewArmies(3, t1);
//		p2->PlaceNewArmies(2, t1);
//		p3->PlaceNewArmies(15, t4);
//		p4->PlaceNewArmies(17, t4);
//
//		std::cout << std::endl;
//		std::cout << "============ MOVING ARMIES ============" << std::endl;
//
//		p1->MoveArmies(3, t1, t4, gameMap);
//		p2->MoveArmies(-5, t3, t8, gameMap); // should output error message (invalid number of armies; negative number)
//		p2->MoveArmies(2, t1, t4, gameMap);
//		p3->MoveArmies(20, t4, t8, gameMap); // should output error message (invalid number of armies; insufficient armies)
//		p3->MoveArmies(15, t4, t8, gameMap);
//		p4->MoveArmies(10, t1, t1, gameMap); // should output error message (invalid destination region)
//		p4->MoveArmies(17, t4, t8, gameMap);
//
//		std::cout << std::endl;
//		std::cout << "T1 army count: " << t1->getArmyCount() << " armies." << std::endl;
//		std::cout << "T3 army count: " << t3->getArmyCount() << " armies." << std::endl;
//		std::cout << "T4 army count: " << t4->getArmyCount() << " armies." << std::endl;
//		std::cout << "T8 army count: " << t8->getArmyCount() << " armies." << std::endl;
//
//		std::cout << std::endl;
//		std::cout << "============ PLACING NEW ARMIES ============" << std::endl;
//
//		p1->PlaceNewArmies(20, t4); // should output error message (invalid number of armies; insufficient armies)
//		p1->PlaceNewArmies(4, t4);
//		p2->PlaceNewArmies(-5, t4); // should output error message (invalid number of armies; negative number)
//		p2->PlaceNewArmies(1, t4);
//		p3->PlaceNewArmies(0, t8); // should output error message (invalid number of armies; can't add zero)
//		p3->PlaceNewArmies(3, t8);
//		p4->PlaceNewArmies(5, t8); // should output error message (invalid number of armies; insufficient armies)
//		p4->PlaceNewArmies(1, t8);
//
//		std::cout << std::endl;
//		std::cout << "T1 army count: " << t1->getArmyCount() << " armies." << std::endl;
//		std::cout << "T3 army count: " << t3->getArmyCount() << " armies." << std::endl;
//		std::cout << "T4 army count: " << t4->getArmyCount() << " armies." << std::endl;
//		std::cout << "T8 army count: " << t8->getArmyCount() << " armies." << std::endl;
//
//		std::cout << std::endl;
//		std::cout << "============ DESTROYING ARMIES ============" << std::endl;
//
//		p1->DestroyArmy(3, t4);
//		p2->DestroyArmy(8, t4); //should output error message (invalid number of armies; not enough armies to destroy)
//		p2->DestroyArmy(2, t4);
//		p3->DestroyArmy(-9, t8); // should output error message (invalid number of armies; negative)
//		p3->DestroyArmy(15, t8);
//		p4->DestroyArmy(7, t8); //should output error message (invalid number of armies; not enough armies to destroy)
//
//		std::cout << std::endl;
//		std::cout << "T1 army count: " << t1->getArmyCount() << " armies." << std::endl;
//		std::cout << "T3 army count: " << t3->getArmyCount() << " armies." << std::endl;
//		std::cout << "T4 army count: " << t4->getArmyCount() << " armies." << std::endl;
//		std::cout << "T8 army count: " << t8->getArmyCount() << " armies." << std::endl;
//
//		std::cout << std::endl;
//		std::cout << "============ BUILDING CITIES ============" << std::endl;
//
//		p1->BuildCity(t1);
//		p1->BuildCity(t1);
//		p1->BuildCity(t1);
//		p1->BuildCity(t1); // should output error message (exceeds city count)
//		p2->BuildCity(t3); // should output error message (no armies present; cannot place city)
//	}
//	catch (TerritoryNotFoundException& e)
//	{
//		std::cout << e << std::endl;
//	}
//}