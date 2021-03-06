#include <cstdlib>
#include <ctime>
#include "PlayerStrategies.h"
#include "MapUtility.h"

ostream& operator<<(ostream& os, const PlayerStrategy& strategy)
{
	return os << strategy.name << std::endl;
}

// Player picks the position of the card
int HumanStrategy::pickCardPosition() {

	int cardposition;

	do {
		std::cout << "Pick a position (1-6): ";
		std::cin >> cardposition;
	} while (cardposition > 6 || cardposition < 1);

	return cardposition;
}

Card* HumanStrategy::chooseCard(Hand* hand, Player* player)
{
	Card* faceCard = nullptr;
	while (faceCard == nullptr) {
		const int cardPosition = pickCardPosition();
		std::cout << "\n";

		faceCard = hand->exchange(cardPosition, player);

		if (faceCard == nullptr) {
			std::cout << "Card not be added to player" << std::endl;
		}
	}

	return faceCard;
}

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

bool HumanStrategy::executeAction(Action* action, Player* player, GameMap* map)
{
	const std::size_t build = action->getName().find("Build");
	const std::size_t destroy = action->getName().find("Destroy");
	const std::size_t place = action->getName().find("Place");
	const std::size_t move = action->getName().find("Move");

	int numOfTry = 0;
	bool actionDone = false;

	while (!actionDone && numOfTry < 10)
	{

		//Build City
		if (build != std::string::npos)
		{
			std::cout << "You may build a city in one of the regions with at least 1 army: " << std::endl;
			Territory<Region>* destination = player->chooseTerritory(MapUtility::printTerritoriesWithArmies(map, player));
			state = "Building city at " + destination->getName();
			actionDone = player->buildCity(destination);
		}
		//Move Armies
		else if (move != std::string::npos)
		{
			if (action->getMultiplier() > player->getNumArmy())
			{
				std::cout << "You don't have enough armies to move." << std::endl;
				return actionDone;
			}

			std::cout << "You may move " << action->getMultiplier() << " armies." << std::endl;
			std::cout << "Please choose the initial region: " << std::endl;

			Territory<Region>* from = player->chooseTerritory(MapUtility::printTerritoriesWithArmies(map, player));
			std::cout << "Please choose the destination region: " << std::endl;
			Territory<Region>* to = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));

			while (to == from)
			{
				std::cout << "Invalid. Please choose a destination other than the initial region: " << std::endl;
				to = player->chooseTerritory(MapUtility::printTerritoriesWithMap(map));
			}
			state = "Moving " + std::to_string(action->getMultiplier()) + "armies to " + to->getName();
			actionDone = player->moveArmies(action->getMultiplier(), from, to, map);
		}
		//Destroy Armies
		else if (destroy != std::string::npos)
		{
			int numArmies = action->getMultiplier();
			std::cout << "You may destroy " << numArmies << " enemy armies. Please choose a region: \n";
			Territory<Region>* location = player->chooseTerritory(MapUtility::printTerritoriesWithEnemyArmies(map, player, numArmies));
			Player* enemyPlayer = player->chooseEnemy(location, numArmies);

			state = "Destroying" + std::to_string(numArmies) + " of " + enemyPlayer->getName() + " at " + location->getName();
			actionDone = player->destroyArmy(numArmies, location, enemyPlayer);
		}
		//Place New Armies
		else if (place != std::string::npos)
		{
			// Place new army(ies) on the starting region or on a chosen region that has an owned city
			const int numArmies = action->getMultiplier();
			std::cout << "You may place " << numArmies << " armies. Please choose a region: \n";
			Territory<Region>* destination = player->chooseTerritory(MapUtility::printTerritoriesForPlacingArmies(map, player));

			state = "Placing " + std::to_string(numArmies) + " at " + destination->getName();
			actionDone = player->placeNewArmies(numArmies, destination, MapUtility::getStartingLocation(map));
		}


		numOfTry++;
	}
	if (numOfTry == 10)
	{
		state = "You ran out of trials for your turn.";
	}

	Notify();
	return actionDone;
}

Territory<Region>* NonHumanStrategy::getRandomTerritory(std::map<int, Territory<Region>*> territories)
{
	auto destinationItr = territories.begin();
	std::advance(destinationItr, rand() % territories.size());
	return destinationItr->second;
}

Card* NonHumanStrategy::chooseCard(Hand* hand, Player* player)
{
	Card* faceCard = nullptr;
	
	int p;
	std::cout << "The bot is picking a card. " << std::endl;
	while (faceCard == nullptr) {

		vector<Card*> cards = hand->getCards();
		auto itr = std::find_if(cards.begin(),cards.end(), [this](const Card* c)
		{
			bool foundCard = false;

			for(const string& action : wantedActions)
			{
				foundCard = (c->getAction() != nullptr && c->getAction()->getName().find(action) != std::string::npos) || (c->getSecondAction() != nullptr && c->getSecondAction()->getName().find(action) != std::string::npos);

				if (foundCard)
				{
					break;
				}
			}
			
			return foundCard;
		});
		
		int cardPosition;

		const int foundPosition = itr == cards.end() ? -1 : static_cast<int>(std::distance(cards.begin(), itr)) + 1;
		
		if (foundPosition != -1 && Hand::getCardCost(foundPosition) <= player->getBalance())
		{
			cardPosition = foundPosition;
		}
		else
		{
			do {
				cardPosition = rand() % 6 + 1;
			} while (cardPosition > 6 || cardPosition < 1);
		}
		
		faceCard = hand->exchange(cardPosition, player);
		p = cardPosition;
	}
	std::cout << "The bot picked the card at position " << p << "." << std::endl;

	return faceCard;
}

bool NonHumanStrategy::executeAction(Action* action, Player* player, GameMap* map)
{
	const std::size_t build = action->getName().find("Build");
	const std::size_t destroy = action->getName().find("Destroy");
	const std::size_t place = action->getName().find("Place");
	const std::size_t move = action->getName().find("Move");
	bool actionDone = false;
	int numOfTry = 0;
	srand(time(nullptr));

	while (!actionDone && numOfTry < 10)
	{
		//Build City
		if (build != std::string::npos)
		{
			std::cout << player->getName() << " may build a city in one of the regions with at least 1 army. " << std::endl;

			std::map<int, Territory<Region>*> destinations = MapUtility::printTerritoriesWithArmies(map, player);

			if (destinations.empty())
			{
				std::cout << "There is no region where to build a city." << std::endl;
				return false;
			}
			auto destination = getRandomTerritory(destinations);
			state = "Building city at " + destination->getName();
			actionDone = player->buildCity(destination); // Selecting random destination
		}
		//Move Armies
		else if (move != std::string::npos)
		{
			if (action->getMultiplier() > player->getNumArmy())
			{
				std::cout << "You don't have enough armies to move." << std::endl;
				return actionDone;
			}

			std::cout << player->getName() << " may move " << action->getMultiplier() << " armies." << std::endl;

			std::map<int, Territory<Region>*> froms = MapUtility::printTerritoriesWithArmies(map, player);
			Territory<Region>* from = getRandomTerritory(froms); // Selecting random initial region

			std::map<int, Territory<Region>*> tos = MapUtility::printTerritoriesWithMap(map);
			Territory<Region>* to = getRandomTerritory(tos); // Selecting random destination

			if (froms.empty() || tos.empty())
			{
				std::cout << "Moving armies is currently impossible." << std::endl;
				return false;
			}

			while (to == from)
			{
				to = getRandomTerritory(tos);
			}
			state = "Moving " + std::to_string(action->getMultiplier()) + "armies to " + to->getName();
			actionDone = player->moveArmies(action->getMultiplier(), from, to, map);
		}
		//Destroy Armies
		else if (destroy != std::string::npos)
		{
			const int numArmies = action->getMultiplier();
			std::cout << player->getName() << " may destroy " << numArmies << " enemy armies. Choosing a region. \n";

			std::map<int, Territory<Region>*> locations = MapUtility::printTerritoriesWithEnemyArmies(map, player, numArmies);

			if (locations.empty())
			{
				std::cout << "There is no region where " << numArmies << " armies can be destroyed." << std::endl;
				return false;
			}

			Territory<Region>* location = getRandomTerritory(locations);
			Player* chosenEnemy = nullptr;

			bool invalid = true;
			do
			{
				auto newEnemyItr = location->armies.begin();
				std::advance(newEnemyItr, rand() % location->armies.size());

				if (player != newEnemyItr->first && chosenEnemy != newEnemyItr->first)
				{
					invalid = false;
					chosenEnemy = newEnemyItr->first;
				}

			} while (invalid);
			state = "Destroying " + std::to_string(numArmies) + " of " + chosenEnemy->getName() + " at " + location->getName();
			actionDone = player->destroyArmy(numArmies, location, chosenEnemy);
		}
		//Place New Armies
		else if (place != std::string::npos)
		{
			const int numArmies = action->getMultiplier();
			std::cout << player->getName() << " may place " << numArmies << " armies. Choosing a region.\n";

			const std::map<int, Territory<Region>*> destinations = MapUtility::printTerritoriesForPlacingArmies(map, player);
			Territory<Region>* destination;

			// Selecting a destination until it's valid
			do
			{
				destination = getRandomTerritory(destinations);
			} while (destination != MapUtility::getStartingLocation(map) && destination->getPlacedCities(player) == 0);

			state = "Placing " + std::to_string(numArmies) + " at " + destination->getName();
			actionDone = player->placeNewArmies(numArmies, destination, MapUtility::getStartingLocation(map));
		}
		numOfTry++;
	}

	if (numOfTry >= 10) {
		state = "No more tries available";
	}

	Notify();
	return actionDone;
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

void ActionObserver::Update()
{
	display();
}

void ActionObserver::display()
{
	std::cout << "Turn events: " << subject->state << std::endl;
}

ActionObserver::ActionObserver(PlayerStrategy* s)
{
	subject = s;
	subject->Attach(this);
}
ActionObserver::~ActionObserver()
{
	subject->Detach(this);
}