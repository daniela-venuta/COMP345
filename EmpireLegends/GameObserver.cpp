#include "GameObserver.h"

#pragma region Observer
Observer::~Observer()
{
	//empty
}

Observer::Observer()
{
	//empty
}
#pragma endregion

#pragma region Subject
void Observable::Attach(Observer* o)
{
	_observers->push_back(o);
}

void Observable::Detach(Observer* o)
{
	_observers->remove(o);
}

void Observable::Notify()
{
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); i++)
	{
		(*i)->Update();
	}
}

Observable::Observable()
{
	_observers = new list<Observer*>;
}

Observable::~Observable()
{
	delete _observers;
}
#pragma endregion