#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Card {
public:
	Card(const string goodDesc, const string actionDesc);
	Card(const Card& otherCard);
	~Card();

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

	void draw();
private:
	vector<Card> cardDeck;
};

class Hand {
public:
	Hand();
	Hand(const Hand& otherHand);
	~Hand();

	void exchange();
private:
	vector<Card> handCards;
};