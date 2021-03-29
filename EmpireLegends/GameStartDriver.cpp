//#include <iostream>
//#include <sstream>
//
//#include "GameStart.h"
//#include "Cards.h"
//
//using namespace std;
//
//int main() {
//	GameStart* startGame = new GameStart();
//
//	startGame->loadMap();
//	startGame->detPlayerCount();
//
//	// CARD VARIABLES
//	Card* card1 = new Card("Dire dragon", new Flying, new Action("Place 3 armies", 3), new Action("Destroy one army", 1), AndOr::AND);
//	Card* card2 = new Card("Dire giant", new Immune, new Action("Place 3 armies", 3), new Action("Destroy 1 army", 1), AndOr::AND);
//	Card* card3 = new Card("Dire eye", new Flying, new Action("Place 4 armies", 4));
//	Card* card4 = new Card("Dire Goblin", new Elixir(1), new Action("Move 5 armies", 5));
//	Card* card5 = new Card("Dire Ogre", new CoinVPs, new Action("Move 2 armies", 2));
//	Card* card6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place 2 armies", 2), new Action("Move 3 armies", 3), AndOr::AND);
//	Card* card7 = new Card("Forest Elf", new ExtraArmy, new Action("Place 3 armies", 3), new Action("Move 2 armies", 2), AndOr::OR);
//	Card* card8 = new Card("Forest Gnome", new Elixir(3), new Action("Move 2 armies", 2));
//	Card* card9 = new Card("Forest Tree Town", new ExtraMove, new Action("Place a city", 1));
//	Card* card10 = new Card("Graveyard", new SetNameVPs(CardSet::cursed), new Action("Place 2 armies", 2));
//	Card* card11 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place 3 armies", 3));
//	Card* card12 = new Card("Castle", new Elixir(1), new Action("Place 3 armies", 3), new Action("Build a city", 1), AndOr::OR);
//
//	// Add Cards to Deck
//	vector<Card*> cardVector;
//	cardVector.push_back(card1);
//	cardVector.push_back(card2);
//	cardVector.push_back(card3);
//	cardVector.push_back(card4);
//	cardVector.push_back(card5);
//	cardVector.push_back(card6);
//	cardVector.push_back(card7);
//	cardVector.push_back(card8);
//	cardVector.push_back(card9);
//	cardVector.push_back(card10);
//	cardVector.push_back(card11);
//	cardVector.push_back(card12);
//
//	std::cout << "Printing deck:" << std::endl;
//	Deck* deck = new Deck(cardVector);
//	std::cout << *deck;
//
//	delete deck;
//	delete startGame;
//}