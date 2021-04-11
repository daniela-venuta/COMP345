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

			player->moveArmies(action->getMultiplier(), from, to, map);
		}
		//Destroy Armies
		else if (destroy != std::string::npos)
		{
			int numArmies = action->getMultiplier();
			std::cout << "You may destroy " << numArmies << " enemy armies. Please choose a region: \n";
			Territory<Region>* location = player->chooseTerritory(MapUtility::printTerritoriesWithEnemyArmies(map, player, numArmies));
			Player* enemyPlayer = player->chooseEnemy(location, numArmies);

			player->destroyArmy(numArmies, location, enemyPlayer);
		}
		//Place New Armies
		else if (place != std::string::npos)
		{
			// Place new army(ies) on the starting region or on a chosen region that has an owned city
			int numArmies = action->getMultiplier();
			std::cout << "You may place " << numArmies << " armies. Please choose a region: \n";
			Territory<Region>* destination = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));
			player->placeNewArmies(numArmies, destination, MapUtility::getStartingLocation(map));
		}
	}
}

Action* GreedyStrategy::chooseAction(Action* action1, Action* action2)
{
	return nullptr;
}

Action* ModerateStrategy::chooseAction(Action* action1, Action* action2)
{
	return nullptr;
}
