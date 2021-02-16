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

void Deck::draw(int count)
{
	for(int i=0; i< count; i++)
	{
		// get card to add to the hand
		Card* drawCard = cardDeck.at(cardDeck.size() - 1);

		// remove card from deck
		cardDeck.pop_back();

		// add card to card space (deck hand)
		hand->addCard(drawCard);
	}
}

const Hand* Deck::getHand() const
{
	return hand;
}

ostream& operator<<(ostream& os, const Deck& deck)
{
	string s = "The following cards remain in the deck: ";

	for (const Card* card : deck.cardDeck)
	{
		s += card->getGoods() + " ";
	}
	os << s << std::endl;

	return os;
}

ostream& operator>>(ostream& os, const Deck& deck)
{
	string s = "The following cards remain in the deck: ";

	for (const Card* card : deck.cardDeck)
	{
		s += card->getGoods() + " ";
	}
	os << s << std::endl;
	
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

//Hand& Hand::operator=(const Hand& hand)
//{
//}

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
	string s = "The following cards remain in the hand: ";;

	for(const Card* card : hand.handCards)
	{
		s += card->getGoods() +" ";
	}
	os << s << std::endl;
	
	return os;
}

ostream& operator>>(ostream& os, const Hand& hand)
{
	string s = "The following cards remain in the hand: ";;

	for (const Card* card : hand.handCards)
	{
		s += card->getGoods() + " ";
	}
	os << s << std::endl;
	return os;
}


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
	os << "Card action: " << card.getAction() << ", Card good: " << card.getGoods() << std::endl;
	return os;
}

ostream& operator>>(ostream& os, const Card& card)
{
	os << "Card action: " << card.getAction() << ", Card good: " << card.getGoods() << std::endl;
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

