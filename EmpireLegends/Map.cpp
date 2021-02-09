#include "Map.h"
#include <iostream>

#pragma region exceptions

InvalidMapException::InvalidMapException(const std::string& name, const std::string& reason)
    : MapException(std::string("Invalid Map '" + name + "': " + reason))
{}

TerritoryNotFoundException::TerritoryNotFoundException(const std::string& territoryName, const std::string& graphName)
    : MapException(std::string("Territory '" + territoryName + "' is not in graph '" + graphName + "'\n"))
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
std::string Territory<T>::toString()
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
std::string Territory<T>::getName()
{
    return *reinterpret_cast<Location*>(this->value)->name;
}

template <class T>
void Territory<T>::removeOwnAdjacency(typename std::vector<std::pair<int, Territory<T>*>>::iterator itr)
{
	auto otherAdjacency = itr->second->adjacency;
	for (auto otherItr = otherAdjacency.begin(); otherItr != otherAdjacency.end(); ++otherItr)
	{
		// Removing itself from the other territory's adjacency vector if it's found in it (without deleting the pointer)
		if (otherItr->second->getName() == this->getName())
		{
			otherAdjacency.erase(otherItr);
			break;
		}
	}
}

template <class T>
Territory<T>::~Territory()
{
    if (this->value == nullptr || this->adjacency.empty())
    {
        return;
    }
	
    std::cout << "Deleting territory: " << this->getName() << std::endl;
    for (auto itr = adjacency.begin(); itr != adjacency.end(); itr = adjacency.begin())
    {
    	// If the adjacent territory's value is null or its adjacency vector is empty, it means it's virtually already deleted
        if (itr->second->value == nullptr || itr->second->adjacency.empty())
        {
        	//We shouldn't try to remove it
            break;
        }

    	// Remove the current territory from the adjacent territories
        removeOwnAdjacency(itr);
    	
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
    std::string name = terr->getName();
    typename Territories::iterator itr = terrs.find(name);
    if (itr == terrs.end())
    {
        terrs[name] = terr;
        return;
    }
    std::cout << "\nTerritory '" << terr->getName() << "' already exists in '" << *this->name << "' and was not added\n"
	    << std::endl;
}

template <class T>
void Graph<T>::addEdge(const std::string& first, const std::string& second, double cost)
{
    Territory<T>* f = (terrs.find(first)->second);
    Territory<T>* s = (terrs.find(second)->second);
    std::pair<int, Territory<T>*> edgeFirst = std::make_pair(cost, f);
    std::pair<int, Territory<T>*> edgeSecond = std::make_pair(cost, s);
	// Creating the undirected edge by adding each territory to the other's adjacency vector
    f->adjacency.push_back(edgeSecond);
    s->adjacency.push_back(edgeFirst);
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
    throw TerritoryNotFoundException(name, *this->name);
}

template<class T>
std::string Graph<T>::toString()
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
    std::cout << "Deleting graph: " << *this->name << std::endl;
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

std::string GameMap::toString()
{
	std::string s;
    s.append(*this->name);
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
		} else
		{
			throw InvalidMapException(*this->name, "'" + terrItr->first + "' is in multiple continents\n");
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

	std::cout << *this->name << " is valid\n" << std::endl;
}

#pragma endregion gameMap
