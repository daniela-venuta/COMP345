#pragma once
#include "Cards.h"
#include "Map.h"

// Player trategy interface
class PlayerStrategy
{
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
};

// Human strategy. Choice and execution are dictated by user input.
class HumanStrategy: public PlayerStrategy
{
public:
	Action* chooseAction(Action* action1, Action* action2) override;
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

// Non human strategy. Execution is the same for Greedy and Moderate, but the choice method changes.
class NonHumanStrategy : public PlayerStrategy
{
public:
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

class GreedyStrategy : public NonHumanStrategy
{
public:
	Action* chooseAction(Action* action1, Action* action2) override;
};

class ModerateStrategy : public NonHumanStrategy
{
public:
	Action* chooseAction(Action* action1, Action* action2) override;
};

