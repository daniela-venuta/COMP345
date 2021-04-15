//#include "MapLoader.h"
//#include "StartingPhase.h"
//
//int main()
//{
//	Player* p1 = new Player("Amy", 0);
//	Player* p2 = new Player("Bob", 0);
//	vector<Player*> players;
//	players.push_back(p1);
//	players.push_back(p2);
//
//	// set up cards
//	Card* card1 = new Card("Dire dragon", new Flying, new Action("Place 3 armies", 3), new Action("Destroy one army", 1), AndOr::AND);
//	Card* card2 = new Card("Dire giant", new Immune, new Action("Place 3 armies", 3), new Action("Destroy 1 army", 1), AndOr::AND);
//	Card* card3 = new Card("Dire eye", new Flying, new Action("Place 4 armies", 4));
//	Card* card4 = new Card("Dire Goblin", new Elixir(1), new Action("Move 5 armies", 5));
//	Card* card5 = new Card("Dire Ogre", new CoinVPs, new Action("Move 2 armies", 2));
//	Card* card6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place 2 armies", 2), new Action("Move 3 armies", 3), AndOr::AND);
//
//	// add Cards to a vector
//	vector<Card*> cardVector;
//	cardVector.push_back(card1);
//	cardVector.push_back(card2);
//	cardVector.push_back(card3);
//	cardVector.push_back(card4);
//	cardVector.push_back(card5);
//	cardVector.push_back(card6);
//
//	// Create deck and add cards (this creates a card hand as well)
//	Deck* cardDeck = new Deck(cardVector);
//
//	// get map
//	MapLoader* mapLoader = new MapLoader();
//	GameMap* map = mapLoader->load("valid_map_1.json");
//	
//	StartingPhase* startingPhase = new StartingPhase();
//	startingPhase->startGame(map, players, cardDeck, 2);
//
//	delete startingPhase;
//	
//	return 0;
//}