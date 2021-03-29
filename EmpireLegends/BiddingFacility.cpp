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
	for (auto& player : biddingPlayers)
	{
		do {
			std::cout << "\n" << player->getName() << " place your bid: ";
			std::cin >> playerBid;
		} while (playerBid > player->getCoins() || playerBid < 0);

		system("cls");

		this->addPlayerBid(player, playerBid);
	}

	std::cout << "--------------------------" << std::endl;
	std::cout << "WHO WILL GO FIRST??:" << std::endl;
	std::cout << "--------------------------\n" << std::endl;

	std::cout << "Bids placed by players: " << std::endl;
	for (Player* myPlayer : biddingPlayers)
	{
		std::cout << "Player " << myPlayer->getName() << "\t" << "bids " << this->getPlayerBid(myPlayer) << " coins." << std::endl;
	}

	vector<Player*> maxBidders;
	int maxBid = 0;

	for (Player* player : biddingPlayers)
	{
		const int currentPlayerBid = this->getPlayerBid(player);
		if (maxBid <= currentPlayerBid) {
			// New max bid
			if (maxBid < currentPlayerBid)
			{
				maxBid = currentPlayerBid;
				maxBidders.clear(); // Clearing max bidders vector for new max bid
			}
			maxBidders.push_back(player);
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

		std::cout << "\nThe winner will be chosen by alphabetical last name order." << std::endl;

		std::sort(maxBidders.begin(), maxBidders.end(), [](const Player* player1, const Player* player2)
		{
			auto playerName1 = player1->getName();
			std::transform(playerName1.begin(), playerName1.end(), playerName1.begin(), ::tolower);

			auto playerName2 = player2->getName();
			std::transform(playerName2.begin(), playerName2.end(), playerName2.begin(), ::tolower);

			return playerName1.compare(playerName2) >= 0;
		});
	}

	Player* maxBidder = maxBidders.back();
	const int supply = maxBidder->getCoins() - maxBid;
	maxBidder->setCoins(supply);
	this->setCurrentBid(maxBid);

	std::cout << "\nThe player to start is " << maxBidder->getName() << "! They now have " << maxBidder->getCoins() << " coins.\n";
}
