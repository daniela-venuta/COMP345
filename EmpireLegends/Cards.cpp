#include "Cards.h"

#pragma region Deck
//======= DECK METHODS =======//
Deck::Deck(const vector<Card*>& playingCards)
{
	hand = new Hand();
	cardDeck = playingCards;
}

Deck::~Deck()
{
	hand = nullptr;
	cardDeck.clear();
}

Deck::Deck(const Deck& otherDeck)
{
	this->cardDeck = otherDeck.cardDeck;
	this->hand = new Hand(*(otherDeck.hand));
}

void Deck::draw(const int count)
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

Hand* Deck::getHand() const
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

Deck& Deck::operator=(const Deck& deck)
{
	this->cardDeck = deck.cardDeck;
	this->hand = new Hand(*(deck.hand));
	return *this;
}
#pragma endregion Deck

#pragma region Hand
//======= HAND METHODS =======//
Hand::~Hand()
{
	// clear the vector
	handCards.clear();
}

Hand::Hand(const Hand& otherHand)
{
	this->handCards = otherHand.handCards;
}

Hand& Hand::operator=(const Hand& hand)
{
	this->handCards = hand.handCards;
	return *this;
}

Card* Hand::exchange(int rowPosition, int cost)
{
	const int cardCost = getCardCost(rowPosition);
	Card* exchangeCard = nullptr;

	if(cost == cardCost)
	{
		exchangeCard = handCards.at(rowPosition - 1);

		// remove card from Hand
		handCards.erase(handCards.begin() + rowPosition);
	}
	else
	{
		std::cout << "Incorrect amount of coins entered. Operation failed" << std::endl;
	}
	
	return exchangeCard;
}

void Hand::addCard(Card* card)
{
	// add card to hand
	handCards.push_back(card);
}

int Hand::getCardCost(int position)
{
	int cardCost;
	switch(position)
	{
	case 1:cardCost = 0; break;
	case 2: 
	case 3:cardCost = 1; break;
	case 4:
	case 5:cardCost = 2; break;
	case 6:cardCost = 3; break;
	default: cardCost = 0;
	}

	return cardCost;
}

ostream& operator<<(ostream& os, const Hand& hand)
{
	string s = "The following cards remain in the hand: ";

	for(const Card* card : hand.handCards)
	{
		s += card->getGoods() +" ";
	}
	os << s << std::endl;
	
	return os;
}

ostream& operator>>(ostream& os, const Hand& hand)
{
	string s = "The following cards remain in the hand: ";

	for (const Card* card : hand.handCards)
	{
		s += card->getGoods() + " ";
	}
	os << s << std::endl;
	return os;
}
#pragma endregion Hand

#pragma region Card
//======= CARD METHODS =======//

Card::Card(const string goodDesc, const string actionDesc)
{
	// initialize card
	goods = goodDesc;
	action = actionDesc;
}

Card::Card(const Card& otherCard)
{
	this->goods = otherCard.goods;
	this->action = otherCard.action;
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

Card& Card::operator=(const Card& card)
{
	this->goods = card.goods;
	this->action = card.action;
	return *this;
}

string Card::getAction() const
{
	return action;
}

string Card::getGoods() const
{
	return goods;
}

#pragma endregion Card

