#pragma once
#include "Map.h"
#include <string>

using std::string;

class MapUtility
{
public:
	static GameMap* createValidMap();
	static void printTerritories(GameMap* map);
	static std::map<int, Territory<Region>*> printTerritoriesWithArmies(GameMap* map, Player* player);
	static std::map<int, Territory<Region>*>printTerritoriesWithMap(GameMap* map);
	static std::map<int, Territory<Region>*>printTerritoriesForPlacingArmies(GameMap* map, Player* player);
	static std::map<int, Territory<Region>*> printTerritoriesWithEnemyArmies(GameMap* map, Player* player, int numArmiesToDestroy);
	static Territory<Region>* getStartingLocation(GameMap* map);
	static string getRegionOwner(Territory<Region>* region);
};
