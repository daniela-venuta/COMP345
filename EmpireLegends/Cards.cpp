#include "Cards.h"

//======= DECK METHODS =======//
Deck::Deck()
{

}

Deck::~Deck()
{
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
Hand::Hand()
{

}

Hand::~Hand()
{
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

Card::~Card()
{
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

