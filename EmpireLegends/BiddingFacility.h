#pragma once
#include "Player.h"
#include <string>
using namespace std;

//class player;

class BiddingFacility {

private: 
	// stream insertion operator 
	friend ostream& operator<<(ostream& output, const BiddingFacility& BD);

public: 

	// default constructor 
	BiddingFacility();

	// Constructor 
	BiddingFacility(string name, int bid, int coins);

	// destructor 
	~BiddingFacility();

	// copy constructor
	BiddingFacility(const BiddingFacility& obj);

	// Assignment operator
	BiddingFacility& operator=(const BiddingFacility& rhs);


	// other methods 
	int getBid();
	
	void setBid();
	
	int compareBid();

};