#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>
#include <vector>

// default constructor 
BiddingFacility::BiddingFacility(){
   
}

// copy Constructor 
BiddingFacility::BiddingFacility(const BiddingFacility& obj) {
    

}

// destructor 
BiddingFacility::~BiddingFacility() {
    
}


// set method of bid
void BiddingFacility::setBids(const int bids) {
    
}

// get method of bid
int BiddingFacility::getBids() {
    
}

// stream insertion operator 
ostream& operator<<(ostream& output, const BiddingFacility& BDF) {
    
}

// Assignment operator
BiddingFacility& BiddingFacility::operator=(const BiddingFacility& rhs) {

}

// method to place and compare bids per player
int BiddingFacility::PlaceBid(vector <Player*> myPlayers) {
    
    int bid;
    for (int i = 0; i < myPlayers.size(); i++) {
        cout << myPlayers[i]->getName() << "Place your bid: "; // player will need to place a bid
        cin >> bid;

        void ClearScreen();
        {
            cout << string(100, '\n');
        }
    }

    return bid;





}