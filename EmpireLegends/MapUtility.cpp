#include "MapUtility.h"
#include "Player.h"

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

	std::cout << std::endl;
}

std::map<int, Territory<Region>*> MapUtility::printTerritoriesWithArmies(GameMap* map, Player* player)
{
	std::map<int, Territory<Region>*> terrsWithArmies;
	
	std::cout << std::endl;

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

	std::cout << std::endl;
	
	return terrsWithArmies;
}

map<int, Territory<Region>*> MapUtility::printTerritoriesWithMap(GameMap* map)
{
	std::cout << "List of all Continents and Regions: " << std::endl;
	std::map<int, Territory<Region>*> terrs;

	std::cout << std::endl;
	
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

	std::cout << std::endl;
	
	return terrs;
}

std::map<int, Territory<Region>*> MapUtility::printTerritoriesForPlacingArmies(GameMap* map, Player* player)
{
	std::map<int, Territory<Region>*> terrsForPlacingArmies;
	
	std::cout << std::endl;

	for (auto& continentPair : map->terrs)
	{
		Continent* cont = continentPair.second->value;
		std::cout << cont->getName() << ":" << std::endl;

		for (auto& regionPair : cont->terrs)
		{
			const int placedCities = regionPair.second->getPlacedCities(player);
			if (placedCities > 0 || regionPair.second == getStartingLocation(map))
			{
				int num = terrsForPlacingArmies.size() + 1;
				std::cout << num << "-" << regionPair.second->getName() << " (" + std::to_string(placedCities) + " cities)" << std::endl;
				terrsForPlacingArmies[num] = regionPair.second;
			}
		}
	}

	std::cout << std::endl;

	return terrsForPlacingArmies;
}

// Retrieve the starting Region for all players based on the game map
Territory<Region>* MapUtility::getStartingLocation(GameMap* map)
{
	Continent* continent = map->terrs.begin()->second->value;
	Territory<Region>* region = continent->terrs.begin()->second;

	return region;
}

std::map<int, Territory<Region>*> MapUtility::printTerritoriesWithEnemyArmies(GameMap* map, Player* player, int numArmiesToDestroy)
{
	std::map<int, Territory<Region>*> terrsWithEnemyArmies;

	std::cout << std::endl;

	for (auto& continentPair : map->terrs)
	{
		Continent* cont = continentPair.second->value;
		std::cout << cont->getName() << ":" << std::endl;

		for (auto& regionPair : cont->terrs)
		{
			const int placedArmies = regionPair.second->getPlacedArmies(player);
			const int totalArmies = regionPair.second->getTotalArmyCount();
			if (totalArmies - placedArmies >= numArmiesToDestroy)
			{
				int num = terrsWithEnemyArmies.size() + 1;
				std::cout << num << "-" << regionPair.second->getName() << " (" + std::to_string(totalArmies-placedArmies) + " enemy armies)" << std::endl;
				terrsWithEnemyArmies[num] = regionPair.second;
			}
		}
	}

	std::cout << std::endl;
	
	return terrsWithEnemyArmies;
}

string MapUtility::getRegionOwner(Territory<Region>* region)
{
	for (auto pair : region->armies)
	{
		vector<Territory<Region>*> territories = pair.first->getTerritories();
		bool isOwner = std::find(territories.begin(), territories.end(), region) != territories.end();
		if (isOwner)
		{
			return pair.first->getName();
		}
	}

	return "none";
}
