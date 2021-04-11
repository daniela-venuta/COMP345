#pragma once
#include <list>
using std::list;

class Observer
{
public:
	~Observer();
	virtual void Update() = 0; // pure virtual function, all classes must override
protected:
	Observer();
};

class Subject
{
public:
	virtual void Attach(Observer* o); // push_back(o)
	virtual void Detach(Observer* o); // remove(o)
	virtual void Notify(); // calls update on list of all observer in a for loop
	Subject();
	~Subject();
private:
	list<Observer*>* _observers;
};
