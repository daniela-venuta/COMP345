#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

struct location
{
    std::string* name;

    location(std::string* name) : name(name) {}
};


struct region : location
{
    region(std::string* name) : location(name) {}
};

template <class T>
struct territory
{
    typedef pair<int, territory<T>*> territoryEdge;
    vector<territoryEdge> adjacency; //cost of edge, destination vertex
    T* value;
	
    territory(T* value) : value(value) {}

    string toString();
    string getName();
};

template <class T>
class graph: public location
{
public:
    typedef map<string, territory<T>*> territories;
    territories terrs;

    graph(std::string* name) : location(name) {}

    void addTerritory(territory<T>* terr);
    void addEdge(const string& from, const string& to, double cost);
    virtual string toString();
};

class continent : public graph<region>
{
public:
    continent(std::string* name): graph<region>(name) {}
};

class gameMap : public graph<continent>
{
public:
    gameMap(std::string* name) : graph<continent>(name) {}
	
    string toString() override;
};

#pragma region aliases

template <class T>
using territoryEdge = pair<int, territory<T>*>;

template <class T>
using territories = map<string, territory<T>*>;

#pragma endregion aliases
