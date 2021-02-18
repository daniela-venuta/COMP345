#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>
#include <vector>

//// default constructor 
//BiddingFacility::BiddingFacility(){
//   
//}

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
    return BiddingFacility::bids; 
}

void BiddingFacility::setBids(int bid) {
    bid = bid; 
}

void BiddingFacility::placeBid(vector <Player*> myPlayers) {
   
    int bid;

    for (int i = 0; i < myPlayers.size(); i++) {
        cout << myPlayers[i]->getName() << " Place your bid: "; // player will need to place a bid
        cin >> bid;

        while (bid > myPlayers[i]->getCoins() || bid < 0) {
            cout << " Place your bid: ";
            cout << myPlayers[i]->getName() << " Place your bid: ";
        }
       
        void ClearScreen();
        {
            cout << string(150, '\n');
        }
    }
    // reveals the bid of each player
    for (int i = 0; i < myPlayers.size(); i++) {
        cout << "Bids placed by each player: ";
        cout << "Player "<< myPlayers[i]->getName() << "\tBid: " << myPlayers[i]->getBidFacility()->getBids();
    
    }

    // checks to see who put the highest bid and reveals 
    for (int i = 0; i < myPlayers.size(); i++) {
        int max = 0; 


    }





}