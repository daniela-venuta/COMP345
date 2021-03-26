#include <iostream>
#include <sstream>

#include "MapLoader.h"
#include "GameStart.h"

using namespace std;

int main() {

	GameStart* startGame = new GameStart();

	startGame->loadMap();
	startGame->detPlayerCount();
	startGame->playerBidding();

	// CARD VARIABLES
	Card* card1 = new Card("Dire dragon", "Flying", "Place 3 armies and destroy one army");
	Card* card2 = new Card("Dire giant", "Immune to attack", "Place 3 armies and destroy army");
	Card* card3 = new Card("Dire eye", "Flying", "Place 4 armies");
	Card* card4 = new Card("Dire Goblin", " +1 elixer", "Move 5 armies");
	Card* card5 = new Card("Dire Ogre", " +1 VP per 3 coins", "Move 2 armies");
	Card* card6 = new Card("Lake", " +1 VP per Forest card", "Place 2 armies and move 3 armies");
	Card* card7 = new Card("Forest Elf", " +1 army", "Place 3 armies or movie 2 armies");
	Card* card8 = new Card("Forest Gnome", " +3 elixer", "Move 2 armies");
	Card* card9 = new Card("Forest Tree Town", "Move 1 army", "Place a city");
	Card* card10 = new Card("Graveyard", " +1VP per Cursed card", "Place 2 armies");
	Card* card11 = new Card("Noble Hills", " Three noble cards = 4 VP", "Place 3 armies");
	Card* card12 = new Card("Mountain Treasury", " +1 elixer and +2 coins", "Move 3 armies");
	Card* card13 = new Card("Castle", " +1 elixer", "Place 3 armies or build a city");

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
	cardVector.push_back(card13);

	std::cout << "Printing deck:" << std::endl;
	Deck* deck = new Deck(cardVector);
	std::cout << *deck;
}