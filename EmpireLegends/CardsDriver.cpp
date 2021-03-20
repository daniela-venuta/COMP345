//#include "Cards.h"
//#include <iostream>
//
//int main() {
//
//	// Create Card pointers
//	Card* cardOne = new Card("Dire dragon", "Dire dragon", "Place 3 armies and destroy one army");
//	Card* cardTwo = new Card("Dire giant", "Immune to attack", "Place 3 armies and destroy army");
//	Card* cardThree = new Card("Dire eye", "", "Place 4 armies");
//	Card* cardFour = new Card("Dire Ogre", " +1 VP per 3 coins", "Move 2 armies");
//	Card* cardFive = new Card("Lake", " +1 VP per Forest card", "Place 2 armies and move 3 armies");
//	Card* cardSix = new Card("Noble Hills", " Three noble cards = 4 VP", "Place 3 armies");
//
//	// Example of printing goods and actions of cards
//	std::cout << "Printing cards: \n";
//	std::cout << *cardOne;
//	std::cout << *cardTwo;
//	std::cout << *cardThree << std::endl;
//
//	// add Cards to a vector
//	vector<Card*> cardVector;
//	cardVector.push_back(cardOne);
//	cardVector.push_back(cardTwo);
//	
//
//	// Create deck and add cards (this creates a card hand as well)
//	std::cout << "Printing deck: \n";
//	Deck* deck = new Deck(cardVector);
//	std::cout << *deck;
//
//	//deck->swap(0, 1);
//	std::cout << *deck;
//
//	return 0;
//}
