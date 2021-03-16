#include "MainGame.h"
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

void MainGame::maingameloop(vector<Card*> cardDeck, vector<Player*> myPlayers) {

	int cardpos;

	for (int i = 0; i < myPlayers.size(); i++) {

		std::cout << "\n\nPlayer " << myPlayers[i]->getName() << std::endl;

		do {
			std::cout << "Pick a position (1-6): ";
			std::cin >> cardpos;
		} while (cardpos > 6 || cardpos < 1);

		std::cout << "\n";

		myPlayers[i]->setCoins(faceupCards(cardDeck, cardpos, myPlayers[i]->getCoins()));
		std::cout << "The remaining coins of " << myPlayers[i]->getName() << " is " << myPlayers[i]->getCoins() << std::endl;
	}
}

int MainGame::faceupCards(vector<Card*> cardDeck, int cardpos, int coins) {

	Hand* deckHand = deck->getHand();
	int cardcost = deckHand->getCardCost(cardpos);

	int cardDeckPos = cardpos - 1;
	Card* facecard = cardDeck[cardDeckPos];

	std::cout << "The cost of the card is " << cardcost << std::endl;
	int coinsRemaining = coins - cardcost;

	std::cout << "Players card good : " << facecard->getGoods() << std::endl;
	std::cout << "Players card action : " << facecard->getAction() << std::endl;

	return coinsRemaining;
}


