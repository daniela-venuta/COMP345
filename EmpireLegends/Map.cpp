#pragma once
#include "Map.h"
#include <string>
#include <iostream>

#pragma region territory

template <class T>
string territory<T>::toString()
{
    string s;

    s.append("\t\t");
	
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
string territory<T>::getName()
{
    return *((location*)(this->value))->name;
}

#pragma endregion territory

#pragma region graph

template class graph<region>;
template class graph<continent>;

template <class T>
void graph<T>::addTerritory(territory<T>* terr)
{
    string name = terr->getName();
    typename territories::iterator itr = terrs.find(name);
    if (itr == terrs.end())
    {
        terrs[name] = terr;
        return;
    }
    cout << "\nTerritory already exists!";
}

template <class T>
void graph<T>::addEdge(const string& from, const string& to, double cost)
{
    territory<T>* f = (terrs.find(from)->second);
    territory<T>* t = (terrs.find(to)->second);
    pair<int, territory<T>*> edgeFrom = make_pair(cost, f);
    pair<int, territory<T>*> edgeTo = make_pair(cost, t);
    f->adjacency.push_back(edgeTo);
    t->adjacency.push_back(edgeFrom);
}

template<class T>
string graph<T>::toString()
{
    string s;
    s.append(*this->name);
    s.append("\n");
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append(itr->second->toString());
        s.append("\n");
    }
    return s;
}

#pragma endregion graph

#pragma region gameMap

string gameMap::toString()
{
    string s;
    s.append(*this->name);
    s.append("\n");
    for (auto itr = terrs.begin(); itr != terrs.end(); ++itr)
    {
        s.append("\t");
        s.append(itr->second->value->toString());
        s.append("\n");
    }
    return s;
}

#pragma endregion gameMap

