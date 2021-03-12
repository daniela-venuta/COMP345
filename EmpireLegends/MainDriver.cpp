// Tommy Andrews 40094870
// Émilie Martin 40095423
// Amélie Singoye 40094316
// Vithya Nagamuthu 40077465
// Daniela Venuta 40099441

#include "MapLoader.h"
#include <iostream>
#include <iostream>
#include <vector>
#include "Player.h"
#include "BiddingFacility.h"
#include "MapUtility.h"


void drivePlayer()
{
	// Create player pointers
	auto* p1 = new Player("player1");
	auto* p2 = new Player("player2");
	auto* p3 = new Player("player3");
	auto* p4 = new Player("player4");

	std::cout << std::endl;
	std::cout << "P1 balance: " << p1->getBalance() << " coins." << std::endl;
	std::cout << "P2 balance: " << p2->getBalance() << " coins." << std::endl;
	std::cout << "P3 balance: " << p3->getBalance() << " coins." << std::endl;
	std::cout << "P4 balance: " << p4->getBalance() << " coins." << std::endl;

	std::cout << std::endl;
	p1->PayCoin(2);
	p2->PayCoin(0);
	p3->PayCoin(9);
	p4->PayCoin(-5); // should output error message claiming unsufficient funds

	std::cout << std::endl;
	std::cout << "P1 balance: " << p1->getBalance() << " coins." << std::endl;
	std::cout << "P2 balance: " << p2->getBalance() << " coins." << std::endl;
	std::cout << "P3 balance: " << p3->getBalance() << " coins." << std::endl;
	std::cout << "P4 balance: " << p4->getBalance() << " coins." << std::endl;

	// create game map
	GameMap* gameMap = MapUtility::createValidMap();
	try
	{
		auto* t1 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 1");
		auto* t3 = gameMap->findTerritory("Continent 1")->value->findTerritory("Region 3");
		auto* t4 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 4");
		auto* t8 = gameMap->findTerritory("Continent 2")->value->findTerritory("Region 8");

		std::cout << std::endl;
		std::cout << "preliminary placement of armies...." << std::endl;
		p1->PlaceNewArmies(3, t1);
		p2->PlaceNewArmies(2, t1);
		p3->PlaceNewArmies(15, t4);
		p4->PlaceNewArmies(17, t4);

		std::cout << std::endl;
		std::cout << "============ MOVING ARMIES ============" << std::endl;

		p1->MoveArmies(3, t1, t4, gameMap);
		p2->MoveArmies(-5, t3, t8, gameMap); // should output error message (invalid number of armies; negative number)
		p2->MoveArmies(2, t1, t4, gameMap);
		p3->MoveArmies(20, t4, t8, gameMap); // should output error message (invalid number of armies; insufficient armies)
		p3->MoveArmies(15, t4, t8, gameMap);
		p4->MoveArmies(10, t1, t1, gameMap); // should output error message (invalid destination region)
		p4->MoveArmies(17, t4, t8, gameMap);

		std::cout << std::endl;
		std::cout << "T1 army count: " << t1->getArmyCount() << " armies." << std::endl;
		std::cout << "T3 army count: " << t3->getArmyCount() << " armies." << std::endl;
		std::cout << "T4 army count: " << t4->getArmyCount() << " armies." << std::endl;
		std::cout << "T8 army count: " << t8->getArmyCount() << " armies." << std::endl;

		std::cout << std::endl;
		std::cout << "============ PLACING NEW ARMIES ============" << std::endl;

		p1->PlaceNewArmies(20, t4); // should output error message (invalid number of armies; insufficient armies)
		p1->PlaceNewArmies(4, t4);
		p2->PlaceNewArmies(-5, t4); // should output error message (invalid number of armies; negative number)
		p2->PlaceNewArmies(1, t4);
		p3->PlaceNewArmies(0, t8); // should output error message (invalid number of armies; can't add zero)
		p3->PlaceNewArmies(3, t8);
		p4->PlaceNewArmies(5, t8); // should output error message (invalid number of armies; insufficient armies)
		p4->PlaceNewArmies(1, t8);

		std::cout << std::endl;
		std::cout << "T1 army count: " << t1->getArmyCount() << " armies." << std::endl;
		std::cout << "T3 army count: " << t3->getArmyCount() << " armies." << std::endl;
		std::cout << "T4 army count: " << t4->getArmyCount() << " armies." << std::endl;
		std::cout << "T8 army count: " << t8->getArmyCount() << " armies." << std::endl;

		std::cout << std::endl;
		std::cout << "============ DESTROYING ARMIES ============" << std::endl;

		p1->DestroyArmy(3, t4);
		p2->DestroyArmy(8, t4); //should output error message (invalid number of armies; not enough armies to destroy)
		p2->DestroyArmy(2, t4);
		p3->DestroyArmy(-9, t8); // should output error message (invalid number of armies; negative)
		p3->DestroyArmy(15, t8);
		p4->DestroyArmy(7, t8); //should output error message (invalid number of armies; not enough armies to destroy)

		std::cout << std::endl;
		std::cout << "T1 army count: " << t1->getArmyCount() << " armies." << std::endl;
		std::cout << "T3 army count: " << t3->getArmyCount() << " armies." << std::endl;
		std::cout << "T4 army count: " << t4->getArmyCount() << " armies." << std::endl;
		std::cout << "T8 army count: " << t8->getArmyCount() << " armies." << std::endl;

		std::cout << std::endl;
		std::cout << "============ BUILDING CITIES ============" << std::endl;

		p1->BuildCity(t1);
		p1->BuildCity(t1);
		p1->BuildCity(t1);
		p1->BuildCity(t1); // should output error message (exceeds city count)
		p2->BuildCity(t3); // should output error message (no armies present; cannot place city)
	}
	catch (TerritoryNotFoundException& e)
	{
		std::cout << e << std::endl;
	}
}

void driveMap()
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
	auto* c3 = new Continent("Continent 3");

	c1->addTerritory(t1);
	c1->addTerritory(t2);
	c1->addTerritory(t3);
	try
	{
		c1->addTerritory(t3);
	}
	catch (TerritoryInGraphException& e)
	{
		// Should not be able to add t3 twice
		std::cout << e << std::endl;
	}
	c1->addEdge("Region 1", "Region 2", 1);
	c1->addEdge("Region 1", "Region 3", 1);
	c1->addEdge("Region 2", "Region 3", 1);
	try
	{
		c1->addEdge("Region 1", "Region 2", 1);
	}
	catch (EdgeInGraphException& e)
	{
		//Should not add already existing edge
		std::cout << e << std::endl;
	}
	c2->addTerritory(t4);
	c2->addTerritory(t5);
	c2->addTerritory(t6);
	c2->addTerritory(t7);
	c2->addTerritory(t8);
	c2->addEdge("Region 4", "Region 5", 1);
	c2->addEdge("Region 5", "Region 6", 1);
	c2->addEdge("Region 6", "Region 7", 1);
	c2->addEdge("Region 7", "Region 8", 1);

	//Adding t3 so that it's duplicated in m2
	c3->addTerritory(new Territory<Region>(*t3));
	c3->addTerritory(new Territory<Region>(*t4));
	c3->addTerritory(new Territory<Region>(*t5));
	c3->addTerritory(new Territory<Region>(*t6));

	auto* m1 = new GameMap("Map 1");
	auto* m2 = new GameMap("Map 2");
	auto* t9 = new Territory<Continent>(c1);
	auto* t10 = new Territory<Continent>(c2);
	auto* t11 = new Territory<Continent>(c3);

	m1->addTerritory(t9);
	m1->addTerritory(t10);
	m1->addEdge("Continent 1", "Continent 2", 3);

	Territory<Continent>* t9Copy = new Territory<Continent>(*t9);
	m2->addTerritory(t9Copy);
	m2->addTerritory(t11);
	m2->addEdge("Continent 1", "Continent 3", 3);
	
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << "\nTravel cost (1->2): " << m1->getTravelCost(t1, t3) << std::endl; // Should be 1
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << "\nTravel cost (2->6): " << m1->getTravelCost(t2, t6) << std::endl; // Should be 6
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << "\nTravel cost (2->7): " << m1->getTravelCost(t2, t7) << std::endl; // Should be 5
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << "\nTravel cost (3->4): " << m1->getTravelCost(t3, t4) << std::endl; // Should be 3
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << *m1 << std::endl; //Testing map stream operator overload
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << *c1 << std::endl; //Testing continent stream operator overload
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << *t1 << std::endl; //Testing territory stream operator overload
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	GameMap copiedM1 = *m1; //Testing map copy constructor (which uses all other copy constructors)
	std::cout << "\nPrinting copied map:" << std::endl;
	std::cout << copiedM1 << std::endl;

	try
	{
		//m1 should validate
		m1->validate();
		m2->validate();
	}
	catch (InvalidMapException& e)
	{
		//m2 should not validate
		std::cout << e << std::endl;
	}
	c1->addTerritory(new Territory<Region>(new Region("Extra Region")));
	try
	{
		m1->validate();
	}
	catch (InvalidMapException& e)
	{
		//m1 should have an unconnected region
		std::cout << e << std::endl;
	}
	copiedM1.addTerritory(new Territory<Continent>(new Continent("Extra Continent")));
	try
	{
		c1->findTerritory("test_test");
	}
	catch (TerritoryNotFoundException& e)
	{
		//Should not find territory with incorrect name
		std::cout << e << std::endl;
	}

	delete m1;
	delete m2;
}

void driveMapLoader()
{
	auto* mapLoader = new MapLoader();

	std::cout << "Loading valid_map_1.json: ";

	auto* validMap1 = mapLoader->load("valid_map_1.json");

	std::cout << *validMap1 << std::endl;

	std::cout << "Loading valid_map_2.json: ";

	auto* validMap2 = mapLoader->load("valid_map_2.json");

	std::cout << *validMap2 << std::endl;

	try
	{
		std::cout << "Loading invalid_map_disconnected.json: ";
		mapLoader->load("invalid_map_disconnected.json");
	}
	catch (MapException& e)
	{
		std::cout << e << std::endl;
	}

	try
	{
		std::cout << "Loading invalid_map_missing_name_field.json: ";
		mapLoader->load("invalid_map_missing_name_field.json");
	}
	catch (InvalidMapFileException& e)
	{
		std::cout << e << std::endl;
	}

	try
	{
		std::cout << "Loading invalid_map_missing_edges_field.json: ";
		mapLoader->load("invalid_map_missing_edges_field.json");
	}
	catch (InvalidMapFileException& e)
	{
		std::cout << e << std::endl;
	}

	delete validMap1;
	delete validMap2;
	delete mapLoader;
}

void driveCards()
{
	// Create Card pointers
	Card* cardOne = new Card("Dire dragon", "Dire dragon", "Place 3 armies and destroy one army");
	Card* cardTwo = new Card("Dire giant", "Immune to attack", "Place 3 armies and destroy army");
	Card* cardThree = new Card("Dire eye", "", "Place 4 armies");
	Card* cardFour = new Card("Dire Ogre", " +1 VP per 3 coins", "Move 2 armies");
	Card* cardFive = new Card("Lake", " +1 VP per Forest card", "Place 2 armies and move 3 armies");
	Card* cardSix = new Card("Noble Hills", " Three noble cards = 4 VP", "Place 3 armies");

	// Example of printing goods and actions of cards
	std::cout << "Printing cards: \n";
	std::cout << *cardOne;
	std::cout << *cardTwo;
	std::cout << *cardThree << std::endl;

	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(cardOne);
	cardVector.push_back(cardTwo);
	cardVector.push_back(cardThree);
	cardVector.push_back(cardFour);
	cardVector.push_back(cardFive);
	cardVector.push_back(cardSix);

	// Create deck and add cards (this creates a card hand as well)
	std::cout << "Printing deck: \n";
	Deck* deck = new Deck(cardVector);
	std::cout << *deck;

	// Draw cards from deck and add them to the hand
	deck->draw(4);
	std::cout << "New deck after draw: \n" << *deck << std::endl;

	// Get Hand from the deck
	Hand* deckHand = deck->getHand();
	std::cout << *deckHand << std::endl;

	// Demo exchange method on hand
	const Card* exchangeCard1 = deckHand->exchange(2, 1); // successful exchange
	const Card* exchangeCard2 = deckHand->exchange(2, 0); // unsuccessful exchange, exchangeCard2 is a nullptr

	std::cout << "Exchanged card: " << *exchangeCard1 << std::endl;

	// delete cards created CHECK
	for (Card* card : cardVector)
	{
		delete card;
		card = nullptr;
	}
}

void driveBidding()
{
	// variables 
	int numofPlayers;
	int PlayerCoins = 0;
	string username;
	vector <Player*> myPlayers;
	auto* bidFac = new BiddingFacility();

	std::cout << "--------------------------" << std::endl;
	std::cout << "Eight-Minute-Empire Game" << std::endl;
	std::cout << "--------------------------" << std::endl;

	// determines how many coins per player
	std::cout << "\nNumber of players in the game (2-4): ";
	std::cin >> numofPlayers;

	switch (numofPlayers) {

	case 2:
		PlayerCoins = 14;
		std::cout << "Each player gets 14 coins" << std::endl;
		break;

	case 3:
		PlayerCoins = 11;
		std::cout << "Each player gets 11 coins" << std::endl;
		break;

	case 4:
		PlayerCoins = 9;
		std::cout << "Each player gets 9 coins" << std::endl;
		break;

	default:
		while (numofPlayers > 4 || numofPlayers < 2) {
			std::cout << "Invalid number of players";
			std::cout << "\nNumber of players in the game (2-4): ";
			std::cin >> numofPlayers;
		}
	}

	// enable the player objects and store in vector 
	std::cout << "\nWho will be playing the game: " << std::endl;
	for (auto i = 0; i < numofPlayers; i++) {
		std::cout << "Player: ";
		std::cin >> username;

		// creates a new pointer for each player object and adds it to the player vector
		myPlayers.push_back(new Player(username, PlayerCoins));
	}

	// Players place bids
	bidFac->placeBids(myPlayers);
}

int main()
{
	std::cout << std::endl << "------------------------------------" << std::endl;
	std::cout << "============ MAP DRIVER ============";
	std::cout << std::endl << "------------------------------------" << std::endl << std::endl;
	driveMap();
	std::cout << std::endl << "----------------------------------------" << std::endl;
	std::cout << "============ MAP LOADER DRIVER ============";
	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;
	driveMapLoader();
	std::cout << std::endl << "----------------------------------------" << std::endl;
	std::cout << "============ PLAYER DRIVER ============";
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	drivePlayer();
	std::cout << std::endl << "----------------------------------------" << std::endl;
	std::cout << "============ CARDS DRIVER ============";
	std::cout << std::endl << "--------------------------------------" << std::endl << std::endl;
	driveCards();
	std::cout << std::endl << "----------------------------------------" << std::endl;
	std::cout << "============ BIDDING DRIVER ============" << std::endl;
	std::cout << "----------------------------------------" << std::endl << std::endl;

	driveBidding();
}
