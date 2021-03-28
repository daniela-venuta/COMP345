#include "MapUtility.h"

GameMap* MapUtility::createValidMap()
{
	auto* c1 = new Continent("Continent 1");
	auto* t1 = new Territory<Region>(new Region("Region 1"));
	auto* t2 = new Territory<Region>(new Region("Region 2"));
	auto* t3 = new Territory<Region>(new Region("Region 3"));
	auto* c2 = new Continent("Continent 2");
	auto* t4 = new Territory<Region>(new Region("Region 4"));
	auto* t5 = new Territory<Region>(new Region("Region 5"));
	auto* t6 = new Territory<Region>(new Region("Region 6"));
	auto* t7 = new Territory<Region>(new Region("Region 7"));
	auto* t8 = new Territory<Region>(new Region("Region 8"));

	c1->addTerritory(t1);
	c1->addTerritory(t2);
	c1->addTerritory(t3);

	c1->addEdge("Region 1", "Region 2", 1);
	c1->addEdge("Region 1", "Region 3", 1);
	c1->addEdge("Region 2", "Region 3", 1);

	c2->addTerritory(t4);
	c2->addTerritory(t5);
	c2->addTerritory(t6);
	c2->addTerritory(t7);
	c2->addTerritory(t8);
	c2->addEdge("Region 4", "Region 5", 1);
	c2->addEdge("Region 5", "Region 6", 1);
	c2->addEdge("Region 6", "Region 7", 1);
	c2->addEdge("Region 7", "Region 8", 1);

	auto* m1 = new GameMap("Map 1");
	auto* t9 = new Territory<Continent>(c1);
	auto* t10 = new Territory<Continent>(c2);

	m1->addTerritory(t9);
	m1->addTerritory(t10);
	m1->addEdge("Continent 1", "Continent 2", 3);

	return m1;
}

// Prints a list of all the Continents and Regions on a map for informative purposes
void MapUtility::printTerritories(GameMap* map)
{
	std::cout << "List of all Continents and Regions: " << std::endl;

	auto continentIterator = map->terrs.begin();
	while (continentIterator != map->terrs.end())
	{
		std::string name = continentIterator->second->getName();
		std::cout << name << std::endl;

		auto regionIterator = continentIterator->second->value->terrs.begin();
		while (regionIterator != continentIterator->second->value->terrs.end())
		{
			std::string regionName = regionIterator->second->getName();
			std::cout << regionName << std::endl;

			// Increment the Iterator to point to next entry
			++regionIterator;
		}

		// Increment the Iterator to point to next entry
		++continentIterator;
	}
}

std::map<int, Territory<Region>*> MapUtility::printTerritoriesWithArmies(GameMap* map, Player* player)
{
	std::map<int, Territory<Region>*> terrsWithArmies;

	for (auto& continentPair: map->terrs)
	{
		Continent* cont = continentPair.second->value;
		std::cout << cont->getName() << ":" << std::endl;

		for(auto& regionPair: cont->terrs)
		{
			const int placedArmies = regionPair.second->getPlacedArmies(player);
			if (placedArmies > 0)
			{
				int num = terrsWithArmies.size() + 1;
				std::cout << num << "-" << regionPair.second->getName() << " (" + std::to_string(placedArmies) + " armies)" << std::endl;
				terrsWithArmies[num] = regionPair.second;
			}
		}
	}
	
	return terrsWithArmies;
}

map<int, Territory<Region>*> MapUtility::printTerritoriesInVector(GameMap* map)
{
	std::cout << "List of all Continents and Regions: " << std::endl;
	std::map<int, Territory<Region>*> terrs;
	
	auto continentIterator = map->terrs.begin();
	while (continentIterator != map->terrs.end())
	{
		std::string name = continentIterator->second->getName();
		std::cout << name << std::endl;

		auto regionIterator = continentIterator->second->value->terrs.begin();
		while (regionIterator != continentIterator->second->value->terrs.end())
		{
			int num = terrs.size() + 1;
			terrs[num] = regionIterator->second;
			std::string regionName = regionIterator->second->getName();
			std::cout << num << "-" << regionName << std::endl;

			// Increment the Iterator to point to next entry
			++regionIterator;
			
		}

		// Increment the Iterator to point to next entry
		++continentIterator;
	}

	return terrs;
}