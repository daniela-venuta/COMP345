#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>
#include <vector>
#include <algorithm>

// default constructor 
BiddingFacility::BiddingFacility() {
    bid = bid; 
}

// copy Constructor 
BiddingFacility::BiddingFacility(const BiddingFacility& obj) {
    bid = obj.bid; 
}

// stream insertion operator 
ostream& operator<<(ostream& output, const BiddingFacility& BDF) {
    output << "The bid is : " << BDF.getBids() ;
    return output;
}

// Assignment operator
BiddingFacility& BiddingFacility::operator=(const BiddingFacility& rhs) {
    return *this;
}


int BiddingFacility::getBids() const {
    return bid;
}

void BiddingFacility::setBids(int bid) {
    BiddingFacility::bid = bid;
}

void BiddingFacility::placeBid(vector <Player*> myPlayers) {

    int bid; 
    int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
    int maxbid = 0; 
    int supply3 =0;
    string temp; 
   
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

    cout << "--------------------------" << endl;
    cout << "WHO WILL GO FIRST??:" << endl;
    cout << "--------------------------\n" << endl;

    cout << "Bids placed by players: ";
    // checks if bids are equivalent or all zero
    for (int i = 0; i < myPlayers.size(); i++) {
       
        temp1 = myPlayers[i]->getBidFac()->getBids(); 
        
        for (int j = i+1; j < myPlayers.size(); j++) {
           
            temp2 = myPlayers[j]->getBidFac()->getBids();

            // checks if bids are equivalent or all bids are zero 
            if (temp1 == temp2 || (temp1 == 0 && temp2 == 0)) {
                temp3 = 1; 
            }     
        }
        cout << "\nPlayer: " << myPlayers[i]->getName() << "\t" << "Bids: " << myPlayers[i]->getBidFac()->getBids();   
    }  
            
    switch (temp3) {
    case 1:

        for (int i = 1; i < myPlayers.size(); i++) {
            if (i == 0) {
                continue; 
            }

            int a = myPlayers[i]->getName().length();
            int b = myPlayers[i-1]->getName().length();
            int rand = min(a, b);
            int j =0; 

           for (; j < rand; j++) {
                if (myPlayers[i]->getName().at(j) < myPlayers[i - 1]->getName().at(j)) {
                    
                    string rand1 = myPlayers[i - 1]->getName();
                    myPlayers[i - 1]->setName(myPlayers[i]->getName());
                    myPlayers[i]->setName(rand1); 
                    i = i - 2; 
                   break;
                }
                else if (myPlayers[i]->getName().at(j) == myPlayers[i - 1]->getName().at(j)) {
                    continue;

                }
                else if (myPlayers[i]->getName().at(j) > myPlayers[i - 1]->getName().at(j)) {
                    break; 
                }                                  
           }
            
            if (j == rand) {
                if (a <= b) {
                    string rand2 = myPlayers[i-1]->getName(); 
                    myPlayers[i - 1]->setName(myPlayers[i]->getName());
                    myPlayers[i]->setName(rand2);
                    i = i - 2;
                }
            }
        }

        cout << endl; 
        cout << "\n\nThe player to go first is " << myPlayers[0]->getName();

        break; 

    default: 
        for (int i = 0; i < myPlayers.size(); i++) {
            if (maxbid < myPlayers[i]->getBidFac()->getBids()) {
                maxbid = myPlayers[i]->getBidFac()->getBids();
                temp4 = i;
            }
        }
        cout << "\n\nThe player with the highest bid is " << myPlayers[temp4]->getName();

        supply3 = myPlayers[temp4]->getCoins() - myPlayers[temp4]->getBidFac()->getBids();

        myPlayers[temp4]->setCoins(supply3);
        cout << "\n" << myPlayers[temp4]->getName() << " now has " << supply3 << " coins.";
    }
}            
               
  
