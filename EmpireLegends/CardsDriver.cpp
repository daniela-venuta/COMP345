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
//	cardVector.push_back(cardThree);
//	cardVector.push_back(cardFour);
//	cardVector.push_back(cardFive);
//	cardVector.push_back(cardSix);
//
//	// Create deck and add cards (this creates a card hand as well)
//	std::cout << "Printing deck: \n";
//	Deck* deck = new Deck(cardVector);
//	std::cout << *deck;
//	
//	// Draw cards from deck and add them to the hand
//	deck->draw(4);
//	std::cout <<"New deck after draw: \n" <<*deck << std::endl;
//
//	// Get Hand from the deck
//	Hand* deckHand = deck->getHand();
//	std::cout << *deckHand << std::endl;
//
//	// Demo exchange method on hand
//	const Card* exchangeCard1 = deckHand->exchange(2,1); // successful exchange
//	const Card* exchangeCard2 = deckHand->exchange(2, 0); // unsuccessful exchange, exchangeCard2 is a nullptr
//
//	std::cout << "Exchanged card: " << *exchangeCard1 << std::endl;
//
//	// delete cards created CHECK
//	for(Card* card : cardVector)
//	{
//		delete card;
//		card = nullptr;
//	}
//	
//	return 0;
//}
