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


void MainGame::mainGameloop(vector<Card*> cardVector, int numOfTurns, vector<Player*> players) {

    int cardposition = 0;

    while (numOfTurns > 0) {

        for (int i = 0; i < players.size(); i++) {

            std::cout << "\n\nPlayer " << players[i]->getName() << std::endl;

            cardposition = pickACard();

            std::cout << "\n";

            Hand* deckHand = deck->getHand();

            int cardcost = deckHand->getCardCost(cardposition);
            int cardDeckPos = (cardposition - 1);

            Card* facecard = cardVector[cardDeckPos];

            if (players[i]->getBalance() >= cardcost) {

                players[i]->payCoin(cardcost);

                players[i]->applyGood(facecard->getGood());

                std::cout << "Players card good : " << *facecard->getGood() << std::endl;

                std::cout << "Players card action : " << facecard->getAction() << std::endl;
            }
            else {

                std::cout << "Card not added to player" << std::endl;
            }
        }
        numOfTurns--;
    }
    std::cout << "The Game is Over!!" << std::endl;
}

int MainGame::pickACard() {

    int cardposition;

    do {
        std::cout << "Pick a position (1-6): ";
        std::cin >> cardposition;
    } while (cardposition > 6 || cardposition < 1);

    return cardposition;
}