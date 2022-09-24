#include "Map.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <stack>
#include<algorithm>
#include<vector>
#include <typeinfo>



Territory::Territory()
{
    tName = "";
    tID = 0;
    continentName = "";
    playerID = 0;
    armyAmount = 0;

}
Territory::Territory(string tName, string continentName, int tID)
{
    this->tName = tName;
    this->tID = tID;
    this->continentName = continentName;
    this->playerID = 0;
    this->armyAmount = 0;

}
//ostream& operator<< (ostream& out, const Territory& t) {}

//copy constructor
Territory::Territory(const Territory* t) {
    tName = t->tName;
    tID = t->tID;
    continentName = t->continentName;
    playerID = t->playerID;
    armyAmount = t->armyAmount;
}
//assignment operator
Territory& Territory::operator=(const Territory& t)
{
    this->tName = t.tName;
    this->tID = t.tID;
    this->continentName = t.continentName;
    this->playerID = t.playerID;
    this->armyAmount = t.armyAmount;
    return *this;
}

Territory::~Territory() {}
string Territory::getTName() { return tName; }
int Territory::getTID() { return tID; }
string Territory::getContinentName() { return continentName; }
int Territory::getPlayerID() { return playerID; }
int Territory::getArmyAmount() { return armyAmount; }

void Territory::setTName(string tName)
{
    tName = tName;
}
void Territory::setTID(int tID)
{
    tID = tID;
}
vector<string> Territory::getAdjacentTerritoryMembers() { return adjacentTerritoryMembers; }

Continent::Continent()
{
    cName = "";
    cID = 0;
}
Continent::Continent(string cName, int cID)
{
    this->cName = cName;
    this->cID = cID;
}

string Continent::getCName() { return cName; }
int Continent::getCID() { return cID; }


Map::Map()
{
    mName = "";
    graph;

}

Map::Map(string mName)
{
    this->mName = mName;

}

string Map::getMName() { return mName; }
string Map::getTerritoryNameFromTerritoryID(int tID)
{
    string tName = allTerritory[tID]->getTName(); 
    return tName;
};

int Map::getTerritoryIDFromTName(string tName)
{
    std::map<string, int>::iterator it;
    it = territoryIndexDictionary.find(tName);

    return territoryIndexDictionary.find(tName)->second;
   
}

vector<Territory*> Map::getAllTerritory() { return allTerritory; }
vector<Continent*> Map::getAllContinent() { return allContinent; }
void Map::setMapName(string mName)
{
    mName = mName;
}

void Map::addEdge(vector<int> graph[], int source, int destination)
{
    graph[source].push_back(destination);
    //Uncomment to check if edge has been added
    /*string sourceTerritory = getTerritoryNameFromTerritoryID(source);
    string destinationTerritory = getTerritoryNameFromTerritoryID(destination);
    cout << "edge from " << sourceTerritory << " to " <<destinationTerritory << " has been added!" <<endl;
    */
}

bool Map::edgeExistance(vector<int>graph[], int src, int destination)
{
    for (int i = 0; i < allTerritory.size(); i++)
    {
        for (auto x : graph[i])
        {
            if (src == i && destination == x)
                return true;
        }
        
    }
    return false;
}

void Map::printGraph(vector<int> graph[])
{
    string territoryName;
    for (int v = 0; v < allTerritory.size(); ++v) {
        territoryName = getTerritoryNameFromTerritoryID(v);
        cout << "\n Adjacency list of territory " << territoryName <<endl;
        cout << "\n " <<v;
        for (auto x : graph[v])
            cout << "-> " << x;
        printf("\n");
    }
}