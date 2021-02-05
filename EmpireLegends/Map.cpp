#include "Map.h"
#include <iostream>

#pragma region exceptions

invalidMapException::invalidMapException(const string& name, const string& reason)
    : exception((new string("Invalid Map '" + name + "': " + reason))->c_str())
{}

territoryNotFoundException::territoryNotFoundException(const string& territory_name, const string& graph_name)
    : exception((new string("Territory '" + territory_name + "' is not in graph '" + graph_name + "'\n"))->c_str())

{}

#pragma endregion exceptions

#pragma region location

location::~location()
{
    delete name;
}

#pragma endregion  location

#pragma region territory

template class territory<region>;
template class territory<continent>;

template <class T>
string territory<T>::to_string()
{
    string s;
    s.append("\t");
    for (const auto pair : adjacency)
    {
        s.append("(");
        s.append(this->get_name());
        s.append(", ");
        s.append(pair.second->get_name());
        s.append(", ");
        s.append(std::to_string(pair.first));
        s.append(") ");
    }
    return s;
}

template <class T>
string territory<T>::get_name()
{
    return *reinterpret_cast<location*>(this->value)->name;
}

template <class T>
territory<T>::~territory()
{
    if (this->value == nullptr || this->adjacency.empty())
    {
        return;
    }
	
    cout << "Deleting territory: " << this->get_name() << endl;
    for (auto itr = adjacency.begin(); itr != adjacency.end(); itr = adjacency.begin())
    {
        if (itr->second->value == nullptr || itr->second->adjacency.empty())
        {
            break;
        }
    	
        auto other_adjacency = itr->second->adjacency;

        for (auto other_itr = other_adjacency.begin(); other_itr != other_adjacency.end(); ++other_itr)
        {
            if (other_itr->second->get_name() == this->get_name())
            {
                other_adjacency.erase(other_itr);
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

template class graph<region>;
template class graph<continent>;

template <class T>
void graph<T>::add_territory(territory<T>* terr)
{
    string name = terr->get_name();
    typename territories::iterator itr = terrs.find(name);
    if (itr == terrs.end())
    {
        terrs[name] = terr;
        return;
    }
    cout << "\nTerritory '" << terr->get_name() << "' already exists in '" << *this->name << "' and was not added\n" <<endl;
}

template <class T>
void graph<T>::add_edge(const string& first, const string& second, double cost)
{
    territory<T>* f = (terrs.find(first)->second);
    territory<T>* s = (terrs.find(second)->second);
    pair<int, territory<T>*> edgeFirst = make_pair(cost, f);
    pair<int, territory<T>*> edgeSecond = make_pair(cost, s);
    f->adjacency.push_back(edgeSecond);
    s->adjacency.push_back(edgeFirst);
}

template <class T>
territory<T>* graph<T>::find_territory(string name)
{	
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
    	if (itr->second->get_name() == name)
    	{
            return itr->second;
    	}
    }
    throw territoryNotFoundException(name, *this->name);
}

template<class T>
string graph<T>::to_string()
{
    string s;
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append("\t");
        s.append(itr->second->to_string());
        s.append("\n");
    }
    return s;
}

template <class T>
graph<T>::~graph()
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

string gameMap::to_string()
{
    string s;
    s.append(*this->name);
    s.append("\n");
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append(itr->second->to_string());
        s.append("\n");
        s.append(itr->second->value->to_string());
        s.append("\n");
    }
    return s;
}

void gameMap::validate()
{
    vector<string> keys;
    for (auto continent_itr = terrs.begin(); continent_itr != terrs.end(); ++continent_itr)
    {
        auto continent_terrs = continent_itr->second->value->terrs;
        for (auto terr_itr = continent_terrs.begin(); terr_itr != continent_terrs.end(); ++terr_itr)
        {
        	if (find(keys.begin(), keys.end(), terr_itr->first) == keys.end())
        	{
                keys.push_back(terr_itr->first);
        	} else
            {
                throw invalidMapException(*this->name, "'" + terr_itr->first + "' is in multiple continents\n");
            }
        }
    }

    cout << *this->name << " is valid\n" << endl;
}

#pragma endregion gameMap
