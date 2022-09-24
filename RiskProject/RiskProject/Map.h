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
    string territoryOwner;            //the owner of a territory
    int tID;                          // the ID of a territory
    int playerID;                     // the ID of a player
    int armyAmount;                   //the amount of army in a territory
  
    
public: 
    vector<string> adjacentTerritoryMembers;  //the list of adjacent territories
    friend ostream& operator<< (ostream& out, const Territory& t); // stream insertion operator

    Territory();                                                                //default constructor
    Territory(const Territory*);                                                //copy constructor
    Territory(string tName, string continentName, int tID);   //four parameter constructor
    Territory& operator= (const Territory&);                                   //assigment operator
    ~Territory();                                                              //destructor
    
    string getTName();
    string getContinentName();
    int getTID();
    int getPlayerID();
    int getArmyAmount();
    void setTName(string tName);
    void setTID(int tID);
    vector<string> getAdjacentTerritoryMembers();
};

class Continent
{
private:
    string cName;
    int cID;

public:
   /* TODO  friend ostream& operator<< (ostream& out, const Continent& t);*/ // stream insertion operator

    Continent();                              //default constructor
    //TODO  Continent(const Continent*);             //copy constructor
    Continent(string cName, int cID);        //two parameter constructor
    //TODO  Continent& operator= (const Continent&);   //assigment operator
    //TODO   ~Continent();                             //destructor

    string getCName();
    int getCID();
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
    vector<int> graph[200]; //territories - if territories are connected then the continents MUST be connected -> thus only need to validate the connectedness of territories 
    //friend ostream& operator<< (ostream& out, const Continent& t); // stream insertion operator

    Map();                                     //default constructor
   /*TODO   Map(const Continent*);     */              //copy constructor
    Map(string mName);                    //two parameter constructor
    //TODO   Map& operator= (const Map&);          //assigment operator
    //TODO  ~Map();
    
    string getMName();
    string getTerritoryNameFromTerritoryID(int tID);
    int getTerritoryIDFromTName(string tName);
    vector<Territory*> getAllTerritory();
    vector<Continent*> getAllContinent();
    void setMapName(string mName);
    void addEdge(vector<int> graph[], int src, int dest);
    bool edgeExistance(vector<int>graph[], int src, int destination);
    void printGraph(vector<int> graph[]);
    //TODO   void validate();

};

//Requirments from Assignment #1 description:
//All classes must implement a correct copy constructor, assignment operator,and stream insertion operator.