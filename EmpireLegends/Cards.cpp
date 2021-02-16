#include "Cards.h"

//======= DECK METHODS =======//
Deck::Deck(const vector<Card*> playingCards)
{
	hand = new Hand();
	cardDeck = playingCards;
}

Deck::~Deck()
{
	hand = nullptr;
	cardDeck.clear();
}

void Deck::draw()
{
	const int last = cardDeck.size();
	Card* drawCard = cardDeck.at(last-1);

	// add card to card space (deck hand)
	hand->addCard(drawCard);
}

ostream& operator<<(ostream& os, const Deck& deck)
{
	os << "";
	return os;
}

ostream& operator>>(ostream& os, const Deck& deck)
{
	os << "";
	return os;
}

//Deck& Deck::operator=(const Deck& deck)
//{
//}

//======= HAND METHODS =======//
Hand::~Hand()
{
	handCards.clear();
}

Hand& Hand::operator=(const Hand& hand)
{
}

Card* Hand::exchange(int rowPosition, int cost)
{
	Card* exchangeCard = handCards.at(rowPosition - 1);

	// remove card from Hand
	handCards.erase(handCards.begin() + rowPosition);

	return exchangeCard;
}

void Hand::addCard(Card* card)
{
	// add card to hand
	handCards.push_back(card);
}

ostream& operator<<(ostream& os, const Hand& hand)
{
	os << "";
	return os;
}

ostream& operator>>(ostream& os, const Hand& hand)
{
	os << "";
	return os;
}


//Hand& Hand::operator=(const Hand& hand)
//{
//}

//======= CARD METHODS =======//
Card::Card(const string goodDesc, const string actionDesc)
{
	// initialize card
	goods = goodDesc;
	action = actionDesc;
}

Card::Card(const Card& otherCard)
{
	goods = otherCard.goods;
	action = otherCard.action;
}

ostream& operator<<(ostream& os, const Card& card)
{
	os << "this is a card";
	return os;
}

ostream& operator>>(ostream& os, const Card& card)
{
	os << "this is a card";
	return os;
}

//Card& Card::operator=(const Card& card)
//{
//}

string Card::getAction() const
{
	return action;
}

string Card::getGoods() const
{
	return goods;
}

