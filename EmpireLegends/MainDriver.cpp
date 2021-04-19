//
//// Tommy Andrews 40094870
//// Émilie Martin 40095423
//// Amélie Singoye 40094316
//// Vithya Nagamuthu 40077465
//// Daniela Venuta 40099441
//
#include <iostream>
#include <iostream>
#include <vector>

#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "GameStart.h"
#include "StartingPhase.h"
#include "MainGame.h"
#include "MapUtility.h"
#include "PlayerStrategies.h"

Deck* setDeck()
{
	vector<Card*> cardVector;
	cardVector.reserve(27);

	Card* card1 = new Card("Dire Dragon", new Flying, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card2 = new Card("Dire Giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card3 = new Card("Dire Eye", new Flying, new Action("Place armies", 4));
	Card* card4 = new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2));
	Card* card5 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::AND);
	Card* card6 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place armies", 3));
	Card* card7 = new Card("Arcane Phoenix", new Flying, new Action("Move armies", 5));
	Card* card8 = new Card("Cursed Gargoyles", new Flying, new Action("Move armies", 5));
	Card* card9 = new Card("Arcane Sphinx", new Flying, new Action("Place armies", 2), new Action("Move armies", 4), AndOr::OR);
	Card* card10 = new Card("Dire Goblin", new Elixir(1), new Action("Move armies", 5));
	Card* card11 = new Card("Forest Elf", new ExtraArmy, new Action("Place armies", 3), new Action("Move armies", 2), AndOr::OR);
	Card* card12 = new Card("Forest Tree Town", new ExtraMove, new Action("Build city", 1));
	Card* card13 = new Card("Noble Knight", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND);
	Card* card14 = new Card("Noble Unicorn", new ExtraMove, new Action("Move armies", 4), new Action("Place armies", 1), AndOr::AND);
	Card* card15 = new Card("Night Hydra", new ExtraArmy, new Action("Move armies", 5), new Action("Destroy armies", 1), AndOr::AND);
	Card* card16 = new Card("Night Village", new ExtraArmy, new Action("Build city", 1));
	Card* card17 = new Card("Castle 1", new Elixir(1), new Action("Place armies", 3), new Action("Build city", 1), AndOr::OR);
	Card* card18 = new Card("Forest Pixie", new ExtraArmy, new Action("Move armies", 4));
	Card* card19 = new Card("Arcane Manticore", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND);
	Card* card20 = new Card("Ancient Woods", new ExtraArmy, new Action("Build city", 1), new Action("Place armies", 1), AndOr::AND);
	Card* card21 = new Card("Forest Gnome", new Elixir(3), new Action("Move armies", 2));
	Card* card22 = new Card("Castle 2", new Elixir(1), new Action("Move armies", 3), new Action("Build city", 1), AndOr::OR);
	Card* card23 = new Card("Ancient Tree Spirit", new Elixir(3), new Action("Place armies", 4), new Action("Build city", 1), AndOr::OR);
	Card* card24 = new Card("Ancient Woods", new ExtraArmy, new Action("Build city", 1), new Action("Place armies", 1), AndOr::AND);
	Card* card25 = new Card("Cursed Banshee", new Elixir(2), new Action("Move armies", 5));
	Card* card26 = new Card("Cursed King", new Elixir(1), new Action("Move armies", 4), new Action("Place armies", 3), AndOr::OR);
	Card* card27 = new Card("Cursed Mausoleum", new ExtraMove, new Action("Build city", 1));

	cardVector.push_back(card1);
	cardVector.push_back(card2);
	cardVector.push_back(card3);
	cardVector.push_back(card4);
	cardVector.push_back(card5);
	cardVector.push_back(card6);
	cardVector.push_back(card7);
	cardVector.push_back(card8);
	cardVector.push_back(card9);
	cardVector.push_back(card10);
	cardVector.push_back(card11);
	cardVector.push_back(card12);
	cardVector.push_back(card13);
	cardVector.push_back(card14);
	cardVector.push_back(card15);
	cardVector.push_back(card16);
	cardVector.push_back(card17);
	cardVector.push_back(card18);
	cardVector.push_back(card19);
	cardVector.push_back(card20);
	cardVector.push_back(card21);
	cardVector.push_back(card22);
	cardVector.push_back(card23);
	cardVector.push_back(card24);
	cardVector.push_back(card25);
	cardVector.push_back(card26);
	cardVector.push_back(card27);

	Deck* deck = new Deck(cardVector);

	return deck;
}

void PlayerStrategiesDemo()
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
	Card* c4 = new Card("Ancient Tree Spirit", new Elixir(3), new Action("Place armies", 4), new Action("Build city", 1), AndOr::OR);
	Card* c6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Build city"), AndOr::OR);
	Card* c7 = new Card("Dire dragon", new Flying, new Action("Move armies", 3), new Action("Build city"), AndOr::OR);
	
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

	Hand* greedyHand = new Hand();
	greedyHand->addCard(c4);
	greedyHand->addCard(c2);
	
	std::cout << "Greedy player should choose to build a city:" << std::endl;
	greedy->andOrAction(greedy->chooseCard(greedyHand), map);

	Hand* moderateHand = new Hand();
	moderateHand->addCard(new Card(*c2));
	moderateHand->addCard(new Card(*c4));
	
	std::cout << std::endl << "Moderate player should choose to place armies:" << std::endl;
	moderate->andOrAction(moderate->chooseCard(moderateHand), map);


	greedyHand = new Hand();
	greedyHand->addCard(new Card(*c2));
	greedyHand->addCard(new Card(*c1));
	
	std::cout << "Changing moderate to greedy:" << std::endl;
	moderate->setStrategy(new GreedyStrategy());

	moderateHand = new Hand();
	moderateHand->addCard(new Card(*c2));
	moderateHand->addCard(new Card(*c4));
	
	std::cout << std::endl << "Moderate player is now greedy, so it should choose to destroy armies:" << std::endl;
	moderate->andOrAction(moderate->chooseCard(greedyHand), map);

	Hand* playerHand = new Hand();
	playerHand->addCard(new Card(*c6));
	playerHand->addCard(new Card(*c7));
	
	std::cout << std::endl << "Human player can choose which action to execute:" << std::endl;
	human->andOrAction(human->chooseCard(playerHand), map);

	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
	
	delete human;
	delete greedy;
	delete moderate;
	delete map;
	delete greedyHand;
	delete moderateHand;
	delete playerHand;
}

void PhaseObserverDemo()
{
	vector<ActionObserver*> actionObservers;
	GameStart* gameStart = new GameStart();
	GameStartObserver* gameStartObserver = new GameStartObserver(gameStart);

	//Game Start Part
	GameMap* gameMap = gameStart->loadMap();
	vector<Player*> players = gameStart->detPlayerBotCount();

	Deck* deck = setDeck();

	StartingPhase* startPhase = new StartingPhase(gameMap, deck, players);
	StartingPhaseObserver* startingPhaseObserver = new StartingPhaseObserver(startPhase);
	players = startPhase->startGame();

	for (int i = 0; i < players.size(); i++)
	{
		PlayerStrategy* strat = players[i]->getStrategy();
		ActionObserver* actionObserver = new ActionObserver(strat);
		actionObservers.push_back(actionObserver);
	}

	MainGame* mainGame = new MainGame(gameMap, deck, players);
	MainGameObserver* mainGameObserver = new MainGameObserver(mainGame);

	int numOfTurns = 4;
	mainGame->mainGameloop(numOfTurns);// Number of turns was set to a specific value based on criterias

	delete gameStartObserver;
	delete gameStart;
	delete startingPhaseObserver;
	delete startPhase;

	for (auto& actionObserver : actionObservers)
	{
		delete actionObserver;
	}
	delete deck;
	delete mainGameObserver;
	delete mainGame;
}

void GameStatsObserverDemo()
{
	// Start game
	GameStart* gameStart = new GameStart();
	GameMap* gameMap = gameStart->loadMap();
	vector<Player*> players = gameStart->detPlayerBotCount();

	Deck* deck = setDeck();
	StartingPhase* startPhase = new StartingPhase(gameMap, deck, players);
	players = startPhase->startGame();

	MainGame* mainGame = new MainGame(gameMap, deck, players);
	GameStatisticsObserver* gameStatisticsObserver = new GameStatisticsObserver(mainGame);

	int numOfTurns = 4;
	mainGame->mainGameloop(numOfTurns);

	delete gameStart;
	delete startPhase;
	delete deck;
	delete gameStatisticsObserver;
	delete mainGame;
}

void TournamentDemo()
{
	std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Welcome to the Eight-Minute Empire Game " << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
	
		GameEngine* gameEngine = new GameEngine();
		
		int choice = 0;
	
		std::cout << "\nPick a Game Mode " << std::endl;
		std::cout << "\t1- Single Mode " << std::endl;
		std::cout << "\t2- Tournament Mode " << std::endl;
		std::cout << "\nEnter choice here: ";
	
		while (choice < 1 || choice > 2)
		{
			std::cin >> choice;
	
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bad entry. Enter a NUMBER: ";
			} else if (choice < 1 || choice > 2) {
				std::cin.clear();
				std::cout << "Not a valid choice. Please try again: ";
			}
		}
	
		choice == 1 ? gameEngine->singleMode() : gameEngine->tournamentMode();
	
		delete gameEngine;
}


int main()
{
	std::cout << "================= Player Strategy Demo =================" << std::endl;
	PlayerStrategiesDemo();

	std::cout << "================= Phase Observer Demo =================" << std::endl;
	//PhaseObserverDemo();

	std::cout << "================= Game Stats Observer Demo =================" << std::endl;
	//GameStatsObserverDemo();
	
	std::cout << "================= Game Tournament Demo =================" << std::endl;
	//TournamentDemo();

	return 0;
}
