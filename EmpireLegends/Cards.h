#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

class Action;
using std::string;
using std::vector;
using std::map;
using std::ostream;

class Player;
struct Resources;

enum class CardSet
{
	forest,
	dire,
	ancient,
	noble,
	mountain,
	arcane,
	cursed,
	night
};

// String switch paridgam   
class CardSetMap
{
	static map<CardSet, string> map;

	CardSetMap() = default;

public:
	static std::map<CardSet, string> createMap();
	static string getString(CardSet set) { return map[set]; }
};

class Good
{
public:
	string getName() const;

	// Pure virtual method to apply good
	virtual void applyGood(Resources* resources) = 0;
	virtual ~Good() = default;

	friend ostream& operator<<(ostream& os, const Good& good) { return os << good.toString(); }

protected:

	explicit Good(string name) : name(std::move(name)) {}

	string name;

	virtual string toString() const;
};

class ExtraMove : public Good
{
public:

	explicit ExtraMove() : Good("+1 Move") {}

	void applyGood(Resources* resources) override;

	ExtraMove& operator=(const ExtraMove& good);
};

class ExtraArmy : public Good
{
public:

	explicit ExtraArmy() : Good("+1 Army") {}

	void applyGood(Resources* resources) override;

	ExtraArmy& operator=(const ExtraArmy& good);
};

class Flying : public Good
{
public:

	explicit Flying() : Good("Flying") {}

	void applyGood(Resources* resources) override;

	Flying& operator=(const Flying& good);
};

class Elixir : public Good
{
public:

	explicit Elixir(int num);

	void applyGood(Resources* resources) override;

	Elixir& operator=(const Elixir& good);
private:
	int elixirs;
};

class GainCoins : public Good
{
public:

	explicit GainCoins(int nbCoins);

	void applyGood(Resources* resources) override;

	string toString() const override;

	GainCoins& operator=(const GainCoins& good);

private:
	int coins;
};

class Immune : public Good
{
public:

	explicit Immune() : Good("Immune to Attack") {}

	void applyGood(Resources* resources) override;

	Immune& operator=(const Immune& good);
};

class CoinVPs : public Good
{
public:

	explicit CoinVPs() : Good("+1 VP per 3 coins") {}

	void applyGood(Resources* resources) override;

	CoinVPs& operator=(const CoinVPs& good);
};

class SetNameVPs : public Good
{
public:

	explicit SetNameVPs(CardSet set);

	void applyGood(Resources* resources) override;

	SetNameVPs& operator=(const SetNameVPs& good);

private:
	CardSet set;
};

class CompleteSetVPs : public Good
{
public:

	explicit CompleteSetVPs(int setSize, CardSet set);

	void applyGood(Resources* resources) override;

	CompleteSetVPs& operator=(const CompleteSetVPs& good);

private:
	CardSet set;
	string setSize;
};

enum class AndOr
{
	AND,
	OR,
	SINGLE
};

class Card
{
public:
	Card() = default;
	Card(string name, Good* good, Action* actionDesc);
	Card(string name, Good* good, Action* firstAction, Action* secondAction, AndOr andOr);
	~Card();

	// copy constructor
	Card(const Card& otherCard);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Card& card);

	// assignment operator
	Card& operator=(const Card& card);

	// getters and setters
	string getName() const;
	Good* getGood() const;
	Action* getAction() const;
	Action* getSecondAction() const;
	AndOr getAndOr() const;

private:
	string name;
	Good* good = nullptr;
	Action* action = nullptr;
	Action* secondAction = nullptr;
	AndOr andOr;
};

class Action
{
	string name;
	int multiplier;

public:

	explicit Action(string name, int multiplier = 0);
	~Action() = default;
	// copy constructor
	Action(const Action& action);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Action& action);
	// assignment operator
	Action& operator=(const Action& action);

	string getName() const { return name; }
	int getMultiplier() const { return multiplier; }
};

class Hand
{
public:
	Hand() = default;
	~Hand();

	// copy constructor
	Hand(const Hand& otherHand);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Hand& hand);

	//assignment operator
	Hand& operator = (const Hand& hand);

	Card* exchange(int rowPosition, Player* player);
	void addCard(Card* card);
	static int getCardCost(int position);

	vector<Card*> getCards();

private:

	vector<Card*> handCards;
};


class Deck
{
public:
	Deck() = default;
	Deck(const vector<Card*>& playingCards);
	~Deck();

	// copy constructor
	Deck(const Deck& otherDeck);

	// stream insertion operator overload
	friend ostream& operator<<(ostream& os, const Deck& deck);

	// assignment operator
	Deck& operator = (const Deck& deck);

	void draw(const int count);
	bool shuffle();

	Hand* getHand() const;

private:
	vector<Card*> cardDeck;
	Hand* hand;

	void swap(int indexOne, int indexTwo);
	bool isEmpty() const;
};

struct CardCost
{
	vector<int> cardCost = {};
};