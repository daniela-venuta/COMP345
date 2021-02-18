#pragma once
#include "Player.h"
#include <string>
#include <vector>
using namespace std;

class BiddingFacility {

private: 
	int bids; 

public: 
	
	 void placeBid(vector <Player*> myPlayers);
	 int getBids();
	 void setBids(int bid); 

	//// default constructor 
	//BiddingFacility();

	//// destructor 
	//~BiddingFacility();

	//// copy constructor
	//BiddingFacility(const BiddingFacility& obj);

	//// stream insertion operator 
	//friend ostream& operator<<(ostream& output, const BiddingFacility& BDF);

	//// Assignment operator
	//BiddingFacility& operator=(const BiddingFacility& rhs);

	
	//
	//void setBids(const int bids);

	

};