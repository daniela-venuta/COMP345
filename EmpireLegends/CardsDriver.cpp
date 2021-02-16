#include "Cards.h"
#include <iostream>

int main() {
	Card* cardOne = new Card("1", "");
	Card* cardTwo = new Card("2", "");
	Card* cardThree = new Card("3", "");
	Card* cardFour = new Card("4", "");
	Card* cardFive = new Card("5", "");
	Card* cardSix = new Card("6", "");

	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(cardOne);
	cardVector.push_back(cardTwo);
	cardVector.push_back(cardThree);
	cardVector.push_back(cardFour);
	cardVector.push_back(cardFive);
	cardVector.push_back(cardSix);

	// Create deck and add cards
	Deck* deck = new Deck(cardVector);

	// Draw cards and add them to the hand
	deck->draw(4);

	const Hand* deckHand = deck->getHand();

	// print this way dany
	//std::cout << *cardOne;
	
	std::cout << *deck;
	std::cout << *deckHand;

	return 0;
}
