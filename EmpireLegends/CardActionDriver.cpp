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
//	vector<Player*> currentPlayers;
//
//	auto* r1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
//	auto* r2 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 2");
//	auto* r3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
//	auto* r4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");
//
//
//	auto* p1 = new Player("PlayerA");
//	currentPlayers.push_back(p1);
//	auto* p2 = new Player("PlayerB");
//	currentPlayers.push_back(p2);
//	p1->getResources();
//
//	
//	std::cout << "===== Tests of Main Loop Game - Card Actions =====" << std::endl;
//	std::cout << "\n";
//	//PayCoin()
//	std::cout << "-- Pay Coin() Tests --" << std::endl;
//	p1->PayCoin(2);//success
//	p2->PayCoin(15);//fail
//	std::cout << "\n\n";
//
//	//PlaceNewArmies() + BuildCity()
//	std::cout << "-- BuildCity() + PlaceNewArmies() Tests --" << std::endl;
//	p1->BuildCity(r1);//fail
//
//	p1->PlaceNewArmies(3, r1);//succeed
//	p2->PlaceNewArmies(3, r1);//succeed
//
//	p2->BuildCity(r4);//fail
//	p2->PlaceNewArmies(1, r4);//fail
//	std::cout << "\n\n";
//
//	//MoveArmies() + MoveOverLand()
//	std::cout << "-- MoverArmies Tests (Over Land) --" << std::endl;
//	p2->MoveArmies(1, r1, r3, gameMap);//succeed
//	p2->MoveArmies(1, r4, r3, gameMap);//fail
//	p1->MoveArmies(3, r1, r3, gameMap);//succeed
//	std::cout << "\n\n";
//
//	//MoveArmies() + MoveOverWater()
//	std::cout << "-- MoverArmies Tests (Over Water) --" << std::endl;
//	p1->setCoins(20);
//	p1->MoveArmies(1, r3, r4, gameMap);//succeed
//	std::cout << "\n\n";
//
//	//DestroyArmy()
//	std::cout << "-- DestroyArmy Tests --" << std::endl;
//	p2->DestroyArmy(1, r4, currentPlayers); //fail - P2 doesn't have an army there
//	p2->DestroyArmy(3,r3, currentPlayers); //fail - There isn't a minimum 2 armies not owned by P2 on this Region
//	p2->DestroyArmy(2, r3, currentPlayers); //successs - Should destroy the army of P1 on this Region
//	std::cout << "\n\n";
//
//	//AndOrAction()
//	Card* c1 = new Card("Dire Dragon", new Flying, "Destroy Army", "Place New Armies");
//	Card* c2 = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
//
//	p1->AndOrAction(c2);
//	p2->AndOrAction(c1);
//
//	return 0;
//}