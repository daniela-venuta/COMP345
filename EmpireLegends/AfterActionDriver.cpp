//#include "MainGame.h"
//
//int main()
//{
//	Card* card1 = new Card("Dire Dragon", new Flying, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
//	Card* card2 = new Card("Dire Giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
//	Card* card3 = new Card("Dire Eye", new Flying, new Action("Place armies", 4));
//	Card* card4 = new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2));
//	Card* card5 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::AND);
//	Card* card6 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place armies", 3));
//	Card* card7 = new Card("Arcane Phoenix", new Flying, new Action("Move armies", 5));
//	Card* card8 = new Card("Cursed Gargoyles", new Flying, new Action("Move armies", 5));
//	Card* card9 = new Card("Arcane Sphinx", new Flying, new Action("Place armies", 2), new Action("Move armies", 4), AndOr::OR);
//	vector<Card*> cards;
//	cards.push_back(card1);
//	cards.push_back(card2);
//	cards.push_back(card3);
//	cards.push_back(card4);
//	cards.push_back(card5);
//	cards.push_back(card6);
//	cards.push_back(card7);
//	cards.push_back(card8);
//	cards.push_back(card9);
//	Deck* deck = new Deck(cards);
//	deck->draw(6);
//	vector<Player*> players;
//	players.push_back(new Player("p1", 10));
//	players.push_back(new Player("p2",10));
//	
//	MainGame* mainGame = new MainGame(nullptr, deck, players);
//
//	std::cout << "First player: " << mainGame->getCurrentPlayer()->getName() << std::endl;
//
//	std::cout << std::endl << "Before first action:" << std::endl;
//	std::cout << "-----------------------------------------------" << std::endl;
//	std::cout << *deck->getHand() << std::endl;
//	
//	Card* cardExchange1 = deck->getHand()->exchange(3, mainGame->getCurrentPlayer());
//	mainGame->getCurrentPlayer()->addCard(cardExchange1);
//	std::cout << "Card exchanged: " << *cardExchange1 << std::endl;
//	std::cout << std::endl << "After first action (removing third card):" << std::endl;
//	std::cout << "-----------------------------------------------" << std::endl;
//	mainGame->afterAction();
//	std::cout << *deck->getHand() << std::endl;
//
//	Card* cardExchange2 = deck->getHand()->exchange(1, mainGame->getCurrentPlayer());
//	mainGame->getCurrentPlayer()->addCard(cardExchange2);
//	std::cout << "Card exchanged: " << *cardExchange2 << std::endl;
//	std::cout << std::endl << "After second action (removing first card):" << std::endl;
//	std::cout << "-----------------------------------------------" << std::endl;
//	mainGame->afterAction();
//	std::cout << *deck->getHand() << std::endl;
//
//	Card* cardExchange3 = deck->getHand()->exchange(6, mainGame->getCurrentPlayer());
//	mainGame->getCurrentPlayer()->addCard(cardExchange3);
//	std::cout << "Card exchanged: " << *cardExchange3 << std::endl;
//	std::cout << std::endl << "After third action (removing sixth card):" << std::endl;
//	std::cout << "-----------------------------------------------" << std::endl;
//	mainGame->afterAction();
//	std::cout << *deck->getHand() << std::endl;
//	
//	delete mainGame;
//	return 0;
//}
