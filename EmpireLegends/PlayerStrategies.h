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
	/// Choosing a card.
	/// </summary>
	/// <param name="hand">Hand to pick a card from</param>
	/// <param name="player">Player making the choice</param>
	/// /// <returns>Chosen action</returns>
	virtual Card* chooseCard(Hand* hand, Player* player) = 0;
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
	virtual bool executeAction(Action* action, Player* player, GameMap* map) = 0;

	friend ostream& operator<<(ostream& os, const PlayerStrategy& strategy);
};

// Human strategy. Choice and execution are dictated by user input.
class HumanStrategy: public PlayerStrategy
{
private:
	int pickCardPosition();
public:
	HumanStrategy() : PlayerStrategy("human") {}
	Card* chooseCard(Hand* hand, Player* player) override;
	Action* chooseAction(Action* action1, Action* action2) override;
	bool executeAction(Action* action, Player* player, GameMap* map) override;
};

// Non human strategy. Execution is the same for Greedy and Moderate, but the choice method changes.
class NonHumanStrategy : public PlayerStrategy
{
private:
	vector<string> wantedActions;
	static Territory<Region>* getRandomTerritory(std::map<int, Territory<Region>*> territories);
protected:
	NonHumanStrategy(const string& stratName, vector<string> actions) : PlayerStrategy("non human: " + stratName), wantedActions(actions) { }
public:
	Card* chooseCard(Hand* hand, Player* player) override;
	bool executeAction(Action* action, Player* player, GameMap* map) override;
};

// Prioritizes building cities and destroying armies
class GreedyStrategy : public NonHumanStrategy
{
public:
	GreedyStrategy() : NonHumanStrategy("greedy", { "Build", "Destroy" }) {}
	Action* chooseAction(Action* action1, Action* action2) override;
};

// Prioritizes placing new armies on the board
class ModerateStrategy : public NonHumanStrategy
{
public:
	ModerateStrategy() : NonHumanStrategy("moderate", { "Place" }) {}
	Action* chooseAction(Action* action1, Action* action2) override;
};

