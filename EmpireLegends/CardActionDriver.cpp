//#include "Player.h"
//#include "MapLoader.h"
//#include <string>
//
//
////Tests for Part 4 in A2 
//
//int main() {
//
//	auto* mapLoader = new MapLoader();
//	auto* gameMap = mapLoader->load("valid_map_1.json");
//
//	auto* r1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
//	auto* r2 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 2");
//	auto* r3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
//	auto* r4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");
//
//
//	auto* p1 = new Player("PlayerA");
//	auto* p2 = new Player("PlayerB");
//	p1->getResources();
//
//	
//	std::cout << "=====Tests of Main Loop Game - Card Actions:" << std::endl;
//	std::cout << "\n";
//	//PayCoin()
//	std::cout << "--Pay Coin():" << std::endl;
//	std::cout << "\n";
//	p1->PayCoin(2);//success
//	p2->PayCoin(15);//fail
//	std::cout << "\n\n";
//
//	//PlaceNewArmies() + BuildCity(
//	std::cout << "--BuildCity() + PlaceNewArmies():" << std::endl;
//	std::cout << "\n";
//	p1->BuildCity(r1);//fail
//
//	p1->PlaceNewArmies(2, r1);//succeed
//	p2->PlaceNewArmies(3, r1);//succeed
//
//	p2->BuildCity(r4);//fail
//	p2->PlaceNewArmies(1, r4);//fail
//	std::cout << "\n\n";
//
//	//MoveArmies() + MoveOverLand()
//	std::cout << "--MoveArmies() + MoveOverLand():" << std::endl;
//	std::cout << "\n";
//	p2->MoveArmies(1, r1, r3, gameMap);//succeed
//	p2->MoveArmies(1, r4, r3, gameMap);//fail
//	p1->MoveArmies(2, r1, r3, gameMap);//succeed
//	std::cout << "\n\n";
//
//	//MoveArmies() + MoveOverWater()
//	std::cout << "--MoveArmies() + MoveOverWater():" << std::endl;
//	std::cout << "\n";
//	p1->setCoins(20);
//	p1->MoveArmies(2, r3, r4, gameMap);
//
//	//BuildCity()
//
//	//DestroyArmy()
//
//	//AndOrAction()
//
//	Card* c1 = new Card("Dire Dragon", new Flying, "Destroy Army", "Place New Armies");
//	Card* c2 = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
//
//	p1->AndOrAction(c2);
//	p2->AndOrAction(c1);
//
//	return 0;
//}