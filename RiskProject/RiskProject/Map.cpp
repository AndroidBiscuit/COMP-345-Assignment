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

vector<Territory*> Territory::getAdjTerritoriesInSameContinent() {
    vector<Territory*> adjTerritoriesInSameContinent;
    for (auto t : adjTerritories) {
        if (t->getCID() == this->getCID()) {
            adjTerritoriesInSameContinent.push_back(t);
        }
    }

    return adjTerritoriesInSameContinent;
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
//check continent's subGraph is a connected graph or not
//if subGraph is good, return true.
//if not, return false.
bool Continent::checkSubGraph()
{
    int len = this->subGraph.size();//get length of all nodes in one continent
    vector<string> visited;//record all visited node in same continent
    for (int i = 0; i < len; i++) {//loop all nodes
        if (visited.empty()) {//add first node into visited list
            visited.push_back(this->subGraph[i]->getTName());
        }
        int len1 = this->subGraph[i]->getAdjTerritoriesInSameContinent().size();//get length of each node's adjacent list
        for (int j = 0; j < len1; j++) {//loop the adjacent list
            string temp = this->subGraph[i]->getAdjTerritoriesInSameContinent()[j]->getTName();//get the adjacent node id
            int len2 = visited.size();//get the length of visited list
            for (int k = 0; k < len2; k++) {//loop visited list
                if (temp == visited[k]) {//if adjacent node id exist in visited list, goto next adjacent node
                    break;
                }
                if (k == (len2 - 1)) {//if adjacent node not exist in visited list, add it into visited list
                    if (temp != visited[k]) {
                        visited.push_back(temp);
                    }
                }
            }
        }
    }
    if (visited.size() != len) {//all visited list length should equal length of all nodes in one continent
        return false;//subgraph is not connected
    }
    return true;//subgraph is connected
}


// Checks that the given Map object is a connected graph
bool Map::isConnected() {
    int len = this->allTerritory.size();//get length of all nodes in one map
    vector<string> visited;//record all visited node in same continent
    for (int i = 0; i < len; i++) {//loop all nodes
        if (visited.empty()) {//add first node into visited list
            visited.push_back(this->allTerritory[i]->getTName());
        }
        int len1 = this->allTerritory[i]->getAdjTerritories().size();//get length of each node's adjacent list
        for (int j = 0; j < len1; j++) {//loop the adjacent list
            string temp = this->allTerritory[i]->getAdjTerritories()[j]->getTName();//get the adjacent node id
            int len2 = visited.size();//get the length of visited list
            for (int k = 0; k < len2; k++) {//loop visited list
                if (temp == visited[k]) {//if adjacent node id exist in visited list, goto next adjacent node
                    break;
                }
                if (k == (len2 - 1)) {//if adjacent node not exist in visited list, add it into visited list
                    if (temp != visited[k]) {
                        visited.push_back(temp);
                    }
                }
            }
        }
    }
    if (visited.size() != len) {//all visited list length should equal length of all nodes in one map
        cout << "The map is not connected" << endl;
        return false;//graph is not connected
    }
    cout << "The map is a connected graph." << endl;
    return true;//graph is connected
}

bool Map::continentSubgraphs(Map* map) {
    for (Continent* con : map->getAllContinent()) {
        if (!con->checkSubGraph()) {
            cout << "The continent " << con->name << " is not a connected graph." << endl;  // print which continentID is not inner connected
                    return false;
        }
        cout << "All the continents are connected subgraphs" << endl;
        return true;
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



