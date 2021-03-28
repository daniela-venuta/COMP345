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
//	Card* cardOne = new Card("Dire dragon", new Flying, "Place 3 armies and destroy one army");
//	Card* cardTwo = new Card("Dire giant", new Immune, "Place 3 armies and destroy army");
//	Card* cardThree = new Card("Dire eye", new Flying, "Place 4 armies");
//	Card* cardFour = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
//	Card* cardFive = new Card("Lake", new SetNameVPs(CardSet::forest), "Place 2 armies and move 3 armies");
//	Card* cardSix = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), "Place 3 armies");
//
//	// add Cards to a vector
//	vector<Card*> cardVector;
//	cardVector.push_back(cardOne);
//	cardVector.push_back(cardTwo);
//	cardVector.push_back(cardThree);
//	cardVector.push_back(cardFour);
//	cardVector.push_back(cardFive);
//	cardVector.push_back(cardSix);
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
//	startingPhase = nullptr;
//	
//	return 0;
//}