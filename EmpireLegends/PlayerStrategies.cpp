#include <stdlib.h>
#include <time.h>
#include "PlayerStrategies.h"
#include "MapUtility.h"

Action* HumanStrategy::chooseAction(Action* action1, Action* action2)
{
	Action* chosenAction = nullptr;
	int option = 0;

	std::cout << "You must chose which action to use." << std::endl;
	
	while (chosenAction == nullptr)
	{
		std::cout << "Please enter the number next to the desired action:" << std::endl;
		std::cout << "1 : " << *action1 << std::endl;
		std::cout << "2 : " << *action2 << std::endl;
		std::cin >> option;

		if (std::cin.fail())
		{
			std::cout << "The value you entered isn't a valid option. Please input a valid option. \n(Make sure that it is an integer)" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			switch (option) {
			case 1:
				chosenAction = action1;
				std::cout << "You have chosen " << *action1 << "." << std::endl;
				break;
			case 2:
				chosenAction = action2;
				std::cout << "You have chosen " << *action2 << "." << std::endl;
				break;
			default:
				std::cout << "The value you entered isn't a valid option. Please input a valid option." << std::endl;
			}
		}
	}

	return chosenAction;
}

void HumanStrategy::executeAction(Action* action, Player* player, GameMap* map)
{
	const std::size_t build = action->getName().find("Build");
	const std::size_t destroy = action->getName().find("Destroy");
	const std::size_t place = action->getName().find("Place");
	const std::size_t move = action->getName().find("Move");
	bool actionDone = false;

	while (!actionDone)
	{
		//Build City
		if (build != std::string::npos)
		{
			std::cout << "You may build a city in one of the regions with at least 1 army: " << std::endl;
			Territory<Region>* destination = player->chooseTerritory(MapUtility::printTerritoriesWithArmies(map, player));
			actionDone = player->buildCity(destination);
		}
		//Move Armies
		else if (move != std::string::npos)
		{
			std::cout << "You may move" << action->getMultiplier() << " armies." << std::endl;
			std::cout << "Please choose the initial region: " << std::endl;

			Territory<Region>* from = player->chooseTerritory(MapUtility::printTerritoriesWithArmies(map, player));
			std::cout << "Please choose the destination region: " << std::endl;
			Territory<Region>* to = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));

			while (to == from)
			{
				std::cout << "Invalid. Please choose a destination other than the initial region: " << std::endl;
				to = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));
			}

			actionDone = player->moveArmies(action->getMultiplier(), from, to, map);
		}
		//Destroy Armies
		else if (destroy != std::string::npos)
		{
			int numArmies = action->getMultiplier();
			std::cout << "You may destroy " << numArmies << " enemy armies. Please choose a region: \n";
			Territory<Region>* location = player->chooseTerritory(MapUtility::printTerritoriesWithEnemyArmies(map, player, numArmies));
			Player* enemyPlayer = player->chooseEnemy(location, numArmies);

			actionDone = player->destroyArmy(numArmies, location, enemyPlayer);
		}
		//Place New Armies
		else if (place != std::string::npos)
		{
			// Place new army(ies) on the starting region or on a chosen region that has an owned city
			const int numArmies = action->getMultiplier();
			std::cout << "You may place " << numArmies << " armies. Please choose a region: \n";
			Territory<Region>* destination = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));
			actionDone = player->placeNewArmies(numArmies, destination, MapUtility::getStartingLocation(map));
		}
	}
}

void NonHumanStrategy::executeAction(Action* action, Player* player, GameMap* map)
{
	const std::size_t build = action->getName().find("Build");
	const std::size_t destroy = action->getName().find("Destroy");
	const std::size_t place = action->getName().find("Place");
	const std::size_t move = action->getName().find("Move");
	bool actionDone = false;
	srand(time(nullptr));

	while (!actionDone)
	{
		//Build City
		if (build != std::string::npos)
		{
			std::map<int, Territory<Region>*> destinations = MapUtility::printTerritoriesWithArmies(map, player);

			if (destinations.empty())
			{
				std::cout << "There is no region where to build a city." << std::endl;
				return;
			}

			std::cout << player->getName() << " may build a city in one of the regions with at least 1 army. " << std::endl;
			actionDone = player->buildCity(destinations.at(rand() % destinations.size())); // Selecting random destination
		}
		//Move Armies
		else if (move != std::string::npos)
		{
			std::cout << player->getName() << " may move" << action->getMultiplier() << " armies." << std::endl;

			std::map<int, Territory<Region>*> froms = MapUtility::printTerritoriesWithArmies(map, player);
			Territory<Region>* from = froms.at(rand() % froms.size()); // Selecting random initial region

			std::map<int, Territory<Region>*> tos = MapUtility::printTerritoriesWithArmies(map, player);
			Territory<Region>* to = tos.at(rand() % tos.size()); // Selecting random destination;

			if (froms.empty() || tos.empty())
			{
				std::cout << "Moving armies is currently impossible." << std::endl;
				return;
			}

			while (to == from)
			{
				to = tos.at(rand() % tos.size());
			}

			actionDone = player->moveArmies(action->getMultiplier(), from, to, map);
		}
		//Destroy Armies
		else if (destroy != std::string::npos)
		{
			const int numArmies = action->getMultiplier();
			std::map<int, Territory<Region>*> locations = MapUtility::printTerritoriesWithEnemyArmies(map, player, numArmies);

			if (locations.empty())
			{
				std::cout << "There is no region where " << numArmies << " armies can be destroyed." << std::endl;
				return;
			}

			std::cout << player->getName() << " may destroy " << numArmies << " enemy armies. Choosing a region. \n";

			Territory<Region>* location = locations.at(rand() % locations.size());
			Player* enemyPlayer = player->chooseEnemy(location, numArmies);

			actionDone = player->destroyArmy(numArmies, location, enemyPlayer);
		}
		//Place New Armies
		else if (place != std::string::npos)
		{
			std::map<int, Territory<Region>*> destinations = MapUtility::printTerritoriesWithMap(map);

			const int numArmies = action->getMultiplier();
			std::cout << player->getName() << " may place " << numArmies << " armies. Choosing a region.\n";
			Territory<Region>* destination;

			// Selecting a destination until it's valid
			do
			{
				destination = destinations.at(rand() % destinations.size());
			} 			while (destination != MapUtility::getStartingLocation(map) && destination->getPlacedCities(player) == 0);

			actionDone = player->placeNewArmies(numArmies, destination, MapUtility::getStartingLocation(map));
		}
	}
}

Action* GreedyStrategy::chooseAction(Action* action1, Action* action2)
{
	const std::size_t build1 = action1->getName().find("Build");
	const std::size_t destroy1 = action1->getName().find("Destroy");
	const std::size_t build2 = action2->getName().find("Build");
	const std::size_t destroy2 = action2->getName().find("Destroy");

	// Choosing the destroy army action that destroys the most armies
	if (destroy1 != std::string::npos && destroy2 != std::string::npos)
	{
		return action1->getMultiplier() >= action2->getMultiplier() ? action1 : action2;
	}
	
	if (build1 != std::string::npos || destroy1 != std::string::npos)
	{
		return action1;
	}
	
	if (build2 != std::string::npos || destroy2 != std::string::npos)
	{
		return action2;
	}

	// Choosing the first action if neither of them is for building a city or destroying armies
	return action1;
}

Action* ModerateStrategy::chooseAction(Action* action1, Action* action2)
{
	const std::size_t place1 = action1->getName().find("Place");
	const std::size_t place2 = action2->getName().find("Place");

	// Choosing the place army action that places the most armies
	if (place1 != std::string::npos && place2 != std::string::npos)
	{
		return action1->getMultiplier() >= action2->getMultiplier() ? action1 : action2;
	}

	if (place1 != std::string::npos)
	{
		return action1;
	}

	if (place2 != std::string::npos)
	{
		return action2;
	}

	// Choosing the first action if neither of them is for placing armies
	return action1;
}