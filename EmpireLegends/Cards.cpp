#include "Cards.h"

//======= DECK METHODS =======//
Deck::Deck() {

}

//======= HAND METHODS =======//
Hand::Hand() {

}

//======= CARD METHODS =======//
Card::Card(string goodDesc, string actionDesc) {
	// initialize card
	goods = goodDesc;
	action = actionDesc;
}
