#pragma once
#include <string>
using namespace std;

//class player;

class BiddingFacility {

	// Constructor 
	BiddingFacility(string name, int bid, int coins);

	// destructor 
	~BiddingFacility();

	// copy constructor
	BiddingFacility(const BiddingFacility& obj);

	// Assignment operator
	BiddingFacility& operator=(const BiddingFacility& rhs);

	// stream insertion operator 
	friend ostream& operator<<(ostream& output, const BiddingFacility& BD);

	// other methods 
	int getBid();
	void setBid();
	int compareBid();

};