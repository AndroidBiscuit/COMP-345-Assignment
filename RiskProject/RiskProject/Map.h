#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
using namespace std;

class Player;

//Territory acts a the nodes of the map
class Territory{
private:
    int territoryID;
    string name;                      
    Player* owner;                   
    vector<Territory*> adjTerritories;
    int armyAmount;    
    int continentID;
  /*  Continent* cont;*/
  
    
public: 
    //Stream Insertion
    friend ostream& operator<< (ostream& out, const Territory& t); 

    //Constructors
    Territory(int tID, int cID);                                                                
    Territory(int tID, int cID, string name);
    Territory(const Territory& other);

    //assignment operator
    Territory& operator= (const Territory&);  

    //destructor
    ~Territory();          

    //accessor
    string getTName();
    int getTID();
    int getCID();
    int getArmyAmount();
    vector<Territory*> getAdjTerritories();
    vector<Territory*> getAdjTerritoriesInSameContinent();

    //methods
    void addAdj(Territory* t);
    void setOwner(Player* p);
   
};

struct Continent{
    int cID;
    string name;
    int armyValue;
    vector<Territory*> subGraph;

    //constructors
    Continent(int cID, string name);
    Continent(int cID, string name, int armyValue);
    Continent(const Continent& other);

    //friend class
    friend class MapLoader;
    friend class Map;
    Continent& operator=(const Continent& c);
    friend ostream& operator<<(ostream& out, const Continent& p);
    //accessor
    vector<Territory*> getSubGraph();
    bool checkSubGraph();
    bool getAdjacentTerritoryInSameContinent();

    //destructor
    ~Continent();
};

class Map{
private:
    string name;
    vector<Continent*> allContinent;
    bool valid = true;

public:
    vector<Territory*> allTerritory;
    //Stream insertion:
    friend ostream& operator << (ostream& out, const Map& p);

    bool* visited;
    int numTerritories;

    //friend class
    friend class Maploader;

    //constructors
    Map();
    Map(const Map& toCopy);

    //destructor
    ~Map();

    void addContinent(Continent* theContinent);
    void addTerritory(Territory* theTerritory);
    bool getValid();
    void setValid(bool);
    string getName();
    void setName(string);
    Territory* getTerritory(int territoryID);
    vector<Territory*> getAllTerritory();
    vector<Continent*> getAllContinent();

    //methods related to validate()
 
    bool validate(bool a, bool b, bool c);// Must check the following 3 functions	
    bool validate(void);
    bool isConnected(void);// Test to the see if the map is a connected graph	
    bool continentSubgraphs(Map* map); // Test to see that continents are connected subgraphs	
    bool countryToContinentRelation(void); // Test to see that each country belongs to only one continent
};

//Requirments from Assignment #1 description:
//All classes must implement a correct copy constructor, assignment operator,and stream insertion operator.