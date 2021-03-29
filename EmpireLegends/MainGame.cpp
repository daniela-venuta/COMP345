#include "MainGame.h"
#include "Player.h"
#include "Cards.h"

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

int PlayerRotation::getNbPlayers()
{
	return players.size();
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

void MainGame::mainGameloop(int numOfTurns) {
	deck->draw(6);
	std::cout << *deck->getHand() << std::endl;

	while (numOfTurns > 0) {
		std::cout << "The number of turns " << numOfTurns << std::endl;

		for (int i = 0; i < players->getNbPlayers(); i++) {

			Player* player = getCurrentPlayer();
			std::cout << "\n\nPlayer " << player->getName() << std::endl;

			Card* faceCard = nullptr;

			while (faceCard == nullptr) {
				const int cardPosition = pickACard();
				std::cout << "\n";

				Hand* deckHand = deck->getHand();

				faceCard = deckHand->exchange(cardPosition, player);

				if (faceCard == nullptr) {
					std::cout << "Card not added to player" << std::endl;
				}
			}
			std::cout << "Picked card: " << std::endl << *faceCard << std::endl;

			player->applyGood(faceCard->getGood());

			afterAction();
			std::cout << *deck->getHand() << std::endl;
		}
		numOfTurns--;
	}
	std::cout << "The Game is Over!!" << std::endl;
}

// Player picks the position of the card
int MainGame::pickACard() {

	int cardposition;

	do {
		std::cout << "Pick a position (1-6): ";
		std::cin >> cardposition;
	} while (cardposition > 6 || cardposition < 1);

	return cardposition;
}