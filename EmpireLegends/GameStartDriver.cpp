#include <iostream>
#include <sstream>

#include "GameStart.h"
#include "Cards.h"

using namespace std;

int main() {

	GameStart* startGame = new GameStart();

	startGame->loadMap();
	startGame->detPlayerCount();
	startGame->playerBidding();

	// CARD VARIABLES
	Card* card1 = new Card("Dire dragon", new Flying, "Place 3 armies and destroy one army");
	Card* card2 = new Card("Dire giant", new Immune, "Place 3 armies and destroy army");
	Card* card3 = new Card("Dire eye", new Flying, "Place 4 armies");
	Card* card4 = new Card("Dire Goblin", new Elixir(1), "Move 5 armies");
	Card* card5 = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
	Card* card6 = new Card("Lake", new SetNameVPs(CardSet::forest), "Place 2 armies and move 3 armies");
	Card* card7 = new Card("Forest Elf", new ExtraArmy, "Place 3 armies or movie 2 armies");
	Card* card8 = new Card("Forest Gnome", new Elixir(3), "Move 2 armies");
	Card* card9 = new Card("Forest Tree Town", new ExtraMove, "Place a city");
	Card* card10 = new Card("Graveyard", new SetNameVPs(CardSet::cursed), "Place 2 armies");
	Card* card11 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), "Place 3 armies");
	Card* card12 = new Card("Castle", new Elixir(1), "Place 3 armies or build a city");

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
}