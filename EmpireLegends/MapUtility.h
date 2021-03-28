#pragma once
#include "Map.h"
#include "Player.h"

class MapUtility
{
public:
	static GameMap* createValidMap();
	static void printTerritories(GameMap* map);
	static std::map<int, Territory<Region>*> printTerritoriesWithArmies(GameMap* map, Player* player);
	static map<int, Territory<Region>*>printTerritoriesWithMap(GameMap* map);
	static Territory<Region>* getStartingLocation(GameMap* map);
};
