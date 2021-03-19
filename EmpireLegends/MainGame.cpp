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
		
	do {
			int cardpos;
			
			for (int i = 0; i < myPlayers.size(); i++) {

				std::cout << "\n\nPlayer " << myPlayers[i]->getName() << std::endl;

				do {
					std::cout << "Pick a position (1-6): ";
					std::cin >> cardpos;
				} while (cardpos > 6 || cardpos < 1);

				
				std::cout << "\n";

				Hand* deckHand = deck->getHand();
				int cardcost = deckHand->getCardCost(cardpos);
				 				
				myPlayers[i]->PayCoin(cardcost);

				int cardDeckPos = cardpos - 1;
				Card* facecard = cardDeck[cardDeckPos];				
				
				myPlayers[i]->setNumofcards();
				
				PlayerFaceCard(facecard, myPlayers[i]);							
			}
			
			std::cout << "The number of cards for " << myPlayers[0]->getName()<< " is " << myPlayers[0]->getNumofcards() << std::endl;

			std::cout << "The number of cards for " << myPlayers[1]->getName() << " is " << myPlayers[1]->getNumofcards() << std::endl;
		
		} while (myPlayers[0]->getNumofcards() < 13 || myPlayers[1]->getNumofcards() < 13);	

		std::cout << "The Game is Over!! " << std::endl; 
}

void MainGame::PlayerFaceCard(Card* facecard, Player* myPlayers) {
		
	std::cout << "Players card good : " << facecard->getGoods() << std::endl;
	std::cout << "Players card action : " << facecard->getAction() << std::endl;		
}