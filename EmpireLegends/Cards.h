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
	~Card();

	// copy constructor
	Card(const Card& otherCard);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Card& card);
	friend ostream& operator>>(ostream& os, const Card& card);

	// assignment operator
	Card& operator = (const Card& card);

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
	~Deck();

	// copy constructor
	Deck(const Deck& otherDeck);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Deck& deck);
	friend ostream& operator>>(ostream& os, const Deck& deck);

	// assignment operator
	Deck& operator = (const Deck& deck);

	Card draw();
private:
	vector<Card> cardDeck;
};

class Hand {
public:
	Hand();
	~Hand();

	// copy constructor
	Hand(const Hand& otherHand);
	
	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Hand& hand);
	friend ostream& operator>>(ostream& os, const Hand& hand);

	//assignment operator
	Hand& operator = (const Hand& hand);
	
	void exchange();
private:
	vector<Card> handCards;
};

