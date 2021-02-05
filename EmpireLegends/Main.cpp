#include <iostream>
#include "Map.h"

void mapDriverStart() {
	auto* c1 = new continent(new string("Continent 1"));
	auto* t1 = new territory<region>(new region(new string("Region 1")));
	auto* t2 = new territory<region>(new region(new string("Region 2")));
	auto* t3 = new territory<region>(new region(new string("Region 3")));
	auto* c2 = new continent(new string("Continent 2"));
	auto* t4 = new territory<region>(new region(new string("Region 4")));
	auto* t5 = new territory<region>(new region(new string("Region 5")));
	auto* t6 = new territory<region>(new region(new string("Region 6")));
	auto* c3 = new continent(new string("Continent 3"));

	c1->add_territory(t1);
	c1->add_territory(t2);
	c1->add_territory(t3);
	c1->add_territory(t3);
	c1->add_edge("Region 1", "Region 2", 1);
	c1->add_edge("Region 1", "Region 3", 1);
	c1->add_edge("Region 2", "Region 3", 1);

	c2->add_territory(t4);
	c2->add_territory(t5);
	c2->add_territory(t6);
	c2->add_edge("Region 4", "Region 5", 1);
	c2->add_edge("Region 5", "Region 6", 1);

	//Adding t3 so that it's duplicated in m2
	c3->add_territory(t3);
	c3->add_territory(t4);
	c3->add_territory(t5);
	c3->add_territory(t6);
	c3->add_edge("Region 4", "Region 5", 1);
	c3->add_edge("Region 5", "Region 6", 1);

	auto* m1 = new gameMap(new string("Map 1"));
	auto* m2 = new gameMap(new string("Map 2"));
	auto* t7 = new territory<continent>(c1);
	auto* t8 = new territory<continent>(c2);
	auto* t9 = new territory<continent>(c3);

	m1->add_territory(t7);
	m1->add_territory(t8);
	m1->add_edge("Continent 1", "Continent 2", 3);

	m2->add_territory(t7);
	m2->add_territory(t9);
	m2->add_edge("Continent 1", "Continent 3", 3);
	
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << m1->to_string() << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << m2->to_string() << endl;
	cout << "----------------------------------------------------------------------------------" << endl;

	try
	{
		//m1 should validate
		m1->validate();
		m2->validate();
	} catch (invalidMapException& e)
	{
		//m2 should not validate
		cout << e.what() << endl;
	}
	try
	{
		c1->find_territory("test_test");
	}
	catch (territoryNotFoundException& e)
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
