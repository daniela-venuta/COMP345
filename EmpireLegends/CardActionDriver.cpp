#include "Player.h"
#include "MapLoader.h"

//Tests for Part 4 in A2 

int main() {

	MapLoader* mapLoader = new MapLoader();
	auto* gameMap = mapLoader->load("valid_map_1.json");


	auto* r1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
	auto* r2 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 2");
	auto* r3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
	auto* r4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");

	auto* p1 = new Player("PlayerA");
	currentPlayers.push_back(p1);
	auto* p2 = new Player("PlayerB");
	currentPlayers.push_back(p2);
	
	std::cout << "===== Tests of Main Loop Game - Card Actions =====" << std::endl;
	std::cout << "\n";
	//PayCoin()
	std::cout << "-- Pay Coin() Tests --" << std::endl;
	std::cout << p1->getName() + "'s turn: " << std::endl;
	p1->payCoin(2);//success
	std::cout << p2->getName() + "'s turn: " << std::endl;
	std::cout << "\n";

	p2->payCoin(15);//fail
	std::cout << "\n\n";

	//PlaceNewArmies() + BuildCity()
	std::cout << "-- BuildCity() + PlaceNewArmies() Tests --" << std::endl;
	std::cout << p1->getName() + "'s turn: " << std::endl;
	p1->BuildCity(r1);//fail
	p1->PlaceNewArmies(4, r1);//succeed
	std::cout << "\n";

	std::cout << p2->getName() + "'s turn: " << std::endl;
	p2->PlaceNewArmies(3, r1);//succeed
	p2->BuildCity(r4);//fail
	p2->PlaceNewArmies(1, r4);//fail
	std::cout << "\n\n";

	//MoveArmies() + MoveOverLand()
	std::cout << "-- MoverArmies Tests (Over Land) --" << std::endl;
	std::cout << p2->getName() + "'s turn: " << std::endl;
	p2->MoveArmies(1, r1, r3, gameMap);//succeed
	p2->MoveArmies(1, r4, r3, gameMap);//fail
	std::cout << "\n";

    std::cout << p1->getName() + "'s turn: "<< std::endl;
	p1->MoveArmies(4, r1, r3, gameMap);//succeed
	std::cout << "\n\n";

	//MoveArmies() + MoveOverWater()
	std::cout << "-- MoverArmies Tests (Over Water) --" << std::endl;
	std::cout << p1->getName() + "'s turn: "<< std::endl;
	p1->setCoins(20);
	p1->MoveArmies(1, r3, r4, gameMap);//succeed
	std::cout << "\n\n";

	//DestroyArmy()
	std::cout << "-- DestroyArmy Tests --" << std::endl;
	std::cout << p2->getName() + "'s turn: " << std::endl;
	p2->DestroyArmy(1, r4, currentPlayers); //fail - P2 doesn't have an army there
	p2->DestroyArmy(4,r3, currentPlayers); //fail - There isn't a minimum 2 armies not owned by P2 on this Region
	p2->DestroyArmy(2, r3, currentPlayers); //successs - Should destroy the army of P1 on this Region
	std::cout << "\n\n";

	//AndOrAction()
	std::cout << "-- AndOrAction Tests --" << std::endl;
	Card* c1 = new Card("Dire Dragon", new Flying, "Move 3 Armies", "Destroy 1 Army", "and");
	Card* c2 = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
	Card* c3 = new Card("Dire Giant", new Immune, "Place 3 armies", "Destroy 1 Army", "or");

	std::cout << p1->getName() + "'s turn: " << std::endl;
	p1->andOrAction(c2, gameMap);//fail - Card has only one action
	std::cout << "\n";

	Player* p3 = new Player();
	p3->setName("Not-initialized Player");
	std::cout << p3->getName() + "'s turn: " << std::endl;
	p3->andOrAction(c1, gameMap); // fail due to not having stuff
	
	std::cout << "\n";

	std::cout << p2->getName() + "'s turn: " << std::endl;
	p2->andOrAction(c3, gameMap);

	for (auto* player : currentPlayers)
	{
		delete player;
		player = nullptr;
	}
	delete p3;

	delete c1;
	delete c2;
	delete c3;


	return 0;
}