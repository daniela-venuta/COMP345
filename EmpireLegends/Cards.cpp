#include "Cards.h"

//======= DECK METHODS =======//
Deck::Deck() {

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

//======= HAND METHODS =======//
Hand::Hand() {

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


//======= CARD METHODS =======//
Card::Card(const string goodDesc, const string actionDesc) {
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
	os << "";
	return os;
}

ostream& operator>>(ostream& os, const Card& card)
{
	os << "";
	return os;
}

string Card::getAction() const
{
	return action;
}

string Card::getGoods() const
{
	return goods;
}

