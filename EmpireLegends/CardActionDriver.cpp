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
	p1->buildCity(r1);//fail
	p1->placeNewArmies(4, r1);//succeed
	std::cout << "\n";

	std::cout << p2->getName() + "'s turn: " << std::endl;
	p2->placeNewArmies(3, r1);//succeed
	p2->buildCity(r4);//fail
	p2->placeNewArmies(1, r4);//fail
	std::cout << "\n\n";

	//MoveArmies() + MoveOverLand()
	std::cout << "-- MoverArmies Tests (Over Land) --" << std::endl;


	//MoveArmies() + MoveOverWater()
	std::cout << "-- MoverArmies Tests (Over Water) --" << std::endl;


	//DestroyArmy()
	std::cout << "-- DestroyArmy Tests --" << std::endl;

	//AndOrAction()
	std::cout << "-- AndOrAction Tests --" << std::endl;
	Card* c1 = new Card("Dire dragon", new Flying, new Action("Place armies", 3), new Action("Destroy armies", 1), AndOr::AND);
	Card* c2 = new Card("Dire giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 1), AndOr::AND);
	Card* c3 = new Card("Dire eye", new Flying, new Action("Place armies", 4));
	Card* c4 = new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2));
	Card* c5 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::OR);
	Card* c6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Build city", 2), new Action("Move armies", 3), AndOr::OR);

	std::cout << "AND Action: " << std::endl;
	p1->andOrAction(c6, gameMap);
	std::cout << "\n";
	
	std::cout << "\n";

	std::cout << "OR Action: " << std::endl;
	p2->andOrAction(c3, gameMap);

	for (auto* player : currentPlayers)
	{
		delete player;
		player = nullptr;
	}
	delete c1;
	delete c2;
	delete c3;


	return 0;
}