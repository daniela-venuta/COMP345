//#include "MapLoader.h"
//#include <iostream>
//
//int main()
//{
//	auto* mapLoader = new MapLoader();
//
//	std::cout << "Loading valid_map_1.json: ";
//	
//	auto* validMap1 = mapLoader->load("valid_map_1.json");
//
//	std::cout << *validMap1 << std::endl;
//
//	std::cout << "Loading valid_map_2.json: ";
//
//	auto* validMap2 = mapLoader->load("valid_map_2.json");
//
//	std::cout << *validMap2 << std::endl;
//
//	try
//	{
//		std::cout << "Loading invalid_map_disconnected.json: ";
//		mapLoader->load("invalid_map_disconnected.json");
//	} catch (MapException& e)
//	{
//		std::cout << e << std::endl;
//	}
//
//	try
//	{
//		std::cout << "Loading invalid_map_missing_name_field.json: ";
//		mapLoader->load("invalid_map_missing_name_field.json");
//	} catch (InvalidMapFileException& e)
//	{
//		std::cout << e << std::endl;
//	}
//
//	try
//	{
//		std::cout << "Loading invalid_map_missing_edges_field.json: ";
//		mapLoader->load("invalid_map_missing_edges_field.json");
//	}
//	catch (InvalidMapFileException& e)
//	{
//		std::cout << e << std::endl;
//	}
//
//	delete validMap1;
//	delete validMap2;
//	delete mapLoader;
//    return 0;
//}
