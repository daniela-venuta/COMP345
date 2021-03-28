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


void MainGame::mainGameloop(int numOfTurns, vector<Player*> players) {

    int cardposition = 0;
    
    deck->draw(6); 
    std::cout << *deck->getHand() << std::endl;
     
    while (numOfTurns > 0) {
              
        for (int i = 0; i < players.size(); i++) {

            std::cout << "\n\nPlayer " << players[i]->getName() << std::endl;

            cardposition = pickACard();
            std::cout << "\n";

            Hand* deckHand = deck->getHand();
          
           //Card* handDeck = deckHand->getHandCards();

                     
            int cardcost = deckHand->getCardCost(cardposition);
            int cardDeckPos = (cardposition - 1);
          
            vector<Card*> Hand = deckHand->getHandCards();
           
            Card* facecard =  Hand.at(cardDeckPos);
           
            std::cout << "Card exchanged: " << *deck->getHand()->exchange(cardDeckPos, players[i]) << std::endl;
            
            //deck->getCardDeck();
            
            //Card* facecard = deckHand->getHandCards()[cardDeckPos];
                      
            if (players[i]->getBalance() >= cardcost) {

                players[i]->payCoin(cardcost);

                players[i]->applyGood(facecard->getGood());

                std::cout << "Players card good : " << *facecard->getGood() << std::endl;

                std::cout << "Players card action : " << facecard->getAction() << std::endl;
            }
            else {

                std::cout << "Card not added to player" << std::endl;
            }      
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