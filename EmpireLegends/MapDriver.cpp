//#include <iostream>
//#include "Map.h"
//
//int main() {
//	auto* c1 = new Continent("Continent 1");
//	auto* t1 = new Territory<Region>(new Region("Region 1"));
//	auto* t2 = new Territory<Region>(new Region("Region 2"));
//	auto* t3 = new Territory<Region>(new Region("Region 3"));
//	auto* c2 = new Continent("Continent 2");
//	auto* t4 = new Territory<Region>(new Region("Region 4"));
//	auto* t5 = new Territory<Region>(new Region("Region 5"));
//	auto* t6 = new Territory<Region>(new Region("Region 6"));
//	auto* t7 = new Territory<Region>(new Region("Region 7"));
//	auto* t8 = new Territory<Region>(new Region("Region 8"));
//	auto* c3 = new Continent("Continent 3");
//
//	c1->addTerritory(t1);
//	c1->addTerritory(t2);
//	c1->addTerritory(t3);
//	try
//	{
//		c1->addTerritory(t3);
//	} catch (TerritoryInGraphException& e)
//	{
//		// Should not be able to add t3 twice
//		std::cout << e << std::endl;
//	}
//	c1->addEdge("Region 1", "Region 2", 1);
//	c1->addEdge("Region 1", "Region 3", 1);
//	c1->addEdge("Region 2", "Region 3", 1);
//	try
//	{
//		c1->addEdge("Region 1", "Region 2", 1);
//	}
//	catch (EdgeInGraphException& e)
//	{
//		//Should not add already existing edge
//		std::cout << e << std::endl;
//	}
//	c2->addTerritory(t4);
//	c2->addTerritory(t5);
//	c2->addTerritory(t6);
//	c2->addTerritory(t7);
//	c2->addTerritory(t8);
//	c2->addEdge("Region 4", "Region 5", 1);
//	c2->addEdge("Region 5", "Region 6", 1);
//	c2->addEdge("Region 6", "Region 7", 1);
//	c2->addEdge("Region 7", "Region 8", 1);
//
//	//Adding t3 so that it's duplicated in m2
//	c3->addTerritory(new Territory<Region>(*t3));
//	c3->addTerritory(new Territory<Region>(*t4));
//	c3->addTerritory(new Territory<Region>(*t5));
//	c3->addTerritory(new Territory<Region>(*t6));
//
//	auto* m1 = new GameMap("Map 1");
//	auto* m2 = new GameMap("Map 2");
//	auto* t9 = new Territory<Continent>(c1);
//	auto* t10 = new Territory<Continent>(c2);
//	auto* t11 = new Territory<Continent>(c3);
//
//	m1->addTerritory(t9);
//	m1->addTerritory(t10);
//	m1->addEdge("Continent 1", "Continent 2", 3);
//
//	Territory<Continent>* t9Copy = new Territory<Continent>(*t9);
//	m2->addTerritory(t9Copy);
//	m2->addTerritory(t11);
//	m2->addEdge("Continent 1", "Continent 3", 3);
//	
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << "\nTravel cost (1->2): " << m1->getTravelCost(t1, t3) << std::endl; // Should be 1
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << "\nTravel cost (2->6): " << m1->getTravelCost(t2, t6) << std::endl; // Should be 6
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << "\nTravel cost (2->7): " << m1->getTravelCost(t2, t7) << std::endl; // Should be 5
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << "\nTravel cost (3->4): " << m1->getTravelCost(t3, t4) << std::endl; // Should be 3
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << *m1 << std::endl; //Testing map stream operator overload
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << *c1 << std::endl; //Testing continent stream operator overload
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	std::cout << *t1 << std::endl; //Testing territory stream operator overload
//	std::cout << "----------------------------------------------------------------------------------" << std::endl;
//	GameMap copiedM1 = *m1; //Testing map copy constructor (which uses all other copy constructors)
//	std::cout << "\nPrinting copied map:" << std::endl;
//	std::cout << copiedM1 << std::endl;
//
//	try
//	{
//		//m1 should validate
//		m1->validate();
//		m2->validate();
//	}
//	catch (InvalidMapException& e)
//	{
//		//m2 should not validate
//		std::cout << e << std::endl;
//	}
//	c1->addTerritory(new Territory<Region>(new Region("Extra Region")));
//	try
//	{
//		m1->validate();
//	}
//	catch (InvalidMapException& e)
//	{
//		//m1 should have an unconnected region
//		std::cout << e << std::endl;
//	}
//	copiedM1.addTerritory(new Territory<Continent>(new Continent("Extra Continent")));
//	try
//	{
//		c1->findTerritory("test_test");
//	}
//	catch (TerritoryNotFoundException& e)
//	{
//		//Should not find territory with incorrect name
//		std::cout << e << std::endl;
//	}
//
//	delete m1;
//	delete m2;
//	return 0;
//}
