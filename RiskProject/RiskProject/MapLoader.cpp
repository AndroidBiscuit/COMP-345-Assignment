#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include<map>
#include <sstream>
#include "MapLoader.h"
#include "Map.h"


//default constructor
MapLoader::MapLoader() {
    cout << "MapLoader created" << endl;
}

//copy constructor
MapLoader::MapLoader(const MapLoader* ml) {
    loadedMap = ml->loadedMap;
    inputFileName = ml->inputFileName;
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
}

//accessor
string MapLoader::getInputFileName() {
    return inputFileName;
}

//mutator
void MapLoader::setInputFileName(const string& s) {
    inputFileName = s;
}

Map* MapLoader::getMap(){
    return &loadedMap;
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
int MapLoader::getCID(Map* createdMap,string cName) {
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
                    cout << current << endl;
                    getline(input, current);
                    readingContinents = true;
                    readingTerritories = false;
                    validCondition1 = true;
                  

                }
                else if (current == "[Territories]") {
                    cout << current << endl;
                    getline(input, current);
                    readingContinents = false;
                    readingTerritories = true;
                    validCondition2 = true;
                  
                }

                if (readingContinents) { //reads and adds continent objects
                    cout << current << endl;
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
                    cout << current << endl;
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
                        cout << *ret;
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

                    createdMap->visited = new bool[createdTerri - 1];
                    createdMap->numTerritories = createdTerri - 1;

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
                           /* cout << "TID:" << tID << p << endl;*/
                            edges.push_back(getTID(createdMap, p)); //1 2 3
                        }

                        Territory* t = createdMap->getAllTerritory()[edges[0] - 1]; // 1
                        int k = edges[0] - 1;

                        for (int i = 1; i < edges.size(); i++) { // add 2 and 3 to 1's territories
                            Territory* o = createdMap->getAllTerritory()[edges[i] - 1];
                            t->addAdj(o);
                          
                        }
                        
                    }
                    
                }
                //Printing territories that belong to the first continent:
                cout << "Here is First Continent Information:" << endl;
                cout << *createdMap->getAllContinent()[0] << endl;
             

                // validate() method here
                cout << "\nValidating Map " << endl;
                cout << "\n---------------------------------------------------" << endl;
                bool a = createdMap->isConnected();
                bool b = createdMap->continentSubgraphs(createdMap);
                bool c = createdMap->countryToContinentRelation();
                bool result = createdMap->validate(a, b, c);
                if (result) {
                    loadedMap = *createdMap;
                    createdMap->setValid(true);
                    return createdMap;
                }
                else {
                    loadedMap = *createdMap;
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
    loadedMap = *createdMap;
    return createdMap;


}

