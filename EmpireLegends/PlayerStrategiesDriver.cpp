#include "MapUtility.h"
#include "PlayerStrategies.h"

int main()
{
	GameMap* map = MapUtility::createValidMap();
	Territory<Region>* startingLocation = MapUtility::getStartingLocation(map);
	Player* randomPlayer = new Player();
	Player* human = new Player("Human", 50);
	Player* greedy = new Player("Greedy", 50, new GreedyStrategy());
	Player* moderate = new Player("Moderate", 50, new ModerateStrategy());

	std::cout << "Strategy assignment:" << std::endl;
	human->setStrategy(new HumanStrategy());

	Card* c1 = new Card("Dire dragon", new Flying, new Action("Move armies", 3), new Action("Build city"), AndOr::OR);
	Card* c2 = new Card("Dire giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 1), AndOr::OR);
	Card* c3 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Build city"), AndOr::OR);

	std::cout << "SETUP STEPS:" << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;

	Territory<Region>* region2 = map->findTerritory("Continent 1")->value->findTerritory("Region 2");
	Territory<Region>* region3 = map->findTerritory("Continent 1")->value->findTerritory("Region 3");
	Territory<Region>* region4 = map->findTerritory("Continent 2")->value->findTerritory("Region 4");
	Territory<Region>* region5 = map->findTerritory("Continent 2")->value->findTerritory("Region 5");
	greedy->placeNewArmies(5, startingLocation, startingLocation);
	greedy->moveArmies(3, startingLocation, region2, map);
	moderate->placeNewArmies(5, startingLocation, startingLocation);
	moderate->moveArmies(3, startingLocation, region5, map);
	moderate->buildCity(region5);
	moderate->moveArmies(2, startingLocation, region3, map);
	moderate->buildCity(region3);
	human->placeNewArmies(5, startingLocation, startingLocation);
	human->moveArmies(2, startingLocation, region4, map);
	human->buildCity(region4);
	
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl << std::endl;
	std::cout << "TEST STEPS:" << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;

	std::cout << "Greedy player should choose to build a city:" << std::endl;
	greedy->andOrAction(c1, map);

	std::cout << std::endl << "Moderate player should choose to place armies:" << std::endl;
	moderate->andOrAction(c2, map);

	std::cout << "Changing moderate to greedy:" << std::endl;
	moderate->setStrategy(new GreedyStrategy());

	std::cout << std::endl << "Moderate player is now greedy, so it should choose to destroy armies:" << std::endl;
	moderate->andOrAction(c2, map);

	std::cout << std::endl << "Human player can choose which action to execute:" << std::endl;
	human->andOrAction(c3, map);

	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
	
	delete human;
	delete greedy;
	delete moderate;
	delete map;
	delete c1;
	delete c2;
	delete c3;
	return 0;
}