#include "Cards.h"

//======= DECK METHODS =======//
Deck::Deck() {

}

//======= HAND METHODS =======//
Hand::Hand() {

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

string Card::getAction() const
{
	return action;
}

string Card::getGoods() const
{
	return goods;
}


