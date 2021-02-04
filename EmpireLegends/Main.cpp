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

	c1->addTerritory(t1);
	c1->addTerritory(t2);
	c1->addTerritory(t3);

	c1->addEdge("Region 1", "Region 2", 1);
	c1->addEdge("Region 1", "Region 3", 1);
	c1->addEdge("Region 2", "Region 3", 1);

	c2->addTerritory(t4);
	c2->addTerritory(t5);
	c2->addTerritory(t6);

	c2->addEdge("Region 4", "Region 5", 1);
	c2->addEdge("Region 5", "Region 6", 1);

	auto* m1 = new gameMap(new string("Map 1"));
	auto* t7 = new territory<continent>(c1);
	auto* t8 = new territory<continent>(c2);

	m1->addTerritory(t7);
	m1->addTerritory(t8);

	m1->addEdge("Continent 1", "Continent 2", 3);
	
	cout << m1->toString() << endl;
}

int main(int argc, const char* argv[]) {
	mapDriverStart();
}
