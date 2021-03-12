#pragma once

#include <string>
#include <vector>
#include <iostream>


using std::string;
using std::vector;
using std::ostream;

class Player;

class Card {
public:
	Card() = default;
	Card(const string nameStr, const string goodDesc, const string actionDesc);
	~Card() = default;

	// copy constructor
	Card(const Card& otherCard);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Card& card);
	friend ostream& operator>>(ostream& os, const Card& card);

	// assignment operator
	Card& operator = (const Card& card);

	// getters and setters
	string getName() const;
	string getGoods() const;
	string getAction() const;

private:
	string name;
	string goods;
	string action;
};

class Hand {
public:
	Hand() = default;
	~Hand();

	// copy constructor
	Hand(const Hand& otherHand);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Hand& hand);
	friend ostream& operator>>(ostream& os, const Hand& hand);

	//assignment operator
	Hand& operator = (const Hand& hand);

	Card* exchange(int rowPosition, Player* player);
	void addCard(Card* card);

private:
	static int getCardCost(int position);

	vector<Card*> handCards;
};


class Deck {
public:
	Deck() = default;
	Deck(const vector<Card*>& playingCards);
	~Deck();

	// copy constructor
	Deck(const Deck& otherDeck);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Deck& deck);
	friend ostream& operator>>(ostream& os, const Deck& deck);

	// assignment operator
	Deck& operator = (const Deck& deck);

	void draw(const int count);
	void shuffle();
	
	Hand* getHand() const;
private:
	vector<Card*> cardDeck;
	Hand* hand;
};


