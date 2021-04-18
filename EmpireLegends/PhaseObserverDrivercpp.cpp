
#include "StartingPhase.h"
#include "MainGame.h"
#include "GameStart.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"

void demoGameStartObservers()
{
	GameStart* gameStart = new GameStart();
	GameStartObserver* gameStartObserver = new GameStartObserver(gameStart);
	gameStart->loadMap();
	gameStart->detPlayerCount();

	delete gameStartObserver;
	delete gameStart;
}

void demoStartupPhaseObservers()
{
	Player* p1 = new Player("Amy", 0);
	Player* p2 = new Player("Bob", 0);
	vector<Player*> players;
	players.push_back(p1);
	players.push_back(p2);
	
	// set up cards
	Card* card1 = new Card("Dire dragon", new Flying, new Action("Place 3 armies", 3), new Action("Destroy one army", 1), AndOr::AND);
	Card* card2 = new Card("Dire giant", new Immune, new Action("Place 3 armies", 3), new Action("Destroy 1 army", 1), AndOr::AND);
	Card* card3 = new Card("Dire eye", new Flying, new Action("Place 4 armies", 4));
	Card* card4 = new Card("Dire Goblin", new Elixir(1), new Action("Move 5 armies", 5));
	Card* card5 = new Card("Dire Ogre", new CoinVPs, new Action("Move 2 armies", 2));
	Card* card6 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place 2 armies", 2), new Action("Move 3 armies", 3), AndOr::AND);
	
	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(card1);
	cardVector.push_back(card2);
	cardVector.push_back(card3);
	cardVector.push_back(card4);
	cardVector.push_back(card5);
	cardVector.push_back(card6);
	
	// Create deck and add cards (this creates a card hand as well)
	Deck* cardDeck = new Deck(cardVector);
	
	// get map
	MapLoader* mapLoader = new MapLoader();
	GameMap* map = mapLoader->load("valid_map_1.json");
	StartingPhase* startingPhase = new StartingPhase();
	StartingPhaseObserver* startingPhaseObserver = new StartingPhaseObserver(startingPhase);
	startingPhase->startGame(map, players, cardDeck, 2);

	delete startingPhaseObserver;
	delete startingPhase;
}

void demoMainGameObservers()
{
	vector<Card*> cardVector;
	cardVector.reserve(27);
	vector<Player*> players;
	int numOfTurns = 0;
	int playerCount = 0;

	Card* card1 = new Card("Dire Dragon", new Flying, new Action("Place armies", 3) , new Action("Destroy armies", 3), AndOr::AND);
	Card* card2 = new Card("Dire Giant", new Immune, new Action("Place armies", 3), new Action("Destroy armies", 3), AndOr::AND);
	Card* card3 = new Card("Dire Eye", new Flying, new Action("Place armies", 4));
	Card* card4 = new Card("Dire Ogre", new CoinVPs, new Action("Move armies", 2));
	Card* card5 = new Card("Lake", new SetNameVPs(CardSet::forest), new Action("Place armies", 2), new Action("Move armies", 3),AndOr::AND);
	Card* card8 = new Card("Cursed Gargoyles", new Flying, new Action("Move armies", 5));
	Card* card9 = new Card("Arcane Sphinx", new Flying, new Action("Place armies", 2), new Action("Move armies", 4), AndOr::OR);
	Card* card10 = new Card("Dire Goblin", new Elixir(1), new Action("Move armies", 5));
	Card* card11 = new Card("Forest Elf", new ExtraArmy, new Action("Place armies", 3), new Action("Move armies", 2), AndOr::OR);
	Card* card12 = new Card("Forest Tree Town", new ExtraMove, new Action("Build city", 1));
	Card* card13 = new Card("Noble Knight", new ExtraMove, new Action("Place armies", 4), new Action("Destroy armies", 1), AndOr::AND);
	Card* card14 = new Card("Noble Unicorn", new ExtraMove, new Action("Move armies", 4), new Action("Place armies", 1), AndOr::AND);
	Card* card15 = new Card("Night Hydra", new ExtraArmy, new Action("Move armies", 5), new Action("Destroy armies", 1), AndOr::AND);
	Card* card16 = new Card("Night Village", new ExtraArmy, new Action("Build city", 1));
	Card* card17 = new Card("Castle 1", new Elixir(1), new Action("Place armies", 3),new Action("Build city", 1), AndOr::OR);
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

	players.push_back(new Player("John", 14, new HumanStrategy()));
	players.push_back(new Player("Bob", 14, new HumanStrategy()));
	numOfTurns = 4;

	MainGame* mainGame = new MainGame(nullptr, deck, players);
	MainGameObserver* mainGameObserver = new MainGameObserver(mainGame);
	mainGame->mainGameloop(numOfTurns);

	delete mainGameObserver;
	delete mainGame;
}

Deck* setDeck()
{
	Deck* deck = new Deck();
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

int main()
{
	GameStart* gameStart = new GameStart();
	GameStartObserver* gameStartObersever = new GameStartObserver(gameStart);
	
	//Game Start Part
	GameMap* gameMap = gameStart->loadMap();
	vector<Player*> players = gameStart->detPlayerBotCount();

	int num = players.size();
	StartingPhase* startPhase = new StartingPhase();
	StartingPhaseObserver* startingPhase = new StartingPhaseObserver(startPhase);
	Deck* deck = setDeck();
	players = startPhase->startGame(gameMap, players, deck, num);

	MainGame* mainGame = new MainGame(gameMap, deck, players);
	MainGameObserver* mainGameObserver = new MainGameObserver(mainGame);

	int numOfTurns = 4;
	mainGame->mainGameloop(numOfTurns);// Number of turns was set to a specific value based on criterias
	
	return 0;
}