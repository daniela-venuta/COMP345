#pragma once
#include "Cards.h"
#include "Map.h"

class PlayerStrategy
{
public:
	virtual ~PlayerStrategy() = default;
	virtual Action* chooseAction(Action* action1, Action* action2) = 0;
	virtual void executeAction(Action* action, Player* player, GameMap* map) = 0;
};

class HumanStrategy: public PlayerStrategy
{
public:
	Action* chooseAction(Action* action1, Action* action2) override;
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

class GreedyStrategy : public PlayerStrategy
{
public:
	Action* chooseAction(Action* action1, Action* action2) override;
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

class ModerateStrategy : public PlayerStrategy
{
public:
	Action* chooseAction(Action* action1, Action* action2) override;
	void executeAction(Action* action, Player* player, GameMap* map) override;
};

