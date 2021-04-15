#pragma once
#include <map>
#include <string>
#include "BiddingFacility.h"

struct Region;
class GameMap;
class Player;
class Action;

using std::string;
using std::ostream;
using std::map;

// Player trategy interface
class PlayerStrategy
{
protected:
	string name;

	PlayerStrategy(string stratName) : name(std::move(stratName)) {}
public:
	virtual ~PlayerStrategy() = default;
	/// <summary>
	/// Choosing between 2 actions to play.
	/// </summary>
	/// <param name="action1"></param>
	/// <param name="action2"></param>
	/// <returns>Chosen action</returns>
	virtual Action* chooseAction(Action* action1, Action* action2) = 0;
	/// <summary>
	/// Execution of an action.
	/// </summary>
	/// <param name="action"></param>
	/// <param name="player"></param>
	/// <param name="map"></param>
	virtual void executeAction(Action* action, Player* player, GameMap* map) = 0;

	friend ostream& operator<<(ostream& os, const PlayerStrategy& strategy);
};

// Human strategy. Choice and execution are dictated by user input.
class HumanStrategy: public PlayerStrategy
{
public:
	HumanStrategy() : PlayerStrategy("human") {}
	Action* chooseAction(Action* action1, Action* action2) override;
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

// Non human strategy. Execution is the same for Greedy and Moderate, but the choice method changes.
class NonHumanStrategy : public PlayerStrategy
{
	static Territory<Region>* getRandomTerritory(std::map<int, Territory<Region>*> territories);
protected:
	NonHumanStrategy(const string& stratName) : PlayerStrategy("non human: " + stratName) {}
public:
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

class GreedyStrategy : public NonHumanStrategy
{
public:
	GreedyStrategy() : NonHumanStrategy("greedy") {}
	Action* chooseAction(Action* action1, Action* action2) override;
};

class ModerateStrategy : public NonHumanStrategy
{
public:
	ModerateStrategy() : NonHumanStrategy("moderate") {}
	Action* chooseAction(Action* action1, Action* action2) override;
};

