#include "Map.h"
#include <iostream>
#include <queue>

#pragma region exceptions

TerritoryInGraphException::TerritoryInGraphException(const std::string& territoryName, const std::string& graphName)
    : MapException(std::string("Territory '" + territoryName + "' is already in graph '" + graphName + "'\n"))
{}

EdgeInGraphException::EdgeInGraphException(const std::string& firstName, const std::string& secondName, const std::string& graphName)
    : MapException(std::string("Edge between '" + firstName + "' and '" + secondName + "' is already in graph '" + graphName + "'\n"))
{}

InvalidMapException::InvalidMapException(const std::string& name, const std::string& reason)
    : MapException(std::string("Invalid Map '" + name + "': " + reason))
{}

TerritoryNotFoundException::TerritoryNotFoundException(const std::string& territoryName, const std::string& graphName)
    : MapException(std::string("Territory '" + territoryName + "' is not in graph '" + graphName + "'\n"))
{}

#pragma endregion exceptions

#pragma region region

Region::Region(const Region& region) : Location(region.name)
{}

Region& Region::operator=(Region region)
{
    this->name = region.name;
    return *this;
}

#pragma endregion  region

#pragma region territory

// Declaring possible templates for Territory
template class Territory<Region>;
template class Territory<Continent>;

template <class T>
std::string Territory<T>::toString() const
{
    std::string s;
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
std::string Territory<T>::getName() const
{
    return value->name;
}

template <class T>
Territory<T>::Territory(const Territory<T>& territory)
{
    this->value = new T(*territory.value);
}

template <class T>
Territory<T>& Territory<T>::operator=(Territory<T> territory)
{
    if (this == &territory)
    {
        return *this;
    }

    auto newValue = *territory.value;
    this->value = &newValue;

    return *this;
}

template <class T>
Territory<T>::~Territory()
{
    if (this->value == nullptr || this->adjacency.empty())
    {
        return;
    }

    std::cout << "\nDeleting territory: " << this->getName() << std::endl;

    this->adjacency.clear();
    delete this->value;
    this->value = nullptr;
}

#pragma endregion territory

#pragma region graph

// Declaring possible templates for Graph
template class Graph<Region>;
template class Graph<Continent>;

template <class T>
void Graph<T>::addTerritory(Territory<T>* terr)
{
    std::string name = terr->getName();

    typename Territories::iterator itr = terrs.find(name);
    if (itr == terrs.end())
    {
        terrs[name] = terr;
        return;
    }
    throw TerritoryInGraphException(terr->getName(), this->name);
}

template <class T>
void Graph<T>::addEdge(const std::string& first, const std::string& second, int cost)
{
    Territory<T>* f = terrs.find(first)->second;
    Territory<T>* s = terrs.find(second)->second;
    std::pair<int, Territory<T>*> edgeFirst = std::make_pair(cost, f);
    std::pair<int, Territory<T>*> edgeSecond = std::make_pair(cost, s);
    // Creating the undirected edge by adding each territory to the other's adjacency vector

    for (auto itr = f->adjacency.begin(); itr != f->adjacency.end(); ++itr)
    {
        if (itr->second->getName() == s->getName())
        {
            throw EdgeInGraphException(f->getName(), s->getName(), this->name);
        }
    }

    f->adjacency.push_back(edgeSecond);
    s->adjacency.push_back(edgeFirst);
}

template <class T>
Graph<T>::Graph(const Graph<T>& graph) : Location(graph.name)
{
    for (auto itr = graph.terrs.begin(); itr != graph.terrs.end(); ++itr)
    {
        Territory<T>* currentTerritoryCopy = new Territory<T>(*itr->second);

        try
        {
            this->addTerritory(currentTerritoryCopy);
        }
        catch (TerritoryInGraphException&) {}

        // Copying edges
        for (auto terrItr = itr->second->adjacency.begin(); terrItr != itr->second->adjacency.end(); ++terrItr)
        {
            Territory<T>* innerTerritoryCopy = new Territory<T>(*terrItr->second);

            try
            {
                // Adding other territory if not already in the graph
                this->addTerritory(innerTerritoryCopy);
            }
            catch (TerritoryInGraphException&) {}

            try
            {
                // Adding edge if not already defined
                this->addEdge(currentTerritoryCopy->getName(), innerTerritoryCopy->getName(), terrItr->first);
            }
            catch (EdgeInGraphException&) {}
        }
    }
}

template <class T>
Graph<T>& Graph<T>::operator=(Graph<T> graph)
{
    return *this;
}

template <class T>
Territory<T>* Graph<T>::findTerritory(std::string name)
{
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        if (itr->second->getName() == name)
        {
            return itr->second;
        }
    }
    throw TerritoryNotFoundException(name, this->name);
}

template<class T>
std::string Graph<T>::toString() const
{
    std::string s;
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
    if (this->terrs.empty())
    {
        return;
    }

    std::cout << "\nDeleting graph: " << this->name << std::endl;
    //Deleting all territories in the graph
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        if (itr->second->value != nullptr && !itr->second->adjacency.empty())
        {
            delete itr->second;
        }
    }
    terrs.clear();
}

#pragma endregion graph

#pragma region gameMap

std::string GameMap::toString() const
{
    std::string s;
    s.append(this->name);
    s.append("\n");
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append(itr->second->getName());
        s.append("\n");
        s.append(itr->second->toString());
        s.append("\n");
        s.append(itr->second->value->toString());
        s.append("\n");
    }
    return s;
}

void GameMap::checkForKeyDuplicates(std::vector<std::string>& keys, std::map<std::string, Territory<Continent>*>::iterator continentItr)
{
    auto continentTerrs = continentItr->second->value->terrs;
    for (auto terrItr = continentTerrs.begin(); terrItr != continentTerrs.end(); ++terrItr)
    {
        // If the key is not in the keys vector
        if (find(keys.begin(), keys.end(), terrItr->first) == keys.end())
        {
            // Adding the territory's key to the keys vector
            keys.push_back(terrItr->first);
        }
        else
        {
            throw InvalidMapException(this->name, "'" + terrItr->first + "' is in multiple continents\n");
        }
    }
}

void GameMap::validate()
{
    std::vector<std::string> keys;
    // Check that all regions from all continents are never found twice in the keys vector 
    for (auto continentItr = terrs.begin(); continentItr != terrs.end(); ++continentItr)
    {
        checkForKeyDuplicates(keys, continentItr);
    }

    std::cout << this->name << " is valid\n" << std::endl;
}

#pragma endregion gameMap