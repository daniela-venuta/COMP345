#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;


class Card {
public:
	Card(const string goodDesc,const string actionDesc);
	Card(const Card& otherCard);
	~Card();

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Card& card);
	friend ostream& operator>>(ostream& os, const Card& card);

	// getters and setters
	string getGoods() const;
	string getAction() const;

private:
	string goods;
	string action;
};

class Deck {
public:
	Deck();
	Deck(const Deck& otherDeck);
	~Deck();

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Deck& deck);
	friend ostream& operator>>(ostream& os, const Deck& deck);

	Card draw();
private:
	vector<Card> cardDeck;
};

class Hand {
public:
	Hand();
	Hand(const Hand& otherHand);
	~Hand();

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Hand& hand);
	friend ostream& operator>>(ostream& os, const Hand& hand);
	
	void exchange();
private:
	vector<Card> handCards;
};

