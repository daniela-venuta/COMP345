#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>

// default constructor 
BiddingFacility::BiddingFacility(){
    
}

// copy Constructor 
BiddingFacility::BiddingFacility(const BiddingFacility& obj) {
    
}

// destructor 
BiddingFacility::~BiddingFacility() {
    delete ptrbid;
}


// set method of bid
void BiddingFacility::setBids(const int bids) {
    *ptrbid = bids;
}

// get method of bid
int BiddingFacility::getBids() {
    return *ptrbid;
}


// method to let player place their bid
//PlaceBid(vector<Player*>& myPlayers)
int BiddingFacility:: PlaceBid(vector<Player*>& myPlayers) {
    int bid; 
    
    for (int i = 0; i < myPlayers.size(); i++) {
        cout << myPlayers[i]->getName()<<  "Place your bid: "; // player will need to place a bid
        cin >> bid;

        void ClearScreen();
        {
            cout << string(100, '\n');
        }
    }

    return bid; 
}


