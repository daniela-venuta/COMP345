#include "MapLoader.h"
#include <fstream>

InvalidMapFileException::InvalidMapFileException(const std::string& reason)
	: MapException(std::string("Invalid map file: " + reason + "\n"))
{}

FileFieldException::FileFieldException(const std::string& field, const std::string& reason)
	: InvalidMapFileException(std::string("Field '" + field + "' " + reason))
{}

GameMap* MapLoader::load(const std::string& fileName) const
{
	GameMap* map = nullptr;

	Json::Value root;
	Json::CharReaderBuilder builder;

	std::ifstream file(fileName, std::ifstream::binary);

	std::string errs;
	
	if (!Json::parseFromStream(builder, file, &root, &errs))
	{
		std::cout << errs << "\n";
	}

	try
	{
		auto mapName = root["name"].asString();

		if (mapName.empty())
		{
			throw FileFieldException("map.name", "is missing");
		}
		
		map = new GameMap(mapName);

		auto continentsNode = root["continents"];

		if (continentsNode.empty())
		{
			throw FileFieldException("map.continents", "is missing  or empty");
		}

		for (const auto& continentNode : continentsNode)
		{
			auto* territory = new Territory<Continent>(this->loadContinent(continentNode));

			try
			{
				map->addTerritory(territory);
			}
			catch (TerritoryInGraphException&)
			{
				delete territory;
				throw;
			}
		}

		loadEdgesMap(map, root, 3);

		map->validate();
	} catch (Json::Exception& e)
	{
		delete map;
		std::cout << e.what() << std::endl;
	} catch (std::exception&)
	{
		delete map;
		throw;
	}

	return map;
}

Continent* MapLoader::loadContinent(const Json::Value& continentNode)
{
	auto continentName = continentNode["name"].asString();

	if (continentName.empty())
	{
		throw FileFieldException("continent.name", "is missing");
	}

	auto regionsNode = continentNode["regions"];

	if (regionsNode.empty())
	{
		throw FileFieldException("continent.regions", "is missing or empty");
	}

	auto* continent = new Continent(continentName);
	
	for (const auto& regionNode : regionsNode)
	{
		auto* territory = new Territory<Region>(loadRegion(regionNode));
		try
		{
			continent->addTerritory(territory);
		} catch (MapException&)
		{
			delete continent;
			delete territory;
			throw;
		}
	}

	try
	{
		loadEdgesContinent(continent, continentNode, 1);
	} catch (MapException&)
	{
		delete continent;
		throw;
	}

	return continent;
}

Region* MapLoader::loadRegion(const Json::Value& regionNode)
{
	auto regionName = regionNode["name"].asString();
	
	if (regionName.empty())
	{
		throw FileFieldException("region.name", "is missing");
	}
	
	return new Region(regionName);
}

template <class T>
void MapLoader::loadEdges(Graph<T>* graph, const std::string& graphType, const Json::Value& edgesNode, const int& cost)
{
	auto edges = edgesNode["edges"];

	if (edges.empty())
	{
		throw FileFieldException(graphType + ".edges", "is missing  or empty");
	}
	
	for (const auto& edgeNode : edges)
	{
		auto firstName = edgeNode["first"].asString();
		auto secondName = edgeNode["second"].asString();

		if (firstName.empty())
		{
			throw FileFieldException("edge.first", "is missing");
		}
		if (secondName.empty())
		{
			throw FileFieldException("edge.second", "is missing");
		}
		
		graph->addEdge(firstName, secondName, cost);
	}
}

void MapLoader::loadEdgesMap(GameMap* graph, const Json::Value& edgesNode, const int& cost)
{
	loadEdges(graph, "map", edgesNode, cost);
}

void MapLoader::loadEdgesContinent(Continent* graph, const Json::Value& edgesNode, const int& cost)
{
	loadEdges(graph, "continent", edgesNode, cost);
}
