#include "Map.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
    out << "Territories that belong to " << p.name << "the Continent : " << endl;
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
    cout << "The continent " << name << " was deleted." << endl;
    for (auto p : subGraph) {
        delete p;
    }
    subGraph.clear();
}

vector<Territory*> Continent::getSubGraph() {
    return subGraph;
}
//default constructor
MapLoader::MapLoader() {
    cout << "MapLoader created" << endl;
}
 

//copy constructor
MapLoader::MapLoader(const MapLoader& other) {
    inputFileName = other.inputFileName;
    loadedMap = other.loadedMap;

}

//assignment operator
MapLoader& MapLoader::operator = (const MapLoader& ml) {
    this->loadedMap = ml.loadedMap;
    this->inputFileName = ml.inputFileName;
    return *this;
}

//stream insertion operator
ostream& operator << (ostream& out, const MapLoader& p) {
    out << "Loaded File: " << p.inputFileName << endl;
    return out;
}

//destructor
MapLoader::~MapLoader() {
    cout << "MapLoader was destroyed" << endl;
    for (auto p : loadedMap) {
        delete p;
    }
    loadedMap.clear();
}

//accessor
string MapLoader::getInputFileName() {
    return inputFileName;
}

//mutator
void MapLoader::setInputFileName(const string& s) {
    inputFileName = s;
}

vector<Map*> MapLoader::getMaps() {
    return loadedMap;
}

//splits the line information from the text file by certain delimiter
vector<string> MapLoader::tokenizeString(const string& s, char delimiter) {
    vector <string> tokens;                   // Vector of string to save tokens
    stringstream text(s);                     // stringstream class check1
    string token;
    while (getline(text, token, delimiter))  // Tokenizing by delimiter like '=', ','
    {
        tokens.push_back(token);
    }
    return tokens;
}


//gets the continent ID by given continent name
int MapLoader::getCID(Map* createdMap, string cName) {
    for (auto conti : createdMap->getAllContinent()) {
        /*    cout <<"conti:" << conti->name << "find name" << cName;*/
        if (conti->name == cName) {
            return conti->cID;
        }
    }
}

//helps to compare the string ignore the case issue
bool iequals(const string& a, const string& b)
{
    return std::equal(a.begin(), a.end(),
        b.begin(), b.end(),
        [](char a, char b) {
            return tolower(a) == tolower(b);
        });
}

//gets the territory ID by given territory name
int MapLoader::getTID(Map* createdMap, string tName) {
    for (auto terri : createdMap->getAllTerritory()) {
        if (iequals(terri->getTName(), tName)) {
            return terri->getTID();
        }
    }
    return -1;
}


//reads the map file and stores the map as a Map object 
Map* MapLoader::loadMap(string mapFile) {
    ifstream input;
    bool readingContinents = false;
    bool readingTerritories = false;
    Map* createdMap = new Map();
    createdMap->setName(mapFile);
    vector<string> contents;
    bool validCondition1 = false, validCondition2 = false;
    int createdConti = 0;
    int createdTerri = 0;
    vector<vector<string>> allAdjTerritories;

    input.open(mapFile);
    if (input) {
        string current;
        cout << "----------------------------------------" << endl;
        //check if file exists but is empty
        if (input.peek() == std::ifstream::traits_type::eof()) {
            cout << "ERROR - File is empty!" << endl;
            throw invalid_argument("Received Empty File.");
            return createdMap;
        }
        else {

            while (input.peek() != EOF && getline(input, current)) {
                if (current == "[Continents]") {
                    getline(input, current);
                    readingContinents = true;
                    readingTerritories = false;
                    validCondition1 = true;


                }
                else if (current == "[Territories]") {
                    getline(input, current);
                    readingContinents = false;
                    readingTerritories = true;
                    validCondition2 = true;

                }

                if (readingContinents) { //reads and adds continent objects
                    createdConti++;
                    contents = tokenizeString(current, '=');
                    if (contents.size() > 0) {
                        string name = contents[0];
                        int cID = createdConti;
                        int armyValue = stoi(contents[1]);
                        Continent* rec = new Continent(cID, name, armyValue);
                        createdMap->addContinent(rec);
                    }

                }
                else if (readingTerritories)
                {
                    contents = tokenizeString(current, ',');
                    createdTerri++;
                    if (contents.size() > 0)
                    {
                        int tID = createdTerri;
                        string tName = contents[0];
                        string cName = contents[3];
                        int cID = getCID(createdMap, cName);
                        Territory* ret = new Territory(tID, cID, tName);
                        createdMap->addTerritory(ret);
                        vector<string> adjTerritories;
                        adjTerritories.push_back(contents[0]);
                        for (int i = 4; i < contents.size(); i++) {
                            adjTerritories.push_back(contents[i]);
                        }
                        allAdjTerritories.push_back(adjTerritories);

                        for (Continent* cont : createdMap->getAllContinent()) {
                            if (cont->cID == cID) {
                                cont->subGraph.push_back(ret);
                            }
                        }

                    }

                    else if (contents.size() <= 0) {
                        createdTerri--;
                        continue;
                    }

                    createdMap->numTerritories = createdTerri;

                }
                else {
                    /*cout << current << endl;*/
                    readingContinents = false;
                    readingTerritories = false;
                }

            }
            if (validCondition1 && validCondition2) {
                cout << "EOF" << endl;
                // adds adjacent territories as a object vector to associated territory 
                for (auto v : allAdjTerritories) {
                    if (v.size() > 0) {
                        vector<int> edges;

                        for (string p : v) {
                            int tID = getTID(createdMap, p);
                             if (tID < 0) {
                                 cout << "ERROR - File is of incorrect format! Tertitories message is missing. Please check that the file meets the Map parameters." << endl;
                                 throw invalid_argument("ERROR - File is of incorrect format! Keywords were not found.");
                                 return createdMap;
                             }
                            edges.push_back(getTID(createdMap, p)); //1 2 3
                        }

                        Territory* t = createdMap->getAllTerritory()[edges[0] - 1]; // 1
                      /*  int k = edges[0] - 1;*/

                        for (int i = 1; i < edges.size(); i++) { // add 2 and 3 to 1's territories
                            Territory* o = createdMap->getAllTerritory()[edges[i] - 1];
                            t->addAdj(o);

                        }

                    }

                }
                //Printing territories that belong to the first continent:
                cout << "Reading file is complete! Here is First Continent Information:" << endl;
                cout << *createdMap->getAllContinent()[0] << endl;


                // validate() method here
                cout << "\nValidating Map " << endl;
                cout << "\n---------------------------------------------------" << endl;
                bool result = createdMap->validate();
                if (result) {
                    loadedMap.push_back(createdMap);
                    createdMap->setValid(true);
                    return createdMap;
                }
                else {
                    loadedMap.push_back(createdMap);
                    createdMap->setValid(false);
                    return createdMap;
                }

            }
            else {
                cout << "ERROR - File is of incorrect format! Keywords were not found. Please check that the file meets the Map parameters." << endl;
                throw invalid_argument("ERROR - File is of incorrect format! Keywords were not found.");
                return createdMap;
            }

        }

    }
    else {
        cout << "ERROR - File could not be opened!" << endl;
        throw invalid_argument("ERROR - File could not be opened!");
        return createdMap;
    }


    //Map Creation:
    loadedMap.push_back(createdMap);
    return createdMap;


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
    for (auto c : allContinent) { delete c; }
    allContinent.clear();
    allTerritory.clear();
    cout << "The map " << name << " was deleted." << endl;
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

string Map::getName() { return name; }
void Map::setName(string n) {
    name = n;
}
vector<Territory*> Map::getAllTerritory() {
    return allTerritory;
}

vector<Continent*> Map::getAllContinent() {
    return allContinent;
}

// Given a territory string, will return the associate Territory Object
Territory* Map::getTerritory(string territoryToFind) {
    vector<Territory*> currentTerritoryVector = this->getAllTerritory();
    Territory* theTerritory = 0;
    for (auto t : currentTerritoryVector) {
        if (t->getTName() == territoryToFind)
            theTerritory = t;
    }
    return theTerritory;
}

// Functions for Map Validation 
//helper function for the DFS_helper to check a certain string in a string vector or not
bool Map::isContains(string s, vector<string> s_v) {
    return (find(s_v.begin(), s_v.end(), s) != s_v.end());
}

// Checks that the given Map object is a connected graph
bool Map::isConnected() {
    for (auto t : this->getAllTerritory()) {
        DFS(t->getTName(), t);
        for (auto t : this->getAllTerritory()) { 
            if (!(_visited.size() == this->getAllTerritory().size()))  // check if the traverse nodes is equal all nodes, which means the graph is not connected
            { 
                cout << "Territory " << t->getTName() << " cannot reach to all the other territories: ";  // print which continent is not inner connected
                cout << "The map" << this->name << " is not connected" << endl;
                return false;
            
            }
        }

    }
    _visited.clear();
    cout << "The map " << this->name << " is a connected graph." << endl;
    return true;
}

// Assists the isConnected function
void Map::DFS(string s, Territory* t) {
    _visited.clear(); //starting with all nodes as not visited
    DFS_helper(s, t->getAdjTerritories()); 	// Let the helper do the DFS recursively

}

// Assists the isConnected function
void Map::DFS_helper(string s, vector<Territory*> terr) {
    _visited.push_back(s); // mark the current node as visited
    for (auto t : terr) { // Go through the neighbors vector, if not visited, go visit, if visited, iterate to next one
        if (!isContains(t->getTName(), _visited)) {
            DFS_helper(t->getTName(), t->getAdjTerritories());
            
        }
    }
}

//Almost the same checking steps for the subgraph
bool Map::checkSubGraph(vector<Territory*> subGraph) {
    for (auto t : subGraph) {
        DFS1(t->getTName(), t);
        for (auto t : subGraph) {
        
            if (!(_visited.size() == subGraph.size())) {
               
                cout << "Territory " << t->getTName() << " cannot reach to all the other territories: ";  // print which continentID is not inner connected
                return false;

            }
        }

    }
    _visited.clear();
    return true;
}

void Map::DFS1(string s, Territory* t) {
    _visited.clear();
    DFS_helper1(s, t->getAdjTerritoriesInSameContinent());

}

void Map::DFS_helper1(string s, vector<Territory*> terr) {
    _visited.push_back(s);
    for (auto t : terr) {
   /*     cout << "_visited.size" << _visited.size() << endl;*/
        if (!isContains(t->getTName(), _visited)) {
         /*   cout << t->getTName() << endl;*/
          /*  cout << "_visited.size" << _visited.size() << endl;*/
            DFS_helper1(t->getTName(), t->getAdjTerritoriesInSameContinent());

        }
    }
}

//checks the continent as subgraph one by one
bool Map::continentSubgraphs(Map* map) {
    for (Continent* con : map->getAllContinent()) {
        if (!checkSubGraph(con->subGraph)) {
            cout << "The continent " << con->name << " is not a connected graph." << endl;  
            return false;
        }
        else {
            cout << "The continent " << con->name << " is a connected graph." << endl;
        }
    }
    cout << "All the continents are connected subgraphs" << endl;
    return true;
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


