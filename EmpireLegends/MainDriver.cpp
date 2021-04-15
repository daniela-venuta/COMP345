
// Tommy Andrews 40094870
// Émilie Martin 40095423
// Amélie Singoye 40094316
// Vithya Nagamuthu 40077465
// Daniela Venuta 40099441

#include <iostream>
#include <iostream>
#include <vector>
#include "MapLoader.h"
#include "Player.h"
#include "GameStart.h"
#include "StartingPhase.h"
#include "MainGame.h"
#include "MapUtility.h"

void driveGameStart()
{
	GameStart* startGame = new GameStart();

	startGame->loadMap();
	startGame->detPlayerCount();

	// CARD VARIABLES
	Card* card1 = new Card("Dire dragon", new Flying, new Action("Place 3 armies", 3), new Action("Destroy one army", 1), AndOr::AND);
	Card* card2 = new Card("Dire giant", new Immune, new Action("Place 3 armies", 3), new Action("Destroy 1 army", 1), AndOr::AND);
	Card* card3 = new Card("Dire eye", new Flying, new Action("Place 4 armies", 4));
	Card* card4 = new Card("Dire Goblin", new Elixir(1), new Action("Move 5 armies", 5));
	Card* card5 = new Card("Dire Ogre", new CoinVPs, new Action("Move 2 armies", 2));
	Card* card6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place 2 armies", 2), new Action("Move 3 armies", 3), AndOr::AND);
	Card* card7 = new Card("Forest Elf", new ExtraArmy, new Action("Place 3 armies", 3), new Action("Move 2 armies", 2), AndOr::OR);
	Card* card8 = new Card("Forest Gnome", new Elixir(3), new Action("Move 2 armies", 2));
	Card* card9 = new Card("Forest Tree Town", new ExtraMove, new Action("Place a city", 1));
	Card* card10 = new Card("Graveyard", new SetNameVPs(CardSet::cursed), new Action("Place 2 armies", 2));
	Card* card11 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place 3 armies", 3));
	Card* card12 = new Card("Castle", new Elixir(1), new Action("Place 3 armies", 3), new Action("Build a city", 1), AndOr::OR);

	// Add Cards to Deck
	vector<Card*> cardVector;
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

	std::cout << "Printing deck:" << std::endl;
	Deck* deck = new Deck(cardVector);
	std::cout << *deck;

	delete deck;
	delete startGame;
}

void driveStartUp()
{
	Player* p1 = new Player("Amy", 0);
	Player* p2 = new Player("Bob", 0);
	vector<Player*> players;
	players.push_back(p1);
	players.push_back(p2);

	// set up cards
	Card* card1 = new Card("Dire dragon", new Flying, new Action("Place 3 armies", 3), new Action("Destroy one army", 1), AndOr::AND);
	Card* card2 = new Card("Dire giant", new Immune, new Action("Place 3 armies", 3), new Action("Destroy 1 army", 1), AndOr::AND);
	Card* card3 = new Card("Dire eye", new Flying, new Action("Place 4 armies", 4));
	Card* card4 = new Card("Dire Goblin", new Elixir(1), new Action("Move 5 armies", 5));
	Card* card5 = new Card("Dire Ogre", new CoinVPs, new Action("Move 2 armies", 2));
	Card* card6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place 2 armies", 2), new Action("Move 3 armies", 3), AndOr::AND);

	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(card1);
	cardVector.push_back(card2);
	cardVector.push_back(card3);
	cardVector.push_back(card4);
	cardVector.push_back(card5);
	cardVector.push_back(card6);

	// Create deck and add cards (this creates a card hand as well)
	Deck* cardDeck = new Deck(cardVector);

	// get map
	MapLoader* mapLoader = new MapLoader();
	GameMap* map = mapLoader->load("valid_map_1.json");

	StartingPhase* startingPhase = new StartingPhase();
	startingPhase->startGame(map, players, cardDeck, 2);

	delete startingPhase;
	startingPhase = nullptr;
}

void driveMainLoop()
{
	vector<Card*> cardVector;
	cardVector.reserve(27);
	vector<Player*> players;
	int numOfTurns = 0;
	int playerCount = 0;

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

	do {
		std::cout << "How many players will be playing (2-4)?  ";
		std::cin >> playerCount;
	} while (playerCount > 4 || playerCount < 2);


	switch (playerCount) {
	case 2:
		players.push_back(new Player("John", 14));
		players.push_back(new Player("Bob", 14));
		numOfTurns = 13;
		break;

	case 3:
		players.push_back(new Player("John", 11));
		players.push_back(new Player("Bob", 11));
		players.push_back(new Player("Anna", 11));
		numOfTurns = 10;
		break;

	case 4:
		players.push_back(new Player("John", 9));
		players.push_back(new Player("Bob", 9));
		players.push_back(new Player("Jack", 9));
		players.push_back(new Player("Anna", 9));
		numOfTurns = 8;
		break;
	}

	MainGame* mainGame = new MainGame(nullptr, deck, players);

	mainGame->mainGameloop(numOfTurns);

	delete mainGame;
}

void driveCardAction()
{
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

	p2->payCoin(15);//fail sine funds are insufficient
	std::cout << "\n\n";

	p1->placeNewArmies(8, r1, r1);//succeed since it's the starting region

	//MoveArmies (Over land)
	std::cout << "-- MoverArmies Tests (Over Land) --" << std::endl;
	p1->moveArmies(2, r2, r3, gameMap); //fail since there are no armies in r2
	p1->moveArmies(2, r1, r3, gameMap); //success since there are armies in r1

	//MoveArmies (over water)
	std::cout << "-- MoverArmies Tests (Over Water) --" << std::endl;
	p1->moveArmies(2, r1, r4, gameMap);

	//PlaceNewArmies() + BuildCity()
	std::cout << "-- BuildCity() + PlaceNewArmies() Tests --" << std::endl;
	p1->buildCity(r2);//fail because no army is present
	p1->buildCity(r3);//success since there are armies
	std::cout << "\n";

	//DestroyArmy()
	std::cout << "-- DestroyArmy Tests --" << std::endl;

	//AndOrAction()
	std::cout << "-- AndOrAction Tests --" << std::endl;
	Card* c1 = new Card("Dire dragon", new Flying, new Action("Build city", 3), new Action("Destroy armies", 1), AndOr::AND);
	Card* c2 = new Card("Dire giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 1), AndOr::AND);
	Card* c3 = new Card("Dire eye", new Flying, new Action("Place armies", 4));
	Card* c4 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::OR);

	p2->placeNewArmies(4, r1, r1);
	p2->moveArmies(2, r1, r2, gameMap);

	std::cout << "AND Action: " << std::endl;
	p1->andOrAction(c1, gameMap);
	std::cout << "\n";
	p1->andOrAction(c1, gameMap);
	std::cout << "\n";

	std::cout << "OR Action: " << std::endl;
	p2->andOrAction(c4, gameMap);

	std::cout << "SINGLE Action: " << std::endl;
	p2->andOrAction(c3, gameMap);

	for (auto* player : currentPlayers)
	{
		delete player;
		player = nullptr;
	}

	delete c1;
	delete c2;
	delete c3;
	delete c4;
	delete gameMap;
}

void driveAfterAction()
{
	Card* card1 = new Card("Dire Dragon", new Flying, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card2 = new Card("Dire Giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card3 = new Card("Dire Eye", new Flying, new Action("Place armies", 4));
	Card* card4 = new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2));
	Card* card5 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::AND);
	Card* card6 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place armies", 3));
	Card* card7 = new Card("Arcane Phoenix", new Flying, new Action("Move armies", 5));
	Card* card8 = new Card("Cursed Gargoyles", new Flying, new Action("Move armies", 5));
	Card* card9 = new Card("Arcane Sphinx", new Flying, new Action("Place armies", 2), new Action("Move armies", 4), AndOr::OR);
	vector<Card*> cards;
	cards.push_back(card1);
	cards.push_back(card2);
	cards.push_back(card3);
	cards.push_back(card4);
	cards.push_back(card5);
	cards.push_back(card6);
	cards.push_back(card7);
	cards.push_back(card8);
	cards.push_back(card9);
	Deck* deck = new Deck(cards);
	deck->draw(6);
	vector<Player*> players;
	players.push_back(new Player("p1", 10));
	players.push_back(new Player("p2", 10));

	MainGame* mainGame = new MainGame(nullptr, deck, players);

	std::cout << "First player: " << mainGame->getCurrentPlayer()->getName() << std::endl;

	std::cout << std::endl << "Before first action:" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << *deck->getHand() << std::endl;

	Card* cardExchange1 = deck->getHand()->exchange(3, mainGame->getCurrentPlayer());
	mainGame->getCurrentPlayer()->addCard(cardExchange1);
	std::cout << "Card exchanged: " << *cardExchange1 << std::endl;
	std::cout << std::endl << "After first action (removing third card):" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	mainGame->afterAction();
	std::cout << *deck->getHand() << std::endl;

	Card* cardExchange2 = deck->getHand()->exchange(1, mainGame->getCurrentPlayer());
	mainGame->getCurrentPlayer()->addCard(cardExchange2);
	std::cout << "Card exchanged: " << *cardExchange2 << std::endl;
	std::cout << std::endl << "After second action (removing first card):" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	mainGame->afterAction();
	std::cout << *deck->getHand() << std::endl;

	Card* cardExchange3 = deck->getHand()->exchange(6, mainGame->getCurrentPlayer());
	mainGame->getCurrentPlayer()->addCard(cardExchange3);
	std::cout << "Card exchanged: " << *cardExchange3 << std::endl;
	std::cout << std::endl << "After third action (removing sixth card):" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	mainGame->afterAction();
	std::cout << *deck->getHand() << std::endl;

	delete mainGame;
}

void driveComputeScore()
{
	MapLoader* mapLoader = new MapLoader();
	auto* gameMap = mapLoader->load("valid_map_1.json");

	auto* r1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
	auto* r2 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 2");
	auto* r3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
	auto* r4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");

	vector<Player*> players{};
	Player* p1 = new Player("p1", 14);
	players.push_back(p1);
	Player* p2 = new Player("p2", 14);
	players.push_back(p2);

	vector<Card*> cardVector;

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
	deck->draw(5);
	GameMap* map = MapUtility::createValidMap();
	MainGame* mainGame = new MainGame(map, deck, players);

	p1->addCard(deck->getHand()->exchange(1, p1));
	p1->addCard(deck->getHand()->exchange(1, p1));
	p2->addCard(deck->getHand()->exchange(1, p1));
	p2->addCard(deck->getHand()->exchange(1, p1));
	p2->addCard(deck->getHand()->exchange(1, p1));

	mainGame->chooseWinner();
	std::cout << "P1 VP: " << p1->getVictoryPoints() << std::endl;
	std::cout << "P2 VP: " << p2->getVictoryPoints() << std::endl;

	delete mapLoader;
	delete mainGame;
}

//int main()
//{
	/*std::cout << std::endl << "------------------------------------" << std::endl;
	std::cout << "============ Game Start DRIVER ============";
	std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	driveGameStart();*/
	
	/*std::cout << std::endl << "------------------------------------" << std::endl;
	std::cout << "============ Startup Phase DRIVER ============";
	std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	driveStartUp();*/
	
	//std::cout << std::endl << "------------------------------------" << std::endl;
	//std::cout << "============ Main Loop DRIVER ============";
	//std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	//driveMainLoop();
	
	//std::cout << std::endl << "------------------------------------" << std::endl;
	//std::cout << "============ Card Action DRIVER ============";
	//std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	//driveCardAction();
	
	//std::cout << std::endl << "------------------------------------" << std::endl;
	//std::cout << "============ After Action DRIVER ============";
	//std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	//driveAfterAction();
	
	//std::cout << std::endl << "------------------------------------" << std::endl;
	//std::cout << "============ Compute Score DRIVER ============";
	//std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	//driveComputeScore();

//	return 0;
//}