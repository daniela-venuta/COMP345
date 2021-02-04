#include "Map.h"
#include <string>
#include <iostream>


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
    s.append("\t\t");
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
    return *static_cast<location*>(this->value)->name;
}

template <class T>
territory<T>::~territory()
{
    cout << "Deleting territory: " << this->get_name() << endl;
    //Deleting all pointers in the vector
    for (auto adj : adjacency)
    {
        adj.second = nullptr;
    }
    adjacency.clear();
    delete value;
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
    cout << "\nTerritory already exists!";
}

template <class T>
void graph<T>::add_edge(const string& from, const string& to, double cost)
{
    territory<T>* f = (terrs.find(from)->second);
    territory<T>* t = (terrs.find(to)->second);
    pair<int, territory<T>*> edgeFrom = make_pair(cost, f);
    pair<int, territory<T>*> edgeTo = make_pair(cost, t);
    f->adjacency.push_back(edgeTo);
    t->adjacency.push_back(edgeFrom);
}

template<class T>
string graph<T>::to_string()
{
    string s;
    s.append(*this->name);
    s.append("\n");
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append(itr->second->to_string());
        s.append("\n");
    }
    return s;
}

template <class T>
graph<T>::~graph()
{
    cout << "Deleting graph: " << *this->name << endl;
	//Deleting all pointers in the map
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        delete itr->second;
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
        s.append("\t");
        s.append(itr->second->value->to_string());
        s.append("\n");
    }
    return s;
}

#pragma endregion gameMap

