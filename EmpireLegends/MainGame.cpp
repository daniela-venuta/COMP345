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


void MainGame::maingameloop(vector<Card*> cardVector, int numOfTurns , vector<Player*> myPlayers) {
       
    int cardposition = 0;
    std::cout << myPlayers[0]->getBalance(); 
    std::cout << myPlayers[1]->getBalance();
        
    while (numOfTurns > 0) {
            
        std::cout <<"The number od turns player: "<< numOfTurns << std::endl; 
        for (int i = 0; i < myPlayers.size(); i++) {
         
            std::cout << "\n\nPlayer " << myPlayers[i]->getName() << std::endl;
             
            cardposition = PickACard();
                                      
            std::cout << "\n";
               
            Hand* deckHand = deck->getHand();
                
            int cardcost = deckHand->getCardCost(cardposition);              
            int cardDeckPos = (cardposition - 1);
                
            Card* facecard = cardVector[cardDeckPos];
               
            if (myPlayers[i]->getBalance() >= cardcost) {
                                 
                myPlayers[i]->PayCoin(cardcost);
                   
                myPlayers[i]->addGoods(facecard->getGood());
                  
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



int MainGame::PickACard() {

    int cardposition;

    do {
        std::cout << "Pick a position (1-6): ";
        std::cin >> cardposition;
    } while (cardposition > 6 || cardposition < 1);

    return cardposition;
}




