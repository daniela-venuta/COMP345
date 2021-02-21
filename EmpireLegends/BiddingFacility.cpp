#include "Player.h"
#include "BiddingFacility.h"
#include <iostream>
#include <vector>
#include <algorithm>

// default constructor 
BiddingFacility::BiddingFacility() {
	this->bid = 0;
}

// copy Constructor 
BiddingFacility::BiddingFacility(const BiddingFacility& obj) {
	this->bid = obj.bid;
}

// stream insertion operator 
ostream& operator<<(ostream& output, const BiddingFacility& facility) {
	output << "The bid is : " << facility.getCurrentBid();
	return output;
}

// Assignment operator
BiddingFacility& BiddingFacility::operator=(const BiddingFacility& rhs) {
	this->bid = rhs.getCurrentBid();
	return *this;
}

int BiddingFacility::getCurrentBid() const {
	return bid;
}

void BiddingFacility::setCurrentBid(int bid) {
	this->bid = bid;
}

void BiddingFacility::addPlayerBid(Player* player, int playerBid)
{
	this->bids.insert(std::make_pair(player, playerBid));
}

int BiddingFacility::getPlayerBid(Player* player)
{
	return this->bids[player];
}

void BiddingFacility::placeBids(vector<Player*> biddingPlayers) {

	auto playerBid = 0;
	string temp;

	// each players places their bid
	for (auto& myPlayer : biddingPlayers)
	{
		do {
			std::cout << "\n" << myPlayer->getName() << " Place your bid: ";
			std::cin >> playerBid;
		} while (playerBid > myPlayer->getCoins() || playerBid < 0);

		system("cls");

		this->addPlayerBid(myPlayer, playerBid);
	}

	std::cout << "--------------------------" << std::endl;
	std::cout << "WHO WILL GO FIRST??:" << std::endl;
	std::cout << "--------------------------\n" << std::endl;

	std::cout << "Bids placed by players: " << std::endl;
	// checks if bids are equivalent or all zero
	for (auto& myPlayer : biddingPlayers)
	{
		std::cout << "Player: " << myPlayer->getName() << "\t" << "Bids: " << this->getPlayerBid(myPlayer) << std::endl;
	}

	vector<Player*> maxBidders;
	auto maxBid = 0;

	for (auto& myPlayer : biddingPlayers)
	{
		const auto currentPlayerBid = this->getPlayerBid(myPlayer);
		if (maxBid <= currentPlayerBid) {
			// New max bid
			if (maxBid < currentPlayerBid)
			{
				maxBid = currentPlayerBid;
				maxBidders.clear(); // Clearing max bidders vector for new max bid
			}
			maxBidders.push_back(myPlayer);
		}
	}

	if (maxBidders.size() > 1)
	{
		if (maxBid == 0)
		{
			std::cout << "\nAll players bid 0." << std::endl;
		} else
		{
			std::cout << "\nThere is a tie for highest bidder at " << maxBid << "." << std::endl;
		}
		// Sorting max bidders by alphabetical last name order
		std::sort(maxBidders.begin(), maxBidders.end(), [](const auto lhs, const auto rhs)
		{
			auto lowerCaseLeft = lhs->getName();
			std::transform(lowerCaseLeft.begin(), lowerCaseLeft.end(), lowerCaseLeft.begin(), ::tolower);
			auto lowerCaseRight = rhs->getName();
			std::transform(lowerCaseRight.begin(), lowerCaseRight.end(), lowerCaseRight.begin(), ::tolower);
			return lowerCaseLeft.compare(lowerCaseRight) >= 0;
		});

		std::cout << "\nThe winner will be chosen by alphabetical last name order." << std::endl;
	}

	auto* maxBidder = maxBidders.front();
	
	const auto supply = maxBidder->getCoins() - maxBid;

	maxBidder->setCoins(supply);
	this->setCurrentBid(maxBid);
	std::cout << "\nThe player to start is " << maxBidder->getName() << "! They now have " << maxBidder->getCoins() << " coins.\n";
}