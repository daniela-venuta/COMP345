#include "Cards.h"
#include <iostream>

int main() {

	// Create Card pointers
	Card* cardOne = new Card("1", "");
	Card* cardTwo = new Card("2", "");
	Card* cardThree = new Card("3", "");
	Card* cardFour = new Card("4", "");
	Card* cardFive = new Card("5", "");
	Card* cardSix = new Card("6", "");

	// Example of printing goods and actions of cards
	std::cout << *cardOne;
	std::cout << *cardTwo;
	std::cout << *cardThree;

	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(cardOne);
	cardVector.push_back(cardTwo);
	cardVector.push_back(cardThree);
	cardVector.push_back(cardFour);
	cardVector.push_back(cardFive);
	cardVector.push_back(cardSix);

	// Create deck and add cards (this creates a card hand as well)
	Deck* deck = new Deck(cardVector);
	std::cout << *deck;
	
	// Draw cards from deck and add them to the hand
	deck->draw(4);
	std::cout <<"New deck after draw: \n" <<*deck;

	// Get Hand from the deck
	Hand* deckHand = deck->getHand();
	std::cout << *deckHand;

	// Demo exchange method on hand
	const Card* exchangeCard1 = deckHand->exchange(2,1); // successful exchange
	const Card* exchangeCard2 = deckHand->exchange(2, 0); // unsuccessful exchange, exchangeCard2 is a nullptr

	std::cout << "Exchanged card: " << *exchangeCard1 << std::endl;
	

	return 0;
}
