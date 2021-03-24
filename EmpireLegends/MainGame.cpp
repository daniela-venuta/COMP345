#include "MainGame.h"

PlayerRotation::PlayerRotation(const vector<Player*>& players)
{
	this->players = players;
	this->current = this->players.begin();
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

Player* MainGame::getCurrentPlayer()
{
	return players->getCurrentPlayer();
}

MainGame::MainGame(BiddingFacility* biddingFacility, GameMap* map, Deck* deck, vector<Player*> players)
{
	this->biddingFacility = biddingFacility;
	this->map = map;
	this->deck = deck;
	this->players = new PlayerRotation(players);
}

void MainGame::afterAction()
{
	this->deck->draw(1);
	this->players->rotate();
	std::cout << getCurrentPlayer()->getName() << " plays next." << std::endl;
}
