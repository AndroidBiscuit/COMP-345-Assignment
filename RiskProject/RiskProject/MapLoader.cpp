#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"
#include "Map.h"

//default constructor
MapLoader::MapLoader() {
    myMap = nullptr;
    inputFileName = "none";
}

//copy constructor
MapLoader::MapLoader(const MapLoader* ml) {
    myMap = ml->myMap;
    inputFileName = ml->inputFileName;
}

//two parameters constructor
MapLoader::MapLoader(Map* myMap, string fileName) {
    this->myMap = new Map();
    this->inputFileName = fileName;
    
}

//assignment operator
MapLoader& MapLoader::operator = (const MapLoader& ml) {
    this->myMap = ml.myMap;
    this->inputFileName = ml.inputFileName;
    return *this;
}

//stream insertion operator
ostream& operator<< (ostream& out, const MapLoader& m) {
    out << m.myMap << m.inputFileName << endl;
    return out;
}

//destructor
MapLoader::~MapLoader() {
    inputFileName.clear();
    delete myMap;
    myMap = NULL;
}

//accessor
string MapLoader::getInputFileName() {
    return inputFileName;
}

//mutator
void MapLoader::setInputFileName(const string& s) {
    inputFileName = s;
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

// captitalizes the first character of the name of Territories or continents
void MapLoader::toUpper(std::string& str) {
    if (str.length() == 0) {
        return;
    }

    str[0] = std::toupper(str[0]);
}


//reads the map file and stores the map as a Map object 
void MapLoader::parseMapFile() {
    bool mapFlag = false;
    bool continentFlag = false;
    bool territoryFlag = false;
    string lineText;             
    // Read from the text file
    ifstream MyReadFile(this->inputFileName);
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, lineText)) {
        if (lineText == "[Map]") {
            mapFlag = true;
            continue;
        }
        if (mapFlag) {
            this->myMap = new Map();
            mapFlag = false;
            
        }
        if (lineText != "[Continents]" && !continentFlag && !territoryFlag) {
            continue;
        }
        if (lineText == "[Continents]") {
            continentFlag = true;
            continue;
        }
        if (continentFlag) {
            vector<string> lineTokens;
            lineTokens = tokenizeString(lineText, '=');
            if (lineText.empty()) {
                continentFlag = false;
                territoryFlag = true;
                continue;
            }
        
            toUpper(lineTokens[0]);
            myMap->allContinent.push_back(new Continent(lineTokens[0]));
           /* cout << "Information" << line[0] << cID << endl;*/


        }

//TODO:  Start to update this part this afternoon 15:00 2022-9-22
    //    if (myText == "[Territories]") {
    //        myMap->numOfAllTerritory = continentNum;
    //        territoryFlag = true;
    //        continue;
    //    }

    //    if (territoryFlag) {
    //        cout << territoryNum << endl;
    //        if (myText.empty()) {
    //            /* cout << "Wrong MapFile format!!! Map has invalid Territory elements" << endl;*/
    //            continue;
    //        }
    //        else {
    //            territoryNum++;
    //        }
    //        vector<string> line;
    //        cout << "TERRI:" << myText << endl;
    //        line = tokenizeString(myText, ',');
    //        int tID = territoryNum;
    //        cout << "tID:" << tID << endl;
    //        int continentID = getIndex(continents, line[3]);
    //        cout << "continentID" << continentID << endl;
    //        myMap->allTerritory.push_back(new Territory(line[0], line[3], tID, continentID));
    //        toUpper(line[0]);
    //        territories.push_back(line[0]);

    //        string adj{};
    //        for (int i = 3; i < line.size(); i++) {
    //            toUpper(line[i]);
    //            if (i == line.size() - 1) {
    //                adj += line[i];
    //            }
    //            else {
    //                adj += line[i] + ",";
    //            }

    //        }
    //        adjacentTerritory.push_back(adj);


    //    }
    //}
    //cout << "adjacent Territory size" << adjacentTerritory.size() << endl;

    //for (int i = 0; i < adjacentTerritory.size(); i++) {
    //    adjacentRow = i;
    //    vector<string> adj;
    //    adj = tokenizeString(adjacentTerritory[i], ',');
    //    cout << adjacentTerritory[i] << endl;
    //    for (int j = 1; j < adj.size(); j++) {
    //        worldMap->allTerritory[adjacentRow]->adjacentTerritoryInMap.push_back(adj[j]);
    //        int territoryID = getIndex(territories, adj[j]);
    //        cout << "territory ID: " << territoryID << adj[j] << endl;
    //        string currentContinent = worldMap->allTerritory[territoryID]->getContinentName();
    //        int continentID = getIndex(continents, currentContinent);
    //        cout << "current Continent: " << currentContinent << endl;
    //        cout << "Terri continent: " << adj[0] << endl;
    //        if (currentContinent == adj[0]) {
    //            /* cout << "HereFlat" << endl;*/
    //            worldMap->allTerritory[territoryID]->adjacentTerritoryInSameContinent.push_back(adj[j]);
    //        }
    //        if (currentContinent != adj[0]) {
    //            cout << "HereFlat" << endl;
    //            cout << worldMap->allTerritory[territoryID]->getContinentName() << endl;
    //            worldMap->allContinent[continentID]->reachableForeignContinent.insert(worldMap->allTerritory[territoryID]->getContinentName());
    //            /* cout << "reachable conti" << worldMap->allContinent[continentID]->reachableForeignContinent.size() << endl;*/
    //        }
    //    }


    //}
    //myMap->setNumOfAllTerritory(worldMap->allTerritory.size());
    //cout << "all Territory size" << worldMap->allTerritory.size() << endl;

    // Close the file
    MyReadFile.close();
}
