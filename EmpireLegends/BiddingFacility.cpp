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

bool BiddingFacility::mycomp(string a, string b) {
    return a < b;
}
vector<string> BiddingFacility::alphabaticallySort(vector<string> a) {
    int n = a.size();
    sort(a.begin(), a.end(), mycomp());
    return a; 
}

void BiddingFacility::placeBid(vector <Player*> myPlayers) {

    int bid; 
    int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
    int maxbid = 0; 
    int supply1 = 0, supply2 = 0 , supply3 =0;
    string tmp; 
    string name;
    vector<string> names;

   

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
    }
            
    switch (temp3) {
    case 1:        
        for (int i = 0; i < myPlayers.size(); i++) {
            string name = myPlayers[i]->getName();
            names.push_back(name); 
        }
        names = alphabaticallySort(names); 
        cout << "\nThe player to go first is " << names[0];
        break; 

    default: 
        for (int i = 0; i < myPlayers.size(); i++) {
            if (maxbid < myPlayers[i]->getBidFac()->getBids()) {
                maxbid = myPlayers[i]->getBidFac()->getBids();
                temp4 = i;
            }
        }
        cout << "\nThe player with the highest bid is " << myPlayers[temp4]->getName();

        supply3 = myPlayers[temp4]->getCoins() - myPlayers[temp4]->getBidFac()->getBids();

        myPlayers[temp4]->setCoins(supply3);
        cout << "\n" << myPlayers[temp4]->getName() << " now has " << supply3 << " coins.";
    }
}





    
        
    
/*for (int i = 0; i < myPlayers.size(); i++) {
           for (int j = 1; j < myPlayers.size(); j++) {
               int k = 0;

               if (myPlayers[i]->getName().at(k) == myPlayers[j]->getName().at(k)) {
                   k++;
                   if (myPlayers[i]->getName().at(k) < myPlayers[j]->getName().at(k)) {
                       tmp = myPlayers[i]->getName();
                       cout << tmp << "\n";
                       myPlayers[i]->getName() = myPlayers[j]->getName();
                       myPlayers[j]->getName() = tmp;
                   }
               }
           }
       }
       */
    


