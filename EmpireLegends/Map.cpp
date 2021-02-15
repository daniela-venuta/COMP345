#include "Map.h"
#include <iostream>

#pragma region exceptions

InvalidMapException::InvalidMapException(const string& name, const string& reason)
    : exception((new string("Invalid Map '" + name + "': " + reason))->c_str())
{}

TerritoryNotFoundException::TerritoryNotFoundException(const string& territoryName, const string& graphName)
    : exception((new string("Territory '" + territoryName + "' is not in graph '" + graphName + "'\n"))->c_str())

{}

#pragma endregion exceptions

#pragma region location

Location::~Location()
{
    delete name;
}

#pragma endregion  location

#pragma region territory

template class Territory<Region>;
template class Territory<Continent>;

template <class T>
string Territory<T>::toString()
{
    string s;
    s.append("\t");
    for (const auto pair : adjacency)
    {
        s.append("(");
        s.append(this->getName());
        s.append(", ");
        s.append(pair.second->getName());
        s.append(", ");
        s.append(std::to_string(pair.first));
        s.append(") ");
    }
    return s;
}

template <class T>
string Territory<T>::getName()
{
    return *reinterpret_cast<Location*>(this->value)->name;
}

template <class T>
Territory<T>::~Territory()
{
    if (this->value == nullptr || this->adjacency.empty())
    {
        return;
    }
	
    cout << "Deleting territory: " << this->getName() << endl;
    for (auto itr = adjacency.begin(); itr != adjacency.end(); itr = adjacency.begin())
    {
        if (itr->second->value == nullptr || itr->second->adjacency.empty())
        {
            break;
        }
    	
        auto otherAdjacency = itr->second->adjacency;

        for (auto otherItr = otherAdjacency.begin(); otherItr != otherAdjacency.end(); ++otherItr)
        {
            if (otherItr->second->getName() == this->getName())
            {
                otherAdjacency.erase(otherItr);
                break;
            }
        }
        adjacency.erase(itr);
    }
    this->adjacency.clear();
    delete  this->value;
    this->value = nullptr;
}

#pragma endregion territory

#pragma region graph

template class Graph<Region>;
template class Graph<Continent>;

template <class T>
void Graph<T>::addTerritory(Territory<T>* terr)
{
    string name = terr->getName();
    typename Territories::iterator itr = terrs.find(name);
    if (itr == terrs.end())
    {
        terrs[name] = terr;
        return;
    }
    cout << "\nTerritory '" << terr->getName() << "' already exists in '" << *this->name << "' and was not added\n" <<endl;
}

template <class T>
void Graph<T>::addEdge(const string& first, const string& second, double cost)
{
    Territory<T>* f = (terrs.find(first)->second);
    Territory<T>* s = (terrs.find(second)->second);
    pair<int, Territory<T>*> edgeFirst = make_pair(cost, f);
    pair<int, Territory<T>*> edgeSecond = make_pair(cost, s);
    f->adjacency.push_back(edgeSecond);
    s->adjacency.push_back(edgeFirst);
}

template <class T>
Territory<T>* Graph<T>::findTerritory(string name)
{	
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
    	if (itr->second->getName() == name)
    	{
            return itr->second;
    	}
    }
    throw TerritoryNotFoundException(name, *this->name);
}

template<class T>
string Graph<T>::toString()
{
    string s;
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append("\t");
        s.append(itr->second->toString());
        s.append("\n");
    }
    return s;
}

template <class T>
Graph<T>::~Graph()
{
    cout << "Deleting graph: " << *this->name << endl;
	//Deleting all territories in the graph
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
    	if (!itr->second->adjacency.empty())
    	{
            delete itr->second;
    	}
    }
    terrs.clear();
}

#pragma endregion graph

#pragma region gameMap

string GameMap::toString()
{
    string s;
    s.append(*this->name);
    s.append("\n");
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append(itr->second->toString());
        s.append("\n");
        s.append(itr->second->value->toString());
        s.append("\n");
    }
    return s;
}

void GameMap::validate()
{
    vector<string> keys;
    for (auto continentItr = terrs.begin(); continentItr != terrs.end(); ++continentItr)
    {
        auto continentTerrs = continentItr->second->value->terrs;
        for (auto terrItr = continentTerrs.begin(); terrItr != continentTerrs.end(); ++terrItr)
        {
        	if (find(keys.begin(), keys.end(), terrItr->first) == keys.end())
        	{
                keys.push_back(terrItr->first);
        	} else
            {
                throw InvalidMapException(*this->name, "'" + terrItr->first + "' is in multiple continents\n");
            }
        }
    }

    cout << *this->name << " is valid\n" << endl;
}

#pragma endregion gameMap
