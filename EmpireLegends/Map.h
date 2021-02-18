#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

/// <summary>
/// Location class
/// </summary>
struct Location
{
    std::string name;

    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">location name</param>
    explicit Location(std::string name)
    {
        this->name = std::move(name);
    }
};

/// <summary>
/// Region class
/// </summary>
struct Region : Location
{
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">region name</param>
    explicit Region(std::string name) : Location(name) {}
    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="region">region to copy</param>
    Region(const Region& region);
    /// <summary>
    /// Assignment operator overload
    /// </summary>
    /// <param name="region">region to assign to this instance</param>
    /// <returns>Region copied from parameter region</returns>
    Region& operator=(Region region);
};

/// <summary>
/// Generic territory class that acts as a graph node and stores a value
/// </summary>
template <class T>
class Territory
{
    int getTravelCostWithVisits(Territory<T>* destination, std::vector<Territory<T>*>& visited);
public:
    typedef std::pair<int, Territory<T>*> TerritoryEdge;
    std::vector<TerritoryEdge> adjacency;
    T* value;

    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="value">territory's value</param>
    explicit Territory(T* value) : value(value) {}
    /// <summary>
    /// Copy constructor. Does not copy the adjacency vector, since it's the graph's responsibility
    /// </summary>
    /// <param name="territory">territory to copy</param>
    Territory(const Territory<T>& territory);
    /// <summary>
    /// Assignment operator overload
    /// </summary>
    /// <param name="territory">territory to assign to this instance</param>
    /// <returns>Territory copied from parameter region</returns>
    Territory<T>& operator=(Territory<T> territory);
	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~Territory();

    /// <summary>
    /// Returns the territory's string representation
    /// </summary>
    /// <returns>string representation</returns>
    std::string toString() const;
    /// <summary>
    /// Stream insertion operator overload
    /// </summary>
    /// <param name="os">stream to write to</param>
    /// <param name="os">stream to write to</param>
    /// <param name="terr">territory to add to the stream</param>
    /// <returns>stream with the territory's string representation added</returns>
    friend std::ostream& operator<<(std::ostream& os, const Territory& terr) {
        return os << terr.toString();
    }
    /// <summary>
    /// Returns the territory's name
    /// </summary>
    /// <returns>territory's name</returns>
    std::string getName() const;

    int getTravelCost(Territory<T>* destination);
    void addArmies(int number);
    void removeArmies(int number);
    int getArmyCount();

private:
    int armyCount;
};

/// <summary>
/// Generic undirected graph class
/// </summary>
template <class T>
class Graph: public Location
{
protected:
	/// <summary>
	/// 1-parameter constructor
	/// </summary>
	/// <param name="name">graph's name</param>
	explicit Graph(std::string name) : Location(name) {}

public:
    typedef std::map<std::string, Territory<T>*> Territories;
    Territories terrs;
	
    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="graph">graph to copy</param>
    Graph<T>(const Graph<T>& graph);
    /// <summary>
    /// Assignment operator overload
    /// </summary>
    /// <param name="graph">graph to assign to this instance</param>
    /// <returns>Graph copied from parameter region</returns>
    Graph<T>& operator=(Graph<T> graph);
	
    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~Graph();

    /// <summary>
    /// Adding a territory to the graph
    /// </summary>
    /// <param name="terr">territory to add</param>
    void addTerritory(Territory<T>* terr);
    /// <summary>
    /// Adding an edge to the graph
    /// </summary>
    /// <param name="first">first territory name</param>
    /// <param name="second">second territory name</param>
    /// <param name="cost">cost to travel between the two territories</param>
    void addEdge(const std::string& first, const std::string& second, int cost);
    /// <summary>
    /// Finding a territory in the graph
    /// </summary>
    /// <param name="name">territory name</param>
    /// <returns>found territory</returns>
    Territory<T>* findTerritory(std::string name);
    /// <summary>
    /// Returns the graph's string representation
    /// </summary>
    /// <returns>string representation</returns>
	virtual std::string toString() const;

    /// <summary>
    /// Stream insertion operator overload
    /// </summary>
    /// <param name="os">stream to write to</param>
    /// <param name="graph">graph to add to the stream</param>
    /// <returns>stream with the graph's string representation added</returns>
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        return os << graph.toString();
    }
};

/// <summary>
/// Continent class, which is a graph of regions
/// </summary>
class Continent : public Graph<Region>
{
public:
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">continent's name</param>
    explicit Continent(std::string name): Graph<Region>(name) {}

    /// <summary>
    /// Gets the best cost to travel to the region (either from the first or from the last)
    /// </summary>
    /// <param name="terr">target region territory</param>
    /// <returns>cost of traveling to the region territory</returns>
    int getBestCost(Territory<Region>* terr);
    /// <summary>
    /// Checks whether a region is in the continent
    /// </summary>
    /// <param name="terr">checked region territory</param>
    /// <returns>whether the region is in the continent</returns>
    bool contains(Territory<Region>* terr);
};

/// <summary>
/// GameMap class, which is a graph of continents
/// </summary>
class GameMap : public Graph<Continent>
{
	/// <summary>
    /// Checks that a continent is valid. Throws InvalidMapException if a duplication is found or a region is unconnected.
    /// </summary>
	/// <param name="keys">already validated territories</param>
	/// <param name="continentTerrs">continent territories</param>
	void validateContinent(std::vector<std::string>& keys, std::map<std::string, Territory<Region>*> continentTerrs) const;
public:
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">map's name</param>
    explicit GameMap(std::string name) : Graph<Continent>(name) {}

    /// <summary>
    /// Returns the map's string representation
    /// </summary>
    /// <returns>string representation</returns>
    std::string toString() const override;
    /// <summary>
    /// Validates the map. If the map is invalid, it throws an InvalidMapException
    /// </summary>
    void validate();
    /// <summary>
    /// Get the travel cost between two regions
    /// </summary>
    /// <param name="from">first region territory</param>
    /// <param name="to">second region territory</param>
    /// <returns></returns>
    int getTravelCost(Territory<Region>* from, Territory<Region>* to);
};

#pragma region aliases

template <class T>
using TerritoryEdge = std::pair<int, Territory<T>*>;

template <class T>
using Territories = std::map<std::string, Territory<T>*>;

#pragma endregion aliases

#pragma region exceptions

/// <summary>
/// Generic map exception
/// </summary>
struct MapException : std::exception
{
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="message">exception name</param>
    MapException(std::string message) : exception((new std::string(message))->c_str()) {}

    /// <summary>
    /// Stream insertion operator overload
    /// </summary>
    /// <param name="os">stream to write to</param>
    /// <param name="graph">graph to add to the stream</param>
    /// <returns>stream with the graph's string representation added</returns>
    friend std::ostream& operator<<(std::ostream& os, MapException e) {
        return os << std::string(e.what());
    }
};

/// <summary>
/// Territory already in graph exception
/// </summary>
struct TerritoryInGraphException : MapException
{
    /// <summary>
    /// 2-parameter constructor
    /// </summary>
    /// <param name="territoryName">territory name</param>
    /// <param name="graphName">graph name</param>
    TerritoryInGraphException(const std::string& territoryName, const std::string& graphName);
};

/// <summary>
/// Edge already in graph exception
/// </summary>
struct EdgeInGraphException : MapException
{
    /// <summary>
    /// 2-parameter constructor
    /// </summary>
    /// <param name="firstName">first territory name</param>
    /// <param name="secondName">second territory name</param>
    /// <param name="graphName">graph name</param>
    EdgeInGraphException(const std::string& firstName, const std::string& secondName, const std::string& graphName);
};

/// <summary>
/// Invalid map exception
/// </summary>
struct InvalidMapException : MapException
{
    /// <summary>
    /// 2-parameter constructor
    /// </summary>
    /// <param name="name">map name</param>
    /// <param name="reason">invalidity reason</param>
    InvalidMapException(const std::string& name, const std::string& reason);
};

/// <summary>
/// Territory not found exception
/// </summary>
struct TerritoryNotFoundException : MapException
{
    /// <summary>
    /// 2-parameter constructor
    /// </summary>
    /// <param name="territoryName">element name</param>
    /// <param name="graphName">searched graph's name</param>
    TerritoryNotFoundException(const std::string& territoryName, const std::string& graphName);
};

#pragma endregion exceptions

