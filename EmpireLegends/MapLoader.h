#pragma once
#include <string>
#include "Map.h"
#include "json/json.h"


class MapLoader
{
	static Region* loadRegion(const Json::Value& regionNode);
	static Continent* loadContinent(const Json::Value& continentNode);
	template<class T>
	static void loadEdges(Graph<T>* graph, const std::string& graphType, const Json::Value& edgesNode, const int& cost);
	static void loadEdgesContinent(Continent* graph, const Json::Value& edgesNode, const int& cost);
	static void loadEdgesMap(GameMap* graph, const Json::Value& edgesNode, const int& cost);

public:
	
	explicit MapLoader() = default;

	~MapLoader() = default;

	GameMap* load(const std::string& fileName) const;
};

/// <summary>
/// Invalid map file exception
/// </summary>
struct InvalidMapFileException : MapException
{
	/// <summary>
	/// 1-parameter constructor
	/// </summary>
	/// <param name="reason">invalidity reason</param>
	InvalidMapFileException(const std::string& reason);

	friend std::ostream& operator<<(std::ostream& os, InvalidMapFileException e) {
		return os << std::string(e.what());
	}
};

/// <summary>
/// File field exception
/// </summary>
struct FileFieldException : InvalidMapFileException
{
	/// <summary>
	/// 1-parameter constructor
	/// </summary>
	/// <param name="field">field name</param>
	/// <param name="reason">invalidity reason</param>
	FileFieldException(const std::string& field, const std::string& reason);
};
