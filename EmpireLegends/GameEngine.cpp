#include "GameEngine.h"
#include <iostream>
#include <fstream>


GameEngine::GameEngine()
{
	gameStart = new GameStart();
	startPhase = nullptr;
	mainGame = nullptr;
	setDeck();
}

GameEngine::~GameEngine()
{
	delete gameStart;
	delete startPhase;
	delete mainGame;
	delete deck;
}

void GameEngine::setDeck()
{
	vector<Card*> cardVector;
	cardVector.reserve(27);

	cardVector.push_back(new Card("Dire Dragon", new Flying, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND));
	cardVector.push_back(new Card("Dire Giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND));
	cardVector.push_back(new Card("Dire Eye", new Flying, new Action("Place armies", 4)));
	cardVector.push_back(new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2)));
	cardVector.push_back(new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3), AndOr::AND));
	cardVector.push_back(new Card("Noble Hills", new CompleteSetVPs(3, CardSet::noble), new Action("Place armies", 3)));
	cardVector.push_back(new Card("Arcane Phoenix", new Flying, new Action("Move armies", 5)));
	cardVector.push_back(new Card("Cursed Gargoyles", new Flying(), new Action("Move armies", 5)));
	cardVector.push_back(new Card("Arcane Sphinx", new Flying, new Action("Place armies", 2), new Action("Move armies", 4), AndOr::OR));
	cardVector.push_back(new Card("Dire Goblin", new Elixir(1), new Action("Move armies", 5)));
	cardVector.push_back(new Card("Forest Elf", new ExtraArmy, new Action("Place armies", 3), new Action("Move armies", 2), AndOr::OR));
	cardVector.push_back(new Card("Forest Tree Town", new ExtraMove, new Action("Build city", 1)));
	cardVector.push_back(new Card("Noble Knight", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND));
	cardVector.push_back(new Card("Noble Unicorn", new ExtraMove, new Action("Move armies", 4), new Action("Place armies", 1), AndOr::AND));
	cardVector.push_back(new Card("Night Hydra", new ExtraArmy, new Action("Move armies", 5), new Action("Destroy armies", 1), AndOr::AND));
	cardVector.push_back(new Card("Night Village", new ExtraArmy, new Action("Build city", 1)));
	cardVector.push_back(new Card("Castle 1", new Elixir(1), new Action("Place armies", 3), new Action("Build city", 1), AndOr::OR));
	cardVector.push_back(new Card("Forest Pixie", new ExtraArmy, new Action("Move armies", 4)));
	cardVector.push_back(new Card("Arcane Manticore", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND));
	cardVector.push_back(new Card("Ancient Woods", new ExtraArmy, new Action("Build city", 1), new Action("Place armies", 1), AndOr::AND));
	cardVector.push_back(new Card("Forest Gnome", new Elixir(3), new Action("Move armies", 2)));
	cardVector.push_back(new Card("Castle 2", new Elixir(1), new Action("Move armies", 3), new Action("Build city", 1), AndOr::OR));
	cardVector.push_back(new Card("Ancient Tree Spirit", new Elixir(3), new Action("Place armies", 4), new Action("Build city", 1), AndOr::OR));
	cardVector.push_back(new Card("Ancient Woods", new ExtraArmy, new Action("Build city", 1), new Action("Place armies", 1), AndOr::AND));
	cardVector.push_back(new Card("Cursed Banshee", new Elixir(2), new Action("Move armies", 5)));
	cardVector.push_back(new Card("Cursed King", new Elixir(1), new Action("Move armies", 4), new Action("Place armies", 3), AndOr::OR));
	cardVector.push_back(new Card("Cursed Mausoleum", new ExtraMove, new Action("Build city", 1)));

	deck = new Deck(cardVector);
}

void GameEngine::singleMode()
{
	std::cout << "\n-------------------" << std::endl;
	std::cout << "Single Game Mode" << std::endl; 
	std::cout << "------------------" << std::endl;

	//Game Start Part
	GameMap* gameMap = gameStart->loadMap();
	vector<Player*> players = gameStart->detPlayerBotCount();

	startPhase = new StartingPhase(gameMap, deck);
	players = startPhase->startGame(players);

	mainGame = new MainGame(gameMap, deck, players);

	int numOfTurns = 10;
	mainGame->mainGameloop(numOfTurns); // Number of turns was set to a value based on specified criteria
	
	players.clear();
}

void GameEngine::tournamentMode()
{
	std::cout << "\n----------------------" << std::endl;
	std::cout << "Tournament Game Mode" << std::endl;
	std::cout << "----------------------" << std::endl;

	//Game Start Part
	GameMap* gameMap = gameStart->loadMap();
	vector<Player*> bots = gameStart->detBotCount();

	startPhase = new StartingPhase(gameMap, deck);
	bots = startPhase->startGame(bots);

	// Main game loop	
	mainGame = new MainGame(gameMap, deck, bots);

	int numOfTurns = 10;
	mainGame->mainGameloop(numOfTurns); // Number of turns was set to a value based on specified criteria
}