#pragma once
#include <string>
#include <vector>
#include <set>
#include<map>
#include <list>
using namespace std;

class Territory
{
private:
    string tName;                      //the name and continent of a territory
    string continentName;
    string territoryOwner;   
    int xCoord;
    int yCoord;         //the owner of a territory
    int TID;    
    int continentID;   
    int playerID;                     // the ID of a player
    int armyAmount;                   //the amount of army in a territory
    // vector<Territory*> adjacentTerritoryMembers; 
    
public: 
     //the list of adjacent territories
    friend ostream& operator<< (ostream& out, const Territory& t); // stream insertion operator
    vector<Territory*> adjacentTerritoryMembers; 
    Territory();                                                                //default constructor
    Territory(Territory* t);                                                //copy constructor
    Territory(int TID, int xCoord, int yCoord, string tName, int continentID);   //five parameter constructor
    Territory& operator= (Territory* t);                                   //assigment operator
    // ~Territory();                                                              //destructor
    void addAdjacentTerritoryMembers(Territory* t);
    void adjacentTerritoryMembersToString();
    const string getTName() const;
    const int getContinentID() const;
    const int getTID() const;
    const int getPlayerID() const ;
    const int getXCoord() const; 
    const int getYCoord() const;
    int getArmyAmount();
    void setTName(string tName);
    void setTID(int tID);
    // void addEdge(vector<int> graph[], int src, int dest);

    const vector<Territory*> getAdjacentTerritoryMembers() const;
    string toString();
};

class Continent
{
private:
    string cName;
    int continentID;
    int numberOfTerritories;
    vector<Territory*> territories;
public:
   /* TODO  friend ostream& operator<< (ostream& out, const Continent& t);*/ // stream insertion operator

    Continent();                              //default constructor
    Continent(Continent* c);             //copy constructor
    Continent(int continentID, string cName, int numberOfTerritories);        //two parameter constructor
    Continent& operator= (Continent* c);   //assigment operator
    void addTerritory(Territory* t);
    const int getNumberOfTerritories() const;
    const string getCName() const;
    const int getContinentID() const;
    vector<Territory*> getTerritories();
    string toString();
    void territoriesToString();
};

class Map
{
private:
    string mName;

public:
    vector<Territory*> allTerritory;
    vector<Continent*> allContinent;
    map<string, int> territoryIndexDictionary;
    map<string, int> continentIndexDictionary;
    // void addContinent(Continent* continent);
    // void addTerritory(Territory* territory);
    vector<int> graph[200]; //territories - if territories are connected then the continents MUST be connected -> thus only need to validate the connectedness of territories 
    //friend ostream& operator<< (ostream& out, const Continent& t); // stream insertion operator

    Map();  
    Map(Map* map);     
    Map& operator=(Map* map);                             
    Map(string mName);                    //two parameter constructor
    void addContinent(Continent* c);
    void addTerritory(Territory* t);
    void addAdjacentTerritoryMembers(vector<Territory*> addTerritories);
    string getMName();
    string getTerritoryNameFromTerritoryID(int tID);
    int getTerritoryIDFromTName(string tName);
    vector<Territory*> getAllTerritory();
    vector<Continent*> getAllContinent();
    void setMapName(string mName);
    //void addEdge(vector<int> graph[], int src, int dest);
    //bool edgeExistance(vector<int>graph[], int src, int destination);
    bool validate();
    bool eachTerritoryToContinent();
    void dfsForTerritories(int territoryID, Territory* territory, vector<bool>& visitedTerritories);
    void dfsForContinentSubGraph(int territoryID, int continentID, Territory* territory, vector<bool>& visitedTerritories, vector<int>& subGraphCounter );
    void printGraph(vector<int> graph[]);
    Territory* getTerritoryID(int territoryID);
    Continent* getCID(int continentID);
    //TODO   void validate();

};

//Requirments from Assignment #1 description:
//All classes must implement a correct copy constructor, assignment operator,and stream insertion operator.