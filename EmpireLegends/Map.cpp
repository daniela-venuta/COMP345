#include <iostream>
#include <queue>
#include "Map.h"
#include "Player.h"

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

#pragma region location

std::string Location::getName() const
{
    return this->name;
}

void Location::setName(const std::string& newName)
{
    this->name = newName;
}

#pragma endregion location

#pragma region region

Region::Region(const Region& region) : Location(region.getName())
{}

Region& Region::operator=(Region region)
{
    this->setName(region.getName());
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
    return static_cast<Location*>(value)->getName();
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
    adjacency.clear();
    delete this->value;
    this->value = nullptr;
}

template <class T>
int Territory<T>::getTravelCostWithVisits(Territory<T>* destination, std::vector<Territory<T>*>& visited)
{
    if (std::find(visited.begin(), visited.end(), this) != visited.end())
    {
        return 0;
    }

    auto cost = 0;

    visited.push_back(this);

    for (auto itr = this->adjacency.begin(); itr != this->adjacency.end(); ++itr)
    {
        if (itr->second == destination)
        {
        	// Stop recursion
            return itr->first * visited.size();
        }

    	// Continue recursion
        cost += itr->second->getTravelCostWithVisits(destination, visited);
    }

    return cost;
}

template <class T>
int Territory<T>::getTravelCost(Territory<T>* destination)
{
	if (this == destination)
	{
        return 0;
	}

    auto visited = std::vector<Territory<T>*>();
    visited.push_back(this);
    auto cost = 0;

	for (auto itr = this->adjacency.begin(); itr != this->adjacency.end(); ++itr)
	{
		if (itr->second == destination)
		{
            return itr->first;
		}
		// Start recursion
        cost += itr->second->getTravelCostWithVisits(destination, visited);
	}

    visited.clear();

    return cost;
}

template <class T>
bool Territory<T>::addArmies(int number, Player* player)
{
    bool added = false;

    if (number > 0 && number <= 18 && (armies[player] + number) <= 72)
    {
        armies[player] = armies[player] + number;
        added = true;

    	// Adding ownership of the territory if only owned armies are on it
        if (armies[player] == getTotalArmyCount())
        {
            for (auto itr = armies.begin(); itr != armies.end(); ++itr)
            {
                // Removing ownership of the territory from the previous owner
                if (itr->second == armies[player])
                {
                    player->addOwnedTerritory(dynamic_cast<Territory<Region>*>(this));
                    itr->first->removeOwnedTerritory(dynamic_cast<Territory<Region>*>(this));
                }
            }
        }
    }
    else
    {
        std::cout << "Cannot add specified number of armies." << std::endl;;
    }
    return added;
}

template <class T>
bool Territory<T>::removeArmies(int number, Player* player)
{
    bool removed = false;
	
    if (number > 0 && number <= 18 && armies[player] - number >= 0)
    {
        armies[player] = armies[player] - number;
        removed = true;

        // Removing ownership of the territory if no owned armies are on it
    	if (armies[player] == 0)
    	{
            player->removeOwnedTerritory(dynamic_cast<Territory<Region>*>(this));
    	}

        for (auto itr = armies.begin(); itr != armies.end(); ++itr)
        {
            // Adding ownership of the territory if someone else owns it now
            if (itr->second == getTotalArmyCount())
            {
                player->addOwnedTerritory(dynamic_cast<Territory<Region>*>(this));
                break;
            }
    	}
    }
    else
    {
        std::cout << "Cannot remove specified number of armies." << std::endl;;
    }

    return removed;
}

template<class T>
void Territory<T>::addCity(Player* player)
{
    cities[player] = cities[player] + 1;
}

template <class T>
int Territory<T>::getTotalArmyCount() const
{
    int totalCount = 0;

    for (auto& army : armies)
    {
        totalCount += army.second;
    }
    return totalCount;
}

template <class T>
int Territory<T>::getPlacedArmies(Player* player) const
{
    if (armies.count(player) > 0)
    {
        return armies.at(player);
    }
	
    return 0;
}

template <class T>
int Territory<T>::getPlacedCities(Player* player) const
{
    if(cities.count(player) > 0)
    {
        return cities.at(player);
    }

    return 0;
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
    throw TerritoryInGraphException(terr->getName(), this->getName());
}

template <class T>
void Graph<T>::addEdge(const std::string& first, const std::string& second, int cost)
{
    auto* f = terrs[first];
    auto* s = terrs[second];
    std::pair<int, Territory<T>*> edgeFirst = std::make_pair(cost, f);
    std::pair<int, Territory<T>*> edgeSecond = std::make_pair(cost, s);
	// Creating the undirected edge by adding each territory to the other's adjacency vector

	for (auto itr = f->adjacency.begin(); itr != f->adjacency.end(); ++itr)
	{
		if (itr->second->getName() == s->getName())
		{
            throw EdgeInGraphException(f->getName(), s->getName(), this->getName());
		}
	}

    f->adjacency.push_back(edgeSecond);
    s->adjacency.push_back(edgeFirst);
}

template <class T>
Graph<T>::Graph(const Graph<T>& graph) : Location(graph.getName())
{
	// Adding territories
    for (auto itr = graph.terrs.begin(); itr != graph.terrs.end(); ++itr)
    {
        try
        {
            this->addTerritory(new Territory<T>(*itr->second));
        }
        catch (TerritoryInGraphException&) {}
    }

    // Adding edges
    for (auto itr = graph.terrs.begin(); itr != graph.terrs.end(); ++itr)
    {
        Territory<T>* terr1 = itr->second;

    	// Copying edges
        for (auto terrItr = terr1->adjacency.begin(); terrItr != itr->second->adjacency.end(); ++terrItr)
        {
            Territory<T>* terr2 = terrItr->second;

            try
            {
                findTerritory(terr2->getName());
                // Adding edge if not already defined
                this->addEdge(terr1->getName(), terr2->getName(), terrItr->first);
            }
            catch (MapException&) {}
        }
    }
}

template <class T>
Graph<T>& Graph<T>::operator=(const Graph<T>& graph)
{
    auto* copy = new Graph<T>(graph);

    this->setName(graph.getName());
	this->terrs = copy->terrs;

    delete copy;
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
    throw TerritoryNotFoundException(name, this->getName());
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
	
    for (std::pair<const std::string, Territory<T>*>& pair : terrs)
    {
	    delete pair.second;
	    pair.second = nullptr;
    }
}

#pragma endregion graph


#pragma region continent

bool Continent::contains(Territory<Region>* terr)
{
    return this->terrs.find(terr->getName()) != this->terrs.end();
}

int Continent::getBestCost(Territory<Region>* terr)
{
    auto* first = this->terrs.begin()->second;
    auto* last = this->terrs.rbegin()->second;
	// Getting cost when using the first territory
    auto travelCostFirst = terr->getTravelCost(first);
    // Getting cost when using the last territory
    auto travelCostLast = terr->getTravelCost(last);

    return travelCostFirst <= travelCostLast ? travelCostFirst : travelCostLast;
}

#pragma endregion continent

#pragma region gameMap

std::string GameMap::toString() const
{
	std::string s;
    s.append(this->getName());
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

void GameMap::validateContinent(std::vector<std::string>& keys, std::map<std::string, Territory<Region>*> continentTerrs) const
{
	for (auto terrItr = continentTerrs.begin(); terrItr != continentTerrs.end(); ++terrItr)
	{
        if (std::empty(terrItr->second->adjacency))
        {
            throw InvalidMapException(this->getName(), "'" + terrItr->first + "' is not connected to any other region\n");
        }
		
		// If the key is not in the keys vector
		if (find(keys.begin(), keys.end(), terrItr->first) == keys.end())
		{
			// Adding the territory's key to the keys vector
			keys.push_back(terrItr->first);
		} else
		{
			throw InvalidMapException(this->getName(), "'" + terrItr->first + "' is in multiple continents\n");
		}
	}
}

void GameMap::validate()
{
	std::vector<std::string> keys;
    // Check that all regions from all continents are never found twice in the keys vector 
    for (auto continentItr = terrs.begin(); continentItr != terrs.end(); ++continentItr)
    {
        if (std::empty(continentItr->second->adjacency))
        {
            throw InvalidMapException(this->getName(), "'" + continentItr->first + "' is not connected to any other continent\n");
        }
        validateContinent(keys, continentItr->second->value->terrs);
    }

	std::cout << this->getName() << " is valid\n" << std::endl;
}

int GameMap::getTravelCost(Territory<Region>* from, Territory<Region>* to)
{
    auto cost = from->getTravelCost(to);

	// Both territories are in the same continent
	if (cost > 0)
	{
        return cost;
	}

    Territory<Continent>* continentFrom = nullptr;
    Territory<Continent>* continentTo = nullptr;

	// Find both continents the territories belong to
	for (auto itr = this->terrs.begin(); itr != this->terrs.end(); ++itr)
	{
        auto* tempContinent = itr->second;
		
		// Stop when both continents are found
		if (continentFrom != nullptr && continentTo != nullptr)
		{
            break;
		}
		if (continentFrom == nullptr && tempContinent->value->contains(from))
        {
            continentFrom = tempContinent;
            continue;
        }
        if (continentTo == nullptr && tempContinent->value->contains(to))
        {
            continentTo = tempContinent;
        }
	}

    if (continentFrom == nullptr || continentTo == nullptr)
    {
        return 0;
    }

    cost += continentFrom->value->getBestCost(from);
    cost += continentFrom->getTravelCost(continentTo);
    cost += continentTo->value->getBestCost(to);
	
    return cost;
}

#pragma endregion gameMap
