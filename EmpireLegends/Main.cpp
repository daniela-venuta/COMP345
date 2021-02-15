#include <iostream>
#include "Map.h"

void mapDriverStart() {
	auto* c1 = new Continent(new string("Continent 1"));
	auto* t1 = new Territory<Region>(new Region(new string("Region 1")));
	auto* t2 = new Territory<Region>(new Region(new string("Region 2")));
	auto* t3 = new Territory<Region>(new Region(new string("Region 3")));
	auto* c2 = new Continent(new string("Continent 2"));
	auto* t4 = new Territory<Region>(new Region(new string("Region 4")));
	auto* t5 = new Territory<Region>(new Region(new string("Region 5")));
	auto* t6 = new Territory<Region>(new Region(new string("Region 6")));
	auto* c3 = new Continent(new string("Continent 3"));

	c1->addTerritory(t1);
	c1->addTerritory(t2);
	c1->addTerritory(t3);
	c1->addTerritory(t3);
	c1->addEdge("Region 1", "Region 2", 1);
	c1->addEdge("Region 1", "Region 3", 1);
	c1->addEdge("Region 2", "Region 3", 1);

	c2->addTerritory(t4);
	c2->addTerritory(t5);
	c2->addTerritory(t6);
	c2->addEdge("Region 4", "Region 5", 1);
	c2->addEdge("Region 5", "Region 6", 1);

	//Adding t3 so that it's duplicated in m2
	c3->addTerritory(t3);
	c3->addTerritory(t4);
	c3->addTerritory(t5);
	c3->addTerritory(t6);
	c3->addEdge("Region 4", "Region 5", 1);
	c3->addEdge("Region 5", "Region 6", 1);

	auto* m1 = new GameMap(new string("Map 1"));
	auto* m2 = new GameMap(new string("Map 2"));
	auto* t7 = new Territory<Continent>(c1);
	auto* t8 = new Territory<Continent>(c2);
	auto* t9 = new Territory<Continent>(c3);

	m1->addTerritory(t7);
	m1->addTerritory(t8);
	m1->addEdge("Continent 1", "Continent 2", 3);

	m2->addTerritory(t7);
	m2->addTerritory(t9);
	m2->addEdge("Continent 1", "Continent 3", 3);
	
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << m1->toString() << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << m2->toString() << endl;
	cout << "----------------------------------------------------------------------------------" << endl;

	try
	{
		//m1 should validate
		m1->validate();
		m2->validate();
	} catch (InvalidMapException& e)
	{
		//m2 should not validate
		cout << e.what() << endl;
	}
	try
	{
		c1->findTerritory("test_test");
	}
	catch (TerritoryNotFoundException& e)
	{
		//Should not find territory with incorrect name
		cout << e.what() << endl;
	}

	delete m1;
	delete m2;
}

int main(int argc, const char* argv[]) {
	mapDriverStart();
}
