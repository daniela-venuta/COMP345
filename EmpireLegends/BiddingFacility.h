#pragma once
#include <string>
#include <vector>
using namespace std;

class Player;

class BiddingFacility {

private: 
	int bid; 

public: 
	
	 void placeBid(vector <Player*> myPlayers);
	 int getBids() const;
	 void setBids(int bid); 

	// default constructor 
	BiddingFacility();

	// copy constructor
	BiddingFacility(const BiddingFacility& obj);

	// stream insertion operator 
	friend ostream& operator<<(ostream& output, const BiddingFacility& BDF);

	//// Assignment operator
	BiddingFacility& operator=(const BiddingFacility& rhs);
};