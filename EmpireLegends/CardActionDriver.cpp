//#include "Player.h"
//#include "MapLoader.h"
//
////Tests for Part 4 in A2 
//
//int main() {
//	MapLoader* mapLoader = new MapLoader();
//	auto* gameMap = mapLoader->load("valid_map_1.json");
//
//	auto* r1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
//	auto* r2 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 2");
//	auto* r3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
//	auto* r4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");
//
//	vector<Player*> currentPlayers;
//	auto* p1 = new Player("PlayerA", 60, new HumanStrategy());
//	currentPlayers.push_back(p1);
//	auto* p2 = new Player("PlayerB", 60, new HumanStrategy());
//	currentPlayers.push_back(p2);
//	
//	std::cout << "===== Tests of Main Loop Game - Card Actions =====" << std::endl;
//	std::cout << "\n";
//	//PayCoin()
//	std::cout << "-- Pay Coin() Tests --" << std::endl;
//	std::cout << p1->getName() + "'s turn: " << std::endl;
//	p1->payCoin(2);//success
//	std::cout << p2->getName() + "'s turn: " << std::endl;
//	std::cout << "\n";
//
//	p2->payCoin(15);//fail since funds are insufficient
//	std::cout << "\n\n";
//
//	p1->placeNewArmies(8, r1, r1);//success since it's the starting region
//
//	//MoveArmies (Over land)
//	std::cout << "-- MoverArmies Tests (Over Land) --" << std::endl;
//	p1->moveArmies(2, r2, r3, gameMap); //fail since there are no armies in r2
//	p1->moveArmies(2, r1, r3, gameMap); //success since there are armies in r1
//
//	//MoveArmies (over water)
//	std::cout << "-- MoverArmies Tests (Over Water) --" << std::endl;
//	p1->moveArmies(2, r1, r4, gameMap);
//
//	//PlaceNewArmies() + BuildCity()
//	std::cout << "-- BuildCity() + PlaceNewArmies() Tests --" << std::endl;
//	p1->buildCity(r2);//fail because no army is present
//	p1->buildCity(r3);//success since there are armies
//	std::cout << "\n";
//
//	//DestroyArmy()
//	std::cout << "-- DestroyArmy Tests --" << std::endl;
//	
//	//AndOrAction()
//	std::cout << "-- AndOrAction Tests --" << std::endl;
//	Card* c1 = new Card("Dire dragon", new Flying, new Action("Build city", 3), new Action("Destroy armies", 1), AndOr::AND);
//	Card* c2 = new Card("Dire giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 1), AndOr::AND);
//	Card* c3 = new Card("Dire eye", new Flying, new Action("Place armies", 4));
//	Card* c4 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::OR);
//
//	p2->placeNewArmies(4, r1, r1);
//	p2->moveArmies(2, r1, r2, gameMap);
//	
//	std::cout << "AND Action: " << std::endl;
//	p1->andOrAction(c1, gameMap);
//	std::cout << "\n";
//	p1->andOrAction(c1, gameMap);
//	std::cout << "\n";
//
//	std::cout << "OR Action: " << std::endl;
//	p2->andOrAction(c4, gameMap);
//
//	std::cout << "SINGLE Action: " << std::endl;
//	p2->andOrAction(c3, gameMap);
//
//	for (auto* player : currentPlayers)
//	{
//		delete player;
//		player = nullptr;
//	}
//	
//	delete c1;
//	delete c2;
//	delete c3;
//	delete c4;
//	delete gameMap;
//
//	return 0;
//}