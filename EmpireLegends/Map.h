#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

struct location
{
    std::string* name;

    explicit location(std::string* name) : name(name) {}
    virtual ~location();
};


struct region : location
{
    explicit region(std::string* name) : location(name) {}
};

template <class T>
struct territory
{
    typedef pair<int, territory<T>*> territoryEdge;
    vector<territoryEdge> adjacency;
    T* value;
	
    explicit territory(T* value) : value(value) {}
    virtual ~territory();

    string to_string();
    string get_name();
};

template <class T>
class graph: public location
{
protected:
	explicit graph(std::string* name) : location(name) {}

public:
    typedef map<string, territory<T>*> territories;
    territories terrs;

    virtual ~graph();

    void add_territory(territory<T>* terr);
    void add_edge(const string& from, const string& to, double cost);
    virtual string to_string();
};

class continent : public graph<region>
{
public:
    explicit continent(std::string* name): graph<region>(name) {}
};

class gameMap : public graph<continent>
{
public:
    explicit gameMap(std::string* name) : graph<continent>(name) {}
	
    string to_string() override;
};

#pragma region aliases

template <class T>
using territoryEdge = pair<int, territory<T>*>;

template <class T>
using territories = map<string, territory<T>*>;

#pragma endregion aliases
