#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>
#include <vector>

//// default constructor 
BiddingFacility::BiddingFacility(){}

//// copy Constructor 
//BiddingFacility::BiddingFacility(const BiddingFacility& obj) {
//    
//
//}
//
//// destructor 
//BiddingFacility::~BiddingFacility() {
//    
//}

//// stream insertion operator 
//ostream& operator<<(ostream& output, const BiddingFacility& BDF) {
//    
//}
//
//// Assignment operator
//BiddingFacility& BiddingFacility::operator=(const BiddingFacility& rhs) {
//
//}

int BiddingFacility::getBids() {
    return bid;
}

void BiddingFacility::setBids(int bid) {
    BiddingFacility::bid = bid;
}

void BiddingFacility::placeBid(vector <Player*> myPlayers) {

    int bid; 
    int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
    int maxbid = 0; 
    int supply1 = 0, supply2 = 0 , supply3 =0;
    string tmp; 

    // each players places their bid
    for (int i = 0; i < myPlayers.size(); i++) { 
        
        do {
            cout << "\n" << myPlayers[i]->getName() << " Place your bid: ";
            cin >> bid;
        } while (bid > myPlayers[i]->getCoins() || bid < 0);
        
        void ClearScreen();
        {
            cout << string(150, '\n');
        }
        myPlayers[i]->getBidFac()->setBids(bid); // sets each player w/ a bid
        
    }

    cout << "Bids of players and who will go first:" << endl;

    // checks if bids are equivalent or all zero
    for (int i = 0; i < myPlayers.size(); i++) {
       
        temp1 = myPlayers[i]->getBidFac()->getBids(); 
        
        for (int j = i+1; j < myPlayers.size(); j++) {
           
            temp2 = myPlayers[j]->getBidFac()->getBids();

            // checks if bids are equivalent or all bids are zero 
            if (temp1 == temp2 ) {
                temp3 = 2; 
            }
            if (temp1 == 0 && temp2 == 0) {

            }
        }       
    }

   // puts in alphabetical order 
    if (temp3 == 2) {

        for ( int i = 0; i < myPlayers.size(); i++) {
            for ( int j = 0; j < myPlayers.size(); j++) {
                if (myPlayers[i]->getName().at(0) < myPlayers[j]->getName().at(0)) {
                    tmp = myPlayers[i]->getName();
                    myPlayers[i]->getName() = myPlayers[j]->getName();
                    myPlayers[j]->getName() = tmp;
                }
            }
        }    
        cout << "The play to go first " << myPlayers[0]->getName();
    }

    else {
        for (int i = 0; i < myPlayers.size(); i++) {
            if (maxbid < myPlayers[i]->getBidFac()->getBids()) {
                maxbid = myPlayers[i]->getBidFac()->getBids(); 
                temp4 = i; 
            }
        }

        cout << "The player with the highest bid is " << myPlayers[temp4]->getName();
        supply1 = myPlayers[temp4]->getCoins(); 
        supply2 = myPlayers[temp4]->getBidFac()->getBids();
        supply3 = supply1 - supply2; 
        myPlayers[temp4]->setCoins(supply3);
        cout << "\n"<<myPlayers[temp4]->getName() << " now has " << myPlayers[temp4]->getCoins() << " coins."; 
    
    }

}








