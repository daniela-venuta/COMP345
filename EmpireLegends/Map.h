#pragma once
#include <vector>
#include <map>
#include <string>

/// <summary>
/// Location class
/// </summary>
struct Location
{
    std::string* name;

    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">location name</param>
    explicit Location(std::string* name) : name(name) {}
    virtual ~Location();
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
    explicit Region(std::string name) : Location(new std::string(name)) {}
};

/// <summary>
/// Generic territory class that acts as a graph node and stores a value
/// </summary>
template <class T>
class Territory
{
    /// <summary>
    /// Removes the territory's presence in adjacent territories.
    /// </summary>
    /// <param name="itr">vector iterator for adjacent territories</param>
    void removeOwnAdjacency(typename std::vector<std::pair<int, Territory<T>*>>::iterator itr);

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
	/// Destructor
	/// </summary>
	virtual ~Territory();

    /// <summary>
    /// Returns the territory's string representation
    /// </summary>
    /// <returns>string representation</returns>
    std::string toString();
    /// <summary>
    /// String stream operator overload
    /// </summary>
    /// <param name="os">stream to write to</param>
    /// <param name="terr">territory to add to the stream</param>
    /// <returns>stream with the territory's string representation added</returns>
    friend std::ostream& operator<<(std::ostream& os, Territory* terr) {
        return os << terr->toString();
    }
    /// <summary>
    /// Returns the territory's name
    /// </summary>
    /// <returns>territory's name</returns>
    std::string getName();
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
	explicit Graph(std::string* name) : Location(name) {}

public:
    typedef std::map<std::string, Territory<T>*> Territories;
    Territories terrs;
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
    /// <param name="cost"></param>
    void addEdge(const std::string& first, const std::string& second, double cost);
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
	virtual std::string toString();

    /// <summary>
    /// String stream operator overload
    /// </summary>
    /// <param name="os">stream to write to</param>
    /// <param name="graph">graph to add to the stream</param>
    /// <returns>stream with the graph's string representation added</returns>
    friend std::ostream& operator<<(std::ostream& os, Graph* graph) {
        return os << graph->toString();
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
    explicit Continent(std::string name): Graph<Region>(new std::string(name)) {}
};

/// <summary>
/// GameMap class, which is a graph of continents
/// </summary>
class GameMap : public Graph<Continent>
{
    /// <summary>
    /// Checks that there are no duplicated keys found in a continent iterator. Throws InvalidMapException if a duplication is found.
    /// </summary>
	void checkForKeyDuplicates(std::vector<std::string>& keys, std::map<std::string, Territory<Continent>*>::iterator continentTerrs);
public:
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">map's name</param>
    explicit GameMap(std::string name) : Graph<Continent>(new std::string(name)) {}

    /// <summary>
    /// Returns the map's string representation
    /// </summary>
    /// <returns>string representation</returns>
    std::string toString() override;
    /// <summary>
    /// Validates the map. If the map is invalid, it throws an InvalidMapException
    /// </summary>
    void validate();
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
    /// String stream operator overload
    /// </summary>
    /// <param name="os">stream to write to</param>
    /// <param name="graph">graph to add to the stream</param>
    /// <returns>stream with the graph's string representation added</returns>
    friend std::ostream& operator<<(std::ostream& os, MapException e) {
        return os << std::string(e.what());
    }
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

