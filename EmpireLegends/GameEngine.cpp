#include "GameEngine.h"
#include <iostream>
#include <fstream>


GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

Deck* GameEngine::setDeck()
{
	vector<Card*> cardVector;
	cardVector.reserve(27);

	Card* card1 = new Card("Dire Dragon", new Flying, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card2 = new Card("Dire Giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card3 = new Card("Dire Eye", new Flying, new Action("Place armies", 4));
	Card* card4 = new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2));
	Card* card5 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::AND);
	Card* card6 = new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place armies", 3));
	Card* card7 = new Card("Arcane Phoenix", new Flying, new Action("Move armies", 5));
	Card* card8 = new Card("Cursed Gargoyles", new Flying, new Action("Move armies", 5));
	Card* card9 = new Card("Arcane Sphinx", new Flying, new Action("Place armies", 2), new Action("Move armies", 4), AndOr::OR);
	Card* card10 = new Card("Dire Goblin", new Elixir(1), new Action("Move armies", 5));
	Card* card11 = new Card("Forest Elf", new ExtraArmy, new Action("Place armies", 3), new Action("Move armies", 2), AndOr::OR);
	Card* card12 = new Card("Forest Tree Town", new ExtraMove, new Action("Build city", 1));
	Card* card13 = new Card("Noble Knight", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND);
	Card* card14 = new Card("Noble Unicorn", new ExtraMove, new Action("Move armies", 4), new Action("Place armies", 1), AndOr::AND);
	Card* card15 = new Card("Night Hydra", new ExtraArmy, new Action("Move armies", 5), new Action("Destroy armies", 1), AndOr::AND);
	Card* card16 = new Card("Night Village", new ExtraArmy, new Action("Build city", 1));
	Card* card17 = new Card("Castle 1", new Elixir(1), new Action("Place armies", 3), new Action("Build city", 1), AndOr::OR);
	Card* card18 = new Card("Forest Pixie", new ExtraArmy, new Action("Move armies", 4));
	Card* card19 = new Card("Arcane Manticore", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND);
	Card* card20 = new Card("Ancient Woods", new ExtraArmy, new Action("Build city", 1), new Action("Place armies", 1), AndOr::AND);
	Card* card21 = new Card("Forest Gnome", new Elixir(3), new Action("Move armies", 2));
	Card* card22 = new Card("Castle 2", new Elixir(1), new Action("Move armies", 3), new Action("Build city", 1), AndOr::OR);
	Card* card23 = new Card("Ancient Tree Spirit", new Elixir(3), new Action("Place armies", 4), new Action("Build city", 1), AndOr::OR);
	Card* card24 = new Card("Ancient Woods", new ExtraArmy, new Action("Build city", 1), new Action("Place armies", 1), AndOr::AND);
	Card* card25 = new Card("Cursed Banshee", new Elixir(2), new Action("Move armies", 5));
	Card* card26 = new Card("Cursed King", new Elixir(1), new Action("Move armies", 4), new Action("Place armies", 3), AndOr::OR);
	Card* card27 = new Card("Cursed Mausoleum", new ExtraMove, new Action("Build city", 1));

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

	deck = new Deck(cardVector);

	return deck;
}

void GameEngine::singleMode()
{
	std::cout << "\n-------------------" << std::endl;
	std::cout << "Single Game Mode" << std::endl; 
	std::cout << "------------------" << std::endl;
	
	gameMap = gameStart->loadMap();
	vector<Player*> bots = gameStart->detPlayerBotCount();
}

void GameEngine::tournamentMode()
{
	std::cout << "\n----------------------" << std::endl;
	std::cout << "Tournament Game Mode" << std::endl;
	std::cout << "----------------------" << std::endl;

	//Game Start Part
	gameMap  = gameStart->loadMap();
	vector<Player*> bots = gameStart->detBotCount();

	int num = bots.size();

	//Starting Phase
	startPhase = new StartingPhase();

	bots = startPhase->startGameBot(gameMap, bots, setDeck(), num);

	// Maingameloop	
	mainGame = new MainGame(gameMap, setDeck(), bots);
	mainGame->mainGameloop(10);

}





//int GameEngine::numOfTurns(int playerCount) {
//
//	switch (playerCount) {
//	case 2:
//		players.push_back(new Player("John", 14));
//		players.push_back(new Player("Bob", 14));
//		return  10;
//		
//	case 3:
//		players.push_back(new Player("John", 11));
//		players.push_back(new Player("Bob", 11));
//		players.push_back(new Player("Anna", 11));
//		return 5;
//		
//	case 4:
//		players.push_back(new Player("John", 9));
//		players.push_back(new Player("Bob", 9));
//		players.push_back(new Player("Jack", 9));
//		players.push_back(new Player("Anna", 9));
//		return 3;
//		
//	}
//	
//}
	