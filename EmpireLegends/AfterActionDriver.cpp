#include "MainGame.h"

Deck* createDeck()
{

	vector<Card*> cardVector;
	cardVector.reserve(10);
	
	for (int i = 0; i < 10; i++)
	{
		cardVector.push_back(new Card("Card" + std::to_string(10-i), "Card" + std::to_string(10-i), "Some_action"));
	}

	Deck* deck = new Deck(cardVector);

	deck->draw(6);

	return deck;
}

int main()
{
	Deck* deck = createDeck();
	vector<Player*> players;
	players.push_back(new Player("p1", 10));
	players.push_back(new Player("p2",10));
	
	MainGame* mainGame = new MainGame(nullptr, nullptr, deck, players);

	std::cout << "First player: " << mainGame->getCurrentPlayer()->getName() << std::endl;

	std::cout << "Before first action:" << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << *deck->getHand() << std::endl;
	std::cout << "After first action:" << std::endl;
	std::cout << "---------------------" << std::endl;
	//deck->getHand()->exchange(2, mainGame->getCurrentPlayer());
	mainGame->afterAction();
	std::cout << *deck->getHand() << std::endl;

	std::cout << "Before second action:" << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << *deck->getHand() << std::endl;
	std::cout << "After second action:" << std::endl;
	mainGame->afterAction();
	std::cout << *deck->getHand() << std::endl;

	return 0;
}
