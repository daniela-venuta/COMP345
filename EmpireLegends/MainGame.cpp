#include "MainGame.h"
#include "Cards.h"
#include "Player.h"

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
    while (myPlayers[0]->getNumofcards() != 13|| myPlayers[1]->getNumofcards() != 13) {


        for (int i = 0; i < myPlayers.size(); i++) {

            std::cout << "\n\nPlayer " << myPlayers[i]->getName() << std::endl;

            int cardposition = PickACard();
            myPlayers[i]->setNumofcards(); // adds a card to the player when a  card is picked

            std::cout << "\n";

            Hand* deckHand = deck->getHand();
            int cardcost = deckHand->getCardCost(cardposition);

            myPlayers[i]->PayCoin(cardcost);

            int cardDeckPos = (cardposition);
            Card* facecard = cardDeck[cardDeckPos];

            myPlayers[i]->addGoods(facecard->getGood());

            std::cout << "Players card good : " << *facecard->getGood() << std::endl;
            std::cout << "Players card action : " << facecard->getAction() << std::endl;
                
            std::cout << "The number of cards for " << myPlayers[0]->getName() << " is " << myPlayers[0]->getNumofcards() << std::endl;
            std::cout << "The number of cards for " << myPlayers[1]->getName() << " is " << myPlayers[1]->getNumofcards() << std::endl;   

            if (myPlayers[i]->getNumofcards() == 13)
            {
                std::cout << "The Game is Over!! " << std::endl;
                exit(0);
            }

        }

    } 
}

int MainGame::PickACard() {

    int cardposition;

    do {
        std::cout << "Pick a position (1-6): ";
        std::cin >> cardposition;
    } while (cardposition > 6  || cardposition < 1);

    return cardposition;
}

