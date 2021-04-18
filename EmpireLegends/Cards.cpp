#include "Cards.h"
#include <stdlib.h>
#include <time.h> 

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
		card = nullptr;
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
		if (cardDeck.empty()) {
			std::cout << "The deck is empty so no draw can be made" << std::endl;
			return;
		}
		// get card to add to the hand
		Card* drawCard = cardDeck.at(cardDeck.size() - 1);

		// remove card from deck
		cardDeck.pop_back();

		// add card to card space (deck hand)
		hand->addCard(drawCard);
	}
}

bool Deck::shuffle()
{
	bool success = false;
	if (!this->isEmpty())
	{
		std::srand(time(0));

		int numCards = cardDeck.capacity();
		for (int i = 0; i < numCards; i++)
		{
			int rand = i + (std::rand() % (numCards)-i);
			this->swap(rand, i);
		}

		success = true;
	}

	return success;
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

void Deck::swap(int indexOne, int indexTwo)
{
	Card* temp = cardDeck[indexOne];
	cardDeck[indexOne] = cardDeck[indexTwo];
	cardDeck[indexTwo] = temp;
}

bool Deck::isEmpty() const
{
	return (cardDeck.capacity() > 0) ? false : true;
}
#pragma endregion Deck

#pragma region Hand
Action::Action(string name, int multiplier)
{
	this->name = name;
	this->multiplier = multiplier;
}

Action::Action(const Action& action)
{
	this->name = action.getName();
	this->multiplier = action.getMultiplier();
}

Action& Action::operator=(const Action& action)
{
	this->name = action.getName();
	this->multiplier = action.getMultiplier();

	return *this;
}

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
	int nonBot = player->getName().find("Bot");

	if (handCards.empty()) {
		std::cout << "The hand is empty" << std::endl;
	}
	else if (rowPosition > handCards.size()) {
		std::cout << "Invalid card position" << std::endl;
	}
	else if (player->getBalance() >= cardCost)
	{
		exchangeCard = handCards.at(rowPosition - 1);

		// remove card from Hand
		handCards.erase(handCards.begin() + rowPosition - 1);

		if (cardCost > -1)
		{
			player->payCoin(cardCost);
		}
	}
	//Only printing for human players
	else if (nonBot == std::string::npos)
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

ostream& operator<<(ostream& os, const Action& action)
{
	string s;
	s += "Action: " + action.name;

	if (action.multiplier > 0)
	{
		s += " (" + std::to_string(action.multiplier) + ")";
	}
	return os << s;
}

vector<Card*> Hand::getCards()
{
	return handCards;
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
#pragma endregion Hand

#pragma region Card
//======= CARD METHODS =======//

Card::Card(string name, Good* good, Action* action)
{
	// initialize card
	this->name = std::move(name);
	this->good = good;
	this->action = action;
	this->secondAction = nullptr;
	this->andOr = AndOr::SINGLE;
}

Card::Card(string name, Good* good, Action* firstAction, Action* secondAction, AndOr andOr)
{
	this->name = std::move(name);
	this->good = good;
	this->action = firstAction;
	this->secondAction = secondAction;
	this->andOr = andOr;
}

Card::~Card()
{
	delete good;
	delete action;
	delete secondAction;
	good = nullptr;
	action = nullptr;
	secondAction = nullptr;
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
	os << "Card name: " << card.getName() << std::endl << *card.getGood() << std::endl << *card.getAction() << std::endl;
	if (card.getSecondAction() != nullptr)
	{
		if (card.getAndOr() == AndOr::OR)
		{
			os << "or" << std::endl;
		}
		else if (card.getAndOr() == AndOr::AND)
		{
			os << "and" << std::endl;
		}
		os << *card.getSecondAction() << std::endl;
	}
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

Action* Card::getAction() const
{
	return action;
}

Action* Card::getSecondAction() const
{
	return secondAction;
}

AndOr Card::getAndOr() const
{
	return andOr;
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
	resources->coinVPs = true;
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
	map.operator[](CardSet::night) = "Night";
	return map;
}

// Initializing static map member for CardSetMap
map<CardSet, string> CardSetMap::map = createMap();