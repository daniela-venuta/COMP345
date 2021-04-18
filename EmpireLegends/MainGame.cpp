#include "MainGame.h"
#include "Player.h"
#include "Cards.h"
#include <algorithm>
#include <iomanip>

PlayerRotation::PlayerRotation(const vector<Player*>& players)
{
	this->players = players;
	this->current = this->players.begin();
}

PlayerRotation::~PlayerRotation()
{
	for (auto* player : players)
	{
		delete player;
		player = nullptr;
	}
	players.clear();
}

void PlayerRotation::rotate()
{
	++current;

	if (current == players.end())
	{
		current = players.begin();
	}
}

Player* PlayerRotation::getCurrentPlayer()
{
	return *current;
}

int PlayerRotation::getNbPlayers()
{
	return players.size();
}

Player* MainGame::getCurrentPlayer()
{
	return players->getCurrentPlayer();
}

void MainGame::startPlayerTurn(const Player* player)
{
	state = player->getName() + "'s turn. They are buying a card";
	Notify();
}

void MainGame::SetupEndGame()
{
	state = "Initiating End Game and Calculating Winner....";
	Notify();
}

MainGame::MainGame(GameMap* map, Deck* deck, vector<Player*>& players)
{
	this->map = map;
	this->deck = deck;
	this->players = new PlayerRotation(players);
}

MainGame::~MainGame()
{
	delete map;
	delete players;
}

void MainGame::afterAction()
{
	state = "Turn ended.";
	Notify();

	this->deck->draw(1);
	this->players->rotate();
	std::cout << std::endl;
	std::cout << getCurrentPlayer()->getName() << " plays next." << std::endl;
}

void MainGame::mainGameloop(int numOfTurns) {
	deck->draw(6);
	std::cout << *deck->getHand() << std::endl;
	int turnNum = 1;

	while (turnNum <= numOfTurns) {
		std::cout << "-----------------------------------------------------------------------------"<< std::endl;
		std::cout << "Turn #" << turnNum << std::endl;

		for (int i = 0; i < players->getNbPlayers(); i++) {


			Player* player = getCurrentPlayer();
			startPlayerTurn(player);

			Card* faceCard = player->chooseCard(deck->getHand());

			std::cout << "Picked card: " << std::endl << *faceCard << std::endl;
			bool getCard = player->andOrAction(faceCard, map);
			
			if (getCard == true)
			{
				
				std::cout << "The card " + faceCard->getName() + " has been added to " << player->getName() << "'s hand." << std::endl;
				player->addCard(faceCard);
				player->applyGood(faceCard->getGood());
			}


			afterAction();
			std::cout << *deck->getHand() << std::endl;
		}
		turnNum++;
		Notify();
	}
	std::cout << "The Game is Over!!" << std::endl;
	chooseWinner();
}

// Calculate winner based off victory points (VPs)
void MainGame::chooseWinner() {

	SetupEndGame();
	vector<Player*> allPlayers = players->players;

	for (Player* player : allPlayers) {
		player->computeScore();
	}

	//1VP per owned continent
	auto continentIterator = map->terrs.begin();
	while (continentIterator != map->terrs.end()) {
		std::map<Player*, int> regionCounts;
		auto* cont = continentIterator->second->value;
		for (Player* p : allPlayers)
		{
			for (auto& region : cont->terrs)
			{
				auto playerTerrs = p->getTerritories();
				if (std::find(playerTerrs.begin(), playerTerrs.end(), region.second) != playerTerrs.end())
				{
					regionCounts[p] = regionCounts[p] + 1;
				}
			}
		}

		int maxCount = 0;
		vector<Player*> winners;
		for (auto itr = regionCounts.begin(); itr != regionCounts.end(); ++itr)
		{
			if (maxCount < itr->second)
			{
				maxCount = itr->second;
				winners.push_back(itr->first);
			}

			if (maxCount <= itr->second) {
				// New max bid
				if (maxCount < itr->second)
				{
					maxCount = itr->second;
					winners.clear(); // Clearing max bidders vector for new max bid
				}
				winners.push_back(itr->first);
			}
		}

		if (winners.size() == 1)
		{
			winners.at(0)->addVictoryPoints(maxCount);
		}

		// Increment the Iterator to point to next entry
		++continentIterator;
	}

	std::cout << "Determining the winner...";

	// 2VP for max elixir
	Player* mostElixirs{};
	for (int i = 0; i < allPlayers.size() - 1; i++) {
		if (allPlayers.at(i)->getResources()->elixir > allPlayers.at(i + 1)->getResources()->elixir) {
			mostElixirs = allPlayers.at(i);
		}
		else {
			mostElixirs = allPlayers.at(i + 1);
		}
	}
	mostElixirs->addVictoryPoints(2);

	// Determine winner
	vector<Player*> highestVPplayers;
	int highestVP = 0;
	for (Player* player : allPlayers) {
		int playerVP = player->getVictoryPoints();
		if (highestVP <= playerVP) {
			// New highest VP count
			if (highestVP < playerVP)
			{
				highestVP = playerVP;
				highestVPplayers.clear(); // Clearing highest VP player vector for new highest
			}
			highestVPplayers.push_back(player);
		}
	}

	// Tie on most VPs (most coins owned wins)
	vector<Player*> richestPlayers;
	int highestCoins = 0;

	if (highestVPplayers.size() > 1) {
		std::cout << "\nThere is a tie for victory points." << std::endl;
		std::cout << "Sorting by number of coins..." << std::endl;

		for (Player* player : allPlayers) {
			int playerCoins = player->getCoins();
			if (highestCoins <= playerCoins) {
				// New highest coin count
				if (highestCoins < playerCoins)
				{
					highestCoins = playerCoins;
					richestPlayers.clear(); // Clearing highest coin count vector for new highest
				}
				richestPlayers.push_back(player);
			}
		}

		// Tie on most coins (most armies owned wins)
		vector<Player*> mostArmiesPlayers;
		int highestArmyCount = 0;

		if (richestPlayers.size() > 1) {
			std::cout << "\nThere is a tie for number of coins." << std::endl;
			std::cout << "Sorting by number of armies..." << std::endl;

			for (Player* player : allPlayers) {
				int playerArmies = 18 - player->getResources()->unplacedArmies;
				if (highestArmyCount <= playerArmies) {
					// New highest army count
					if (highestArmyCount < playerArmies)
					{
						highestArmyCount = playerArmies;
						mostArmiesPlayers.clear(); // Clearing highest army count vector for new highest
					}
					mostArmiesPlayers.push_back(player);
				}
			}

			// Tie on most armies (most regions owned wins)
			Player* mostRegionsOwnedPlayer = mostArmiesPlayers.back();
			int highestNumberOfRegions = 0;

			if (mostArmiesPlayers.size() > 1) {
				std::cout << "\nThere is a tie for number of armies." << std::endl;
				std::cout << "Sorting by number of region..." << std::endl;

				for (Player* player : allPlayers) {
					int playerRegions = player->getTerritories().size();
					if (highestNumberOfRegions < playerRegions) {
						highestNumberOfRegions = playerRegions;
						mostRegionsOwnedPlayer = player;
					}
				}
			}
			else {
				std::cout << "The winner is " << mostRegionsOwnedPlayer->getName() << " with " << mostRegionsOwnedPlayer->getVictoryPoints() << " VPs!\n" << std::endl;
			}
		}
		else {
			std::cout << "The winner is " << richestPlayers.back()->getName() << " with " << richestPlayers.back()->getVictoryPoints() << " VPs!\n" << std::endl;
		}
	}
	else {
		std::cout << "The winner is " << highestVPplayers.back()->getName() << " with " << highestVPplayers.back()->getVictoryPoints() << " VPs!\n" << std::endl;
	}

	// function to display results 
	const char separator = '|';
	const int nameWidth = 15;
	const int numWidth = 10; 
	
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	std::cout << "Player #"
		<< std::setw(nameWidth + 3) << "Cards"
		<< std::setw(numWidth + 10) << "Victory Points"
		<< std::setw(numWidth) << "Coins"
		<< std::setw(numWidth + 10) << "Armies Placed" << std::endl;
	std::cout << "----------------------------------------------------------------------------" << std::endl;

	for (auto& player : allPlayers)
	{
		std::cout  << std::left<<  std::setw(nameWidth) << player->getName()
			<< std::right << std::setw(numWidth) << player->geNumOfOwnedCard()
			<< std::setw(numWidth + 10) << player->getVictoryPoints() 
			<< std::setw(numWidth) << player->getResources()->totalCoins
			<< std::setw(numWidth + 10) << player->getNumArmy() << std::endl;
		std::cout << "----------------------------------------------------------------------------" << std::endl;
	}
}

MainGameObserver::MainGameObserver(MainGame* s)
{
	subject = s;
	subject->Attach(this);
}

MainGameObserver::~MainGameObserver()
{
	subject->Detach(this);
}

void MainGameObserver::Update()
{
	display();
}

void MainGameObserver::display()
{
	std::cout << "--------------------------------------------------------------------- \n ---------------------------------------------------------------------  " << std::endl;
	std::cout << "Main Game: " << subject->getState() << std::endl;
	std::cout << "--------------------------------------------------------------------- \n ---------------------------------------------------------------------  " << std::endl;
}