#include "Cards.h"

#include <utility>
#include "Player.h"

#pragma region Deck
//======= DECK METHODS =======//
Deck::Deck(const vector<Card*>& playingCards)
{
	hand = new Hand();
	cardDeck = playingCards;
}

Deck::~Deck()
{
	delete hand;
	hand = nullptr;

	for (Card* card : cardDeck)
	{
		delete card;
		card = nullptr;;
	}

	cardDeck.clear();
}

Deck::Deck(const Deck& otherDeck)
{
	this->cardDeck = otherDeck.cardDeck;
	this->hand = new Hand(*(otherDeck.hand));
}

void Deck::draw(const int count)
{
	for (int i = 0; i < count; i++)
	{
		// get card to add to the hand
		Card* drawCard = cardDeck.at(cardDeck.size() - 1);

		// remove card from deck
		cardDeck.pop_back();

		// add card to card space (deck hand)
		hand->addCard(drawCard);
	}
}

void Deck::shuffle()
{
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
		s += "| " + card->getName() + " ";
	}

	s += "| ";

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
	for (Card* card : handCards)
	{
		delete card;
		card = nullptr;
	}
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

Card* Hand::exchange(int rowPosition, Player* player)
{
	const int cardCost = getCardCost(rowPosition);
	Card* exchangeCard = nullptr;

	if (player->getBalance() >= cardCost)
	{
		exchangeCard = handCards.at(rowPosition - 1);

		// remove card from Hand
		handCards.erase(handCards.begin() + rowPosition - 1);

		if (cardCost > 0)
		{
			player->payCoin(cardCost);
		}
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
	switch (position)
	{
	case 1:cardCost = 0; break;
	case 2:cardCost = 1; break;
	case 3:cardCost = 1; break;
	case 4:cardCost = 2; break;
	case 5:cardCost = 2; break;
	case 6:cardCost = 3; break;
	default: cardCost = -1;
	}

	return cardCost;
}

ostream& operator<<(ostream& os, const Hand& hand)
{
	string s = "The following cards remain in the hand: ";

	for (const Card* card : hand.handCards)
	{
		s += "| " + card->getName() + " ";
	}

	s += "| ";

	os << s << std::endl;

	return os;
}

vector<Card*> Hand::getHandCards() {
	return handCards;
}

#pragma endregion Hand

#pragma region Card
//======= CARD METHODS =======//

Card::Card(string nameStr, Good* good, string actionDesc)
{
	// initialize card
	this->name = std::move(nameStr);
	this->good = good;
	this->action = std::move(actionDesc);
	this->secondAction = "";
}

Card::Card(string nameStr, Good* good, string firstActionDesc, string secondActionDesc) 
{
	this->name = std::move(nameStr);
	this->good = good;
	this->action = std::move(firstActionDesc);
	this->secondAction = std::move(secondActionDesc);
}

Card::~Card()
{
	delete good;
	good = nullptr;
}

Card::Card(const Card& otherCard)
{
	this->name = otherCard.name;
	this->good = otherCard.good;
	this->action = otherCard.action;
	this->secondAction = otherCard.secondAction;
}

ostream& operator<<(ostream& os, const Card& card)
{
	os << "Card name: " << card.getName() << std::endl << *card.getGood() << std::endl;
	return os;
}

Card& Card::operator=(const Card& card)
{
	this->name = card.name;
	this->good = card.good;
	this->action = card.action;
	this->secondAction = card.secondAction;

	return *this;
}

string Card::getName() const
{
	return name;
}

string Card::getAction() const
{
	return action;
}

string Card::getSecondAction() const
{
	return secondAction;
}

Good* Card::getGood() const
{
	return good;
}

#pragma endregion Card

#pragma region Good

string Good::getName() const
{
	return name;
}

string Good::toString() const
{
	return "Good: " + this->getName();
}

void ExtraMove::applyGood(Resources* resources)
{
	resources->extraMoves++;
}

ExtraMove& ExtraMove::operator=(const ExtraMove& good)
{
	this->name = good.getName();
	return *this;
}

void ExtraArmy::applyGood(Resources* resources)
{
	resources->extraArmies++;
}

ExtraArmy& ExtraArmy::operator=(const ExtraArmy& good)
{
	this->name = good.getName();
	return *this;
}

void Flying::applyGood(Resources* resources)
{
	resources->flying++;
}

Flying& Flying::operator=(const Flying& good)
{
	this->name = good.getName();
	return *this;
}

Elixir::Elixir(int numElixirs) : Good("Elixir")
{
	elixirs = numElixirs;
}

void Elixir::applyGood(Resources* resources)
{
	resources->elixir += elixirs;
}

Elixir& Elixir::operator=(const Elixir& good)
{
	this->name = good.getName();
	return *this;
}

GainCoins::GainCoins(int nbCoins) : Good("Gain Coins")
{
	coins = nbCoins;
}

string GainCoins::toString() const
{
	return "Good: " + this->getName() + ", +" + std::to_string(this->coins);
}

void GainCoins::applyGood(Resources* resources)
{
	resources->totalCoins += coins;
}

GainCoins& GainCoins::operator=(const GainCoins& good)
{
	this->name = good.getName();
	this->coins = good.coins;
	return *this;
}

void Immune::applyGood(Resources* resources)
{
	resources->immune = true;
}

Immune& Immune::operator=(const Immune& good)
{
	this->name = good.getName();
	return *this;
}

SetNameVPs::SetNameVPs(CardSet set) : Good("+ 1 VP per " + CardSetMap::getString(set) + " card")
{
	this->set = set;
}

void SetNameVPs::applyGood(Resources* resources)
{
	resources->setNameVPs[this->set] = true;
}

SetNameVPs& SetNameVPs::operator=(const SetNameVPs& good)
{
	this->name = good.getName();
	this->set = good.set;
	return *this;
}

CompleteSetVPs::CompleteSetVPs(int setSize, CardSet set) : Good("All " + std::to_string(setSize) + " " + CardSetMap::getString(set) + " cards = 4 VP")
{
	this->setSize = setSize;
	this->set = set;
}

void CompleteSetVPs::applyGood(Resources* resources)
{
	resources->completeSetVPs[this->set] = true;
}

CompleteSetVPs& CompleteSetVPs::operator=(const CompleteSetVPs& good)
{
	this->name = good.getName();
	this->set = good.set;
	return *this;
}

void CoinVPs::applyGood(Resources* resources)
{
	resources->coinVPs++;
}

CoinVPs& CoinVPs::operator=(const CoinVPs& good)
{
	this->name = good.getName();
	return *this;
}

#pragma endregion Good

std::map<CardSet, string> CardSetMap::createMap()
{
	std::map<CardSet, string> map;
	map.operator[](CardSet::forest) = "Forest";
	map.operator[](CardSet::dire) = "Dire";
	map.operator[](CardSet::ancient) = "Ancient";
	map.operator[](CardSet::noble) = "Noble";
	map.operator[](CardSet::mountain) = "Mountain";
	map.operator[](CardSet::arcane) = "Arcane";
	map.operator[](CardSet::cursed) = "Cursed";
	return map;
}

// Initializing static map member for CardSetMap
map<CardSet, string> CardSetMap::map = createMap();