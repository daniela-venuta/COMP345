#include "MainGame.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
	vector<Card*> cardVector;
	cardVector.reserve(27);
	vector<Player*> players;
	int numOfTurns = 0;
	int PlayerCount = 0;

	Card* card1 = new Card("Dire Dragon", new Flying, "Place 3 armies and destroy one army");
	Card* card2 = new Card("Dire Giant", new Immune, "Place 3 armies and destroy army");
	Card* card3 = new Card("Dire Eye", new Flying, "Place 4 armies");
	Card* card4 = new Card("Dire Ogre", new CoinVPs, "Move 2 armies");
	Card* card5 = new Card("Lake", new SetNameVPs(CardSet::forest), "Place 2 armies and move 3 armies");
	Card* card6 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), "Place 3 armies");
	Card* card7 = new Card("Arcane Phoenix", new Flying, "Move 5 armies ");
	Card* card8 = new Card("Cursed Gargoyles", new Flying, "Move 5 armies");
	Card* card9 = new Card("Arcane Sphinx", new Flying, "Place 2 armies or Move 4 armies");
	Card* card10 = new Card("Dire Goblin", new Elixir(1), "Move 5 armies");
	Card* card11 = new Card("Forest Elf", new ExtraArmy, "Place 3 armies or Move 2 armies");
	Card* card12 = new Card("Forest Tree Town", new ExtraMove, "Build a city");
	Card* card13 = new Card("Noble Knight", new ExtraMove, "Place 4 armies and destroy one army");
	Card* card14 = new Card("Noble Unicorn", new ExtraMove, "Move 4 armies and place one army");
	Card* card15 = new Card("Night Hydra", new ExtraArmy, "Move 5 armies and destroy one army");
	Card* card16 = new Card("Night Village", new ExtraArmy, "Build a city");
	Card* card17 = new Card("Castle 1", new Elixir(1), "Place 3 armies or Build a city");
	Card* card18 = new Card("Forest Pixie", new ExtraArmy, "Move 4 armies");
	Card* card19 = new Card("Arcane Manticore", new ExtraMove, "Place 4 armies and destroy one army");
	Card* card20 = new Card("Ancient Woods", new ExtraArmy, "Build a city and place one army");
	Card* card21 = new Card("Forest Gnome", new Elixir(3), "Move 2 armies");
	Card* card22 = new Card("Castle 2", new Elixir(1), "Move 3 armies or Build a city");
	Card* card23 = new Card("Ancient Tree Spirit", new Elixir(3), "Place 4 armies or Build a city");
	Card* card24 = new Card("Ancent Woods", new ExtraArmy, "Build a city and place and army");
	Card* card25 = new Card("Cursed Banshee", new Elixir(2), "Move 5 armies");
	Card* card26 = new Card("Cursed King", new Elixir(1), "Move 4 armies or place 3 armies");
	Card* card27 = new Card("Cursed Mausoleum", new ExtraMove, "Build a city");

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
	cardVector.push_back(card14);
	cardVector.push_back(card15);
	cardVector.push_back(card16);
	cardVector.push_back(card17);
	cardVector.push_back(card18);
	cardVector.push_back(card19);
	cardVector.push_back(card20);
	cardVector.push_back(card21);
	cardVector.push_back(card22);
	cardVector.push_back(card23);
	cardVector.push_back(card24);
	cardVector.push_back(card25);
	cardVector.push_back(card26);
	cardVector.push_back(card27);

	Deck* deck = new Deck(cardVector);

	std::cout << "Face up cards: \n";
	std::cout << "1- " << *card6;
	std::cout << "2- " << *card5;
	std::cout << "3- " << *card4;
	std::cout << "4- " << *card3;
	std::cout << "5- " << *card2;
	std::cout << "6- " << *card1 << std::endl;

	do {
		std::cout << "How many players will be playing (2-4)?  ";
		std::cin >> PlayerCount;
	} while (PlayerCount > 4 || PlayerCount < 2);


	switch (PlayerCount) {

	case 2:
		players.push_back(new Player("John", 14));
		players.push_back(new Player("Bob", 14));
		numOfTurns = 13;
		break;

	case 3:
		players.push_back(new Player("John", 11));
		players.push_back(new Player("Bob", 11));
		players.push_back(new Player("Anna", 11));
		numOfTurns = 10;
		break;

	case 4:
		players.push_back(new Player("John", 9));
		players.push_back(new Player("Bob", 9));
		players.push_back(new Player("Jack", 9));
		players.push_back(new Player("Anna", 9));
		numOfTurns = 8;
		break;
	}

	MainGame* mainGame = new MainGame(nullptr, nullptr, deck, players);

	mainGame->mainGameloop(cardVector, numOfTurns, players);

	for (Card* card : cardVector)
	{
		delete card;
		card = nullptr;
	}

	for (Player* player : players)
	{
		delete player;
	}

	return 0;
}