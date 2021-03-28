#include "Cards.h"
#include "Player.h"
#include <iostream>

int main() {
	Player* p1 = new Player("A", 10);
	Player* p2 = new Player("B", 0);
	
	// Create Card pointers
	Card* cardOne = new Card("Dire dragon", new Flying, "Place 3 armies and destroy one army");
	Card* cardTwo = new Card("Dire giant", new Immune, "Place 3 armies and destroy army");
	Card* cardThree = new Card("Dire eye", new Flying, "Place 4 armies");
	Card* cardFour = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
	Card* cardFive = new Card("Lake", new SetNameVPs(CardSet::forest), "Place 2 armies and move 3 armies");
	Card* cardSix = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), "Place 3 armies");

	// Example of printing goods and actions of cards
	std::cout << "Printing cards: \n";
	std::cout << *cardOne << std::endl;
	std::cout << *cardTwo << std::endl;
	std::cout << *cardThree << std::endl;
	std::cout << *cardFour << std::endl;
	std::cout << *cardFive << std::endl;
	std::cout << *cardSix << std::endl;

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
	std::cout << "Deck in the player's hand: \n" << *deck->getHand() << std::endl;

	// Demo exchange method on hand
	const Card* exchangeCard = deck->getHand()->exchange(2, p1); // successful exchange
	deck->getHand()->exchange(2, p2); // unsuccessful exchange, exchangeCard2 is a nullptr

	std::cout << "Exchanged card: " << *exchangeCard << std::endl;

	cardVector.clear();
	delete exchangeCard;
	delete p1;
	delete p2;
	delete deck;
}
