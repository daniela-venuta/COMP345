#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

struct nullValueException : exception {};

/// <summary>
/// Location class
/// </summary>
struct location
{
    std::string* name;

    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">location name</param>
    explicit location(string* name) : name(name) {}
    virtual ~location();
};

/// <summary>
/// Region class
/// </summary>
struct region : location
{
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">region name</param>
    explicit region(string* name) : location(name) {}
};

/// <summary>
/// Generic territory class that acts as a graph node and stores a value
/// </summary>
template <class T>
struct territory
{
    typedef pair<int, territory<T>*> territoryEdge;
    vector<territoryEdge> adjacency;
    T* value;

    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="value">territory's value</param>
    explicit territory(T* value) : value(value) {}
	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~territory();

    /// <summary>
    /// Returns the territory's string representation
    /// </summary>
    /// <returns>string representation</returns>
    string to_string();
    /// <summary>
    /// Returns the territory's name
    /// </summary>
    /// <returns>territory's name</returns>
    string get_name();
};

/// <summary>
/// Generic undirected graph class
/// </summary>
template <class T>
class graph: public location
{
protected:
	/// <summary>
	/// 1-parameter constructor
	/// </summary>
	/// <param name="name">graph's name</param>
	explicit graph(string* name) : location(name) {}

public:
    typedef map<string, territory<T>*> territories;
    territories terrs;
    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~graph();

    /// <summary>
    /// Adding a territory to the graph
    /// </summary>
    /// <param name="terr">territory to add</param>
    void add_territory(territory<T>* terr);
    /// <summary>
    /// Adding an edge to the graph
    /// </summary>
    /// <param name="first">first territory name</param>
    /// <param name="second">second territory name</param>
    /// <param name="cost"></param>
    void add_edge(const string& first, const string& second, double cost);
    /// <summary>
    /// Returns the graph's string representation
    /// </summary>
    /// <returns>string representation</returns>
	virtual string to_string();
};

/// <summary>
/// Continent class, which is a graph of regions
/// </summary>
class continent : public graph<region>
{
public:
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">continent's name</param>
    explicit continent(string* name): graph<region>(name) {}
};

/// <summary>
/// Invalid map exception
/// </summary>
struct invalidMapException : exception
{
	/// <summary>
	/// 2-parameter constructor
	/// </summary>
	/// <param name="name">map name</param>
	/// <param name="reason">invalidity reason</param>
	invalidMapException(const string& name, const string& reason);
};

/// <summary>
/// GameMap class, which is a graph of continents
/// </summary>
class gameMap : public graph<continent>
{
public:
    /// <summary>
    /// 1-parameter constructor
    /// </summary>
    /// <param name="name">map's name</param>
    explicit gameMap(string* name) : graph<continent>(name) {}

    /// <summary>
    /// Returns the map's string representation
    /// </summary>
    /// <returns>string representation</returns>
    string to_string() override;
    /// <summary>
    /// Validates the map. If the map is invalid, it throws an invalidMapException
    /// </summary>
    void validate();
};

#pragma region aliases

template <class T>
using territoryEdge = pair<int, territory<T>*>;

template <class T>
using territories = map<string, territory<T>*>;

#pragma endregion aliases
