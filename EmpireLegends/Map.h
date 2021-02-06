#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

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
    explicit Location(string* name) : name(name) {}
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
    explicit Region(string* name) : Location(name) {}
};

/// <summary>
/// Generic territory class that acts as a graph node and stores a value
/// </summary>
template <class T>
struct Territory
{
    typedef pair<int, Territory<T>*> TerritoryEdge;
    vector<TerritoryEdge> adjacency;
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
    string toString();
    /// <summary>
    /// Returns the territory's name
    /// </summary>
    /// <returns>territory's name</returns>
    string getName();
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
	explicit Graph(string* name) : Location(name) {}

public:
    typedef map<string, Territory<T>*> Territories;
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
    void addEdge(const string& first, const string& second, double cost);
    /// <summary>
    /// Finding a territory in the graph
    /// </summary>
    /// <param name="name">territory name</param>
    /// <returns>found territory</returns>
    /// <throws>TerritoryNotFoundException</throws>
    Territory<T>* findTerritory(string name);
    /// <summary>
    /// Returns the graph's string representation
    /// </summary>
    /// <returns>string representation</returns>
	virtual string toString();
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
    explicit Continent(string* name): Graph<Region>(name) {}
};

/// <summary>
/// GameMap class, which is a graph of continents
/// </summary>
class GameMap : public Graph<Continent>
{
public:
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">map's name</param>
    explicit GameMap(string* name) : Graph<Continent>(name) {}

    /// <summary>
    /// Returns the map's string representation
    /// </summary>
    /// <returns>string representation</returns>
    string toString() override;
    /// <summary>
    /// Validates the map. If the map is invalid, it throws an invalidMapException
    /// </summary>
    /// <throws>InvalidMapException</throws>
    void validate();
};

#pragma region aliases

template <class T>
using TerritoryEdge = pair<int, Territory<T>*>;

template <class T>
using Territories = map<string, Territory<T>*>;

#pragma endregion aliases

#pragma region exceptions

/// <summary>
/// Invalid map exception
/// </summary>
struct InvalidMapException : exception
{
    /// <summary>
    /// 2-parameter constructor
    /// </summary>
    /// <param name="name">map name</param>
    /// <param name="reason">invalidity reason</param>
    InvalidMapException(const string& name, const string& reason);
};

/// <summary>
/// Territory not found exception
/// </summary>
struct TerritoryNotFoundException : exception
{
    /// <summary>
    /// 2-parameter constructor
    /// </summary>
    /// <param name="territoryName">element name</param>
    /// <param name="graphName">searched graph's name</param>
    TerritoryNotFoundException(const string& territoryName, const string& graphName);
};

#pragma endregion exceptions

