#include "MainGame.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
	vector<Card*> cardVector;
	vector<Player*> myPlayers;

	Card* cardOne = new Card("card1", "Dire dragon", "Place 3 armies and destroy one army");
	Card* cardTwo = new Card("card2", "Dire giant", "Place 3 armies and destroy army");
	Card* cardThree = new Card("card3", "Dire eye", "Place 4 armies");
	Card* cardFour = new Card("card4", "Dire Ogre", "Move 2 armies");
	Card* cardFive = new Card("card5", "Lake", "Place 2 armies and move 3 armies");
	Card* cardSix = new Card("card6", "Noble Hills", "Place 3 armies");

	cardVector.push_back(cardOne);
	cardVector.push_back(cardTwo);
	cardVector.push_back(cardThree);
	cardVector.push_back(cardFour);
	cardVector.push_back(cardFive);
	cardVector.push_back(cardSix);

	Deck* cardDeck = new Deck(cardVector);

	cardDeck->draw(6);

	std::cout << "Face up cards: \n";
	std::cout << "1- " << *cardOne;
	std::cout << "2- " << *cardTwo;
	std::cout << "3- " << *cardThree;
	std::cout << "4- " << *cardFour;
	std::cout << "5- " << *cardFive;
	std::cout << "6- " << *cardSix << std::endl;

	myPlayers.push_back(new Player("John", 11));
	myPlayers.push_back(new Player("Bob", 11));
	myPlayers.push_back(new Player("Jack", 11));

	MainGame* mainGameL = new MainGame(nullptr, nullptr, cardDeck, myPlayers);

	mainGameL->maingameloop(cardVector, myPlayers);

	for (Card* card : cardVector)
	{
		delete card;
		card = nullptr;
	}

	for (Player* player : myPlayers)
	{
		delete player;
	}
		
	return 0;
}



