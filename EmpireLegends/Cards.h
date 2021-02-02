#pragma once

#include <string>
using std::string;

class Deck {
public:
	Deck();
	~Deck();

	void draw();
};

class Hand {
public:
	Hand();
	~Hand();

	void exchange();
private:
	Card *cards[13]; // max amount of cards a player can hold
};

class Card {
public:
	Card(string goodDesc, string actionDesc);
	~Card();

	//TODO: copyConstructor

	// getters and setters
	string getGoods();
	string getAction();

private:
	string goods;
	string action;
};