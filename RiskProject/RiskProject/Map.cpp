#include "Map.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <stack>
#include<algorithm>
#include<vector>
#include <typeinfo>

class Player;
//for the Territory Class
// Constructors 
Territory::Territory(int tID, int cID) {
    Player* nullPlayer = new Player();
    owner = nullPlayer;
    name = "Default";
    continentID = cID;
    territoryID = tID;
    vector<Territory*> adjTerritories;
    armyAmount = 0;
}
Territory::Territory(int tID, int cID, string o){
    owner = NULL;
    continentID = cID;
    territoryID = tID;
    name = o;
    vector<Territory*> adjTerritories;
    armyAmount = 0;
}

//stream Insertion
ostream& operator<<(ostream& out, const Territory& p)
{
    out << p.name << " " << p.territoryID << " " << p.continentID << endl;
    return out;
}

//copy constructor
Territory::Territory(const Territory& other) : adjTerritories(other.adjTerritories.size()) {
    continentID = other.continentID;
    territoryID = other.territoryID;
    name = other.name;
    armyAmount = other.armyAmount;
    owner = other.owner;

    for (auto p : other.adjTerritories) {
        Territory* temp = new Territory(*p);
        adjTerritories.push_back(temp);
    }
}

//assignment operator
Territory& Territory::operator=(const Territory& t)
{
    continentID = t.continentID;
    territoryID = t.territoryID;
    name = t.name;
    armyAmount = t.armyAmount;
    owner = t.owner;

    for (auto p : t.adjTerritories) {
        Territory* temp = new Territory(*p);
        adjTerritories.push_back(temp);
    }
    return *this;
}

//destructor
Territory::~Territory() {
    cout << "The territory " << name << " was deleted." << endl;
    adjTerritories.clear();
}

int Territory::getCID(){
    return continentID;
}
int Territory::getTID(){
    return territoryID;
}
vector<Territory*> Territory::getAdjTerritories(){
    return adjTerritories;
}
void Territory::addAdj(Territory* o){
    adjTerritories.push_back(o);
}

void Territory::setOwner(Player* o){
    owner = o;
}

string Territory::getTName(){
    return name;
}

int Territory::getArmyAmount() { return armyAmount; }

//for the Continent struct
// constructor
Continent::Continent(int cID, string name) {
    this->cID = cID;
    this->name = name;
    vector<Territory*> subGraph;

}

Continent::Continent(int cID, string name, int armyValue) {
    this->cID = cID;
    this->name = name;
    vector<Territory*> subGraph;

}

Continent::Continent(const Continent& other) : subGraph(other.subGraph.size()) {
    this->cID = cID;
    this->name = name;

    for (auto p : other.subGraph) {
        Territory* temp = new Territory(*p);
        subGraph.push_back(temp);
    }

}
// stream insertion
ostream& operator<<(ostream& out, const Continent& p)
{
    out << "Territories that belong to the Continent: " << endl;
    for (Territory* a : p.subGraph) {
        out << *a;
    }
    return out;
}

//assignment operator
Continent& Continent::operator=(const Continent& c){
    this->cID = c.cID;
    this->name = c.name;

    for (auto p : c.subGraph) {
        Territory* temp = new Territory(*p);
        subGraph.push_back(temp);
    }
    return *this;
}

// Desructor 
Continent::~Continent() {
    for (auto p : subGraph) {
        delete p;
    }
    subGraph.clear();
}

vector<Territory*> Continent::getSubGraph() {
    return subGraph;
}

//constructors
Map::Map(){
    numTerritories = 0;
}

Map::Map(const Map& other) {
    numTerritories = other.numTerritories;
    allContinent = other.allContinent;
    allTerritory = other.allTerritory;
}

// Destructor for the Map Class
Map:: ~Map() {
    allContinent.clear();
    allTerritory.clear();
}

//stream Insertion
ostream& operator<<(ostream& out, const Map& p)
{
    out << "Territories in the Map: " << endl;
    for (Territory* a : p.allTerritory) {
        out << *a;
    }
    out << "Continents in the Map: " << endl;
    for (Continent* a : p.allContinent) {
        out << a->name << " " << a->cID << endl;
    }
    return out;
}

void Map::addContinent(Continent* theContinent){
    allContinent.push_back(theContinent);
}

void Map::addTerritory(Territory* theTerritory) {
    allTerritory.push_back(theTerritory);
}

bool Map::getValid() { return valid; }

void Map::setValid(bool b) {
    valid = b;
}
vector<Territory*> Map::getAllTerritory() {
    return allTerritory;
}

vector<Continent*> Map::getAllContinent() {
    return allContinent;
}

// Given a territory ID, will return the associate Territory Object
Territory* Map::getTerritory(int territoryToFind) {
    vector<Territory*> currentTerritoryVector = this->getAllTerritory();
    Territory* theTerritory = 0;
    for (auto t : currentTerritoryVector) {
        if (t->getTID() == territoryToFind)
            theTerritory = t;
    }
    return theTerritory;
}


// Functions for Map Validation

// Checks that the given Map object is a connected graph
bool Map::isConnected() {
    for (int i = 0; i < numTerritories; i++) {
        DFS(i); // fill in the boolean values in wasVisited vector
        for (int j = 0; j < numTerritories; j++) {
            if (!visited[j])    // check if there is any false value in the above array, which means the graph is not connected
            {
                int index = i;
                cout << "TerritoryId " << (index + 1) << " cannot reach to all the other territories: ";  // print which continentID is not inner connected
                cout << "The map is not connected" << endl;
                return false;
            }
        }
    }
    delete visited;
    cout << "The map is a connected graph." << endl;
    return true;
}
// Assists the isConnected function
void Map::DFS(int s) {

    //starting with all nodes as not visited
    for (int i = 0; i < numTerritories; i++) {
        visited[i] = false;
    }
    // Let the helper do the DFS recursively
    DFS_helper(s, visited);

}
// Assists the isConnected function
void Map::DFS_helper(int s, bool* visitedOrNot) {
    // mark the current node as visited
    visitedOrNot[s] = true;

    // Go through the neighbors vector	

    for (int i : neighbors[s]) {
        // if the neighbor is not visited, go visit that neighbor; if visited, iterate to the next neighbor
        if (!visitedOrNot[i]) {
            int index = i;
            int index2 = s;
            DFS_helper(i, visitedOrNot);
        }
    }

}


bool Map::continentSubgraphs(Map* map) {
    vector<Territory*> trr = map->getAllTerritory();

    for (Continent* con : map->getAllContinent()) {
        int bond = con->subGraph.size();
        visited = new bool[bond];
        for (int i = 0; i < bond; i++) {

            DFS1(i, bond, trr); // fill in the boolean values in wasVisited vector
            for (int j = 0; j < bond; j++) {
                if (!visited[j])    // check if there is any false value in the above array, which means the graph is not connected
                {
                    cout << "Problem" << j << endl;
                    cout << "The continent " << con->name << " is not a connected graph." << endl;  // print which continentID is not inner connected
                    return false;

                }
            }
        }
    }

    delete visited;
    cout << "All the continents are connected subgraphs" << endl;
    return true;

}
// Assists the continentSubgraph function
void Map::DFS1(int s, int bond, vector<Territory*> trr) {

    //starting with all nodes as not visited
    for (int i = 0; i < bond; i++) {
        visited[i] = false;
    }
    // Let the helper do the DFS recursively
    DFS_helper1(s, visited, trr);

}
// Assists the continentSubgraph function
void Map::DFS_helper1(int s, bool* visitedOrNot, vector<Territory*> trr) {



    int tID = trr[s]->getTID();
    int cID = trr[s]->getCID();
    vector<int> localNeighbors = neighbors[s]; // [1] connects to [21] [3] => localNeighbors[0] is (21-1) 

    // mark the current node as visited
    visitedOrNot[s] = true;

    // Go through the neighbors vector	
    for (int i = 0; i < neighbors[s].size(); i++)
    {
        int tID2 = localNeighbors[i];
        int cID2 = trr[tID2]->getCID();

        if ((cID2 == cID) && (!visitedOrNot[tID2]))
        {
            int index = s;
            //cout << "Going to visit " << tID2+1 << " from " << (index + 1) << endl;
            DFS_helper1(tID2, visitedOrNot, trr);

        }

    }

}

// Will traverse through countryList, checking that each entry has a valid unique value for continentID
bool Map::countryToContinentRelation() {
    //This method checks only for copies of Territory objects. Two Territories of the same name, but stored at different addresses, will not count as copies. 
    int sum = 0;
    cout << "Checking Relation between Territories and Continents" << endl;
    for (Territory* currentTerritory : allTerritory) {
        sum = 0;
        for (Continent* p : allContinent) {
            vector<Territory*> contains = p->getSubGraph();
            string terrName = currentTerritory->getTName();
            auto it = find_if(contains.begin(), contains.end(), [&terrName](Territory* obj) {
                return obj->getTName() == terrName; });
            if (it != contains.end()) {
                sum++;
                cout << "\tFound " << currentTerritory->getTName() << " in " << p->name << ". It has been found in " << sum << " continents." << endl;

            }
            if (sum > 1) {
                cout << "\tTerritory " << currentTerritory->getTName() << " belongs to more than one continent." << endl;
                return false;
            }
        }
        if (sum > 1) {
            cout << "\tTerritory " << currentTerritory->getTName() << " belongs to more than one continent." << endl;
            return false;
        }

    }
    cout << "Each Territory on the Map Belongs on One and Only One Continent" << endl;
    return true;
}

// Checks isConnected, continentSubgraphs and countryToContinentRelation. Returns True when all are True.
// Is called during MapLoader::loadMap()
bool Map::validate(bool a, bool b, bool c) {
    if (a && b && c) {
        cout << "MAP VALIDITY: The Map is valid." << endl;
        return true;
    }
    else {
        cout << "MAP VALIDITY: The Map is NOT valid." << endl;
        return false;
    }
}

bool Map::validate(void) {
    bool a = isConnected();
    bool b = continentSubgraphs(this);
    bool c = countryToContinentRelation();
    if (a && b && c) {
        cout << "MAP VALIDITY: The Map is valid." << endl;
        return true;
    }
    else {
        cout << "MAP VALIDITY: The Map is NOT valid." << endl;
        return false;
    }
}



