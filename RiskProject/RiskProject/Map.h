#pragma once
#include <string>
#include <vector>
#include <set>
using namespace std;

class Territory
{
private:
    string tName;                      //the name and continent of a territory
    string continentName;
    string territoryOwner;            //the owner of a territory
    int armyAmount;                   //the amount of army in a territory
    
public: 
    Territory();
    Territory(string tName, string continentName);
    string getTName();
    string getContinentName();
    int getArmyAmount();
    void setTName(string tName);

};

class Continent
{
private:
    string cName;
    vector<Territory*> adjacentTerritoryMembers;

public:
    Continent();
    Continent(string cName, int cID);

    string getCName();
    vector<Territory*> getAdjacentMembers();
};

class Map
{
private:
    string mName;
    vector<Territory*> allTerritory;
    vector<Continent*> allContinent;

public:
    Map();
    Map(string mName);

    string getMName();
    vector<Territory*> getAllTerritory();
    void setMapName(string mName);
    void setNumOfAllTerritory(int numOfAllTerritory);
    void setNumOfAllContinent(int numOfAllContinent);
    void validate();

};


//Requirments from Assignment #1 description:
//All classes must implement a correct copy constructor, assignment operator,and stream insertion operator.